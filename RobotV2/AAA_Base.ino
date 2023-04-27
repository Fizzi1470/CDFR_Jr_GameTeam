#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h> // Utiliser la librairie suivante : https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#include <MechaQMC5883.h> // Utiliser la librairie suivante : https://github.com/keepworking/Mecha_QMC5883L
MechaQMC5883 qmc;
#include <TM1637Display.h>  // Utiliser la librairie suivante : https://github.com/avishorp/TM1637.git
TM1637Display afficheurs(A0,A1);
#include <SwitchProBT.h> //Utiliser la librairie suivante : https://github.com/felis/USB_Host_Shield_2.0
USB Usb;
#include <usbhub.h>
//USBHub Hub1(&Usb);
#include <SPI.h>
BTD Btd(&Usb);
//SwitchProBT SwitchPro(&Btd, PAIR); int mode_appairage = 1;
SwitchProBT SwitchPro(&Btd); int mode_appairage = 0;


//========================== Variables ==========================
int message = -1;

int x, y, z;
float azimuth;
int mode_deplacement = mode_deplacement_defaut;
int premiere_boucle = 1;
int stop_deguisement = 0;
uint32_t watchdog_manette;
int type_manette = manette_defaut;
int message_avail;

int alerte_buzzer;
void alerte(int gravite, String raison){ // gravité 1,2, ou 3, une gravité à 1 ne lance pas de bips du buzzer
  Serial.println("ALERTE : " + raison + " !");
  debug(9,"alerte buzzer lancée, gravité ", gravite);
  if (gravite > alerte_buzzer)
    alerte_buzzer = gravite;
}

int clamerdejeanmichelonapasdemanette;

Servo levage_bras1;
Servo axe_bras1;

Servo levage_bras2;
Servo axe_bras2;

Servo tube_cerise;
Servo porte_aspiro;

Servo baie_gauche_gauche;
Servo baie_gauche_droite;
Servo baie_arriere_gauche;
Servo baie_arriere_droite;
Servo baie_droite_gauche;
Servo baie_droite_droite;


//==================== Fonctions principales ====================

void setup() {
  Serial.begin(115200);
  Serial.println("======================================================================");
  Serial.println("Robot GameTeam 2023 au démarrage . . .");
  Serial.println("(Peut refuser de démarrer entièrement si non alimenté correctement)");
  Serial.println(String("mode débug : ") + mode_debug);
  Serial.println(String("mode limite afficheurs : ") + score_max);
  Serial.print("programme uploadé le : "); Serial.print(__DATE__);  Serial.print(" à "); Serial.println(__TIME__);
  Serial.print("version : ");Serial.println(version_prog);
  Serial.println("conçu pour la Carte Logique V1 et les cartes associées");

  
  Serial2.begin(57600);
  Serial3.begin(38400);
  
  Wire.begin();
  qmc.init();
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  if (Usb.Init() == -1) {Serial.println("ERREUR CRITIQUE : USB en erreur ! Manette BT inutilisable !"); clamerdejeanmichelonapasdemanette = 1;}

  
 
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
  pinMode(44,OUTPUT);  //Module 1 PWM
  pinMode(45,OUTPUT);  //Module 2 PWM
  pinMode(A2,INPUT_PULLUP);  //bouton1 IHM
  pinMode(A3,OUTPUT);  //S0 latch IHM
  pinMode(A4,OUTPUT);  //S1 clock IHM
  pinMode(A5,INPUT_PULLUP);  //Slide1 IHM
  pinMode(A6,OUTPUT);  //S2 data IHM
  pinMode(A7,INPUT_PULLUP);  //slide2 IHM
  pinMode(A14,INPUT);  //Anexe
  pinMode(A15,INPUT);  //Tension batt

  if (buzzer == 1){
    analogWrite(4,127);
  } else {
    Serial.println("ATTENTION : Buzzer désactivé, à utiliser avec précautions.");
  }
  
  digitalWrite(33-deguisement1,1);
  digitalWrite(33-deguisement2,1);

  digitalWrite(A3, LOW);
  shiftOut(A6, A4, LSBFIRST, 0b11111111);
  digitalWrite(A3, HIGH);

  afficheurs.clear();
  afficheurs.setBrightness(0x0f);
  afficheurs.showNumberDec(8888);

  digitalWrite(33-deguisement1,0);
  digitalWrite(33-deguisement2,0);

  digitalWrite(A3, LOW);
  shiftOut(A6, A4, LSBFIRST, 0b00000000);
  digitalWrite(A3, HIGH);

  afficheurs.showNumberDec(score_defaut);

  analogWrite(4,0);

  if (mode_debug != 0 || desac_bras == 1 || clamerdejeanmichelonapasdemanette == 1 || mode_appairage == 1){
    if (buzzer == 1){
    delay(100);
    analogWrite(4,127);
    delay(100);
    analogWrite(4,0);
    delay(100);
    analogWrite(4,127);
    delay(100);
    analogWrite(4,0);
    delay(100);
    }
    
    if (desac_bras == 1){
      
      Serial.println("ATTENTION : Bras désactivés, ne pas utiliser cette configuration en match !!!");
    }
    if (mode_debug != 0){
      Serial.println("ATTENTION : Mode débug actif, ne pas utiliser cette configuration en match !!!");
    }
    if (clamerdejeanmichelonapasdemanette == 1 ){
      Serial.println("ERREUR CRITIQUE : Manette BT indisponnible !!!");
    }
    if (autoriser_console == 1){
      Serial.println("ATTENTION : Console active, configuration déconseillée en match !!!");
    }
    if (mode_appairage == 1){
      Serial.println("ATTENTION : Mode appairage . . .");
    }
  }
  Serial.println("Robot GameTeam 2023 prêt !");
  if (autoriser_console == 1) Serial.println("Console active, tappez 'help' pour afficher les commandes disponibles");
  Serial.println("======================================================================");
}

