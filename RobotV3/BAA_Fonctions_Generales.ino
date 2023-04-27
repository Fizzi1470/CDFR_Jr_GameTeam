void debug(byte id_debug, String message_debug, int info_add){
  if (id_debug == mode_debug){
    if (info_add == -99){Serial.println(message_debug);}
    else{Serial.println(message_debug + String(info_add));}
  }
}

byte alerte_buzzer;
void alerte(byte gravite, String raison){ // gravité 1,2, ou 3, une gravité à 1 ne lance pas de bips du buzzer
  Serial.print(F("ALERTE de gravité ")); Serial.print(gravite); Serial.print(F(" : ")); Serial.print(raison); Serial.println(F(" !"));
  //debug(9,F("alerte buzzer lancée, gravité "), gravite);
  if (gravite > alerte_buzzer)
    alerte_buzzer = gravite;
}

void bras1_ventouse(boolean statut_ventouse){
  digitalWrite(33 - pompe1, statut_ventouse);
  if(statut_ventouse == 1) statut_ventouse = 0; else statut_ventouse = 1;
  digitalWrite(33 - EV1, statut_ventouse);
}

void bras2_ventouse(boolean statut_ventouse){
  digitalWrite(33 - pompe2, statut_ventouse);
  if(statut_ventouse == 1) statut_ventouse = 0; else statut_ventouse = 1;
  digitalWrite(33 - EV2, statut_ventouse);
}
