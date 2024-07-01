#include       //Define PIC Registers
#include     //Define I/O Function
#define Buz   RB0     //RB0 interfaced to Buzzer
__CONFIG(0x3f72); //Select HS oscillator, Enable (PWRTE,BOREN),
  //Disable (CPD,CP,WDTEN,In-circuit Debugger)
#define FOSC   10000   //10Mhz==>10000Khz
#define BAUD_RATE 9.6 //9600 Baudrate
#define BAUD_VAL   ((char)(FOSC/ (16 * BAUD_RATE )) – 1)    
//Calculation For 9600 Baudrate @10Mhz
void Serial_init(void);//Serial Communication Initialization
void DelayMs(unsigned int);
void main()
{
unsigned char ReceivChar;
TRISB = 0x00;  
PORTB = 0x04;     //PORTB configured as O/P
Serial_init();        
printf("\033[2J");                
DelayMs(20);
printf("Press 1: Buzzer ON \n\r\t2: Buzzer OFF");
while(1)
{
while(RCIF==0); //Wait until the reception is over
RCIF=0;         //Clear the flag for next reception
ReceivChar=RCREG; //Store the received char to a variable
printf(" %c",ReceivChar);//Dislpay the character received
switch(ReceivChar)
{  
         case '1':   //If '1' is received Buzzer turned ON
         Buz=1;
         break;
 
         case '2':   //If '2' is received Buzzer turned OFF
         Buz=0;
break;
}
}
}
void Serial_init()
{
TRISC=0xc0;       //RC7,RC6 set to usart mode(INPUT)  
TXSTA=0x24;       //Enable (Serial Transmission,
                     //Asynchronous mode, High Speed mode)
SPBRG=BAUD_VAL;   //9600 baud at 10Mhz
RCSTA=0x90;       //Usart Enable, Continuous receive enable
TXIF=1;           //Start Transmit
}
void putch(unsigned char data)
{
while(TXIF==0);
TXREG=data;       //Transmit the data serially
}
void DelayMs(unsigned int Ms)
{
 int delay_cnst;
 while(Ms>0)
{
Ms--;
for(delay_cnst = 0;delay_cnst <220;delay_cnst++);
}
}
