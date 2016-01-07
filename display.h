#ifndef DISPLAY_H
#define DISPLAY_H
#include "config.h"

#if defined(LCD_PRINT)


  #include <Wire.h>
  #include <LCD.h>
  #include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library
  // LCD
  #define I2C_ADDR    0x38  // Define I2C Address for controller
  #define  LED_OFF  0
  #define  LED_ON  1

  #define BACKLIGHT_PIN  7
  #define En_pin  6
  #define Rw_pin  5
  #define Rs_pin  4
  #define D4_pin  0
  #define D5_pin  1
  #define D6_pin  2
  #define D7_pin  3
  //LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
  
  class LcdDisplay : public LiquidCrystal_I2C {
  
   public:
//	LcdDisplay(uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7 );
	LcdDisplay(uint8_t lcd_Addr);
	void lcd_data( unsigned char Data);
	void lcd_clear( void );
	void lcd_line(unsigned char Line);
	//Clear single line of display
	void lcd_clear_line(unsigned char Line);
	//Write probe pin number to the LCD
	void lcd_testpin(unsigned char Probe);
	//Display a space
	void lcd_space(void);
	//Display a string
	void lcd_string(char *String);
	//Display a fixed string stored in PROGMEM
	void lcd_fixed_string(const unsigned char *String);
  void component(uint8_t c);
  void pins(uint8_t a, uint8_t b, uint8_t c){}
  private:
  uint8_t _comp;  
};
  
 #endif // defined(LCD_PRINT)
#endif // DISPLAY_H
