int i = 200;
boolean turbine;

void changer_etat_aspiro(){  
  if (turbine == 0 && BAU == 0){
    //debug(4,F("aspirateur à l'allumage . . . "),-99);
    Usb.Task();
    while (i < 255){
      //debug(4,"i :",i);
      delay(1.5);
      i = i + 1;
      analogWrite(13, i);
    }
    Usb.Task();
    digitalWrite(13,1);
    //debug(4,F("aspirateur lancé"),-99);
    turbine = 1;
  } else {
    digitalWrite(13,0);
    i = 200;
    //debug(4,F("aspirateur éteint"),-99);
    turbine = 0; // au cas ou c'est le BAU qui fait stopper
  } 
}

void gestion_BAU_turbine(){
  if (BAU == 1) {digitalWrite(13,0);turbine = 0;}
}

void ouvrir_reservoir(){
  servo(F("Servo_clapet_cerise"),70); 
  //debug(4,F("porte aspirateur  ouverte"),-99);  
}
void fermer_reservoir(){
  servo(F("Servo_clapet_cerise"),160);
  //debug(4,F("porte aspirateur  fermée"),-99);
}
