/*
==========================================================================================================================================================================================================================================================================
==========================================================================================================================================================================================================================================================================

                        BIEN REGLER LA CARTE SUR ARDUINO PRO MINI 3.3V 8MHZ AVANT DE FLASHER,SINON ON OBTIENT DE LA GROSSE MERDE EN SORTIE (des valeurs au dessus de 200 et dans les 96), ET CE MEME SI LA MANETTE N'EST PAS CONNECTEE

==========================================================================================================================================================================================================================================================================
==========================================================================================================================================================================================================================================================================


============= CODES : =============
 * 1-49
 * 51-99
 * 101-149
 * 152-200
 * 
 * 201-218 : boutons appuyés 
 * 219-225 : boutons relachés
 * 
 * 230 : librairie OK (démarrage)
 * 231 : librairie en erreur (démarrage)
 * 
 * 001 : activer mode alerte
 * 002 : desactiver mode alerte
 */
 
#include <SwitchProUSB.h>
#include <SPI.h>

USB Usb;
SwitchProUSB SwitchPro(&Usb);

#define DeadzoneL 250
#define DeadzoneR 250
#define DelaisJoystick 1
#define DelaisGeneral 0

bool printAngle = false;
uint32_t lastMessageCounter = -1;
int ordre_recu;
int ZR_enclenche;

/* ================================================================================================ Initialisation ================================================================================================*/

void setup() {
  Serial.begin(57600);

  if (Usb.Init() == -1) {
    Serial.write(231);
    while (1); // Halt
  }
  Serial.write(230);
}

void loop() {
  Usb.Task();
/*
=====================================================================================================================
Délais général pour laisser le temps à l'arduino principale de lire le contenu de son buffer, A AJUSTER EN PERMANANCE
=====================================================================================================================*/
delay(DelaisGeneral);

/* ================================================================================================ Lecture des joysticks ================================================================================================ */

  if (SwitchPro.connected() && lastMessageCounter != SwitchPro.getMessageCounter()) {
    lastMessageCounter = SwitchPro.getMessageCounter();

/* ===== Joystick Droite (Right) ===== */

    if (SwitchPro.getAnalogHat(RightHatX) > DeadzoneR || SwitchPro.getAnalogHat(RightHatX) < -(DeadzoneR)) {
      if (SwitchPro.getAnalogHat(RightHatX) > DeadzoneR) {
        Serial.write(round(SwitchPro.getAnalogHat(RightHatX)/58.3)+25);
      }
      else Serial.write(round(SwitchPro.getAnalogHat(RightHatX)/70.8)+25);
    }
    else Serial.write(25);

    delay(DelaisJoystick);
  
    if (SwitchPro.getAnalogHat(RightHatY) > DeadzoneR || SwitchPro.getAnalogHat(RightHatY) < -(DeadzoneR)) {
      if (SwitchPro.getAnalogHat(RightHatY) > DeadzoneR) {
        Serial.write((round(SwitchPro.getAnalogHat(RightHatY)/69.6)*-1)+75);
      }
      else Serial.write((round(SwitchPro.getAnalogHat(RightHatY)/66.6)*-1)+75);
    }
    else Serial.write(75);

    delay(DelaisJoystick);
    
/* ===== Joystick Gauche (Left) ===== */

    if (SwitchPro.getAnalogHat(LeftHatX) > DeadzoneL || SwitchPro.getAnalogHat(LeftHatX) < -(DeadzoneL)) {
      if (SwitchPro.getAnalogHat(LeftHatX) > DeadzoneL) {
        Serial.write(round(SwitchPro.getAnalogHat(LeftHatX)/58.3)+125);
      }
      else Serial.write(round(SwitchPro.getAnalogHat(LeftHatX)/71.6)+125);
    }
    else Serial.write(125);

    delay(DelaisJoystick);

    if (SwitchPro.getAnalogHat(LeftHatY) > DeadzoneL || SwitchPro.getAnalogHat(LeftHatY) < -(DeadzoneL)) {
      if (SwitchPro.getAnalogHat(LeftHatY) > DeadzoneL) {
        Serial.write((round(SwitchPro.getAnalogHat(LeftHatY)/72.0)*-1)+175);
      }
      else Serial.write((round(SwitchPro.getAnalogHat(LeftHatY)/60.8)*-1)+175);
    }
    else Serial.write(175);

    delay(DelaisJoystick);

/* ================================================================================================ Lecture des boutons ================================================================================================ */

    if (SwitchPro.getButtonClick(CAPTURE)){
      Serial.write(201);
    }    
    if (SwitchPro.getButtonClick(HOME)) {
      Serial.write(202);
    }


    if (SwitchPro.getButtonClick(LEFT)) {
      Serial.write(203);
    }
    if (SwitchPro.getButtonClick(UP)) {
      Serial.write(204);
    }
    if (SwitchPro.getButtonClick(RIGHT)) {
      Serial.write(205);
    }
    if (SwitchPro.getButtonClick(DOWN)) {
      Serial.write(206);
    }

    
    if (SwitchPro.getButtonClick(PLUS)) {
      Serial.write(207);
    }
    if (SwitchPro.getButtonClick(MINUS)){
      Serial.write(208);
    }


    if (SwitchPro.getButtonClick(A)){
      Serial.write(209);
    }
    if (SwitchPro.getButtonClick(B)) {
      Serial.write(210);
    }
    if (SwitchPro.getButtonClick(X)){
      Serial.write(211);
    }
    if (SwitchPro.getButtonClick(Y)){
      Serial.write(212);
    }


    if (SwitchPro.getButtonClick(L)) {
      Serial.write(213);
    }
    if (SwitchPro.getButtonClick(R)) {
      Serial.write(214);
    }
    if (SwitchPro.getButtonClick(ZL)) {
      Serial.write(215);
    }
    //if (SwitchPro.getButtonClick(ZR)) {
    //  Serial.write(216);
    //}

    if (SwitchPro.getButtonPress(ZR) == 1 || ZR_enclenche == 1){
      if (SwitchPro.getButtonPress(ZR) == 1){
        if (ZR_enclenche == 0)
          Serial.write(216);
        ZR_enclenche =1;
      }else{
        Serial.write(219);
        ZR_enclenche = 0;
      }
    }
    
    if (SwitchPro.getButtonClick(L3)){
      Serial.write(217);
    }
    if (SwitchPro.getButtonClick(R3)){
      Serial.write(218);
    }
    
    if (SwitchPro.connected() == 0){    //au cas ou la manette se déconnecte; on envoie stop à tous les moteurs
      Serial.write(25);
      Serial.write(75);
      Serial.write(125);
      Serial.write(175);
    }
    
    
/* ================================================================================================ Reception/transmission/envoi d'ordres ================================================================================================ */
// Il est important que cette partie reste en dehors de la condition if Switchpro.connected !
    if (Serial.available() > 0) {
      ordre_recu = Serial.read();
      ordre_recu = ordre_recu - 48;
      
      if (ordre_recu == 1) {
        SwitchPro.setLedHomeOn();
      }
      if (ordre_recu == 2) {
        SwitchPro.setLedHomeOff();
      }
    }
  }
}
