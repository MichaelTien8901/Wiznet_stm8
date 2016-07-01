/*
 * setup.h
 */
#ifndef _SETUP_H
#define _SETUP_H
//#include "config.h"

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


#define BEEP_PORT    GPIOD
#define BEEP_PIN     GPIO_PIN_4

#define BUTTON_PORT   GPIOC
#define BUTTON_PINS	   (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3)

//#define BUTTON2_PORT  GPIOE
//#define BUTTON2_PIN     (GPIO_PIN_3)

#define KEY_1 17
#define KEY_10 18
#define KEY_PAYOUT 19

//#define KEY_CONFIRM KEY_PAYOUT
//#define KEY_CANCEL 0x0E

//#define LOCK_PORT     GPIOD
//#define LOCK_PIN      GPIO_PIN_0

#define STATE_LED_PORT GPIOC
#define STATE_LED_PINS (GPIO_PIN_6|GPIO_PIN_7)
#define STATE_LED_ADD_PIN GPIO_PIN_6
#define STATE_LED_SUB_PIN GPIO_PIN_7

#define LED_GPIO_PORT  (GPIOD)
#define LED_GPIO_PINS  (GPIO_PIN_3 | GPIO_PIN_2 )
#define LED_DATA_PIN	 (GPIO_PIN_3)
#define LED_CLK_PIN		 (GPIO_PIN_2)

#define KEYCODE_1 16 
#define KEYCODE_2 12 
#define KEYCODE_3 8
#define KEYCODE_4 15 
#define KEYCODE_5 11 
#define KEYCODE_6 7
#define KEYCODE_7 14 
#define KEYCODE_8 10 
#define KEYCODE_9 6
#define KEYCODE_0 9 
#define KEYCODE_00 13
#define KEYCODE_ADD 3
#define KEYCODE_SUB 2
#define KEYCODE_ACC 4
#define KEYCODE_CONFIRM 1
#define KEYCODE_DOT 5

void initLED(int8_t demo_flag);
void initKey(void);
void TIM4_Config(void);
void Beep(void);
void LongBeep(void);
void HardwareSetup(void);
int8_t isButtonPressed(void);
int isButtonLongPressed(void);
void clearButtons(void);
void Delay(__IO uint16_t nTime);
void DelayNoWait(__IO uint16_t nTime );
int8_t DelayTimeUp(void);

void Show_Number32(uint32_t num );
//void Select_HP(int8_t select);
void Show_Empty(void);
void Show_Blank(void);
void Show_Error( uint8_t err );
void Show_Unloc1(void);
void Show_Unloc2(void);
void LongBeeps( uint8_t count );

void Shift_LED(void);
void hopper_process_active(void);
//void hopper_process_poweroff(void);
void Show_Setting_OK(void);
void Show_Pass_OK(void);
void Flash_Programming( uint16_t addr, uint16_t len, uint8_t *data );
void Flash_Programming_Zero( uint16_t addr, uint16_t len );
void Update_Setup_Code( uint32_t *pnewValue );
void Update_Pass_Code( uint32_t *pnewValue );
void UpdateDisplayOrientation(void);
void enable_setup_id(void);
void save_network_id(void);

typedef struct {
	uint8_t boot_flag; // 0: use passcode, 1: need boot card
//   uint8_t reader_orientation;
   uint8_t usage; // 0: add + sub value, 1: add value only, 2: sub value only
   uint8_t print; // 0: only shift, 1: add + shift(default), 2: sub + shift, 3: all, 4: none 
	uint16_t signature; // setting signature
   uint16_t crc16;
} SC_SETTINGS;

typedef union {
   struct {
   u8 limit: 2; // 0: no limit condition, 1: need boot card unlock, 2: need admin card unlock, 3: unlock pending
   u8 card: 1;
   } BITS;
   u8 BYTE;
} LIMIT_STATE;
extern LIMIT_STATE limit_state;
extern EEPROM SC_SETTINGS my_settings;
#define UNLOCK_DATA()  disableInterrupts(); FLASH->DUKR = 0xAE; FLASH->DUKR = 0x56; 
#define UNLOCK_PROG()  FLASH->PUKR = 0x56; FLASH->PUKR = 0xAE; 
#define LOCK_PROG()   FLASH->IAPSR &= (uint8_t)FLASH_MEMTYPE_PROG;
#define LOCK_DATA()   FLASH->IAPSR &= (uint8_t)FLASH_MEMTYPE_DATA; enableInterrupts();
#define UNLOCK_OPTION()  FLASH->CR2 |= FLASH_CR2_OPT; \
          FLASH->NCR2 &= (uint8_t)(~FLASH_NCR2_NOPT);
