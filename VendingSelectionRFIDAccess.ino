/*
 * by: Kirollos Gerges
 */
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
char userChoice[2];
bool flag = false;
#include <LiquidCrystal.h>
#include <Keypad.h>

const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//-------------Keypad--------------------//
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {0, 2, 19, 18}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {17, 16, 15, 14}; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//--------------------------------------//

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  //Serial.println("Scan your");
  //Serial.println();

  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Scan your");
  lcd.setCursor(0,1);
  lcd.print("card...");

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "83 66 60 1A" || content.substring(1) == "04 5D 3D 82 63 62 80") //change here the UID of the card/cards that you want to give access
  {

    lcd.clear();
    //lcd.setCursor(0,0);
    lcd.print("Access granted");
    //Serial.println("Authorized access");
    //Serial.println();
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Select drink");
    lcd.setCursor(0,1);
    lcd.print("from menu..");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tequila | Vodka ");
    lcd.setCursor(0,1);
    lcd.print("  A1    |   A2 ");
    delay(3000);

  while(flag == false){

      lcd.clear();
      lcd.setCursor(0,0);

      for(int i = 0; i < 2; i++){
      
         char key = keypad.waitForKey();
        //char key = keypad.getKey();// Read the key
        
        // Print if key pressed
        if (key){
          Serial.print("Key Pressed : ");
          Serial.println(key);
          userChoice[i] = key;
          lcd.print(key);
          delay(100);
        }
      }
  
    if(userChoice[0] == 'A' && userChoice[1] == '1'){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("You Chose tequila");
      lcd.setCursor(0,1);
      lcd.print("Making the drink..");
      flag = true;
    }
    else if(userChoice[0] == 'A' && userChoice[1] == '2'){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("You Chose vodka");
      lcd.setCursor(0,1);
      lcd.print("Making the drink..");
      flag = true;

    }
    else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Invalid Choice");
      lcd.setCursor(0,1);
      lcd.print("try again..");
      delay(3000);

    }
  }

  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Access denied");
    lcd.setCursor(0,1);
    lcd.print("Try again..");
    delay(3000);
  }
} 
