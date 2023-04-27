uint32_t timer_sequence;

void arriere_vers_droite(int timer){
    if (millis() - timer < 500){                                 bras1_ventouse(0);
                                                                 baie_droite(0);
                                                                 bras1_haut();
                                                                 bras1_arriere();}
    if ((millis() - timer > 500) && (millis() - timer < 800))  { bras1_bas();
                                                                 bras1_ventouse(1); 
                                                                 baie_droite(1);}
    if ((millis() - timer > 800) && (millis() - timer < 1100)) { bras1_haut(); }
    if ((millis() - timer > 1100) && (millis() - timer < 1500)){ bras1_avant();}
    if ((millis() - timer > 1500) && (millis() - timer < 1800)){ bras1_bas(); 
                                                                 baie_droite(0);}
    if ((millis() - timer > 1800) && (millis() - timer < 2100)){ bras1_ventouse(0);
                                                                 bras1_haut(); }
    if (millis() - timer > 2100){                                bras1_milieu();}    
  }
  
void droite_vers_arriere(int timer){
  
}
void arriere_vers_avant(int timer){
  
}
void avant_vers_arriere(int timer){
  
}
void droite_vers_avant(int timer){
  
}



// ======================================================================


void sequence412(){
  
}
void sequence421(){
  
}
void sequence413(){
  
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

void sequence234(){
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
