
#include <stm32f4xx.h>
	 
#include "stm32f4xx_conf.h"
#include "stm32f4xx_spi.h"

/* SPI_1 pins definition for test */
#define RCC_SPI2_CLK                RCC_APB1Periph_SPI2
#define SPI2_GPIO_PORT              GPIOB
#define RCC_SPI2_PORT               RCC_AHB1Periph_GPIOB
#define SPI2_SCK                    GPIO_Pin_13
#define SPI2_MISO                   GPIO_Pin_14
#define SPI2_MOSI                   GPIO_Pin_15
#define SPI2_SCK_SOURCE             GPIO_PinSource13
#define SPI2_MISO_SOURCE            GPIO_PinSource14
#define SPI2_MOSI_SOURCE            GPIO_PinSource15

/* ARMJISHU_TouchScreen_ADS7843 */

#define RCC_ADS7843_CS                         RCC_AHB1Periph_GPIOB
#define GPIO_ADS7843_CS_PORT                   GPIOB 
#define GPIO_ADS7843_CS                        GPIO_Pin_12  

//NRF24L01 SPI�ӿ�CS�ź�
//#define NRF24L01_CSN      		GPIO_Pin_14
//#define GPIO_NRF24L01_CSN  		GPIOB
//#define RCC_NRF24L01_CSN  		RCC_AHB1Periph_GPIOB 



#define RCC_ADS7843_INT                        RCC_AHB1Periph_GPIOA
#define GPIO_ADS7843_INT_PORT                  GPIOA  
#define GPIO_ADS7843_INT                       GPIO_Pin_8  
//#define GPIO_ADS7843_EXTI_LINE                 EXTI_Line7
//#define GPIO_ADS7843_EXTI_PORT_SOURCE          EXTI_PortSourceGPIOG
//#define GPIO_ADS7843_EXTI_PIN_SOURCE           EXTI_PinSource7
//#define GPIO_ADS7843_EXTI_IRQn                 EXTI9_5_IRQn 

#define GPIO_ADS7843_INT_VALID   (!GPIO_ReadInputDataBit(GPIO_ADS7843_INT_PORT, GPIO_ADS7843_INT))

/* Select ADS7843: ChipSelect pin low  */
#define ADS7843_CS_LOW()     GPIO_ResetBits(GPIO_ADS7843_CS_PORT, GPIO_ADS7843_CS)
/* Deselect ADS7843: ChipSelect pin high */
#define ADS7843_CS_HIGH()    GPIO_SetBits(GPIO_ADS7843_CS_PORT, GPIO_ADS7843_CS)

void ADS7843_Init(void);
void ARMJISHU_TouchScreen_ADS7843(void);