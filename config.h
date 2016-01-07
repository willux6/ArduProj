#ifndef CONFIG_H
#define CONFIG_H
                                                 //ARDUTESTER FEATURES
//#define DEBUG_                                   // just debug printing to serial
#define WDT_enabled                              // Enable watchdog 25.12.2015
#define BUTTON_INST                              // Button Installed

// Choose which setup, only one is allowed
//#define LCD_PRINT                              //Print on LCD with I2C interface
#define LCD_DOGM128                              //use LCD DOGM128
//#define DEBUG_PRINT                            //Print on Serial Port

#define DET_COMP_ANALYSIS                        //Detailed Component Analysis (Soon)
#define TIMEOUT_BL            600                //LCD Backlight Timeout
#define LONG_PRESS            50                 //Button Long Press (was 26 before 2.01.2016)
#define NUM_TESTS             6                  //Test 7 prints Graphic icons (6 or 7)
#define PWM_TOOL_SUPPORT
#ifdef LCD_PRINT
 #define USER_WAIT            3000               //Nexpage Timeout
#else
 #define USER_WAIT            1000               //Nexpage Timeout
#endif
//Test probes - Must be an ADC port :-)
#define ADC_PORT              PORTC              //ADC port data register 
#define ADC_DDR               DDRC               //ADC port data direction register 
#define ADC_PIN               PINC               //Port input pins register 
#define TP1                   0                  //Test pin 1 (=0) 
#define TP2                   1                  //Test pin 2 (=1) 
#define TP3                   2                  //Test pin 3 (=2) 
/*
   Probe resistors: 
   The resistors must be connected to the lower 6 pins of the port in
   following sequence:
    - pin 0: Rl1 680R (test pin 1)
    - pin 1: Rh1 470k (test pin 1)
    - pin 2: Rl2 680R (test pin 2)
    - pin 3: Rh2 470k (test pin 2)
    - pin 4: Rl3 680R (test pin 3)
    - pin 5: Rh3 470k (test pin 3)
    Except when connected to PortD we shift 2 bits higher
*/
#define R_PORT                PORTD              //Port data register 
#define R_DDR                 DDRD               //Port data direction register
#define R_SHIFT               2                  //Additional Shift positions for PORTB it should be 0, for PORT D it should be 2

//Push button
#define TEST_BUTTON           A3                 //Test/start push button (low active)

//Button Delay
#define CYCLE_DELAY           3000
//************************** ARDUTESTER PARAMETERS ***********

//Maximum number of measurements without any components found.
#define CYCLE_MAX             5
//ADC voltage reference based on Vcc (in mV). 
#define UREF_VCC              5001
/*
  Offset for the internal bandgap voltage reference (in mV): -100 up to 100
   - To compensate any difference between real value and measured value.
   - The ADC has a resolution of about 4.88mV for V_ref = 5V (Vcc) and
     1.07mV for V_ref = 1.1V (bandgap).
   - Will be added to measured voltage of bandgap reference.
*/
#define UREF_OFFSET           0
/*
   Exact values of probe resistors.
    - Standard value for Rl is 680 Ohms.
    - Standard value for Rh is 470k Ohms.
*/
//Rl in Ohms
#define R_LOW                 680
//Rh in Ohms
#define R_HIGH                470000
//Offset for systematic error of resistor measurement with Rh (470k) in Ohms.
#define RH_OFFSET             700 
/*
   Resistance of probe leads (in 0.01 Ohms).
    - Resistance of two probe leads in series.
    - Assuming all probe leads got same/similar resistance.
*/
#define R_ZERO                20
/* 
   Capacitance of the wires between PCB and terminals (in pF).
   Examples:
    - 2pF for wires 10cm long
*/
#define CAP_WIRES             15
/* 
   Capacitance of the probe leads connected to the tester (in pF).
   Examples:
     capacity  length of probe leads
     -------------------------------
      3pF      about 10cm
      9pF      about 30cm
     15pF      about 50cm
*/
#define CAP_PROBELEADS        9
//Maximum voltage at which we consider a capacitor being discharged (in mV)
#define CAP_DISCHARGED        2
/*
   Number of ADC samples to perform for each mesurement.
    - Valid values are in the range of 1 - 255.
*/
#define ADC_SAMPLES           25
//Estimated internal resistance of port to GND (in 0.1 Ohms)
#define R_MCU_LOW             200                //Default: 209
//Estimated internal resistance of port to VCC (in 0.1 Ohms)
#define R_MCU_HIGH            220                //Default: 235
//Voltage offset of µCs analog comparator (in mV): -50 up to 50
#define COMPARATOR_OFFSET     15
//Capacitance of the probe tracks of the PCB and the µC (in pF)
#define CAP_PCB               42
//Total default capacitance (in pF): max. 255
#define C_ZERO                CAP_PCB + CAP_WIRES + CAP_PROBELEADS
//ATMEGA328, 16Mhz Related
#define ADC_CLOCK_DIV         (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)
#define CPU_FREQ              F_CPU
#define OSC_STARTUP           16384

