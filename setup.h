/*
 * setup.h
 */
#ifndef _SETUP_H
#define _SETUP_H

#define SPI_CS_PORT GPIOG
#define SPI_CS_PIN GPIO_PIN_1

#define SPI_RESET_PORT GPIOG
#define SPI_RESET_PIN GPIO_PIN_0

#define SPI_CK_PORT GPIOC
#define SPI_CK_PIN  GPIO_PIN_5

#define SPI_MOSI_PORT GPIOC
#define SPI_MOSI_PIN  GPIO_PIN_6

#define SPI_MISO_PORT GPIOC
#define SPI_MISO_PIN  GPIO_PIN_7

#define SET_SPI_CS  SPI_CS_PORT->ODR |=  (u8) SPI_CS_PIN
#define CLR_SPI_CS  SPI_CS_PORT->ODR &= ~(u8) SPI_CS_PIN

//#define SET_SPI_CK  SPI_CK_PORT->ODR |=  (u8) SPI_CK_PIN
//#define CLR_SPI_CK  SPI_CK_PORT->ODR &= ~(u8) SPI_CK_PIN

//#define SET_SPI_MOSI  SPI_MOSI_PORT->ODR |=  (u8) SPI_MOSI_PIN
//#define CLR_SPI_MOSI  SPI_MOSI_PORT->ODR &= ~ (u8) SPI_MOSI_PIN

//#define STU_SPI_MISO  (SPI_MISO_PORT->IDR & (u8) SPI_MISO_PIN)

#define SET_WIZNET_RST  (SPI_RESET_PORT->ODR |=  (u8) SPI_RESET_PIN)
#define CLR_WIZNET_RST  (SPI_RESET_PORT->ODR &= ~(u8) SPI_RESET_PIN)
void HardwareSetup(void);
#endif
