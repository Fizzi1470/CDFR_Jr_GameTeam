#include <PS3BT.h> //https://github.com/felis/USB_Host_Shield_2.0
#include <usbhub.h>
#include <SPI.h>
#include <avr/wdt.h>
#include <Adafruit_PWMServoDriver.h> //https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
#include <TM1637Display.h>  //https://github.com/avishorp/TM1637.git
TM1637Display afficheurs(A0,A1);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
USB Usb;
USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
PS3BT PS3(&Btd);

boolean deguisement;
int64_t lastMessageCounter = -1;
uint32_t capture_timer;
boolean premiere_conexion = 1;
boolean type_manette = manette_defaut;
float axeX;
float axeY;
int axeTourner;
boolean mode_deplacement = mode_deplacement_defaut;
float azimuth;
void rien(){}//tout est dans le titre
boolean sequence_prete;
int sequence;
byte identifiant_sequence;
boolean sequence_terminee = 1;
boolean BAU;
boolean mode_sequence;
boolean premier_relachement_bouton_sequence;
void add_sequence(byte numero){sequence = (sequence*10) + numero;}
uint32_t timer_sequence_principal;
boolean turbine;
boolean ancien_turbine;

uint32_t ancienT;

void gestion_BAU(){
  if (digitalRead(53) == 1) {BAU = 1; identifiant_sequence = 0; sequence_terminee = 1;sequence_prete = 0;sequence = 0;digitalWrite(13,0);}
  else if (BAU != digitalRead(53)){BAU = 0;}
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(57600);
  Serial3.begin(38400);
  Wire.begin();
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  if (Usb.Init() == -1)Serial.println(F("USB INIT FAIL !!!"));

  PS3.disconnect();
  
  Serial.print(F("Robot GameTeam 2023, version "));Serial.println(version_prog);
  Serial.print(F("programme uploadé le : ")); Serial.print(F(__DATE__));  Serial.print(F(" à ")); Serial.println(F(__TIME__));

  pinMode(2,OUTPUT);  //Anexe
  pinMode(3,OUTPUT);  //Anexe(musique)
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
  digitalWrite(3,1);
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

  afficheurs.clear();
  afficheurs.setBrightness(0x0f);
  afficheurs.showNumberDec(8888);

  bras1_haut();
  bras2_haut();
  delay(500);
  bras1_milieu();
  bras2_milieu();
  
  if (activer_watchdog == 1) wdt_enable(WDTO_1S);
  if (activer_watchdog == 2) wdt_enable(WDTO_2S);
}

