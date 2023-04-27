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


void debug(int id_debug, String message_debug, double info_add){
  if (id_debug == mode_debug)
    if (info_add == -99){
      Serial.println(message_debug);
    }else{
      Serial.println(message_debug + String(info_add));
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
void bras1_ventouse(int statut_ventouse1){
  digitalWrite(46, statut_ventouse1);
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
void bras2_ventouse(int statut_ventouse2){
  digitalWrite(44, statut_ventouse2);
}


void baie_gauche(int statut){
  if (statut == 0){
    baie_gauche_gauche.write(90);
    baie_gauche_droite.write(105);
  } else if (statut == 1){
    baie_gauche_gauche.write(145);
    baie_gauche_droite.write(50);  
  } else if (baie_gauche_gauche.read() == 145){
    baie_gauche_gauche.write(90);
    baie_gauche_droite.write(105);
  } else {
    baie_gauche_gauche.write(145);
    baie_gauche_droite.write(50);
  }
}
void baie_arriere(int statut){
  if (statut == 1){
    baie_arriere_gauche.write(110);
    baie_arriere_droite.write(50);
  } else if (statut == 0){
    baie_arriere_gauche.write(40);
    baie_arriere_droite.write(135);  
  }else if (baie_arriere_gauche.read() == 40){
    baie_arriere_gauche.write(110);
    baie_arriere_droite.write(50);
  } else {
    baie_arriere_gauche.write(40);
    baie_arriere_droite.write(135); 
  }
}
void baie_droite(int statut){
  if (statut == 1){
    baie_droite_gauche.write(70);
    baie_droite_droite.write(60);
  } else if (statut == 0){
    baie_droite_gauche.write(20);
    baie_droite_droite.write(130);  
  }else if (baie_droite_gauche.read() == 25){
    baie_droite_gauche.write(80);
    baie_droite_droite.write(50);
  } else {
    baie_droite_gauche.write(25);
    baie_droite_droite.write(130); 
  }
}
