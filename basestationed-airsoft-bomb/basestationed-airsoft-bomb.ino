#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <TM1637Display.h>


#define CLK 2//pins definitions for TM1637 and can be changed to other ports
#define DIO 3

 
#define RST_PIN         9   //MFRC522 pins    
#define SS_PIN          10  

  const uint8_t SEG_DONE[] = {
	SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_C | SEG_E | SEG_G,                           // n
	SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
	};

  const uint8_t SEG_START[] = {
  SEG_G, SEG_G, SEG_G, SEG_G
	};

  TM1637Display display(CLK, DIO);

  int time = 0; // time in seconds that game runs
  int viive = 850; //time between countdown going down.
  int buzz = 500; // time that piezo is active
  MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
 
void setup(){
  
  pinMode(5, INPUT); //DIP3
  pinMode(6, INPUT); //DIP2
  pinMode(7, INPUT); //DIP1
  pinMode(4, OUTPUT); //PIEZO

  display.clear();
  display.setBrightness(4);
  display.showNumberDec(1234, false);
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init(); 

            // Add 330 to any time value this is endtime counter that increases numberflow and sound effects speed during last minute of game time
    if (digitalRead(5) == LOW && digitalRead(6) == LOW && digitalRead(7) == LOW){ 
      // O O O
    time = 570;  //5 minutes time untill "explosion"
  }
    if (digitalRead(5) == HIGH && digitalRead(6) == HIGH && digitalRead(7) == HIGH){
      // I I I 
    time = 870; //10 minutes time untill "explosion"
  }
    if (digitalRead(5) == HIGH && digitalRead(6) == HIGH && digitalRead(7) == LOW){
    // pos3
    time = 1170; //15 minutes time untill "explosion"
  }
    if (digitalRead(5) == LOW && digitalRead(6) == HIGH && digitalRead(7) == HIGH){
    // pos4
    // time = 365;
  }
    if (digitalRead(5) == HIGH && digitalRead(6) == LOW && digitalRead(7) == LOW){
    // pos5
    // time = 365;
  }
      if (digitalRead(5) == LOW && digitalRead(6) == LOW && digitalRead(7) == HIGH){
    // pos6
    // time = 365;
  }
    if (digitalRead(5) == LOW && digitalRead(6) == HIGH && digitalRead(7) == LOW){
    // pos7
    // time = 365;
  }
    if (digitalRead(5) == HIGH && digitalRead(6) == LOW && digitalRead(7) == HIGH){
    // pos8
    // time = 365;
  }
   time = 1170; // MUISTA POISTAA!!!!
}

uint8_t buf[10]= {};
MFRC522::Uid id;
MFRC522::Uid id2;
bool is_card_present = false;
uint8_t control = 0x00;
void PrintHex(uint8_t *data, uint8_t length) // prints 8-bit data in hex with leading zeroes
{
     char tmp[16];
       for (int i=0; i<length; i++) { 
         sprintf(tmp, "0x%.2X",data[i]); 
         Serial.print(tmp); Serial.print(" ");
       }
}
 
//*****************************************************************************************//
 
void cpid(MFRC522::Uid *id){
  memset(id, 0, sizeof(MFRC522::Uid));
  memcpy(id->uidByte, mfrc522.uid.uidByte, mfrc522.uid.size);
  id->size = mfrc522.uid.size;
  id->sak = mfrc522.uid.sak;
}
 
void loop(){



  start:


  display.setSegments(SEG_START);
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  MFRC522::StatusCode status;
 
    // Look for new cards
  if ( !mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( !mfrc522.PICC_ReadCardSerial()) {
    return;
  }
 
    bool result = true;
  uint8_t buf_len=4;
  cpid(&id);
  Serial.print("NewCard ");
  PrintHex(id.uidByte, id.size);
  Serial.println("");
 
    while(true){


if (time == 0){
  goto end;
}
display.setBrightness(7);
digitalWrite(4, HIGH);
display.showNumberDec(time, false); 
delay(viive);
time --;
tone(4, 800, buzz);
if (time == 330){ //end timer increases countdown speed aprox one minute
  viive = 50;
  buzz = 100;
}




      

    control=0;
    for(int i=0; i<3; i++){
      if(!mfrc522.PICC_IsNewCardPresent()){
        if(mfrc522.PICC_ReadCardSerial()){
          //Serial.print('a');
          control |= 0x16;
        }
        if(mfrc522.PICC_ReadCardSerial()){
          //Serial.print('b');
          control |= 0x16;
        }
        //Serial.print('c');
          control += 0x1;
      }
      //Serial.print('d');
      control += 0x4;
    }
     
    //Serial.println(control);
    if(control == 13 || control == 14){
      //card is still there
    } else {
      break;
    }
  }
  Serial.println("CardRemoved");

  delay(100); //change value if you want to read cards faster
 
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  if (time > 0){
    goto start;
  }
  end:
  display.setSegments(SEG_DONE);
  if (time == 0){
    goto end;
  }
}