//Components ID's
#define COMP_NONE             0
#define COMP_ERROR            1
#define COMP_MENU             2
#define COMP_RESISTOR         10
#define COMP_CAPACITOR        11
#define COMP_INDUCTOR         12
#define COMP_DIODE            20
#define COMP_BJT              21
#define COMP_FET              22
#define COMP_IGBT             23
#define COMP_TRIAC            24
#define COMP_THYRISTOR        25

//Chars
#define LCD_CHAR_UNSET        0                  //Just a place holder 
#define LCD_CHAR_DIODE1       1                  //Diode icon '>|' 
#define LCD_CHAR_DIODE2       2                  //Diode icon '|<' 
#define LCD_CHAR_CAP          3                  //Capacitor icon '||' 
#define LCD_CHAR_FLAG         4                  //Flag Icon
#define LCD_CHAR_RESIS1       6                  //Resistor left icon '[' 
#define LCD_CHAR_RESIS2       7                  //Resistor right icon ']'
#ifdef DEBUG_PRINT
  #define LCD_CHAR_OMEGA      79              
  #define LCD_CHAR_MICRO      '\u00B5'           //Code for Arduino Serial Monitor
#else
 #ifdef LCD_PRINT
  #define LCD_CHAR_OMEGA      244                //Default: 244 
  #define LCD_CHAR_MICRO      228
 #else
  //LCD_DOGM128
  #define LCD_CHAR_OMEGA      248                // omega
  #define LCD_CHAR_MICRO      117                // u
 #endif
#endif

//Error type IDs
#define TYPE_DISCHARGE        1                  //Discharge error

//FET type bit masks (also used for IGBTs)
#define TYPE_N_CHANNEL        0b00000001         //n channel 
#define TYPE_P_CHANNEL        0b00000010         //p channel 
#define TYPE_ENHANCEMENT      0b00000100         //Enhancement mode 
#define TYPE_DEPLETION        0b00001000         //Depletion mode 
#define TYPE_MOSFET           0b00010000         //MOSFET 
#define TYPE_JFET             0b00100000         //JFET 
#define TYPE_IGBT             0b01000000         //IGBT (no FET) 

//Mode bitmask
#define MODE_LOW_CURRENT      0b00000001         //Low test current 
#define MODE_HIGH_CURRENT     0b00000010         //High test current 
#define MODE_DELAYED_START    0b00000100         //Delayed start

//BJT (bipolar junction transistor) type IDs 
#define TYPE_NPN              1                  //NPN
#define TYPE_PNP              2                  //PNP

//Tester operation modes
#define MODE_CONTINOUS        0                  //Continous
#define MODE_AUTOHOLD         1                  //Auto hold 

//Multiplicator tables
#define TABLE_SMALL_CAP       1
#define TABLE_LARGE_CAP       2
#define TABLE_INDUCTOR        3

//Bit flags for PullProbe()
#define FLAG_PULLDOWN         0b00000000
#define FLAG_PULLUP           0b00000001
#define FLAG_1MS              0b00001000
#define FLAG_10MS             0b00010000

// Component Icon values for LCD_DOGM128
#define COMPONENT_NONE             0
#define COMPONENT_ERROR            1
#define COMPONENT_MENU             2
#define COMPONENT_RESISTOR         3
#define COMPONENT_CAPACITOR        4
#define COMPONENT_INDUCTOR         5
#define COMPONENT_DIODE            6
#define COMPONENT_NPN              7
#define COMPONENT_PNP              8 
#define COMPONENT_NFET             9
#define COMPONENT_PFET             10
#define COMPONENT_NIGBT            11
#define COMPONENT_PIGBT            12
#define COMPONENT_TRIAC            13
#define COMPONENT_THYRISTOR        14
#define COMPONENT_ZENER            15
#define COMPONENT_NMOS             16
#define COMPONENT_PMOS             17
#define COMPONENT_BJTN             18
#define COMPONENT_BJTP             19
#define COMPONENT_NMOSD            20
#define COMPONENT_PMOSD            21
#define COMPONENT_NEVER            99

#endif // CONFIG_H
