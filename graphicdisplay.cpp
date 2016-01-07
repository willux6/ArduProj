#ifndef GRAPHICDISPLAY_CPP
#define GRAPHICDISPLAY_CPP
#include "graphicdisplay.h"
#ifdef LCD_DOGM128
	GraphicDisplay::GraphicDisplay(){
	  //U8GLIB_DOGM128(13,11,10,9,255);
	}
	GraphicDisplay::GraphicDisplay(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t m) {
		 U8GLIB_DOGM128(13,11,10,9,255); // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
	}
	void GraphicDisplay::lcd_data( unsigned char Data) {
    _symbuffer[_row*21+_column] = Data;
    if( _column < 20) _column++;
	}
	void GraphicDisplay::lcd_clear( void ) {
    for( int i = 0; i < 168; i++ ) {
      _symbuffer[i] = ' ';
    }
    _column = 0;
    _row = 0;
	}
	void GraphicDisplay::lcd_line(unsigned char Line) {
		_column = 0;
    _row = Line;
	}
	//Clear single line of display
	void GraphicDisplay::lcd_clear_line(unsigned char Line)
	{
    _row = Line;
    _column = 0;
    for( int i = _row*21; i < _row*21+21; i++) {
      _symbuffer[i] = ' ';
    }
	}
	//Write probe pin number to the LCD
	void GraphicDisplay::lcd_testpin(unsigned char Probe)
	{
		//Since TP1 is 0 we simply add the value to '1'
		this->lcd_data('1' + Probe);                   //Send data
	}

	//Display a space
	void GraphicDisplay::lcd_space(void)
	{
		this->lcd_data(' ');
	}

	//Display a string
	void GraphicDisplay::lcd_string(char *String)
	{
		while (*String)                                //Loop until trailing 0 is reached
		{
			this->lcd_data(*String);                           //Send character
			String++;                                    //Next one
		}
	}

	//Display a fixed string stored in PROGMEM
	void GraphicDisplay::lcd_fixed_string(const unsigned char *String)
	{
		while (pgm_read_byte(String) != 0x00) 
			this->lcd_data(pgm_read_byte(String++));           //Send character
	}
	void GraphicDisplay::print(const char *Str)
	{
    for( int i = _row*21+_column; i < _row*21+21; i++ ) {
      _symbuffer[i] = (byte)*Str++;
      _column++;
    }
	}
	void GraphicDisplay::begin(uint8_t cols, uint8_t rows)
	{
		// flip screen, if required
		this->setRot180();
  
		// set SPI backup if required
		//setHardwareBackup(u8g_backup_avr_spi);

		// assign default color value
		if ( this->getMode() == U8G_MODE_R3G3B2 ) {
			this->setColorIndex(255);     // white
		}
		else if ( this->getMode() == U8G_MODE_GRAY2BIT ) {
			this->setColorIndex(3);         // max intensity
		}
		else if ( this->getMode() == U8G_MODE_BW ) {
			this->setColorIndex(1);         // pixel on
		}
		else if ( this->getMode() == U8G_MODE_HICOLOR ) {
			this->setHiColorByRGB(255,255,255);
		}
		//u8g_font_unifont 
		this->setFont(u8g_font_6x12);
    for( int i=0; i < 168; i++) {
     _symbuffer[i] = ' ';
    }
    _comp = COMPONENT_NONE;
    this->home();
	}
	void GraphicDisplay::setCursor(uint8_t col, uint8_t row)
	{
		_column = col;
    _row = row;
	}
	void GraphicDisplay::backlight(void)
	{
	}
	void GraphicDisplay::createChar(uint8_t location, uint8_t charmap[])
	{
	}
	#ifdef __AVR__
	void GraphicDisplay::createChar(uint8_t location, const unsigned char *charmap)
	{
	}
	#endif // __AVR__
	void GraphicDisplay::home(void)
	{
		_column = 0;
    _row = 0;
	}
  void GraphicDisplay::component(uint8_t c){
    _comp = c;
  }
  
  #define X_OFFSET 87
  #define Y_OFFSET 32
  #define Y_CENTRAL 48
  #define X_CENTRAL 106
  #define ICON_WIDTH 32
  #define ICON_HEIGHT 32
  
  void GraphicDisplay::update(void)
  {
    this->setColorIndex(1);
    this->firstPage();
    do {
      // symbol buffer
      char buf[22];
      for( int k=0; k <8; k++) {
        for( int i=0; i <21; i++) {
          buf[i] = _symbuffer[k*21+i];
        }
        buf[21] = 0;
        this->drawStr((u8g_uint_t)0,(u8g_uint_t)(k*8+8),(const char*)buf);
        //Serial.println(buf);
      }
      // Component icon
      if(_comp != COMPONENT_NEVER) {
        this->setColorIndex(0);
        this->drawBox(X_OFFSET,Y_OFFSET,ICON_WIDTH,ICON_HEIGHT);
      }
      this->setColorIndex(1);
      switch (_comp) {
        case COMPONENT_NONE:
        case COMPONENT_ERROR:
        case COMPONENT_NEVER:
        case COMPONENT_MENU:
          break;
        case COMPONENT_RESISTOR:
          this->drawFrame(X_OFFSET + 8,Y_OFFSET + 12, 16, 8);
          this->drawHLine(X_OFFSET, Y_CENTRAL, 8);
          this->drawHLine(X_OFFSET + 24, Y_CENTRAL, 8);
          break;
        case COMPONENT_CAPACITOR:
          this->drawBox(X_OFFSET + 10, Y_OFFSET + 10, 4, 16);
          this->drawBox(X_OFFSET + 16, Y_OFFSET + 10, 4, 16);
          this->drawHLine(X_OFFSET, Y_CENTRAL + 1, 10);
          this->drawHLine(X_OFFSET + 20, Y_CENTRAL + 1, 10);
          break;
        case COMPONENT_INDUCTOR:
          this->drawHLine(X_OFFSET + 3, Y_CENTRAL, 4);
          this->drawVLine(X_OFFSET + 6, Y_CENTRAL - 2, 3);
          this->drawHLine(X_OFFSET + 7, Y_CENTRAL - 3, 3);
          this->drawVLine(X_OFFSET + 10, Y_CENTRAL - 2, 5);
          this->drawHLine(X_OFFSET + 11, Y_CENTRAL + 3, 3);
          this->drawVLine(X_OFFSET + 14, Y_CENTRAL - 2, 5);
          this->drawHLine(X_OFFSET + 15, Y_CENTRAL - 3, 3);
          this->drawVLine(X_OFFSET + 18, Y_CENTRAL - 2, 5);
          this->drawHLine(X_OFFSET + 19, Y_CENTRAL + 3, 3);
          this->drawVLine(X_OFFSET + 22, Y_CENTRAL - 2, 5);
          this->drawHLine(X_OFFSET + 23, Y_CENTRAL - 3, 3);
          this->drawVLine(X_OFFSET + 26, Y_CENTRAL - 2, 3);
          this->drawHLine(X_OFFSET + 27, Y_CENTRAL, 3);
          break;
        case COMPONENT_DIODE:
          this->drawTriangle(X_OFFSET + 12, Y_CENTRAL - 8, X_OFFSET + 12, Y_CENTRAL + 8, X_OFFSET + 20, Y_CENTRAL);
          this->drawBox(X_OFFSET + 21, Y_CENTRAL - 8, 2, 17);
          this->drawHLine(X_OFFSET + 3,Y_CENTRAL, 26);
          break;
        case COMPONENT_ZENER:
          this->drawHLine( X_OFFSET + 3, Y_CENTRAL, 4);
          this->drawVLine( X_OFFSET + 7, Y_CENTRAL - 8, 17);
          this->drawHLine( X_OFFSET + 8, Y_CENTRAL - 8, 23);
          this->drawHLine( X_OFFSET + 8, Y_CENTRAL + 8, 23);
          this->drawTriangle(X_OFFSET + 15, Y_CENTRAL - 8, X_OFFSET + 24, Y_CENTRAL - 13, X_OFFSET + 24, Y_CENTRAL - 3);
          this->drawTriangle(X_OFFSET + 13, Y_CENTRAL + 3, X_OFFSET + 13, Y_CENTRAL + 13, X_OFFSET + 22, Y_CENTRAL + 8);
          this->drawBox(X_OFFSET + 13, Y_CENTRAL - 13, 2, 11);
          this->drawBox(X_OFFSET + 22, Y_CENTRAL + 3, 2, 11);
          break;
        case COMPONENT_BJTN:
          this->drawHLine(X_OFFSET + 20, Y_OFFSET + 6, 5);
          this->drawVLine(X_OFFSET + 24, Y_OFFSET + 7, 17);
          this->drawHLine(X_OFFSET + 20, Y_OFFSET + 24, 5);
          this->drawBox(X_OFFSET + 21, Y_OFFSET + 11, 7, 2);
          this->drawTriangle(X_OFFSET + 24, Y_OFFSET + 13, X_OFFSET + 20, Y_OFFSET + 17, X_OFFSET + 28, Y_OFFSET + 17);
        case COMPONENT_NPN:
          this->drawHLine(X_OFFSET + 2, Y_OFFSET + 15, 6);
          this->drawBox(X_OFFSET + 8, Y_OFFSET + 6, 2, 19);
          this->drawLine(X_OFFSET + 10, Y_OFFSET + 15, X_OFFSET + 19, Y_OFFSET + 6);
          this->drawVLine(X_OFFSET + 19, Y_OFFSET + 2, 4);
          this->drawLine(X_OFFSET + 10, Y_OFFSET + 15, X_OFFSET + 19, Y_OFFSET + 24);
          this->drawVLine(X_OFFSET + 19, Y_OFFSET + 25, 4);
          this->drawTriangle(X_OFFSET + 14, Y_OFFSET + 23, X_OFFSET + 18, Y_OFFSET + 19, X_OFFSET + 18, Y_OFFSET + 23);
          break;
        case COMPONENT_BJTP:
          this->drawHLine(X_OFFSET + 20, Y_OFFSET + 6, 5);
          this->drawVLine(X_OFFSET + 24, Y_OFFSET + 7, 17);
          this->drawHLine(X_OFFSET + 20, Y_OFFSET + 24, 5);
          this->drawTriangle(X_OFFSET + 20, Y_OFFSET + 11, X_OFFSET + 28, Y_OFFSET + 11, X_OFFSET + 24, Y_OFFSET + 15);
          this->drawBox(X_OFFSET + 21, Y_OFFSET + 16, 7, 2);          
        case COMPONENT_PNP:
          this->drawHLine(X_OFFSET + 2, Y_OFFSET + 15, 6);
          this->drawBox(X_OFFSET + 8, Y_OFFSET + 6, 2, 19);
          this->drawLine(X_OFFSET + 10, Y_OFFSET + 15, X_OFFSET + 19, Y_OFFSET + 6);
          this->drawLine(X_OFFSET + 10, Y_OFFSET + 15, X_OFFSET + 19, Y_OFFSET + 24);
          this->drawVLine(X_OFFSET + 19, Y_OFFSET + 2, 4);
          this->drawVLine(X_OFFSET + 19, Y_OFFSET + 25, 4);
          this->drawTriangle(X_OFFSET + 14, Y_OFFSET + 19, X_OFFSET + 14, Y_OFFSET + 23, X_OFFSET + 18, Y_OFFSET + 19);
          break;
        case COMPONENT_NFET:
          this->drawHLine(X_OFFSET + 3, Y_OFFSET + 22, 23);
          this->drawVLine(X_OFFSET + 25, Y_OFFSET + 23, 6);
          this->drawVLine(X_OFFSET + 12, Y_OFFSET + 5, 21);
          this->drawHLine(X_OFFSET + 13, Y_OFFSET + 8, 13);
          this->drawVLine(X_OFFSET + 25, Y_OFFSET + 2, 6);
          this->drawTriangle(X_OFFSET + 8, Y_OFFSET + 19, X_OFFSET + 8, Y_OFFSET + 25, X_OFFSET + 11, Y_OFFSET + 22);
          break;
        case COMPONENT_PFET:
          this->drawHLine(X_OFFSET + 3, Y_OFFSET + 22, 23);
          this->drawVLine(X_OFFSET + 25, Y_OFFSET + 23, 6);
          this->drawVLine(X_OFFSET + 12, Y_OFFSET + 5, 21);
          this->drawHLine(X_OFFSET + 13, Y_OFFSET + 8, 13);
          this->drawVLine(X_OFFSET + 25, Y_OFFSET + 2, 6);
          this->drawTriangle(X_OFFSET + 6, Y_OFFSET + 22, X_OFFSET + 9, Y_OFFSET + 19, X_OFFSET + 9, Y_OFFSET + 25);
          break;
        case COMPONENT_NIGBT:
          this->drawHLine(X_OFFSET + 3, Y_OFFSET + 15, 6);
          this->drawVLine(X_OFFSET + 9, Y_OFFSET + 7, 17);
          this->drawBox(X_OFFSET + 11, Y_OFFSET + 6, 2, 19);
          this->drawLine(X_OFFSET + 13, Y_OFFSET + 15, X_OFFSET + 22, Y_OFFSET + 6);
          this->drawVLine(X_OFFSET + 22, Y_OFFSET + 2, 4);
          this->drawLine(X_OFFSET + 13, Y_OFFSET + 15, X_OFFSET + 22, Y_OFFSET + 24);
          this->drawVLine(X_OFFSET + 22, Y_OFFSET + 25, 4);
          this->drawTriangle(X_OFFSET + 17, Y_OFFSET + 23, X_OFFSET + 21, Y_OFFSET + 19, X_OFFSET + 21, Y_OFFSET + 23);
          break;
        case COMPONENT_PIGBT:
          this->drawHLine(X_OFFSET + 3, Y_OFFSET + 15, 6);
          this->drawVLine(X_OFFSET + 9, Y_OFFSET + 7, 17);
          this->drawBox(X_OFFSET + 11, Y_OFFSET + 6, 2, 19);
          this->drawLine(X_OFFSET + 13, Y_OFFSET + 15, X_OFFSET + 22, Y_OFFSET + 6);
          this->drawVLine(X_OFFSET + 22, Y_OFFSET + 2, 4);
          this->drawLine(X_OFFSET + 13, Y_OFFSET + 15, X_OFFSET + 22, Y_OFFSET + 24);
          this->drawVLine(X_OFFSET + 22, Y_OFFSET + 25, 4);
          this->drawTriangle(X_OFFSET + 16, Y_OFFSET + 19, X_OFFSET + 16, Y_OFFSET + 23, X_OFFSET + 20, Y_OFFSET + 19);
          break;
        case COMPONENT_TRIAC:
          this->drawHLine(X_OFFSET, Y_OFFSET + 28, 6);
          this->drawLine(X_OFFSET + 6, Y_OFFSET + 27, X_OFFSET + 12, Y_OFFSET + 21);
          this->drawVLine(X_OFFSET + 14, Y_OFFSET + 21, 8);
          this->drawHLine(X_OFFSET + 14, Y_OFFSET + 29, 16);
          this->drawVLine(X_OFFSET + 14, Y_OFFSET + 2, 8);
          this->drawHLine(X_OFFSET + 15, Y_OFFSET + 2, 15);
          this->drawHLine(X_OFFSET + 20, Y_OFFSET + 10, 10);
          this->drawHLine(X_OFFSET + 2, Y_OFFSET + 20, 10);
          this->drawTriangle(X_OFFSET + 2, Y_OFFSET + 10, X_OFFSET + 19, Y_OFFSET + 10, X_OFFSET + 10, Y_OFFSET + 19);
          this->drawTriangle(X_OFFSET + 12, Y_OFFSET + 20, X_OFFSET + 30, Y_OFFSET + 20, X_OFFSET + 21, Y_OFFSET + 11);
          break;
        case COMPONENT_THYRISTOR:
          this->drawHLine(X_OFFSET + 2, Y_OFFSET + 26, 6);
          this->drawLine(X_OFFSET + 8, Y_OFFSET + 25, X_OFFSET + 13, Y_OFFSET + 20);
          this->drawVLine(X_OFFSET + 15, Y_OFFSET + 4, 25);
          this->drawHLine(X_OFFSET + 16, Y_OFFSET + 4, 14);
          this->drawHLine(X_OFFSET + 16, Y_OFFSET + 28, 14);
          this->drawBox(X_OFFSET + 9, Y_OFFSET + 18, 13, 2);
          this->drawTriangle(X_OFFSET + 9, Y_OFFSET + 11, X_OFFSET + 21, Y_OFFSET + 11, X_OFFSET + 15, Y_OFFSET + 17);
          break;
        case COMPONENT_NMOSD:
          this->drawVLine(X_OFFSET + 12, Y_OFFSET + 5, 22);
        case COMPONENT_NMOS:
          this->drawHLine(X_OFFSET + 3, Y_OFFSET + 22, 7);
          this->drawVLine(X_OFFSET + 9, Y_OFFSET + 8, 14);
          this->drawVLine(X_OFFSET + 12, Y_OFFSET + 11, 9);
          this->drawVLine(X_OFFSET + 12, Y_OFFSET + 5, 4);
          this->drawVLine(X_OFFSET + 12, Y_OFFSET + 22, 4);
          this->drawHLine(X_OFFSET + 13, Y_OFFSET + 8, 12);
          this->drawHLine(X_OFFSET + 13, Y_OFFSET + 22, 12);
          this->drawHLine(X_OFFSET + 13, Y_OFFSET + 15, 6);
          this->drawVLine(X_OFFSET + 19, Y_OFFSET + 15, 7);
          this->drawVLine(X_OFFSET + 25, Y_OFFSET + 2, 27);
          this->drawTriangle(X_OFFSET + 14, Y_OFFSET + 15, X_OFFSET + 17, Y_OFFSET + 12, X_OFFSET + 17, Y_OFFSET + 18);
          this->drawHLine(X_OFFSET + 22, Y_OFFSET + 13, 7);
          this->drawTriangle(X_OFFSET + 22, Y_OFFSET + 17, X_OFFSET + 29, Y_OFFSET + 17, X_OFFSET + 25, Y_OFFSET + 14);          
          break;
        case COMPONENT_PMOSD:
          this->drawVLine(X_OFFSET + 12, Y_OFFSET + 5, 22);
        case COMPONENT_PMOS:
          this->drawHLine(X_OFFSET + 3, Y_OFFSET + 22, 7);
          this->drawVLine(X_OFFSET + 9, Y_OFFSET + 8, 14);
          this->drawVLine(X_OFFSET + 12, Y_OFFSET + 11, 9);
          this->drawVLine(X_OFFSET + 12, Y_OFFSET + 5, 4);
          this->drawVLine(X_OFFSET + 12, Y_OFFSET + 22, 4);
          this->drawHLine(X_OFFSET + 13, Y_OFFSET + 8, 12);
          this->drawHLine(X_OFFSET + 13, Y_OFFSET + 22, 12);
          this->drawHLine(X_OFFSET + 13, Y_OFFSET + 15, 6);
          this->drawVLine(X_OFFSET + 19, Y_OFFSET + 15, 7);
          this->drawVLine(X_OFFSET + 25, Y_OFFSET + 2, 27);
          this->drawTriangle(X_OFFSET + 14, Y_OFFSET + 12, X_OFFSET + 14, Y_OFFSET + 18, X_OFFSET + 17, Y_OFFSET + 15);
          this->drawHLine(X_OFFSET + 22, Y_OFFSET + 17, 7);
          this->drawTriangle(X_OFFSET + 22, Y_OFFSET + 13, X_OFFSET + 29, Y_OFFSET + 13, X_OFFSET + 25, Y_OFFSET + 16);          
          break;
        default:
          break;
      }
    } while(this->nextPage());
  }
  void GraphicDisplay::pins(uint8_t a, uint8_t b, uint8_t c)
  {
    uint8_t r, co;
    co = _column;
    r = _row;

    this->setCursor( 13, 5);
    this->lcd_data('1'+a);
    if(c==' ')
      this->setCursor( 20, 5);
    else
      this->setCursor(20,4);
    this->lcd_data('1'+b);
    this->setCursor( 20, 7); 
    if( c!=' ')
      this->lcd_data('1'+c);
    else
      this->lcd_data(' ');
    this->setCursor( co, r);
  }
#endif // LCD_DOGM128
#endif // GRAPHICDISPLAY_CPP

