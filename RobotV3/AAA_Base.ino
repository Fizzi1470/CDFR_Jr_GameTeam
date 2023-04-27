#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <Wire.h>
#include <avr/wdt.h>
#include <SwitchProBT.h> //https://github.com/felis/USB_Host_Shield_2.0
#include <Adafruit_PWMServoDriver.h> //https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
#include <QMC5883LCompass.h> //https://github.com/mprograms/QMC5883LCompass
#include <TM1637Display.h>  //https://github.com/avishorp/TM1637.git
TM1637Display afficheurs(A0,A1);
QMC5883LCompass compass;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
USB Usb;
//USBHub Hub1(&Usb); // en cas de congle interne à la clé Bluetooth
BTD Btd(&Usb);


//========================== Réglages ==========================
//SwitchProBT SwitchPro(&Btd, PAIR); const boolean mode_appairage = 1;
SwitchProBT SwitchPro(&Btd); const boolean mode_appairage = 0;
//==============================================================

boolean premiere_boucle = 1; //égal à 1 lors du premier passage de la fonction loop()
boolean stop_deguisement; //mise a 1 lorsque le déguisement est actif, pour desactiver les moteurs
byte mode_deplacement = mode_deplacement_defaut;
byte type_manette = manette_defaut;
boolean bargraph[8];
boolean BAU;
byte mode_debug = debug_mode;
int x, y, z;
float azimuth;
boolean sequence_prete;
int sequence;
uint32_t timer_sequence_principal;

uint32_t valeur;
uint32_t ancienT;
uint32_t ancienGT;
void delta(){
  valeur = micros() - ancienT;if(valeur > 550)Serial3.println(valeur);ancienT = micros();
  }
void deltaG(){
  int valeur = micros() - ancienGT;Serial3.println(valeur);ancienT = micros();
}

uint16_t lastMessageCounter = -1;
uint32_t capture_timer;

int axeX;
int axeY;
int axeTourner;

boolean premiere_conexion = 1;

boolean mode_sequence;
boolean premier_relachement_bouton_sequence;
void add_sequence(byte numero){sequence = (sequence*10) + numero;}

void rien(){} //Tout est dans le titre




