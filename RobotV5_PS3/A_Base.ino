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
uint32_t timer_sequence_cerise;
boolean cerise_avant;
boolean cerise_arriere;
boolean cerise_gauche;
boolean cerise_droite;
boolean sequence_cerise_en_cours;
boolean sequence_cerises_prete;
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
boolean reservoir;
uint32_t timer_antiblocage_reservoir;
boolean vidange;
boolean bouton_cerise_presse;
boolean maintient_L1;
boolean resettrigger;

uint32_t ancienT;

void setup() {
  Serial.begin(115200); // PC
  Serial1.begin(115200); // Anexe (magnétomètre)
  Serial2.begin(57600); // Manette filaire 
  Serial3.begin(38400); // module BT 
  Wire.begin();
  Wire.setWireTimeout(30000);
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

  bargraph(3,mode_deplacement);

  bras1_haut();
  bras2_haut();
  delay(500);
  bras1_milieu();
  bras2_milieu();

  cerise_bras1_fermer();
  cerise_bras2_fermer();

  fermer_reservoir();
  changer_position_antiblocage_reservoir();
  changer_etat_deguisement();

  afficheurs.showNumberDec(score_defaut);
  
  if (activer_watchdog == 1) wdt_enable(WDTO_1S);
  if (activer_watchdog == 2) wdt_enable(WDTO_2S);
}

void loop() {
  if (resettrigger==1) digitalWrite(2,1); 
  if (activer_watchdog > 0) wdt_reset();
  Usb.Task();
  int temps = micros() - ancienT;Serial.println(temps);ancienT = micros(); 

  gestion_manette();
  
  if (activer_watchdog > 0) wdt_reset();
  Usb.Task();
  temps = micros() - ancienT;Serial.println(temps);ancienT = micros(); 

  if(digitalRead(53) == 1 || deguisement == 1){ // Bouton d'arrêt d'urgence
    sequence_terminee = 1;
    identifiant_sequence = 0;
    sequence = 0;
    sequence_prete = 0;
    digitalWrite(13, 0);
    turbine = 0;
  }

  //gestion_vidange();
  //gestion_IHM();
  gestion_deplacements();
  if(mode_deplacement == 1) gestion_magneto();
  gestion_score();
  if (sequence_cerise_en_cours == 1){gestion_sequences_cerises();}
  if (identifiant_sequence != 0){gestion_sequences();}
  if (sequence_prete == 1){gestion_sequences_principales();}
  if (deguisement == 1) {gestion_deguisement();}
  if (reservoir == 1 && millis() - timer_antiblocage_reservoir > 500){changer_position_antiblocage_reservoir();timer_antiblocage_reservoir = millis();}
}
