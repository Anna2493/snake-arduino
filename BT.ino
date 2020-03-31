#include <SoftwareSerial.h>
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

char snakeDirection;
int incomingByte;

void setup()
{
  Serial.begin(9600);
  BTSerial.begin(38400);
}

void loop()
{
  getDirection();
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
