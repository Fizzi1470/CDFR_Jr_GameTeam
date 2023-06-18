boolean bargraph_buffer[8];
#define dataPin A6
#define latchPin A3
#define clockPin A4
byte batt_lvl_robot(){int valeur = (analogRead(A15)-419)/45; if (valeur < 0)return 6; else if (valeur > 3) return 3; else return valeur;} // revnoie une valeur de 0 à 3, renvoie 5 si alim externe, renvoie 6 si non alimenté
byte batt_lvl_manette(){if(PS3.PS3Connected == 0)return 6; else if (PS3.getStatus(Charging)) return 5; else if(PS3.getStatus(Dying))return 0; else if(PS3.getStatus(Low))return 1;else if(PS3.getStatus(High))return 2; else if(PS3.getStatus(Full))return 3;} //renvoie une valeur de 0 à 3, renvoie 5 si en charge, renvoie 6 si déco

void bargraph(byte led, byte etat){
  bargraph_buffer[led] = etat;
  int a_afficher = 0;
  for( uint8_t i =0; i <8; i++ ) 
  a_afficher += bargraph_buffer[i] << i;
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, a_afficher); //remplacer LSBFIRST par MSBFIRST pour inverser le sens
  digitalWrite(latchPin, HIGH);
}

void gestion_vidange(){
  if (digitalRead(A2) == 0 && vidange == 0){
    vidange = 1;
    analogWrite(4,127);
    ouvrir_reservoir();
    cerise_bras1_vidanger();
    cerise_bras2_vidanger();
  } else if (digitalRead(A2) == 1 && vidange == 1){
    vidange = 0;
    digitalWrite(4,0);
    fermer_reservoir();
    cerise_bras1_fermer();
    cerise_bras2_fermer();
  }
}

void gestion_IHM() {
  if (digitalRead(A5) == 1){
    bargraph_buffer[7] = 0;
    bargraph_buffer[6] = 0;
    bargraph_buffer[5] = 0;
    bargraph_buffer[4] = 0;
    if (batt_lvl_manette() == 6){
      bargraph_buffer[6] = 0;
      bargraph_buffer[5] = 0;
      bargraph_buffer[4] = 0;
      bargraph(7, 0);
    } else if (batt_lvl_manette() == 5){
      bargraph_buffer[6] = 1;
      bargraph_buffer[5] = 1;
      bargraph_buffer[4] = 1;
      bargraph(7, 1);
    } else {
      bargraph(7 - batt_lvl_manette(), 1);
    }
  } else {
    bargraph_buffer[7] = 0;
    bargraph_buffer[6] = 0;
    bargraph_buffer[5] = 0;
    bargraph_buffer[4] = 0;
    if (batt_lvl_robot() == 6){
      bargraph_buffer[6] = 0;
      bargraph_buffer[5] = 0;
      bargraph_buffer[4] = 0;
      bargraph(7, 0);
    } else if (batt_lvl_robot() == 5){
      bargraph_buffer[6] = 1;
      bargraph_buffer[5] = 1;
      bargraph_buffer[4] = 1;
      bargraph(7, 1);
    } else bargraph(7 - batt_lvl_robot(), 1);
  }
}

/*
void gestion_IHM(){
  
}
  if (PS3.getStatus(Charging)){
    if (millis() - clignotement_charge > 500){
      PS3.setLedToggle(LED1);
      PS3.setLedToggle(LED3);
      PS3.setLedToggle(LED4);
      clignotement_charge = millis();
    }
  } else {
    PS3.setLedOn(LED1);
    if (PS3.getStatus(Low))PS3.setLedOn(LED2);
    if (PS3.getStatus(High))PS3.setLedOn(LED3);
    if (PS3.getStatus(Full))PS3.setLedOn(LED4);
  }







unsigned long timer_batt_read;
unsigned long timer_buzzer;
unsigned long timer_led_alerte;
int bargraph[8];
int a_afficher;
int bouton_enfonce;
float battlvl;


#define dataPin A6
#define latchPin A3
#define clockPin A4



void IHM(){
  if (millis() - timer_batt_read > 20000 || premiere_boucle == 1){
    timer_batt_read = millis();
    actu_batt();
    bargraph[4] = 0;bargraph[5] = 0;bargraph[6] = 0;bargraph[7] = 0;
    if(analogRead(A15) >= 483 && analogRead(A15) <= 487){
      bargraph[4] = 1;bargraph[5] = 1;bargraph[6] = 1;bargraph[7] = 1;
    } else if (analogRead(A15) < 200) {
      alerte(1, "Alimentation coupée, étage logique uniquement, via USB");
    } else if(battlvl > 3.25){
      bargraph[4] = 1;
    } else if (battlvl > 2.75) {
      bargraph[5] = 1;
    } else if (battlvl > 2) {
      bargraph[6] = 1;
    } else {
      bargraph[7] = 1;
      alerte(3, "Batterie faible");
    }
    actu_bargraph();
  }

  if (digitalRead(A2) == 0 || premiere_boucle == 1){
  if (bouton_enfonce == 0){
    bouton_enfonce = 1;
    bargraph[1] = 0;bargraph[2] = 0;bargraph[3] = 0;
    if (type_manette >= type_manette_max)
      type_manette = 1;
    else
      type_manette = type_manette + 1;
    bargraph[type_manette] = 1;
    actu_bargraph();
    debug(9,"Manette modifée, nouvelle manette sélectionnée : ", type_manette);
  }
  } else bouton_enfonce = 0;

  if (alerte_buzzer > 0 && millis() - timer_led_alerte > 1000 / alerte_buzzer){
    timer_led_alerte = millis();
    if (bargraph[0] == 1)
      bargraph[0] = 0;
    else 
      bargraph[0] = 1;

    actu_bargraph();
  }
    
  if (alerte_buzzer > 1 && buzzer == 1){
    if (millis() - timer_buzzer > (20 / alerte_buzzer)*1000){
      analogWrite(4, 127);
      if (millis() - timer_buzzer > (20 / alerte_buzzer)*1000 + 300){
        analogWrite(4, 0);
        timer_buzzer = millis();
      }
    }
  }
}*/
