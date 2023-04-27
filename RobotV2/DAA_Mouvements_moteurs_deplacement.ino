int decalageAzimuth;
int tourner1;
int tourner2;
int axe1a;
int axe1r;
int axe2a;
int axe2r;
int axeX;
int axeXprocess;
int axeY;
int axeYprocess;

void mouvements(){
  if(azimuth != 225 && stop_deguisement == 0){ //vieux bug de l'azimuth 225, normalement réglé mais bon on la connait hein
    if(((message)==(218))){ //modification de l'azimuth en fonction du décalage par rapport à l'azimuth 0
      decalageAzimuth = -azimuth;
      //analogWrite(2,127);
    }else{
      if(mode_deplacement == 1) azimuth = -45;
      else azimuth = -azimuth + decalageAzimuth;
      //analogWrite(2,0);
    }

// reception des valeurs de rotation et conversion en ordre moteur
    
    if(((message) > (0)) && ((message) < (100))){
      if((message) < (50)){
        if((message) < (25)){
          tourner1 = ((25) - (message)) * (10.2);
          tourner2 = 0;
        }
        if((message) > (25)){
          tourner1 = 0;
          tourner2 = ((message) - (25)) * (10.2);
        }
        if(((message)==(25))){
          tourner1 = 0;
          tourner2 = 0;
        }
      }
    }else{

//reception valeurs de déplacement et adaptation à l'angle

    if(((message) > (100)) && ((message) < (201))){
      if((message) < (150)){
        axeX = (message) - (125);
      }
      if((message) > (150)){
        axeY = (message) - (175);
      }

// process des valeurs en ordres moteur

    if((axeX*axeX + axeY*axeY) > (25*25)){
      axeX = axeX*sqrt((25*25) / (axeX*axeX + axeY*axeY));
      axeY = axeY*sqrt((25*25) / (axeX*axeX + axeY*axeY));
    }
  
    axeXprocess = axeX*cos(radians(azimuth)) - axeY*sin(radians(azimuth));
    axeYprocess = axeX*sin(radians(azimuth)) + axeY*cos(radians(azimuth));
      
        if((axeXprocess) < (0)){
          axe1a = 0;
          axe1r = (axeXprocess) * (-10.2);
        }
        if((axeXprocess) > (0)){
          axe1r = 0;
          axe1a = (axeXprocess) * (10.2);
        }
        if(((axeXprocess)==(0))){
          axe1r = 0;
          axe1a = 0;
        }
        if((axeYprocess) < (0)){
          axe2a = 0;
          axe2r = (axeYprocess) * (-10.2);
        }
        if((axeYprocess) > (0)){
          axe2a = (axeYprocess) * (10.2);
          axe2r = 0;
        }
        if(((axeYprocess)==(0))){
          axe2a = 0;
          axe2r = 0;
        }
    }
  }

debug(1,"-------",-99);
debug(1,"message : ", message);
debug(1,"azimuth : ", azimuth);
debug(1,"azimuth rad : ", radians(azimuth));
debug(1,"axeX : ", axeX);
debug(1,"axeXprocess : ", axeXprocess);
debug(1,"axeY : ", axeY);
debug(1,"axeYprocess : ", axeYprocess);
debug(1,"tourner1 : ", tourner1);
debug(1,"tourner2 : ", tourner2);
debug(1,"axe1a : ", axe1a);
debug(1,"axe1r : ", axe1r);
debug(1,"axe2a : ", axe2a);
debug(1,"axe2r : ", axe2r);

//envoi des ordres moteur
  if((!(((tourner1)==(0)))) || (!(((tourner2)==(0))))){
    analogWrite(5,((axe2a) + (tourner2)) / (2));
    analogWrite(6,((axe2r) + (tourner1)) / (2));
    analogWrite(7,((axe2a) + (tourner1)) / (2));
    analogWrite(8,((axe2r) + (tourner2)) / (2));
    analogWrite(9,((axe1a) + (tourner2)) / (2));
    analogWrite(10,((axe1r) + (tourner1)) / (2));
    analogWrite(11,((axe1a) + (tourner1)) / (2));
    analogWrite(12,((axe1r) + (tourner2)) / (2));
  }else{
    analogWrite(5,axe2a);
    analogWrite(6,axe2r);
    analogWrite(7,axe2a);
    analogWrite(8,axe2r);
    analogWrite(9,axe1a);
    analogWrite(10,axe1r);
    analogWrite(11,axe1a);
    analogWrite(12,axe1r);
  }
  }
  else { //si azimuth=225, aucun changement n'est fait aux déplacements et une ligne est sortie au terminal si le mode debug est actif, si c'est le deguisement qui fait passer tout ça, faire arrêter les moteurs également
    debug(1, "valeur ignorée, azimuth 225", -99);
    if (stop_deguisement == 1){
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
}

//changement entre mode mormal et mode azimuth
void changement_mode(){
  if(((message)==(217))){
    if (mode_deplacement == 1)  {mode_deplacement = 2;}
    else                        {mode_deplacement = 1;}
    debug(7,"mode : ", mode_deplacement);
    message = -1;
    if (mode_deplacement == 1){
      if (type_manette == 1){Serial2.write(002);}
      else if (type_manette == 2) {SwitchPro.setLedHomeOff();}
    } else {
      if (type_manette == 1){Serial2.write(001);}
      else if (type_manette == 2) {SwitchPro.setLedHomeOn();}
    }
    
  }
}
