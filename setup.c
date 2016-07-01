#include <stm8s.h>
#include "setup.h"
//#include "version.h"


extern ErrorStatus CLK_ClockSwitchConfig2(CLK_Source_TypeDef CLK_NewClock );
void HardwareSetup(void)
{
   /* Initialization of the clock */
   /* Clock divider to HSI/1 */
   CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
   /* set to external clock */
   /************************************************************
    * need to define (1) HSE_Value (2) HSE_VALUE=(u32)16000000 
    * in project definition
    ************************************************************
    */
   CLK_HSECmd(ENABLE);
   if ( CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, DISABLE) == SUCCESS ) 
      CLK_HSICmd(DISABLE);
   else {
      CLK->SWCR &= ~CLK_SWCR_SWBSY;
   }
	/* Set GPIO for LED LD1 (PD0)  */
   GPIO_Init(GPIOD, 0x01 , GPIO_MODE_OUT_PP_LOW_FAST);  
   SPI_DeInit();      
   /* Initialize SPI in master mode  */
   SPI_Init(SPI_FIRSTBIT_MSB, 
         SPI_BAUDRATEPRESCALER_2, 
         SPI_MODE_MASTER, 
         SPI_CLOCKPOLARITY_LOW,
         SPI_CLOCKPHASE_1EDGE, 
         SPI_DATADIRECTION_2LINES_FULLDUPLEX, 
         SPI_NSS_SOFT,(uint8_t)0x07);
   // SPI_GPIO configuration
   GPIO_Init( SPI_CS_PORT,    SPI_CS_PIN,    GPIO_MODE_OUT_PP_HIGH_FAST );
   GPIO_Init( SPI_RESET_PORT, SPI_RESET_PIN, GPIO_MODE_OUT_PP_HIGH_FAST );
   
//   GPIO_Init( SPI_CK_PORT,    SPI_CK_PIN,    GPIO_MODE_OUT_PP_HIGH_FAST );
//   GPIO_Init( SPI_MOSI_PORT,  SPI_MOSI_PIN,  GPIO_MODE_OUT_PP_HIGH_FAST );
//   GPIO_Init( SPI_MISO_PORT,  SPI_MISO_PIN,  GPIO_MODE_IN_PU_NO_IT );
   // debug COM port
   UART2_DeInit();
   UART2_Init((u32)9600, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, UART2_PARITY_NO, UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TXRX_ENABLE);
   
	/* Enable the SPI*/
   SPI_Cmd(ENABLE);
		
   enableInterrupts();

}
