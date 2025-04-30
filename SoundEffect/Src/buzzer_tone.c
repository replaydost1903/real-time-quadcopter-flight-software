#include "buzzer_tone.h"

extern TIM_HandleTypeDef htim2;

#define TIM_FREQ	168000000

uint32_t presForFrequency(int frequency)
{
	if(frequency==0) return 0;
	return (TIM_FREQ/(1000*frequency));
}

void quadcopter_opening_tone(void)
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

	// 🚀 Yükselen açılış efekti (enerjik yükseliş)
	__HAL_TIM_SET_PRESCALER(&htim2, presForFrequency(1000));
	HAL_Delay(300);
	__HAL_TIM_SET_PRESCALER(&htim2, presForFrequency(2000));
	HAL_Delay(100);
	__HAL_TIM_SET_PRESCALER(&htim2, presForFrequency(4000));
	HAL_Delay(300);
	__HAL_TIM_SET_PRESCALER(&htim2, presForFrequency(8000));
	HAL_Delay(100);
	__HAL_TIM_SET_PRESCALER(&htim2, presForFrequency(12000));
	HAL_Delay(300);

	// ✅ Hazır sesi (dikkat çeken sabit ton)
	__HAL_TIM_SET_PRESCALER(&htim2, presForFrequency(3000));
	HAL_Delay(250);

	// 🔻 Yumuşak iniş efekti (çıkışa geçiş hissi)
	__HAL_TIM_SET_PRESCALER(&htim2, presForFrequency(6000));
	HAL_Delay(100);
	__HAL_TIM_SET_PRESCALER(&htim2, presForFrequency(4000));
	HAL_Delay(100);
	__HAL_TIM_SET_PRESCALER(&htim2, presForFrequency(2000));
	HAL_Delay(120);
	__HAL_TIM_SET_PRESCALER(&htim2, presForFrequency(1000));
	HAL_Delay(150);

	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
}

