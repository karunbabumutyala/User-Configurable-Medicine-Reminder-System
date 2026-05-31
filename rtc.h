#include "types.h"               // Includes user-defined data types (u8, u32, etc.)

#ifndef _RTC_H_                  // Include guard start to prevent multiple inclusion
#define _RTC_H_                  // Define macro for include guard

#define FOSC 12000000            // Oscillator frequency = 12 MHz
#define CCLK (FOSC*5)           // CPU clock = FOSC × 5
#define PCLK (CCLK/4)           // Peripheral clock = CCLK / 4

//PRESCALAR INT & FRAC           // Section for RTC prescaler values
#define PREINT_VAL (int)((PCLK/32768)-1)         // Integer part of prescaler calculation
#define PREFRAC_VAL (PCLK-(PREINT_VAL+1)*32768)  // Fractional part of prescaler

//CCR                            // RTC Clock Control Register bit definitions
#define RTC_RESET (1<<1)        // Bit to reset RTC
#define RTC_ENABLE (1<<0)       // Bit to enable RTC
#define RTC_CLKSRC (1<<4)       // Bit to select clock source

enum day{SUN,MON,TUE,WED,THU,FRI,SAT}; // Enumeration for days of the week (0–6)

void init_rtc(void);            // Function to initialize RTC

//MINI PROJECT                   // Section for mini project RTC-related functions
void display_time(void);        // Function to display current time
void set_time_by_kpm(void);     // Function to set time using keypad
void display_date(void);        // Function to display current date
void set_date_by_kpm(void);     // Function to set date using keypad
void display_weekday(void);     // Function to display current weekday
void set_weekday_by_kpm(void);  // Function to set weekday using keypad
void display_rtc(void);         // Function to display full RTC info
void auto_set_weekday(void);    // Function to automatically calculate weekday

#endif                          // End of include guard
