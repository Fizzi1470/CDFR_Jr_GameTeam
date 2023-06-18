int tourner1;
int tourner2;
int axe1a;
int axe1r;
int axe2a;
int axe2r;
float axeXprocess;
float axeYprocess;
float axeXadapte;
float axeYadapte; 
int axeCombine;
int lecture_serie;
float buffer_serie;
float buffer_azimuth;
float decalageAzimuth;

void calibrer_azimuth(){
  decalageAzimuth = buffer_azimuth;
}

void gestion_magneto(){
  if (Serial1.available()){
    lecture_serie = Serial1.read()-48;
    if(lecture_serie == -1)buffer_serie = 0;
    else if (lecture_serie == 10){buffer_azimuth = buffer_serie; azimuth = buffer_azimuth - decalageAzimuth; /*Serial.print(azimuth);Serial.print(" ; "); Serial.println(decalageAzimuth);*/}
    else buffer_serie = (buffer_serie*10) + lecture_serie;
  } 
}

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

  //Serial.print(axeX); Serial.print(";");Serial.print(axeY);Serial.print(";");

  if((axeX*axeX + axeY*axeY) > (25*25)){
    axeXadapte = axeX*sqrt((25*25) / (axeX*axeX + axeY*axeY));
    axeYadapte = axeY*sqrt((25*25) / (axeX*axeX + axeY*axeY));
  } else {
    axeXadapte = axeX;
    axeYadapte = axeY;
  }
  //Serial.print(axeXadapte); Serial.print(";");Serial.print(axeYadapte);Serial.print(";");
  
  //axeXadapte = axeX;
  //axeYadapte = axeY;
  
  if(mode_deplacement == 0){
    if (turbine == 1) azimuth = 0;
    else azimuth = -45;
  }
    
  axeXprocess = axeXadapte*cos(radians(azimuth)) - axeYadapte*sin(radians(azimuth));
  axeYprocess = axeXadapte*sin(radians(azimuth)) + axeYadapte*cos(radians(azimuth));
  //Serial.print(axeXprocess); Serial.print(";");Serial.print(axeYprocess);Serial.print(";");
  
  if (axeXprocess > 25) axeXprocess = 25;
  else if (axeXprocess < -25) axeXprocess = -25;
  if (axeYprocess > 25) axeYprocess = 25;
  else if (axeYprocess < -25) axeYprocess = -25;
  //Serial.print(axeXprocess); Serial.print(";");Serial.println(axeYprocess);

  /*
  axeCombine = sqrt(axeXprocess*axeXprocess + axeYprocess*axeYprocess);
  if (axeCombine > 625){
    axeXprocess = (25*axeXprocess)/axeCombine;
    axeYprocess = (25*axeYprocess)/axeCombine;
  }*/
  //Serial.print(axeXprocess); Serial.print(";");Serial.println(axeYprocess);
  
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

    //Serial.print(axe1a);Serial.print(";"); Serial.print(axe1r);Serial.print(";");Serial.print(axe2a);Serial.print(";"); Serial.print(axe2r);Serial.println();
 
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

void changer_mode(){
  mode_deplacement = !mode_deplacement;
  bargraph(3,mode_deplacement);
}
