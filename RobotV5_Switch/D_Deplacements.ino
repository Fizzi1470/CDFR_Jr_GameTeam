int tourner1;
int tourner2;
int axe1a;
int axe1r;
int axe2a;
int axe2r;
int axeXprocess;
int axeYprocess;
int lecture_serie;
float buffer_serie;
float decalageAzimuth;
/*
void calibrer_azimuth(){
  decalageAzimuth = azimuth;
}

void gestion_magneto(){
  if (Serial1.available()){
    lecture_serie = Serial1.read()-48;
    if(lecture_serie == -1)buffer_serie = 0;
    else if (lecture_serie == 10){azimuth = buffer_serie - decalageAzimuth;Serial.println(azimuth);}
    else buffer_serie = (buffer_serie*10) + lecture_serie;
  } 
}
*/
void gestion_deplacements(){
if(deguisement == 0){
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
  
// process des valeurs en ordres moteur

  /*
  if((axeX*axeX + axeY*axeY) > (25*25)){
    axeX = axeX*sqrt((25*25) / (axeX*axeX + axeY*axeY));
    axeY = axeY*sqrt((25*25) / (axeX*axeX + axeY*axeY));
  }
  */
  
  if(mode_deplacement == 0) azimuth = -45;
    
  axeXprocess = axeX*cos(radians(azimuth)) - axeY*sin(radians(azimuth));
  axeYprocess = axeX*sin(radians(azimuth)) + axeY*cos(radians(azimuth));
  
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
/*
void changer_mode(){
  mode_deplacement = !mode_deplacement;
  if (mode_deplacement == 0){
    if (type_manette == 0){Serial2.write(002);}
    else {SwitchPro.setLedHomeOff();}
  } else {
    if (type_manette == 0){Serial2.write(001);}
    else {SwitchPro.setLedHomeOn();}
  }
}*/
