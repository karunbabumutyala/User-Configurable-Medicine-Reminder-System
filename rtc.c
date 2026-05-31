#include "rtc.h"              // Include RTC header definitions
#include "types.h"            // Include user-defined data types
#include "lcd.h"              // Include LCD functions
#include "lpc21xx.h"          // Include LPC21xx register definitions
#include "m_kpm.h"            // Include keypad module functions
#include "delay.h"            // Include delay functions

u8 week_day[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"}; // Array storing weekday strings

void init_rtc(void)           // Function to initialize RTC
{
	CCR = RTC_RESET;        // Disable and reset RTC

	#ifndef _LCP2148        // Check if controller is not LPC2148

	//SET THE PRESCALAR INTEGER AND FRACTION  // Comment already present (kept as-is)

	PREINT  = PREINT_VAL;   // Load prescaler integer value
	PREFRAC = PREFRAC_VAL;  // Load prescaler fractional value

	//ENABLE THE RTC        // Comment already present (kept as-is)

	CCR = RTC_ENABLE;       // Enable RTC

	#else                   // If controller is LPC2148

	CCR = RTC_ENABLE|RTC_CLKSRC; // Enable RTC with clock source selection

	#endif                  // End of conditional compilation

	YEAR =2026;             // Set default year value
	MONTH =1;               // Set default month value
	DOM =1;                 // Set default day of month
	
}



void set_time_by_kpm(void)        // Function to set time using keypad
{
	
	int check;                  // Variable to store keypad input

HOUR_LABEL:	                   // Label for hour input section
	cmd_lcd(CLR_LCD);          // Clear LCD
	cmd_lcd(GOTO_LINE2_POS0);  // Move cursor to line 2
	display_time();            // Display current time

	//setting of hours          // Existing comment (kept)

	cmd_lcd(GOTO_LINE1_POS0);  // Move cursor to line 1
	str_lcd((u8*)"HOURs(0-23):"); // Display hour prompt
	check =readnum();          // Read number from keypad
	
	//checking entered value of HOUR ,is valid..?   // Existing comment

	if((check<24)&&(check>=-2)) // Check valid range or control values
	{
		if(check==-1){}        // Skip condition (do nothing)
		else if(check==-2)     // Back condition
		{
			goto HOUR_LABEL;  // Go back to hour input
		}
		else                  // Valid hour entered
		{
			HOUR = check;    // Store hour
			cmd_lcd(GOTO_LINE2_POS0); // Move cursor
			display_time();  // Display updated time
			delay_ms(100);   // Delay
		}
	}
	else                      // Invalid input
	{
		cmd_lcd(CLR_LCD);    // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move to line 1
		str_lcd((u8*)"ERROR...!!!"); // Show error
		cmd_lcd(GOTO_LINE2_POS0); // Move to line 2
		str_lcd((u8*)"enter AGAIN...!"); // Retry message
		delay_ms(500);       // Delay
		cmd_lcd(CLR_LCD);    // Clear LCD
		goto HOUR_LABEL;     // Retry hour input
	}

	delay_ms(400);          // Delay
	cmd_lcd(CLR_LCD);       // Clear LCD
	
	//setting for minutes    // Existing comment

MIN_LABEL:	               // Label for minute input
	cmd_lcd(GOTO_LINE2_POS0); // Move cursor to line 2
	display_time();         // Display current time
	cmd_lcd(GOTO_LINE1_POS0); // Move to line 1
	str_lcd((u8*)"MIN's(0-59):"); // Display minute prompt
	check = readnum();      // Read minutes
	
	//	//checking entered value of MIN ,is valid..?   // Existing comment

	if((check<60)&&(check>=-2)) // Validate minute input
	{
		if(check==-1){}        // Skip
		else if(check==-2)     // Back
		{
			goto HOUR_LABEL;  // Go back to hour input
		}
		else                  // Valid minute
		{
			MIN = check;     // Store minute
			cmd_lcd(GOTO_LINE2_POS0); // Move cursor
			display_time();  // Display updated time
		}
	}
	else                      // Invalid minute
	{
		cmd_lcd(CLR_LCD);    // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move to line 1
		str_lcd((u8*)"ERROR...!!!"); // Error message
		cmd_lcd(GOTO_LINE2_POS0); // Move to line 2
		str_lcd((u8*)"enter min's AGAIN...!"); // Retry message
		delay_ms(400);       // Delay
		cmd_lcd(CLR_LCD);    // Clear LCD
		goto MIN_LABEL;      // Retry minute input
	}

	delay_ms(1000);         // Delay
	cmd_lcd(CLR_LCD);       // Clear LCD
	
	//setting for seconds    // Existing comment

SEC_LABEL:	               // Label for second input
	cmd_lcd(GOTO_LINE2_POS0); // Move cursor to line 2
	display_time();         // Display current time
	cmd_lcd(GOTO_LINE1_POS0); // Move to line 1
	str_lcd((u8*)"SEC's(0-59):"); // Display seconds prompt
	check =readnum();       // Read seconds

	if((check<60)&&(check>=-2)) // Validate seconds
	{
		if(check==-1){}        // Skip
		else if(check==-2)     // Back
		{
			goto MIN_LABEL;   // Go back to minute input
		}
		else                  // Valid seconds
		{
			SEC = check;     // Store seconds
			cmd_lcd(GOTO_LINE2_POS0); // Move cursor
			display_time();  // Display updated time
			delay_ms(400);   // Delay
		}
	}
	else                      // Invalid seconds
	{
		cmd_lcd(CLR_LCD);    // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move to line 1
		str_lcd((u8*)"ERROR...!!!"); // Error message
		cmd_lcd(GOTO_LINE2_POS0); // Move to line 2
		str_lcd((u8*)"enter SEC's AGAIN...!"); // Retry message
		delay_ms(500);       // Delay
		cmd_lcd(CLR_LCD);    // Clear LCD
		goto SEC_LABEL;      // Retry seconds
	}

	cmd_lcd(CLR_LCD);       // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0); // Move to line 1
	str_lcd((u8*)"    SET   "); // Display "SET"
	cmd_lcd(GOTO_LINE2_POS0); // Move to line 2
	str_lcd((u8*)"SUCCESSFULLY"); // Display success message
	delay_ms(500);          // Delay
	cmd_lcd(CLR_LCD);       // Clear LCD
}

/// function for display the time only i.e., HH:MM:SS   // Existing comment

void display_time(void)      // Function to display time
{
	
	char_lcd(HOUR/10+48);  // Display hour tens digit
	char_lcd(HOUR%10+48);  // Display hour units digit
	char_lcd(':');         // Display separator
	char_lcd(MIN/10+48);   // Display minute tens digit
	char_lcd(MIN%10+48);   // Display minute units digit
	char_lcd(':');         // Display separator
	char_lcd(SEC/10+48);   // Display second tens digit
	char_lcd(SEC%10+48);   // Display second units digit
}

/// function for display the DATE only i.e., DD/MM/YYYY   // Existing comment

void display_date(void)        // Function to display date on LCD
{
	
	char_lcd(DOM/10+48);   // Display tens digit of day (DOM)
	char_lcd(DOM%10+48);   // Display units digit of day (DOM)
	char_lcd('/');         // Display '/' separator
	char_lcd(MONTH/10+48); // Display tens digit of month
	char_lcd(MONTH%10+48); // Display units digit of month
	char_lcd('/');         // Display '/' separator
	u32_lcd(YEAR);         // Display full year value
}
void set_date_by_kpm(void)        // Function to set date using keypad
{
	int date;                    // Variable to store date input
	int month;                   // Variable to store month input
	int year;                    // Variable to store year input
	s32 date1,month1,year1;     // Variables to store previous values

DATE_LABEL:	                   // Label for date input
	date1= DOM;                // Backup current date
	month1 =MONTH;             // Backup current month
	year1 = YEAR;              // Backup current year

	//date setting             // Existing comment

	cmd_lcd(GOTO_LINE2_POS0); // Move cursor to line 2
	display_date();           // Display current date
	cmd_lcd(GOTO_LINE1_POS0); // Move cursor to line 1
	str_lcd((u8*)"enter DATE:"); // Prompt for date
	date =readnum();          // Read date input
	
	//skipping the date entry  // Existing comment

	if(date==-1)              // Check skip condition
	{
		date =date1;          // Restore previous date
	}

	//backward                // Existing comment

	if(date ==-2)             // Check back condition
	{
		goto DATE_LABEL;      // Go back to date input
	}
	
	cmd_lcd(GOTO_LINE2_POS0); // Move cursor
	DOM =date;               // Set date
	display_date();          // Display updated date
	delay_ms(200);           // Delay

MONTH_LABEL:	               // Label for month input
	cmd_lcd(CLR_LCD);        // Clear LCD
	cmd_lcd(GOTO_LINE2_POS0);// Move cursor
	display_date();          // Show date
	cmd_lcd(GOTO_LINE1_POS0);// Move to line 1
	str_lcd((u8*)"enter MONTH:"); // Prompt for month
	month =readnum();        // Read month input
		
	//skipping the month entry // Existing comment

	if(month==-1)             // Skip condition
	{
		month =month1;       // Restore previous month
	}

	//move back the date      // Existing comment

	if(month ==-2)            // Back condition
	{
		goto DATE_LABEL;     // Go back to date input
	}

	cmd_lcd(GOTO_LINE2_POS0);// Move cursor
	MONTH =month;            // Set month
	display_date();          // Display updated date
	delay_ms(200);           // Delay
	
	cmd_lcd(CLR_LCD);        // Clear LCD
	cmd_lcd(GOTO_LINE2_POS0);// Move cursor
	display_date();          // Show date
	cmd_lcd(GOTO_LINE1_POS0);// Move to line 1
	str_lcd((u8*)"enter YEAR:"); // Prompt for year
	year =readnum();         // Read year input
		
	//skipping the date no need entering   // Existing comment

	if(year==-1)              // Skip condition
	{
		year =year1;         // Restore previous year
	}

	//move back the month     // Existing comment

	if(year ==-2)             // Back condition
	{
		goto MONTH_LABEL;    // Go back to month input
	}
	
	cmd_lcd(GOTO_LINE2_POS0);// Move cursor
	YEAR =year;              // Set year
	display_date();          // Display updated date
	delay_ms(200);           // Delay
	cmd_lcd(CLR_LCD);        // Clear LCD
	
	
	//checking the value valid or not   // Existing comment

	if((year>=2000)&&(year<=4096)) // Validate year range
	{
		if((month>=0)&&(month<= 12)) // Validate month range
		{
			if((((month>0)&&(month<8))&&(month%2))||(((month>7)&&(month<13))&&(month%2==0))) // 31-day months
			{
				if((date<32)&&(date>0)) // Validate date
				{
					DOM =date;        // Set date
					MONTH = month;    // Set month
					YEAR = year;      // Set year
					cmd_lcd(CLR_LCD); // Clear LCD
					cmd_lcd(GOTO_LINE1_POS0); // Move cursor
					str_lcd((u8*)"    SET   "); // Show message
					cmd_lcd(GOTO_LINE2_POS0); // Move cursor
					str_lcd((u8*)"SUCCESSFULLY"); // Success message
					delay_ms(500);   // Delay
					cmd_lcd(CLR_LCD);// Clear LCD
					return;          // Exit function
				}
			}
			else if(month==2) // February case
			{
				if((year%4==0)&&(year%100!=0)) // Leap year check
				{
					if((date<30)&&(date>0)) // Max 29 days
					{
						DOM =date;    
						MONTH = month;
						YEAR = year;
						cmd_lcd(CLR_LCD);
						cmd_lcd(GOTO_LINE1_POS0);
						str_lcd((u8*)"    SET   ");
						cmd_lcd(GOTO_LINE2_POS0);
						str_lcd((u8*)"SUCCESSFULLY");
						delay_ms(500);
						cmd_lcd(CLR_LCD);
						return;
					}	
				}
				else                   // Non-leap year
				{
					if((date<29)&&(date>0)) // Max 28 days
					{
						DOM =date;
						MONTH = month;
						YEAR = year;
						cmd_lcd(CLR_LCD);
						cmd_lcd(CLR_LCD);
						cmd_lcd(GOTO_LINE1_POS0);
						str_lcd((u8*)"    SET   ");
						cmd_lcd(GOTO_LINE2_POS0);
						str_lcd((u8*)"SUCCESSFULLY");
						delay_ms(500);
						cmd_lcd(CLR_LCD);
						return;
					}
				}
			}
			else                    // 30-day months
			{
				if((date<31)&&(date>0)) // Validate date
				{
					DOM =date;
					MONTH = month;
					YEAR = year;
					cmd_lcd(CLR_LCD);
					cmd_lcd(GOTO_LINE1_POS0);
					str_lcd((u8*)"    SET   ");
					cmd_lcd(GOTO_LINE2_POS0);
					str_lcd((u8*)"SUCCESSFULLY");
					delay_ms(500);
					cmd_lcd(CLR_LCD);
					return;
				}
			}
		}
		
	}

	cmd_lcd(CLR_LCD);        // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0);// Move cursor
	str_lcd((u8*)"ERROR...!!!"); // Error message
	cmd_lcd(GOTO_LINE2_POS0);// Move cursor
	str_lcd((u8*)"enter date AGAIN...!"); // Retry message
	delay_ms(500);           // Delay
	cmd_lcd(CLR_LCD);        // Clear LCD
	goto DATE_LABEL;         // Restart process
}
void display_weekday(void)        // Function to display weekday
{
	
	str_lcd(week_day[DOW]);     // Display weekday string using DOW index
}

void set_weekday_by_kpm(void)    // Function to set weekday using keypad
{
	s32 check;                  // Variable to store key input
	int k;                      // Variable for weekday index
	k=DOW;                      // Initialize k with current weekday

WEEK_LABEL:	                   // Label for retry
	cmd_lcd(CLR_LCD);          // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0);  // Move cursor to line 1
	str_lcd((u8*)"enter DAY:"); // Display prompt

	cmd_lcd(GOTO_LINE2_POS0);  // Move to line 2
	char_lcd('<');             // Display left arrow

	cmd_lcd(GOTO_LINE2_POS0+5); // Move cursor to middle
	str_lcd(week_day[k]);      // Display current weekday

	cmd_lcd(GOTO_LINE2_POS0+10); // Move cursor right
	char_lcd('>');             // Display right arrow

	while(1)                   // Infinite loop for input handling
	{
		cmd_lcd(GOTO_LINE1_POS0); // Move to line 1
		str_lcd((u8*)"enter DAY:"); // Display prompt again
		
		check=keyscan();       // Read key from keypad

		cmd_lcd(GOTO_LINE2_POS0); // Move to line 2
		char_lcd('<');         // Display left arrow

		cmd_lcd(GOTO_LINE2_POS0+10); // Move right
		char_lcd('>');         // Display right arrow

		if(check =='>')        // If next key pressed
		{
			k++;              // Increment weekday index
			if(k>6)           // Check overflow
			{
				k=0;         // Wrap to Sunday
			}

			cmd_lcd(GOTO_LINE2_POS0+5); // Move cursor
			str_lcd(week_day[k]); // Display updated weekday
		}

		else if(check=='<')   // If previous key pressed
		{
			--k;             // Decrement weekday index
			if(k<0)          // Check underflow
			{
				k=6;         // Wrap to Saturday
			}

			cmd_lcd(GOTO_LINE2_POS0+5); // Move cursor
			str_lcd(week_day[k]); // Display updated weekday
		}

		else if(check =='/')  // Cancel operation
		{
			//	check =check1;   // Existing comment (kept)
			break;            // Exit loop
		}

		else if(check =='=') // Confirm selection
		{
			cmd_lcd(CLR_LCD); // Clear LCD
			DOW =k;          // Set selected weekday
			break;           // Exit loop
		}

		else                 // Invalid key
		{
			cmd_lcd(CLR_LCD); // Clear LCD
			cmd_lcd(GOTO_LINE1_POS0); // Move to line 1
			str_lcd((u8*)"ERROR...!!!"); // Show error
			cmd_lcd(GOTO_LINE2_POS0); // Move to line 2
			str_lcd((u8*)"enter AGAIN...!"); // Retry message
			delay_ms(500);  // Delay
			cmd_lcd(CLR_LCD); // Clear LCD
			goto WEEK_LABEL; // Restart process
		}
	}
	
	
	/*check =readnum();        // Old method (commented code)
	//checking the entered value
	if((check>=0)&&(check<=6))
	{
		DOW = check;
	}
	else
	{
		cmd_lcd(CLR_LCD);
		cmd_lcd(GOTO_LINE1_POS0);
		str_lcd((u8*)"ERROR...!!!");
		cmd_lcd(GOTO_LINE2_POS0);
		str_lcd((u8*)"enter AGAIN...!");
		delay_ms(500);
		cmd_lcd(CLR_LCD);
	}
	delay_ms(500);*/

	cmd_lcd(CLR_LCD);        // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0);// Move to line 1
	str_lcd((u8*)"    SET   "); // Display "SET"
	cmd_lcd(GOTO_LINE2_POS0);// Move to line 2
	str_lcd((u8*)"SUCCESSFULLY"); // Display success message
	delay_ms(500);           // Delay
	cmd_lcd(CLR_LCD);        // Clear LCD
}

void auto_set_weekday(void)   // Function to auto calculate weekday
{
	int week,dom,month,y1,y2,year; // Declare variables

	dom =DOM;               // Copy day of month
	month =MONTH;           // Copy month
	year = YEAR;            // Copy year
	
	if((month ==1)||(month==2)) // Check Jan/Feb
	{
		month +=12;         // Adjust month
		year -=1;           // Adjust year
	}

	y1= year%100;           // Last two digits of year
	y2 =year/100;           // First two digits of year

	week =(dom+((13*(month+1))/5)+y1+(y1/4)+(y2/4)+(5*y2))%7; // Zeller formula

	DOW =week;              // Store result
	DOW-=1;                 // Adjust index
}
void display_rtc(void)           // Function to display full RTC information
{
	cmd_lcd(GOTO_LINE1_POS0); // Move cursor to line 1 starting position
	display_time();           // Display current time (HH:MM:SS)

	cmd_lcd(GOTO_LINE2_POS0); // Move cursor to line 2 starting position
	display_date();           // Display current date (DD/MM/YYYY)

	cmd_lcd(GOTO_LINE1_POS0+10); // Move cursor to line 1, position 10
	display_weekday();        // Display weekday at that position
}
