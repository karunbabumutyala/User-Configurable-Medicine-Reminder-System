#ifndef _M_KPM_H_           // Include guard start: prevents multiple inclusion of this header file
#define _M_KPM_H_           // Defines the macro _M_KPM_H_ to indicate this file is included

//row pins and column pins   // Section describing row and column pin mappings for keypad

#define ROW0 16            //@P1.16 ? Defines ROW0 connected to pin number 16 (Port 1, Pin 16)
#define ROW1 17            // Defines ROW1 connected to pin number 17
#define ROW2 18            // Defines ROW2 connected to pin number 18
#define ROW3 19            // Defines ROW3 connected to pin number 19
#define COL0 20            // Defines COL0 connected to pin number 20
#define COL1 21            // Defines COL1 connected to pin number 21
#define COL2 22            // Defines COL2 connected to pin number 22
#define COL3 23            // Defines COL3 connected to pin number 23

//kpm functions declaration   // Section for keypad-related function declarations (prototypes)

void init_kpm(void);        // Function prototype to initialize keypad module (set pin directions, etc.)
char colscan(void);         // Function prototype to scan columns and detect active column
char rowcheck(void);        // Function prototype to check which row is active
char colcheck(void);        // Function prototype to check column status
unsigned char keyscan(void); // Function prototype to perform full keypad scan and return pressed key
int readnum(void);          // Function prototype to read a numeric value from keypad input

#endif                      // End of include guard (_M_KPM_H_)
