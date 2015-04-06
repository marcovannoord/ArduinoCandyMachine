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
#include <LiquidCrystal.h>
#include <avr/eeprom.h>
#include "ESP8266.h"

#define KEYTIMEOUT 5000
#define MOTORTIMEOUT 4000
#define PRICEOFFSET 50
#define PRODUCT_AMOUNT 40

//settings for the WIFI-module on Serial1
#define SSID        "Free WiFi"
#define PASSWORD    "jemoeder"
#define HOST_NAME   "192.168.0.5"
#define HOST_PORT   (80)

ESP8266 wifi(Serial1);

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

byte inventory[PRODUCT_AMOUNT]; //stores the amount of inventory left, here we have 4 rows of 10 items each

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
byte ledPin = 13;
byte motorPin = 12;

byte selectedRow = 0;
byte selectedColumn = 0;

long accesscode = 0;
int enterednrs = 0;

boolean blink = false;
boolean ledPin_state;

State Standby = State(standbyEnterState, standbyState, standbyExitState);
State Processing = State(processingState);
State MotorTest = State(motorStartState, motorTurningState, motorExitState);
State Wifi = State(wifiState);

FSM ArduinoStateMachine = FSM(Standby);

unsigned long previousMillis = 0;        // will store last time LED was updated

uint16_t prices[40] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(53, 52, 50, 48, 46, 44);

void setup(){
	delay(200); //delay because VS is too slow?
	Serial.begin(9600);
	Serial.println("start");
	pinMode(ledPin, OUTPUT);              // Sets the digital pin as output.
	pinMode(motorPin, OUTPUT);				//dummy motor
	digitalWrite(ledPin, HIGH);           // Turn the LED on.
	ledPin_state = digitalRead(ledPin);   // Store initial LED state. HIGH when LED is on.
	readEEPROM(); //reading the inventory and prices
	//updatePrices //TODO: get prices from internet
	keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
	attachInterrupt(0, motorStop, RISING); //interrupt for full rotation of motor
	// set up the LCD's number of columns and rows: 
	lcd.begin(16, 2);
	setupWifi();
}

void loop(){
	ArduinoStateMachine.update(); //starts the function that's part of the state
}

void setupWifi(){

	Serial.print("FW Version:");
	Serial.println(wifi.getVersion().c_str());

	if (wifi.setOprToStationSoftAP()) {
	//	Serial.print("to station + softap ok\r\n");
	}
	else {
		Serial.print("to station + softap err\r\n");
	}

	if (wifi.joinAP(SSID, PASSWORD)) {
	//	Serial.print("Join AP success\r\n");

		Serial.print("IP:");
		Serial.println(wifi.getLocalIP().c_str());
	}
	else {
		Serial.print("Join AP failure\r\n");
	}

	if (wifi.disableMUX()) {
	//	Serial.print("single ok\r\n");
	}
	else {
	//	Serial.print("single err\r\n");
	}

	//Serial.print("setup end\r\n");
}

