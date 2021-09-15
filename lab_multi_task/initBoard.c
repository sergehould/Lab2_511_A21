/***********************************************************************************************
*
*
* FileName:  initBoard.c      
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author        	Date            Version     Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Serge Hould      14 Jan. 2021		v1.0.0      Setup for PIC32    
* Serge Hould      27 Apr. 2021     v1.1        Set PBCLK to 80MHz to facilitate simulation.  Both sysclk and pbclk are the same.
*                                              T2 pre-scaler set to 1:4
* Serge Hould      6 Sept. 2021     v1.2       Disable JTAG inside initIO() - JTAG shared with RA5, RA4, RA1 and RA0                                          
* 
*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 
 #include "include/initBoard.h"
#include <stdint.h>
#include <xc.h>
#include <sys/attribs.h>


 // Configuration Bit settings
// SYSCLK = 80 MHz 
//(8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 40 MHz
// Primary Osc w/PLL (HS+PLL)
// WDT OFF, Peripheral Bus is CPU clock÷8
// Other options are default as per datasheet
// see file:C:\Program Files (x86)\Microchip\xc32\v1.40\docs\config_docs\32mx795f512l.html
 

#pragma config FPLLMUL = MUL_20
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLODIV = DIV_1 
#pragma config POSCMOD = HS, FNOSC = PRIPLL
#pragma config FPBDIV = DIV_1  // PBCLK = SYSCLK/DIV_1
#pragma config FWDTEN =  OFF    // disable


/* Sets up the IOs */
void initIO(void)
{
    DDPCONbits.JTAGEN = 0; // JTAG shared with RA5, RA4, RA1 and RA0
    /* LEDs */
    TRISAbits.TRISA7 = 0;       //LED D10
    TRISAbits.TRISA5 = 0;       //LED D8
    TRISAbits.TRISA4 = 0;       //LED D7
    TRISAbits.TRISA3 = 0;       //LED D6
    TRISAbits.TRISA2 = 0;       //LED D5
    TRISAbits.TRISA1 = 0;       //LED D4
    TRISAbits.TRISA0 = 0;       //LED D3
    
   
    TRISDbits.TRISD6 =1; //S3
    TRISDbits.TRISD7 =1;//S6
    TRISDbits.TRISD13 =1;//S4
    TRISAbits.TRISA6 =1; //S5 - shared with LED D9
	
     //TRISFbits.TRISF5=0; // TX
    
    /* Turns off all LEDs*/
     LATA = LATA & 0xffff0000;
     
     
       
}
 

       




/*
	Function that set timer 2 
	input: 
	output:

*/
void initTimer2( void)
{
// Initialize and enable Timer2
	T2CONbits.TON = 0; // Disable Timer
	T2CONbits.TCS = 0; // Select internal instruction cycle clock
	T2CONbits.TGATE = 0; // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b010; // Select 1:4 Prescaler
   // T2CONbits.TCKPS = 0b000; // Select 1:1 Prescaler
	TMR2 = 0x00; // Clear timer register
	PR2=0xffff; // Load the period value. 
	IPC2bits.T2IP = 0x01; // Set Timer 2 Interrupt Priority Level
	IFS0bits.T2IF = 0; // Clear Timer 2 Interrupt Flag
	IEC0bits.T2IE = 1; // Enable Timer 2 interrupt
   // _T2IP = 6; // Enable Timer 2 interrupt
	T2CONbits.TON = 1; // Start Timer              

} // init


