// install the servo library
#include <Servo.h>

// declare servos
Servo petal_1;
Servo petal_2;
Servo petal_3;

// define digital pins for button and servos
#define SERV_PIN1 10
#define SERV_PIN2 9
#define SERV_PIN3 8
#define BUTT_PIN 20

// time to delay servo motion between degree change
int wait = 60;

// toggle for button press to activate motors
bool activateServo;

// state variable initialized at high (meaning button is off)
boolean buttOldState = HIGH;

void setup() { 
  Serial.begin(9600); // begin serial monitor
  
  pinMode(BUTT_PIN, INPUT_PULLUP);
    // initilaizes button pin as input without resistor

  // attach servos
  petal_1.attach(SERV_PIN1);
  petal_2.attach(SERV_PIN2);
  petal_3.attach(SERV_PIN3);

  // initialize servo activation
  activateServo = false;

  // ensure servos are at 0 degrees
  petal_1.write(0);
  petal_2.write(0);
  petal_3.write(0);

}

void loop() {

  // get a reading from your pushbutton
  boolean buttNewState = digitalRead(BUTT_PIN);

  // check if button state has changed from off to on
  if((buttNewState == LOW) && (buttOldState == HIGH)) {
    // short delay to debounce button.
    delay(20);

    // get a new reading from your pushbutton
    buttNewState = digitalRead(BUTT_PIN);
    // if it is still on, activate the servo motors
    if(buttNewState == LOW) {      
      Serial.println("button press");
      activateServo = true;
    }
  }

  // check if the button has been pressed
  if (activateServo == true) {
    Serial.println("movin to 60");

    // slowly move your servo motors to desired angle
    for (int i = 0; i <= 60; i++) {
      petal_1.write(i);
      petal_2.write(i);
      petal_3.write(i);
      delay(wait);
    }
    // slowly move your servos back to 0
    for (int i = 60; i >= 0; i--) {
      petal_1.write(i);
      petal_2.write(i);
      petal_3.write(i);
      delay(wait);
    }
    // stop servo motion
    activateServo = false;
  }

  // Set the last-read button state to the old state, should be off (high)
  buttOldState = buttNewState;
}