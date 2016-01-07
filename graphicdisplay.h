#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H
#include "config.h"
#if (ARDUINO <  100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
#include <inttypes.h>

#if defined(LCD_DOGM128)

  #include <U8glib.h> 
  
  class GraphicDisplay : protected U8GLIB_DOGM128 {
  
   public:
	GraphicDisplay();
	GraphicDisplay(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t m);
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
	//void print(const unsigned char *Str);
	void print(const char *Str);
	// Dummy functions
	void begin(uint8_t cols, uint8_t rows);
	void setCursor(uint8_t col, uint8_t row);
	void backlight(void);
	void createChar(uint8_t location, uint8_t charmap[]);
	#ifdef __AVR__
	void createChar(uint8_t location, const unsigned char *charmap);
	#endif // __AVR__
//#if (ARDUINO <  100)
//	void write(uint8_t value);
//#else
//	size_t write(uint8_t value);
//#endif
	void home(void);
  void component(uint8_t c);
  void pins(uint8_t a, uint8_t b, uint8_t c);
  void update(void);
 private:
  u8g_uint_t _column;
  u8g_uint_t _row;
  byte _symbuffer[168];
  u8g_uint_t _comp;
};
  
 #endif // defined(LCD_DOGM128)
#endif // GRAPHICDISPLAY_H
