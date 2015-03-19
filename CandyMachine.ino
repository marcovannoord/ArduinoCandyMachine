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

byte rowPins[ROWS] = { 5, 4, 3, 10 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 9, 8, 7, 6 }; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
byte ledPin = 13;
byte motorPin = 12;

boolean blink = false;
boolean ledPin_state;

State Standby = State(standbyState);
State Processing = State(processingState);
State MotorTest = State(motorStartState, motorTestState, motorStopState);

FSM ArduinoStateMachine = FSM(Standby);

void setup(){
	Serial.begin(9600);
	pinMode(ledPin, OUTPUT);              // Sets the digital pin as output.
	pinMode(motorPin, OUTPUT);				//dummy motor
	digitalWrite(ledPin, HIGH);           // Turn the LED on.
	ledPin_state = digitalRead(ledPin);   // Store initial LED state. HIGH when LED is on.
	keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
	attachInterrupt(0, motorStop, RISING); //interrupt for full rotation of motor
}

void loop(){
	ArduinoStateMachine.update(); //starts the function that's part of the state
}
//this is the "normal" state, if no other state preferred, this state should be active. 
void standbyState(){
	checkKeyboard();
}
void processingState(){
	delay(2000);
	ArduinoStateMachine.transitionTo(Standby);
}

void motorStartState(){
	delay(200); //200ms to make fully sure motor isn't already running, thus ruining the
	digitalWrite(motorPin, HIGH);
}
void motorTestState(){
	
	//delay(1000);
	
	//ArduinoStateMachine.transitionTo(Standby);
	checkKeyboard();
}
void motorStopState(){
	digitalWrite(motorPin, LOW);
}


//Interrupt routine that gets called when a motor did a full rotation. Be careful not to put any time-hogging stuff in it!
void motorStop(){ 
	
	if (ArduinoStateMachine.isInState(MotorTest)){
		digitalWrite(ledPin, !digitalRead(ledPin)); //toggle led to show the motor just rotated
		ArduinoStateMachine.immediateTransitionTo(Standby); //TODO: might not be safe; will always transfer to Standby, even if motor is not running?
															//UPDATE: Fixed, now checking if in state where motor can run (maybe add other states where motor might run?)
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