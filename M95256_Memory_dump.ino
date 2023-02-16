#include <SPI.h>

int addr = 0x030000;

const byte WRITE_ENABLE = B00000110;
const byte WRITE_DISABLE = B00000100;
const byte READ_STATUS_REGISTER = B00000101;
const byte WRITE_STATUS_REGISTER = B00000001;
const byte READ = B00000011;
const byte WRITE = B00000010;

void setup() {
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8); // 2/4/8/16/32/64/128
  SPI.setBitOrder(MSBFIRST); // In datasheet

  Serial.begin(9600);

  delay(3000);
}

void writeEnable(){
  digitalWrite(SS, LOW);

  uint8_t result = 0;
  result = SPI.transfer(WRITE_ENABLE); // Instruction ID

  result = 0;
  result = SPI.transfer((uint8_t)0);

  digitalWrite(SS, HIGH);

  delay(10);
}

void writeDisable(){
  digitalWrite(SS, LOW);

  uint8_t result = 0;
  result = SPI.transfer(WRITE_DISABLE); // Instruction ID

  result = 0;
  result = SPI.transfer((uint8_t)0);

  digitalWrite(SS, HIGH);

  delay(10);
}

uint8_t readStatusRegister(){
  digitalWrite(SS, LOW);

  uint8_t result = 0;
  result = SPI.transfer(READ_STATUS_REGISTER); // Instruction ID

  result = 0;
  result = SPI.transfer(0);

  digitalWrite(SS, HIGH);

  delay(10);

  return result;
}

void writeStatusRegister(uint8_t data){
  //Not Validated
  writeEnable();

  digitalWrite(SS, LOW);

  uint8_t result = 0;
  result = SPI.transfer(WRITE_STATUS_REGISTER); // Instruction ID

  result = 0;
  result = SPI.transfer(data);

  digitalWrite(SS, HIGH);

  delay(10);

  writeDisable();
}

uint8_t readMemoryArray(uint8_t upper, uint8_t lower){
  digitalWrite(SS, LOW);

  uint8_t result = 0;
  result = SPI.transfer(READ); // Instruction ID

  result = 0;
  result = SPI.transfer(upper);

  result = 0;
  result = SPI.transfer(lower);

  result = 0;
  result = SPI.transfer(0);

  digitalWrite(SS, HIGH);

  delay(10);

  return result;
}

void writeMemoryArray(uint8_t upper, uint8_t lower, uint8_t data){

  writeEnable();

  digitalWrite(SS, LOW);

  uint8_t result = 0;
  result = SPI.transfer(WRITE); // Instruction ID

  result = 0;
  result = SPI.transfer(upper);

  result = 0;
  result = SPI.transfer(lower);

  result = 0;
  result = SPI.transfer(data);

  digitalWrite(SS, HIGH);

  delay(10);

  writeDisable();
}

void loop() {
  
  Serial.println("\nStart");

  //===========================================================================

  for(int i=0;i<128;i++){
    for(int j=0;j<256;j++){
      Serial.print(readMemoryArray(i, j), HEX);
    }
  }

  //============================================================================

  Serial.println("END");

  SPI.end();

  delay(100000000000000000000000000);

}
