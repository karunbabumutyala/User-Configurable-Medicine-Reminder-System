#include "lpc21xx.h"          // Include LPC21xx register definitions
#include "m_kpm.h"            // Include keypad module
#include "lcd.h"              // Include LCD functions
#include "macros.h"           // Include macros
#include "delay.h"            // Include delay functions
#include "types.h"            // Include data types
#include "interrupt.h"        // Include interrupt functions
#include "medicine.h"         // Include medicine module

int j;                        // Global variable j
int timings[5][2];            // 2D array to store timings (hour, minute)
int entries,flag;             // Variables for number of entries and flag
int taken_flag=0;             // Flag to indicate medicine taken

void  enter_timings(void)     // Function to enter medicine timings
{
	int i,check1;            // Local variables

entries_label:	              // Label for retrying entry count
	cmd_lcd(CLR_LCD);       // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0); // Move cursor to line 1
	str_lcd((u8*)"enter No.of times"); // Prompt user
	cmd_lcd(GOTO_LINE2_POS0); // Move cursor to line 2
	str_lcd((u8*)"(max=5):"); // Display max limit
	entries = readnum();    // Read number of entries

	//check the entries is valid or not   // Existing comment

	if((entries>5)||(entries<=0)) // Validate range
	{
		cmd_lcd(CLR_LCD);   // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move cursor
		str_lcd((u8*)"WRONG INPUT"); // Error message
		cmd_lcd(GOTO_LINE2_POS0); // Move cursor
		str_lcd((u8*)"again enter"); // Retry message
		delay_ms(500);      // Delay
		goto entries_label; // Retry input
	}

	delay_ms(100);          // Delay
	cmd_lcd(CLR_LCD);       // Clear LCD

	for(i=0;i<entries;i++)  // Loop for each timing entry
	{
LABEL1:	
		cmd_lcd(CLR_LCD);  // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move cursor
		str_lcd((u8*)"timing of "); // Display text
		char_lcd(i+1+48);  // Display entry number
		cmd_lcd(GOTO_LINE2_POS0); // Move cursor
		str_lcd((u8*)"HOUR(0-23):"); // Prompt for hour
		check1=readnum();  // Read hour

		if(check1==-1)     // Skip condition
		{
			entries =i;    // Update entries count
			break;         // Exit loop
		}
		
		if(!((check1>=0)&&(check1<24))) // Validate hour
		{
			cmd_lcd(CLR_LCD); // Clear LCD
			cmd_lcd(GOTO_LINE1_POS0); // Move cursor
			str_lcd((u8*)"Invalid hours:"); // Error message
			cmd_lcd(GOTO_LINE2_POS0); // Move cursor
			str_lcd((u8*)"Enter again..!"); // Retry message
			delay_ms(400);  // Delay
			cmd_lcd(CLR_LCD); // Clear LCD
			goto LABEL1;   // Retry hour
		}

		timings[i][0]=check1; // Store hour
		delay_ms(500);        // Delay
		
LABEL2:
		cmd_lcd(CLR_LCD);  // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move cursor
		str_lcd((u8*)"timing of "); // Display text
		char_lcd(i+1+48);  // Display entry number
		cmd_lcd(GOTO_LINE2_POS0); // Move cursor
		str_lcd((u8*)"MINTUEs(0-59):"); // Prompt for minute
		check1 =readnum(); // Read minute

		if(check1==-1)     // Skip condition
		{
			entries =i;    // Update entries
			break;         // Exit loop
		}
		
		if(!((check1>=0)&&(check1<60))) // Validate minute
		{
			cmd_lcd(CLR_LCD); // Clear LCD
			cmd_lcd(GOTO_LINE1_POS0); // Move cursor
			str_lcd((u8*)"Invalid minitues.."); // Error
			cmd_lcd(GOTO_LINE2_POS0); // Move cursor
			str_lcd((u8*)"Enter again..!"); // Retry message
			delay_ms(400);  // Delay
			cmd_lcd(CLR_LCD); // Clear LCD
			goto LABEL2;   // Retry minute
		}
		
		timings[i][1]=check1; // Store minute
		
		if(!checking(timings[i][0],timings[i][1],i)) // Check duplicate timing
		{
			cmd_lcd(CLR_LCD); // Clear LCD
			cmd_lcd(GOTO_LINE1_POS0); // Move cursor
			str_lcd((u8*)"Already Set"); // Message
			cmd_lcd(GOTO_LINE2_POS0); // Move cursor
			str_lcd((u8*)"Enter again..!"); // Retry message
			delay_ms(400);  // Delay
			cmd_lcd(CLR_LCD); // Clear LCD
			goto LABEL1;   // Restart entry
		}

		delay_ms(500);      // Delay
		cmd_lcd(CLR_LCD);   // Clear LCD
	}
	
	cmd_lcd(CLR_LCD);       // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0); // Move cursor
	str_lcd((u8*)"    SET   "); // Display "SET"
	cmd_lcd(GOTO_LINE2_POS0); // Move cursor
	str_lcd((u8*)"SUCCESSFULLY"); // Success message
	delay_ms(500);          // Delay
	cmd_lcd(CLR_LCD);       // Clear LCD
}
int check_timings(void)           // Function to check current time with stored medicine timings
{
	u8 alert_min;               // Variable to store alert minute
	static int min1;            // Static variable to track previous minute
	
	if(flag ==0)                // Check if initialization not done
	{
		IODIR1 |=1<<BUZZER;   // Set BUZZER pin as output
		flag =1;               // Mark initialization done
	}

	if(min1!=MIN)              // Check if minute has changed
	{
		taken_flag=0;         // Reset taken flag
		min1 = 	MIN;         // Update previous minute
		show_next_timings();  // Display next timing
	}

	for(j=0;j<entries;j++)    // Loop through all stored timings
	{
		if((HOUR ==timings[j][0])&&(MIN == timings[j][1])) // Check match with current time
		{
			if(taken_flag==0) // Check if medicine not yet taken
			{
				alert_min=MIN; // Store current minute

				disable_interrupt_eint0(); // Disable external interrupt 0

				//the above statement for to make the below statements(section)  // Existing comment
				//CRITICAL SECTION                                                // Existing comment
		
				cmd_lcd(GOTO_LINE1_POS0); // Move cursor to line 1
				str_lcd((u8*)"*ALERT..!!!!!"); // Display alert message
				cmd_lcd(GOTO_LINE2_POS0); // Move cursor to line 2
				str_lcd((u8*)"TAKE medicine     "); // Display instruction

				G_SETBIT(IOSET1,BUZZER); // Turn ON buzzer
							
				//after getting alert message External interrupt 1 will enable  // Existing comment

				enable_interrupt_eint1(); // Enable external interrupt 1
							
				//wait here till upto min over or eint1 press  // Existing comment

				while((alert_min==MIN)&&(taken_flag==0)); // Wait until minute changes or button pressed

				disable_interrupt_eint1(); // Disable external interrupt 1
				enable_interrupt_eint0();  // Re-enable external interrupt 0

				G_SETBIT(IOCLR1,BUZZER); // Turn OFF buzzer

				cmd_lcd(CLR_LCD); // Clear LCD
			}						
		}
	}
		
	return 0;                  // Return 0 after checking
}
void disp_medi_times(void)        // Function to display all medicine timings
{
	s32 l;                       // Loop variable

	if(entries ==0)             // Check if no timings stored
	{
		cmd_lcd(CLR_LCD);      // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move cursor to line 1
		str_lcd((u8*)"SLOTS are EMPTY"); // Display message
		delay_ms(500);         // Delay
		return;                // Exit function
	}

	if(entries ==1)             // Check if only one timing exists
	{
		cmd_lcd(CLR_LCD);      // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move cursor
		str_lcd((u8*)"s 1:hr:"); // Display slot info
		char_lcd((timings[0][0]/10)+48); // Display hour tens digit
		char_lcd((timings[0][0]%10)+48); // Display hour units digit
		str_lcd((u8*)" min:"); // Display "min:"
		char_lcd((timings[0][1]/10)+48); // Display minute tens digit
		char_lcd((timings[0][1]%10)+48); // Display minute units digit
		delay_ms(500);         // Delay
	}

	for(l=0;l<(entries-1);l++)  // Loop through timings (2 per screen)
	{
		cmd_lcd(CLR_LCD);      // Clear LCD

		cmd_lcd(GOTO_LINE1_POS0); // Move cursor to line 1
		str_lcd((u8*)"s ");   // Display "s "
		char_lcd(l+1+48);     // Display slot number
		str_lcd((u8*)" hr:"); // Display "hr:"
		char_lcd((timings[l][0]/10)+48); // Display hour tens digit
		char_lcd((timings[l][0]%10)+48); // Display hour units digit
		str_lcd((u8*)" min:"); // Display "min:"
		char_lcd((timings[l][1]/10)+48); // Display minute tens digit
		char_lcd((timings[l][1]%10)+48); // Display minute units digit
		
		cmd_lcd(GOTO_LINE2_POS0); // Move cursor to line 2
		str_lcd((u8*)"s ");   // Display "s "
		char_lcd(l+2+48);     // Display next slot number
		str_lcd((u8*)" hr:"); // Display "hr:"
		char_lcd((timings[l+1][0]/10)+48); // Display hour tens digit
		char_lcd((timings[l+1][0]%10)+48); // Display hour units digit
		str_lcd((u8*)" min:"); // Display "min:"
		char_lcd((timings[l+1][1]/10)+48); // Display minute tens digit
		char_lcd((timings[l+1][1]%10)+48); // Display minute units digit

		delay_ms(500);         // Delay before next display
	}
}
void clear_timings(void)         // Function to clear all stored timings
{
	entries=0;                  // Reset number of entries to zero

	cmd_lcd(CLR_LCD);          // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0);  // Move cursor to line 1
	str_lcd((u8*)"all slots are clear"); // Display message

	cmd_lcd(GOTO_LINE2_POS0);  // Move cursor to line 2
	str_lcd((u8*)"slots are empty"); // Display message

	delay_ms(500);             // Delay
	cmd_lcd(CLR_LCD);          // Clear LCD
}

