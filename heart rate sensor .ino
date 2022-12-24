// This example shows various featues of the library for LCD with 16 chars and 2 lines.

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#define USE_ARDUINO_INTERRUPTS true // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h> // Includes the PulseSensorPlayground Library.

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const int PulseWire = 0; // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13; // The on-board Arduino LED, close to PIN 13.
int Threshold = 550; // Determine which Signal to "count as a beat" and which to ignore.
// Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
// Otherwise leave the default "550" value.
 
PulseSensorPlayground pulseSensor; // Creates an instance of the PulseSensorPlayground object called "pulseSensor"



void setup() {
  int error;

  Serial.begin(115200);
  Serial.println("LCD...");
  lcd.begin(16, 2);  // initialize the lcd

  // See http://playground.arduino.cc/Main/I2cScanner how to test for a I2C device.
  Wire.begin();
  Wire.beginTransmission(0x27);
  // Configure the PulseSensor object, by assigning our variables to it.
pulseSensor.analogInput(PulseWire);
pulseSensor.blinkOnPulse(LED13); //auto-magically blink Arduino's LED with heartbeat.
pulseSensor.setThreshold(Threshold);
 
// Double-check the "pulseSensor" object was created and "began" seeing a signal.
if (pulseSensor.begin()) {
Serial.println("We created a pulseSensor Object !"); //This prints one time at Arduino power-up, or on Arduino reset.
lcd.setCursor(0,0);
lcd.print(" Heart Rate Monitor");
 
}
}  // setup()


void loop() {
  delay(100);
  lcd.clear();
  lcd.home();
  lcd.setBacklight(255);
  lcd.print("Hello LCD");
  delay(1000);
  lcd.clear();
  lcd.home();

int myBPM = pulseSensor.getBeatsPerMinute(); // Calls function on our pulseSensor object that returns BPM as an "int".
// "myBPM" hold this BPM value now.
lcd.setCursor(0,0);
lcd.clear();
if (pulseSensor.sawStartOfBeat()) { // Constantly test to see if "a beat happened".
Serial.println("♥ A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
Serial.print("BPM: "); // Print phrase "BPM: "
Serial.println(myBPM); // Print the value inside of myBPM.
lcd.setCursor(0,0);
lcd.print("HeartBeat Happened !"); // If test is "true", print a message "a heartbeat happened".
lcd.setCursor(0,1);
lcd.print("BPM: "); // Print phrase "BPM: "
lcd.print(myBPM);
}
delay(2000); // considered best practice in a simple sketch.
}  // loop()
