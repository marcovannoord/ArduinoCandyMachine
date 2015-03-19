
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