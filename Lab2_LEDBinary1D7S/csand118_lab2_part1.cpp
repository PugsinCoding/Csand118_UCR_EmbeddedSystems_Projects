/*
  Name and Email: Chase Audrey Sanders, csand118@ucr.edu
  Discussion Section: 024
  Assignment Lab # Exercise #: 2, 1
  Exercise Description: Using buttons to shift led light output either left or right. Holding down the button shifts only once.

   I acknowledge all content contained herein, excluding template or example code, is my own original work.

   Demo Link: https://youtu.be/ByYj3Uwc9cY 
*/

#include <avr/io.h>
#include <util/delay.h>

/*unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
   return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
              //   Set bit to 1           Set bit to 0
}

unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

// TODO: complete nums
// the index is also the digit it represents
// eg: nums[0]="0", nums[9]="9", nums[15]="f"
// bits layout:   gfedcba   (REVERSE ORDER!)
int nums[16] = {0b0111111, // 0
                0b0000110, // 1
                0b1011011, // 2
                0b1001111, // 3 
                0b1100110, // 4
                0b1101101, // 5
                0b1111101, // 6
                0b0000111, // 7
                0b1111111, // 8
                0b1100111, // 9
                0b1110111, // a
                0b1111100, // b
                0b0111001, // c 
                0b1011110, // d
                0b1111001, // e
                0b1110001  // f 
                }; 

//TODO: complete outNum()
void outNum(int num){
	PORTB = 0xFF; // depends on your wiring. Assign bits (e-a), which are bits (4-0) from nums[] to register PORTB
  PORTD = 0x01; // Assign bits (g & f) which are bits 6 & 5 of nums[] to register PORTD
} */

enum btn_States {SMStart, Start, Left, Right, Stasis} btn_State;


void Tick() {
  
  switch(btn_State) {
      case SMStart:
        btn_State = Start;
        break;
      case Start:
        if((PINC & 0x01)){
          btn_State = Left;
        }
        else{
          btn_State = Start;
        }
        break;
      case Left:
        while(PINC & 0x01){}
        btn_State = Stasis;
        break;
      case Right:
        while((PINC >> 1) & 0x01){}
        btn_State = Stasis;
        break;
      case Stasis:
        if(PINC & 0x01 && !((PINC >> 1) & 0x01) && !((PIND >> 5) & 0x01)){
          btn_State = Left;
        }
        else if((PINC >> 1) & 0x01 && !(PINC & 0x01)){
          if((PIND >> 2) & 0x01){
            btn_State = Start;
          }
          else btn_State = Right;
        }
        else {
          btn_State = Stasis;
        }
        break;
      default:
        break;
  }

  switch(btn_State) {
      case Start:
        PORTD = 0x04;
        break;
      case Left:
        PORTD = PORTD << 1;
        break;
      case Right:
        PORTD = PORTD >> 1;
        break;
      case Stasis:
        break;
      default:
        break;
  }

}

int main(void)
{
  //TODO: initialize all outputs and inputs
  DDRB = 0xFF;
  PORTB = 0x00;
  
  DDRC = 0xF8; //11111000 
  PORTC = 0x07;

  DDRD = 0xFF;
  PORTD = 0x04;

  //TODO: initialize your state
  btn_State = SMStart;
  
  while (1) {
    Tick();
  }
}