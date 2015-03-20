void processingState(){
	//Serial.print(selectedColumn);
	//Serial.print(".");
	//Serial.println(selectedRow);
	//checking if row isn't empty
	int inventorySelected = inventory[matrixToInt()];
	if (inventorySelected == 0){
		Serial.println("sorry, ran out of this product");
	}
	else{
		Serial.println(inventorySelected);
		ArduinoStateMachine.transitionTo(MotorTest);
		return;// don't forget return, otherwise function will continue towards next transition.
	}
	delay(2000);
	ArduinoStateMachine.transitionTo(Standby);
}
