const int bras1_haut_angle = 107;
const int bras1_passe_levage_angle = 92;
const int bras1_bas_angle = 57;

const int bras1_arriere_angle = 180;
const int bras1_milieu_angle = 115;
const int bras1_passe_axe_angle = 0;
const int bras1_avant_angle = 52;
const int bras1_avant_cerise_angle = 40;
const int bras1_avant_passe_gauche_angle = 50;
const int bras1_avant_passe_arriere_angle = 60;

const int bras2_haut_angle = 10;
const int bras2_passe_levage_angle = 20;
const int bras2_bas_angle = 55;

const int bras2_arriere_angle = 0;
const int bras2_milieu_angle = 80;
const int bras2_passe_axe_angle = 180;
const int bras2_avant_angle = 125;

const int tube_cerise_ouvert = 40;
const int tube_cerise_ferme = 77;


const int Servo_min_minis = 80;
const int Servo_max_minis = 510;
const int Servo_min_moyens = 70;
const int Servo_max_moyens = 510;

//les éléments en dessous de cette ligne ne sont pas des paramètres

int baie_avant_etat;
int baie_droite_etat;
int baie_gauche_etat;
int baie_arriere_etat;

int port(String nom){
  int valeur;
  if      (nom == "Servo_baie_avant_droite")    valeur = Servo_baie_avant_droite;
  else if (nom == "Servo_baie_avant_gauche")    valeur = Servo_baie_avant_gauche;
  else if (nom == "Servo_baie_arriere_droite")  valeur = Servo_baie_arriere_droite;
  else if (nom == "Servo_baie_arriere_gauche")  valeur = Servo_baie_arriere_gauche;
  else if (nom == "Servo_baie_gauche_droite")   valeur = Servo_baie_gauche_droite;
  else if (nom == "Servo_baie_gauche_gauche")   valeur = Servo_baie_gauche_gauche;  
  else if (nom == "Servo_baie_droite_droite")   valeur = Servo_baie_droite_droite;
  else if (nom == "Servo_baie_droite_gauche")   valeur = Servo_baie_droite_gauche;
  else if (nom == "Servo_clapet_cerise")        valeur = Servo_clapet_cerise;
  else if (nom == "Servo_tube_cerise")          valeur = Servo_tube_cerise;
  else if (nom == "Servo_axe2")                 valeur = Servo_axe2;
  else if (nom == "Servo_levage2")              valeur = Servo_levage2;
  else if (nom == "Servo_axe1")                 valeur = Servo_axe1;
  else if (nom == "Servo_levage1")              valeur = Servo_levage1;
  else {Serial.print("ERREUR CRITIQUE : la fonction port a été appellée avec un nom de moteur inexistant !");alerte(2, "Moteur_inexistant");}
  debug(11, "valeur de port : ", valeur);
  
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
  else {Serial.print("ERREUR CRITIQUE : l'un des moteur a été assigné à un port inexistant !");alerte(2, "Port_inexistant");}
}
int angle(int valeur, String type){
  long minimum; long maximum;
  if (valeur > 180){ valeur = 180; Serial.print("ERREUR : la fonction angle a été appellée avec un angle supérieur à 180");}
  else if (valeur < 0){ valeur = 0; Serial.print("ERREUR : la fonction angle a été appellée avec un angle inférieur à 0");}
  if(type = "mini"){ minimum = Servo_min_minis; maximum = Servo_max_minis;}
  else if (type = "moyen") { minimum = Servo_min_moyens; maximum = Servo_max_moyens;}
  else {Serial.print("ERREUR CRITIQUE : la fonction angle a été appellée avec un type de moteur inexistant !");alerte(2, "Servo_inexistant");}
  long a_return = (((maximum - minimum) * valeur) / 180) + minimum;
  debug(11, "angle demande " ,valeur);
  debug(11, type ,-99);
  debug(11, "minimum ", minimum);
  debug(11, "maximum ", maximum);
  debug(11, "equivalent ",a_return);
  return(a_return);
}
void servo(String moteur, int angle_demande){
  int pin = port(moteur);
  String type;
  if (moteur == Servo_axe2 || moteur == Servo_axe1 || moteur == Servo_levage1 || moteur == Servo_levage2) type = "moyen";
  else type = "mini";
  pwm.setPWM(pin, 0, angle(angle_demande, type));
}

void debug(int id_debug, String message_debug, double info_add){
  if (id_debug == mode_debug){
    if (info_add == -99){Serial.println(message_debug);}
    else{Serial.println(message_debug + String(info_add));}
  }
}

