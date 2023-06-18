boolean R2_simule;
boolean L2_simule;
boolean R1_simule;
boolean L1_simule;

void gestion_manette(){
if (type_manette == 1){
  if (PS3.PS3Connected) {
    if (PS3.getAnalogHat(RightHatX) > 127+DeadzoneR || PS3.getAnalogHat(RightHatX) < 127-DeadzoneR) {
      if (PS3.getAnalogHat(RightHatX) > 127+DeadzoneR)  axeTourner = (round((PS3.getAnalogHat(RightHatX)-127.5)/5.1));
      else                                              axeTourner = (round((PS3.getAnalogHat(RightHatX)-127.5)/5.1));
    } else axeTourner = 0;
    /*
    if (PS3.getAnalogHat(RightHatY) > DeadzoneR || PS3.getAnalogHat(RightHatY) < -(DeadzoneR)) {
      if (PS3.getAnalogHat(RightHatY) > DeadzoneR)  message = ((round(PS3.getAnalogHat(RightHatY)/69.6)*-1));
      else                                                message = ((round(PS3.getAnalogHat(RightHatY)/66.6)*-1));
    } else message = 0;
    */
    /* ===== Joystick Gauche (Left) ===== */

    if (PS3.getAnalogHat(LeftHatX) > 127+DeadzoneL || PS3.getAnalogHat(LeftHatX) < 127-DeadzoneL) {
      if (PS3.getAnalogHat(LeftHatX) > 127+DeadzoneL) axeX = (round((PS3.getAnalogHat(LeftHatX)-127.5)/5.1));
      else                                            axeX = (round((PS3.getAnalogHat(LeftHatX)-127.5)/5.1));
    } else axeX = 0;

    if (PS3.getAnalogHat(LeftHatY) > 127+DeadzoneL || PS3.getAnalogHat(LeftHatY) < 127-DeadzoneL) {
      if (PS3.getAnalogHat(LeftHatY) > 127+DeadzoneL) axeY = (round((PS3.getAnalogHat(LeftHatY)-127.5)/5.1))*-1;
      else                                            axeY = (round((PS3.getAnalogHat(LeftHatY)-127.5)/5.1))*-1;
    } else axeY = 0;
    //Serial.print(axeTourner);Serial.print(";"); Serial.print(axeX);Serial.print(";");Serial.println(axeY);

    if (PS3.getButtonPress(PS)) {
      if (millis() - capture_timer > 1000) PS3.disconnect();
    } else capture_timer = millis();

    if (PS3.getButtonClick(PS))changer_etat_deguisement();

    if (PS3.getButtonClick(LEFT))if(mode_sequence) sequence = 499; else lancer_sequence(42);
    if (PS3.getButtonClick(UP))if(mode_sequence) sequence = 299; else lancer_sequence(1);
    if (PS3.getButtonClick(RIGHT))if(mode_sequence) sequence = 199; else lancer_sequence(12);
    if (PS3.getButtonClick(DOWN))if(mode_sequence) sequence = 399; else lancer_sequence(32);
  
    if (PS3.getButtonClick(START))augmenter_score();
    if (PS3.getButtonClick(SELECT))diminuer_score();
    
    if (PS3.getButtonClick(CIRCLE))if (mode_sequence) add_sequence(1); else if (maintient_L1){bouton_cerise_presse = 1;cerise_droite = 1;} else baie_droite(-1);
    if (PS3.getButtonClick(CROSS))if (mode_sequence) add_sequence(3); else if (maintient_L1){bouton_cerise_presse = 1;cerise_arriere = 1;} else baie_arriere(-1);
    if (PS3.getButtonClick(TRIANGLE))if (mode_sequence) add_sequence(2); else if (maintient_L1){bouton_cerise_presse = 1;cerise_avant = 1;} else baie_avant(-1);
    if (PS3.getButtonClick(SQUARE))if (mode_sequence) add_sequence(4); else if (maintient_L1){bouton_cerise_presse = 1;cerise_gauche = 1;} else baie_gauche(-1);

    if (PS3.getButtonPress(L1)){maintient_L1 = 1;
                              } else if (maintient_L1){
                                maintient_L1 = 0;
                                if (bouton_cerise_presse == 0){
                                  if(sequence_cerises_prete == 0){cerise_avant = 1;cerise_arriere = 1;cerise_droite = 1;cerise_gauche = 1;}
                                }
                                sequence_cerises_prete = 1;
                                bouton_cerise_presse = 0;
                                if (sequence_cerise_en_cours == 0)lancer_sequence_cerises();else {cerise_avant = 0;cerise_arriere = 0;cerise_droite = 0;cerise_gauche = 0;}
                              }
                                 
    if (PS3.getButtonPress(R1) && sequence_prete == 0){mode_sequence = 1;premier_relachement_bouton_sequence = 1;/*PS3.setRumbleOn(RumbleHigh);*/} else{ mode_sequence = 0;/*PS3.setRumbleOff();*/
                                                                                                                                if (premier_relachement_bouton_sequence == 1){
                                                                                                                                  if (sequence < 100 || sequence > 1000) sequence = 0;
                                                                                                                                  else {sequence_prete = 1;timer_sequence_principal = millis();}}
                                                                                                                                premier_relachement_bouton_sequence = 0;}

    if (PS3.getButtonPress(CIRCLE) && PS3.getButtonPress(CROSS) && PS3.getButtonPress(TRIANGLE) && PS3.getButtonPress(SQUARE) && mode_sequence == 1) {
      sequence_terminee = 1;
      identifiant_sequence = 0;
      sequence = 0;
      sequence_prete = 0;
    }
  
    if (PS3.getAnalogButton(R2) > 150 && deguisement == 0){if (ancien_turbine == turbine){changer_etat_aspiro();}}else ancien_turbine = turbine;
    if (PS3.getAnalogButton(L2) > 150 && deguisement == 0){if(reservoir != 1)ouvrir_reservoir();} else {if(reservoir != 0 && vidange == 0)fermer_reservoir();}

    if (PS3.getButtonClick(L3))changer_mode();
    if (PS3.getButtonClick(R3))calibrer_azimuth();
    
  }
  else {
    analogWrite(5,0);
    analogWrite(6,0);
    analogWrite(7,0);
    analogWrite(8,0);
    analogWrite(9,0);
    analogWrite(10,0);
    analogWrite(11,0);
    analogWrite(12,0);
    premiere_conexion = 1;
  }   
  
  if(PS3.PS3Connected && premiere_conexion == 1){
    PS3.setLedOff(LED1);
    PS3.setLedOff(LED2);
    PS3.setLedOn(LED3);
    PS3.setLedOn(LED4);
    premiere_conexion = 0;
  }
}
}
/*
if (Serial2.available() > 0){
  int message = Serial2.read() - 48;

    if (message == 222){R1_simule == 1;}else if (message == 223){R1_simule == 0;}
    if (message == 217){L2_simule == 1;}else if (message == 218){L2_simule == 0;}
    if (message == 220){L1_simule == 1;}else if (message == 221){L1_simule == 0;}

    if(message < 51){
      axeTourner = message - 25;
    }
    if(message > 50 && message < 102){
      axeX = message - 76;
    }
    if(message > 101 && message < 153){
      axeY = message - 127;
    }
    
    if (message == 204)changer_etat_deguisement();

    if (message == 212)lancer_sequence(42);
    if (message == 209)lancer_sequence(1);
    if (message == 210)lancer_sequence(12);
    if (message == 211)lancer_sequence(32);
  
    if (message == 214)augmenter_score();
    if (message == 213)diminuer_score();
    
    if (message == 206)if (mode_sequence) add_sequence(1); else if (maintient_L1){bouton_cerise_presse = 1;cerise_droite = 1;} else baie_droite(-1);
    if (message == 207)if (mode_sequence) add_sequence(3); else if (maintient_L1){bouton_cerise_presse = 1;cerise_arriere = 1;} else baie_arriere(-1);
    if (message == 205)if (mode_sequence) add_sequence(2); else if (maintient_L1){bouton_cerise_presse = 1;cerise_avant = 1;} else baie_avant(-1);
    if (message == 208)if (mode_sequence) add_sequence(4); else if (maintient_L1){bouton_cerise_presse = 1;cerise_gauche = 1;} else baie_gauche(-1);

    if (L1_simule){maintient_L1 = 1;
                              } else if (maintient_L1){
                                maintient_L1 = 0;
                                if (bouton_cerise_presse == 0){
                                  if(sequence_cerises_prete == 0){cerise_avant = 1;cerise_arriere = 1;cerise_droite = 1;cerise_gauche = 1;}
                                }
                                sequence_cerises_prete = 1;
                                bouton_cerise_presse = 0;
                                if (sequence_cerise_en_cours == 0)lancer_sequence_cerises();else {cerise_avant = 0;cerise_arriere = 0;cerise_droite = 0;cerise_gauche = 0;}
                              }
                                 
    if (R1_simule && sequence_prete == 0){mode_sequence = 1;premier_relachement_bouton_sequence = 1;} else{ mode_sequence = 0;//PS3.setRumbleOff();
                                                                                                                                if (premier_relachement_bouton_sequence == 1){
                                                                                                                                  if (sequence < 100 || sequence > 1000) sequence = 0;
                                                                                                                                  else {sequence_prete = 1;timer_sequence_principal = millis();}}
                                                                                                                                premier_relachement_bouton_sequence = 0;}

    if (message == 230 && mode_sequence == 1) {
      sequence_terminee = 1;
      identifiant_sequence = 0;
      sequence = 0;
      sequence_prete = 0;
    }
  
    if (message == 219 && deguisement == 0)changer_etat_aspiro();
    if (L2_simule > 150 && deguisement == 0){if(reservoir != 1)ouvrir_reservoir();} else {if(reservoir != 0 && vidange == 0)fermer_reservoir();}

    if (message == 216)changer_mode();
    if (message == 215)calibrer_azimuth();

    message = -1;
  }
*/
