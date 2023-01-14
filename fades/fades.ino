#include <Debouncer.h>

const int btnPin = 10;
const int ledPin = 9;
int duration_ms = 50;

Debouncer debouncer(btnPin, duration_ms);
bool is_on = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);

    // add from lambda
    debouncer.subscribe(Debouncer::Edge::FALL, [](const int state) {
        // do something on falling edge
        if (is_on) {
          Serial.println("turn led off");
          digitalWrite(ledPin, LOW);
          is_on = false;
        } else {
          Serial.println("turn led on");
          digitalWrite(ledPin, HIGH);
          is_on = true;
        }
    });

    debouncer.subscribe(Debouncer::Edge::RISE, [](const int state) {
        // do something on rising edge

    });

    debouncer.subscribe(Debouncer::Edge::CHANGED, [](const int state) {
        // do something every edge
    });

    // this simplified one can also be used to register callback to Edge::CHANGED
    debouncer.subscribe([](const int state) {
        // do something every edge
    });

  Serial.begin(9600);
}


void loop() {
  debouncer.update();
}

    
