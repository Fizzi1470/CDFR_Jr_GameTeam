int mode_bargraph;
unsigned long timer_batt_read;
unsigned long timer_blink_batt_off;
unsigned long timer_buzzer;
int mode_led;

// INOPERRANT POUR LE MOMENT !!!

void afficheur_etat(){
    if(digitalRead(50)== 0){ //si le bouton alim est sur mode batterie
      if((millis() - timer_batt_read) > 10000){
          battlvl = round(((analogRead(A0+15)-607)*100)/165/10); // sort normalement une valeur de 0 à 10
          timer_batt_read = millis();
      }
        
      if(((digitalRead(51))==(0))){ // appui sur le bouton batterie avec selecteur alim sur batterie
          if(!(mode_bargraph)==(1)){
              bargraph.setLevel(battlvl);
              mode_bargraph = 1;
          }
            
      }else{                      // si le bouton n'est pas enclenché
          mode_bargraph = 0;
          afficher_etat_actuel();
       }
      
    }else{ //si le bouton alim est sur mode secteur 
        if(((digitalRead(51))==(0))){ // appui sur le bouton batterie avec selecteur alim en mode secteur 
            if ((millis() - timer_blink_batt_off) > 500){ // faire clignoter la led correspondante au mode batterie pour indiquer qu'il n'est pas actif et que donc uen requête du niveau batterie est impossible
              if (mode_led == 1 )
                mode_led = 0;
              else
                mode_led = 1;
              bargraph.setLed(3, (mode_led));
              timer_blink_batt_off = millis();
            }
        }
      afficher_etat_actuel();
    }   
}

void alerte_buzzer(){
  if(battlvl < 3){
    if((millis() - timer_buzzer) > 10000){
      analogWrite(2, 127);
      if((millis() - timer_buzzer) > 11000)
        timer_buzzer = millis();
    }
    else
      analogWrite(2, 0);
  }
}

void afficher_etat_actuel(){
  if (0 == 0){
    bargraph.setLevel(1);
  }
}
