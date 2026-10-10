/*
  Name and Email: Chase Audrey Sanders, csand118@ucr.edu
  Discussion Section: 024
  Assignment Lab # Exercise #: 2, 2
  Exercise Description: Using buttons to produce LED output in binary addition or subtraction from 0-15. Going past 15 reverts to 0 and
  vice versa. Holding down buttons shifts leds more than once. reset button sets leds to 0.

  I acknowledge all content contained herein, excluding template or example code, is my own original work.

  Demo Link: https://youtu.be/ABxZ6oeafz4 
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

enum btn_States {SMStart, Start, End, Left, Right, Stasis, Reset} btn_State; //TODO: finish the enum for the SM


void Tick() {
  // Declare any static variables here

  // State Transistions
  //TODO: complete transitions 
  switch(btn_State) {
      case SMStart:
        btn_State = Start;
        break;
      case Start:
        if(PINC & 0x01){
          btn_State = Left;
          _delay_ms(500);
        } 
        else if((PINC >> 1) & 0x01){
          btn_State = End;
          _delay_ms(500);
        } 
        else if((PINC >> 2) & 0x01){
          btn_State = Reset;
          _delay_ms(500);
        } 
        else btn_State = Start;
        break;
      case End:
        if(PINC & 0x01){
          btn_State = Start;
          _delay_ms(500);
        }
        else if((PINC >> 1) & 0x01){
          btn_State = Right;
          _delay_ms(500);
        } 
        else if((PINC >> 2) & 0x01){
           btn_State = Reset;
           _delay_ms(500);
        }
        else btn_State = End;
        break;
      case Left:
        if(PINC & 0x01){
          if(PORTD == 0x38){
            btn_State = End;
            _delay_ms(500);
          }
          else if(PORTD == 0x3C){
            btn_State = Start;
            _delay_ms(500);
          }
          else{ 
            btn_State = Left;
            _delay_ms(500);
          }
        }
        else btn_State = Stasis;
        break;
      case Right:
        if((PINC >> 1) & 0x01){
          if(PORTD == 0x04){
            btn_State = Start;
            _delay_ms(500);
          }
          else if(PORTD == 0x00){
            btn_State = End;
            _delay_ms(500);
          }
          else {
            btn_State = Right;
            _delay_ms(500);
          }
        }
        else btn_State = Stasis;
        break;
      case Stasis:
        if(PINC & 0x01){
          if(PORTD == 0x38){
           btn_State = End;
          _delay_ms(500);
          }
          else if(PORTD == 0x3C){
            btn_State = Start;
            _delay_ms(500);
          }
          else{
            btn_State = Left;
            _delay_ms(500);
          }
        }
        else if((PINC >> 1) & 0x01){
          if(PORTD == 0x04){
            btn_State = Start;
            _delay_ms(500);
          }
          else if(PORTD == 0x00){
            btn_State = End;
            _delay_ms(500);
          }
          else {
            btn_State = Right;
            _delay_ms(500);
          }
        }
        else if((PINC >> 2) & 0x01){
          btn_State = Reset;
        }
        else btn_State = Stasis;
        break;
      case Reset:
        while((PINC >> 2) & 0x01){}
        btn_State = Start;
        break;
      default:
        break;
  }

  // State Actions
  //TODO: complete transitions
  switch(btn_State) {
      case Start:
        PORTD = 0x00;
    	PORTC = 0x07;
        break;
      case End:
        PORTD = 0x3C;
        break;
      case Left:
        PORTD = PORTD + (1 << 2);
        break;
      case Right:
        PORTD = PORTD - (1 << 2);
        break;
      case Stasis:
        PORTD = PORTD;
        break;
      case Reset:
        PORTD = PORTD & 0x00;
        PORTC = 0x17;
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
  PORTD = 0x00;

  //TODO: initialize your state
  btn_State = SMStart;
  
  while (1) {
    Tick();
  }
}