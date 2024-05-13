#include "fan.h"

void Fan_Init(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, 0);
}
