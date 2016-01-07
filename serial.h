#ifndef SERIAL_H
#define SERIAL_H
#include "config.h"
#if (ARDUINO <  100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
#include <inttypes.h>

 #ifdef DEBUG_PRINT
 class SerialDisplay {
  
   public:
	SerialDisplay();
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
	void lcd_string(char *Str);
	//Display a fixed string stored in PROGMEM
	void lcd_fixed_string(const unsigned char *Str);
	void print(const unsigned char *Str);
  void print(const char *Str);
  // Dummy functions
	void begin(uint8_t cols, uint8_t rows);
	void setCursor(uint8_t col, uint8_t row);
	void backlight(void);
	void createChar(uint8_t location, uint8_t charmap[]);
	#ifdef __AVR__
	void createChar(uint8_t location, const char *charmap);
	#endif // __AVR__
#if (ARDUINO <  100)
	void write(uint8_t value);
#else
	size_t write(uint8_t value);
#endif
	void home();
  void component(uint8_t c);
  void pins(uint8_t a, uint8_t b, uint8_t c){}
private:
  uint8_t _comp;
};

 #endif // DEBUG_PRINT
#endif // SERIAL_H
