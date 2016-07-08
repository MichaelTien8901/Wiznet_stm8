# Wiznet_stm8
STM8 with WIZ550io 
This project add STM8 with WIZ550io for Ethernet connection. 

## Hardware 
STM8S Discovery board and WIZ550io.  An optional RS232 adapter is used for debugging purpose.

## Referred Project

The main program and settings of SPI is from [this project using STM32 to connect WIZ500](http://www.carminenoviello.com/2015/08/28/adding-ethernet-connectivity-stm32-nucleo/) 

## C compiler

Use the free version of COSMIC C compiler for STM8.  

## IO Library 
The IO libray used is from [https://github.com/Wiznet/ioLibrary_Driver](https://github.com/Wiznet/ioLibrary_Driver)

Some changes are necessary because of name conflicts.
## Tests
### Test 1 Basic Socket 
Use telnet to connect to defined IP and port.  In this example, connect to 192.168.1.192 port 5000.  The telnet client will receive a message and port closed.
### Test 2 TCP Server
### Test 3 TCP Client
### Test 4 Ping Client
  For porting to other MCU, Ping.c need define Endian correctly for the function htons.  STM8 is Big Endian, so nothing is needed to do.  For STM32, ATMEGA, you will need to define LITTLE_ENDIAN.  
  
## PINs Used
STM8S Discovery Board, switch power to 3.3V(JP1 to 1)

| Signal | STM8 |CPU Pin|WIZNET|DISCOVERY BOARD|
|--------|------|-------|------|---------------|
|SPI-SCK | PC5  | 30    | J1-5 |CN2-6          |
|SPI-MISO| PC7  | 34    | J1-4 |CN2-10         | 
|SPI_MOSI| PC6  | 33    | J1-3 |CN2-9          |
|SCSn    | PG1  | 36    | J1-6 |CN2-12         |
|WIZNET_RESET|PG0| 35   | J2-3 |CN2-11         |
|INTn(*not Used) | PC4  | 29    | J2-5 |CN2-5          |  Not used
|GND     |      |       | J1-1, J1-2, J2-6 |CN2-7      |
|3V3     |      |       | J1-7,J1-8,J2-1   |CN2-8,CN1-7|



STM8S207C8 Board used for private project. 

| Signal | STM8 |CPU Pin|WIZNET|IC-PIN|
|--------|------|-------|------|------|
|SPI-SCK | PC5  | 30    | J1-5 |  U5-5|
|SPI-MISO| PC7  | 34    | J1-4 | U5-13| 
|SPI_MOSI| PC6  | 33    | J1-3 | U4-5 |
|SCSn    | PE5  | 25    | J1-6 | U5-4*|
|WIZNET_RESET|PE7| 23   | J2-3 | U4-11 |
|INTn    | PC4  | 29    | J2-5 | U4-3|  
|GND     |      |       | J1-1, J1-2, J2-6 | U4-7, U5-7 |
|3V3     |      |       | J1-7,J1-8,J2-1|  |
|5V      |      |       |      | U4-14,U5-14|

* SSR connect to H.  U5-3 if SSR connect to L

