
/*
   Relay Shield - Blink
   Turns on the relay for two seconds, then off for two seconds, repeatedly.

   Relay Shield transistor closes relay when D1 is HIGH
*/
#include <vector>

const int relayPin = D1;

std::vector<int> pins = {D3, D4};
using namespace std;

const int wait = 500;


void setup() {
  for (int i = 0; i < pins.size(); i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  // Turn on all pins
  for (int i = 0; i < pins.size(); i++) {
    digitalWrite(pins[i], LOW);
    delay(wait);
    digitalWrite(pins[i], HIGH);
    delay(wait);
  }

}
