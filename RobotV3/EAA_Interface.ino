unsigned long timer_batt_read;
unsigned long timer_buzzer;
unsigned long timer_led_alerte;
int a_afficher;
boolean bouton_enfonce;
float battlvl;
void actu_batt(){battlvl = (analogRead(A15)-419)/42.25;}//note : crochet à retirer si on remet debug//debug(9,F("valeur batterie : "), battlvl);//debug(9,F("valeur brute : "), analogRead(A15));} // revnoie une valeur de 0 à 4

#define dataPin A6
#define latchPin A3
#define clockPin A4

void gestion_BAU(){
  if (digitalRead(53) == 1) {BAU = 1; identifiant_sequence = F("rien"); sequence_terminee = 1; bargraph[0] = 1; actu_bargraph();}
  else if (BAU != digitalRead(53)){BAU = 0;bargraph[0] = 0; actu_bargraph();}
}

void actu_bargraph(){
  a_afficher = 0;
  for( uint8_t i =0; i <8; i++ ) 
  a_afficher += bargraph[i] << i;

  Usb.Task();
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, a_afficher); //remplacer LSBFIRST par MSBFIRST pour inverser le sens
  digitalWrite(latchPin, HIGH);
  Usb.Task();
}

void gestion_IHM(){
  if (millis() - timer_batt_read > 20000 || premiere_boucle == 1){
    timer_batt_read = millis();
    actu_batt();
    bargraph[4] = 0;bargraph[5] = 0;bargraph[6] = 0;bargraph[7] = 0;
    if(analogRead(A15) >= 485 && analogRead(A15) <= 489){
      bargraph[4] = 1;bargraph[5] = 1;bargraph[6] = 1;bargraph[7] = 1;
    } else if (analogRead(A15) < 200) {
      alerte(1,F("Alimentation coupée, étage logique uniquement, via USB"));
    } else if(battlvl > 3.25){
      bargraph[4] = 1;
    } else if (battlvl > 2.75) {
      bargraph[5] = 1;
    } else if (battlvl > 2) {
      bargraph[6] = 1;
    } else {
      bargraph[7] = 1;
      alerte(3,F("Batterie faible"));
    }
    actu_bargraph();
  }

  if (digitalRead(A2) == 0){
  if (bouton_enfonce == 0){
    bouton_enfonce = 1;
    bargraph[1] = 0; bargraph[2] = 0;
    if (type_manette == 1)
      type_manette = 2;
    else type_manette = 1;
    bargraph[type_manette] = 1;
    actu_bargraph();
    //debug(9,F("Manette modifée, nouvelle manette sélectionnée : "), type_manette);
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
}

void gestion_buzzer(){
  if (alerte_buzzer > 1 && buzzer == 1){
    if (millis() - timer_buzzer > (20 / alerte_buzzer)*1000){
      analogWrite(4, 127);
      if (millis() - timer_buzzer > (20 / alerte_buzzer)*1000 + 300){
        analogWrite(4, 0);
        timer_buzzer = millis();
      }
    }
  }
}
