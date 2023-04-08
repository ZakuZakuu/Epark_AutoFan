#include "dht11.h"
#include "oled.h" 
/**
  * @brief  DHT11驱动函数
  * @param  void
  * @retval None
  */
void DHT11(void)
{
		DHT11_READ_DATA();
    HAL_Delay(50);  		             //  阈设延迟
}
 
/**
  * @brief  ????????????
  * @param  void
  * @retval None
  */
void DHT11_START(void)
{
    DHT11_GPIO_MODE_SET(0);                         //  ?????????
    
    DHT11_PIN_RESET;                                //  ??????
    
    HAL_Delay(20);                                  //  ???? 18 < ms > 30
    
    DHT11_GPIO_MODE_SET(1);                         //  ?????????,??DHT11??
}                                                   //  ?????????,GPIO -> 1
 
/**
  * @brief  ?????? 1bit
  * @param  void
  * @retval 0/1
  */
unsigned char DHT11_READ_BIT(void)
{
    while(!DHT11_READ_IO);                          //  ???????? 
    
    Tims_delay_us(40);                              //  ????????
    
    if(DHT11_READ_IO)                               //  ????????????? 1
    {
        while(DHT11_READ_IO);                       //  ????????
        return 1;
    }   
    else                                            //  ??????? 0
    {
        return 0;
    }
}
 
/**
  * @brief  ???????? 1byte / 8bit
  * @param  void
  * @retval temp
  */
unsigned char DHT11_READ_BYTE(void)
{
    uint8_t i,temp = 0;                             //  ??????
    
    for(i=0; i<8 ;i++)
    {
        temp <<= 1;                                 
        if(DHT11_READ_BIT())                        //  1byte -> 8bit
        {
            temp |= 1;                              //  0000 0001
        }
    }
    return temp;
}
 
/**
  * @brief  ?????????? 5byte / 40bit
  * @param  void
  * @retval 0/1/2
  */
unsigned char DHT11_READ_DATA(void)
{
    uint8_t i;
    uint8_t data[5] = {0};
    
    DHT11_START();                                  //  ????????
    
    if(DHT11_Check())                               //  ??DHT11??     
    {  
        while(!DHT11_READ_IO);                      //  ??DHT11????????
        while(DHT11_READ_IO);                       //  ??DHT11????????
        
        for(i=0; i<5; i++)
        {                        
            data[i] = DHT11_READ_BYTE();            //  ?? 5byte
        }
        
        if(data[0] + data[1] + data[2] + data[3] == data[4])
        {
						//温度显示
						OLED_ShowCN_STR(0,4,0,2);
						OLED_ShowStr(32,4,":",2);
            OLED_ShowNum(40,4,data[2],2,16);
						OLED_ShowCN_STR(59,4,4,1);
					
						//湿度显示
						OLED_ShowCN_STR(0,6,2,2);
						OLED_ShowStr(32,6,":",2);
						OLED_ShowNum(40,6,data[0],2,16);
						OLED_ShowStr(59,6,"HR",2);
            return 1;                               //  ??????
        }
        else
        {
            return 0;                               //  ??????
        }
    }
    else                                            //  ??DHT11???
    {
        return 2;
    }
}
 
/**
  * @brief  ????????????(??DHT11?????)
  * @param  void
  * @retval 0/1
  */
unsigned char DHT11_Check(void)
{
    Tims_delay_us(40);
    if(DHT11_READ_IO == 0)                          //  ???DHT11??
    {
        return 1;
    }
    else                                            //  ???DHT11???
    {
        return 0;
    }
}
 
/**
  * @brief  ??????
  * @param  mode: 0->out, 1->in
  * @retval None
  */
static void DHT11_GPIO_MODE_SET(uint8_t mode)
{
    if(mode)
    {
        /*  ??  */
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.Pin = GPIO_PIN_9;                   //  9???
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;             //  ????
        GPIO_InitStruct.Pull = GPIO_PULLUP;                 //  ????
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
    else 
    {
        /*  ??  */
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.Pin = GPIO_PIN_9;                //  9???
        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;      //  Push Pull ??????
        GPIO_InitStructure.Pull = GPIO_PULLUP;              //  ????
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;    //  ??
        HAL_GPIO_Init(GPIOB,&GPIO_InitStructure);
    }
}
 
/**
  * @brief  ?????us,Prescaler -> 72-1
  * @param  us: <= 65535
  * @retval None
  */
void Tims_delay_us(uint16_t nus)
{
	__HAL_TIM_SET_COUNTER(DLY_TIM_Handle, 0);
	__HAL_TIM_ENABLE(DLY_TIM_Handle);
	while (__HAL_TIM_GET_COUNTER(DLY_TIM_Handle) < nus)
	{
	}
	__HAL_TIM_DISABLE(DLY_TIM_Handle);
}
 
/**
  * @brief  ???? us , ??? 72M ?????
  * @param  us: <= 4294967295
  * @retval None
  */
void Coarse_delay_us(uint32_t us)
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
    while (delay--)
	{
		;
	}
}
