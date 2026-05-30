void delay_us(unsigned int i)        // Function to generate microsecond delay
{
	for(i*=12;i>0;i--);            // Multiply i by 12 and run empty loop for delay
}

void delay_ms(unsigned int i)        // Function to generate millisecond delay
{
	for(i*=12000;i>0;i--);         // Multiply i by 12000 and run empty loop for delay
}

void delay_s(unsigned int i)         // Function to generate second delay
{
	for(i*=12000000;i>0;i--);      // Multiply i by 12000000 and run empty loop for delay
}
