#define SWITCH_PIN      10 // input for toggle switch
#define LED_PIN1      	6 // output to FET module
#define LED_PIN2      	7 // output to FET module

#define STROBE_COUNT_DELAY 18000 // [ms] time between strobe cycles

int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin
int num_presses = 0;
int strobe_count = 0;

// byte target, current; // target and current pwm value

int FADE_INTERVAL_1 = 	30; // [ms] time between fade steps
int NEXTFADE_INTERVAL_1 = 1500; // [ms] time between fade cycles
int FADE_INTERVAL_2 = 	30; // [ms] time between fade steps
int NEXTFADE_INTERVAL_2 = 1500; // [ms] time between fade cycles

byte current; // current pwm value
byte target; // target pwm value
unsigned long time_for_fadestep_1;
unsigned long time_for_nextfade_1;
unsigned long time_for_fadestep_2;
unsigned long time_for_nextfade_2;
unsigned long time_for_strobe_delay;
unsigned long lastDebounceTime;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  pinMode(SWITCH_PIN, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

              
void loop() 
{
// read the state of the switch into a local variable:
  int reading = digitalRead(SWITCH_PIN);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        // increment our count for number of times pressed
        num_presses += 1;
        Serial.println("button is being pressed!");
      }
    }
  }
   // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

    // button hasn't been pressed yet (or has been reset)
    if (num_presses == 0)
    {
      	digitalWrite(4, LOW);
      	digitalWrite(5, LOW);
      	digitalWrite(6, LOW);
      	digitalWrite(7, LOW);
        Serial.println("num_presses 0");
    }
    // button has been pressed once!
    if (num_presses == 1)
    {
        digitalWrite(4, HIGH);
      	digitalWrite(5, HIGH);
      	digitalWrite(6, LOW);
      	digitalWrite(7, LOW);
        Serial.println("num_presses 1"); 
    }
  // button has been pressed twice!
    if (num_presses == 2)
    {
        digitalWrite(4, HIGH);
      	digitalWrite(5, HIGH);
        Serial.println("num_presses 2");

  if (millis() > time_for_nextfade_1) {
    time_for_nextfade_1 = millis() + (unsigned long)NEXTFADE_INTERVAL_1;
  if (current == 0) { 
    target = 20;
    strobe_count += 1;
    Serial.println("strobe_count");
  }}
  
   if (current == 20) { 
    target = 0;
   }
  
  if (millis() > time_for_fadestep_1) {
    time_for_fadestep_1 = millis() + (unsigned long)FADE_INTERVAL_1;
    if (current < target) current+=4; 
    if (current > target) current-=.5; 
    analogWrite(LED_PIN1, current);
    Serial.print(target);
    Serial.print("  ");
    Serial.println(current);
  }
      
      
      if (millis() > time_for_nextfade_2) {
    time_for_nextfade_2 = millis() + (unsigned long)NEXTFADE_INTERVAL_2;
  if (current == 1) { 
    target = 20;
  }}
  
   if (current == 20) { 
    target = 0;
   }
  
  if (millis() > time_for_fadestep_2) {
    time_for_fadestep_2 = millis() + (unsigned long)FADE_INTERVAL_2;
    if (current < target) current+=4; 
    if (current > target) current-=.5; 
    analogWrite(LED_PIN2, current);
    Serial.print(target);
    Serial.print("  ");
    Serial.println(current);
  }
    }
  
  
    if (digitalRead(10) == HIGH && num_presses == 3)
    {
        Serial.println("num_presses 3, resetting num_presses to 0");
        num_presses = 0;
    }
  
  // stobe count causes reset
    if (strobe_count == 6)
    {
      	num_presses = 1;
        Serial.println("stobe count delay");
      
    if (millis() > time_for_strobe_delay) {
    time_for_strobe_delay = millis() + (unsigned long)STROBE_COUNT_DELAY;
        strobe_count = 0;
       	num_presses = 2;
    } 
  }
}
    

