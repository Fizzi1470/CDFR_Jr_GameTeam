#include <SwitchProBT.h> //https://github.com/felis/USB_Host_Shield_2.0
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


//SwitchProBT SwitchPro(&Btd, PAIR);
SwitchProBT SwitchPro(&Btd);

boolean deguisement;
int64_t lastMessageCounter = -1;
uint32_t capture_timer;
boolean premiere_conexion = 1;
boolean type_manette = manette_defaut;
int axeX;
int axeY;
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
  SwitchPro.disconnect();

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
  
  wdt_enable(WDTO_1S);
}

void loop() {
  if (digitalRead(A2) == 0) analogWrite(4, 127);
  wdt_reset();
  Usb.Task();
  
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
    gestion_deplacements();

    if (SwitchPro.getButtonPress(CAPTURE)) {
      if (millis() - capture_timer > 1000) SwitchPro.disconnect();
    } else capture_timer = millis();

    //if (SwitchPro.getButtonClick(CAPTURE))rien();
    if (SwitchPro.getButtonClick(HOME))changer_etat_deguisement();

    if (SwitchPro.getButtonClick(LEFT))lancer_sequence(42);
    if (SwitchPro.getButtonClick(UP))lancer_sequence(1);
    if (SwitchPro.getButtonClick(RIGHT))lancer_sequence(12);
    if (SwitchPro.getButtonClick(DOWN))lancer_sequence(32);

    if (SwitchPro.getButtonClick(PLUS))augmenter_score();
    if (SwitchPro.getButtonClick(MINUS))diminuer_score();
    
    if (SwitchPro.getButtonClick(A))if (mode_sequence) add_sequence(1); else baie_droite(-1);
    if (SwitchPro.getButtonClick(B))if (mode_sequence) add_sequence(3); else baie_arriere(-1);
    if (SwitchPro.getButtonClick(X))if (mode_sequence) add_sequence(2); else baie_avant(-1);
    if (SwitchPro.getButtonClick(Y))if (mode_sequence) add_sequence(4); else baie_gauche(-1);

    //if (SwitchPro.getButtonClick(L))rien();
    if (SwitchPro.getButtonPress(R) && sequence_prete == 0){mode_sequence = 1;premier_relachement_bouton_sequence = 1;SwitchPro.setRumbleRight(true);} else{ mode_sequence = 0;SwitchPro.setRumbleRight(false);
                                                                                                                                if (premier_relachement_bouton_sequence == 1){
                                                                                                                                  if (sequence < 100 || sequence > 1000) sequence = 0;
                                                                                                                                  else {sequence_prete = 1;timer_sequence_principal = millis();}}
                                                                                                                                premier_relachement_bouton_sequence = 0;}
  
    if (SwitchPro.getButtonClick(ZL))changer_etat_aspiro(); 
    //if (SwitchPro.getButtonClick(ZR))rien(); 

    //if (SwitchPro.getButtonClick(L3))rien();changer_mode();
    //if (SwitchPro.getButtonClick(R3))rien();calibrer_azimuth();
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
    /*if(mode_deplacement == 0)SwitchPro.setLedHomeOff();
    else SwitchPro.setLedHomeOn();
    SwitchPro.setLedOn(LED1);
    SwitchPro.setLedOn(LED2);
    SwitchPro.setLedOn(LED3);
    SwitchPro.setLedOn(LED4);*/
    premiere_conexion = 0;
  }
  /*
  wdt_reset();
  Usb.Task();
  //gestion_magneto();Usb.Task();
  gestion_score();Usb.Task();
  if (identifiant_sequence != 0){gestion_sequences();Usb.Task();}
  if (sequence_prete == 1){gestion_sequences_principales();Usb.Task();}
  if (deguisement == 1) {gestion_deguisement();Usb.Task();}
  */
}
