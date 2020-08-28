#include <16F877A.h>
#use delay(clock = 20M)
//SRF05
sbit SRF05_Trigger        at RD0_bit;
sbit SRF05_Echo           at RD1_bit;

sbit SRF05_Trigger_Direction         at TRISD0_bit;
sbit SRF05_Echo_Direction            at TRISD1_bit;

unsigned     int time = 0;
unsigned char distance = 0;
unsigned int chuc = 0;
unsigned int donvi = 0;
//tao ma hex cho doan code
const unsigned int8 ma7doan[] = { 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90 };
unsigned int8 led0, led1;
void sf{

     ADCON1 |= 0x07;      // Khong dung ADC

     // Khoi tao ket noi voi SRF05
     SRF05_Trigger_Direction = 0;    // Chan Trigger la ngo ra
     SRF05 - Trigger = 0;

     SRF05_Echo_Direction = 1;    // Chan Echo la ngo vao

     // Khoi tao timer1
     T1CON.TMR1CS = 0;     // Dem xung noi
     T1CON.T1CKPS1 = 0;    // Ti le bo chia truoc la 1:2
     T1CON.T1CKPS0 = 1;

     while (1)
     {
         // Tao xung Trigger
         SRF05_Trigger = 1;
         delay - ms(15);
         SRF05_Trigger = 0;

         while (SRF05_Echo == 0);
         T1CON.TMR1ON = 1;     //Timer1 bat dau dem
         while (SRF05_Echo == 1);
         T1CON.TMRON = 0;        //Dung Timer1;

         // Tinh khoang cach
         time = TMR1H;
         time <<= 8;
         time += TMR1L;

         if (time > 60 && time < 5700)
         {
            distance = time / 58;
         }
            chuc = distance / 10;
            donvi = distance - chuc * 10;
   }
}
void giaima()
{
    led0 = ma7doan[chuc];
    led1 = ma7doan[donvi];
}
void hienthi()
{
    output_b(led0);     output_low(pin_a4);   delay_ms(1);  output_high(pin_a4);
    output_b(led2);     output_low(pin_a5);   delay_ms(1);  output_high(pin_a5);
}
void main()
{
    set_trist_a(0x00);
    set_trist_b(0x00);

    while (true)
    {
        giaima();
        hienthi();
    }
}
