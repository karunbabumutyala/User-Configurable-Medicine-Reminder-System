#ifndef _medicine_h_            // Include guard start to prevent multiple inclusion
#define _medicine_h_            // Define macro for include guard

#define BUZZER 24              // Define BUZZER pin connected to pin number 24

void  enter_timings(void);     // Function prototype to enter medicine timings
int check_timings(void);       // Function prototype to check current time with stored timings
void disp_medi_times(void);    // Function prototype to display all medicine timings
void clear_timings(void);      // Function prototype to clear all stored timings
char checking(int a,int b,int c); // Function prototype to check specific condition (time match logic)
void add_timings(void);        // Function prototype to add new timing
void modify_timings(void);     // Function prototype to modify existing timings
void show_next_timings(void);  // Function prototype to show upcoming timing

#endif                         // End of include guard
