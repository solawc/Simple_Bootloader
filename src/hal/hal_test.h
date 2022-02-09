#ifndef __hal_test_h
#define __hal_test_h

#include "../main.h"

/* Motor pins */
 
#define X_STEP_PROT         GPIOC       
#define X_STEP_PIN          GPIO_PIN_12

#define Y_STEP_PROT         GPIOA
#define Y_STEP_PIN          GPIO_PIN_11

#define Z_STEP_PROT         GPIOC
#define Z_STEP_PIN          GPIO_PIN_7

#define E_STEP_PROT         GPIOB
#define E_STEP_PIN          GPIO_PIN_10

#define E1_STEP_PROT        GPIOC
#define E1_STEP_PIN         GPIO_PIN_4
    
#define X_DIR_PROT          GPIOB
#define X_DIR_PIN           GPIO_PIN_3

#define Y_DIR_PROT          GPIOA
#define Y_DIR_PIN           GPIO_PIN_15

#define Z_DIR_PROT          GPIOC
#define Z_DIR_PIN           GPIO_PIN_9

#define E_DIR_PROT          GPIOB
#define E_DIR_PIN           GPIO_PIN_1

#define E1_DIR_PROT         GPIOA
#define E1_DIR_PIN          GPIO_PIN_4

#define X_EN_PROT           GPIOD
#define X_EN_PIN            GPIO_PIN_2

#define Y_EN_PROT           GPIOA
#define Y_EN_PIN            GPIO_PIN_12

#define Z_EN_PROT           GPIOC
#define Z_EN_PIN            GPIO_PIN_8

#define E_EN_PROT           GPIOC
#define E_EN_PIN            GPIO_PIN_6

#define E1_EN_PROT          GPIOC
#define E1_EN_PIN           GPIO_PIN_5

/* Limit pins */
#define X_LIMIT_PORT        GPIOA
#define X_LIMIT_PIN         GPIO_PIN_13

#define Y_LIMIT_PORT        GPIOB
#define Y_LIMIT_PIN         GPIO_PIN_8

#define Z_LIMIT_PORT        GPIOC
#define Z_LIMIT_PIN         GPIO_PIN_13

#define Z_LIMIT_D_PORT      GPIOC
#define Z_LIMIT_D_PIN       GPIO_PIN_14

/* TH and TB */
#define TH0_PORT            GPIOA
#define TH0_PIN             GPIO_PIN_6

#define TB_PORT             GPIOA
#define TB_PIN              GPIO_PIN_5

#endif
