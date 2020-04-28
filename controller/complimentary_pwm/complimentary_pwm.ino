
void setup () {

  // PWM Set-up on pins PC7 and PA20 (Arduino Pins 39(PWMH2) and 43(PWML2)): see Datasheet chap. 38.5.1 page 973
  PMC->PMC_PCER1 |= PMC_PCER1_PID36;                   // PWM power ON
  
  PWM->PWM_DIS = PWM_DIS_CHID2;                        // Disable PWM channel 2

  // Select Instance=PWM; Signal=PWMH2 (channel 2); I/O Line=PC7 (P7, Arduino pin 39, see pinout diagram) ; Peripheral type =B
  PIOC->PIO_PDR |= PIO_PDR_P7;                          // Set the pin to the peripheral PWM, not the GPIO

  PIOC->PIO_ABSR |= PIO_PC7B_PWMH2;                     // Set PWM pin perhipheral type B

  // Select Instance=PWM; Signal=PWML2 (channel 2); I/O Line=PA20 (P20, Arduino pin 43, see pinout diagram) ; Peripheral=B
  PIOA->PIO_PDR |= PIO_PDR_P20;                          // Set the pin to the peripheral PWM, not the GPIO

  PIOA->PIO_ABSR |= PIO_PA20B_PWML2;                    // Set PWM pin perhipheral type B

  // Enable the PWM channel 2 (see datasheet page 973)

  PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);    // Set the PWM clock rate to 2MHz (84MHz/42). Adjust DIVA for the resolution you are looking for

  PWM->PWM_CH_NUM[2].PWM_CMR = PWM_CMR_CPRE_CLKA;     // The period is left aligned, clock source as CLKA on channel 2

  PWM->PWM_CH_NUM[2].PWM_CPRD = 100;                             // Channel 2 : Set the PWM frequency 2MHz/(2 * CPRD) = F ;

  PWM->PWM_CH_NUM[2].PWM_CDTY = 50;                             // Channel 2: Set the PWM duty cycle to x%= (CDTY/ CPRD)  * 100 % ;

  PWM->PWM_ENA = PWM_ENA_CHID2;

  // Alternately, you can use this format :  REG_PWM_CPRD2 = 50;

}

void loop() {
  
}
