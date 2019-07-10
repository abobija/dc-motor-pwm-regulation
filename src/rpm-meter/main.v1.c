unsigned rpm = 0;
unsigned ovfcnt = 0;
char dig[4], i;
char map[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

void interrupt()
{
  if(CCP1IF_bit)
  {
    rpm = 60 * (1e6 / (ovfcnt * 0xFFFF + (CCPR1H << 8 | CCPR1L)));
    
    ovfcnt = 0x0000;
    TMR1L = 0x00;
    TMR1H = 0x00;
    TMR1IF_bit = 0;
    CCP1IF_bit = 0;
  }
  
  if(TMR1IF_bit)
  {
    ovfcnt++;
    TMR1IF_bit = 0;
  }
}

void main() {
  IRCF0_bit = 1;
  
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
  
  T1CKPS1_bit = 0;
  T1CKPS0_bit = 1;

  TMR1IE_bit = 1;
  TMR1IF_bit = 0;
  PEIE_bit = 1;
  TMR1ON_bit = 1;
  
  TMR1L = 0x00;
  TMR1H = 0x00;
  
  GIE_bit = 1;
  
  while(1)
  {
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