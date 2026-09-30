#include <Arduino.h>
#include <avr/io.h>

 int main(void)
 {
   DDRB = 0x3C; 
   PORTB = 0x00; 
   // Turns all of port D into outputs with DDRD and sets each bit low with PORTD. Only bit 3 actually needed

   DDRD = 0x00; 
   PORTD = 0xFF; 
   // Turns all of port B into inputs. Only bit 2 actually needed

   while (1)
   {
     if(((PIND >> 7) & 0x01) && ((PORTB >> 2) != 0x0F)){
       PORTB = PORTB + (1 << 2);
       _delay_ms(500);
     }
     if(((PIND >> 6) & 0x01) && ((PORTB >> 2) != 0x00)){
     	PORTB = PORTB - (1 << 2);
       _delay_ms(500);
     }
     else{
     	PORTB = PORTB;
     }
   }
   return 0;
 }