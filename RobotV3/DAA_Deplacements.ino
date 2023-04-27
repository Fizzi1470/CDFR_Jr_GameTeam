int tourner1;
int tourner2;
int axe1a;
int axe1r;
int axe2a;
int axe2r;
int axeXprocess;
int axeYprocess;
int decalageAzimuth;

void calibrer_azimuth(){
  Usb.Task();delta();
  //azimuth = compass.getAzimuth();
  decalageAzimuth = azimuth;
  Usb.Task();delta();
  //debug(7,F("azimuth calibré : "), decalageAzimuth);
}

void gestion_deplacements(){
  Usb.Task();delta();
  if(stop_deguisement == 0){
    
  // reception des valeurs de rotation et conversion en ordre moteur
  if((axeTourner) < (0)){
    tourner1 = axeTourner * (-10.2);
    tourner2 = 0;
  } else
  if(axeTourner > 0){
    tourner1 = 0;
    tourner2 = axeTourner * (10.2);
  } else
  if(axeTourner == 0){
    tourner1 = 0;
    tourner2 = 0;
  }
  Usb.Task();delta();
// process des valeurs en ordres moteur

  /*
  if((axeX*axeX + axeY*axeY) > (25*25)){
    axeX = axeX*sqrt((25*25) / (axeX*axeX + axeY*axeY));
    axeY = axeY*sqrt((25*25) / (axeX*axeX + axeY*axeY));
  }
  
  Usb.Task();delta();*/
  if(mode_deplacement == 1) azimuth = -45;
    else {
      //azimuth = compass.getAzimuth();
      azimuth = azimuth - decalageAzimuth;
    } 
  Usb.Task();delta();
  axeXprocess = axeX*cos(radians(azimuth)) - axeY*sin(radians(azimuth));
  axeYprocess = axeX*sin(radians(azimuth)) + axeY*cos(radians(azimuth));
  Usb.Task();delta();
  
  if((axeXprocess) < (0)){
    axe1a = 0;
    axe1r = (axeXprocess) * (-10.2);
  }
  else if((axeXprocess) > (0)){
    axe1r = 0;
    axe1a = (axeXprocess) * (10.2);
  }
  else if(((axeXprocess)==(0))){
    axe1r = 0;
    axe1a = 0;
  }
  Usb.Task();delta();
  if((axeYprocess) < (0)){
    axe2a = 0;
    axe2r = (axeYprocess) * (-10.2);
  }
  else if((axeYprocess) > (0)){
    axe2a = (axeYprocess) * (10.2);
    axe2r = 0;
  }
  else if(((axeYprocess)==(0))){
    axe2a = 0;
    axe2r = 0;
  }
  
  //debug(1,F("-------"),-99);
  //debug(1,F("azimuth : "), azimuth);
  //debug(1,F("azimuth rad : "), radians(azimuth));
  //debug(1,F("axeX : "), axeX);
  //debug(1,F("axeXprocess : "), axeXprocess);
  //debug(1,F("axeY : "), axeY);
  //debug(1,F("axeYprocess : "), axeYprocess);
  //debug(1,F("axeTourner : "), axeTourner);
  //debug(1,F("tourner1 : "), tourner1);
  //debug(1,F("tourner2 : "), tourner2);
  //debug(1,F("axe1a : "), axe1a);
  //debug(1,F("axe1r : "), axe1r);
  //debug(1,F("axe2a : "), axe2a);
  //debug(1,F("axe2r : "), axe2r);
Usb.Task();delta();
//envoi des ordres moteur
  if(tourner1 != 0 || tourner2 != 0){
    analogWrite(5,(axe2r + tourner1) / 2);
    analogWrite(6,(axe2a + tourner2) / 2);
    analogWrite(7,(axe2a + tourner1) / 2);
    analogWrite(8,(axe2r + tourner2) / 2);
    analogWrite(9,(axe1a + tourner1) / 2);
    analogWrite(10,(axe1r + tourner2) / 2);
    analogWrite(11,(axe1r + tourner1) / 2);
    analogWrite(12,(axe1a + tourner2) / 2);
  }else{
    analogWrite(5,axe2r);
    analogWrite(6,axe2a);
    analogWrite(7,axe2a);
    analogWrite(8,axe2r);
    analogWrite(9,axe1a);
    analogWrite(10,axe1r);
    analogWrite(11,axe1r);
    analogWrite(12,axe1a);
  }
  } else { 
    analogWrite(5,0);
    analogWrite(6,0);
    analogWrite(7,0);
    analogWrite(8,0);
    analogWrite(9,0);
    analogWrite(10,0);
    analogWrite(11,0);
    analogWrite(12,0);
  }  
}

//changement entre mode mormal et mode azimuth
void changer_mode(){
  Usb.Task();delta();
  if (mode_deplacement == 1)  {mode_deplacement = 2;}
  else                        {mode_deplacement = 1;}
  //debug(7,F("mode : "), mode_deplacement);
  if (mode_deplacement == 1){
    bargraph[3] = 0; actu_bargraph();
    if (type_manette == 1){Serial2.write(002);}
    else if (type_manette == 2) {SwitchPro.setLedHomeOff();}
  } else {
    bargraph[3] = 1; actu_bargraph();
    if (type_manette == 1){Serial2.write(001);}
    else if (type_manette == 2) {SwitchPro.setLedHomeOn();}
  }Usb.Task();delta();
}