#define LOCK_OPTION() FLASH->CR2 &= (uint8_t)(~FLASH_CR2_OPT); \
    FLASH->NCR2 |= FLASH_NCR2_NOPT;
    
#define FLASH_WAIT_STATE_OPTION 0x480D
//#define SELF_TEST
#ifdef SELF_TEST
   #define Uses_SECURITY_SELF_TEST
   
#endif
void init_network(void);

#define Uses_LOCK_CARD

typedef struct {
   u8 bLock;
   u8 card_id[7];
} LOCK_CARD;
extern LOCK_CARD sc_lock_card;

extern void lock_card(void);
extern void lock_card2(void); 
extern void unlock_card(void);
s8 is_card_lock(void);

#ifdef Uses_CARDLESS_PAYOUT
void initCardlessPayout(void);
void update_cardless_payout(u8 id[], u32);
void set_update_cardless_payout(u8 id[], u32);
void reset_cardless_payout(void);
int8_t is_cardless_payout_pending(void);
void recover_cardless_payout_CardID(void);
#endif
//typedef struct {
//   u8 pending;
//   u8 value;
//} PENDING_HP_SW;
//extern PENDING_HP_SW pending_hp_sw;
//void monitor_pending_hp_sw(void);

//#if defined(Uses_CARD_TRANSACTION_NO)
void update_trans_pending( s32 delta, u32 amount, u32 card_trans_no, u8 trans_serial);
//void update_trans_pending2( s32 delta, u32 amount, u32 card_trans_no);
//#else
//void update_trans_pending( s32 delta, u32 amount);
//void update_trans_pending2( s32 delta, u32 amount);
//#endif
void reset_trans_pending(void);

#if defined( Uses_SYNC_TRANSACTION )
void clone_last_trans(void);
s8 is_last_transaction(void);
#endif

s16 is_trans_pending_update(void);

typedef struct {
  u8 fram_flag; 
  u16 signature;
} SC_ErrorSettings;   
extern EEPROM SC_ErrorSettings my_error_settings;

#ifdef Uses_ERROR_COUNTER
typedef struct 
{
   u16 noise;
   u16 crc;
   u16 parsing;
} ERROR_COUNT;
extern ERROR_COUNT error_counter;
#endif

extern EEPROM u16 my_clock_error;
s8 is_mark_clock_error(void);
void mark_clock_error(void);
typedef struct {
   u16 year;
   u8 month, day, hour, min;
} STIME;   
#if 0
typedef struct { 
   u16 signature;
   u32 addVal, subVal;
   STIME prev_shift, shift;
   u8 location[16];
   u8 verification[4];
   s8 flag;
   s8 sum;
} TShiftReport;
extern TShiftReport mShiftReport;
#endif
typedef struct {
   u16 signature;
   STIME print_time;
   u8 location[16+1];
   u8 cardNo[7+1];
   u8 mode; // 1: shift, 2: add value, 3: sub value
   u8 prep_mode; // 0: disable, 1: shift, 2: add value, 3: sub value
   u8 flag;
   union {
      struct {
         STIME prev_shift;
         u32 addVal, subVal;
         u8 verification[4]; 
         u32 serial;        
      } shift;
      struct {
         u32 delta, amount;
         u32 promote_delta, promote_amount;
      } addValue;
      struct {
         u32 delta, amount;
         u32 promote_delta, promote_amount;
      } subValue;
   } data;
   s8 sum; // need to define for save to FRAM
} TPrintData;
extern TPrintData mPrintData;
typedef struct {
   u16 signature;
   u32 serial;
   STIME print_time;
   s8 sum;
} TPrintSerial;
extern TPrintSerial mPrintSerial; 
void reset_io_account(void);
void FmInitIOAccount(void);
void io_account_add_value(u32 value);
void io_account_sub_value(u32 value);
u32 io_account_in(void);
u32 io_account_out(void);
void FmInitShiftReport(void);
void FmInitPrintData(void);
void FmInitPrintSerial(void);
void store_print_data(void);
void store_print_serial(void);
void update_console_password( u32* pnewValue );

#endif