void loop() {
  if (digitalRead(A2) == 0) analogWrite(4, 127);
  if (activer_watchdog == 1 || activer_watchdog == 2) wdt_reset();
  Usb.Task();
  //Serial.println(micros() - ancienT);
  //ancienT = micros(); 
  
  if (PS3.PS3Connected) {

    if (PS3.getAnalogHat(RightHatX) > 127+DeadzoneR || PS3.getAnalogHat(RightHatX) < 127-DeadzoneR) {
      if (PS3.getAnalogHat(RightHatX) > 127+DeadzoneR)  axeTourner = (round((PS3.getAnalogHat(RightHatX)-127.5)/5.1));
      else                                              axeTourner = (round((PS3.getAnalogHat(RightHatX)-127.5)/5.1));
    } else axeTourner = 0;
    /*
    if (PS3.getAnalogHat(RightHatY) > DeadzoneR || PS3.getAnalogHat(RightHatY) < -(DeadzoneR)) {
      if (PS3.getAnalogHat(RightHatY) > DeadzoneR)  message = ((round(PS3.getAnalogHat(RightHatY)/69.6)*-1));
      else                                                message = ((round(PS3.getAnalogHat(RightHatY)/66.6)*-1));
    } else message = 0;
    */
    /* ===== Joystick Gauche (Left) ===== */

    if (PS3.getAnalogHat(LeftHatX) > 127+DeadzoneL || PS3.getAnalogHat(LeftHatX) < 127-DeadzoneL) {
      if (PS3.getAnalogHat(LeftHatX) > 127+DeadzoneL) axeX = (round((PS3.getAnalogHat(LeftHatX)-127.5)/5.1));
      else                                            axeX = (round((PS3.getAnalogHat(LeftHatX)-127.5)/5.1));
    } else axeX = 0;

    if (PS3.getAnalogHat(LeftHatY) > 127+DeadzoneL || PS3.getAnalogHat(LeftHatY) < 127-DeadzoneL) {
      if (PS3.getAnalogHat(LeftHatY) > 127+DeadzoneL) axeY = (round((PS3.getAnalogHat(LeftHatY)-127.5)/5.1))*-1;
      else                                            axeY = (round((PS3.getAnalogHat(LeftHatY)-127.5)/5.1))*-1;
    } else axeY = 0;

    //Serial.print(axeTourner);Serial.print(";"); Serial.print(axeX);Serial.print(";");Serial.println(axeY);

    if (PS3.getButtonPress(PS)) {
      if (millis() - capture_timer > 1000) PS3.disconnect();
    } else capture_timer = millis();

    if (PS3.getButtonClick(PS))changer_etat_deguisement();

    if (PS3.getButtonClick(LEFT))lancer_sequence(42);
    if (PS3.getButtonClick(UP))lancer_sequence(1);
    if (PS3.getButtonClick(RIGHT))lancer_sequence(12);
    if (PS3.getButtonClick(DOWN))lancer_sequence(32);
  
    if (PS3.getButtonClick(START))augmenter_score();
    if (PS3.getButtonClick(SELECT))diminuer_score();
    
    if (PS3.getButtonClick(CIRCLE))if (mode_sequence) add_sequence(1); else baie_droite(-1);
    if (PS3.getButtonClick(CROSS))if (mode_sequence) add_sequence(3); else baie_arriere(-1);
    if (PS3.getButtonClick(TRIANGLE))if (mode_sequence) add_sequence(2); else baie_avant(-1);
    if (PS3.getButtonClick(SQUARE))if (mode_sequence) add_sequence(4); else baie_gauche(-1);

    //if (PS3.getButtonClick(L1))rien();
    if (PS3.getButtonPress(R1) && sequence_prete == 0){mode_sequence = 1;premier_relachement_bouton_sequence = 1;/*PS3.setRumbleOn(RumbleHigh);*/} else{ mode_sequence = 0;/*PS3.setRumbleOff();*/
                                                                                                                                if (premier_relachement_bouton_sequence == 1){
                                                                                                                                  if (sequence < 100 || sequence > 1000) sequence = 0;
                                                                                                                                  else {sequence_prete = 1;timer_sequence_principal = millis();}}
                                                                                                                                premier_relachement_bouton_sequence = 0;}
  
    if (PS3.getAnalogButton(R2) > 150){ if (ancien_turbine == turbine){changer_etat_aspiro();}}else ancien_turbine = turbine;
    //if (PS3.getAnalogButton(L2) > 150)rien(); 

    //if (PS3.getButtonClick(L3))rien();changer_mode();
    //if (PS3.getButtonClick(R3))rien();calibrer_azimuth();
    
  }
  else {
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
  
  if(PS3.PS3Connected && premiere_conexion == 1){
    PS3.setLedOn(LED1);
    PS3.setLedOn(LED2);
    PS3.setLedOn(LED3);
    PS3.setLedOn(LED4);
    premiere_conexion = 0;
  }
  
  if (activer_watchdog == 1 || activer_watchdog == 2) wdt_reset();
  Usb.Task();
  
  gestion_deplacements();
  //gestion_magneto();
  gestion_score();
  if (identifiant_sequence != 0){gestion_sequences();}
  if (sequence_prete == 1){gestion_sequences_principales();}
  if (deguisement == 1) {gestion_deguisement();}
}
