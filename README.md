# Enter_bootloader

## Describe

On the one hand, this bootloader serves as my own functional reserve, and it will also provide the functions of a bootloader for later things.

Why would I do this? According to my own work experience and personal cognition, a bootloader should be required for the product level. The reasons are as follows:

- 1. Customers do not have JLINK or stlink burning tools, and it is impossible for customers to buy such burning tools, which is unrealistic

- 2. On different products, the application of bootloader should be different. For example, some use SD card to update, the SD card also distinguishes spi/sdio, some need lcd/ serial port screen to display the update progress, some need USB flash disk, and finally, some need all

- 3. if each project is an independent bootloader project, the maintenance is quite cumbersome. Therefore, I use platformio to uniformly manage my bootloader project.

- 4. It has good portability. Even if you use keil/iar and other tools to directly put the relevant source files into it, it may need to be adjusted H, but it does not need to be modified. Relevant interfaces are also reduced and released as far as possible to reduce the need to modify logic.

## Support

This MCU is currently in batch use, and more support will be added later.

| MCU           | Manufacturer | Kernel      |
| ------------- | ------------ | ----------- |
| STM32F401RCTx | ST           | Cortex-M4F  |
| STM32F407VETx | ST           | Cortex-M4F  |
| STM32G0B0CETx | ST           | Cortex-CM0+ |

## Boards support

At present, only some boards I have used are supported. Of course, it is easy to add your own board settings. In this regard, you need to have a certain understanding of platformio, so that you can better operate and add new cards:

- 在.ini文件中加入这样的信息：

`[env:your_env_name]`

`extends = stm32_common` ;if you use stm32, you can use this  

`board = your_board_support`

`build_unflags = ${stm32_common.build_unflags}`

`build_flags = ${stm32_common.build_flags}`

​       `-DHSE_VALUE=8000000 ;Frequency of crystal oscillator on main board`

So you can quickly build your board

`default_envs = your_env_name`

In addition, you need to provide the pins file for your motherboard and name it pins_ xxx. h. There are also system startup files and three operation functions.

Then you can compile normally



## Development

I want my bootloader to be selectable and tailorable. So I will switch many functional things through macros, and they will be written in bl_ config. H in this file.