void setup() {//debug(8,F("setup"), -99); 
  Serial.begin(250000);
  Serial.println(F("======================================================================"));
  Serial.println(F("Robot GameTeam 2023 au démarrage . . ."));
  Serial.println(F("(Peut refuser de démarrer entièrement si non alimenté correctement)"));
  Serial.println(F("A NOTER : la manette peut devenir instable si le robot est connecté en USB ! "));
  Serial.print(F("mode débug : ")); Serial.println(mode_debug);
  Serial.print(F("programme uploadé le : ")); Serial.print(F(__DATE__));  Serial.print(F(" à ")); Serial.println(F(__TIME__));
  Serial.print(F("version : "));Serial.println(version_prog);
  Serial.println(F("conçu pour la Carte Logique V1 et les cartes associées"));
    
  pinMode(2,OUTPUT);  //Anexe
  pinMode(3,OUTPUT);  //Anexe
  pinMode(4,OUTPUT);  //buzzer
  pinMode(5,OUTPUT);  //mot1
  pinMode(6,OUTPUT);  //mot1
  pinMode(7,OUTPUT);  //mot2
  pinMode(8,OUTPUT);  //mot2
  pinMode(9,OUTPUT);  //mot3
  pinMode(10,OUTPUT);  //mot3
  pinMode(11,OUTPUT);  //mot4
  pinMode(12,OUTPUT);  //mot4
  pinMode(13,OUTPUT);  //turbine
  pinMode(25,OUTPUT);  //12v
  pinMode(26,OUTPUT);  //12v
  pinMode(27,OUTPUT);  //12v
  pinMode(28,OUTPUT);  //12v
  pinMode(29,OUTPUT);  //12v
  pinMode(30,OUTPUT);  //12v
  pinMode(31,OUTPUT);  //12v
  //pinMode(44,OUTPUT);  //Module 1 PWM 
  //pinMode(45,OUTPUT);  //Module 2 PWM
  //pinMode(53,INPUT_PULLUP); //Bouton arret urgence (inverse) Attention : cette pin n'est pas a pull up, si on le fait, le programme crash sur le USB.task, je pense que c'est parce qu'elle est déjà pull up étant donné que c'est la SS du SPI hardware, mais je n'ai pas vraiment cherché, le tout étant qu'elle marche même sans être définie en pull up
  pinMode(A2,INPUT_PULLUP);  //bouton1 IHM
  pinMode(A3,OUTPUT);  //S0 latch IHM
  pinMode(A4,OUTPUT);  //S1 clock IHM
  pinMode(A5,INPUT_PULLUP);  //Slide1 IHM
  pinMode(A6,OUTPUT);  //S2 data IHM
  pinMode(A7,INPUT_PULLUP);  //slide2 IHM
  pinMode(A14,INPUT);  //Anexe
  pinMode(A15,INPUT);  //Tension batt

  digitalWrite(5,0);
  digitalWrite(6,0);
  digitalWrite(7,0);
  digitalWrite(8,0);
  digitalWrite(9,0);
  digitalWrite(10,0);
  digitalWrite(11,0);
  digitalWrite(12,0);
  digitalWrite(13,0);
  digitalWrite(25,0);
  digitalWrite(26,0);
  digitalWrite(27,0);
  digitalWrite(28,0);
  digitalWrite(29,0);
  digitalWrite(30,0);
  digitalWrite(31,0);

  Serial2.begin(57600);
  Serial3.begin(38400);
  Wire.begin();
  //Wire.setWireTimeout(800, false);
  //compass.init();
  //compass.setCalibration(-945, 643, -158, 1448, -1396, 0);
  //compass.setMode(0x01, 0x0C, 0x10, 0x40);
  //compass.setSmoothing(5,true); 
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  
  if (buzzer == 1) {analogWrite(4, 127);}
  
  digitalWrite(33-deguisement1,1);
  digitalWrite(33-deguisement2,1);

  digitalWrite(A3, LOW);
  shiftOut(A6, A4, LSBFIRST, 0b11111111);
  digitalWrite(A3, HIGH);

//  afficheurs.clear();
//  afficheurs.setBrightness(0x0f);
//  afficheurs.showNumberDec(8888);

  baie_avant(1);
  baie_arriere(1);
  baie_droite(1);
  baie_gauche(1);

  delay(500);

  digitalWrite(A3, LOW);
  shiftOut(A6, A4, LSBFIRST, 0b00000000);
  digitalWrite(A3, HIGH);

  digitalWrite(33-deguisement1,0);
  digitalWrite(33-deguisement2,0);

//  afficheurs.showNumberDec(score_defaut);

  if (mode_debug != 0 || desac_bras == 1 || mode_appairage == 1){
    if (buzzer == 1){delay(200);analogWrite(4,127);delay(200);analogWrite(4,0);delay(200);analogWrite(4,127);delay(200);analogWrite(4,0);}
  } else analogWrite(4,0);

  bargraph[1] = 0;bargraph[2] = 0;
  
  if (type_manette == 1){
    bargraph[1] = 1;
  } else bargraph[2] = 1;

  if (mode_deplacement == 2){
    bargraph[3] = 1;
  } else {bargraph[3] = 0;}

  actu_bargraph();
 
 Serial.println(F("Robot GameTeam 2023 prêt !"));
  if (autoriser_console == 1) Serial.println(F("Console active, tappez 'help' pour afficher les commandes disponibles"));
  Serial.println(F("======================================================================"));

  if (Usb.Init() == -1) {Serial.println(F("============================================== \nERREUR CRITIQUE : MANETTE BT INDISPONNIBLE !!! \n=============================================="));alerte(3, "BT init failed");}
  if (mode_appairage == 1) {Serial.println(F("ATTENTION : Mode appairage de la manette BT"));}
  if (buzzer == 0){Serial.println(F("ATTENTION : Buzzer désactivé, à utiliser avec précautions."));} 
  if (desac_bras == 1){Serial.println(F("ATTENTION : Bras désactivés, ne pas utiliser cette configuration en match !!!"));}
  if (mode_debug != 0){Serial.println(F("ATTENTION : Mode débug actif, ne pas utiliser cette configuration en match !!!"));}
  if (autoriser_console == 1){Serial.println(F("ATTENTION : Console active, ne pas utiliser cette configuration en match !!!"));}

  if (activer_watchdog == 1) wdt_enable(WDTO_1S);
}

