#include "sd_spi_drv.h"

#ifdef SD_CARD_SPI

SPI_HandleTypeDef sd_hspi;
uint8_t  SD_Type=0;

static void BspSdSpiGpioInit(void) {

    GPIO_InitTypeDef SPI_GPIO_Init = {
	
		#ifdef BOARD_SD_GPIO_AF
        	.Alternate = BOARD_SD_GPIO_AF, 
		#endif
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_PULLUP,
    };

    GPIO_InitTypeDef SPI_DET_GPIO_Init = {
        .Mode = GPIO_MODE_INPUT,
        .Pull = GPIO_PULLUP,
        .Speed = GPIO_SPEED_FREQ_LOW,
    };

    _SD_GPIO_CLK_ENABLE();                          // Enable SPI and GPIO Clock

    SPI_GPIO_Init.Pin = SD_SPI_MISO_PIN|
                        SD_SPI_MOSI_PIN|
                        SD_SPI_SCK_PIN;
    HAL_GPIO_Init(SD_SPI_SCK_PORT, &SPI_GPIO_Init);

    SPI_GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    SPI_GPIO_Init.Pull = GPIO_PULLUP;
    SPI_GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
    SPI_GPIO_Init.Pin = SD_SPI_CS_PIN;
    HAL_GPIO_Init(SD_SPI_CS_PORT, &SPI_GPIO_Init);

    SPI_DET_GPIO_Init.Pin = SD_DET_PIN;
    HAL_GPIO_Init(SD_DET_PORT, &SPI_DET_GPIO_Init);
}

static void BspSpiInit(void) {

    sd_hspi.Instance = SD_CARD_SPI;
    sd_hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;// SD_SPI_LOW_SPEED;
    sd_hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    sd_hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    sd_hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    sd_hspi.Init.CRCPolynomial = 10;
    sd_hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    sd_hspi.Init.Direction = SPI_DIRECTION_2LINES;
    sd_hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    sd_hspi.Init.Mode = SPI_MODE_MASTER;
    sd_hspi.Init.NSS = SPI_NSS_SOFT;
    sd_hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    if (HAL_SPI_Init(&sd_hspi) != HAL_OK) {
        Error_Handler();
    }
    __HAL_SPI_ENABLE(&sd_hspi);
}

void BspSdSetSpeed(uint32_t SPI_BaudRatePrescaler) {
    sd_hspi.Init.BaudRatePrescaler = SPI_BaudRatePrescaler;
    HAL_SPI_Init(&sd_hspi);
    __HAL_SPI_ENABLE(&sd_hspi);
}


void BspSdBegin() {
    HAL_GPIO_WritePin(SD_SPI_CS_PORT, SD_SPI_CS_PIN, GPIO_PIN_RESET);
}

void BspSdEnd() {
    HAL_GPIO_WritePin(SD_SPI_CS_PORT, SD_SPI_CS_PIN, GPIO_PIN_SET);
}

uint8_t BspSdSpiReadWriteByte(uint8_t data) {
    uint8_t rxdata = 0;
    HAL_SPI_TransmitReceive(&sd_hspi, &data, &rxdata, 1, 1000);
    return rxdata;
}

uint8_t BspDetRead(void) {

    if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(SD_DET_PORT, SD_DET_PIN)) { return 0; }
    else return 1;
}

uint32_t BspSpiAutoSpeed(void) {

	/*******************************************
	 * get_clk calc:
	 * 	spi speed = ((F_CPU / 2) / 2) / 8 (Mbyte/s)  < 10Mbyte/s 
	 */

    uint16_t get_clk = (HAL_RCC_GetHCLKFreq() / 1000000) / 2; 

    uint8_t sd_spi_min_clk_div = ((get_clk / 2) / 8) / 10;       // 8兆需要高分频

    if(sd_spi_min_clk_div <= 2)         return SPI_BAUDRATEPRESCALER_2;
    else if(sd_spi_min_clk_div <= 4)    return SPI_BAUDRATEPRESCALER_4;
    else if(sd_spi_min_clk_div <= 8)    return SPI_BAUDRATEPRESCALER_8;
    else if(sd_spi_min_clk_div <= 16)    return SPI_BAUDRATEPRESCALER_16;
    else if(sd_spi_min_clk_div <= 32)    return SPI_BAUDRATEPRESCALER_32;
    else return SPI_BAUDRATEPRESCALER_32;
}

uint8_t SdReadyWait(void) {
    
    uint32_t t=0;
	do
	{	
		if(BspSdSpiReadWriteByte(0XFF)==0XFF) return 0;
		t++;		  	
	}while(t<0XFFFFFF);  //0XFFFFFF
	return 1;
}

void SdSpiDrvDeinit(void) {
    _SD_GPIO_CLK_DISABLE();
    HAL_SPI_DeInit(&sd_hspi);
}

void SdSpiDrvInit(void) {
    BspSdSpiGpioInit();         /* Init SD SPI GPIO */
    BspSpiInit();               /* Init SD SPI */
}

