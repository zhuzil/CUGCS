/* Main.c file generated by New Project wizard
 *
 * Created:   ��һ 3�� 14 2016
 * Processor: 8086
 * Compiler:  Digital Mars C
 *
 */
 
 /*
 * Before starting simulation set Internal Memory Size 
 * in the 8086 model properties to 0x10000
 */

#define OUT373  7000H

// Write a byte to the specified I/O port
void outp(unsigned int addr, unsigned char data) {
  __asm {
    mov dx, addr
    mov al, data
    out dx, al
  }
}
 
unsigned char tmp;

void main(void) {
  while (1) {
    // Write your code here
    tmp = 0b00000001;
    outp(OUT373, ~tmp);
  }
}
