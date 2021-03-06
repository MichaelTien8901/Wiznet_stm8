#include <stm8s.h>
#include <stddef.h>
#include <string.h>
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
   UART2_Init((u32)19200, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, UART2_PARITY_NO, UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TXRX_ENABLE);
   
	/* Enable the SPI*/
   SPI_Cmd(ENABLE);
		
   enableInterrupts();

}

#ifdef _RAISONANCE_
	#define PUTCHAR_PROTOTYPE int putchar (char c)
	#define GETCHAR_PROTOTYPE int getchar (void)
#elif defined (_COSMIC_)
	#define PUTCHAR_PROTOTYPE char putchar (char c)
	#define GETCHAR_PROTOTYPE char getchar (void)
#else   // _IAR_ 
	#define PUTCHAR_PROTOTYPE int putchar (int c)
	#define GETCHAR_PROTOTYPE int getchar (void)
#endif  // _RAISONANCE_

void SerialPutChar(char c)
{
    while ((UART2->SR & UART2_SR_TXE ) != UART2_SR_TXE );
    UART2_SendData8(c);
}
/**
  * @brief Retargets the C library printf function to the UART.
  * @param c Character to send
  * @retval char Character sent
  */
unsigned char putchar (unsigned char c)
{
  SerialPutChar(c);
  return (c);
}

/* ISO/IEC 9899 7.11.5.8 strtok. DEPRECATED.
 * Split string into tokens, and return one at a time while retaining state
 * internally.
 *
 * WARNING: Only one set of state is held and this means that the
 * WARNING: function is not thread-safe nor safe for multiple uses within
 * WARNING: one thread.
 *
 * NOTE: No library may call this function.
 */

char *strtok(char *s1, const char *delimit)
{
    static char *lastToken = NULL; /* UNSAFE SHARED STATE! */
    char *tmp;

    /* Skip leading delimiters if new string. */
    if ( s1 == NULL ) {
        s1 = lastToken;
        if (s1 == NULL)         /* End of story? */
            return NULL;
    } else {
        s1 += strspn(s1, delimit);
    }

    /* Find end of segment */
    tmp = strpbrk(s1, delimit);
    if (tmp) {
        /* Found another delimiter, split string and save state. */
        *tmp = '\0';
        lastToken = tmp + 1;
    } else {
        /* Last segment, remember that. */
        lastToken = NULL;
    }

    return s1;
}