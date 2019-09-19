/*
 * LCD0.c
 *
 * Created: 2019-03-12 10:47:41 PM
 * Author : user
 */ 
#include "LCD.h"
#define F_CPU 8000000UL
#include <avr/interrupt.h>
#define BUZZER_PORT     PB7     // Buzzer pin Port
#define BUZZER_DELAY    200     // Delay for each tick

void ToneBuzzer()
{
	int delay = 0;
	while (1)
	{
		if (delay < 1) delay = BUZZER_DELAY;
		PORTB |= (1 << BUZZER_PORT);
		_delay_loop_2(delay);
		PORTB &= ~(1 << BUZZER_PORT);
		_delay_loop_2(delay);
		delay--;
	}
}

int keypressed(void)                      //Function for receiving input form keypad
{
	int row,col,keynum;
	while(1)
	{
		for(col=0;col<4;col++)
		{
			DDRA=(0b00010000<<col);
			PORTA=(~(0b00010000<<col));
			for(row=0;row<4;row++)
			{
				if(!(PINA&(1<<row)))
				{
					keynum=4*row+col+1;
					return keynum;
				}
			}
		}
	}
}

int TimeR=0;           //global variable as factor of time
int i;                 //Questions&Answers Counter
int j;                //7 Segment Counter
void Time_Initial()        //initializing time function
{
	TimeR=0;
	TCCR1B|=(1<<CS12);     //prescalar 256
	TCNT1=34285;          //real time calculation for 7.5 seconds
	TIMSK|=(1<<TOIE1);   //interrupt flag
	sei();              //interrupt function
}

ISR(TIMER1_OVF_vect)
{
	TimeR++;
	if(TimeR==12)   //time reaches 7.5*12= 90 seconds =1.5 minute
	{
        CursorPos(0,0);                     
        SendString("TimeOut,Score Is");
        CursorPos(1,0);                      
        SendString("On 7 Segment____");
		_delay_ms(5000);
		
		if(j-1>=5) 
		    {
			ClrScr(); 
			CursorPos(0,0); SendString("Congratulations");       
			CursorPos(1,0); SendString("You Succeeded");
			}
       else {
			ClrScr(); 
			CursorPos(0,0); SendString("Hard lock :' ");
			CursorPos(1,0); SendString("You Failed");
			}
		_delay_ms(20000);
		TCNT1=34285;  //reset timer
		TimeR=0;      //reset factor
	}
	else TCNT1=34285;  //restart next 7.5 seconds in timer
}

 void Rot_0_Deg()
 {
	 for(int c=0;c<20;c++)
	 {
		 PORTB|=(1<<7);
		 _delay_us(1000);
		 PORTB&=~(1<<7);
		 _delay_us(19000);
	 }
 }
 void Rot_1_Deg()
 {
	 	 for(int c=0;c<20;c++)
	 {
		 PORTB|=(1<<7);
		 _delay_us(1000+111);
		 PORTB&=~(1<<7);
		 _delay_us(19000-111);
	 }
 }

 void Rot_2_Deg()
 {
	 for(int c=0;c<20;c++)
	 {
		 PORTB|=(1<<7);
		 _delay_us(1000+2*111);
		 PORTB&=~(1<<7);
		 _delay_us(19000-2*111);
	 }
 }
 void Rot_3_Deg()
 {
	 for(int c=0;c<20;c++)

	 {
		 PORTB|=(1<<7);
		 _delay_us(1000+3*111);
		 PORTB&=~(1<<7);
		 _delay_us(19000-3*111);
	 }
 }
 void Rot_4_Deg()
 {
	 for(int c=0;c<20;c++)

	 {
		 PORTB|=(1<<7);
		 _delay_us(1000+4*111);
		 PORTB&=~(1<<7);
		 _delay_us(19000-4*111);
	 }
 }
 void Rot_5_Deg()
 {
	 for(int c=0;c<20;c++)

	 {
		 PORTB|=(1<<7);
		 _delay_us(1000+5*111);
		 PORTB&=~(1<<7);
		 _delay_us(19000-5*111);
	 }
 }
 void Rot_6_Deg()
 {
	 for(int c=0;c<20;c++)

	 {
		 PORTB|=(1<<7);
		 _delay_us(1000+6*111);
		 PORTB&=~(1<<7);
		 _delay_us(19000-6*111);
	 }
 }

 void Rot_7_Deg()
 {
	 for(int c=0;c<20;c++)

	 {
		 PORTB|=(1<<7);
		 _delay_us(1000+7*111);
		 PORTB&=~(1<<7);
		 _delay_us(19000-7*111);
	 }
 }

 void Rot_8_Deg()
 {
	 for(int c=0;c<20;c++)
	 {
		 PORTB|=(1<<7);
		 _delay_us(1000+8*111);
		 PORTB&=~(1<<7);
		 _delay_us(19000-8*111);
	 }
 }

 void Rot_9_Deg()
 {
	 for(int c=0;c<20;c++)
	 {
		 PORTB|=(1<<7);
		 _delay_us(1000+9*111);
		 PORTB&=~(1<<7);
		 _delay_us(19000-9*111);
	 }
 }

