bool printAngle = false;
uint32_t lastMessageCounter = -1;
uint32_t capture_timer;
int ZR_enclenche;
int R_enclenche;

/*============= CODES : =============
 * 1-49
 * 51-99
 * 101-149
 * 152-200
 * 
 * 201-218 : boutons appuyés 
 * 219-225 : boutons relachés
 * 
 * 001 : activer la led du bouton home
 * 002 : désactiver la led du bouton home
 */

const int type_manette_max = 2; // indiquer le nombre de manettes, de 1 à x, pour le selecteur de l'IHM

void manette_actu(){
  if(type_manette == 1){ // =========================== Manette filaire (UART)===========================
    if (Serial2.available() > 0) {
      message = Serial2.read();
      message_avail = 1;
      watchdog_manette = millis();
    }
  } else if (type_manette == 2){ // =========================== Manette BT ===========================
    if (SwitchPro.connected() && lastMessageCounter != SwitchPro.getMessageCounter()) {
      lastMessageCounter = SwitchPro.getMessageCounter();
  
      /* ===== Joystick Droite (Right) ===== */
  
      if (SwitchPro.getAnalogHat(RightHatX) > DeadzoneR || SwitchPro.getAnalogHat(RightHatX) < -(DeadzoneR)) {
        if (SwitchPro.getAnalogHat(RightHatX) > DeadzoneR) {
          message = (round(SwitchPro.getAnalogHat(RightHatX)/58.3)+25);
        }
        else message = (round(SwitchPro.getAnalogHat(RightHatX)/70.8)+25);
      }
      else message = 25;
      mouvements();debug(12, "mvmts",-99);
  
      if (SwitchPro.getAnalogHat(RightHatY) > DeadzoneR || SwitchPro.getAnalogHat(RightHatY) < -(DeadzoneR)) {
        if (SwitchPro.getAnalogHat(RightHatY) > DeadzoneR) {
          message = ((round(SwitchPro.getAnalogHat(RightHatY)/69.6)*-1)+75);
        }
        else message = ((round(SwitchPro.getAnalogHat(RightHatY)/66.6)*-1)+75);
      }
      else message = 75;
      mouvements();debug(12, "mvmts",-99);

      /* ===== Joystick Gauche (Left) ===== */

      if (SwitchPro.getAnalogHat(LeftHatX) > DeadzoneL || SwitchPro.getAnalogHat(LeftHatX) < -(DeadzoneL)) {
        if (SwitchPro.getAnalogHat(LeftHatX) > DeadzoneL) {
          message = (round(SwitchPro.getAnalogHat(LeftHatX)/58.3)+125);
        }
        else message = (round(SwitchPro.getAnalogHat(LeftHatX)/71.6)+125);
      }
      else message = 125;
      mouvements();debug(12, "mvmts",-99);

      if (SwitchPro.getAnalogHat(LeftHatY) > DeadzoneL || SwitchPro.getAnalogHat(LeftHatY) < -(DeadzoneL)) {
        if (SwitchPro.getAnalogHat(LeftHatY) > DeadzoneL) {
          message = ((round(SwitchPro.getAnalogHat(LeftHatY)/72.0)*-1)+175);
        }
        else message = ((round(SwitchPro.getAnalogHat(LeftHatY)/60.8)*-1)+175);
      }
      else message = 175;
      mouvements();debug(12, "mvmts",-99);

      if (SwitchPro.getButtonPress(CAPTURE)) { //déconexion de la manette si 1s sur le bouton capture
        if (millis() - capture_timer > 1000){SwitchPro.setLedHomeOff();SwitchPro.disconnect();}
      } else
          capture_timer = millis();
      if (SwitchPro.getButtonClick(CAPTURE)){message = 201;message_avail = 1;debug(12,"Capture",-99);return;}
      if (SwitchPro.getButtonClick(HOME))   {message = 202;message_avail = 1;debug(12,"Home",-99);return;}
      if (SwitchPro.getButtonClick(LEFT))   {message = 203;message_avail = 1;debug(12,"Left",-99);return;}
      if (SwitchPro.getButtonClick(UP))     {message = 204;message_avail = 1;debug(12,"Up",-99);return;}
      if (SwitchPro.getButtonClick(RIGHT))  {message = 205;message_avail = 1;debug(12,"Right",-99);return;}
      if (SwitchPro.getButtonClick(DOWN))   {message = 206;message_avail = 1;debug(12,"Down",-99);return;}
      if (SwitchPro.getButtonClick(PLUS))   {message = 207;message_avail = 1;debug(12,"Plus",-99);return;}
      if (SwitchPro.getButtonClick(MINUS))  {message = 208;message_avail = 1;debug(12,"Minus",-99);return;}
      if (SwitchPro.getButtonClick(A))      {message = 209;message_avail = 1;debug(12,"A",-99);return;}
      if (SwitchPro.getButtonClick(B))      {message = 210;message_avail = 1;debug(12,"B",-99);return;}
      if (SwitchPro.getButtonClick(X))      {message = 211;message_avail = 1;debug(12,"X",-99);return;}
      if (SwitchPro.getButtonClick(Y))      {message = 212;message_avail = 1;debug(12,"Y",-99);return;}
      if (SwitchPro.getButtonClick(L))      {message = 213;message_avail = 1;debug(12,"L",-99);return;}
      //if (SwitchPro.getButtonClick(R))      {message = 214;message_avail = 1;debug(12,"R",-99);return;}
      /*if (SwitchPro.getButtonPress(R) == 1 || R_enclenche == 1){
        if (SwitchPro.getButtonPress(R) == 1){
          if (R_enclenche == 0){message = 214;message_avail = 1;return;}
          R_enclenche = 1;
      }else{message = 220; R_enclenche = 0;message_avail = 1;return;}
      }
      if (SwitchPro.getButtonClick(ZL))     {message = 215;message_avail = 1;debug(12,"ZL",-99);return;}
      //if (SwitchPro.getButtonClick(ZR))     {message = 216;message_avail = 1;debug(12,"ZR",-99);return;}
      if (SwitchPro.getButtonPress(ZR) == 1 || ZR_enclenche == 1){
        if (SwitchPro.getButtonPress(ZR) == 1){
          if (ZR_enclenche == 0){message = 216;message_avail = 1;return;}
          ZR_enclenche = 1;
      }else{message = 219; ZR_enclenche = 0;message_avail = 1;return;}
      }*/
      if (SwitchPro.getButtonClick(L3))     {message = 217;message_avail = 1;debug(12,"L3",-99);return;}
      if (SwitchPro.getButtonClick(R3))     {message = 218;message_avail = 1;debug(12,"R3",-99);return;}      
    }    
    
  }












  
}