char checking(int a,int b,int c) // Function to check duplicate timings
{
	int m;                     // Loop variable

	for(m=0;m<c;m++)          // Loop through existing entries
	{
		if((a==timings[m][0])&&(b==timings[m][1])) // Compare hour and minute
		{
			return 0;         // Return 0 if duplicate found
		}
	}
	
	return 1;                 // Return 1 if no duplicate found
}
void add_timings(void)          // Function to add a new timing
{
	int check2;               // Variable to store input value

	if(entries==5)           // Check if all slots are full
	{
		cmd_lcd(CLR_LCD);   // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move cursor to line 1
		str_lcd((u8*)"slot are full"); // Display message
		delay_ms(500);      // Delay
		cmd_lcd(CLR_LCD);   // Clear LCD
		return ;            // Exit function
	}

LABEL1:	                     // Label for retrying hour input
	cmd_lcd(CLR_LCD);        // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0);// Move cursor to line 1
	str_lcd((u8*)"hour(0-23):"); // Prompt for hour
	check2=readnum();        // Read hour input

	if(check2==-1){return;}  // Exit if skip key pressed

	if(!((check2>=0)&&(check2<24))) // Validate hour range
	{
		cmd_lcd(CLR_LCD);   // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move cursor
		str_lcd((u8*)"Invalid hours:"); // Error message
		cmd_lcd(GOTO_LINE2_POS0); // Move cursor
		str_lcd((u8*)"Enter again..!"); // Retry message
		delay_ms(400);      // Delay
		cmd_lcd(CLR_LCD);   // Clear LCD
		goto LABEL1;        // Retry hour input
	}

	timings[entries][0]=check2; // Store hour value
		
		
LABEL2:	                     // Label for retrying minute input
	cmd_lcd(CLR_LCD);        // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0);// Move cursor to line 1
	str_lcd((u8*)"min's(0-59):"); // Prompt for minutes
	check2=readnum();        // Read minute input

	if(check2==-1){return;}  // Exit if skip key pressed

	if(!((check2>=0)&&(check2<60))) // Validate minute range
	{
		cmd_lcd(CLR_LCD);   // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move cursor
		str_lcd((u8*)"Invalid minutes..!"); // Error message
		cmd_lcd(GOTO_LINE2_POS0); // Move cursor
		str_lcd((u8*)"Enter again..!"); // Retry message
		delay_ms(400);      // Delay
		cmd_lcd(CLR_LCD);   // Clear LCD
		goto LABEL2;        // Retry minute input
	}

	timings[entries][1]=check2; // Store minute value

	entries++;               // Increment number of entries
	
	cmd_lcd(CLR_LCD);        // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0);// Move cursor to line 1
	str_lcd((u8*)"  sucessfully "); // Display success message
	cmd_lcd(GOTO_LINE2_POS0);// Move cursor to line 2
	str_lcd((u8*)"    added"); // Display "added"
	delay_ms(500);           // Delay
	cmd_lcd(CLR_LCD);        // Clear LCD
	
}
void modify_timings(void)          // Function to modify existing timings
{
	char ch;                    // Variable to store key input
	int i=1,check1;             // i ? slot index, check1 ? input value

	//******************************   // Existing comment

	if(entries ==0)            // Check if no timings available
	{
		cmd_lcd(CLR_LCD);     // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move cursor to line 1
		str_lcd((u8*)"slots are empty"); // Display message
		delay_ms(500);        // Delay
		return;               // Exit function
	}
	
	//********************************  // Existing comment

LABEL:	                         // Label for slot selection
	cmd_lcd(CLR_LCD);            // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0);    // Move cursor to line 1
	str_lcd((u8*)"<AVALIBLE SLOTS>"); // Display heading

	cmd_lcd(GOTO_LINE2_POS0+2);  // Move cursor
	char_lcd('<');               // Display left arrow

	cmd_lcd(GOTO_LINE2_POS0+5);  // Move cursor
	str_lcd((u8*)"SLOT ");      // Display text
	char_lcd('1');              // Display initial slot number

	cmd_lcd(GOTO_LINE2_POS0+13); // Move cursor
	char_lcd('>');              // Display right arrow

	while(1)                     // Loop for slot selection
	{
		ch=keyscan();           // Read key

/***********************************************/  // Existing comment

		if(ch=='>')             // Next slot
		{
			i++;               // Increment slot index
			if(i>entries)      // Check overflow
			{
				i=1;          // Wrap to first slot
			}

			cmd_lcd(CLR_LCD);  // Clear LCD
			cmd_lcd(GOTO_LINE1_POS0);
			str_lcd((u8*)"<AVALIBLE SLOTS>");
			cmd_lcd(GOTO_LINE2_POS0+2);
			char_lcd('<');
			cmd_lcd(GOTO_LINE2_POS0+5);
			str_lcd((u8*)" SLOT ");
			char_lcd(i+48);    // Display slot number
			cmd_lcd(GOTO_LINE2_POS0+13);
			char_lcd('>');
		}

/***********************************************/  // Existing comment

		else if(ch=='<')        // Previous slot
		{
			i--;               // Decrement slot index
			if(i<=0)           // Check underflow
			{
				i=entries;    // Wrap to last slot
			}

			cmd_lcd(CLR_LCD);
			cmd_lcd(GOTO_LINE1_POS0);
			str_lcd((u8*)"<AVALIBLE SLOTS>");
			cmd_lcd(GOTO_LINE2_POS0+2);
			char_lcd('<');
			cmd_lcd(GOTO_LINE2_POS0+5);
			str_lcd((u8*)" SLOT ");
			char_lcd(i+48);    // Display slot number
			cmd_lcd(GOTO_LINE2_POS0+13);
			char_lcd('>');
		}

/*************************************************/  // Existing comment

		else if(ch == '=')      // Confirm selection
		{
			cmd_lcd(CLR_LCD);  // Clear LCD
			break;             // Exit loop
		}

/**************************************************/  // Existing comment

		else if(ch =='/')       // Cancel operation
		{
			return;            // Exit function
		}

/*****************************************************/  // Existing comment

		else                    // Invalid input
		{
			cmd_lcd(CLR_LCD);
			cmd_lcd(GOTO_LINE1_POS0);
			str_lcd((u8*)"ERROR...!!!");
			cmd_lcd(GOTO_LINE2_POS0);
			str_lcd((u8*)"enter AGAIN...!");
			delay_ms(500);
			cmd_lcd(CLR_LCD);
			goto LABEL;        // Restart selection
		}

/*****************************************************/  // Existing comment
	}
	
LABEL1:	
	cmd_lcd(CLR_LCD);         // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0); // Move cursor
	str_lcd((u8*)"timing of "); // Display text
	char_lcd(i+48);           // Display slot number
	cmd_lcd(GOTO_LINE2_POS0); // Move cursor
	str_lcd((u8*)"hour:");   // Prompt for hour
	check1=readnum();         // Read hour

	if(check1 == -1)          // Skip condition
	{
		return;               // Exit function
	}
		
	if(!((check1>=0)&&(check1<24))) // Validate hour
	{
		cmd_lcd(CLR_LCD);
		cmd_lcd(GOTO_LINE1_POS0);
		str_lcd((u8*)"Invalid hours:");
		cmd_lcd(GOTO_LINE2_POS0);
		str_lcd((u8*)"Enter again..!");
		delay_ms(400);
		cmd_lcd(CLR_LCD);
		goto LABEL1;          // Retry hour
	}

	timings[i-1][0]=check1;  // Store hour
	delay_ms(500);           // Delay
		
LABEL2:
	cmd_lcd(CLR_LCD);
	cmd_lcd(GOTO_LINE1_POS0);
	str_lcd((u8*)"timing of ");
	char_lcd(i+48);
	cmd_lcd(GOTO_LINE2_POS0);
	str_lcd((u8*)"mintues:");
	check1 =readnum();       // Read minute
		
	if(!((check1>=0)&&(check1<60))) // Validate minute
	{
		cmd_lcd(CLR_LCD);
		cmd_lcd(GOTO_LINE1_POS0);
		str_lcd((u8*)"Invalid minitues..");
		cmd_lcd(GOTO_LINE2_POS0);
		str_lcd((u8*)"Enter again..!");
		delay_ms(400);
		cmd_lcd(CLR_LCD);	
		goto LABEL2;          // Retry minute
	}
		
	timings[i-1][1]=check1;  // Store minute
		
	if(!checking(timings[i-1][0],timings[i-1][1],i-1)) // Check duplicate
	{
		cmd_lcd(CLR_LCD);
		cmd_lcd(GOTO_LINE1_POS0);
		str_lcd((u8*)"Already Set");
		cmd_lcd(GOTO_LINE2_POS0);
		str_lcd((u8*)"Enter again..!");
		delay_ms(400);
		cmd_lcd(CLR_LCD);
		goto LABEL1;          // Retry full entry
	}

	delay_ms(500);           // Delay

	cmd_lcd(CLR_LCD);
	cmd_lcd(GOTO_LINE1_POS0);
	str_lcd((u8*)"    SET   ");
	cmd_lcd(GOTO_LINE2_POS0);
	str_lcd((u8*)"SUCCESSFULLY");
	delay_ms(500);
	cmd_lcd(CLR_LCD);
}
void show_next_timings(void)        // Function to display next upcoming medicine timing
{
	char i,min=60,hr=24;           // i ? loop variable, min=60 & hr=24 used as initial max values

	if(entries==0)                 // Check if no timings are stored
	{
		return;                   // Exit function
	}
	
	for(i=0;i<entries;i++)        // Loop through all stored timings
	{
		if((timings[i][0] > HOUR) || ((timings[i][0] == HOUR) && (timings[i][1] > MIN))) // Check future time
		{
			if((timings[i][0] < hr) || ((timings[i][0] == hr) && (timings[i][1] < min))) // Find smallest next time
			{
				hr = timings[i][0]; // Update next hour
				min = timings[i][1]; // Update next minute
			}
		}
	}

	if(hr==24)                    // Check if no future timing found
	{
		cmd_lcd(CLR_LCD);        // Clear LCD
		cmd_lcd(GOTO_LINE1_POS0); // Move cursor to line 1
		str_lcd((u8*)" DONE TODAY  "); // Display message
		cmd_lcd(GOTO_LINE2_POS0); // Move cursor to line 2
		str_lcd((u8*)" NO MEDICINE "); // Display message
		delay_ms(500);           // Delay
		cmd_lcd(CLR_LCD); 
		return;                 // Exit function
	}
	
	cmd_lcd(CLR_LCD);            // Clear LCD
	cmd_lcd(GOTO_LINE1_POS0);    // Move cursor to line 1
	str_lcd((u8*)"   NEXT SLOT  "); // Display heading

	cmd_lcd(GOTO_LINE2_POS0);    // Move cursor to line 2
	str_lcd((u8*)"   HH:");     // Display "HH:"

	char_lcd(hr/10 +48);         // Display hour tens digit
	char_lcd(hr%10 +48);         // Display hour units digit

	str_lcd((u8*)" MM:");       // Display "MM:"

	char_lcd(min/10 +48);        // Display minute tens digit
	char_lcd(min%10 +48);        // Display minute units digit

	delay_ms(600);               // Delay
	cmd_lcd(CLR_LCD);            // Clear LCD
}