void loop() {//debug(8,F("loop"), -99);
  if (activer_watchdog == 1) wdt_reset();

  Usb.Task();
  
  //deltaG();
  //Usb.Task();delta(0.1);compass.read();

  //gestion_manette();//debug(8,F("ma"), -99);
  //Usb.Task();delta();
  if (type_manette == 2 && premiere_boucle == 1){SwitchPro.disconnect();} //en cas de reset du robot sans déconexion propre de la manette, on ne peut pas la reco sinon
/*if(autoriser_timeout_manette != 0 && type_manette == 2){
  }
  //SwitchPro.getLastMessageTime()
*/
  //Usb.Task();//delta();
  
  if(Serial3.available() > 0){gestion_score();}//debug(8, F("sc"),-99);
  //Usb.Task();delta();
  if(autoriser_console == 1 && Serial.available() > 0){lire_console();}//debug(8,F("co"), -99);
  //Usb.Task();delta();
  
  gestion_score();//debug(8,F("lectsc"), -99);
  //Usb.Task();delta();
  gestion_deguisement();//debug(8,F("deg"), -99);
  //Usb.Task();delta();
  gestion_deplacements();//debug(8,F("dep"), -99);
  //Usb.Task();delta();
  gestion_IHM();//debug(8,F("ihm"), -99);
  //Usb.Task();delta();
  gestion_sequences();//debug(8,F("seq"), -99);
  //Usb.Task();delta();
  gestion_sequences_principales();//debug(8,F("seqpr"), -99);
  //Usb.Task();delta();
  gestion_buzzer();//debug(8,F("buz"), -99);
  //Usb.Task();delta();
  
  gestion_BAU();//debug(8,F("bau"), -99);
  //Usb.Task();delta();
  gestion_BAU_turbine();//debug(8,F("tur"), -99);
  //Usb.Task();delta();


  if (type_manette == 2){
  if (SwitchPro.connected() && lastMessageCounter != SwitchPro.getMessageCounter()) {
    lastMessageCounter = SwitchPro.getMessageCounter();
    
  if (SwitchPro.getAnalogHat(RightHatX) > DeadzoneR || SwitchPro.getAnalogHat(RightHatX) < -(DeadzoneR)) {
      if (SwitchPro.getAnalogHat(RightHatX) > DeadzoneR)  axeTourner = (round(SwitchPro.getAnalogHat(RightHatX)/58.3));
      else                                                axeTourner = (round(SwitchPro.getAnalogHat(RightHatX)/70.8));
    } else axeTourner = 0;
    /*
    if (SwitchPro.getAnalogHat(RightHatY) > DeadzoneR || SwitchPro.getAnalogHat(RightHatY) < -(DeadzoneR)) {
      if (SwitchPro.getAnalogHat(RightHatY) > DeadzoneR)  message = ((round(SwitchPro.getAnalogHat(RightHatY)/69.6)*-1));
      else                                                message = ((round(SwitchPro.getAnalogHat(RightHatY)/66.6)*-1));
    } else message = 0;
    */
    /* ===== Joystick Gauche (Left) ===== */

    if (SwitchPro.getAnalogHat(LeftHatX) > DeadzoneL || SwitchPro.getAnalogHat(LeftHatX) < -(DeadzoneL)) {
      if (SwitchPro.getAnalogHat(LeftHatX) > DeadzoneL) axeX = (round(SwitchPro.getAnalogHat(LeftHatX)/58.3));
      else                                              axeX = (round(SwitchPro.getAnalogHat(LeftHatX)/71.6));
    } else axeX = 0;

    if (SwitchPro.getAnalogHat(LeftHatY) > DeadzoneL || SwitchPro.getAnalogHat(LeftHatY) < -(DeadzoneL)) {
      if (SwitchPro.getAnalogHat(LeftHatY) > DeadzoneL) axeY = ((round(SwitchPro.getAnalogHat(LeftHatY)/72.0)*-1));
      else                                              axeY = ((round(SwitchPro.getAnalogHat(LeftHatY)/60.8)*-1));
    } else axeY = 0;
      

  // Hold the CAPTURE button for 1 second to disconnect the controller
  // This prevents the controller from disconnecting when it is reconnected,
  // as the CAPTURE button is sent when it reconnects
  /*
  if (SwitchPro.getButtonPress(CAPTURE)) {
    if (millis() - capture_timer > 1000) SwitchPro.disconnect();
  } else capture_timer = millis();
*/
  if (SwitchPro.getButtonClick(CAPTURE))rien();
  if (SwitchPro.getButtonClick(HOME))changer_etat_deguisement();

  if (SwitchPro.getButtonClick(LEFT))lancer_sequence(F("gauche_vers_avant"));  
  if (SwitchPro.getButtonClick(UP))lancer_sequence(F("cerise_avant"));
  if (SwitchPro.getButtonClick(RIGHT))lancer_sequence(F("droite_vers_avant")); 
  if (SwitchPro.getButtonClick(DOWN))lancer_sequence(F("arriere_vers_avant"));

  if (SwitchPro.getButtonClick(PLUS))//augmenter_score();
  if (SwitchPro.getButtonClick(MINUS))//diminuer_score();
    
  if (SwitchPro.getButtonClick(A))if (mode_sequence) add_sequence(4); else baie_droite(-1);
  if (SwitchPro.getButtonClick(B))if (mode_sequence) add_sequence(2); else baie_arriere(-1);
  if (SwitchPro.getButtonClick(X))if (mode_sequence) add_sequence(1); else baie_avant(-1);
  if (SwitchPro.getButtonClick(Y))if (mode_sequence) add_sequence(3); else baie_gauche(-1);

  if (SwitchPro.getButtonClick(L))rien();
  if (SwitchPro.getButtonPress(R)){mode_sequence = 1;premier_relachement_bouton_sequence = 1;SwitchPro.setRumbleRight(true);} else{ mode_sequence = 0;SwitchPro.setRumbleRight(false);
                                                                                                                                if (premier_relachement_bouton_sequence == 1){
                                                                                                                                  if (sequence < 100 || sequence > 1000) sequence = 0;
                                                                                                                                  else {sequence_prete = 1;timer_sequence_principal = millis();}}
                                                                                                                                premier_relachement_bouton_sequence = 0;}
  
  if (SwitchPro.getButtonClick(ZL))changer_etat_aspiro();  
  if (SwitchPro.getButtonClick(ZR))rien(); 

  if (SwitchPro.getButtonClick(L3))changer_mode();
  if (SwitchPro.getButtonClick(R3))calibrer_azimuth();
  
  }
  
  else if (SwitchPro.connected() == 0){
    analogWrite(5,0);
    analogWrite(6,0);
    analogWrite(7,0);
    analogWrite(8,0);
    analogWrite(9,0);
    analogWrite(10,0);
    analogWrite(11,0);
    analogWrite(12,0);
    premiere_conexion = 1;
  }   
  
  if(SwitchPro.connected() && premiere_conexion == 1){
    if(mode_deplacement == 1)SwitchPro.setLedHomeOff();
    else SwitchPro.setLedHomeOn();
    SwitchPro.setLedOn(LED1);
    SwitchPro.setLedOn(LED2);
    SwitchPro.setLedOn(LED3);
    SwitchPro.setLedOn(LED4);
    premiere_conexion = 0;
    
  }
  }
  
  if(Wire.getWireTimeoutFlag())Wire.clearWireTimeoutFlag();
  if(premiere_boucle == 1) premiere_boucle = 0;
}
