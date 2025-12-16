

int counts[12] = {30, 40, 50, 60, 70, 80, 0, 0, 0, 0, 0, 0};

float startTime;

void setup() {
  Serial.begin(9600);
  analogReference(AR_DEFAULT);
  analogReadResolution(12);
  pinMode(A0, INPUT);

  //  Set prescaler to 8 example (can be adjusted)
  // ADC->CTRLA.bit.ENABLE = 0;
  // while (ADC->STATUS.bit.SYNCBUSY) {}
  ADC->CTRLB.bit.PRESCALER = ADC_CTRLB_PRESCALER_DIV8_Val;
  ADC->CTRLA.reg |= ADC_CTRLA_ENABLE; // Enable the AD
  // while (ADC->STATUS.bit.SYNCBUSY) {}
  // analogReference(AR_INTERNAL1V65);
  delay(2000);
  startTime = millis();
}

void loop() {
  float currentTime = (millis() - startTime) / 1000.0;
  float mV = ((analogRead(A0) - 400) * 1.2) / 4096.0 * 3300;
  for (int i = 5; i >= 0; i--) {
    if (mV > counts[i]) {
      counts[i + 6]++;
      break;
    }
  }
  if (mV <= counts[0]) return;
  Serial.println("**********************************");
  Serial.println("TOTAL TIME: " + (String)currentTime);
  Serial.print("Thresh ");
  for (size_t i = 0; i < 6; i++) {
    Serial.print((String)counts[i] + " ");
  }
  Serial.println();
  Serial.print("Counts ");
  for (size_t i = 6; i < 12; i++) {
    Serial.print((String)counts[i] + " ");
  }
  Serial.println();
  Serial.print("CPS    ");
  for (size_t i = 6; i < 12; i++) {
    Serial.print((String)(counts[i] / currentTime) + " ");
  }
  Serial.println();
  Serial.println("Recorded " + (String)mV);
  while(mV > counts[0]) {
    mV = (analogRead(A0) - 400) * 1.2 / 4096.0 * 3300;
    Serial.println("Current millivolts: " + (String) mV + ", waiting to get below " + (String)counts[0]);
  }
  // if (mV > 200)
    // Serial.println(mV);
  // Serial.println();
  // delay(500);


}

// Use this later for a polynomial fit to calibration data
// float get_sipm_voltage(float adc_value)
// {
// int N = sizeof(cal)/sizeof(float);
// float v = cal[0];
// for (int i = 1; i < N; ++i) {
// v = v * adc_value + cal[i];
// }
// return v;
// }
