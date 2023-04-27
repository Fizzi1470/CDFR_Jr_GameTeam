uint32_t timer_cerise;
uint32_t timer_zone_arriere;
uint32_t timer_zone_gauche;
uint32_t timer_zone_droite;
int zone_actuelle;

int mode_sequence;
int sequence;
int lancer_sequence;

// note : A 209, B 210, X 211, Y 212
// note : HAUT 204, BAS 206, GAUCHE 203, DROITE 205

void lancements_sequence_bras(){
  if(message == 214){
    mode_sequence = 1;
  } else if (message = 220){
    mode_sequence = 0;
    if (sequence < 100 || sequence > 1000) sequence = 0;
    else {lancer_sequence = 1;timer_sequence = millis();}
  }
  if(mode_sequence == 1){
    if (message == 204) sequence = (sequence*10) + 1;
    if (message == 206) sequence = (sequence*10) + 2;
    if (message == 203) sequence = (sequence*10) + 3;
    if (message == 205) sequence = (sequence*10) + 4;
  }
}

void sequences(){
  if(lancer_sequence == 1){
   if      (sequence == 412) sequence412();
   else if (sequence == 421) sequence421();
   else if (sequence == 413) sequence413();
   else if (sequence == 431) sequence431();
   else if (sequence == 423) sequence423();
   else if (sequence == 432) sequence432();
   else if (sequence == 123) sequence123();
   else if (sequence == 132) sequence132();
   else if (sequence == 124) sequence124();
   else if (sequence == 142) sequence142();
   else if (sequence == 134) sequence134();
   else if (sequence == 143) sequence143();
   else if (sequence == 213) sequence213();
   else if (sequence == 231) sequence231();
   else if (sequence == 243) sequence243();
   else if (sequence == 234) sequence234();
   else if (sequence == 214) sequence214();
   else if (sequence == 241) sequence241();
   else if (sequence == 312) sequence312();
   else if (sequence == 321) sequence321();
   else if (sequence == 314) sequence314();
   else if (sequence == 341) sequence341();
   else if (sequence == 324) sequence324();
   else if (sequence == 342) sequence342();
  }
}

