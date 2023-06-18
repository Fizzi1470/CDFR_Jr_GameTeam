#define Servo_min_minis 80;
#define Servo_max_minis 510;
#define Servo_min_moyens 70;
#define Servo_max_moyens 510;
byte baie_avant_etat = 1;
byte baie_droite_etat = 1;
byte baie_gauche_etat = 1;
byte baie_arriere_etat = 1;
boolean antiblocage;

void bras1_ventouse(boolean statut_ventouse){
  digitalWrite(33 - pompe1, statut_ventouse);
  if(statut_ventouse == 1) statut_ventouse = 0; else statut_ventouse = 1;
  digitalWrite(33 - EV1, statut_ventouse);
}

void bras2_ventouse(boolean statut_ventouse){
  digitalWrite(33 - pompe2, statut_ventouse);
  if(statut_ventouse == 1) statut_ventouse = 0; else statut_ventouse = 1;
  digitalWrite(33 - EV2, statut_ventouse);
}

int port(String nom){
  byte valeur;
  if      (nom == F("Servo_baie_avant_droite"))    valeur = Servo_baie_avant_droite;
  else if (nom == F("Servo_baie_avant_gauche"))    valeur = Servo_baie_avant_gauche;
  else if (nom == F("Servo_baie_arriere_droite"))  valeur = Servo_baie_arriere_droite;
  else if (nom == F("Servo_baie_arriere_gauche"))  valeur = Servo_baie_arriere_gauche;
  else if (nom == F("Servo_baie_gauche_droite"))   valeur = Servo_baie_gauche_droite;
  else if (nom == F("Servo_baie_gauche_gauche"))   valeur = Servo_baie_gauche_gauche;  
  else if (nom == F("Servo_baie_droite_droite"))   valeur = Servo_baie_droite_droite;
  else if (nom == F("Servo_baie_droite_gauche"))   valeur = Servo_baie_droite_gauche;
  else if (nom == F("Servo_clapet_cerise"))        valeur = Servo_clapet_cerise;
  else if (nom == F("Servo_antiblocage"))          valeur = Servo_antiblocage;
  else if (nom == F("Servo_tube_cerise1"))         valeur = Servo_tube_cerise1;
  else if (nom == F("Servo_tube_cerise2"))         valeur = Servo_tube_cerise2;
  else if (nom == F("Servo_axe2"))                 valeur = Servo_axe2;
  else if (nom == F("Servo_levage2"))              valeur = Servo_levage2;
  else if (nom == F("Servo_axe1"))                 valeur = Servo_axe1;
  else if (nom == F("Servo_levage1"))              valeur = Servo_levage1;
  else {Serial.println(F("ERREUR CRITIQUE : la fonction port a été appellée avec un nom de moteur inexistant !"));}
  
  if      (valeur == 11)  return(2);
  else if (valeur == 12)  return(4);
  else if (valeur == 13)  return(1);
  else if (valeur == 14)  return(0); 
  else if (valeur == 15)  return(3); 
  else if (valeur == 16)  return(5); 
  else if (valeur == 17)  return(7); 
  else if (valeur == 18)  return(6); 
  else if (valeur == 21)  return(8);
  else if (valeur == 22)  return(9);
  else if (valeur == 23)  return(10);
  else if (valeur == 24)  return(11);
  else if (valeur == 25)  return(15);
  else if (valeur == 26)  return(14);
  else if (valeur == 27)  return(13);
  else if (valeur == 28)  return(12);
  else {Serial.println(F("ERREUR CRITIQUE : l'un des moteurs a été assigné à un port inexistant !"));}
}

