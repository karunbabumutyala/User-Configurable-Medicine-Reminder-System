#ifndef _lcd_h_                 // Include guard start to prevent multiple inclusion
#define _lcd_h_                 // Define macro for include guard

//defines for commands          // Section for LCD control pin and command definitions

#define RS 16                   // Register Select pin connected to P1.16
#define RW 17                   // Read/Write pin connected to P1.17
#define EN 18                   // Enable pin connected to P1.18
#define LCD_DATA 8              // LCD data lines starting position (P1.8–P1.15)

#define MODE_8_BIT_LINE_1 0X30        // LCD 8-bit mode, single line
#define MODE_8_BIT_LINE_2 0X38        // LCD 8-bit mode, two lines
#define DISP_SET_DISP     0X0C        // Display ON, cursor OFF
#define DISP_SET_DISP_CUR 0X0E        // Display ON, cursor ON
#define DISP_SET_DISP_CUR_BLNK 0X0F   // Display ON, cursor blinking
#define CLR_LCD 0X01                 // Clear LCD display
#define ENTRY_MODE_I 0X06            // Entry mode: increment cursor
#define MOVE_CUR_BACK 0X10           // Move cursor one position backward
#define GOTO_LINE1_POS0 0X80         // Set cursor to line 1, position 0
#define GOTO_LINE2_POS0 0XC0         // Set cursor to line 2, position 0

//function lcd declaration      // Section for LCD function prototypes

void write_lcd(unsigned char data);   // Write raw data/command to LCD
void cmd_lcd(unsigned char data);     // Send command to LCD
void init_lcd(void);                  // Initialize LCD
void char_lcd(unsigned char data);    // Display single character on LCD
void str_lcd(unsigned char *str);     // Display string on LCD
void u32_lcd(unsigned int data);      // Display unsigned 32-bit number on LCD
void s32_lcd(int data);               // Display signed 32-bit number on LCD

#endif                               // End of include guard
