#include <16f877a.h>
#device *=16
#device adc=10
#use delay(clock=4M)
#include <lcd.c>
 
float temperatura;
void main(){
   setup_adc_ports(RA0_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_COUNTERS(RTCC_internal.rtcc_div_1);
   set_adc_channel(0);
   lcd_init();
   lcd_gotoxy(1,1);
   delay_ms(350);
   while(true)
   {
      temperatura = (float)read_adc() *5 / 1024 * 100;
      lcd_gotoxy(3,1);
      printf(lcd_putc, "Temperatura:%d", (int)temperatura);
      lcd_putc(223);
      lcd_putc("C");
      delay_ms(200);
      if(temperatura < 20)
      {
         output_high(pin_a1);
         output_low(pin_a2);
         lcd_gotoxy(2,2);
         printf(lcd_putc,"Calefactor Activado");
         delay_ms(200);
      } else if(temperatura >= 20 && temperatura <= 25)
      { 
         output_low(pin_a1);
         output_low(pin_a2);
         lcd_gotoxy(2,2);
         printf(lcd_putc, "Temperatura Normal");
         delay_ms(200);
      }
      else
      {
         output_low(pin_a1);
         output_high(pin_a2);
         lcd_gotoxy(2,2);
         printf(lcd_putc, "Ventilador Activado");
         delay_ms(200);
      }
   }
}
