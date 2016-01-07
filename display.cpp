#ifndef DISPLAY_CPP
#define DISPLAY_CPP
#include "display.h"
#ifdef LCD_PRINT
LcdDisplay::LcdDisplay(uint8_t lcd_Addr) {
	//config(lcd_Addr,6,5,4,0,1,2,3);
}
//	LcdDisplay::LcdDisplay(uint8_t lcd_Addr, uint8_t En, uint8_t Rw, uint8_t Rs, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7 )
//	{
//		config(lcd_Addr,En,Rw,Rs,d4,d5,d6,d7);
//	}
	void LcdDisplay::lcd_data( unsigned char Data) {
		write(Data);
	}
	void LcdDisplay::lcd_clear( void ) {
		clear();
		delay(2);
	}
	void LcdDisplay::lcd_line(unsigned char Line) {
		setCursor(0,Line);
	}
	//Clear single line of display
	void LcdDisplay::lcd_clear_line(unsigned char Line)
	{
		unsigned char Pos;
		lcd_line(Line);                         //Go to beginning of line
		for (Pos = 0; Pos < 20; Pos++)               //For 20 times
		{
			lcd_data(' ');                      //Send space
		}
		lcd_line(Line);                         //Go back to beginning of line
	}
	//Write probe pin number to the LCD
	void LcdDisplay::lcd_testpin(unsigned char Probe)
	{
		//Since TP1 is 0 we simply add the value to '1'
		lcd_data('1' + Probe);                   //Send data
	}

	//Display a space
	void LcdDisplay::lcd_space(void)
	{
		lcd_data(' ');
	}

	//Display a string
	void LcdDisplay::lcd_string(char *String)
	{
		while (*String)                                //Loop until trailing 0 is reached
		{
			lcd_data(*String);                           //Send character
			String++;                                    //Next one
		}
	}

	//Display a fixed string stored in PROGMEM
	void LcdDisplay::lcd_fixed_string(const unsigned char *String)
	{
		while (pgm_read_byte(String) != 0x00) 
			lcd_data(pgm_read_byte(String++));           //Send character
	}
  void LcdDisplay::component(uint8_t c){
    _comp = c;
  }
 #endif // LCD_PRINT
#endif // DISPLAY_CPP

