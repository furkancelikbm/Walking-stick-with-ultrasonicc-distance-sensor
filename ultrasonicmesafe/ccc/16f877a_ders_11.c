#include <16f877a_ders_11.h>
#use delay(clock=4Mhz)
#fuses XT,NOWDT
#include <lcd.c>
#define use_portb_lcd TRUE
#use fast_io(b)
float mesafe,zaman;
#define trig pin_c0
#define echo pin_c1

void main()    
{
lcd_init();

setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);  //Timer� �a��rd�k


   while(TRUE)
   {
      set_tris_b(0b00000000);
      output_b(0b00000010);
      output_high(trig);//bu mesafeyi �l�mek i�in trig pinine sinyal ��k��� olur 5v luk sinyal verdik
      delay_us(10); //mikrosaniye olarak belirledik 
      output_low(trig); //5v geri �ektik
      
      while(!input(echo)) //echo pin 'i bir hareketlilik olmas�n, echo �al��madan �nce while �al��s�n
      //ve echoya sinyal gelmeden �nce timer ile zaman� hesaplayaca��z
      {}
      set_timer1(0);
      
      while(input(echo)) //echo pininden sinyal gelene kadar bekle
      {}
      zaman=get_timer1(); 
      mesafe =(zaman/2)/(29.15);  //gidi� geli� old i�in 2 ,29.15 us/cm ses h�z�
      
      lcd_gotoxy(1,1);   //lcd ekran 16s�tun 2 sat�rdan olu�uyor, 1.sat�r ve 1.s�tununa git
      
      if(mesafe<200)
      {
      set_tris_b(0b00000000);
      output_b(0b00000001);
      delay_ms(200);
      output_b(0b00000010); //bunu deseydim R1 den ak�m gidecektir
      delay_ms(200);
      printf(lcd_putc,"\fDikkat! =%fcm", mesafe);
      delay_ms(500); // bekleme s�resi koyuyoruz ki hemen kaybolmas�n g�z�m�z g�rs�n
      }
      else
      {
      printf(lcd_putc,"\f mesafe=%fcm", mesafe);
      delay_ms(500); // bekleme s�resi koyuyoruz ki hemen kaybolmas�n g�z�m�z g�rs�n
      }  
   }
}
