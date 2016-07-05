/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  
  * @version
  * @date    1-July-2016
  * @brief   Main program body
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include <stm8s.h>
#include <string.h>
#include <stdio.h>
#include "setup.h"
#include "wizchip_conf.h"
#include "socket.h"
//#define TEST1
#define TEST2
//#define TEST3
//#define TEST4
#if defined(TEST1)
void socket_test(int16_t port);
#elif defined(TEST2)
void loop_tcp_server_test(int16_t port);
#elif defined(TEST3)
void loop_tcp_client_test(int16_t port);
#elif defined(TEST4)
void http_server_test(int16_t port);
#endif
/* Private defines -----------------------------------------------------------*/
#define SEPARATOR            "=============================================\r\n"
#define WELCOME_MSG  		 "Welcome to STM8 Ethernet configuration\r\n"
#define NETWORK_MSG  		 "Network configuration:\r\n"
#define IP_MSG 		 		 "  IP ADDRESS:  %d.%d.%d.%d\r\n"
#define NETMASK_MSG	       "  NETMASK:     %d.%d.%d.%d\r\n"
#define GW_MSG 		 		 "  GATEWAY:     %d.%d.%d.%d\r\n"
#define MAC_MSG		 		 "  MAC ADDRESS: %x:%x:%x:%x:%x:%x\r\n"

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void wiznet_sel(void)
{
   CLR_SPI_CS;
}
void wiznet_desel(void)
{
   SET_SPI_CS;
}
uint8_t wiznet_transfer(uint8_t data )
{
   while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
   SPI_SendData(data);
   while (SPI_GetFlagStatus(SPI_FLAG_RXNE)== RESET);
   return SPI_ReceiveData();
}
void wiznet_send_data(uint8_t data )
{
   wiznet_transfer(data);
}
uint8_t wiznet_receive_data(void)
{
   return wiznet_transfer(0);
}
/*******************************************************************************
* Function Name  : SerialPutChar
* Description    : Print a character on the HyperTerminal
* Input          : - c: The character to be printed
* Output         : None
* Return         : None
*******************************************************************************/
void SerialPutChar(char c)
{
    while ((UART2->SR & UART2_SR_TXE ) != UART2_SR_TXE );
    UART2_SendData8(c);
}

/*******************************************************************************
* Function Name  : SerialPutString
* Description    : Print a string on the HyperTerminal
* Input          : - s: The string to be printed
* Output         : None
* Return         : None
*******************************************************************************/
void SerialPutString(char *s)
{
	while (*s)
	{
		SerialPutChar(*s++);
	}
}

extern void SerialPutString(char *s);
#define PRINT_STR SerialPutString

void print_netinfo(wiz_NetInfo netInfo) 
{
   char msg[60];
   PRINT_STR (NETWORK_MSG); 
   sprintf(msg, 
      MAC_MSG, 
      (uint16_t) netInfo.mac[0], 
      (uint16_t) netInfo.mac[1], 
      (uint16_t) netInfo.mac[2], 
      (uint16_t) netInfo.mac[3], 
      (uint16_t) netInfo.mac[4], 
      (uint16_t) netInfo.mac[5]);
   PRINT_STR( msg ); 
   sprintf(msg, 
      IP_MSG, 
      (uint16_t) netInfo.ip[0], 
      (uint16_t) netInfo.ip[1], 
      (uint16_t) netInfo.ip[2], 
      (uint16_t) netInfo.ip[3]);
   PRINT_STR( msg ); 
   sprintf(msg, 
      NETMASK_MSG, 
      (uint16_t) netInfo.sn[0], 
      (uint16_t) netInfo.sn[1], 
      (uint16_t) netInfo.sn[2], 
      (uint16_t) netInfo.sn[3]);
   PRINT_STR( msg ); 
   sprintf(msg, 
      GW_MSG, 
      (uint16_t) netInfo.gw[0], 
      (uint16_t) netInfo.gw[1], 
      (uint16_t) netInfo.gw[2], 
      (uint16_t) netInfo.gw[3]);
   PRINT_STR( msg ); 
}


void HAL_Delay(uint16_t count)
{
   uint16_t i, j, k;
   for ( i = 0; i < count; i ++ ) {
      for ( j = 0; j < 6500; j ++ ) {
         for ( k = 0; k < 10; k ++ ) 
            nop();
      }
   }
}
void reset_wiznet(void)
{
   CLR_WIZNET_RST;
   HAL_Delay(2);
   SET_WIZNET_RST;
   HAL_Delay(10); // need some time after reset 
}
void main(void)
{
   wiz_NetInfo netInfo = {{0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef},	// Mac address
                           {192, 168, 1, 192},					// IP address
                           {255, 255, 255, 0},					// Subnet mask
                           {192, 168, 1, 254}};					// Gateway address
// COSMIC C doesn't support this following format                           
//   wiz_NetInfo netInfo = { .mac 	= {0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef},	// Mac address
//                          .ip 	= {192, 168, 2, 192},					// IP address
//                          .sn 	= {255, 255, 255, 0},					// Subnet mask
//                          .gw 	= {192, 168, 2, 1}};					// Gateway address
   uint8_t bufSize[] = {2, 2, 2, 2};
   int port_no = 5000;
   HardwareSetup();
   // reset WIZNET chip
   reset_wiznet();
   
   // setup WIZ550io
   reg_wizchip_cs_cbfunc( wiznet_sel, wiznet_desel );
   reg_wizchip_spi_cbfunc( wiznet_receive_data, wiznet_send_data );
   
   wizchip_init(bufSize, bufSize);
   wizchip_setnetinfo(&netInfo);
   wizchip_getnetinfo(&netInfo);   
   print_netinfo(netInfo);
#if defined(TEST1)
   socket_test(port_no);
#elif defined(TEST2)
   loop_tcp_server_test(port_no);
#elif defined(TEST3)
   loop_tcp_client_test(port_no);
#elif defined(TEST4)
   http_server_test(port_no);
#endif   
}
    
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
