# Wiznet_stm8
Test Wiznet with stm8

## IO Library 
The IO libray used is from [https://github.com/Wiznet/ioLibrary_Driver](https://github.com/Wiznet/ioLibrary_Driver)

## PINs Used
STM8S Discovery Board, switch power to 3.3V(JP1 to 1)

| Signal | STM8 |CPU Pin|WIZNET|DISCOVERY BOARD|
|--------|------|-------|------|------|
|SPI-SCK | PC5  | 30    | J1-5 |CN2-6 |
|SPI-MISO| PC7  | 34    | J1-4 |CN2-10| 
|SPI_MOSI| PC6  | 33    | J1-3 |CN2-9 |
|SCSn    | PG1  | 36    | J1-6 |CN2-12|
|WIZNET_RESET|PG0| 35   | J2-3 |CN2-11|
|INTn    | PC4  | 29    | J2-5 |CN2-5|  
|GND     |      |       | J1-1, J1-2, J2-6 | CN2-7 |
|3V3     |      |       | J1-7,J1-8,J2-1|CN2-8,CN1-7|

STM8S207C8 Board

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

