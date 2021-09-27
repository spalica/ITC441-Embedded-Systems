#define RED_LED 10
#define GREEN_LED 9
#define PIR 5
bool state = false;
int dutyCycle = 128;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  if (digitalRead(PIR)) {
    digitalWrite(RED_LED, false);
  }
  else {
    (digitalWrite(RED_LED, true));
  }
}