int angle(byte valeur, String type){
  long minimum; long maximum;
  if (valeur > 180){ valeur = 180; }//note : crochet à retirer si on remet debug, pareil ligne en dessous//debug(11,F("ERREUR : la fonction angle a été appellée avec un angle supérieur à 180, valeur ramenée à 180"),-99);}
  else if (valeur < 0){ valeur = 0; }//debug(11,F("ERREUR : la fonction angle a été appellée avec un angle inférieur à 0, valeur ramenée à 0"),-99);}
  
  if(type = F("mini")){ minimum = Servo_min_minis; maximum = Servo_max_minis;}
  else if (type = F("moyen")) { minimum = Servo_min_moyens; maximum = Servo_max_moyens;}
  else {Serial.println(F("ERREUR CRITIQUE : la fonction angle a été appellée avec un type de moteur inexistant !"));}
  
  long a_return = (((maximum - minimum) * valeur) / 180) + minimum;
  if (a_return > maximum) {a_return = maximum;} //note : crochet à retirer si on remet debug, pareil ligne en dessous //debug(11,F("ERREUR : a_return trop grand, ramené à servo max"), -99);}
  else if (a_return < minimum) {a_return = minimum;}//debug(11,F("ERREUR : a_return trop petit, ramené à servo min"), -99);}
  return(a_return);
}

void servo(String moteur, byte angle_demande){
  int pin = port(moteur);
  String type;
  if (moteur == Servo_axe2 || moteur == Servo_axe1 || moteur == Servo_levage1 || moteur == Servo_levage2) type = F("moyen");
  else type = F("mini");
  pwm.setPWM(pin, 0, angle(angle_demande, type));
}

/*
 * Pour les baies : 2 indique une baie ouverte, 1 indique une baie entrouverte 0 indique une baie fermée, -1 fait changer la baie de position
 */

void baie_gauche(int statut){
  if (statut == -1){
    if (baie_gauche_etat == 1){statut = 2;}
    else {statut = 1;}
  }
  if (statut == 2){
    baie_gauche_etat = 2;
    servo(F("Servo_baie_gauche_droite"), 0);
    servo(F("Servo_baie_gauche_gauche"), 160);
  } else if (statut == 1){
    baie_gauche_etat = 1;
    servo(F("Servo_baie_gauche_droite"), 110);
    servo(F("Servo_baie_gauche_gauche"), 42);
  } else if (statut == 0){
    baie_gauche_etat = 0;
    servo(F("Servo_baie_gauche_droite"), 145);
    servo(F("Servo_baie_gauche_gauche"), 10);
  }
}
void baie_arriere(int statut){
  if (statut == -1){
    if (baie_arriere_etat == 1){statut = 2;}
    else {statut = 1;}
  }
  if (statut == 2){
    baie_arriere_etat = 2;
    servo(F("Servo_baie_arriere_droite"), 0);
    servo(F("Servo_baie_arriere_gauche"), 160);
  } else if (statut == 1){
    baie_arriere_etat = 1;
    servo(F("Servo_baie_arriere_droite"), 106);
    servo(F("Servo_baie_arriere_gauche"), 37);
  } else if (statut == 0){
    baie_arriere_etat = 0;
    servo(F("Servo_baie_arriere_droite"), 140);
    servo(F("Servo_baie_arriere_gauche"), 10);
  }
}
void baie_avant(int statut){
  if (statut == -1){
    if (baie_avant_etat == 1){statut = 2;}
    else {statut = 1;}
  }
  if (statut == 2){
    baie_avant_etat = 2;
    servo(F("Servo_baie_avant_droite"), 0);
    servo(F("Servo_baie_avant_gauche"), 179);
  } else if (statut == 1){
    baie_avant_etat = 1;
    servo(F("Servo_baie_avant_droite"), 125);
    servo(F("Servo_baie_avant_gauche"), 90);
  } else if (statut == 0){
    baie_avant_etat = 0;
    servo(F("Servo_baie_avant_droite"), 160);
    servo(F("Servo_baie_avant_gauche"), 40);
  }
}
void baie_droite(int statut){
  if (statut == -1){
    if (baie_droite_etat == 1){statut = 2;}
    else {statut = 1;}
  }
  if (statut == 2){
    baie_droite_etat = 2;
    servo(F("Servo_baie_droite_droite"), 0);
    servo(F("Servo_baie_droite_gauche"), 180);
  } else if (statut == 1){
    baie_droite_etat = 1;
    servo(F("Servo_baie_droite_droite"), 102);
    servo(F("Servo_baie_droite_gauche"), 69);
  } else if (statut == 0){
    baie_droite_etat = 0;
    servo(F("Servo_baie_droite_droite"), 145);
    servo(F("Servo_baie_droite_gauche"), 20);
  }
}

