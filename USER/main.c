#include "stm32f10x.h" // Device heade
#include "delay.h"
#include "PWN.h"
int main()
{
	u8 i;
	delay_init();
	PWN_Init(1439,999);
	while(1)
	{
		for(i=25;i<126;i=i+25)
		{
			TIM_SetCompare4(TIM3,i);
			delay_ms(200);
		}
		for(i=125;i>25;i=i-25)
		{
			TIM_SetCompare4(TIM3,i);
			delay_ms(200);
		}
	}
}

