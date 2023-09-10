#include "main.h"

__IO uint32_t Counter = 0;
__IO uint8_t position = 0;

int main(void)
{
	SYS_Init();

	GPIOInit();

	Tim_Init();

	TIM_EnableIT_UPDATE(TIM2);
	TIM_EnableCounter(TIM2);
	while (1)
	{
/*
	  SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS1);
	  for(int i = 0; i < 5000000; i++);

	  SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
	  for(int i = 0; i < 5000000; i++);*/
	}
}

static void GPIOInit(){

		// Шаг 2. Скорость порта
	GPIOA->OSPEEDR &= ~(0b11 << (1 * 2)); // Сбрасываем значение регистра
	GPIOA->OSPEEDR |= 0b01 << (1 * 2);    // Самая высокая скорость
	// Шаг 3. Тип порта
	GPIOA->OTYPER &= ~(1U << 1);          // Стирая бит устанавливаем тип вывода push-pull
	// Шаг 4. Подтяжка
	GPIOA->PUPDR &= ~(0b11 << (1 * 2));   // Сбрасываем значение регистра
	GPIOA->PUPDR |= (0b00 << (1 * 2));    // Устанавливаем подтяжку к питанию
	// Шаг 5. Указываем что вывод запрограммирован на выход
	GPIOA->MODER &= ~(0b11 << (1 * 2));   // Сбрасываем порт
	GPIOA->MODER |= (0b01 << (1 * 2));    // Устанавливаем его на выход

}

static void Tim_Init(){
	/*Настройка таймера*/
	/*CLEAR_BIT(	TIM2 -> CR1, TIM_CR1_UDIS	);
	CLEAR_BIT(	TIM2 -> CR1, TIM_CR1_URS	);
	CLEAR_BIT(	TIM2 -> CR1, TIM_CR1_OPM	);
	SET_BIT(	TIM2 -> CR1, TIM_CR1_ARPE	);
	CLEAR_BIT(	TIM2 -> CR1, TIM_CR1_UIFREMAP);*/

	/*Разрешить прерывание*/
	NVIC_EnableIRQ(TIM2_IRQn);

	/*прескеллер таймера ||  частотапроцессора 64МГц*/
	//TIM6->PSC = 6400 - 1;
	WRITE_REG(TIM2->PSC, 6399);

	/*значение при котором происходит сброс(перезагрузка)*/
	//TIM6->ARR = 10000 - 1;
	WRITE_REG(TIM2->ARR, 9999);


}

void TIM2_IRQHandler(){
	if(READ_BIT(TIM2 -> SR, TIM_SR_UIF)){
		CLEAR_BIT(TIM2 -> SR, TIM_SR_UIF); //сброс флага прерывания

		switch(position){
			case 0:
				PIN1_ON();
				break;
			case 1:
				PIN1_OFF();
				break;
			default:
				position = 0;
		}
		position++;
	}

	Counter++;
}

static void SYS_Init(){
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;

	RCC->APB1LENR |= RCC_APB1LENR_TIM2EN;
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
