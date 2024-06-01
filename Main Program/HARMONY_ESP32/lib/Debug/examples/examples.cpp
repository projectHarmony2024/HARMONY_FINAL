#include <Arduino.h>

/*  INCLUDE THE HEADER
 *  remove the `src/` to use it on your program
 *  e.g. #include <DEBUG.h>
 */
#include <src/DEBUG.h>

/*  DEBUG MODE
*   Define DEBUG to enable debug mode
*   Do not define to disable debug mode

NOTE:
When DEBUG is not defined, the library becomes inactive, and debugf calls have no effect.
*/
#define DEBUG

void setup()
{
    /* INITIALIZE DEBUG
     * Change according to your preferred baudrate
     * I used 115200 baudrate for ESP32
     * Use 9600 for Arduino
     */
    debug_Init(115200);

    // Define variables of different data types
    int x = 123;
    unsigned int y = 255;
    char initial = 'A';
    float pi = 3.14159265; // Limited precision
    String message = "This is a String.";

    // Various specifiers supported on Arduino Framework
    debugf("Integer (decimal): %d\n", x);          // OUTPUT: Integer (decimal): 123
    debugf("Unsigned integer (decimal): %u\n", y); // OUTPUT: Unsigned integer (decimal): 255
    debugf("Hexadecimal (lowercase): %x\n", y);    // OUTPUT: Hexadecimal (lowercase): ff
    debugf("Hexadecimal (uppercase): %X\n", y);    // OUTPUT: Hexadecimal (uppercase): FF
    debugf("Octal: %o\n", y);                      // OUTPUT: Octal: 377
    debugf("Character: %c\n", initial);            // OUTPUT: Character: A
    debugf("Escape percent sign: %%\n");           // OUTPUT: Escape percent sign: %
    debugf("String literal: %s\n", message);       // OUTPUT: String literal: This is a string

    // Floating-point with limited precision (may vary on different boards)
    debugf("Floating-point (limited precision, 2 decimal places): %.2f\n", pi); // OUTPUT: Floating-point (limited precision): 3.14
    debugf("Floating-point (limited precision, 3 decimal places): %.3f\n", pi); // OUTPUT: Floating-point (limited precision): 3.142
    debugf("Floating-point (limited precision, 4 decimal places): %.4f\n", pi); // OUTPUT: Floating-point (limited precision): 3.1416

    // Unsupported specifiers (will not compile)
    // debugf("Pointer: %p\n", &x);  // Not supported
}
