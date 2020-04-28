//https://forum.arduino.cc/index.php?topic=597543.0
/* This code generates Quasi-Square Waves at 60Hz*/
static byte stateCount = 0;
volatile float CPRDV = 0;
static float inverterFrequency = 60;
int divA = 42;

void setup()
{
  PMC->PMC_PCER1 |= PMC_PCER1_PID36;                  // Enable PWM (Power On)

  PIOC->PIO_PDR |= PIO_PDR_P3 | PIO_PDR_P5 | PIO_PDR_P7;           // Setting pins 3,5,7 (DUE Pins 35, 37, 39) to PWM Peripheral, not GPIO
  PIOC->PIO_ABSR |= PIO_ABSR_P3 | PIO_ABSR_P5 | PIO_ABSR_P7;       // Setting pins to Peripheral B

  PIOC->PIO_PDR |= PIO_PDR_P2 | PIO_PDR_P4 | PIO_PDR_P6;           // Setting pins 2,4,6 (DUE Pins 34, 36, 38) to PWM Peripheral, not GPIO
  PIOC->PIO_ABSR |= PIO_ABSR_P2 | PIO_ABSR_P4 | PIO_ABSR_P6;       // Setting pins to Peripheral B

  PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(divA);  // Set PWM clocke rate to 2MHz (84MHz/42)
  PWM->PWM_SCM |= PWM_SCM_SYNC0 | PWM_SCM_SYNC1 | PWM_SCM_SYNC2 | PWM_SCM_SYNC3 | PWM_SCM_SYNC4;      // Synchronizing of Channels 0, 1, 2, 3 & 4
  PWM->PWM_SCM |= PWM_SCM_UPDM_MODE1;                 // Manual Write of duty-cycle automatic trigger of the update
 
  NVIC_SetPriority(PWM_IRQn, 0);                      // Set the Nested Vector Interrupt Controller (NVIC) priority for the PWM controller to 0 (highest)
  NVIC_EnableIRQ(PWM_IRQn);                           // Connect PWM Controller to Nested Vector Interrupt Controller (NVIC)

  PWM->PWM_IER1 = PWM_IER1_CHID0;                     // Enable interrupt on PWM channel 0 triggered at end of PWM period

  calcCPRDV();
 
  PWM->PWM_CH_NUM[0].PWM_CPRD = CPRDV;                // Channel 0 Period f = 2MHz/(CPRD)= 100Hz = 0.01s |CPRD = 2MHz/f
  PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_CLKA;     // Period is left aligned,clock source is CLKA on Channel 0

  // PWM Channels 3 and 4 set the low and high side dead-time respectively
  PWM->PWM_CMP[3].PWM_CMPV = 2000;                                  // Set the channel 3 compare value to 2000 =~ 1ms
  PWM->PWM_CMP[3].PWM_CMPM = PWM_CMPM_CEN;                          // Enable channel 3 compare match
  PWM->PWM_CMP[4].PWM_CMPV = 2000;                                  // Set the channel 4 compare value to 2000
  PWM->PWM_CMP[4].PWM_CMPM = PWM_CMPM_CEN;                          // Enable channel 4 compare match
  PWM->PWM_IER2 = PWM_IER2_CMPM3 | PWM_IER2_CMPM4;                  // Enable interrupt on PWM channel 0 triggered at end of PWM period
 
  PWM->PWM_ENA = PWM_ENA_CHID0;                                     // Enable synchronous PWM on all channels
}

void loop(){}

