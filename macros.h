#ifndef _MACROS_H_          // Prevents multiple inclusion of this header file
#define _MACROS_H_

// -------------------- MACROS RELATED TO BIT --------------------

// Read a bit at position POS from WORD
// Shifts WORD right by POS and masks with 1 to get the bit value (0 or 1)
#define RBIT(WORD,POS) ((WORD>>POS)&1)

// Set a bit at position POS in WORD
// First clears the bit using ~(1<<POS), then sets it using (1<<POS)
#define SETBIT(WORD,POS) (WORD =(WORD&~(1<<POS))|(1<<POS))

// Clear a bit at position POS in WORD
// Uses ~(1<<POS) to make that bit 0
#define CLRBIT(WORD,POS) (WORD =(WORD&~(1<<POS)))

// Set WORD with only one bit at position POS (all other bits become 0)
// Example: if POS=3 ? WORD = 00001000
#define G_SETBIT(WORD,POS) (WORD =1<<POS)


// -------------------- MACROS RELATED TO NIBBLE (4 BITS) --------------------

// Write a nibble (4 bits) into WORD at position POS
// Clears 4 bits at POS using ~(15<<POS) and inserts NIBBLE using (NIBBLE<<POS)
#define WNIBBLE(WORD,POS,NIBBLE) \
 (WORD =((WORD &(~(15<<POS)))|(NIBBLE<<POS)))
 
// Read a nibble (4 bits) from WORD at position POS
// Shifts WORD and masks with 15 (0xF ? 4 bits)
#define RNIBBLE(WORD,POS) ((WORD>>POS)&15)


// -------------------- MACROS RELATED TO BYTE (8 BITS) --------------------

// Write a byte (8 bits) into WORD at position POS
// Clears 8 bits using ~(0xFF<<POS) and inserts DATA using (DATA<<POS)
#define WBYTE(WORD,POS,DATA) (WORD =(WORD&~(0XFF<<POS))|(DATA<<POS))

#endif   // End of include guard
