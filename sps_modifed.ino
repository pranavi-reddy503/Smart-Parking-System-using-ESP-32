#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// ================= LCD SETUP =================
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change to 0x3F if LCD not showing

// ================= DFPlayer SETUP =================
SoftwareSerial mySerial(16, 17); // RX=16, TX=17
DFRobotDFPlayerMini myDFPlayer;

// ================= IR SENSOR PINS =================
int irPins[4] = {32, 33, 25, 26}; // IR sensor pins
int slotStatus[4];                // HIGH = empty, LOW = occupied

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  Wire.begin();

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Smart Parking");
  delay(1500);
  lcd.clear();

  // Initialize DFPlayer
  lcd.setCursor(0,0);
  lcd.print("Init DFPlayer...");
  if (!myDFPlayer.begin(mySerial)) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("DFPlayer Error!");
    Serial.println("DFPlayer Mini not detected!");
    while(true);
  }
  myDFPlayer.volume(25); // 0–30
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DFPlayer Ready");
  delay(1000);

  // Initialize IR sensor pins
  for(int i=0; i<4; i++){
    pinMode(irPins[i], INPUT);
  }

  lcd.clear();
  lcd.print("System Ready");
  Serial.println("System Ready!");
  delay(1000);
}

void loop() {
  int emptyCount = 0;

  // Read all IR sensors
  for(int i=0; i<4; i++){
    slotStatus[i] = digitalRead(irPins[i]); // HIGH = empty
    if(slotStatus[i] == HIGH) emptyCount++;
  }

  // ================= LCD DISPLAY =================
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Empty Slots: ");
  lcd.print(emptyCount);
  lcd.setCursor(0,1); // second line for slot info

  // ================= AUDIO & DISPLAY LOGIC =================
  int audioIndex = 0;

  // --------- All slots full ---------
  if(emptyCount == 0){
    lcd.print("Parking Full");
    audioIndex = 1; // 0001.mp3
  }
  // --------- All slots empty ---------
  else if(emptyCount == 4){
    lcd.print("All slots empty");
    audioIndex = 16; // 0016.mp3
  }
  // --------- Two slots empty ---------
  else if(emptyCount == 2){
    if(slotStatus[0]==HIGH && slotStatus[1]==HIGH){
      lcd.print("Slot 1 & 2 empty");
      audioIndex = 6;
    } else if(slotStatus[0]==HIGH && slotStatus[2]==HIGH){
      lcd.print("Slot 1 & 3 empty");
      audioIndex = 7;
    } else if(slotStatus[0]==HIGH && slotStatus[3]==HIGH){
      lcd.print("Slot 1 & 4 empty");
      audioIndex = 8;
    } else if(slotStatus[1]==HIGH && slotStatus[2]==HIGH){
      lcd.print("Slot 2 & 3 empty");
      audioIndex = 9;
    } else if(slotStatus[1]==HIGH && slotStatus[3]==HIGH){
      lcd.print("Slot 2 & 4 empty");
      audioIndex = 10;
    } else if(slotStatus[2]==HIGH && slotStatus[3]==HIGH){
      lcd.print("Slot 3 & 4 empty");
      audioIndex = 11;
    }
  }
  // --------- Three slots empty ---------
  else if(emptyCount == 3){
    if(slotStatus[0]==LOW) { lcd.print("Slots 2,3,4"); audioIndex=15; }
    else if(slotStatus[1]==LOW) { lcd.print("Slots 1,3,4"); audioIndex=14; }
    else if(slotStatus[2]==LOW) { lcd.print("Slots 1,2,4"); audioIndex=13; }
    else if(slotStatus[3]==LOW) { lcd.print("Slots 1,2,3"); audioIndex=12; }
  }
  // --------- Single slot empty ---------
  else if(emptyCount == 1){
    for(int i=0;i<4;i++){
      if(slotStatus[i]==HIGH){
        lcd.print("Slot ");
        lcd.print(i+1);
        lcd.print(" empty");
        audioIndex = i+2; // 0002.mp3 → Slot1, 0003.mp3 → Slot2, etc.
        break;
      }
    }
  }

  // Play the corresponding audio file
  if(audioIndex > 0){
    myDFPlayer.playMp3Folder(audioIndex);
    delay(3500); // Wait for the audio to play (adjust based on file length)
  }

  delay(3000); // Wait before next check
}