void gestion_sequences_cerises(){
  if(cerise_avant == 1 || cerise_gauche == 1){
    uint32_t delais = millis() - timer_sequence_cerise;
    if(delais < 500){                               if(cerise_avant){baie_avant(0);bras1_haut();cerise_avant_axe();}      if(cerise_gauche){baie_gauche(0);bras2_haut();cerise_gauche_axe();}          }
    else if(delais > 500 && delais < 900){          if(cerise_avant){bras1_bas();}                                        if(cerise_gauche){bras2_bas();}                                         }
    else if(delais > 900 && delais < 1400){         if(cerise_avant){cerise_bras1_ouvrir();}                              if(cerise_gauche){cerise_bras2_ouvrir();}                               }
    else if(delais > 1400 && delais < 1600){        if(cerise_avant){bras1_haut();}                                       if(cerise_gauche){bras2_haut();}                                        }
    else if(delais > 1600 && delais < 1700){        if(cerise_avant){bras1_milieu();cerise_bras1_fermer();baie_avant(1);} if(cerise_gauche){bras2_milieu();cerise_bras2_fermer();baie_gauche(1);} }
    else if(delais > 1700){cerise_avant = 0; cerise_gauche = 0;timer_sequence_cerise = millis();}
  } else

  if(cerise_droite == 1 || cerise_arriere == 1){
    uint32_t delais = millis() - timer_sequence_cerise;
    if(delais < 500){                               if(cerise_droite){baie_droite(0);bras1_haut();cerise_droite_axe();}     if(cerise_arriere){baie_arriere(0);bras2_haut();cerise_arriere_axe();}    }
    else if(delais > 500 && delais < 1200){         if(cerise_droite){bras1_bas();}                                         if(cerise_arriere){bras2_bas();}                                          }
    else if(delais > 1200 && delais < 1400){        if(cerise_droite){cerise_bras1_ouvrir();}                               if(cerise_arriere){cerise_bras2_ouvrir();}                                }
    else if(delais > 1400 && delais < 1600){        if(cerise_droite){bras1_haut();}                                        if(cerise_arriere){bras2_haut();}                                         }
    else if(delais > 1600 && delais < 1700){        if(cerise_droite){bras1_milieu();cerise_bras1_fermer();baie_droite(1);} if(cerise_arriere){bras2_milieu();cerise_bras2_fermer();baie_arriere(1);} }
    else if(delais > 1700){cerise_arriere = 0; cerise_droite = 0;}
  }
  if (cerise_arriere == 0 && cerise_droite == 0 && cerise_avant == 0 && cerise_gauche == 0){sequence_cerise_en_cours = 0;sequence_cerises_prete = 0;}
}