void PWM_Handler()                       // PWM Interrupt Service Routine (ISR)
{
  static byte count = 0;
  
  if (PWM->PWM_ISR1 & PWM_ISR1_CHID0)    // Check if an update condition has occured
  {       
    update_Duty_Cycle(count);            // Update the duty cycles
  }
  uint32_t status = PWM->PWM_ISR2;
  if (status & PWM_IER2_CMPM3)           // Check if a compare condition on channel 3 has occured
  {
    switch (count)
    {     
      case 1:
        PWM->PWM_OSC = PWM_OSC_OSCL1;    // Disable channel 1 low side override
        break;
      case 3:
        PWM->PWM_OSC = PWM_OSC_OSCL2;    // Disable channel 2 low side override
        break;
      case 5:
        PWM->PWM_OSC = PWM_OSC_OSCL0;    // Disable channel 0 low side override
        break;
      default:
        break;
    }
  }
  if (status & PWM_IER2_CMPM4)         // Check if a compare condition on channel 4 has occured
  {
    switch (count)
    {
      case 0:  
        PWM->PWM_OSC = PWM_OSC_OSCH2;     // Disable channel 2 high side override
        break;      
      case 2:
        PWM->PWM_OSC = PWM_OSC_OSCH0;     // Disable channel 0 high side override     
        break;
      case 4:
        PWM->PWM_OSC = PWM_OSC_OSCH1;     // Disable channel 1 high side override
        break;   
      default:
        break;
    }
    count = (count + 1) % 6;
  }
}

void calcCPRDV ()
{
  //inverterFrequency = 60;
  static float numOfVectors = 6;
  static float adMCKFreq = 84000000;
  static float timerFreq = (adMCKFreq/divA); //2MHz
  static float period = 1/inverterFrequency;
  static float Ts = period/numOfVectors;
  static float switchingFreq = 1/Ts;
  CPRDV = (timerFreq/(1*switchingFreq));
}

void update_Duty_Cycle(byte count)
{
  if(stateCount < 6)
  {
    PWM->PWM_CH_NUM[0].PWM_CDTY = 0;
    PWM->PWM_CH_NUM[1].PWM_CDTY = 0;
    PWM->PWM_CH_NUM[2].PWM_CDTY = 0;
    stateCount++;          
  }
  else
  {       
    static uint32_t p = CPRDV;
    static uint32_t n = 0;
    switch(count)
    {
      case 0: //pnn = 100 => 012    
        PWM->PWM_OSS = PWM_OSS_OSSH2;               // Override the channel 2 high side output to 0V                 
        PWM->PWM_CH_NUM[0].PWM_CDTY = p;
        PWM->PWM_CH_NUM[1].PWM_CDTY = n;
        PWM->PWM_CH_NUM[2].PWM_CDTY = n;
      break;
      case 1: //ppn = 110 => 012  
        PWM->PWM_OSS = PWM_OSS_OSSL1;               // Override the channel 1 low side output to 0V
        PWM->PWM_CH_NUM[0].PWM_CDTY = p;
        PWM->PWM_CH_NUM[1].PWM_CDTY = p;
        PWM->PWM_CH_NUM[2].PWM_CDTY = n;   
      break;
      case 2: //npn = 010 => 012
        PWM->PWM_OSS = PWM_OSS_OSSH0;               // Override the channel 0 high side output to 0V
        PWM->PWM_CH_NUM[0].PWM_CDTY = n;
        PWM->PWM_CH_NUM[1].PWM_CDTY = p;
        PWM->PWM_CH_NUM[2].PWM_CDTY = n; 
      break;
      case 3: //npp = 011 => 012      
        PWM->PWM_OSS = PWM_OSS_OSSL2;               // Override the channel 2 low side output to 0V
        PWM->PWM_CH_NUM[0].PWM_CDTY = n;
        PWM->PWM_CH_NUM[1].PWM_CDTY = p;
        PWM->PWM_CH_NUM[2].PWM_CDTY = p;
      break;
      case 4: //nnp = 001 => 012   
        PWM->PWM_OSS = PWM_OSS_OSSH1;               // Override the channel 1 high side output to 0V
        PWM->PWM_CH_NUM[0].PWM_CDTY = n;
        PWM->PWM_CH_NUM[1].PWM_CDTY = n;
        PWM->PWM_CH_NUM[2].PWM_CDTY = p; 
      break;
      case 5: //pnp = 101 => 012   
        PWM->PWM_OSS = PWM_OSS_OSSL0;              // Override the channel 0 low side output to 0V  
        PWM->PWM_CH_NUM[0].PWM_CDTY = p;
        PWM->PWM_CH_NUM[1].PWM_CDTY = n;
        PWM->PWM_CH_NUM[2].PWM_CDTY = p;          
      break;
      default:
      break;
    }      
  }
}
