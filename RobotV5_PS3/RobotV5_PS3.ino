
//==============================================================================//
//                                                                              //
//                          Programme GameTeam 2023 V5                          //
//            Conçu pour la Carte Logique V1 et les cartes associées            //
//                                 Version PS3                                  //
//                                                                              //
//==============================================================================//

//IMPORTANT : PEU IMPORTE CE QU'ON FOUT DANS LE CODE, LA FONCTION USB.Task() DOIT ETRE APPELEE TOUTES LES 1MS MAX !

//Note : le fichier de config la librairie USB host est a modifier obligatoirement pour avoir la manette BT ! (modifier les pins SS et INT)
//Note : il est important de calibrer le magnétomètre avec la librairie dédiée ! 

//========================== Paramètres ==========================

#define manette_defaut 1          //0 : manette filaire (UART), 1 : manette BT
#define mode_deplacement_defaut 1 //0 : mode normal; 1 : mode azimuth
#define score_max 2               //1 : max 2 chiffres; 2 : max 3 chiffres
#define score_defaut 80           //score affiché par défaut
#define retrait_score 5           //nombre entier retiré au score en cas d'appui sur le bouton -
#define ajout_score 5             //nombre entier ajouté au score en cas d'appui sur le bouton +
#define delais_min_deguisement 2  //coefficient de délais minimal pour l'actualisation du déguisement
#define delais_max_deguisement 6  //coefficient de délais maximal pour l'actualisation du déguisement

#define musique 1                 //activation de la musique "Happy Birthday" lors de l'allumage du déguisement (0 : off, 1 : on)
//#define buzzer 0                  //activation du buzzer embarqué (0: off, 1 : on) NB : ne desactive pas la musique 

#define activer_watchdog 1        //active un watchdog sur tout le programme, qui reset le robot si la loop freeze pendant plus d'une seconde (ou deux si la valeur est à 2)

#define DeadzoneL 15             //Deadzone du joystick de déplacement gauche (manette BT uniquement)
#define DeadzoneR 15             //Deadzone du joystick de déplacement droite (manette BT uniquement)

#define version_prog 5.2          //version du programme (s'affiche dans la console pour distinguer les versions, à modifier manuellement)

//========================== Pinout ==========================
// Premier chiffre indique la carte satellite (1 celle du bas et 2 celle du haut), deuxième chiffre indique le port (de 11 à 18 et de 21 à 28) (Ou pins directs PWM 19 ou 29)

#define Servo_levage1 22
#define Servo_axe1 21
#define Servo_levage2 28
#define Servo_axe2 27
#define Servo_tube_cerise1 23
#define Servo_tube_cerise2 26

#define Servo_baie_avant_droite 14
#define Servo_baie_avant_gauche 13
#define Servo_baie_arriere_droite 17
#define Servo_baie_arriere_gauche 18
#define Servo_baie_gauche_droite 16
#define Servo_baie_gauche_gauche 15
#define Servo_baie_droite_droite 11
#define Servo_baie_droite_gauche 12

#define Servo_clapet_cerise 24
#define Servo_antiblocage 25

//indique le numéro du header 12V, le header prévu pour la turbine étant le 1 (réservé) (de 2 à 8 restants)

#define pompe1 7
#define EV1 2
#define pompe2 8
#define EV2 4

#define deguisement1 5
#define deguisement2 6

//a_lire_avant_de_compiler

//Le arrière vers droite, temps de descente du bras trop court, le "lâche" au dessus de la baie au lieu de proprement le descendre puis le lacher
//Essayer d'accélérer un peu la transmission de la valeur d'azimuth pour fluidifier les mouvements de rotation en déplacement

//ATTENTION : OUVRIR LES CLAPETS UNIQUEMENT APRES AVOIR VENTOUSE LE PALET, POUR GARDER UN BON ALIGNEMENT ET LE METTRE CORRECTEMENT

// ajouter un mode rumble

// ajouter un moyen de forcer la manette sur la manette actuelle (un bouton sur la manette) au cas ou on choisis la mauvaise avant un début de match
