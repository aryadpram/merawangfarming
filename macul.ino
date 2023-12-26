#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#define RE 12
#define DE 14

TFT_eSPI display = TFT_eSPI();  // Invoke custom library

const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xb5, 0xcc};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xe4, 0x0c};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
 
byte values[11];

void setup(void) {
  Serial.begin(9600);
  Serial.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  //DISPLAY
  display.init();
  display.fillScreen(TFT_BLACK);

  // Set "cursor" at top left corner of display (25,10) and select font 4
  display.setCursor(25, 10, 4);
  display.setTextColor(TFT_WHITE, TFT_BLACK);
}

void loop() {

  byte val1,val2,val3;
  val1 = nitrogen();
  delay(250);
  val2 = phosphorous();
  delay(250);
  val3 = potassium();
  delay(250);

  Serial.print("Nitrogen: ");
  Serial.print(val1);
  Serial.println(" mg/kg");
  Serial.print("Phosphorous: ");
  Serial.print(val2);
  Serial.println(" mg/kg");
  Serial.print("Potassium: ");
  Serial.print(val3);
  Serial.println(" mg/kg");
  delay(2000);

  display.fillScreen(TFT_BLACK);
  display.setCursor(25, 10, 4);

  // Display nitrogen
  display.setTextSize(2);
  display.setCursor(5, 20);
  display.print("N: ");
  display.print(val1);
  display.setTextSize(1);
  display.print(" mg/kg");

  // Display phosphor
  display.setTextSize(2);
  display.setCursor(5, 80);
  display.print("P: ");
  display.print(val2);
  display.setTextSize(1);
  display.print(" mg/kg");

  // Display pottasium
  display.setTextSize(2);
  display.setCursor(5, 140);
  display.print("K: ");
  display.print(val3);
  display.setTextSize(1);
  display.print(" mg/kg");

  delay(500);
}

byte nitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(Serial.write(nitro,sizeof(nitro))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(Serial.read(),HEX);
    values[i] = Serial.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
 
byte phosphorous(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(Serial.write(phos,sizeof(phos))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(Serial.read(),HEX);
    values[i] = Serial.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
 
byte potassium(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(100);
  if(Serial.write(pota,sizeof(pota))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(Serial.read(),HEX);
    values[i] = Serial.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}