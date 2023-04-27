//==============================================================================//
//                                                                              //
//                          Programme GameTeam 2023 V2                          //
//            Conçu pour la Carte Logique V1 et les cartes associées            //
//                                                                              //
//==============================================================================//

// Notes : 
//  - à l'allumage, trois bips consécutifs indiquent une impossibilité de lancer le robot pour un match.
//  - une mention "ERREUR CRITIQUE" dans la console indique qu'une fonction n'a pas pu s'éxecuter correctement, et les actions associées n'ont pas été réalisées.
//  - une mention "ERREUR" dans la console indique qu'une fonction n'a pas été correctement utilisée, mais qu'elle a pu s'éxécuter tout de même.
//  - une mention "ALERTE" dans la console indique que le programme fonctionne correctement mais qu'un évènement requiert l'attention du pilote (ex : batterie faible)

//========================== Paramètres ==========================

const int manette_defaut = 2;  //1 : manette filaire (UART), 2 : manette BT
const int mode_deplacement_defaut = 1; // 1 : mode normal; 2 : mode azimuth
const int score_max = 1; // 1 : max 2 chiffres; 2 : max 3 chiffres
const int score_defaut = 65; // score affiché par défaut
const int retrait_score = 5; // nombre entier retiré au score en cas d'appui sur le bouton -
const int ajout_score = 5; // nombre entier ajouté au score en cas d'appui sur le bouton +
const int delais_min_deguisement = 2; // coefficient de délais minimal pour l'actualisation du déguisement
const int delais_max_deguisement = 4; // coefficient de délais maximal pour l'actualisation du déguisement

const int musique = 0; // activation de la musique "Happy Birthday" lors de l'allumage du déguisement (0 : off, 1 : on)
const int buzzer = 1; // activation du buzzer embarqué (0: off, 1 : on) NB : ne desactive pas la musique 

const int mode_debug = 12; // mode débug, voir modes plus bas (NB : a remettre sur 0 avant tout match !!!)
const int autoriser_console = 1; //active et désactive les réponses de la console (NB : a remettre sur 0 avant tout match !!!)
// baud_rate : 115200
const int desac_bras = 0; // désactive les servomoteurs des bras après l'initialisation (0: off, 1 : on)

const int DeadzoneL = 250; //coefficient de Deadzone du joystick de déplacement gauche (manette BT uniquement)
const int DeadzoneR = 250; //coefficient de Deadzone du joystick de déplacement droite (manette BT uniquement)

const float version_prog = 2.1; // version du programme (s'affiche dans la console pour distinguer les versions, à modifier manuellement)

/*  Modes debug disponibles :
 *  0: éteint A REMETTRE SUR ETEINT PENDANT LES MATCHS, DELAIS SUPP SINON
 *  1: informations relatives aux déplacements
 *  2: informations relatives aux scores
 *  3: relayement des messages reçus
 *  4: informations relatives à l'aspirateur de balles
 *  5: informations relatives aux mouvements de bras
 *  6: informations relatives au déguisement
 *  7: informations relatives au changement de mode
 *  8: informations sur les fonctions principales en cours d'execution
 *  9: informations relatives à l'IHM
 *  10:informations relatives à la communication série au pc
 *  11:informations relatives aux fonctions des servomoteurs
 *  12:informations relatives à la manette BT
 */

//========================== Pinout ==========================
// Premier chiffre indique la carte satellite (1 celle du bas et 2 celle du haut), deuxième chiffre indique le port (de 11 à 18 et de 21 à 28) (Ou pins directs PWM 19 ou 29)

const int Servo_levage1 = 21;
const int Servo_axe1 = 22;
const int Servo_levage2 = 28;
const int Servo_axe2 = 27;

const int Servo_baie_avant_droite = 14;
const int Servo_baie_avant_gauche = 13;
const int Servo_baie_arriere_droite = 17;
const int Servo_baie_arriere_gauche = 18;
const int Servo_baie_gauche_droite = 16;
const int Servo_baie_gauche_gauche = 15;
const int Servo_baie_droite_droite = 11;
const int Servo_baie_droite_gauche = 12;

const int Servo_clapet_cerise = 24;
const int Servo_tube_cerise = 23;
const int Vibreur = 25;

//indique le numéro du header 12V, le header prévu pour la turbine étant le 1 (réservé) (de 2 à 8 restants)

const int pompe1 = 7;
const int EV1 = 5;
const int pompe2 = 8;
const int EV2 = 6;

const int deguisement1 = 3;
const int deguisement2 = 2;

//a_lire_avant_de_compiler
//NOTE : refonte de l'initialisation des pins, possiblement inadaptée au reste pour le moment
//NOTE : lib servo a degager
//NOTE : il est possible de faire aller plus loin les servomoteurs en donnant des paramètres à Servo.attach
//NOTE : PCA a calibrer à l'oscillo, voir exemple Servo de la lib
//NOTE : console, commande servos à finir (et autres commandes)
//NOTE : desac bras inactif
//NOTE : servo baie avant gauche atteint sa limite de travel trop tot
//rajouter un help(commande) qui indique ce qu'elle fait


//Ca va necessiter de réécrire tout le code
//mais, il faut prendre l'approche inverse et faire des ifs avec la manette / les messages serie reçus et non l'inverse 
//pour déclencher les fonctions selon les ifs et non selon les valeurs de message avail et message
//il faut tout simplement éviter de foutre toute la gestion manette isolée comme ça 











 
