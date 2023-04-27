
//==============================================================================//
//                                                                              //
//                          Programme GameTeam 2023 V3                          //
//            Conçu pour la Carte Logique V1 et les cartes associées            //
//                                                                              //
//==============================================================================//

//IMPORTANT : PEU IMPORTE CE QU'ON FOUT DANS LE CODE, LA FONCTION USB.Task() DOIT ETRE APPELEE TOUTES LES 1MS GRAND MAX !

//Note : le fichier de config la librairie USB host est a modifier obligatoirement pour avoir la manette BT !
//Note : il est important de calibrer le magnétomètre avec al librairie dédiée ! 

// A savoir : 
//  - à l'allumage, trois bips consécutifs indiquent une impossibilité de lancer le robot pour un match.
//  - une mention "ERREUR CRITIQUE" dans la console indique qu'une fonction n'a pas pu s'éxecuter correctement, et les actions associées n'ont pas été réalisées.
//  - une mention "ERREUR" dans la console indique qu'une fonction n'a pas été correctement utilisée, mais qu'elle a pu s'éxécuter tout de même.
//  - une mention "ALERTE" dans la console indique que le programme fonctionne correctement mais qu'un évènement requiert l'attention du pilote (ex : batterie faible)

//========================== Paramètres ==========================

#define manette_defaut 2          //1 : manette filaire (UART), 2 : manette BT
#define mode_deplacement_defaut 1 //1 : mode normal; 2 : mode azimuth
#define score_max 1               //1 : max 2 chiffres; 2 : max 3 chiffres
#define score_defaut 65           //score affiché par défaut
#define retrait_score 5           //nombre entier retiré au score en cas d'appui sur le bouton -
#define ajout_score 5             //nombre entier ajouté au score en cas d'appui sur le bouton +
#define delais_min_deguisement 2  //coefficient de délais minimal pour l'actualisation du déguisement
#define delais_max_deguisement 4  //coefficient de délais maximal pour l'actualisation du déguisement

#define musique 0                 //activation de la musique "Happy Birthday" lors de l'allumage du déguisement (0 : off, 1 : on)
#define buzzer 0                  //activation du buzzer embarqué (0: off, 1 : on) NB : ne desactive pas la musique 

#define debug_mode 0              //mode débug, voir modes plus bas (NB : a remettre sur 0 avant tout match !!!)
#define autoriser_console 1       // baud_rate : 115200 //active et désactive les réponses de la console (NB : a remettre sur 0 avant tout match !!!)
#define desac_bras 0              //désactive les servomoteurs des bras après l'initialisation (0: off, 1 : on)
#define activer_watchdog 1        //active un watchdog sur tout le programme, qui reset le robot si la loop freeze pendant plus d'une seconde
#define autoriser_timeout_manette 1 // tout ets dans le titre , une valeur 2 provoque un reset à la déconexion

#define DeadzoneL 250             //coefficient de Deadzone du joystick de déplacement gauche (manette BT uniquement)
#define DeadzoneR 250             //coefficient de Deadzone du joystick de déplacement droite (manette BT uniquement)

#define version_prog 3.1          //version du programme (s'affiche dans la console pour distinguer les versions, à modifier manuellement)

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

#define Servo_levage1 22
#define Servo_axe1 21
#define Servo_levage2 28
#define Servo_axe2 27
#define Servo_tube_cerise1 23

#define Servo_baie_avant_droite 14
#define Servo_baie_avant_gauche 13
#define Servo_baie_arriere_droite 17
#define Servo_baie_arriere_gauche 18
#define Servo_baie_gauche_droite 16
#define Servo_baie_gauche_gauche 15
#define Servo_baie_droite_droite 11
#define Servo_baie_droite_gauche 12

#define Servo_clapet_cerise 24
#define Vibreur 25

//indique le numéro du header 12V, le header prévu pour la turbine étant le 1 (réservé) (de 2 à 8 restants)

#define pompe1 7
#define EV1 3
#define pompe2 8
#define EV2 2

#define deguisement1 5
#define deguisement2 6

//a_lire_avant_de_compiler
// certaines commandes sont pas dans info

// !!! retirer le delay(5) de la lecture de la console au profit d'une fonction non bloquante


//A faire : appel de Usb.task en sub 1ms, actuellement plutot dans les 1.5 voire plus dans certains cas
//soit une interruption avec timer, mais il ne reste normalement pas de timer hardware libre
//soit une interruption avec un pin, généré par une arduino externe, depuis le connecteur anexe
//soit mettre des Usb.Task absolument partout, mais c'est ultra moche
//faire également plus attention à l'opti du programme, les if else font perdre énormément de temps, même si leur condition n'est pas satisfaite

// la fonction debug est manquante dans beaucoup de parties du prog

//ATTENTION : OUVRIR LES CLAPETS UNIQUEMENT APRES AVOIR VENTOUSE LE PALET, POUR GARDER UN BON ALIGNEMENT ET LE METTRE CORRECTEMENT
//les EVs ont l'air d'influer l'une sur l'autre, ou de ne pas se fermer correctement

// ajouter un mode rumble sur la manette filaire

//je crois qu'elle deco random encore
// changer le magnétomètre de place, l'éloigner de la batterie

// ajouter un moyen de forcer la manette sur la manette actuelle (un bouton sur la manette) au cas ou on choisis la mauvaise avant un début de match

// IHM : le bouton pour relacher les cerises ? (dans les tubes et le reservoir)
// IHM : choix de la manette sur une glissière et le bouton pour reset les servos (ou tout desactiver a voir)
// /!\ il ne faut pas que les bras reviennent en pos initiale pendant les séquences, il faut que les séquences O vers G ne se soucient pas de pos initiale et finale et que ce soit géré entre elles 
