#include <string.h>
#include <stdio.h>
#include "setup.h"
#include "wizchip_conf.h"
#include "socket.h"
#include "loopback.h"
void HAL_Delay(uint16_t count);

/** STM8S Discovery CPU RAM size is only 2K, we need to 
  * redefine DATA_BUF_SIZE in project settings
  * Project Settings->C Compiler->Predefined Symbox, add 
  * DATA_BUF_SIZE=512
  */
void SerialPutString(char *s);
#define PRINT_STR SerialPutString
  
void loop_tcp_server_test(int16_t port)
{
   uint8_t buffer[DATA_BUF_SIZE];
   PRINT_STR( "TCP server test\r\n" );
   while(1) 
      loopback_tcps(0, buffer, port);
}
void loop_tcp_client_test(uint8_t *destip, int16_t destport)
{
   uint8_t buffer[DATA_BUF_SIZE];
   
   PRINT_STR( "TCP Client Test\r\n" );
   while(1) {
      loopback_tcpc(0, buffer, destip, destport);
   }
}
void ping_client_test(uint8_t *destip)
{
   extern uint8_t ping_auto(uint8_t s, uint8_t *addr);
   PRINT_STR( "Ping Client Test\r\n" );
   while(1)
   ping_auto( 0, destip );
}
