#include <lpc21xx.h>              // Include LPC21xx register definitions
#include "interrupt.h"            // Include interrupt header
#include "types.h"                // Include data types
#include "lcd.h"                  // Include LCD functions
#include "m_kpm.h"                // Include keypad module
#include "medicine.h"             // Include medicine module
#include "rtc.h"                  // Include RTC module
#include "delay.h"                // Include delay functions
#include "macros.h"               // Include macros

extern int taken_flag;            // External flag for medicine taken
extern int eint0_flag;            // External flag for interrupt 0

void init_interrupt(void)         // Function to initialize interrupts
{
	// cfg the p0.1 & p0.3 as EINT0 & EINT1 function   // Existing comment
	
	//clear the 2,3 & 6,7 bit in PINSEL0               // Existing comment
	PINSEL0 &= (~(3<<2))|(~(3<<6));  // Clear bits for P0.1 and P0.3
	
	//update as eint0 &eint1                           // Existing comment
	PINSEL0 |= EINT0_INPUT_PIN|EINT1_INPUT_PIN; // Configure pins as EINT0 & EINT1
	
	//cfg VECTOR INTERRUPT CONTROLLER peripheral       // Existing comment
	
	//EINT0 and EINT1 as irq type interrupts           // Existing comment
	//VICIntSelect = (0<<EINT0_CHNO)|(0<<EINT1_CHNO);  // IRQ selection (not required)
	
	//above statement is no required                   // Existing comment
	
	//default is ZERO(VICIntSelect =0)                 // Existing comment
	
	//enable the EINT0 &EINT1                          // Existing comment
	VICIntEnable = (1<<EINT0_CHNO)|(1<<EINT1_CHNO); // Enable interrupts
	
	//cfg eint0 as virq with highest prority-0         // Existing comment
	VICVectCntl0=(1<<5)|(EINT0_CHNO); // Enable slot and assign channel
	
	//load eint0_isr address int0 LUT sfr              // Existing comment
	VICVectAddr0=(u32)eint0_isr; // Load ISR address
	
	//cfg eint1 as virq with highest prority-1         // Existing comment
	VICVectCntl1=(1<<5)|(EINT1_CHNO); // Enable slot and assign channel
	
	//load eint0_isr address int0 LUT sfr              // Existing comment
	VICVectAddr1=(u32)eint1_isr; // Load ISR address
	
	
	//confg the EXTERNAL INTERRUPTS PERIPHERAL         // Existing comment
	
	//EXTINT =0;//default                              // Existing comment
	
	//cfg the  EINT0 & EINT1 as  EDGE TRIGGERING       // Existing comment
	EXTMODE |= (1<<0)|(1<<1); // Set edge triggered mode
	                           // 0 -> EINT0
	                           // 1 -> EINT1

//cfg the both as falling edge triggering             // Existing comment

	EXTPOLAR &=~(1<<0);      // Set EINT0 as falling edge
	EXTPOLAR &=~(1<<1);      // Set EINT1 as falling edge
}

void enable_interrupt_eint0(void) // Function to enable EINT0
{
	//enable the EINT0 in VIC                         // Existing comment
	VICIntEnable = 1<<EINT0_CHNO; // Enable interrupt
}

void enable_interrupt_eint1(void) // Function to enable EINT1
{
	//enable the EINT1 in VIC                         // Existing comment
	VICIntEnable = 1<<EINT1_CHNO; // Enable interrupt
}

void disable_interrupt_eint0(void) // Function to disable EINT0
{
	//disable the EINT0 in VIC                        // Existing comment
	VICIntEnClr = 1<<EINT0_CHNO; // Disable interrupt
}

