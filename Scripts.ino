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
	writePrice(1);
	readPrice(1);
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

void writePrice(int number){
	eeprom_write_word((uint16_t*)50, 200); //A0
	eeprom_write_word((uint16_t*)52, 200); //A1
	eeprom_write_word((uint16_t*)54, 200); //A2
	eeprom_write_word((uint16_t*)56, 200); //A3
	eeprom_write_word((uint16_t*)58, 200); //A4
	eeprom_write_word((uint16_t*)60, 200); //A5
	eeprom_write_word((uint16_t*)62, 200); //A6
	eeprom_write_word((uint16_t*)64, 200); //A7
	eeprom_write_word((uint16_t*)66, 200); //A8
	eeprom_write_word((uint16_t*)68, 200); //A9

	eeprom_write_word((uint16_t*)70, 200); //B0
	eeprom_write_word((uint16_t*)72, 200); //B1
	eeprom_write_word((uint16_t*)74, 200); //B2
	eeprom_write_word((uint16_t*)76, 200); //B3
	eeprom_write_word((uint16_t*)78, 200); //B4
	eeprom_write_word((uint16_t*)80, 200); //B5
	eeprom_write_word((uint16_t*)82, 200); //B6
	eeprom_write_word((uint16_t*)84, 200); //B7
	eeprom_write_word((uint16_t*)86, 200); //B8
	eeprom_write_word((uint16_t*)88, 200); //B9

	eeprom_write_word((uint16_t*)90, 200); //C0
	eeprom_write_word((uint16_t*)92, 200); //C1
	eeprom_write_word((uint16_t*)94, 200); //C2
	eeprom_write_word((uint16_t*)96, 200); //C3
	eeprom_write_word((uint16_t*)98, 200); //C4
	eeprom_write_word((uint16_t*)100, 200); //C5
	eeprom_write_word((uint16_t*)102, 200); //C6
	eeprom_write_word((uint16_t*)104, 200); //C7
	eeprom_write_word((uint16_t*)106, 200); //C8
	eeprom_write_word((uint16_t*)108, 200); //C9

	eeprom_write_word((uint16_t*)110, 200); //D0
	eeprom_write_word((uint16_t*)112, 200); //D1
	eeprom_write_word((uint16_t*)114, 200); //D2
	eeprom_write_word((uint16_t*)116, 200); //D3
	eeprom_write_word((uint16_t*)118, 200); //D4
	eeprom_write_word((uint16_t*)120, 200); //D5
	eeprom_write_word((uint16_t*)122, 200); //D6
	eeprom_write_word((uint16_t*)124, 200); //D7
	eeprom_write_word((uint16_t*)126, 200); //D8
	eeprom_write_word((uint16_t*)128, 200); //D9
	
}
word readPrice(int number){
	Serial.println(eeprom_read_word((uint16_t*)50)); //A0
	eeprom_read_word((uint16_t*)52); //A1
	eeprom_read_word((uint16_t*)54); //A2
	eeprom_read_word((uint16_t*)56); //A3
	eeprom_read_word((uint16_t*)58); //A4
	eeprom_read_word((uint16_t*)60); //A5
	eeprom_read_word((uint16_t*)62); //A6
	eeprom_read_word((uint16_t*)64); //A7
	eeprom_read_word((uint16_t*)66); //A8
	eeprom_read_word((uint16_t*)68); //A9
}
