// Taking care of some special events.
void keypadEvent(KeypadEvent key){
	switch (keypad.getState()){
	case PRESSED:
		if (key == '#') {
			digitalWrite(ledPin, !digitalRead(ledPin));
			ledPin_state = digitalRead(ledPin);        // Remember LED state, lit or unlit.
		}
		else if (key == '1'){
			selectedColumn = 1;
			displayWriteCol(selectedColumn);
		}
		else if (key == '2'){
			selectedColumn = 2;
			displayWriteCol(selectedColumn);
		}
		else if (key == '3'){
			selectedColumn = 3;
			displayWriteCol(selectedColumn);
		}
		else if (key == '4'){
			selectedColumn = 4;
			displayWriteCol(selectedColumn);
		}
		else if (key == '5'){
			selectedColumn = 5;
			displayWriteCol(selectedColumn);
		}
		else if (key == '6'){
			selectedColumn = 6;
			displayWriteCol(selectedColumn);
		}
		else if (key == '7'){
			selectedColumn = 7;
			displayWriteCol(selectedColumn);
			ArduinoStateMachine.transitionTo(Processing); 
		}
		else if (key == '8'){
			selectedColumn = 8;
			displayWriteCol(selectedColumn);
			ArduinoStateMachine.transitionTo(MotorTest);
		}
		else if (key == '9'){
			selectedColumn = 9;
			displayWriteCol(selectedColumn);
			ArduinoStateMachine.transitionTo(Standby);
		}
		else if (key == 'A'){
			selectedRow = 1;
			displayWriteRow('A');
		}
		else if (key == 'B'){
			selectedRow = 2;
			displayWriteRow('B');
		}
		else if (key == 'C'){
			selectedRow = 3;
			displayWriteRow('C');
		}
		else if (key == 'D'){
			selectedRow = 4;
			displayWriteRow('D');
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



//function that reads does some debugging and show-off for the keyboard
void checkKeyboard(){
	char key = keypad.getKey(); //vital to the workings of the keyboard

	if (key) {
		//Serial.println(key);
	}
	if (blink){
		digitalWrite(ledPin, !digitalRead(ledPin));    // Change the ledPin from Hi2Lo or Lo2Hi.
		delay(100);
	}
}

void displayWriteRow(char input){
	lcd.setCursor(5, 1); // bottom left
	lcd.write(input);
}
void displayWriteCol(int input){
	lcd.setCursor(6, 1); // bottom left
	lcd.print(input);
}
