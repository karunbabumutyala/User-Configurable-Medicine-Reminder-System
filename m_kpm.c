#include <lpc21xx.h>          // Includes LPC21xx microcontroller register definitions
#include "m_kpm.h"           // Includes keypad header file (pin definitions and function prototypes)
#include "macros.h"          // Includes macros for bit, nibble, and byte operations
#include "lcd.h"             // Includes LCD interface functions

// Lookup table for keypad values (4x4 keypad mapping)
char kpm_LUT[4][4]={{'7','8','9','/'},      // First row mapping
										{'4','5','6','>'},      // Second row mapping
										{'1','2','3','<'},      // Third row mapping
										{'-','0','=','B'}};     // Fourth row mapping

static int keyflag =0;       // Static variable to track number of valid key presses

void init_kpm(void)         // Function to initialize keypad
{
	WNIBBLE(IODIR1,ROW0,15);  // Sets ROW0–ROW3 pins as output (15 = 0xF ? 4 bits set)
}

char colscan(void)               // Function to scan columns
{
	if(RNIBBLE(IOPIN1,COL0)==15)  // Reads 4 column bits; if all are HIGH (no key pressed)
			return 1;                 // Return 1 ? no key pressed
	else 
			return 0;                 // Return 0 ? key pressed detected
}

char rowcheck(void)                    // Function to detect which row is active
{
	char row;                            // Variable to store row index
	for(row=0;row<4;row++)               // Loop through all 4 rows
	{ 
		WNIBBLE(IOPIN1,ROW0,(~(1<<row))); // Activate one row at a time (make it LOW)
		if(!colscan())                    // Check if any column becomes LOW (key press detected)
			break;                          // If key found, break loop
	}
	WNIBBLE(IOPIN1,ROW0,0x0);          // Reset all rows to LOW after scanning
	return row;                        // Return detected row index
}

char colcheck(void)                  // Function to detect which column is active
{
	char col;                         // Variable to store column index
	for(col=0;col<4;col++)            // Loop through all 4 columns
	{
		if(!(RBIT(IOPIN1,(COL0+col)))) // Check each column pin; if LOW ? key pressed
			break;                       // Break when active column found
	}
	return col;                     // Return detected column index
}

unsigned char keyscan(void)        // Function to scan keypad and return pressed key
{
	char key,row_val,col_val;        // Variables to store key, row, and column values

	//wait here upto key pressed
	while(colscan());                // Wait until any key is pressed (columns go LOW)

	//then rowcheck for row value
	row_val=rowcheck();              // Get row index of pressed key

	//then colcheck for col value
	col_val=colcheck();              // Get column index of pressed key

	//wait her upto key release 
	while(!colscan());               // Wait until key is released

	key =kpm_LUT[row_val][col_val]; // Get actual key from lookup table
	return key;                     // Return detected key
}

int readnum(void)          // Function to read numeric input from keypad
{ 
	int key,num=0;          // key stores pressed key, num accumulates number

	while(1)                // Infinite loop to read keys continuously
	{
		key = keyscan();    // Get key from keypad
		
		if((((key>='0')&&(key<='9'))||(key=='B'))) // Check if key is digit or backspace
		{
			
			if(!(key =='B')) // If key is not backspace
			{
				char_lcd(key);         // Display key on LCD
				num = num*10+(key-48); // Convert char to int and append to number
				keyflag++;             // Increment key count
			}
			else                      // If key is backspace ('B')
			{
				if(keyflag>0)        // If at least one digit exists
				{
					num/=10;         // Remove last digit
					cmd_lcd(MOVE_CUR_BACK); // Move LCD cursor back
					char_lcd(' ');   // Clear last character on LCD
					cmd_lcd(MOVE_CUR_BACK); // Move cursor back again
					keyflag--;       // Decrement key count
				}
			}
		}	
		else if((key == '=')&&(keyflag>0)) // If '=' pressed and number exists
		{
			break;              // Exit loop (number entry complete)
		}
		else if(key == '/')    // If '/' pressed
		{
			keyflag =0;         // Reset key count
			return (-1);        // Return -1 (special condition)
		}
		else if(key == '-')    // If '-' pressed
		{
			keyflag =0;         // Reset key count
			return (-2);        // Return -2 (special condition)
		}
		
	}
	keyflag=0;               // Reset key count after completion
	return num;              // Return final number entered
}
