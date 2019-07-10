unsigned pot;
char duty, leds, i;

void main()
{
  CMCON0 = 0x07;
  ANSEL = 0x01;
  TRISIO = 0x01;
  GPIO = 0x01;
  
  ADC_Init();
  
  PWM1_Init(5000);
  PWM1_Set_Duty(0);
  PWM1_Start();

  while(1)
  {
    pot = ADC_Read(0);
    duty = pot < 32 ? 0 : (pot > 1023-32 ? 255 : pot * (255 / 1023f));
    PWM1_Set_Duty(duty);
   
    leds = duty * (8 / 255f);
    
    GP5_bit = 0;
    for(i = 0; i < 8; i++)
    {
      GP1_bit = 0;
      GP4_bit = leds > i;
      GP1_bit = 1;
    }
    GP5_bit = 1;
  }
}