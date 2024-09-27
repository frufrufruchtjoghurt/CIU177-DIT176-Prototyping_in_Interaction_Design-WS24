// include library
//#include<FastLED.h>

// Pin inputs
int pin_motor = 2;
int pin_mic = 3;
int pin_slider = 0;
int led_RED = 7;
int led_GREEN = 4;

// vibration
int vibrationTime = 200;

// beat detection
int threshold = 500;
unsigned long lastBeat = 0;
int bpm = 0;
int beatcounter = 0;
unsigned long startTime;

int bpmToTime(int bpm) {
  int interval = 60000 / bpm;
  return interval;
}

void setup() {
  pinMode(pin_motor, OUTPUT);
  pinMode(pin_mic, INPUT);
  pinMode(pin_slider, INPUT);
  startTime = millis(); 
  pinMode(led_RED, OUTPUT);
  pinMode(led_GREEN, OUTPUT);
}

int detectBPM() {
  audiosignal = analogRead(pin_mic);

// was there a beat?
  if (audiosignal > threshold) {
    unsigned long currentTime = millis();
  }

// Count the beat
  if (currentTime - lastbeat > 500) { // prevent double counting
    lastBeat = currentTime;
    beatCounter++;
  }
  if (beatCounter >=5) {
    unsigned long elapsedTime = currentTime - startTime;  // Time for 5 beats
    bpm = (60000 * beatCounter) / elapsedTime;  // Calculate BPM
    beatCounter = 0;    // Reset beat counter
    startTime = currentTime;  // Reset the start time
  }
  return bpm;
}

void loop() {
  // vibrate & RED
  digitalWrite(pin_motor, HIGH);
  digitalWrite(led_RED, HIGH);
  digitalWrite(led_GREEN, LOW);
  delay(vibrationTime);
  // wait
  digitalWrite(pin_motor, LOW);
  digitalWrite(led_RED, LOW);
  digitalWrite(led_GREEN, LOW);
  delay(bpmToTime(detectBPM()) - vibrationTime);
  // vibrate & GREEN
  digitalWrite(pin_motor, HIGH);
  digitalWrite(led_RED, LOW);
  digitalWrite(led_GREEN, HIGH);
  delay(vibrationTime);
  // wait
  digitalWrite(pin_motor, LOW);
  digitalWrite(led_RED, LOW);
  digitalWrite(led_GREEN, LOW);
  delay(bpmToTime(detectBPM())) - vibrationTime);
}
