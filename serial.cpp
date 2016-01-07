#ifndef SERIAL_CPP
#define SERIAL_CPP
#include "serial.h"
#ifdef DEBUG_PRINT
//SerialDisplay::SerialDisplay(uint8_t baudrate) {
//	Serial(baudrate);
//}
//	LcdDisplay::LcdDisplay(uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7 )
//	{
//		config(lcd_Addr,En,Rw,Rs,d4,d5,d6,d7);
//	}
	SerialDisplay::SerialDisplay()
	{
	}
	void SerialDisplay::lcd_data( unsigned char Data) {
		Serial.write(Data);
	}
	void SerialDisplay::lcd_clear( void ) {
		Serial.println();
	}
	void SerialDisplay::lcd_line(unsigned char Line) {
		Serial.println();
	}
	//Clear single line of display
	void SerialDisplay::lcd_clear_line(unsigned char Line)
	{
		Serial.println();
	}
	//Write probe pin number to the LCD
	void SerialDisplay::lcd_testpin(unsigned char Probe)
	{
		//Since TP1 is 0 we simply add the value to '1'
		lcd_data('1' + Probe);                   //Send data
	}

	//Display a space
	void SerialDisplay::lcd_space(void)
	{
		lcd_data(' ');
	}

	//Display a string
	void SerialDisplay::lcd_string(char *Str)
	{
		while (*Str)                                //Loop until trailing 0 is reached
		{
			lcd_data(*Str);                           //Send character
			Str++;                                    //Next one
		}
	}

	//Display a fixed string stored in PROGMEM
	void SerialDisplay::lcd_fixed_string(const unsigned char *Str)
	{
		while (pgm_read_byte(Str) != 0x00) 
			lcd_data(pgm_read_byte(Str++));           //Send character
	}
	void SerialDisplay::print(const unsigned char *Str){
		Serial.print((const String&)Str);
	}
  void SerialDisplay::print(const char *Str){
   Serial.print(Str);
  }
	// Dummy functions
	void SerialDisplay::begin(uint8_t cols, uint8_t rows){}
	void SerialDisplay::setCursor(uint8_t col, uint8_t row)
	{
		Serial.println();
	}
	void SerialDisplay::backlight(void){}
	void SerialDisplay::createChar(uint8_t location, uint8_t charmap[]){}
	#ifdef __AVR__
	void SerialDisplay::createChar(uint8_t location, const char *charmap){}
	#endif // __AVR__
#if (ARDUINO <  100)
	void SerialDisplay::write(uint8_t value)
	{
		Serial.write(value);
	}
#else
	size_t SerialDisplay::write(uint8_t value)
	{
		Serial.write(value);
	}
#endif
	void SerialDisplay::home()
	{
		Serial.println();
	}
  void SerialDisplay::component(uint8_t c){
    _comp = c;
  }
#endif // DEBUG_PRINT
#endif // SERIAL_CPP

