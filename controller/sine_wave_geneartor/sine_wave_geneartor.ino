
/*******************************************************************************************/
/*                Synchro channel PWML0 ONLY with PDC DMA trigger on Compare               */
/*******************************************************************************************/

#define sinsize  (256)                // Sample number (a power of 2 is better)
#define PERIOD_VALUE (31250)//   (15625)        // For a 1 Hz sinwave
#define NbCh      (1)                 // Only channel 0 ---> Number of channels = 1

#define DUTY_BUFFER_LENGTH      (sinsize * NbCh) // Half words

uint16_t Duty_Buffer[DUTY_BUFFER_LENGTH];

#define UpdatePeriod_Msk (0b1111)
#define UpdatePeriod    (UpdatePeriod_Msk & 0b0000) //Defines the time between each duty cycle update of the synchronous channels
//This time equals to (UpdatePeriod + 1) periods of the Reference channel 0

uint16_t Sin_Duty[sinsize];

void setup () {

  Serial.begin(9600);

  PMC->PMC_PCER1 |= PMC_PCER1_PID36;       // PWM controller power ON
  PMC->PMC_PCER0 |= PMC_PCER0_PID13;       // PIOC power ON

  // PWML0 on PC2, peripheral type B
  PIOC->PIO_PDR |= PIO_PDR_P2;
  PIOC->PIO_ABSR |= PIO_PC2B_PWML0;

  // Set synchro channels list : Channel 0
  PWM->PWM_DIS = PWM_DIS_CHID0;

  PWM->PWM_SCM  = PWM_SCM_SYNC0          // Add SYNCx accordingly, at least SYNC0
                  | PWM_SCM_UPDM_MODE2;  //Automatic write of duty-cycle update registers by the PDC DMA

  // Set duty cycle update period
  PWM->PWM_SCUP = PWM_SCUP_UPR(UpdatePeriod);

  // Set the PWM Reference channel 0 i.e. : Clock/Frequency/Alignment
  PWM->PWM_CLK = PWM_CLK_PREA(0b0000) | PWM_CLK_DIVA(3);       // Set the PWM clock rate for 84 MHz/1
  PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_CLKA;               // The period is left aligned, clock source as CLKA on channel 0
  PWM->PWM_CH_NUM[0].PWM_CPRD = PERIOD_VALUE;                   // Set the PWM frequency (84MHz/1)/PERIOD_VALUE Hz

  /****  Final frequency = MCK/DIVA/PRES/CPRD/(UPR + 1)/sinsize = 7 Hz    ****/

  // Set Interrupt events
  PWM->PWM_IER2 = PWM_IER2_WRDY;   //Write Ready for Synchronous Channels Update Interrupt Enable
  //synchro with ENDTX End of TX Buffer Interrupt Enable

  // Fill duty cycle buffer for channels 0, x, y ...
  // Duty_Buffer is a buffer of Half Words(H_W) composed of N lines which structure model for each duty cycle update is :
  // [ H_W: First synchro channel 0 duty cycle **Mandatory** ]/[ H_W: Second synchro channel duty cycle ] ... and so on

  for (int i = 0; i < sinsize; i++) {
    Sin_Duty[i] = 1 + (2047 * (sinf( i * 2 * PI / sinsize ) + 1));
  }

  for (uint32_t i = 0; i < sinsize; i++) {
    Duty_Buffer[i * NbCh + 0] = Sin_Duty[i];
    // ............................................
    // Duty_Buffer[i * NbCh + (NbCh - 1)] = Sin_Duty[i];
  }

  PWM->PWM_ENA = PWM_ENA_CHID0;                  // Enable PWM for all channels, channel 0 Enable is sufficient

  PWM->PWM_TPR  = (uint32_t)Duty_Buffer;        // FIRST DMA buffer
  PWM->PWM_TCR  = DUTY_BUFFER_LENGTH;           // Number of Half words
  PWM->PWM_TNPR = (uint32_t)Duty_Buffer;        // Next DMA buffer
  PWM->PWM_TNCR = DUTY_BUFFER_LENGTH;
  PWM->PWM_PTCR = PWM_PTCR_TXTEN;               // Enable PDC Transmit channel request

  NVIC_EnableIRQ(PWM_IRQn);

}

void loop() {

  // For debugging only :
  // Check correct updates of CDTY via CDTYUPD by DMA
  // Menu > Tools > Serial Tracer -- 9600 baud

  Serial.println(PWM->PWM_CH_NUM[0].PWM_CDTY);

  // Here you can modify PWM->PWM_SCUPUPD()
  // to vary frequency of sine output

}

void PWM_Handler() {  // move PDC DMA pointers to next buffer

  PWM->PWM_ISR2;      // Clear status register

  PWM->PWM_TNPR = (uint32_t)Duty_Buffer;
  PWM->PWM_TNCR = DUTY_BUFFER_LENGTH;

}


