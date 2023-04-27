#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>
#include <MechaQMC5883.h> // Utiliser la librairie suivante : https://github.com/keepworking/Mecha_QMC5883L
MechaQMC5883 qmc;
#include <TM1637Display.h>  // Utiliser la librairie suivante : https://github.com/avishorp/TM1637.git
TM1637Display afficheurs(3,3+1);
#include <Grove_LED_Bar.h>// Utiliser la librairie suivante : https://github.com/Seeed-Studio/Grove_LED_Bar.git
Grove_LED_Bar bargraph(22+1, 22, 1, LED_BAR_10); // Clock pin, Data pin, Orientation

//========================== Paramètres ==========================

#define mode_deplacement_defaut 1; // 1 : mode normal; 2 : mode azimuth
const int score_defaut = 65;
const int retrait_score = 5;
const int ajout_score = 5;
const int delais_min_deguisement = 2;
const int delais_max_deguisement = 4;

const int mode_debug = 0; //note : baud rate : 115200

const float version_prog = 1.1;



/*  Modes debug disponibles : NOTE : SERVOMOTEURS BRAS INACTIFS EN MODE DEBUG
 *   
 *  0: éteint A REMETTRE SUR ETEINT PENDANT LES MATCHS, DELAIS SUPP SINON
 *  1: informations relatives aux déplacements
 *  2: informations relatives aux scores
 *  3: relayement des messages reçus
 *  4: informations relatives à l'aspirateur de balles
 *  5: informations relatives aux mouvements de bras
 *  6: informations relatives au déguisement
 *  7: informations relatives au changement de mode
 */

//========================== Variables ==========================
const char date_flash[] = __DATE__ " " __TIME__;

int message = -1;

int x, y, z;
float azimuth;
int battlvl;
int stop_deguisement = 0;
uint32_t watchdog_manette;

int id_debug;
String message_debug;

unsigned long timer_musique;

//========================== Servomoteurs ==========================

// PAS PLUS DE 12 SERVOMOTEURS SOUS PEINE DE PERDRE LE CONTROLE VITESSE DU MOTEUR ARRIERE !!!!!!!!!!!!!!! librairie de merde serieux
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
  Wire.begin();
  Serial.begin(115200);
  Serial2.begin(57600);
  Serial3.begin(38400);

  Serial.println("==============================================");
  Serial.println("Robot GameTeam 2023 au démarrage . . .");
  Serial.println("(Peut refuser de démarrer si non alimenté)");
  Serial.println(String("mode débug : ") + mode_debug);
  Serial.print("programme uploadé le : "); Serial.print(__DATE__);  Serial.print(" à "); Serial.println(__TIME__);
  Serial.print("version : ");Serial.println(version_prog);
  Serial.println("concu pour l'AIO mère V3 et les cartes associées");
  
  qmc.init();

  pinMode(2,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(38,OUTPUT);
  pinMode(44,OUTPUT);
  pinMode(45,OUTPUT);
  pinMode(46,OUTPUT);
  pinMode(47,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(49,OUTPUT);
  pinMode(50,INPUT_PULLUP);
  pinMode(51,INPUT_PULLUP);
  pinMode(A15,INPUT);

  digitalWrite(45,1);
  digitalWrite(49,1);

  afficheurs.clear();
  afficheurs.setBrightness(0x0f);
  afficheurs.showNumberDec(8888);
  bargraph.setLevel(10);
  
  if(digitalRead(50)==0){
      battlvl = round(((((analogRead(A0+15)) - (607)) * (100)) / (165)) / (10));
  }

  analogWrite(2,127);
  
  levage_bras1.attach(36);
  bras1_haut();
  levage_bras2.attach(27);
  bras2_haut();
  tube_cerise.attach(30);
  cerise_ferme();
  
  delay(300);
  axe_bras1.attach(37);
  bras1_milieu();
  axe_bras2.attach(28);
  bras2_milieu();

  delay(300);
  baie_gauche_gauche.attach(34);
  baie_gauche_droite.attach(33);
  baie_gauche(0);
  baie_arriere_gauche.attach(42);
  baie_arriere_droite.attach(43);
  baie_arriere(1);
  baie_droite_gauche.attach(41);
  baie_droite_droite.attach(40);
  baie_droite(1);
  

  porte_aspiro.attach(39);
  porte_aspiro.write(160);

  bargraph.setLevel(1);
  digitalWrite(45,0);
  digitalWrite(47,0);
  digitalWrite(49,0);

  afficheurs.showNumberDec(score_defaut);

  analogWrite(2,0);

  if (mode_debug != 0){
    delay(100);
    analogWrite(2,127);
    delay(100);
    analogWrite(2,0);
    delay(100);
    analogWrite(2,127);
    delay(100);
    analogWrite(2,0);
    delay(100);
    Serial.println("ATTENTION : Mode débug actif, ne pas utiliser cette configuration en match !!!");

    levage_bras1.detach();
    levage_bras2.detach();
    axe_bras1.detach();
    axe_bras1.detach();  
  }
  
  Serial.println("Robot GameTeam 2023 prêt !");
  Serial.println("==============================================");

}

void loop() {

  qmc.read(&x, &y, &z,&azimuth);
  
  if(Serial3.available() > 0){
    //actu_score(); //ancienne version, qui ne correspond plus à l'application
    gestion_score();
    Serial.println("score tel");
  }

  if (millis() - watchdog_manette > 1000){analogWrite(5,0);analogWrite(6,0);analogWrite(7,0);analogWrite(8,0);analogWrite(9,0);analogWrite(10,0);analogWrite(11,0);analogWrite(12,0);}
  
  if(Serial2.available() > 0){
    message = Serial2.read();
    watchdog_manette = millis();
    debug(3, "message : ", message);

    
    mouvements(); //Serial.println("mvtmot");
    changement_mode(); //Serial.println("chmd");
    aspiro_balles(); //Serial.println("asp");
    //lancements_sequence_bras(); //Serial.println("seq");
    changement_manuel_score(); //Serial.println("mansc");
  }
  
  mouvements_bras(); //Serial.println("mvtbr");
  mouvements_baies(); //Serial.println("baies");
  deguisement(); //Serial.println("deg");
  
  
  //afficheur_etat();
  //alerte_buzzer();
  // voir onglet bargraph, fonctions afficheur_etat et alerte_buzzer inopérante pour le moment 
  
}
