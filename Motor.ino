void motorStartState(){
	delay(200); //200ms to make fully sure motor isn't already running, thus ruining the
	digitalWrite(motorPin, HIGH);
}
void motorTurningState(){
	//motor should be running while in this state
	checkKeyboard(); //checkKeyboard only here for testing purposes; no keyboard entry necessary during handout
}
void motorStopState(){
	digitalWrite(motorPin, LOW);
}


//Interrupt routine that gets called when a motor did a full rotation. Be careful not to put any time-hogging stuff in it!
void motorStop(){

	if (ArduinoStateMachine.isInState(MotorTest)){
		digitalWrite(ledPin, !digitalRead(ledPin)); //toggle led to show the motor just rotated
		ArduinoStateMachine.immediateTransitionTo(Standby); //TODO: might not be safe; will always transfer to Standby, even if motor is not running?
		//UPDATE: Fixed, now checking if in state where motor can run (maybe add other states where motor might run?)
	}
}
