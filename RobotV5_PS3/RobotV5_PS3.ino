
//==============================================================================//
//                                                                              //
//                          Programme GameTeam 2023 V5                          //
//            Conçu pour la Carte Logique V1 et les cartes associées            //
//                                                                              //
//==============================================================================//

//IMPORTANT : PEU IMPORTE CE QU'ON FOUT DANS LE CODE, LA FONCTION USB.Task() DOIT ETRE APPELEE TOUTES LES 1MS MAX !

//Note : le fichier de config la librairie USB host est a modifier obligatoirement pour avoir la manette BT !
//Note : il est important de calibrer le magnétomètre avec al librairie dédiée ! 

// A savoir : 
//  - à l'allumage, trois bips consécutifs indiquent une impossibilité de lancer le robot pour un match.
//  - une mention "ERREUR CRITIQUE" dans la console indique qu'une fonction n'a pas pu s'éxecuter correctement, et les actions associées n'ont pas été réalisées.
//  - une mention "ERREUR" dans la console indique qu'une fonction n'a pas été correctement utilisée, mais qu'elle a pu s'éxécuter tout de même.
//  - une mention "ALERTE" dans la console indique que le programme fonctionne correctement mais qu'un évènement requiert l'attention du pilote (ex : batterie faible)

//========================== Paramètres ==========================

#define manette_defaut 1          //0 : manette filaire (UART), 1 : manette BT
#define mode_deplacement_defaut 0 //0 : mode normal; 1 : mode azimuth
#define score_max 1               //1 : max 2 chiffres; 2 : max 3 chiffres
#define score_defaut 65           //score affiché par défaut
#define retrait_score 5           //nombre entier retiré au score en cas d'appui sur le bouton -
#define ajout_score 5             //nombre entier ajouté au score en cas d'appui sur le bouton +
#define delais_min_deguisement 2  //coefficient de délais minimal pour l'actualisation du déguisement
#define delais_max_deguisement 6  //coefficient de délais maximal pour l'actualisation du déguisement

#define musique 1                 //activation de la musique "Happy Birthday" lors de l'allumage du déguisement (0 : off, 1 : on)
#define buzzer 0                  //activation du buzzer embarqué (0: off, 1 : on) NB : ne desactive pas la musique 

#define activer_watchdog 1        //active un watchdog sur tout le programme, qui reset le robot si la loop freeze pendant plus d'une seconde (ou deux si la valeur est à 2)
#define autoriser_timeout_manette 1 // tout ets dans le titre , une valeur 2 provoque un reset à la déconexion

#define DeadzoneL 15             //coefficient de Deadzone du joystick de déplacement gauche (manette BT uniquement)
#define DeadzoneR 15             //coefficient de Deadzone du joystick de déplacement droite (manette BT uniquement)

#define version_prog 4.0          //version du programme (s'affiche dans la console pour distinguer les versions, à modifier manuellement)

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
#define EV1 2
#define pompe2 8
#define EV2 3

#define deguisement1 5
#define deguisement2 6

//a_lire_avant_de_compiler

//ATTENTION : OUVRIR LES CLAPETS UNIQUEMENT APRES AVOIR VENTOUSE LE PALET, POUR GARDER UN BON ALIGNEMENT ET LE METTRE CORRECTEMENT
//les EVs ont l'air d'influer l'une sur l'autre, ou de ne pas se fermer correctement

// ajouter un mode rumble sur la manette filaire

// changer le magnétomètre de place, l'éloigner de la batterie et faire sa carte dédiée

// ajouter un moyen de forcer la manette sur la manette actuelle (un bouton sur la manette) au cas ou on choisis la mauvaise avant un début de match

// IHM : le bouton pour relacher les cerises ? (dans les tubes et le reservoir)
// IHM : choix de la manette sur une glissière et le bouton pour reset les servos (ou tout desactiver a voir)
// /!\ il ne faut pas que les bras reviennent en pos initiale pendant les séquences, il faut que les séquences O vers G ne se soucient pas de pos initiale et finale et que ce soit géré entre elles
