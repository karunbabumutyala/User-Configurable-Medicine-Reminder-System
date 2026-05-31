#ifndef _interrupt_h_
#define _interrupt_h_

/*---------------------------------------------------------
    External Interrupt Pin Configuration Definitions
----------------------------------------------------------*/

// EINT0 pin configuration value
// Used to configure the required pin as EINT0 function
#define EINT0_INPUT_PIN 0X0000000C

// VIC channel number for EINT0 interrupt
#define EINT0_CHNO 14


// EINT1 pin configuration value
// Used to configure the required pin as EINT1 function
#define EINT1_INPUT_PIN 0x000000C0

// VIC channel number for EINT1 interrupt
#define EINT1_CHNO 15


/*---------------------------------------------------------
    Function Declarations
----------------------------------------------------------*/

/*
    Function : init_interrupt()

    Purpose :
    Initializes external interrupt system.

    This function may configure:
    - Pin function selection
    - Interrupt triggering type
    - VIC interrupt slots
    - ISR addresses
*/
void init_interrupt(void);


/*
    Function : enable_interrupt_eint0()

    Purpose :
    Enables EINT0 interrupt in VIC.
*/
void enable_interrupt_eint0(void);


/*
    Function : enable_interrupt_eint1()

    Purpose :
    Enables EINT1 interrupt in VIC.
*/
void enable_interrupt_eint1(void);


/*
    Function : disable_interrupt_eint0()

    Purpose :
    Disables EINT0 interrupt.
*/
void disable_interrupt_eint0(void);


/*
    Function : disable_interrupt_eint1()

    Purpose :
    Disables EINT1 interrupt.
*/
void disable_interrupt_eint1(void);


/*
    Function : interrupt1_menu()

    Purpose :
    User-defined menu function related to interrupt operations.

    Example uses:
    - LCD display menu
    - UART command menu
    - Interrupt testing options
*/
void interrupt1_menu(void);


/*---------------------------------------------------------
    Interrupt Service Routines (ISR)
----------------------------------------------------------*/

/*
    Function : eint0_isr()

    Purpose :
    ISR for External Interrupt 0.

    Executes automatically when EINT0 interrupt occurs.
*/
void eint0_isr(void)__irq;


/*
    Function : eint1_isr()

    Purpose :
    ISR for External Interrupt 1.

    Executes automatically when EINT1 interrupt occurs.
*/
void eint1_isr(void)__irq;


#endif