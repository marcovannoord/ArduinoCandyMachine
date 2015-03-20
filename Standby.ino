void standbyEnterState(){
	selectedColumn = 0; //reset row and column
	selectedRow = 0;
	lcd.clear();
	lcd.print("Kies een product");
	digitalWrite(ledPin, !digitalRead(ledPin));
	//starting key-timeout logics
}
//this is the "normal" state, if no other state preferred, this state should be active. 
void standbyState(){
	if (millis() - previousMillis >= KEYTIMEOUT){
		(keyTimeout);
	}
	checkKeyboard();
	if (selectedRow != 0 && selectedColumn != 0){
		ArduinoStateMachine.transitionTo(Processing);
	}
}
void standbyExitState(){
}



