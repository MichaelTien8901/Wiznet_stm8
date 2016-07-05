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