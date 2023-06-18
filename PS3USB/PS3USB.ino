#define DeadzoneR 15
#define DeadzoneL 15

#include <PS3USB.h>
#include <SPI.h>
USB Usb;
PS3USB PS3(&Usb); // This will just create the instance

boolean ancien_R2;
boolean ancien_L2;
boolean ancien_R1;
boolean ancien_L1;
boolean premiere_conexion = 1;

void setup() {
  Serial.begin(115200);
  
  if (Usb.Init() == -1) {Serial.print(253);}
  Serial.print(254);
}
void loop() {
  Usb.Task();

  if (PS3.PS3Connected) {
    
    if (PS3.getAnalogHat(RightHatX) > 127+DeadzoneR || PS3.getAnalogHat(RightHatX) < 127-DeadzoneR) {
      if (PS3.getAnalogHat(RightHatX) > 127+DeadzoneR)  Serial.print(round(PS3.getAnalogHat(RightHatX)/5.1));
      else                                              Serial.print(round(PS3.getAnalogHat(RightHatX)/5.1));
    } else Serial.print(25);

    if (PS3.getAnalogHat(LeftHatX) > 127+DeadzoneL || PS3.getAnalogHat(LeftHatX) < 127-DeadzoneL) {
      if (PS3.getAnalogHat(LeftHatX) > 127+DeadzoneL) Serial.print(round(PS3.getAnalogHat(LeftHatX)/5.1)+51);
      else                                            Serial.print(round(PS3.getAnalogHat(LeftHatX)/5.1)+51);
    } else Serial.print(25+51);

    if (PS3.getAnalogHat(LeftHatY) > 127+DeadzoneL || PS3.getAnalogHat(LeftHatY) < 127-DeadzoneL) {
      if (PS3.getAnalogHat(LeftHatY) > 127+DeadzoneL) Serial.print((round(PS3.getAnalogHat(LeftHatY)/5.1)*-1)+102);
      else                                            Serial.print((round(PS3.getAnalogHat(LeftHatY)/5.1)*-1)+102);
    } else Serial.print(25+102);

    if (PS3.getButtonClick(PS))
      Serial.print(204);

    if (PS3.getButtonClick(TRIANGLE))
      Serial.print(205);
    if (PS3.getButtonClick(CIRCLE))
      Serial.print(206);
    if (PS3.getButtonClick(CROSS))
      Serial.print(207);
    if (PS3.getButtonClick(SQUARE))
      Serial.print(208);

    if (PS3.getButtonClick(UP)) 
      Serial.print(209);
    if (PS3.getButtonClick(RIGHT)) 
      Serial.print(210);
    if (PS3.getButtonClick(DOWN))
      Serial.print(211);
    if (PS3.getButtonClick(LEFT))
      Serial.print(212);
      
    if (PS3.getButtonClick(SELECT))
      Serial.print(213);
    if (PS3.getButtonClick(START))
      Serial.print(214);

    if (PS3.getButtonClick(R3))
      Serial.print(215);
    if (PS3.getButtonClick(L3))
      Serial.print(216);
           
    if (PS3.getAnalogButton(L2) > 150){
      if (ancien_L2 == 0){
        ancien_L2 = 1;
        Serial.print(217);
      }
    } else if (ancien_L2 == 1){
      ancien_L2 = 0;
      Serial.print(218);
    }
    
    if (PS3.getAnalogButton(R2) > 150){
      if(ancien_R2 == 0){Serial.print(219);ancien_R2 = 1;}        
    } else ancien_R2 = 0;

    if (PS3.getAnalogButton(L1) > 150){
      if (ancien_L1 == 0){
        ancien_L1 = 1;
        Serial.print(220);
      }
    } else if (ancien_L1 == 1){
      ancien_L1 = 0;
      Serial.print(221);
    }

    if (PS3.getAnalogButton(R1) > 150){
      if (ancien_R1 == 0){
        ancien_R1 = 1;
        Serial.print(222);
      }
    } else if (ancien_R1 == 1){
      ancien_R1 = 0;
      Serial.print(223);
    } 

    if (PS3.getButtonPress(CIRCLE) && PS3.getButtonPress(CROSS) && PS3.getButtonPress(TRIANGLE) && PS3.getButtonPress(SQUARE)) {
      Serial.print(230);
    }
    
  }

  if(PS3.PS3Connected){
    if (premiere_conexion == 1){
      PS3.setLedOn(LED1);
      PS3.setLedOff(LED2);
      PS3.setLedOff(LED3);
      PS3.setLedOn(LED4);
      Serial.print(251);
      premiere_conexion = 0;
    }
  } else if (premiere_conexion == 0) {premiere_conexion = 1;Serial.print(252);}
}
