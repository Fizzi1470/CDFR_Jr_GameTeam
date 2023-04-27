unsigned long rang_actuel = 1;
unsigned long cerise;
unsigned long zone_arriere;
unsigned long zone_gauche;
unsigned long zone_droite;
int prochaine_zone;
int ticket_zones[4];

uint32_t timer_cerise;
uint32_t timer_zone_arriere;
uint32_t timer_zone_gauche;
uint32_t timer_zone_droite;

int minima;
int liste_attente[10];

int zone_actuelle;

// note : A 209, B 210, X 211, Y 212
// note : HAUT 204, BAS 206, GAUCHE 203, DROITE 205

void lancements_sequence_bras(){
  if (message == 209){
    zone_droite = rang_actuel;
    debug(5, "zone droite demandée en position ", rang_actuel);
    rang_actuel = rang_actuel + 1;
  }
  if (message == 210){
    zone_arriere = rang_actuel;
    debug(5, "zone bas demandée en position ", rang_actuel);
    rang_actuel = rang_actuel + 1;
  }
  if (message == 211){
    cerise = rang_actuel;
    debug(5, "cerise demandée en position ", rang_actuel);
    rang_actuel = rang_actuel + 1;
  }
  if (message == 212){
    zone_gauche = rang_actuel;
    debug(5, "zone gauche demandée en position  ", rang_actuel);
    rang_actuel = rang_actuel + 1;
  }
  int ticket_zones[4] = {zone_gauche,zone_droite,zone_arriere,cerise};
}

void mouvements_bras(){

  /*if (zone_gauche != 0 || zone_droite != 0 || zone_arriere != 0 || cerise != 0){
    minima = rang_actuel;
    for(int tours_comptage = 0; tours_comptage = 4; tours_comptage++){
      if (ticket_zones[tours_comptage] != 0){
        if (minima > ticket_zones[tours_comptage]){
          minima = ticket_zones[tours_comptage];
          prochaine_zone = tours_comptage;
        }
      }
    }
  }


  
  */

  //prochaine_zone donne l'identifiant de la prochaine zone à utiliser (0 : zone gauche, 1 : zone droite, 2 : zone arriere, 3 : cerise)

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
  
  if(zone_actuelle == 1){ //Cerise
    if (millis() - timer_cerise < 200){                                   bras1_ventouse(0);
                                                                          bras1_avant_cerise();
                                                                          bras1_haut();}
    if (millis() - timer_cerise > 200 && millis() - timer_cerise < 700) { bras1_bas(); }
    if (millis() - timer_cerise > 700 && millis() - timer_cerise < 1200){ cerise_ouvert(); }
    if (millis() - timer_cerise > 1200 && millis() - timer_cerise < 1700){bras1_haut(); }
    if (millis() - timer_cerise > 1700 ){                                 cerise_ferme();
                                                                          bras1_milieu();
                                                                          cerise = 0;
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
                                                                                         zone_droite = 0;
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
                                                                                    zone_gauche = 0;
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
                                                                                      zone_arriere = 0;
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
  
}
