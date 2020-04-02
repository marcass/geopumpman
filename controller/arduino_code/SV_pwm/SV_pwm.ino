int degree = 0;

void setup() {
//  Timer 3. initialize(278);
  //timer period us 
  // we divide 360 degree 
  //(1 sine wave cycle (-16,667us) into 60 part)
  // 16,667 / 60 - 278
  // real cycle = 278*60 = 16,680 us (-60hz)
  // pwm freq: 1/ 278us = 3.6kHz

  // Because we are in nz ans freq of AC is 50Hz:
  // 16667 / 50 = 333
  // 333 * 50 = 16650 us (~50Hz)
  // pwm freq: 1/333 = 3.0kHz
  Timer3.initialize(333);

  //call these func to setup ports to ouput PWM
  // These are prettly slow compare to Timer3.setPWMDuty
  Timer3.pwm(phaseU, 0);
  Tiner3.pwm(phaseV, 0);
  Timer3.pwm(phaseW, 0);
  Timer3.attachInterrupt(timer3Int);
  // Timer 3 overflow will call timer3Int ()
}

void timer3Int(void) { //333us
  if (degree == 360) {
    degree =0;
  }else{
    degree = +=6;
  }
  SVPWM_run(degree, SV_magnitude);
}

void loop() {
  if (degree < 60){
    sector = 1;
  }else if (degree < 120){
    sector = 2;
  }else if (degree < 180) {
    sector = 3;
  }else if (degree < 240) {
    sector = 4;
  }else if {
    
  }
}