void mouvements_bras(){
  //prochaine_zone donne l'identifiant de la prochaine zone à utiliser (0 : zone gauche, 1 : zone droite, 2 : zone arriere, 3 : cerise)

  if(mode_sequence == 0){
    if(zone_actuelle == 0){
      if(message == 204){
        zone_actuelle = 1;
        timer_cerise = millis();
      }
      if(message == 205){
        zone_actuelle = 2;
        timer_zone_droite = millis();
      } 
      if(message == 203){
        zone_actuelle = 3;
        timer_zone_gauche = millis();
      } 
      if(message == 206){
        zone_actuelle = 4;
        timer_zone_arriere = millis();
      } 
    }
  }
  
  if(zone_actuelle == 1){ //Cerise
    if (millis() - timer_cerise < 200){                                   bras1_ventouse(0);
                                                                          bras1_avant_cerise();
                                                                          bras1_haut();}
    if (millis() - timer_cerise > 200 && millis() - timer_cerise < 700) { bras1_bas(); }
    if (millis() - timer_cerise > 700 && millis() - timer_cerise < 1200){ cerise_ouvert(); }
    if (millis() - timer_cerise > 1200 && millis() - timer_cerise < 1700){bras1_haut(); }
    if (millis() - timer_cerise > 1700 ){                                 cerise_ferme();
                                                                          bras1_milieu();
                                                                          zone_actuelle = 0; }
  }

  if(zone_actuelle == 2){ //Zone droite
    if (millis() - timer_zone_droite < 500){                                             bras1_ventouse(0);
                                                                                         baie_droite(0);
                                                                                         bras1_haut();
                                                                                         bras1_arriere();}
    if ((millis() - timer_zone_droite > 500) && (millis() - timer_zone_droite < 800))  { bras1_bas();
                                                                                         bras1_ventouse(1); 
                                                                                         baie_droite(1);}
    if ((millis() - timer_zone_droite > 800) && (millis() - timer_zone_droite < 1100)) { bras1_haut(); }
    if ((millis() - timer_zone_droite > 1100) && (millis() - timer_zone_droite < 1500)){ bras1_avant();}
    if ((millis() - timer_zone_droite > 1500) && (millis() - timer_zone_droite < 1800)){ bras1_bas(); 
                                                                                         baie_droite(0);}
    if ((millis() - timer_zone_droite > 1800) && (millis() - timer_zone_droite < 2100)){ bras1_ventouse(0);
                                                                                         bras1_haut(); }
    if (millis() - timer_zone_droite > 2100){                                            bras1_milieu();
                                                                                         zone_actuelle = 0; }    
  } 
  
if(zone_actuelle == 3){ //Zone gauche
    
    if (millis() - timer_zone_gauche < 500 ) {                                      bras1_ventouse(0);
                                                                                    bras2_ventouse(0);
                                                                                    bras1_haut();
                                                                                    bras2_haut();
                                                                                    bras1_passe_axe();
                                                                                    bras2_avant();
                                                                                    baie_gauche(1);}
    if (millis() - timer_zone_gauche > 500 && millis() - timer_zone_gauche < 800) { bras2_bas();
                                                                                    bras2_ventouse(1);}
    if (millis() - timer_zone_gauche > 800 && millis() - timer_zone_gauche < 1100){ baie_gauche(1);
                                                                                    bras2_haut(); }
    if (millis() - timer_zone_gauche > 1100 && millis() - timer_zone_gauche < 1600){bras2_passe_axe(); }
    if (millis() - timer_zone_gauche > 1600 && millis() - timer_zone_gauche < 1900){baie_gauche(0);
                                                                                    bras2_passe_levage();
                                                                                    bras1_passe_levage();
                                                                                    bras1_ventouse(1);}
    if (millis() - timer_zone_gauche > 1900 && millis() - timer_zone_gauche < 2200){bras2_ventouse(0);
                                                                                    bras1_haut();
                                                                                    bras2_haut(); }
    if (millis() - timer_zone_gauche > 2200 && millis() - timer_zone_gauche < 2500){bras1_avant_passe_gauche();
                                                                                    bras2_milieu(); }
    if (millis() - timer_zone_gauche > 2500 && millis() - timer_zone_gauche < 2800){bras1_bas(); }
    if (millis() - timer_zone_gauche > 2800 && millis() - timer_zone_gauche < 3100){bras1_ventouse(0);
                                                                                    bras1_haut();
                                                                                    bras2_haut(); }
    if (millis() - timer_zone_gauche > 3100 ){                                      bras1_milieu();
                                                                                    bras2_milieu();
                                                                                    zone_actuelle = 0; }  
  }

  if(zone_actuelle == 4){ //Zone arriere
    if (millis() - timer_zone_arriere < 300 ) {                                       bras1_ventouse(0);
                                                                                      bras2_ventouse(0);
                                                                                      baie_arriere(0);
                                                                                      bras1_haut();
                                                                                      bras2_haut();}
    if (millis() - timer_zone_arriere > 300 && millis() - timer_zone_arriere < 800){  bras2_arriere();
                                                                                      bras1_passe_axe();}
    if (millis() - timer_zone_arriere > 800 && millis() - timer_zone_arriere < 1200){ bras2_bas();
                                                                                      baie_arriere(1);
                                                                                      bras2_ventouse(1);}
    if (millis() - timer_zone_arriere > 1200 && millis() - timer_zone_arriere < 1500){bras2_haut();}
    if (millis() - timer_zone_arriere > 1500 && millis() - timer_zone_arriere < 2500){bras2_passe_axe();
                                                                                      baie_arriere(0);}
    if (millis() - timer_zone_arriere > 2500 && millis() - timer_zone_arriere < 2800){bras2_passe_levage();
                                                                                      bras1_passe_levage();
                                                                                      bras1_ventouse(1);}
    if (millis() - timer_zone_arriere > 2800 && millis() - timer_zone_arriere < 3100){bras2_ventouse(0);
                                                                                      //bras1_haut();
                                                                                      bras2_haut();}
    if (millis() - timer_zone_arriere > 3100 && millis() - timer_zone_arriere < 3600){bras1_avant_passe_arriere();
                                                                                      bras2_milieu();}
    if (millis() - timer_zone_arriere > 3600 && millis() - timer_zone_arriere < 3900){bras1_bas();}
    if (millis() - timer_zone_arriere > 3900 && millis() - timer_zone_arriere < 4200){bras1_ventouse(0);
                                                                                      bras1_haut();
                                                                                      bras2_haut();}
    if (millis() - timer_zone_arriere > 4200){                                        bras1_milieu();
                                                                                      bras2_milieu();
                                                                                      zone_actuelle = 0;}
  }
}





void mouvements_baies(){
  if (message == 212){
    baie_gauche(-1);
    message = -1;
  }
  if (message == 210){
    baie_arriere(-1);
    message = -1;
  }
  if (message == 209){
    baie_droite(-1);
    message = -1;
  }
  if (message == 211){
    baie_avant(-1);
    message = -1;
  } 
}
