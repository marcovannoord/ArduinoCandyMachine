void motorStartState(){
	delay(200); //200ms to make fully sure motor isn't already running, thus ruining the
	digitalWrite(12, HIGH);
	lcd.clear();
	lcd.print("Handing out");

}
void motorTurningState(){
	//motor should be running while in this state
	checkKeyboard(); //checkKeyboard only here for testing purposes; no keyboard maybe possible during turning, could keep motor turning!!
}
void motorExitState(){
	digitalWrite(getColMotorPin(), LOW);
	reduceStock();
	lcd.noBlink();
}


//Interrupt routine that gets called when a motor did a full rotation. Be careful not to put any time-hogging stuff in it!
void motorStop(){

	if (ArduinoStateMachine.isInState(MotorTest)){
		digitalWrite(ledPin, !digitalRead(ledPin)); //toggle led to show the motor just rotated
		ArduinoStateMachine.immediateTransitionTo(Standby); //TODO: might not be safe; will always transfer to Standby, even if motor is not running?
		//UPDATE: Fixed, now checking if in state where motor can run (maybe add other states where motor might run?)
	}
}

//gets the pin that needs to be put LOW (since we're switching the positive side)
int getRowMotorPin(){
	return 1;
}

//gets the pin that needs to be put HIGH (since we're switching the negative side)
int getColMotorPin(){
	return 12;
}

void motorTimeout(){
	ArduinoStateMachine.transitionTo(Standby); //TODO: check if this always work, and also churn out some error
}
