/*
  APDS-9960 - Gesture Sensor

  This example reads gesture data from the on-board APDS-9960 sensor of the
  Nano 33 BLE Sense and prints any detected gestures to the Serial Monitor.

  Gesture directions are as follows:
  - UP:    from USB connector towards antenna
  - DOWN:  from antenna towards USB connector
  - LEFT:  from analog pins side towards digital pins side
  - RIGHT: from digital pins side towards analog pins side

  The circuit:
  - Arduino Nano 33 BLE Sense

  This example code is in the public domain.
*/

#include <Arduino_APDS9960.h>

int up_count = 0;
int down_count = 0;
int left_count = 0;
int right_count = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }

  // for setGestureSensitivity(..) a value between 1 and 100 is required.
  // Higher values make the gesture recognition more sensitive but less accurate
  // (a wrong gesture may be detected). Lower values makes the gesture recognition
  // more accurate but less sensitive (some gestures may be missed).
  // Default is 80
  //APDS.setGestureSensitivity(80);

  Serial.println("Detecting gestures ...");

}
void loop() {

  if (APDS.gestureAvailable()) {
    // a gesture was detected, read and print to Serial Monitor
    int gesture = APDS.readGesture();


    switch (gesture) {
      case GESTURE_UP:
      // checks if UP has already been entered once or twice
        if (up_count < 2) {
          Serial.println("Correct");
            if (up_count == 0) {
              // prints string confirmation of gesture pattern and increments up_count
              Serial.println("OXXXXXXX");
              up_count += 1;}
              else {
              Serial.println("OOXXXXXX");
              up_count += 1;}}
            else {
              // prints if UP is entered a third time and resets up_count
            Serial.println("Wrong McWrongface");
            Serial.println("XXXXXXXX");
            up_count = 0;}
        break;

      case GESTURE_DOWN:
      // checks if up_count has a value of 2, and if down_count value is 0 or 1 
        if (up_count == 2 && down_count == 0 || down_count == 1) {
          Serial.println("Correct");
            if (down_count == 0) {
              // prints string confirmation of gesture pattern and increments down_count
              Serial.println("OOOXXXXX");
              down_count += 1;}
              else{
                Serial.println("OOOOXXXX");
                down_count += 1;}}
            else {
              // prints if DOWN is entered a third time and resets counts
            Serial.println("Wrong McWrongface");
            Serial.println("XXXXXXXX");
            up_count = 0;
            down_count = 0;}
        break;

      case GESTURE_LEFT:
      // checks if up_count = 2
      // and if down_count = 2
      // and if left_count value is 0 or 1
        if (up_count == 2 && down_count == 2 && left_count == 0 || left_count == 1) {
          Serial.println("Correct");
            if (left_count == 0) {
              // prints string confirmation of gesture pattern and increments left_count
              Serial.println("OOOOOXXX");
              left_count += 1;}
              else{
                Serial.println("OOOOOOXX");
                left_count += 1;}}
            else {
              // prints if left is entered a third time and resets all counts
            Serial.println("Wrong McWrongface");
            Serial.println("XXXXXXXX");
            up_count = 0;
            down_count = 0;
            left_count = 0;}
        break;

      case GESTURE_RIGHT:
      // verifies up_count = 2
      // verifies down_count = 2
      // verifies left_count = 2
      // verifies right_count value is 0 or 1
        if (up_count == 2 && down_count == 2 && left_count == 2 && right_count == 0 || right_count == 1) {
          Serial.println("Correct");
            if (right_count == 0) {
              // prints string confirmation of gesture pattern and increments right_count
              Serial.println("OOOOOOOX");
              right_count += 1;}
              else{
                Serial.println("OOOOOOOO");
                Serial.println("You did it!");
                right_count += 1;}
            // breaks the IF loop when pattern successfully entered
            break;}
            else {
              // prints if a non-right gesture is detected and resets all counts
            Serial.println("Wrong McWrongface");
            Serial.println("XXXXXXXX");
            up_count = 0;
            down_count = 0;
            left_count = 0;
            right_count = 0;}
        // breaks the GESTURE_RIGHT loop
        break;

      default:
        // ignore
        break;
    }
  }
}