void gestion_sequences_principales(){
  uint32_t delais = millis() - timer_sequence_principal;

  if      (sequence == 412) sequence412(delais);
  else if (sequence == 421) sequence421(delais);
  else if (sequence == 413) sequence413(delais);
  else if (sequence == 431) sequence431(delais);
  else if (sequence == 423) sequence423(delais);
  else if (sequence == 432) sequence432(delais);
  else if (sequence == 123) sequence123(delais);
  else if (sequence == 132) sequence132(delais);
  else if (sequence == 124) sequence124(delais);
  else if (sequence == 142) sequence142(delais);
  else if (sequence == 134) sequence134(delais);
  else if (sequence == 143) sequence143(delais);
  else if (sequence == 213) sequence213(delais);
  else if (sequence == 231) sequence231(delais);
  else if (sequence == 243) sequence243(delais);
  else if (sequence == 234) sequence234(delais);
  else if (sequence == 214) sequence214(delais);
  else if (sequence == 241) sequence241(delais);
  else if (sequence == 312) sequence312(delais);
  else if (sequence == 321) sequence321(delais);
  else if (sequence == 314) sequence314(delais);
  else if (sequence == 341) sequence341(delais);
  else if (sequence == 324) sequence324(delais);
  else if (sequence == 342) sequence342(delais);
  else if (sequence == 199) sequence199(delais);
  else if (sequence == 299) sequence299(delais);
  else if (sequence == 399) sequence399(delais);
  else if (sequence == 499) sequence499(delais);
  
}

void ouvrir_reservoir(){servo(F("Servo_clapet_cerise"),110);reservoir = 1;}
void fermer_reservoir(){servo(F("Servo_clapet_cerise"),35);reservoir = 0;}
void changer_position_antiblocage_reservoir(){
  antiblocage = !antiblocage;
  if(antiblocage) servo(F("Servo_antiblocage"),10);
  else servo(F("Servo_antiblocage"),170);
}
void changer_etat_aspiro(){if(digitalRead(53) == 1) turbine = 0; else turbine = !turbine;
                            if (turbine == 1){digitalWrite(13, 1);if(baie_arriere_etat == 2){servo(F("Servo_baie_arriere_droite"), 110);}
                                                                  if(baie_droite_etat == 2){servo(F("Servo_baie_droite_gauche"), 65);}}
                            else {digitalWrite(13, 0);}}

// pour les changements de zone sans passe d'un bras à l'autre

void bras1_haut(){servo(F("Servo_levage1"),100);}
void bras1_bas(){servo(F("Servo_levage1"),42);}

void bras1_avant(){servo(F("Servo_axe1"),60);}
void bras1_milieu(){servo(F("Servo_axe1"),100);}
void bras1_arriere(){servo(F("Servo_axe1"),168);}

void bras2_haut(){servo(F("Servo_levage2"),5);}
void bras2_bas(){servo(F("Servo_levage2"),45);}

void bras2_avant(){servo(F("Servo_axe2"),122);}
void bras2_milieu(){servo(F("Servo_axe2"),75);}
void bras2_arriere(){servo(F("Servo_axe2"),10);}

// pour les changements de zone en passant d'un bras à l'autre

void bras1_passe_axe(){servo(F("Servo_axe1"),15);}
void bras1_passe_levage(){servo(F("Servo_levage1"),74);}

void bras2_passe_axe(){servo(F("Servo_axe2"),165);}
void bras2_passe_levage(){servo(F("Servo_levage2"),19);}

// pour les cerises
  
void cerise_avant_axe(){servo(F("Servo_axe1"),48);}
void cerise_gauche_axe(){servo(F("Servo_axe2"),132);}
void cerise_droite_axe(){servo(F("Servo_axe1"),158);}
void cerise_arriere_axe(){servo(F("Servo_axe2"),27);}

void cerise_bras2_ouvrir(){servo(F("Servo_tube_cerise2"),55);}
void cerise_bras2_preparer(){servo(F("Servo_tube_cerise2"),32);}
void cerise_bras2_fermer(){servo(F("Servo_tube_cerise2"),10);}
void cerise_bras2_vidanger(){servo(F("Servo_tube_cerise2"),179);}


void cerise_bras1_ouvrir(){servo(F("Servo_tube_cerise1"),100);}
void cerise_bras1_preparer(){servo(F("Servo_tube_cerise1"),130);}
void cerise_bras1_fermer(){servo(F("Servo_tube_cerise1"),160);}
void cerise_bras1_vidanger(){servo(F("Servo_tube_cerise1"),0);}
