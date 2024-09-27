int pin_slider = 0;
int pin_motor = 3;
int led_RED = 7;
int led_GREEN = 4;

// vibration
int vibrationTime = 200;
int bpm = 104;


int bpmToTime(int bpm) {
  int interval = 60000 / bpm;
  return interval;
}


void setup() {
  pinMode(pin_slider, INPUT);
  pinMode(pin_motor, OUTPUT);
  pinMode(led_RED, OUTPUT);
  pinMode(led_GREEN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Hello");
}

void loop() {
  int sliderValue = analogRead(pin_slider);
  int motorStrength = map(sliderValue, 0, 1023, 50, 255);
  Serial.println(motorStrength);

  // vibrate & RED
  analogWrite(pin_motor, motorStrength);
  digitalWrite(led_RED, HIGH);
  digitalWrite(led_GREEN, LOW);
  delay(vibrationTime);
  // wait
  analogWrite(pin_motor, LOW);
  digitalWrite(led_RED, LOW);
  digitalWrite(led_GREEN, LOW);
  delay(bpmToTime(bpm) - vibrationTime);
  // vibrate & GREEN
  analogWrite(pin_motor, motorStrength);
  digitalWrite(led_RED, LOW);
  digitalWrite(led_GREEN, HIGH);
  delay(vibrationTime);
  // wait
  analogWrite(pin_motor, LOW);
  digitalWrite(led_RED, LOW);
  digitalWrite(led_GREEN, LOW);
  delay(bpmToTime(bpm) - vibrationTime);
}