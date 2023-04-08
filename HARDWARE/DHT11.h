#ifndef __DHT11_H__
#define __DHT11_H__
 
/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "stdio.h"
#include "tim.h"
#include "stm32f1xx.h"
 
/* Private define ------------------------------------------------------------*/
#define DHT11_PIN_SET   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET)                                            //  ??GPIO??
#define DHT11_PIN_RESET HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET)                                          //  ??GPIO??
#define DHT11_READ_IO   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)                                                          //  DHT11 GPIO??
 
#define DLY_TIM_Handle (&htim2)                                                                                     //  ?????
 
#define USER_DHT11_DEBUG                                                                                            //  ??????
 
#ifdef USER_DHT11_DEBUG 
    #define user_dht11_printf(format,...) do{printf(format "\r\n", ##__VA_ARGS__);}while(0)
    #define user_dht11_info(format,...)   do{printf("[    DHT11] info  : "format "\r\n", ##__VA_ARGS__);}while(0)
    #define user_dht11_debug(format,...)  do{printf("[    DHT11] debug : "format "\r\n", ##__VA_ARGS__);}while(0)
    #define user_dht11_error(format,...)  do{printf("[    DHT11] error : "format "\r\n", ##__VA_ARGS__);}while(0)
    /**
      * do-while ??????????
      * web  :   https://www.jianshu.com/p/99efda8dfec9
      */ 
#else   
    #define user_main_printf(format,...)
    #define user_main_info(format,...)
    #define user_main_debug(format,...)
    #define user_main_error(format,...)
    /**
      * ??,???
      */
#endif
 
/* Private variables ---------------------------------------------------------*/
 
/* Private typedef -----------------------------------------------------------*/
 
/* Private function prototypes -----------------------------------------------*/
void DHT11(void);
void DHT11_START(void);
unsigned char DHT11_READ_BIT(void);
unsigned char DHT11_READ_BYTE(void);
unsigned char DHT11_READ_DATA(void);
unsigned char DHT11_Check(void);
static void DHT11_GPIO_MODE_SET(uint8_t mode);
void Tims_delay_us(uint16_t nus);
void delay_us(uint16_t nus);
    
#endif
