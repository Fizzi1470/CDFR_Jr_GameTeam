uint32_t timer_sequence;

void lancer_sequence_cerises(){
  if (sequence_cerises_prete == 1 && sequence_cerise_en_cours == 0 && sequence_terminee == 1){sequence_cerise_en_cours = 1;timer_sequence_cerise = millis();}
}

void lancer_sequence(byte identifiant){
  if (sequence_terminee == 1 && sequence_cerise_en_cours == 0){
    identifiant_sequence = identifiant;
    timer_sequence = millis();
  }
}

/*
 * Cerise 1-4
 * droite 1
 * avant 2
 * arriere 3
 * gauche 4
 */

void gestion_sequences(){
  uint32_t delais = millis() - timer_sequence;

  if (identifiant_sequence == 1){// cerise avant
    if(delais < 500){baie_avant(0);bras1_haut();cerise_avant_axe();sequence_terminee = 0;cerise_bras1_preparer();}
    else if(delais > 500 && delais < 700){bras1_bas();}
    else if(delais > 700 && delais < 1200){cerise_bras1_ouvrir();}
    else if(delais > 1200 && delais < 1400){bras1_haut();}
    else if(delais > 1400 && delais < 1500){cerise_bras1_fermer();baie_avant(1);}
    else if(delais > 1500){sequence_terminee = 1;identifiant_sequence = 0;bras1_milieu();}
  
  } else
  if (identifiant_sequence == 12){ // droite vers avant
    if(delais < 500){baie_droite(0);bras1_haut();bras1_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 600){bras1_bas(); bras1_ventouse(1);}
    else if(delais > 600 && delais < 700){baie_droite(1);}
    else if(delais > 700 && delais < 1000){bras1_haut();}
    else if(delais > 1000 && delais < 1300){bras1_avant();}
    else if(delais > 1600 && delais < 1800){bras1_bas();}
    else if(delais > 2100 && delais < 2200){bras1_ventouse(0);bras1_haut();}
    else if(delais > 2200){sequence_terminee = 1;identifiant_sequence = 0;bras1_milieu();}
    
  } else
  if (identifiant_sequence == 21){ // avant vers droite
    if(delais < 500){baie_avant(0);bras1_haut();bras1_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 600){bras1_bas(); bras1_ventouse(1);}
    else if(delais > 600 && delais < 700){baie_avant(1);}
    else if(delais > 700 && delais < 1000){bras1_haut();}
    else if(delais > 1000 && delais < 1300){bras1_arriere();}
    else if(delais > 1600 && delais < 1800){bras1_bas();}
    else if(delais > 2100 && delais < 2200){bras1_haut();bras1_ventouse(0);}
    else if(delais > 2200){sequence_terminee = 1;identifiant_sequence = 0;bras1_milieu();}
  
  } else
  if (identifiant_sequence == 34){ //arriere vers gauche
    if(delais < 500){baie_arriere(0);bras2_haut();bras2_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 900){bras2_bas(); bras2_ventouse(1);}
    else if(delais > 900 && delais < 1000){baie_arriere(1);}
    else if(delais > 1000 && delais < 1300){bras2_haut();}
    else if(delais > 1300 && delais < 2000){bras2_avant();}
    else if(delais > 2000 && delais < 2300){bras2_bas();}
    else if(delais > 2300 && delais < 2400){bras2_haut();bras2_ventouse(0);}
    else if(delais > 2400){sequence_terminee = 1;identifiant_sequence = 0;bras2_milieu();}

  } else
  if (identifiant_sequence == 43){ // gauche vers arriere
    if(delais < 500){baie_gauche(0);bras2_haut();bras2_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 600){bras2_bas(); bras2_ventouse(1);}
    else if(delais > 600 && delais < 700){baie_gauche(1);}
    else if(delais > 700 && delais < 1000){bras2_haut();}
    else if(delais > 1000 && delais < 1300){bras2_arriere();}
    else if(delais > 1600 && delais < 2000){bras2_bas();}
    else if(delais > 2300 && delais < 2400){bras2_haut();bras2_ventouse(0);}
    else if(delais > 2400){sequence_terminee = 1;identifiant_sequence = 0;bras2_milieu();}
    
  } else
  if(identifiant_sequence == 42){ //gauche vers avant
    if(delais < 500){baie_gauche(0);bras1_haut();bras1_passe_axe();bras2_haut();bras2_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras2_bas(); bras2_ventouse(1);}
    else if(delais > 700 && delais < 800){baie_gauche(1);}
    else if(delais > 800 && delais < 1100){bras2_haut();}
    else if(delais > 1100 && delais < 1400){bras2_passe_axe();}
    else if(delais > 1400 && delais < 1700){bras2_passe_levage();}
    else if(delais > 1700 && delais < 1900){bras1_passe_levage();bras1_ventouse(1);bras2_haut();}
    else if(delais > 2200 && delais < 2400){bras1_avant();bras1_haut();bras2_ventouse(0);}
    else if(delais > 2400 && delais < 2500){bras1_bas();bras2_milieu();}
    else if(delais > 2500 && delais < 2600){bras1_haut();bras1_ventouse(0);}
    else if(delais > 2600){sequence_terminee = 1;identifiant_sequence = 0;bras1_milieu();bras2_milieu();}

  } else
  if(identifiant_sequence == 24){ // avant vers gauche
    if(delais < 500){baie_avant(0);bras2_haut();bras2_passe_axe();bras1_haut();bras1_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras1_bas(); bras1_ventouse(1);}
    else if(delais > 700 && delais < 800){baie_avant(1);}
    else if(delais > 800 && delais < 1100){bras1_haut();}
    else if(delais > 1100 && delais < 1400){bras1_passe_axe();}
    else if(delais > 1400 && delais < 1700){bras1_passe_levage();}
    else if(delais > 1700 && delais < 1900){bras2_passe_levage();bras2_ventouse(1);bras1_haut();}
    else if(delais > 2200 && delais < 2400){bras2_avant();bras1_ventouse(0);}
    else if(delais > 2400 && delais < 2500){bras2_bas();bras1_milieu();}
    else if(delais > 2500 && delais < 2600){bras2_haut();bras2_ventouse(0);}
    else if(delais > 2600){sequence_terminee = 1;identifiant_sequence = 0;bras1_milieu();bras2_milieu();}

  } else
  if(identifiant_sequence == 32){ // arriere vers avant
    if(delais < 500){baie_arriere(0);bras2_haut();bras2_arriere();bras1_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 600){bras2_bas(); bras2_ventouse(1);}
    else if(delais > 600 && delais < 700){baie_arriere(1);}
    else if(delais > 700 && delais < 1100){bras2_haut();}
    else if(delais > 1100 && delais < 1700){bras2_passe_axe();bras1_haut();}
    else if(delais > 1700 && delais < 2000){bras2_passe_levage();bras1_passe_axe();}
    else if(delais > 2000 && delais < 2200){bras1_passe_levage();bras1_ventouse(1);bras2_haut();}
    else if(delais > 2400 && delais < 2500){bras2_ventouse(0);bras1_haut();}
    else if(delais > 2500 && delais < 2700){bras2_milieu();bras1_avant();}
    else if(delais > 2700 && delais < 2900){bras1_bas();}
    else if(delais > 2900 && delais < 3000){bras1_haut();bras1_ventouse(0);}
    else if(delais > 3000){sequence_terminee = 1;identifiant_sequence = 0;bras1_milieu();bras2_milieu();}

  } else
  if (identifiant_sequence == 23){ // avant vers arriere
    if(delais < 500){baie_avant(0);bras1_haut();bras1_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 600){bras1_bas(); bras1_ventouse(1);}
    else if(delais > 600 && delais < 700){baie_avant(1);}
    else if(delais > 700 && delais < 1000){bras1_haut();}
    else if(delais > 1000 && delais < 1300){bras1_passe_axe();bras2_haut();}
    else if(delais > 1300 && delais < 1700){bras1_passe_levage();bras2_passe_axe();}
    else if(delais > 1700 && delais < 1800){bras2_passe_levage();bras2_ventouse(1);bras1_haut();}
    else if(delais > 1800 && delais < 2500){bras1_avant();bras1_ventouse(0);bras2_arriere();bras2_haut();}
    else if(delais > 2500 && delais < 2700){bras2_bas();}
    else if(delais > 2700 && delais < 2800){bras2_haut();bras2_ventouse(0);}
    else if(delais > 2800){sequence_terminee = 1;identifiant_sequence = 0;bras1_milieu();bras2_milieu();}
  
  } else
  if(identifiant_sequence == 31){ // arriere vers droite
    if(delais < 500){baie_arriere(0);bras2_haut();bras1_haut();bras2_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 600){bras2_bas();bras1_avant();bras2_ventouse(1);}
    else if(delais > 600 && delais < 700){baie_arriere(1);}
    else if(delais > 700 && delais < 1100){bras2_haut();}
    else if(delais > 1100 && delais < 1800){bras2_passe_axe();bras1_haut();}
    else if(delais > 1800 && delais < 2200){bras2_passe_levage();bras1_passe_axe();}
    else if(delais > 2200 && delais < 2400){bras1_passe_levage();bras1_ventouse(1);bras2_haut();}
    else if(delais > 2400 && delais < 3000){bras1_arriere();bras2_ventouse(0);bras2_avant();bras1_haut();}
    else if(delais > 3000 && delais < 3400){bras1_bas();}
    else if(delais > 3400 && delais < 3500){bras1_haut();bras1_ventouse(0);}
    else if(delais > 3500){sequence_terminee = 1;identifiant_sequence = 0;bras1_milieu();bras2_milieu();}

  } else
  if (identifiant_sequence == 13){ // droite vers arriere
    if(delais < 500){baie_droite(0);bras2_haut();bras1_haut();bras1_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 600){bras1_bas();bras2_avant();bras1_ventouse(1);}
    else if(delais > 600 && delais < 700){baie_droite(1);}
    else if(delais > 700 && delais < 1000){bras1_haut();}
    else if(delais > 1000 && delais < 1700){bras1_passe_axe();bras2_haut();}
    else if(delais > 1700 && delais < 2000){bras1_passe_levage();bras2_passe_axe();}
    else if(delais > 2000 && delais < 2200){bras2_passe_levage();bras2_ventouse(1);bras1_haut();}
    else if(delais > 2400 && delais < 3100){bras2_arriere();bras1_ventouse(0);bras1_milieu();bras2_haut();}
    else if(delais > 3100 && delais < 3300){bras2_bas();}
    else if(delais > 3300 && delais < 3400){bras2_haut();bras2_ventouse(0);}
    else if(delais > 3400){sequence_terminee = 1;identifiant_sequence = 0;bras1_milieu();bras2_milieu();}

  } else
  if (identifiant_sequence == 41){ // gauche vers droite
    if(delais < 500){baie_gauche(0);bras2_haut();bras1_haut();bras2_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 600){bras2_bas();bras1_avant();bras2_ventouse(1);}
    else if(delais > 600 && delais < 700){baie_gauche(1);}
    else if(delais > 700 && delais < 1300){bras2_haut();}
    else if(delais > 1300 && delais < 1900){bras2_passe_axe();bras1_haut();}
    else if(delais > 1900 && delais < 2200){bras2_passe_levage();bras1_passe_axe();}
    else if(delais > 2200 && delais < 2400){bras1_passe_levage();bras1_ventouse(1);bras2_haut();}
    else if(delais > 2400 && delais < 3100){bras1_arriere();bras2_ventouse(0);bras2_milieu();bras1_haut();}
    else if(delais > 3100 && delais < 3200){bras1_bas();}
    else if(delais > 3200 && delais < 3300){bras1_haut();bras1_ventouse(0);}
    else if(delais > 3300){sequence_terminee = 1;identifiant_sequence = 0;bras1_milieu();bras2_milieu();}
  } else
  if (identifiant_sequence == 14){ // droite vers gauche
    if(delais < 500){baie_droite(0);bras2_haut();bras1_haut();bras1_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 600){bras1_bas();bras2_avant();bras1_ventouse(1);}
    else if(delais > 600 && delais < 700){baie_droite(1);}
    else if(delais > 700 && delais < 1000){bras1_haut();}
    else if(delais > 1000 && delais < 1700){bras1_passe_axe();bras2_haut();}
    else if(delais > 1700 && delais < 2000){bras1_passe_levage();bras2_passe_axe();}
    else if(delais > 2000 && delais < 2200){bras2_passe_levage();bras2_ventouse(1);bras1_haut();}
    else if(delais > 2400 && delais < 2800){bras2_avant();bras1_ventouse(0);bras1_milieu();bras2_haut();}
    else if(delais > 2800 && delais < 3000){bras2_bas();}
    else if(delais > 3000 && delais < 3100){bras2_haut();bras2_ventouse(0);}
    else if(delais > 3100){sequence_terminee = 1;identifiant_sequence = 0;bras1_milieu();bras2_milieu();}
  }
}



