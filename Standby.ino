void standbyEnterState(){
	selectedColumn = 0; //reset row and column
	selectedRow = 0;
}
//this is the "normal" state, if no other state preferred, this state should be active. 
void standbyState(){
	checkKeyboard();
	if (selectedRow != 0 && selectedColumn != 0){
		ArduinoStateMachine.transitionTo(Processing);
	}
}
void standbyExitState(){}