void SdDisSelect(void) {
    BspSdEnd();
    BspSdSpiReadWriteByte(0xff);
}

uint8_t SdSelect() {
    BspSdBegin();
    if(SdReadyWait() ==0 ) return 0;
    SdDisSelect();
    return 1;
}

uint8_t SdGetResponseSkyblue(uint8_t Response) {

    uint16_t conut = 0xffff;
    while ((BspSdSpiReadWriteByte(0XFF)!= Response) && conut) conut--;  //等待得到准确的回应  	  
	if (conut == 0) return MSD_RESPONSE_FAILURE;                        //得到回应失败   
	else return MSD_RESPONSE_NO_ERROR;                                  //正确回应
}


uint8_t SdRecvData(uint8_t*buf, uint16_t len)
{			  	  
	if(SdGetResponseSkyblue(0xFE))return 1;//等待SD卡发回数据起始令牌0xFE
    while(len--)//开始接收数据
    {
        *buf= BspSdSpiReadWriteByte(0xFF);
        buf++;
    }
    //下面是2个伪CRC（dummy CRC）
    BspSdSpiReadWriteByte(0xFF);
    BspSdSpiReadWriteByte(0xFF);									  					    
    return 0;//读取成功
}


uint8_t SdSendBlock(uint8_t*buf,uint8_t cmd)
{	
	uint16_t t;		  	  
	if(SdReadyWait())return 1;//等待准备失效
	BspSdSpiReadWriteByte(cmd);
	if(cmd!=0XFD)//不是结束指令
	{
		for(t=0;t<512;t++) BspSdSpiReadWriteByte(buf[t]);//提高速度,减少函数传参时间
	    BspSdSpiReadWriteByte(0xFF);//忽略crc
	    BspSdSpiReadWriteByte(0xFF);
		t = BspSdSpiReadWriteByte(0xFF);//接收响应
		if((t & 0x1F) != 0x05) return 2;//响应错误									  					    
	}						 									  					    
    return 0;//写入成功
}

uint8_t SdSendCmdSkyblue(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    uint8_t r1;	

	uint8_t Retry=0; 

	SdDisSelect();//取消上次片选

	if(SdSelect()) return 0XFF;//片选失效 

	//发送
    BspSdSpiReadWriteByte(cmd | 0x40);//分别写入命令
    BspSdSpiReadWriteByte(arg >> 24);
    BspSdSpiReadWriteByte(arg >> 16);
    BspSdSpiReadWriteByte(arg >> 8);
    BspSdSpiReadWriteByte(arg);	  
    BspSdSpiReadWriteByte(crc); 
	if(cmd==CMD12) BspSdSpiReadWriteByte(0xff);//Skip a stuff byte when stop reading

    //等待响应，或超时退出
	Retry=0X1F;
	do
	{
		r1 = BspSdSpiReadWriteByte(0xFF);
	}while((r1&0X80) && Retry--);	 
	//返回状态值
    return r1;
}

uint8_t SdGetID(uint8_t *cid_data)
{
    uint8_t r1;	   
    //发CMD10命令，读CID
    r1=SdSendCmdSkyblue(CMD10,0,0x01);
    if(r1==0x00)
	{
		r1=SdRecvData(cid_data, 16);//接收16个字节的数据	 
    }
	SdDisSelect();//取消片选
	if(r1)return 1;
	else return 0;
}	

uint8_t SdGetCSD(uint8_t *csd_data)
{
    uint8_t r1;	 
    r1 = SdSendCmdSkyblue(CMD9,0,0x01);//发CMD9命令，读CSD
    if(r1==0)
	{
    	r1=SdRecvData(csd_data, 16);//接收16个字节的数据 
    }
	SdDisSelect();//取消片选
	if(r1)return 1;
	else return 0;
}  

uint32_t SdGetSectorCount(void)
{
    uint8_t csd[16];
    uint32_t Capacity;  
    uint8_t n;
	uint16_t csize;  					    
	//取CSD信息，如果期间出错，返回0
    if(SdGetCSD(csd)!=0) return 0;	    
    //如果为SDHC卡，按照下面方式计算
    if((csd[0]&0xC0)==0x40)	 //V2.00的卡
    {	
		csize = csd[9] + ((uint16_t)csd[8] << 8) + 1;
		Capacity = (uint32_t)csize << 10;//得到扇区数	 		   
    }else//V1.XX的卡
    {	
		n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
		csize = (csd[8] >> 6) + ((uint16_t)csd[7] << 2) + ((uint16_t)(csd[6] & 3) << 10) + 1;
		Capacity= (uint32_t)csize << (n - 9);//得到扇区数   
    }
    return Capacity;
}