void disable_interrupt_eint1(void) // Function to disable EINT1
{
	//disable the EINT0 in VIC                        // Existing comment
	VICIntEnClr = 1<<EINT1_CHNO; // Disable interrupt
}
void interrupt1_menu(void)          // Function to handle menu via interrupt
{
	u8 choice,rtc_choice,medi_choice; // Variables to store menu selections

	cmd_lcd(CLR_LCD);               // Clear LCD

	while(1)                        // Infinite loop for main menu
	{
		cmd_lcd(GOTO_LINE1_POS0);  // Move cursor to line 1
		str_lcd((u8*)"1.MEDI TIMES "); // Display option 1

		cmd_lcd(GOTO_LINE2_POS0);  // Move cursor to line 2
		str_lcd((u8*)"2.RTC 3.EXIT "); // Display options 2 & 3

		choice = keyscan();        // Read user choice

		switch(choice)             // Switch based on choice
		{
			case '1':             // Medicine menu
								/*cmd_lcd(CLR_LCD);        // Old code (commented)
								enter_timings();*/        // Old code (commented)

								while(1)                // Loop for medicine submenu
								{
									cmd_lcd(CLR_LCD);  // Clear LCD
									cmd_lcd(GOTO_LINE1_POS0); // Move cursor
									str_lcd((u8*)"1.SET 2.CLR 3.ADD"); // Display options

									cmd_lcd(GOTO_LINE2_POS0); // Move cursor
									str_lcd((u8*)"4SEE 5MOD 6EXIT"); // Display options

									medi_choice =keyscan(); // Read submenu choice

									switch(medi_choice)   // Switch for medicine submenu
									{
										case'1':enter_timings(); // Set timings
														break;
										case'2':clear_timings(); // Clear timings
														break;
										case'3':add_timings();   // Add timing
														break;
										case'4':disp_medi_times(); // Display timings
														break;
										case'5':modify_timings(); // Modify timings
														break;
										case'6':cmd_lcd(CLR_LCD); // Exit submenu
														break;
										default:cmd_lcd(CLR_LCD); // Invalid input
														cmd_lcd(GOTO_LINE1_POS0);
														str_lcd((u8*)"INVALId INPUT");
														delay_ms(400);
														break;
									}

									if(medi_choice=='6') // Check exit condition
									{
										break;            // Exit submenu loop
									}
								}
								break;

			case '2':             // RTC menu
								while(1)                // Loop for RTC submenu
								{
									cmd_lcd(CLR_LCD);  // Clear LCD
									cmd_lcd(GOTO_LINE1_POS0);
									str_lcd((u8*)"1.TIME 2.DATE"); // Display options

									cmd_lcd(GOTO_LINE2_POS0);
									str_lcd((u8*)"3.WEEK DAY 4.EXIT"); // Display options

									rtc_choice =keyscan(); // Read RTC choice

									switch(rtc_choice)   // Switch for RTC submenu
									{
										case '1':cmd_lcd(CLR_LCD); // Clear LCD
														 set_time_by_kpm(); // Set time
 														 break;

										case '2':cmd_lcd(CLR_LCD); // Clear LCD
														 set_date_by_kpm(); // Set date
				 										 auto_set_weekday(); // Auto update weekday
														break;

										case '3':cmd_lcd(CLR_LCD); // Clear LCD
														set_weekday_by_kpm(); // Set weekday
														break;

										case '4':cmd_lcd(CLR_LCD); // Exit submenu
															break;

										default:
														cmd_lcd(CLR_LCD); // Invalid input
														cmd_lcd(GOTO_LINE1_POS0);
														str_lcd((u8*)"INVALId INPUT");
														delay_ms(400);
									}

									if(rtc_choice=='4') // Check exit condition
									{
										break;          // Exit RTC submenu
									}
								}
								break;

			case '3':cmd_lcd(CLR_LCD); // Exit main menu
								break;

			default:
								cmd_lcd(CLR_LCD); // Invalid input
								cmd_lcd(GOTO_LINE1_POS0);
								str_lcd((u8*)"INVALId INPUT");				
								delay_ms(400);
		}

		if(choice =='3')         // Check exit condition for main menu
		{
			break;              // Exit main loop
		}
	}
}
void eint0_isr(void)__irq        // ISR for External Interrupt 0
{
	eint0_flag=1;             // Set flag indicating EINT0 occurred
									
	//clear EINT1 status in EXTINT peripheral   // Existing comment
	EXTINT =1<<0;             // Clear EINT0 interrupt flag in EXTINT register
	
	//Clear EINT0 status in VIC peripheral      // Existing comment
	VICVectAddr =0;           // Acknowledge interrupt in VIC
}

void eint1_isr(void)__irq        // ISR for External Interrupt 1
{
	
	// TURN OFF the BUZZER       // Existing comment
	G_SETBIT(IOCLR1,BUZZER);  // Turn OFF buzzer
	
	//clear alert message        // Existing comment
	cmd_lcd(CLR_LCD);         // Clear LCD
	
	//                          // Existing empty comment
	cmd_lcd(CLR_LCD);         // Clear LCD again
	cmd_lcd(GOTO_LINE1_POS0); // Move cursor to line 1
	str_lcd((u8*)"MEDICINE TAKEN"); // Display message
	cmd_lcd(GOTO_LINE2_POS0); // Move cursor to line 2
	str_lcd((u8*)"SUCESSFULLY"); // Display message
	delay_ms(500);            // Delay
	
	//this variable for update after the taken medicine   // Existing comment
	taken_flag=1;             // Set flag indicating medicine taken
	
	//after taken medicine enable the eint0   // Existing comment
	enable_interrupt_eint0(); // Enable EINT0 interrupt
	
	//clear EINT1 status in EXTINT peripheral // Existing comment
	EXTINT =1<<1;             // Clear EINT1 interrupt flag
	
	//Clear EINT0 status in VIC peripheral    // Existing comment
	VICVectAddr =0;           // Acknowledge interrupt in VIC
}