void cerise_ouvert(){
  /*tests, à ne pas utiliser en condition réelle
  int z = tube_cerise_ferme;
  tube_cerise.write(tube_cerise_ferme);
  while(z > tube_cerise_ouvert){
    delay(50);
    tube_cerise.write(z);
    z = z - 1 ;
  }
  */
  tube_cerise.write(tube_cerise_ouvert);

}
void cerise_ferme(){
  tube_cerise.write(tube_cerise_ferme);
}


void bras1_haut(){
  levage_bras1.write(bras1_haut_angle);
}
void bras1_passe_levage(){
  levage_bras1.write(bras1_passe_levage_angle);
}
void bras1_bas(){
  levage_bras1.write(bras1_bas_angle);
}
void bras1_arriere(){
  axe_bras1.write(bras1_arriere_angle);
}
void bras1_milieu(){
  axe_bras1.write(bras1_milieu_angle);
}
void bras1_passe_axe(){
  axe_bras1.write(bras1_passe_axe_angle);
}
void bras1_avant(){
  axe_bras1.write(bras1_avant_angle);
}
void bras1_avant_cerise(){
  axe_bras1.write(bras1_avant_cerise_angle);
}
void bras1_avant_passe_gauche(){
    axe_bras1.write(bras1_avant_passe_gauche_angle);
}
void bras1_avant_passe_arriere(){
    axe_bras1.write(bras1_avant_passe_arriere_angle);
}
void bras1_ventouse(int statut_ventouse){
  digitalWrite(23 + pompe1, statut_ventouse);
  if(statut_ventouse == 1) statut_ventouse = 0; else statut_ventouse = 1;
  digitalWrite(23 + EV1, statut_ventouse);
}


void bras2_haut(){
  levage_bras2.write(bras2_haut_angle);
}
void bras2_passe_levage(){
  levage_bras2.write(bras2_passe_levage_angle);
}
void bras2_bas(){
  levage_bras2.write(bras2_bas_angle);
}
void bras2_arriere(){
  axe_bras2.write(bras2_arriere_angle);
}
void bras2_milieu(){
  axe_bras2.write(bras2_milieu_angle);
}
void bras2_passe_axe(){
  axe_bras2.write(bras2_passe_axe_angle);
}
void bras2_avant(){
  axe_bras2.write(bras2_avant_angle);
}
void bras2_ventouse(int statut_ventouse){
  digitalWrite(23 + pompe2, statut_ventouse);
  if(statut_ventouse == 1) statut_ventouse = 0; else statut_ventouse = 1;
  digitalWrite(23 + EV2, statut_ventouse);
}



/*
 * Pour les baies : 1 indique une baie ouverte, 0 indique une baie fermée, aucune valeur fait changer la baie de position
 */

void baie_gauche(int statut){
  if (statut == 1){
    baie_gauche_etat = 1;
    servo("Servo_baie_gauche_droite", 0);
    servo("Servo_baie_gauche_gauche", 160);
  } else if (statut == 0){
    baie_gauche_etat = 0;
    servo("Servo_baie_gauche_droite", 145);
    servo("Servo_baie_gauche_gauche", 10);
  } else if (baie_gauche_etat == 0){
    baie_gauche_etat = 1;
  } else {
    baie_gauche_etat = 0;
  }
}
void baie_arriere(int statut){
  if (statut == 1){
    baie_arriere_etat = 1;
    servo("Servo_baie_arriere_droite", 0);
    servo("Servo_baie_arriere_gauche", 160);
  } else if (statut == 0){
    baie_arriere_etat = 0;
    servo("Servo_baie_arriere_droite", 150);
    servo("Servo_baie_arriere_gauche", 10);
  } else if (baie_arriere_etat == 0){
    baie_arriere_etat = 1;
  } else {
    baie_arriere_etat = 0;
  }
}
void baie_avant(int statut){
  if (statut == 1){
    baie_avant_etat = 1;
    servo("Servo_baie_avant_droite", 0);
    servo("Servo_baie_avant_gauche", 180);
  } else if (statut == 0){
    baie_avant_etat = 0;
    servo("Servo_baie_avant_droite", 160);
    servo("Servo_baie_avant_gauche", 40);
  }else if (baie_avant_etat == 0){
    baie_avant_etat = 1;
  } else {
    baie_avant_etat = 0;
  }
}
void baie_droite(int statut){
  if (statut == 1){
    baie_droite_etat = 1;
    servo("Servo_baie_droite_droite", 0);
    servo("Servo_baie_droite_gauche", 180);
  } else if (statut == 0){
    baie_droite_etat = 0;
    servo("Servo_baie_droite_droite", 145);
    servo("Servo_baie_droite_gauche", 20);
  }else if (baie_droite_etat == 0){
    baie_droite_etat = 1;
  } else {
    baie_droite_etat = 0; 
  }
}
