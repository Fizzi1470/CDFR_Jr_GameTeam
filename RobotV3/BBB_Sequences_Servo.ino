String identifiant_sequence;
uint32_t timer_sequence;
boolean sequence_terminee = 1;

void lancer_sequence(String identifiant){
  if (sequence_terminee == 1){
    identifiant_sequence = identifiant;
    timer_sequence = millis();
  }
}

void gestion_sequences(){
  uint32_t delais = millis() - timer_sequence;
  Usb.Task();delta();
  if (identifiant_sequence == F("cerise_avant")){
    if(delais < 300){baie_avant(0);bras1_haut();cerise_avant_axe();sequence_terminee = 0;}
    else if(delais > 300 && delais < 500){bras1_bas();}
    else if(delais > 500 && delais < 700){cerise_bras1_ouvrir();}
    else if(delais > 700 && delais < 800){bras1_haut();cerise_bras1_fermer();baie_avant(1);sequence_terminee = 1;}
  
  }
  Usb.Task();delta();
  if (identifiant_sequence == F("droite_vers_avant")){
    if(delais < 500){baie_droite(0);bras1_haut();bras1_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras1_bas(); bras1_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras1_haut();baie_droite(1);}
    else if(delais > 1000 && delais < 1300){bras1_avant();}
    else if(delais > 1600 && delais < 1800){bras1_bas();}
    else if(delais > 2100 && delais < 2200){bras1_haut();bras1_ventouse(0);sequence_terminee = 1;}
    
  }
  Usb.Task();delta(); 
  if (identifiant_sequence == F("avant_vers_droite")){
    if(delais < 500){bras1_haut();bras1_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras1_bas(); bras1_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras1_haut();}
    else if(delais > 1000 && delais < 1300){bras1_arriere();}
    else if(delais > 1600 && delais < 1800){bras1_bas();}
    else if(delais > 2100 && delais < 2200){bras1_haut();bras1_ventouse(0);sequence_terminee = 1;}
  
  } 
  Usb.Task();delta();
  if (identifiant_sequence == F("arriere_vers_gauche")){
    if(delais < 500){bras2_haut();bras2_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras2_bas(); bras2_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras2_haut();}
    else if(delais > 1000 && delais < 1300){bras2_avant();}
    else if(delais > 1600 && delais < 1800){bras2_bas();}
    else if(delais > 2100 && delais < 2200){bras2_haut();bras2_ventouse(0);sequence_terminee = 1;}

  }
  Usb.Task();delta();
  if (identifiant_sequence == F("gauche_vers_arriere")){
    if(delais < 500){bras2_haut();bras2_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras2_bas(); bras2_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras2_haut();}
    else if(delais > 1000 && delais < 1300){bras2_arriere();}
    else if(delais > 1600 && delais < 1800){bras2_bas();}
    else if(delais > 2100 && delais < 2200){bras2_haut();bras2_ventouse(0);sequence_terminee = 1;}
    
  }
  Usb.Task();delta();
  if(identifiant_sequence == F("gauche_vers_avant")){
    if(delais < 500){baie_gauche(0);bras1_haut();bras1_passe_axe();bras2_haut();bras2_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 800){bras2_bas(); bras2_ventouse(1);}
    else if(delais > 800 && delais < 1100){bras2_haut();baie_gauche(1);}
    else if(delais > 1100 && delais < 1400){bras2_passe_axe();}
    else if(delais > 1400 && delais < 1700){bras2_passe_levage();}
    else if(delais > 1700 && delais < 1900){bras1_passe_levage();bras1_ventouse(1);bras2_haut();}
    else if(delais > 2200 && delais < 2400){bras1_avant();bras2_ventouse(0);}
    else if(delais > 2400 && delais < 2500){bras1_bas();}
    else if(delais > 2500 && delais < 2600){bras1_haut();bras1_ventouse(0);sequence_terminee = 1;}

  }
  Usb.Task();delta();
  if(identifiant_sequence == F("avant_vers_gauche")){
    if(delais < 500){bras2_haut();bras2_passe_axe();bras1_haut();bras1_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 800){bras1_bas(); bras1_ventouse(1);}
    else if(delais > 800 && delais < 1100){bras1_haut();}
    else if(delais > 1100 && delais < 1400){bras1_passe_axe();}
    else if(delais > 1400 && delais < 1700){bras1_passe_levage();}
    else if(delais > 1700 && delais < 1900){bras2_passe_levage();bras2_ventouse(1);bras1_haut();}
    else if(delais > 2200 && delais < 2400){bras2_avant();bras1_ventouse(0);}
    else if(delais > 2400 && delais < 2500){bras2_bas();}
    else if(delais > 2500 && delais < 2600){bras2_haut();bras2_ventouse(0);sequence_terminee = 1;}

  }
  Usb.Task();delta();
  if(identifiant_sequence == F("arriere_vers_avant")){
    if(delais < 500){bras2_haut();bras2_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras2_bas(); bras2_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras2_haut();}
    else if(delais > 1000 && delais < 1700){bras2_passe_axe();bras1_haut();}
    else if(delais > 1700 && delais < 2000){bras2_passe_levage();bras1_passe_axe();}
    else if(delais > 2000 && delais < 2200){bras1_passe_levage();bras1_ventouse(1);bras2_haut();}
    else if(delais > 2400 && delais < 2500){bras2_ventouse(0);bras1_haut();}
    else if(delais > 2500 && delais < 2700){bras2_arriere();bras1_avant();}
    else if(delais > 2700 && delais < 2900){bras1_bas();}
    else if(delais > 2900){bras1_haut();bras1_ventouse(0);sequence_terminee = 1;}

  }
  Usb.Task();delta();
  if (identifiant_sequence == F("avant_vers_arriere")){
    if(delais < 500){bras1_haut();bras1_avant();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras1_bas(); bras1_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras1_haut();}
    else if(delais > 1000 && delais < 1300){bras1_passe_axe();bras2_haut();}
    else if(delais > 1300 && delais < 1700){bras1_passe_levage();bras2_passe_axe();}
    else if(delais > 1700 && delais < 1800){bras2_passe_levage();bras2_ventouse(1);bras1_haut();}
    else if(delais > 1800 && delais < 2500){bras1_avant();bras1_ventouse(0);bras2_arriere();bras2_haut();}
    else if(delais > 2500 && delais < 2700){bras2_bas();}
    else if(delais > 2700){bras1_haut();bras2_ventouse(0);sequence_terminee = 1;}
  
  }
  Usb.Task();delta();
  if(identifiant_sequence == F("arriere_vers_droite")){
    if(delais < 500){bras2_haut();bras1_haut();bras2_arriere();sequence_terminee = 0;}
    else if(delais > 500 && delais < 700){bras2_bas();bras1_avant();bras2_ventouse(1);}
    else if(delais > 700 && delais < 1000){bras2_haut();}
    else if(delais > 1000 && delais < 1700){bras2_passe_axe();bras1_haut();}
    else if(delais > 1700 && delais < 2000){bras2_passe_levage();bras1_passe_axe();}
    else if(delais > 2000 && delais < 2200){bras1_passe_levage();bras1_ventouse(1);bras2_haut();}
    else if(delais > 2400 && delais < 3000){bras1_arriere();bras2_ventouse(0);bras2_arriere();bras1_haut();}
    else if(delais > 3000 && delais < 3200){bras1_bas();}
    else if(delais > 3200){bras1_haut();bras1_ventouse(0);sequence_terminee = 1;}

  }
  Usb.Task();delta(); 
  if (identifiant_sequence == F("droite_vers_arriere")){
    
  }
}



void sequence412(){
  Serial.println("t");
  sequence_prete = 0;sequence = 0;
}
void sequence421(){
  Serial.println("e");
  sequence_prete = 0;sequence = 0;
}
void sequence413(){
  Serial.println("h");
  delay(10000);
  Serial.println("g");
  sequence_prete = 0;sequence = 0;
}
void sequence431(){

}
void sequence423(){
  
}
void sequence432(){
  
}
void sequence123(){
  
}
void sequence132(){
  
}
void sequence124(){
  
}
void sequence142(){

}
void sequence134(){
  
}
void sequence143(){
  
}
void sequence213(){
  
}
void sequence231(){
  
}
void sequence243(){
  
}

void sequence234(){/*
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
}

void sequence214(){
  
}
void sequence241(){
  
}
void sequence312(){
  
}
void sequence321(){
  
}
void sequence314(){
  
}
void sequence341(){
  
}
void sequence324(){
  
}
void sequence342(){
  
}
