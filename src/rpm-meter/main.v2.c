unsigned long rpm = 0, ccpovfcnt = 0, valontmr1ovf = 0, tmr1ovfcntzero = 0;
char map[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
char dig[4], i;

void interrupt()
{
  if(CCP1IF_bit)
  {
    ccpovfcnt++;
    CCP1IF_bit = 0;
  }
  
  if(TMR1IF_bit)
  {
    if((valontmr1ovf = ccpovfcnt) == 0)
    {
      tmr1ovfcntzero++;
    }

    ccpovfcnt = 0;
    TMR1IF_bit = 0;
  }
}

void main() {
  ANSEL = 0x00;
  ANSELH = 0x00;
  TRISA = 0x00;
  PORTA = 0x00;
  
  TRISB = 0x00;
  PORTB = 0x00;

  CCP1CON = 0x06; // Capture mode, every 4th rising edge
  
  TRISC2_bit = 1;
  CCP1IF_bit = 0;
  CCP1IE_bit = 1;

  TMR1CS_bit = 0; // The clock source is FOSC/4.
  T1SYNC_bit = 1; // Don't synchronize
  
  T1CKPS1_bit = 1;
  T1CKPS0_bit = 1; // 1:8

  TMR1IE_bit = 1;
  TMR1IF_bit = 0;
  PEIE_bit = 1;
  TMR1ON_bit = 1;
  
  TMR1L = 0x00;
  TMR1H = 0x00;
  
  GIE_bit = 1;
  
  while(1)
  {
    if(tmr1ovfcntzero > 1)
    {
      rpm = 0;
      tmr1ovfcntzero = 0;
    }

    if(valontmr1ovf > 0)
    {
      rpm = 114 * valontmr1ovf;
      valontmr1ovf = 0;
    }
    
    dig[0] = rpm / 1000;
    dig[1] = (rpm / 100) % 10;
    dig[2] = (rpm / 10) % 10;
    dig[3] = rpm % 10;

    PORTB = 0x01;

    for(i = 0; i < 4; i++)
    {
      PORTA = map[ dig[i] ];
      Delay_us(150);
      PORTA = 0x00;
      PORTB <<= 1;
    }
  }
}