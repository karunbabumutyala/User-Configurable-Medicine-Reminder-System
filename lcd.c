#include <lpc21xx.h>          // Includes LPC21xx register definitions
#include "lcd.h"              // Includes LCD definitions and prototypes
#include "types.h"            // Includes user-defined data types (u8, u32, s32, etc.)
#include "delay.h"            // Includes delay functions
#include "macros.h"           // Includes bit/nibble/byte macros

void write_lcd(u8 data)       // Function to write data/command to LCD
{
	G_SETBIT(IOCLR0,RW);    // Set RW = 0 (write operation)
	WBYTE(IOPIN0,LCD_DATA,data); // Place data on LCD data pins
	G_SETBIT(IOSET0,EN);    // Set EN = 1 (enable high)
	delay_us(1);            // Small delay for enable pulse
	G_SETBIT(IOCLR0,EN);    // Set EN = 0 (latch data)
	delay_ms(2);            // Wait for LCD to process
}

void cmd_lcd(u8 data)         // Function to send command to LCD
{
	G_SETBIT(IOCLR0,RS);    // Set RS = 0 (command mode)
	write_lcd(data);        // Send command to LCD
}

void char_lcd(u8 data)        // Function to send character to LCD
{
	G_SETBIT(IOSET0,RS);    // Set RS = 1 (data mode)
	write_lcd(data);        // Send character data
}

void init_lcd(void)           // Function to initialize LCD
{
	PINSEL1 =0X00000000;    // Configure all pins as GPIO
	WBYTE(IODIR0,LCD_DATA,0XFF); // Set LCD data pins as output
	SETBIT(IODIR0,RW);      // Set RW pin as output
	SETBIT(IODIR0,RS);      // Set RS pin as output
	SETBIT(IODIR0,EN);      // Set EN pin as output
	
	delay_ms(15);           // Wait for LCD power stabilization
	cmd_lcd(MODE_8_BIT_LINE_1); // Function set (8-bit mode)
	delay_ms(5);            // Delay
	cmd_lcd(MODE_8_BIT_LINE_1); // Repeat command
	delay_us(100);          // Short delay
	cmd_lcd(MODE_8_BIT_LINE_1); // Repeat again for initialization
	cmd_lcd(MODE_8_BIT_LINE_2); // Set 2-line mode
	cmd_lcd(DISP_SET_DISP);     // Turn ON display, cursor OFF
	cmd_lcd(CLR_LCD);           // Clear display
	cmd_lcd(ENTRY_MODE_I);      // Set entry mode (increment cursor)
}

void str_lcd(u8 *str)         // Function to display string on LCD
{
	while(*str)             // Loop until null character
	{
		char_lcd(*str++);  // Display character and move pointer
	}
}

void u32_lcd(u32 num)        // Function to display unsigned 32-bit number
{
	char a[10];             // Array to store digits
	int i=0;                // Index variable

	while(num)              // Extract digits until number becomes 0
	{
		a[i++]=((num%10)+48); // Convert digit to ASCII and store
		num/=10;              // Remove last digit
	}

	for(--i;i>=0;i--)       // Print digits in reverse order
	{
		char_lcd(a[i]);    // Display each digit
	}
}

void s32_lcd(s32 num)       // Function to display signed 32-bit number
{
	if(num<0)              // Check if number is negative
	{
		char_lcd('-');    // Display minus sign
		num = -num;
	}
	u32_lcd(num);          // Display number using unsigned function
}
