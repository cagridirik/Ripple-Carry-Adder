#include <stdio.h>
#include <stdint.h>


// This code exhibits how a ripple carry adder works for two 32-bit hexadecimal numbers.
// The library stdint.h contains variables like uint32_t.

// Define a new variable that has the components sum and cout, which belong to 1-bit addition.
typedef struct {
    uint8_t sum;
    uint8_t cout;
} AdderResult;

// Function prototypes...
AdderResult bitwise_halfAdder (uint8_t, uint8_t);
AdderResult bitwise_fullAdder (uint8_t, uint8_t, uint8_t);
uint32_t rippleCarryAdder (uint32_t, uint32_t);

// Under the main module, ask for two hexadecimal inputs from the user, express them in decimal, and add them up.
int main() {
    uint32_t hex_1;
    uint32_t hex_2;

    // %x stand for hexadecimal and %u stands for an unsigned integer.
    printf("Enter the first 32-bit hexadecimal number: ");
    scanf("%x", &hex_1);
    printf ("You entered %u in decimal.\n", hex_1);

    printf("Enter the second 32-bit hexadecimal number: ");
    scanf("%x", &hex_2);
    printf ("You entered %u in decimal.\n", hex_2);

    uint32_t sum = rippleCarryAdder(hex_1, hex_2);
    printf("The sum is 0x%08x in hexadecimal.\n", sum);
    printf("The sum is %u in decimal.\n", sum);

    return 0;
}

// Adds two 32-bit unsigned integers.
uint32_t rippleCarryAdder(uint32_t first, uint32_t second) {
    uint32_t sum = 0;
    // Carry-in is 0 for bit 0.
    uint32_t cin = 0;
    
    // The loop deals with each bit one by one starting from the LSB.
    for (int i = 0; i < 32; i++) {

        // >> i shifts the number i bits to the right, and executing a bitwise AND with 1 yields the ith bit as an 8-bit 1 or 0.
        // Say an 8-bit binary number is 01010001, and we need bit 4, which is 1.
        // 01010001 >> 4 gives 00000101 --> Performing bitwise 00000101 AND 00000001 gives 00000001, which was bit 4.
        uint8_t a = (first >> i) & (uint8_t)1;
        uint8_t b = (second >> i) & (uint8_t)1;
        
        // The ith bit of the final sum is the ith result of the full adder module.
        AdderResult ith_result = bitwise_fullAdder(a, b, cin);
        // At every iteration, the carry in for the next bitwise full addition becomes the carry-out of the previous full addition.
        cin = ith_result.cout;
        // << i shifts the number i units to the left, and executing a bitwise OR with the existing sum plugs the ith result into the ith bit of the final sum.
        // Say an 8-bit number is 00010001 and we want to plug in 1 into bit 7, which is 0.
        // 00000001 << 7 gives 10000000 --> Performing bitwise 00010001 OR 10000000 gives 10010001.  
        sum |= ((uint32_t)ith_result.sum << i);
    }
    return sum;
}

// Shows how a half adder works...
AdderResult bitwise_halfAdder(uint8_t a, uint8_t b) {
    AdderResult result;

    // Sum is a XOR b (odd number of variables can be 1, meaning only one of them can be 1).
    result.sum = a ^ b;

    // Carry-out is a AND b.
    result.cout = a & b;
    
    return result;
}

// Shows how a full adder works...
AdderResult bitwise_fullAdder(uint8_t a, uint8_t b, uint8_t cin) {
    AdderResult result;

    // Sum is a XOR b XOR c (odd number of variables can be 1, meaning only one or all of them can be 1).
    result.sum = a ^ b ^ cin;

    // Carry-out is 1 when any two variables are 1.
    result.cout = (a & b) | (a & cin) | (b & cin);

    return result;
}