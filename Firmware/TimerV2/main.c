/*
TimerV2
(c) Created by candrian on 4/26/12.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "main.h"

//Time struct
volatile typedef struct{
	volatile uint8_t second; 
	volatile uint8_t minute;
	volatile uint8_t hour;
}time;
time t;

const uint8_t digittable[] PROGMEM = {
	DIG_0, DIG_1, DIG_2, DIG_3, DIG_4, DIG_5, DIG_6, DIG_7, DIG_8, DIG_9};
PGM_P digittable_p PROGMEM = digittable;


volatile uint8_t to_display_0=0;
volatile uint8_t to_display_1=0;
uint8_t currdigit=0;                // which digit we are currently multiplexing
uint8_t timer_on=0;
ISR (TIMER2_OVF_vect){
    t.second++;
    //Minute passed
	if (t.second>=60) {
		t.second=0;
		t.minute++;
	}
	
	//Hour passed
	if (t.minute>=60) {
		t.minute=0;
		t.hour++;
	}
    if (timer_on==1) {
        if (t.minute==0) {
            to_display_0 =  t.second / 10;
            to_display_1 =  t.second % 10;
        }else{
            to_display_0 =  t.minute / 10;
            to_display_1 =  t.minute % 10; 
        }    
    }

}

//Timer1 overflow ISR 
//Update Display 
ISR (TIMER1_OVF_vect) {

	sei();
    
    if (currdigit==0) {
            clear_display();
            //Turn DISP2 OFF
            PORT_DISP2  &=  ~(1<<DISP2);
            //Turn DISP1 ON
            PORT_DISP1  |=  (1<<DISP1);

            if (to_display_0==0) {
                PORT_A  |=  (1<<A);
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
                PORT_D  |=  (1<<D);
                PORT_E  |=  (1<<E);
                PORT_F  |=  (1<<F);
            } 
            if (to_display_0==1) {
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
            } 
            if (to_display_0==2) {
                PORT_A  |=  (1<<A);
                PORT_B  |=  (1<<B);
                PORT_D  |=  (1<<D);
                PORT_E  |=  (1<<E);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_0==3) {
                PORT_A  |=  (1<<A);
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
                PORT_D  |=  (1<<D);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_0==4) {
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
                PORT_F  |=  (1<<F);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_0==5) {
                PORT_A  |=  (1<<A);
                PORT_C  |=  (1<<C);
                PORT_D  |=  (1<<D);
                PORT_F  |=  (1<<F);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_0==6) {
                PORT_C  |=  (1<<C);
                PORT_D  |=  (1<<D);
                PORT_E  |=  (1<<E);
                PORT_F  |=  (1<<F);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_0==7) {
                PORT_A  |=  (1<<A);
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
            } 
            if (to_display_0==8) {
                PORT_A  |=  (1<<A);
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
                PORT_D  |=  (1<<D);
                PORT_E  |=  (1<<E);
                PORT_F  |=  (1<<F);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_0==9) {
                PORT_A  |=  (1<<A);
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
                PORT_F  |=  (1<<F);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_0==0xFF) {
                clear_display();
            }
            
        }else if(currdigit==1){
            clear_display();
            //Turn DISP1 OFF
            PORT_DISP1  &=  ~(1<<DISP1);
            //Turn DISP2 ON
            PORT_DISP2  |=  (1<<DISP2);
            
            if (to_display_1==0) {
                PORT_A  |=  (1<<A);
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
                PORT_D  |=  (1<<D);
                PORT_E  |=  (1<<E);
                PORT_F  |=  (1<<F);
            } 
            if (to_display_1==1) {
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
            } 
            if (to_display_1==2) {
                PORT_A  |=  (1<<A);
                PORT_B  |=  (1<<B);
                PORT_D  |=  (1<<D);
                PORT_E  |=  (1<<E);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_1==3) {
                PORT_A  |=  (1<<A);
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
                PORT_D  |=  (1<<D);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_1==4) {
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
                PORT_F  |=  (1<<F);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_1==5) {
                PORT_A  |=  (1<<A);
                PORT_C  |=  (1<<C);
                PORT_D  |=  (1<<D);
                PORT_F  |=  (1<<F);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_1==6) {
                PORT_C  |=  (1<<C);
                PORT_D  |=  (1<<D);
                PORT_E  |=  (1<<E);
                PORT_F  |=  (1<<F);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_1==7) {
                PORT_A  |=  (1<<A);
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
            } 
            if (to_display_1==8) {
                PORT_A  |=  (1<<A);
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
                PORT_D  |=  (1<<D);
                PORT_E  |=  (1<<E);
                PORT_F  |=  (1<<F);
                PORT_G  |=  (1<<G);
            } 
            if (to_display_1==9) {
                PORT_A  |=  (1<<A);
                PORT_B  |=  (1<<B);
                PORT_C  |=  (1<<C);
                PORT_F  |=  (1<<F);
                PORT_G  |=  (1<<G);
            }
            if (to_display_1==0xFF) {
                clear_display();
            }

        }
    
    currdigit++;
    if (currdigit>1) {
        currdigit=0;
    }
    
}

void beep(uint8_t delay){
    PORT_BUZZER |=  (1<<BUZZER);
    _delay_ms(delay);
    PORT_BUZZER &=  ~(1<<BUZZER);
}
void clear_time(){
    t.second=0;
    t.minute=0;
    t.hour=0;
    to_display_0=0;
    to_display_1=0;
}
void clear_display(){
    //SEGMETS OFF
    PORT_A      &=  ~(1<<A);
    PORT_B      &=  ~(1<<B);
    PORT_C      &=  ~(1<<C);
    PORT_D      &=  ~(1<<D);
    PORT_E      &=  ~(1<<E);
    PORT_F      &=  ~(1<<F);
    PORT_G      &=  ~(1<<G); 
}

void initialize(){
    // Turn on the RTC by selecting the external 32khz crystal
	// 32.768 / 128 = 256 which is exactly an 8-bit timer overflow
	ASSR |= (1<<AS2);   //Timer/Counter 2 clocked from a crystal to the Timer Oscillator 1 (TOSC1) pin
	TCCR2 = (1<<CS22) | (1<<CS20); //clkT2S/128 (From prescaler)
    
    //Enable Timer/Counter2 & Timer/Counter1 Overflow interrupt    
    TIMSK   |=  (1<<TOIE2);
    TIMSK   |=  (1<<TOIE1);
    TCCR1B  |=  (1<<CS10);         //clkI/O/1 (No prescaling)
    
    //RELAY output
    DDR_RELAY   |=  (1<<RELAY);
    //BUZZER output
    DDR_BUZZER  |=  (1<<BUZZER);
    //SW1 input
    DDR_SW1     &=  ~(1<<SW1);
    //Enable Pull up
    PORT_SW1    |=  (1<<SW1);
    //SW2 input
    DDR_SW2     &=  ~(1<<SW2);
    //Enable Pull up
    PORT_SW2    |=  (1<<SW2);
    //DISP1 output
    DDR_DISP1   |=  (1<<DISP1);
    //DISP2 output
    DDR_DISP2   |=  (1<<DISP2);
    //SEGMENTS output
    DDR_A       |=  (1<<A);
    DDR_B       |=  (1<<B);
    DDR_C       |=  (1<<C);
    DDR_D       |=  (1<<D);
    DDR_E       |=  (1<<E);
    DDR_F       |=  (1<<F);
    DDR_G       |=  (1<<G);

    //RELAY OFF
    PORT_RELAY  &=  ~(1<<RELAY);
    //BUZZER OFF
    PORT_BUZZER &=  ~(1<<BUZZER);
    //DISP1 OFF
    PORT_DISP1  &=  ~(1<<DISP1);
    //DISP2 OFF
    PORT_DISP2  &=  ~(1<<DISP2);
    clear_display();
    
}

int main(void){
    volatile uint8_t limit=10;
    uint32_t counter=0;
    uint8_t flag=0;
    initialize();

    limit=eeprom_read_byte((uint8_t *)EE_LIMIT);
    
    sei();
    
    //limit=eeprom_read_byte((uint8_t *)EE_LIMIT);
    //eeprom_write_byte((uint8_t *)EE_LIMIT, limit);
    
    while (1) {

        if (timer_on==0) {
            clear_time();
        }else{
            //Turn reached limit turn relay off
            if (t.minute==limit) {
                timer_on=0;
                PORT_RELAY  &=  ~(1<<RELAY);
                to_display_0=0;
                to_display_1=0;
                beep(1000);
                beep(1000);
                _delay_ms(500);
                beep(1000);
                beep(1000);
                _delay_ms(500);
                beep(1000);
                beep(1000);
            }
        }
        //Start Timer
        if (((PIN_SW1 & (1<<SW1))==0) && timer_on==0) {
            _delay_ms(20);
            beep(100);
            to_display_0= limit / 10;
            to_display_1= limit % 10;
            _delay_ms(1000);
            timer_on=1;
            clear_time();
            PORT_RELAY  |=  (1<<RELAY);
        }
        //Stop Timer
        if (((PIN_SW2 & (1<<SW2))==0) && timer_on==1) {
            _delay_ms(20);
            //Wait for button release
            while ((PIN_SW2 & (1<<SW2))==0);              
            timer_on=0;
            clear_time();
            beep(100);
            PORT_RELAY  &=  ~(1<<RELAY);
        }
        //Configure timer
        if (((PIN_SW2 & (1<<SW2))==0) && timer_on==0) {
            _delay_ms(20);
            beep(100);
            while (1) {
                
                if (((PIN_SW1 & (1<<SW1))==0)) {
                    _delay_ms(20);
                    beep(100);
                    if (limit>0) {
                        limit--;
                    }
                }
                if (((PIN_SW2 & (1<<SW2))==0)) {
                    _delay_ms(20);
                    beep(100);
                    while ((PIN_SW2 & (1<<SW2))==0) {
                        counter++;
                        _delay_ms(1);
                        if (counter==1000UL) {
                            beep(100);
                        }
                    }
                    if (counter>1000UL) {
                        counter=0;
                        goto    LABEL1;
                    }else{
                        counter=0;   
                        if (limit<99) {
                            limit++;
                        }
                    }
                }
                if (flag==0) {
                    to_display_0=0xFF;
                    to_display_1=0xFF;
                    flag=1;
                }else{
                    to_display_0= limit / 10;
                    to_display_1= limit % 10;                    
                    flag=0;
                }
                _delay_ms(100);
            }
LABEL1:           
            eeprom_write_byte((uint8_t *)EE_LIMIT, limit);
        }
    }


    return 0;
}
