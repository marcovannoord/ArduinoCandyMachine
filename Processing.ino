void processingState(){
	Serial.print(selectedColumn);
	Serial.print(".");
	Serial.println(selectedRow);
	//checking if row isn't empty

	delay(2000);
	ArduinoStateMachine.transitionTo(MotorTest);
}
