//submit with final report
extern "C" {
  void start();
  void temperature();
  void increaseSpeed();
  void decreaseSpeed();
}

void setup() {
  //will output debug info to screen
  void ClearScreen();
  Serial.begin(9600);

  start();
}

void loop() {
  ClearScreen(); //debug
  temperature(); //read temperature data?

  //pass data from temperature() to C code
  int val = ADC; //ADCL and ADCH are data registers from ADC on Arduino
  float voltage = 5 * (val/1023.0);

  //temperature data conversion to celsius
  float a = 0.7943, b = -9.2681, c = 41.072, d = -85.342, e = 101.77, f = -52.446; //polynomial coefficients
  float temp =  a*pow(voltage, 5) + b*pow(voltage, 4) + c*pow(voltage, 3) + d*pow(voltage, 2) + e*voltage + f; 

  if (temp > 30.0) {
    increaseSpeed();
  } else if(temp < 30.0) {
    decreaseSpeed();
  }

  //debug
  Serial.print(temp);
  Serial.print(" ");
  Serial.println(OCR0B);
  Serial.print(voltage);

  //delay to allow heat load temperature to settle before next check
  //minimizes oscillation range of fan speed at equilibrium when the heat load is target temperature
  delay(67); //something weird seems to be on my end, time between updates still 15x longer
             //than delay, if bug not happening, may need to change. delay set to 67, since
             //1000/15 ~ 67
}

//15x longer than delay, specifically, to update again, regardless of its value
//first error found, pwm an dtemp were both using r16? increaseSpeed being called while temp
//< 30 or == 30, fan sounds as though speed changing radiacally each time

// Clears the LCD display and returns to position (1,1)
void ClearScreen(){
  Serial.write(0xFE);
  Serial.write(0x58);
  delay(10);
}
