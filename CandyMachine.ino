/* @file CandyMachine.ino
|| @version 1.0
|| @author Marco van Noord
|| @contact marcovannoord@gmail.com
||
|| @description
|| | runs a Candymachine.
|| #
*/
#include <Keypad.h>
#include <FiniteStateMachine.h>
#include <EEPROM.h>

const byte ROWS = 4; //four rows from keyboard
const byte COLS = 4; //four cols from keyboard
char keys[ROWS][COLS] = {
	{ '1', '2', '3', 'A' },
	{ '4', '5', '6', 'B' },
	{ '7', '8', '9', 'C' },
	{ '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 5, 4, 3, 10 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 9, 8, 7, 6 }; //connect to the column pinouts of the keypad

byte inventory[40]; //stores the amount of inventory left, here we have 4 rows of 10 items each

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
byte ledPin = 13;
byte motorPin = 12;

byte selectedRow = 0;
byte selectedColumn = 0;

boolean blink = false;
boolean ledPin_state;

State Standby = State(standbyEnterState, standbyState, standbyExitState);
State Processing = State(processingState);
State MotorTest = State(motorStartState, motorTurningState, motorStopState);

FSM ArduinoStateMachine = FSM(Standby);

void setup(){
	delay(200); //delay because VS is too slow?
	Serial.begin(9600);
	pinMode(ledPin, OUTPUT);              // Sets the digital pin as output.
	pinMode(motorPin, OUTPUT);				//dummy motor
	digitalWrite(ledPin, HIGH);           // Turn the LED on.
	ledPin_state = digitalRead(ledPin);   // Store initial LED state. HIGH when LED is on.
	readEEPROM(); //reading the inventory and prices
	//updatePrices //TODO: get prices from internet
	keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
	attachInterrupt(0, motorStop, RISING); //interrupt for full rotation of motor
}

void loop(){
	ArduinoStateMachine.update(); //starts the function that's part of the state

}