/*
 * Cerise 1-4
 * droite 1
 * avant 2
 * arriere 3
 * gauche 4
 * X99 : séparation d'un gateau avec départ en zone X
 */
 
void sequence199(int delais){
  if(delais <= 2200)                        {lancer_sequence(12);}
  else if(delais > 2200 && delais <= 5300)  {lancer_sequence(14);}
  else if(delais > 5300){sequence_terminee = 1;identifiant_sequence = 0;sequence = 0;sequence_prete = 0;identifiant_sequence = 0;cerise_avant = 1;cerise_arriere = 0;cerise_droite = 1;cerise_gauche = 1;sequence_cerises_prete = 1;bras1_milieu();bras2_milieu();}
}
void sequence299(int delais){
  if(delais <= 2200)                        {lancer_sequence(21);}
  else if(delais > 2200 && delais <= 4800)  {lancer_sequence(24);}
  else if(delais > 4800){sequence_terminee = 1;identifiant_sequence = 0;sequence = 0;sequence_prete = 0;identifiant_sequence = 0;cerise_avant = 1;cerise_arriere = 0;cerise_droite = 1;cerise_gauche = 1;sequence_cerises_prete = 1;bras1_milieu();bras2_milieu();}
}
void sequence399(int delais){
  if(delais <= 2400)                        {lancer_sequence(34);}
  else if(delais > 2400 && delais <= 5400)  {lancer_sequence(32);}
  else if(delais > 5400){sequence_terminee = 1;identifiant_sequence = 0;sequence = 0;sequence_prete = 0;identifiant_sequence = 0;cerise_avant = 1;cerise_arriere = 1;cerise_droite = 0;cerise_gauche = 1;sequence_cerises_prete = 1;bras1_milieu();bras2_milieu();}
}
void sequence499(int delais){
  if(delais <= 2200)                        {lancer_sequence(43);}
  else if(delais > 2200 && delais <= 4800)  {lancer_sequence(42);}
  else if(delais > 4800){sequence_terminee = 1;identifiant_sequence = 0;sequence = 0;sequence_prete = 0;identifiant_sequence = 0;cerise_avant = 1;cerise_arriere = 1;cerise_droite = 0;cerise_gauche = 1;sequence_cerises_prete = 1;bras1_milieu();bras2_milieu();}
}
void sequence431(int delais){
  if(delais < 3000)                        {lancer_sequence(32);}
  else if(delais > 3000 && delais < 5200)  {lancer_sequence(12);}
  else if(delais > 5200 && delais < 7800)  {lancer_sequence(42);}
  else if(delais > 7800 && delais < 10200) {lancer_sequence(34);}
  else if(delais > 10200 && delais < 13600){lancer_sequence(13);}
  else if(delais > 13600 && delais < 17000){lancer_sequence(13);}
  else if(delais > 17000 && delais < 20300){lancer_sequence(41);}
  else if(delais > 20300 && delais < 23800){lancer_sequence(31);}
  else if(delais > 23800 && delais < 26200){lancer_sequence(43);}
  else if(delais > 26200 && delais < 29500){lancer_sequence(41);}
  else if(delais > 30100){sequence = 0;sequence_prete = 0;identifiant_sequence = 0;cerise_avant = 1;cerise_arriere = 1;cerise_droite = 1;cerise_gauche = 0;sequence_cerises_prete = 1;}
}
void sequence412(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence421(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence413(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence423(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence432(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence123(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence132(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence124(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence142(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence134(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence143(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence213(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence231(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence243(int delais){
  sequence_prete = 0;sequence = 0;
}

void sequence234(int delais){/*
    if (millis() - timer_sequence < 300 ) {                                   
      bras1_ventouse(0);                                                                     
      bras2_ventouse(0);
      baie_arriere(0);
      bras1_haut();
      bras2_haut();}
    if (millis() - timer_sequence > 300 && millis() - timer_sequence < 800){  
      bras2_arriere();
      bras1_passe_axe();}
    if (millis() - timer_sequence > 800 && millis() - timer_sequence < 1200){ 
      bras2_bas();
      baie_arriere(1);
      bras2_ventouse(1);}
    if (millis() - timer_sequence > 1200 && millis() - timer_sequence < 1500){
      bras2_haut();}
    if (millis() - timer_sequence > 1500 && millis() - timer_sequence < 2500){
      bras2_passe_axe();
      baie_arriere(0);}
    if (millis() - timer_sequence > 2500 && millis() - timer_sequence < 2800){
      bras2_passe_levage();
      bras1_passe_levage();
      bras1_ventouse(1);}
    if (millis() - timer_sequence > 2800 && millis() - timer_sequence < 3100){
      bras2_ventouse(0);
      //bras1_haut();
      bras2_haut();}
    if (millis() - timer_sequence > 3100 && millis() - timer_sequence < 3600){
      bras1_avant_passe_arriere();
      bras2_milieu();}
    if (millis() - timer_sequence > 3600 && millis() - timer_sequence < 3900){
      bras1_bas();}
    if (millis() - timer_sequence > 3900 && millis() - timer_sequence < 4200){
      bras1_ventouse(0);
      bras1_haut();
      bras2_haut();}
    if (millis() - timer_sequence > 4200){
      bras1_passe_axe();
      bras2_avant();
      baie_gauche(1);}
    if (millis() - timer_sequence > 500 && millis() - timer_sequence < 800) { 
      bras2_bas();
      bras2_ventouse(1);}
    if (millis() - timer_sequence > 800 && millis() - timer_sequence < 1100){ 
      baie_gauche(1);
      bras2_haut(); }
    if (millis() - timer_sequence > 1100 && millis() - timer_sequence < 1600){
      bras2_passe_axe(); }
    if (millis() - timer_sequence > 1600 && millis() - timer_sequence < 1900){
      baie_gauche(0);
      bras2_passe_levage();
      bras1_passe_levage();
      bras1_ventouse(1);}
    if (millis() - timer_sequence > 1900 && millis() - timer_sequence < 2200){
      bras2_ventouse(0);
      bras1_haut();
      bras2_haut(); }
    if (millis() - timer_sequence > 2200 && millis() - timer_sequence < 2500){
      bras1_avant_passe_gauche();
      bras2_arriere(); }
    if (millis() - timer_sequence > 2500 && millis() - timer_sequence < 2800){
      bras1_bas(); 
      bras2_bas();
      bras2_ventouse(1);}
    if (millis() - timer_sequence > 2800 && millis() - timer_sequence < 3100){
      bras1_ventouse(0);
      bras1_haut();}
    if (millis() - timer_sequence < 500){                                     
      bras1_arriere();
      bras2_passe_levage();}
    if (millis() - timer_sequence > 500 && millis() - timer_sequence < 800){  
      bras1_bas();
      bras1_ventouse(1); 
      baie_droite(1);}
    if (millis() - timer_sequence > 800 && millis() - timer_sequence < 1100) {
      bras1_haut(); }
    if (millis() - timer_sequence > 1100 && millis() - timer_sequence < 1500){
      bras1_avant();}
    if (millis() - timer_sequence > 1500 && millis() - timer_sequence < 1800){
      bras1_bas(); 
      baie_droite(0);}
    if (millis() - timer_sequence > 1800 && millis() - timer_sequence < 2100){
      bras1_ventouse(0);
      bras1_haut();
      bras2_passe_axe();}
    if (millis() - timer_sequence > 1800 && millis() - timer_sequence < 2100){
      bras1_passe_axe();
      bras1_ventouse(1);
      bras2_haut();}
    if (millis() - timer_sequence > 1800 && millis() - timer_sequence < 2100){
      bras1_passe_axe();}
    
    
   */ 
   sequence_prete = 0;sequence = 0;
}

void sequence214(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence241(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence312(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence321(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence314(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence341(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence324(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence342(int delais){
  sequence_prete = 0;sequence = 0;
}