int main(void)
{
InitLCD();
DDRB=0xFF;                       //make B as output (for leds & Buzzer&motor)
char *Question[9];              //array of pointers which contains 9 questions
Question[0]="Q1_  4x+1=45";
Question[1]="Q2_  7x-6=3x+2";
Question[2]="Q3_  x^3-1=26 ";
Question[3]="Q4_  x^2-2x+1=0";
Question[4]="Q5_  x=9i*7i ";
Question[5]="Q6_  Log(x)=2 ";
Question[6]="Q7_  1,4,9,x,25";
Question[7]="Q8_  2,4,x,16,32";
Question[8]="Q9_  1,3,6,x,15";

char *Ans[9];        //array of pointers which contains choises for each question
Ans[0]="9  10  11  13";
Ans[1]="1   2   3   4";
Ans[2]="1   2   3   5";
Ans[3]="1   2   3   4";
Ans[4]="-72 -63 -54 -81";
Ans[5]="1 10 100 1000";
Ans[6]="10  12  16  20";
Ans[7]="5  8  10  12";
Ans[8]="8  10  12  14";

int right[9]={9,6,9,5,6,9,9,6,6};  //array of integers which contains right answers in keypad (right pressed number)
int Segment[10] = {0xDF,0x86,0xBB,0xAF,0xE6,0xED,0xFD,0x87,0xFF,0xEF};


while(1)
{
j=1;                                //counter of right answers
Rot_0_Deg();                       //initially rotate motor 0 degree
PORTB=~Segment[0];                //start 7 Segment by 0
CursorPos(0,0);                      //printing message in column 1,row 1
SendString("Welcome to Exam");      
CursorPos(1,0);                      //printing message in column 1,row 2
SendString("Get Ready ;) ");
_delay_ms(5000);
ClrScr();                           //clear screen for another message

CursorPos(0,0);                    //printing message in column 1,row 1
SendString("Find Value of X");
CursorPos(1,0);                   //printing message in column 1,row 2
SendString("Time is 1.5min");
_delay_ms(5000);

ClrScr();                       //lines form 74 to 79 is to handle some error which happens sometimes
CursorPos(0,0);                 //error is initial value of x "KeyPressed" may be garbage
SendString("If You're Ready");  //so it effects the first answer,so we take first keypressed as welcome message
CursorPos(1,0);                //so what ever it's , it won't effect answers
SendString("Press to start");
int x=keypressed();                //variable receives keypressed        

Time_Initial();               //Start Counting from first Question
for(i=0;i<9;i++)
{
	
ClrScr();                          //clear screen for next question
CursorPos(0,0);                   //printing message in column 1,row 1
SendString(Question[i]);         //printing Q
CursorPos(1,0);                 //printing message in column 1,row 2
SendString(Ans[i]);            //printing Ans. of Question
x=keypressed();
    if(x==right[i]) 
    {
		ClrScr();                           //clear screen for another message
		CursorPos(0,0);                    //printing message in column 1,row 1
		SendString("right answer");
		_delay_ms(200);
		
        PORTB=~Segment[j]; 
     
	        if(j==1) Rot_1_Deg();
       else if(j==2) Rot_2_Deg();
       else if(j==3) Rot_3_Deg();
       else if(j==4) Rot_4_Deg();
       else if(j==5) Rot_5_Deg();
       else if(j==6) Rot_6_Deg();
       else if(j==7) Rot_7_Deg();
       else if(j==8) Rot_8_Deg();
       else if(j==9) Rot_9_Deg();

j++;
	}//check if the right key is pressed -->> increase 7segment & rotate 20 degree
	
	else 
	{
			ClrScr();                           //clear screen for another message
			CursorPos(0,0);                    //printing message in column 1,row 1
			SendString("wrong answer");
	PORTC|=(1<<7); _delay_ms(500); PORTC&=~(1<<7); 
	}     //if answer is wrong>>turn on red led

}
 	if(j-1==9)
	 {
	 		ClrScr();
	 		CursorPos(0,0); SendString("Congratulations");
	 		CursorPos(1,0); SendString("Full Mark ;) ");		 
	 }
	 	else 
		 {
			 
		 if(j-1>=5)
 		{
	 		ClrScr();
	 		CursorPos(0,0); SendString("Congratulations");
	 		CursorPos(1,0); SendString("You Succeeded");
 		}
 		else {
	 		ClrScr();
	 		CursorPos(0,0); SendString("Hard lock :' ");
	 		CursorPos(1,0); SendString("You Failed");
 	       	}
		 }
 		_delay_ms(20000);
 }
}