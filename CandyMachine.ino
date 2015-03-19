/* @file EventSerialKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates using the KeypadEvent.
|| #
*/
#include <Keypad.h>
#include <FiniteStateMachine.h>
#define NUMBER_OF_STATES 3
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
	{ '1', '2', '3', 'A' },
	{ '4', '5', '6', 'B' },
	{ '7', '8', '9', 'C' },
	{ '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 5, 4, 3, 2 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 9, 8, 7, 6 }; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
byte ledPin = 13;
byte motorPin = 12;

boolean blink = false;
boolean ledPin_state;

State Standby = State(standbyState);
State Processing = State(processingState);
State MotorTest = State(motorTestState);

FSM ArduinoStateMachine = FSM(Standby);

void setup(){
	Serial.begin(9600);
	pinMode(ledPin, OUTPUT);              // Sets the digital pin as output.
	pinMode(motorPin, OUTPUT);				//dummy motor
	digitalWrite(ledPin, HIGH);           // Turn the LED on.
	ledPin_state = digitalRead(ledPin);   // Store initial LED state. HIGH when LED is on.
	keypad.addEventListener(keypadEvent); // Add an event listener for this keypad

}

void loop(){
	ArduinoStateMachine.update(); //starts the function that's part of the state
}

void standbyState(){
	checkKeyboard();
}
void processingState(){
	delay(2000);
	ArduinoStateMachine.transitionTo(Standby);
}
void motorTestState(){
	digitalWrite(motorPin, HIGH);
	//delay(1000);
	digitalWrite(motorPin, LOW);
	//ArduinoStateMachine.transitionTo(Standby);
	checkKeyboard();
}

//function that reads does some debugging and show-off for the keyboard
void checkKeyboard(){
	char key = keypad.getKey(); //vital to the workings of the keyboard

	if (key) {
		Serial.println(key);
	}
	if (blink){
		digitalWrite(ledPin, !digitalRead(ledPin));    // Change the ledPin from Hi2Lo or Lo2Hi.
		delay(100);
	}
}

// Taking care of some special events.
void keypadEvent(KeypadEvent key){
	switch (keypad.getState()){
	case PRESSED:
		if (key == '#') {
			digitalWrite(ledPin, !digitalRead(ledPin));
			ledPin_state = digitalRead(ledPin);        // Remember LED state, lit or unlit.
		}
		else if (key == '5'){
			ArduinoStateMachine.transitionTo(Processing);
		}
		else if (key == '1'){
			ArduinoStateMachine.transitionTo(MotorTest);
		}
		else if (key == '2'){
			ArduinoStateMachine.transitionTo(Standby);
		}
		break;

	case RELEASED:
		if (key == '*') {
			digitalWrite(ledPin, ledPin_state);    // Restore LED state from before it started blinking.
			blink = false;
		}
		break;

	case HOLD:
		if (key == '*') {
			blink = true;    // Blink the LED when holding the * key.
		}
		break;
	}
}