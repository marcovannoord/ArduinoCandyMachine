// Taking care of some special events.
void keypadEvent(KeypadEvent key){
	switch (keypad.getState()){
	case PRESSED:
		previousMillis = millis();
		if (key == '#') {
			digitalWrite(ledPin, !digitalRead(ledPin));
			ledPin_state = digitalRead(ledPin);        // Remember LED state, lit or unlit.
		}
		else if (key == '0'){
			inputAccessCode(0);
		}
		else if (key == '1'){
			selectedColumn = 1;
			inputAccessCode(1);
		}
		else if (key == '2'){
			selectedColumn = 2;
			inputAccessCode(2);
		}
		else if (key == '3'){
			selectedColumn = 3;
			inputAccessCode(3);
		}
		else if (key == '4'){
			selectedColumn = 4;
			inputAccessCode(4);
		}
		else if (key == '5'){
			selectedColumn = 5;
			inputAccessCode(5);
		}
		else if (key == '6'){
			selectedColumn = 6;
			inputAccessCode(6);
		}
		else if (key == '7'){
			selectedColumn = 7;
			inputAccessCode(7);
			//ArduinoStateMachine.transitionTo(Processing); 
		}
		else if (key == '8'){
			selectedColumn = 8;
			inputAccessCode(8);
			//ArduinoStateMachine.transitionTo(MotorTest);
		}
		else if (key == '9'){
			selectedColumn = 9;
			inputAccessCode(9);
			//ArduinoStateMachine.transitionTo(Standby);
		}
		else if (key == 'A'){
			selectedRow = 1;
			displayWriteRow('A');
		}
		else if (key == 'B'){
			selectedRow = 2;
			displayWriteRow('B');
			ArduinoStateMachine.transitionTo(Wifi);
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

void keyTimeout(){//needs to clear everything, since we can't go to standbyState again
	selectedColumn = 0;
	selectedRow = 0;
	accesscode = 0;
	enterednrs = 0;

	lcd.setCursor(0, 1);
	lcd.print("          ");
}

void inputAccessCode(int nr){
	Serial.println(nr);
	switch (enterednrs){
	case 0:
		accesscode += nr * 100000;
		break;
	
	case 1:
		accesscode += nr * 10000;
		break;
	
	case 2:
		accesscode += nr * 1000;
		break;
	case 3:
		accesscode += nr * 100;
		break;
	case 4:
		accesscode += nr * 10;
		break;
	case 5:
		accesscode += nr;
		ArduinoStateMachine.transitionTo(Wifi);
		break;
	}
	enterednrs++;
	Serial.println(accesscode);
}