uint8_t SdDrvInitAll(void)
{
    uint8_t r1;      // 存放SD卡的返回值
    uint16_t retry;  // 用来进行超时计数
    uint8_t buf[4];  
	uint16_t i;

	SdSpiDrvInit();

 	for( i= 0; i < 10; i++) BspSdSpiReadWriteByte(0XFF);//发送最少74个脉冲

	retry=20;

	do
	{
		r1=SdSendCmdSkyblue(CMD0,0,0x95);//进入IDLE状态
	}while((r1!=0X01) && retry--);

 	SD_Type=0;//默认无卡
	
    if(r1==0X01)
	{
		if(SdSendCmdSkyblue(CMD8,0x1AA,0x87)==1)//SD V2.0
		{
			for(i=0;i<4;i++)buf[i]=BspSdSpiReadWriteByte(0XFF);	//Get trailing return value of R7 resp
			if(buf[2]==0X01 && buf[3]==0XAA)//卡是否支持2.7~3.6V
			{
				retry=0XFFFE;
				do
				{
					SdSendCmdSkyblue(CMD55, 0, 0X01);	//发送CMD55
					r1=SdSendCmdSkyblue(CMD41,0x40000000,0X01);//发送CMD41
				}while(r1 && retry--);
				if(retry&&SdSendCmdSkyblue(CMD58,0,0X01)==0)//鉴别SD2.0卡版本开始
				{
					for(i=0;i<4;i++)buf[i]=BspSdSpiReadWriteByte(0XFF);//得到OCR值
					if(buf[0]&0x40)SD_Type=SD_TYPE_V2HC;    //检查CCS
					else SD_Type=SD_TYPE_V2;   
				}
			}
		}else//SD V1.x/ MMC	V3
		{
			SdSendCmdSkyblue(CMD55,0,0X01);		//发送CMD55
			r1=SdSendCmdSkyblue(CMD41,0,0X01);	//发送CMD41
			if(r1<=1)
			{		
				SD_Type=SD_TYPE_V1;
				retry=0XFFFE;
				do //等待退出IDLE模式
				{
					SdSendCmdSkyblue(CMD55,0,0X01);	//发送CMD55
					r1=SdSendCmdSkyblue(CMD41,0,0X01);//发送CMD41
				}while(r1&&retry--);
			}else//MMC卡不支持CMD55+CMD41识别
			{
				SD_Type=SD_TYPE_MMC;//MMC V3
				retry=0XFFFE;
				do //等待退出IDLE模式
				{											    
					r1=SdSendCmdSkyblue(CMD1,0,0X01);//发送CMD1
				}while(r1&&retry--);  
			}
			if(retry==0||SdSendCmdSkyblue(CMD16,512,0X01)!=0)SD_Type=SD_TYPE_ERR;//错误的卡
		}
	}
	SdDisSelect();//取消片选

	BspSpiAutoSpeed();
    
	if(SD_Type) {
		return 0;
	}
	else if(r1) {
		return r1;
	}

	return 0xaa;//其他错误
}


//读SD卡
//buf:数据缓存区
//sector:扇区
//cnt:扇区数
//返回值:0,ok;其他,失败.
uint8_t SdSpiReadBuff(uint8_t*buf,uint32_t sector,uint8_t cnt)
{
	uint8_t r1;
	if(SD_Type!=SD_TYPE_V2HC)sector <<= 9;//转换为字节地址
	if(cnt==1)
	{
		r1=SdSendCmdSkyblue(CMD17,sector,0X01);//读命令
		if(r1==0)//指令发送成功
		{
			r1=SdRecvData(buf,512);//接收512个字节	   
		}
	}else
	{
		r1=SdSendCmdSkyblue(CMD18,sector,0X01);//连续读命令
		do
		{
			r1=SdRecvData(buf,512);//接收512个字节	 
			buf+=512;  
		}while(--cnt && r1==0); 	
		SdSendCmdSkyblue(CMD12,0,0X01);	//发送停止命令
	}   
	SdDisSelect();//取消片选
	return r1;//
}

//写SD卡
//buf:数据缓存区
//sector:起始扇区
//cnt:扇区数
//返回值:0,ok;其他,失败.
uint8_t SdSpiWriteBuff(uint8_t*buf,uint32_t sector,uint8_t cnt)
{
	uint8_t r1;
	if(SD_Type!=SD_TYPE_V2HC)sector *= 512;//转换为字节地址
	if(cnt==1)
	{
		r1=SdSendCmdSkyblue(CMD24,sector,0X01);//读命令
		if(r1==0)//指令发送成功
		{
			r1=SdSendBlock(buf,0xFE);//写512个字节	   
		}
	}else
	{
		if(SD_Type!=SD_TYPE_MMC)
		{
			SdSendCmdSkyblue(CMD55,0,0X01);	
			SdSendCmdSkyblue(CMD23,cnt,0X01);//发送指令	
		}
 		r1=SdSendCmdSkyblue(CMD25,sector,0X01);//连续读命令
		if(r1==0)
		{
			do
			{
				r1=SdSendBlock(buf,0xFC);//接收512个字节	 
				buf+=512;  
			}while(--cnt && r1==0);
			r1=SdSendBlock(0,0xFD);//接收512个字节 
		}
	}   
	SdDisSelect();//取消片选
	return r1;//
}	



#endif