void loop() {

  Usb.Task();
  
  if (mode_deplacement == 2)
    qmc.read(&x, &y, &z,&azimuth);

  if(autoriser_console == 1 && Serial.available() > 0){
    debug(8, "cons",-99);
    String lecture_console; debug(10, "lect_cons", -99);
    delay(10);
    while (Serial.available() > 0){
      lecture_console.concat((char)Serial.read());
    }
    Serial.println(String("> ") + lecture_console);
    console(lecture_console); debug(10, "cons", -99);
  }

  
  if(Serial3.available() > 0){
    //actu_score(); //ancienne version, qui ne correspond plus à l'application
    gestion_score();
    debug(8, "score",-99);
  }

  if (millis() - watchdog_manette > 500 && type_manette == 1){analogWrite(5,0);analogWrite(6,0);analogWrite(7,0);analogWrite(8,0);analogWrite(9,0);analogWrite(10,0);analogWrite(11,0);analogWrite(12,0);}
  if (SwitchPro.connected() == 0 && type_manette == 2){analogWrite(5,0);analogWrite(6,0);analogWrite(7,0);analogWrite(8,0);analogWrite(9,0);analogWrite(10,0);analogWrite(11,0);analogWrite(12,0);}
  manette_actu();
  
  if(message_avail == 1){
    debug(3, "message manette : ", message);
    debug(12,"message BT : ", message);
    
    mouvements(); debug(8, "mvmts",-99);
    changement_mode(); debug(8, "ch_md",-99);
    aspiro_balles(); debug(8, "asp",-99);
    lancements_sequence_bras(); debug(8, "lanseq",-99);
    changement_manuel_score(); debug(8, "ch_man_sc",-99);
    
    message_avail = 0;
  }
  
  sequences(); debug(8,"seq", -99);
  mouvements_bras(); debug(8, "mvt_br",-99);
  mouvements_baies(); debug(8, "baies",-99);
  deguisement(); debug(8, "deg",-99);
  
  IHM(); debug(8, "IHM",-99);

  if(premiere_boucle == 1) premiere_boucle = 0;
}
