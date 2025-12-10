

int counts[12] = {1, 10, 20, 30, 40, 50, 0, 0, 0, 0, 0, 0};

float startTime;

void setup() {
  Serial.begin(9600);
  analogReference(AR_DEFAULT);
  analogReadResolution(12);
  pinMode(A0, INPUT);

  //  Set prescaler to 8 example (can be adjusted)
  ADC->CTRLA.bit.ENABLE = 0;
  while (ADC->STATUS.bit.SYNCBUSY) {}
  ADC->CTRLB.bit.PRESCALER = ADC_CTRLB_PRESCALER_DIV8_Val;
  ADC->CTRLA.reg |= ADC_CTRLA_ENABLE; // Enable the AD
  while (ADC->STATUS.bit.SYNCBUSY) {}
  // analogReference(AR_INTERNAL1V65);
  startTime = millis();
}

void loop() {
  float currentTime = (millis() - startTime) / 1000.0;
  float mV = ((analogRead(A0) - 400) * 1.2) / 4096.0 * 3300;
  for (size_t i = 5; i >= 0; i--) {
    if (mV > counts[i]) {
      counts[i + 6]++;
      break;
    }
  }
  Serial.println("**********************************");
  Serial.print("Above ");
  for (size_t i = 0; i < 6; i++) {
    Serial.print(counts[i] + " ");
  }
  Serial.println();
  Serial.print("Counts");
  for (size_t i = 6; i < 12; i++) {
    Serial.print(counts[i] + " ");
  }
  Serial.println();
  Serial.print("CPS   ");
  for (size_t i = 6; i < 12; i++) {
    Serial.print(counts[i] / currentTime + " ");
  }
  // if (mV > 200)
    // Serial.println(mV);
  // Serial.println();
  // delay(500);


}
