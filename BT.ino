#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

const int RX_PIN = 11;
const int TX_PIN = 12;
SoftwareSerial BTSerial(RX_PIN, TX_PIN);
#include <Keypad.h>

//---KEYPAD SETUP---
const byte ROW = 4;
const byte COL = 3;

char keymap[ROW][COL] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROW] = {9,8,7,6};
byte colPins[COL] = {5,4,3};

Keypad keypad = Keypad(makeKeymap(keymap), rowPins, colPins, ROW, COL);

//---LCD--
/*
RS = A1
Enable = A0
D4 = A5
D5 = A4
D6 = A3
D7 = A2
*/

LiquidCrystal lcd(A1, A0, A5, A4, A3, A2);

char snakeDirection;
byte incomingByte;
String score;

void setup()
{
  Serial.begin(9600);
  BTSerial.begin(38400);
   for(int i = 65; i <= 90; i++){
        BTSerial.print((char)i);
        delay(50);
      }
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("SNAKE!");
}

void loop()
{
  getDirection();
  readScore();

//  if(BTSerial.available() > 0){
//    incomingByte = BTSerial.read();
//    lcd.print(incomingByte);

//    if(incomingByte == 48){
//      for(int i = 65; i <= 90; i++){
//        BTSerial.print((char)i);
//        delay(50);
//      }
//    }
//  }

//  /delay(200);
}

void getDirection()
{
  snakeDirection = keypad.getKey(); //Read the key

  if(snakeDirection){
    Serial.print(snakeDirection);
    //Pass snakeDirection via Bluetooth
    BTSerial.print(snakeDirection);
    
  }
  
}

void readScore()
{
  if(BTSerial.available() > 0){
   lcd.clear();
   char incomingChar = (char)BTSerial.read();
   score += incomingChar;
   lcd.print("You scored: " + score);
  }
}
