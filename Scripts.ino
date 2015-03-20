void readEEPROM(){
	//first let's read the eeprom
	for (int i = 0; i < sizeof(inventory); i++){
		inventory[i] = EEPROM.read(i); //read EEPROM at address i
		//Serial.print(i);
		//Serial.print('.');
		//Serial.println(inventory[i]);
		if (inventory[i] == 255) {//we can't have 255 items in our inventory, so we'll assume we have none
			EEPROM.write(i, 0);
			inventory[i] = 0;
		}
	}
	EEPROM.write(1, 10);//some fake product, TODO: Remove
}

int matrixToInt(){
	int rowValue = (selectedRow - 1) * 10;
	int returnValue = rowValue + selectedColumn;
	//Serial.println(returnValue);
	return returnValue;
}

void reduceStock(){
	//TODO: Perhaps to write to EEPROM and then fully reload from EEPROM?
	inventory[matrixToInt()]--; //reduce stock in memory
	EEPROM.write(matrixToInt(),inventory[matrixToInt()]);
}