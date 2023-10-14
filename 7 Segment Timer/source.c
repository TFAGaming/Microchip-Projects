sbit BStart at RA0_bit;
sbit BStop at RA1_bit;

unsigned int toggle = 0;
unsigned int current = 0;

void main() {
     TRISA = 0b00011;
     TRISB = 0b00000000;
     
     PORTB = 0b11000000;
     
     while (1) {
           if (BStart == 1) {
              toggle = 1; // Set the timer to enabled
              PORTB = 0b01000000;
           };
           
           if (BStop == 1) {
              toggle = 0; // Set the timer to disabled
              current = 0; // Reset the timer to 0
              PORTB = 0b11000000;
           };

           if (toggle == 1) {
              if (current > 9) current = 0;

              switch (current) {
                     case 0: {
                          PORTB = 0b00111111;
                          break;
                     }
                     case 1: {
                          PORTB = 0b00000110;
                          break;
                     }
                     case 2: {
                          PORTB = 0b01011011;
                          break;
                     }
                     case 3: {
                          PORTB = 0b01001111;
                          break;
                     }
                     case 4: {
                          PORTB = 0b01100110;
                          break;
                     }
                     case 5: {
                          PORTB = 0b01101101;
                          break;
                     }
                     case 6: {
                          PORTB = 0b01111101;
                          break;
                     }
                     case 7: {
                          PORTB = 0b00000111;
                          break;
                     }
                     case 8: {
                          PORTB = 0b01111111;
                          break;
                     }
                     case 9: {
                          PORTB = 0b01101111;
                          break;
                     }
                     default: {
                          PORTB = 0b01000000;
                     }
              }

              delay_ms(1000);

              current++;
           }
     }
}
