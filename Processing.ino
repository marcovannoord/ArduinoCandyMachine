void processingState(){
	//Serial.print(selectedColumn);
	//Serial.print(".");
	//Serial.println(selectedRow);
	lcd.clear();
	//checking if row isn't empty
	int inventorySelected = inventory[matrixToInt()];
	if (inventorySelected == 0){
		
		lcd.print("No product");
	}
	else{
		lcd.print(" Processing...");
		lcd.blink();
		delay(2000);
		Serial.println(inventorySelected);
		ArduinoStateMachine.transitionTo(MotorTest);
		return;// don't forget return, otherwise function will continue towards next transition.
	}
	delay(2000);
	ArduinoStateMachine.transitionTo(Standby);
}
