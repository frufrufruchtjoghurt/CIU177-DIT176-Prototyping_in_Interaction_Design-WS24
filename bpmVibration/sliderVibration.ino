int pin_slider = 0;
int pin_motor = 3;

void setup() {
  pinMode(pin_slider, INPUT);
  pinMode(pin_motor, OUTPUT);
}

void loop() {
  int sliderValue = analogRead(pin_slider);
  int motorStrength = map(sliderValue, 0, 1023, 0, 255);

  analogWrite(pin_motor, motorStrength);
}