void wifiState(){
	int location = retrieveLocation();
}
int retrieveLocation(){
	uint8_t buffer[1024] = { 0 };

	if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
		Serial.print("create tcp ok\r\n");
	}
	else {
		Serial.print("create tcp err\r\n");
	}

	char *hello = "GET /wp-content/plugins/candymachine/connection.php?secret=20406 HTTP/1.1\r\nHost: 192.168.0.5\r\nConnection: close\r\n\r\n";
	wifi.send((const uint8_t*)hello, strlen(hello));

	uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
	if (len > 0) {
		char wifiRow;
		char wifiCol;
		//Serial.print("Received:[");
		for (uint32_t i = 0; i < len; i++) {
			//Serial.print((char)buffer[i]);
			if ((char)buffer[i] == '#')
			{
				Serial.print((char)buffer[i + 1]);
				wifiRow = (char)buffer[i + 1];
				wifiCol = (char)buffer[i + 2];
				Serial.println((char)buffer[i + 2]);
			}
		}
		Serial.print("\r\n");
		tryFillRowCol(wifiRow, wifiCol);
	}
	else{
	//if nothing is retrieved, or some other error happened, return back to standby
	Serial.println("error retrieving");
	ArduinoStateMachine.transitionTo(Standby);
	}

}

void tryFillRowCol(char row, char col){

	int ia = col - '0';
	if (ia >= 0 && ia <= 9) //successfull
	{
		switch (row){
		case 'A':
			selectedRow = 1;
			break;
		case 'B':
			selectedRow = 2;
			break;		
		case 'C':
			selectedRow = 3;
			break;		
		case 'D':
			selectedRow = 4;
			break;
		default:
			ArduinoStateMachine.transitionTo(Standby);
		}
		selectedColumn = ia;
		ArduinoStateMachine.transitionTo(Processing);
	}
	else{
		ArduinoStateMachine.transitionTo(Standby);
	}
}

