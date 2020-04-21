/*****************************************************8
 * Control a reluctance DC motor using a ps219a3-adt intelligent motor controller and arduino due
 * Datasheet here: https://www.mitsubishielectric.com/semiconductors/files/manuals/super_mini_dipipm_ver5_e.pdf
 * Important points:
 * - Need a min of 1 microsecond gap between phase signals (arm-shoot-through time or dead time)
 * - Maximum freq of pwm is 20kHz
 * - Space vector lookup table here: https://docs.google.com/spreadsheets/d/1md-qKsFOfhslWOQoSdTHKFGMMkS03pnrN5VvrLl9iK4/edit#gid=627269583
 */


/**************************************************************************************/
/*       PWM pulses on TIOA0 (arduino pin 2) Frequency = 15 KHz, Duty cycle = 80%     */
/*       Interruptions on TIOA0 rising and falling edges                              */                
/**************************************************************************************/

void setup() {

  /*************  Timer Counter 0 Channel 0 to generate PWM pulses thru TIOA0  ************/
  PMC->PMC_PCER0 |= PMC_PCER0_PID27;       // TC0 power ON - Timer Counter 0 channel 0 IS TC0
  
  PIOB->PIO_PDR |= PIO_PDR_P25;           // PB25 is no more driven by the GPIO
  PIOB->PIO_ABSR |= PIO_PB25B_TIOA0;

  TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1  // MCK/2, clk on rising edge
                              | TC_CMR_WAVE               // Waveform mode
                              | TC_CMR_WAVSEL_UP_RC        // UP mode with automatic trigger on RC Compare
                              | TC_CMR_ACPA_CLEAR          // Clear TIOA0 on RA compare match
                              | TC_CMR_ACPC_SET;           // Set TIOA0 on RC compare match


  TC0->TC_CHANNEL[0].TC_RC = 2800;  //<*********************  Frequency = (Mck/2)/TC_RC  Hz = 15 KHz
  TC0->TC_CHANNEL[0].TC_RA = 2240;  //<********************   Duty cycle = (TC_RA/TC_RC) * 100  %  = 80 %

  TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS       // Interrupt on RC compare match
                              | TC_IER_CPAS;    // Interrupt on RA compare match
                              
  NVIC_EnableIRQ(TC0_IRQn);                     // Interrupt enable
                           
  TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG | TC_CCR_CLKEN; // Software trigger TC0 counter and enable
}
void TC0_Handler()
{
 uint32_t status;
 status = TC0->TC_CHANNEL[0].TC_SR;  // Read and clear TC0 status register

 if(status & TC_SR_CPAS) {
  // Toggle pin 1
 }
 else  // if(status & TC_SR_CPCS)
  {
  // Toggle pin 2
 }
}
void loop() {
 
}

