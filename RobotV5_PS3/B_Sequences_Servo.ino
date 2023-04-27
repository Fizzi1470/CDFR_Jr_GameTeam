uint32_t timer_sequence;

void lancer_sequence(byte identifiant){
  if (sequence_terminee == 1){
    identifiant_sequence = identifiant;
    timer_sequence = millis();
  }
}

/*
 * Cerise 1-9
 * droite 1
 * avant 2
 * arriere 3
 * gauche 4
 */

void gestion_sequences(){
  uint32_t delais = millis() - timer_sequence;

  if (identifiant_sequence == 1){// cerise avant
    if(delais < 300){baie_avant(0);bras1_haut();cerise_avant_axe();sequence_terminee = 0;}
    else if(delais > 300 && delais < 500){bras1_bas();}
    else if(delais > 500 && delais < 900){cerise_bras1_ouvrir();}
    else if(delais > 900 && delais < 1000){bras1_haut();cerise_bras1_fermer();baie_avant(1);sequence_terminee = 1;}
  
  } else
  if (identifiant_sequence == 12){ // droite vers avant
    if(delais < 500){baie_droite(0);bras1_haut();bras1_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras1_bas(); bras1_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras1_haut();baie_droite(1);}
    else if(delais > 1000 && delais < 1300){bras1_avant();}
    else if(delais > 1600 && delais < 1800){bras1_bas();}
    else if(delais > 2100 && delais < 2200){bras1_haut();bras1_ventouse(0);}
    else if(delais > 2200) sequence_terminee = 1;
    
  } else
  if (identifiant_sequence == 21){ // avant vers droite
    if(delais < 500){bras1_haut();bras1_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras1_bas(); bras1_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras1_haut();}
    else if(delais > 1000 && delais < 1300){bras1_arriere();}
    else if(delais > 1600 && delais < 1800){bras1_bas();}
    else if(delais > 2100 && delais < 2200){bras1_haut();bras1_ventouse(0);sequence_terminee = 1;}
  
  } else
  if (identifiant_sequence == 34){ //arriere vers gauche
    if(delais < 500){bras2_haut();bras2_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras2_bas(); bras2_ventouse(1);}
    else if(delais > 700 && delais < 1300){bras2_haut();}
    else if(delais > 1300 && delais < 1600){bras2_avant();}
    else if(delais > 1600 && delais < 1800){bras2_bas();}
    else if(delais > 2100 && delais < 2200){bras2_haut();bras2_ventouse(0);}
    else if(delais > 2200)sequence_terminee = 1;

  } else
  if (identifiant_sequence == 43){ // gauche vers arriere
    if(delais < 500){bras2_haut();bras2_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras2_bas(); bras2_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras2_haut();}
    else if(delais > 1000 && delais < 1300){bras2_arriere();}
    else if(delais > 1600 && delais < 1800){bras2_bas();}
    else if(delais > 2100 && delais < 2200){bras2_haut();bras2_ventouse(0);}
    else if(delais > 2200)sequence_terminee = 1;
    
  } else
  if(identifiant_sequence == 42){ //gauche vers avant
    if(delais < 500){baie_gauche(0);bras1_haut();bras1_passe_axe();bras2_haut();bras2_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 800){bras2_bas(); bras2_ventouse(1);}
    else if(delais > 800 && delais < 1100){bras2_haut();baie_gauche(1);}
    else if(delais > 1100 && delais < 1400){bras2_passe_axe();}
    else if(delais > 1400 && delais < 1700){bras2_passe_levage();}
    else if(delais > 1700 && delais < 1900){bras1_passe_levage();bras1_ventouse(1);bras2_haut();}
    else if(delais > 2200 && delais < 2400){bras1_avant();bras2_ventouse(0);}
    else if(delais > 2400 && delais < 2500){bras1_bas();}
    else if(delais > 2500 && delais < 2600){bras1_haut();bras1_ventouse(0);bras2_milieu();}
    else if(delais > 2600)sequence_terminee = 1;

  } else
  if(identifiant_sequence == 24){ // avant vers gauche
    if(delais < 500){bras2_haut();bras2_passe_axe();bras1_haut();bras1_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 800){bras1_bas(); bras1_ventouse(1);}
    else if(delais > 800 && delais < 1100){bras1_haut();}
    else if(delais > 1100 && delais < 1400){bras1_passe_axe();}
    else if(delais > 1400 && delais < 1700){bras1_passe_levage();}
    else if(delais > 1700 && delais < 1900){bras2_passe_levage();bras2_ventouse(1);bras1_haut();}
    else if(delais > 2200 && delais < 2400){bras2_avant();bras1_ventouse(0);}
    else if(delais > 2400 && delais < 2500){bras2_bas();}
    else if(delais > 2500 && delais < 2600){bras2_haut();bras2_ventouse(0);sequence_terminee = 1;}

  } else
  if(identifiant_sequence == 32){ // arriere vers avant
    if(delais < 500){bras2_haut();bras2_arriere();bras1_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras2_bas(); bras2_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras2_haut();}
    else if(delais > 1000 && delais < 1700){bras2_passe_axe();bras1_haut();}
    else if(delais > 1700 && delais < 2000){bras2_passe_levage();bras1_passe_axe();}
    else if(delais > 2000 && delais < 2200){bras1_passe_levage();bras1_ventouse(1);bras2_haut();}
    else if(delais > 2400 && delais < 2500){bras2_ventouse(0);bras1_haut();}
    else if(delais > 2500 && delais < 2700){bras2_milieu();bras1_avant();}
    else if(delais > 2700 && delais < 2900){bras1_bas();}
    else if(delais > 2900 && delais < 3000){bras1_haut();bras1_ventouse(0);}
    else if(delais > 3000)sequence_terminee = 1;

  } else
  if (identifiant_sequence == 23){ // avant vers arriere
    if(delais < 500){bras1_haut();bras1_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras1_bas(); bras1_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras1_haut();}
    else if(delais > 1000 && delais < 1300){bras1_passe_axe();bras2_haut();}
    else if(delais > 1300 && delais < 1700){bras1_passe_levage();bras2_passe_axe();}
    else if(delais > 1700 && delais < 1800){bras2_passe_levage();bras2_ventouse(1);bras1_haut();}
    else if(delais > 1800 && delais < 2500){bras1_avant();bras1_ventouse(0);bras2_arriere();bras2_haut();}
    else if(delais > 2500 && delais < 2700){bras2_bas();}
    else if(delais > 2700){bras1_haut();bras2_ventouse(0);sequence_terminee = 1;}
  
  } else
  if(identifiant_sequence == 31){ // arriere vers droite
    if(delais < 500){bras2_haut();bras1_haut();bras2_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras2_bas();bras1_avant();bras2_ventouse(1);}
    else if(delais > 700 && delais < 1100){bras2_haut();}
    else if(delais > 1100 && delais < 1800){bras2_passe_axe();bras1_haut();}
    else if(delais > 1800 && delais < 2200){bras2_passe_levage();bras1_passe_axe();}
    else if(delais > 2200 && delais < 2400){bras1_passe_levage();bras1_ventouse(1);bras2_haut();}
    else if(delais > 2400 && delais < 3000){bras1_arriere();bras2_ventouse(0);bras2_arriere();bras1_haut();}
    else if(delais > 3000 && delais < 3200){bras1_bas();}
    else if(delais > 3200 && delais < 3300){bras1_haut();bras1_ventouse(0);}
    else if(delais > 3300)sequence_terminee = 1;

  } else
  if (identifiant_sequence == 13){ // droite vers arriere
    if(delais < 500){bras2_haut();bras1_haut();bras1_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras1_bas();bras2_avant();bras1_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras1_haut();}
    else if(delais > 1000 && delais < 1700){bras1_passe_axe();bras2_haut();}
    else if(delais > 1700 && delais < 2000){bras1_passe_levage();bras2_passe_axe();}
    else if(delais > 2000 && delais < 2200){bras2_passe_levage();bras2_ventouse(1);bras1_haut();}
    else if(delais > 2400 && delais < 3100){bras2_arriere();bras1_ventouse(0);bras1_milieu();bras2_haut();}
    else if(delais > 3100 && delais < 3300){bras2_bas();}
    else if(delais > 3300 && delais < 3400){bras2_haut();bras2_ventouse(0);}
    else if(delais > 3400) sequence_terminee = 1;

  } else
  if (identifiant_sequence == 41){ // gauche vers droite
    if(delais < 500){bras2_haut();bras1_haut();bras2_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras2_bas();bras1_avant();bras2_ventouse(1);}
    else if(delais > 700 && delais < 1300){bras2_haut();}
    else if(delais > 1300 && delais < 1900){bras2_passe_axe();bras1_haut();}
    else if(delais > 1900 && delais < 2200){bras2_passe_levage();bras1_passe_axe();}
    else if(delais > 2200 && delais < 2400){bras1_passe_levage();bras1_ventouse(1);bras2_haut();}
    else if(delais > 2400 && delais < 3100){bras1_arriere();bras2_ventouse(0);bras2_milieu();bras1_haut();}
    else if(delais > 3100 && delais < 3200){bras1_bas();}
    else if(delais > 3200 && delais < 3300){bras1_haut();bras1_ventouse(0);}
    else if(delais > 3300) sequence_terminee = 1;
  }
}



/*
 * Cerise 1-9
 * droite 1
 * avant 2
 * arriere 3
 * gauche 4
 */

void sequence412(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence421(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence413(int delais){
  sequence_prete = 0;sequence = 0;
}
void sequence431(int delais){
  if(delais < 3000)                        {lancer_sequence(32);}
  else if(delais > 3000 && delais < 5200)  {lancer_sequence(12);}
  else if(delais > 5200 && delais < 7800)  {lancer_sequence(42);}
  else if(delais > 7800 && delais < 10000) {lancer_sequence(34);}
  else if(delais > 10000 && delais < 13400){lancer_sequence(13);}
  else if(delais > 13400 && delais < 16800){lancer_sequence(13);}
  else if(delais > 16800 && delais < 20100){lancer_sequence(41);}
  else if(delais > 20100 && delais < 23400){lancer_sequence(31);}
  else if(delais > 23400 && delais < 25600){lancer_sequence(43);}
  else if(delais > 25600 && delais < 28900){lancer_sequence(41);}
  else if(delais > 28900){sequence_prete = 0;sequence = 0;}
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
