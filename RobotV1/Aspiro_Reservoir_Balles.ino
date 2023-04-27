int i = 200;
int turbine = 1;

void aspiro_balles(){

  if (message == 215){
    turbine = turbine * -1;
    if (turbine == 1){
      debug(4, "aspirateur à l'allumage . . . ",-99);
      digitalWrite(48,1);
      while (i < 255){
        debug(4,"i :",i);
        delay(1.5);
        i = i + 1;
        analogWrite(13, i);
      }
      digitalWrite(13,1);
      debug(4, "aspirateur lancé",-99);
    } else {
        digitalWrite(48,0);
        digitalWrite(13,0);
        i = 200;
        debug(4, "aspirateur éteint",-99);
      }
    message = -1;  
  }

  if (message == 216){
    porte_aspiro.write(70);
    digitalWrite(38, 1);   
  }
  if (message == 219){
    porte_aspiro.write(160);
    digitalWrite(38, 0);   
  }
}
