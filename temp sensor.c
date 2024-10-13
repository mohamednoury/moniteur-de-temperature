/* Written By Engr Brandon NM
   Temperature monitoring with the PIC16F877A MCU
*/
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;
//
sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;
//
float temperature;
float Displaytemp;
char temp[4];
//
void main(){
  TRISB=0X00;            //all PORTB as output
  TRISA=0x0F;            //PORTA0 as input
  TRISC=0X00;             // PORTC as output
  //
  Lcd_Init();          //initialise the LCD
  ADC_Init();         //initialise ADC
  //
  Lcd_Cmd(_LCD_CLEAR);   //clear the LCD
  Lcd_Cmd(_LCD_CURSOR_OFF);   //cursor off
  //
  Lcd_Out(1,1,"temperature");        //3
  Lcd_Out(2,1,"sensor");                //4
           //1
  delay_ms(1000);
  //
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
  //
  while(1){
    temperature=ADC_Read(RA0);
    floattostr(Displaytemp,temp);
    Lcd_Out(1,2,"temperature=");

    Displaytemp=(temperature*50*10)/1023;
    Lcd_Out(2,12,Ltrim(temp));
    //
    Lcd_Out(2,16,"C");
    delay_ms(500);
    if(Displaytemp<22){
      PORTC.F0=1;       //HEATER ON
      PORTC.F1=0;       //FAN OFF
      Lcd_Out(3,-3,"HEATER ON");
      Lcd_Out(3,-3,"FAN OFF");
    }
    if(Displaytemp>22 && Displaytemp<25){
      PORTC.F0=0;       //HEATER OFF
      PORTC.F1=0;       //FAN OFF
      Lcd_Out(3,-3,"HEATER OFF");
      Lcd_Out(3,-3,"FAN OFF");
    }
    if(Displaytemp>25){
      PORTC.F0=0;       //HEATER OFF
      PORTC.F1=1;       //FAN ON
      Lcd_Out(3,-3,"HEATER OFF");
      Lcd_Out(3,-3,"FAN ON");
    }
  }
}