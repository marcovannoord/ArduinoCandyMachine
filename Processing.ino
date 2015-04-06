void processingState(){
	Serial.print(selectedColumn);
	Serial.print(".");
	Serial.println(selectedRow);
	lcd.clear();
	//checking if row isn't empty
	int inventorySelected = inventory[matrixToInt()];
	double price = uintToDouble(prices[matrixToInt()]);
	if (inventorySelected == 0){
		
		lcd.print("No product");
	}
	else{
		lcd.print(" Processing...");
		lcd.setCursor(0, 1);
		lcd.print("price: E");
		lcd.print(price);
		lcd.blink();
		delay(1000);
		Serial.println(inventorySelected);
		ArduinoStateMachine.transitionTo(MotorTest);
		return;// don't forget return, otherwise function will continue towards next transition.
	}
	delay(2000); //impossible to get here
	ArduinoStateMachine.transitionTo(Standby);
}
