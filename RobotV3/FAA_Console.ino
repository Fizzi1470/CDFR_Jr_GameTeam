void lire_console(){
  String lecture_console;
  //debug(10,F("lect_cons"), -99);
  delay(5);
  while (Serial.available() > 0){
    lecture_console.concat((char)Serial.read());
  }
  Serial.print(F("> ")); Serial.println(lecture_console);
  console(lecture_console); //debug(10, "cons", -99);
}

void test1(){
  lancer_sequence(F("arriere_vers_gauche"));
  //bras1_passe_levage();
}

void test2(){
  lancer_sequence(F("droite_vers_avant"));
}



void console(String commande){
  if(commande == F("ping")){
    Serial.println(F("Pong !"));

  } else if(commande == F("reset")){
    Serial.println(F("en cours . . ."));
    wdt_enable(WDTO_1S);
    delay(2000);
    
  } else if(commande == F("help")){
    Serial.println(F("======= Commandes : ======="));
    Serial.println(F(" ping \n reset \n test1 \n test2 \n help \n info(commande) (note : ne pas inclure les parenthèses des commandes)\n stop \n servo(nom,angle) \n debug(valeur) \n noms \n turbine \n deguisement \n mode_deplacement \n calibrer_azimuth \n clapets_ouvrir \n clapets_entrouvrir \n clapets_fermer \n clapets_relacher \n bras1_haut \n bras1_bas \n bras2_haut \n bras2_bas \n bras1_arriere \n bras1_avant \n bras2_arriere \n bras2_avant \n lancer_sequence(sequence) \n pompe(numéro, état)"));
    Serial.println(F("==========================="));
    
  } else if(commande.substring(0,4) == F("info")){
    String infoCommande = (commande.substring(commande.indexOf("(") + 1 , commande.indexOf(")")));
    if(infoCommande == "ping") Serial.println(F("Répond pong"));
    else if(infoCommande == F("help")) Serial.println(F("Donne la liste des commandes disponnibles"));
    else if(infoCommande == F("info")) Serial.println(F("Donne les informations sur une commande"));
    else if(infoCommande == F("stop")) Serial.println(F("Stoppe tous les actionneurs du robot (Attention : ne le fait qu'une fois, dans le cas des moteurs de déplacement par exemple, si une nouvelle valeur du joystick leur est fournie, ils se relanceront, il en va de même pour les servomoteurs et autres actionneurs)"));
    else if(infoCommande == F("servo")) Serial.println(F("Oriente le servomoteur spécifié à l'angle spécifié (liste des servo disponnible avec la commande ''noms'', et angle entre 0 et 180 inclus)"));
    else if(infoCommande == F("debug")) Serial.println(F("Met la variable debug à la valeur spécifiée"));
    else if(infoCommande == F("noms")) Serial.println(F("Donne la liste des noms des servomoteurs disponnibles"));
    else if(infoCommande == F("turbine")) Serial.println(F("Allume/Eteint la turbine d'aspiration"));
    else if(infoCommande == F("clapets_ouvrir")) Serial.println(F("Ouvre tous les clapets"));
    else if(infoCommande == F("clapets_fermer")) Serial.println(F("Ferme tous les clapets"));
    else if(infoCommande == F("clapets_relacher")) Serial.println(F("Libère le maintient de position des clapets pour une manipulation manuelle"));
    else Serial.println(F("Commande inconnue"));
    
  } else if(commande.substring(0,5) == F("servo")){
    String moteur_console = (commande.substring(commande.indexOf("(") + 1 , commande.indexOf(",",commande.indexOf("(") + 1)));
    String valeurAngleString = (commande.substring(commande.indexOf(",") + 1 , commande.indexOf(")",commande.indexOf(",") + 1)));
    int angle_console = valeurAngleString.toInt();
    servo(moteur_console,angle_console);
    Serial.print(F("Moteur ''")); Serial.print(moteur_console); Serial.print(F("'' mis à l'angle ")); Serial.println(angle_console);
    
  } else if(commande.substring(0,5) == F("debug")){
    String valeurdebugString = (commande.substring(commande.indexOf("(") + 1 , commande.indexOf(")")));
    mode_debug = valeurdebugString.toInt();
    Serial.print(F("Mode débug modifié, nouvelle valeur : ")); Serial.println(mode_debug);
    
  } else if(commande == F("clapets_fermer")){
    baie_gauche(0);
    baie_droite(0);
    baie_arriere(0);
    baie_avant(0);
    Serial.println(F("fait !"));

  } else if(commande == F("clapets_entrouvrir")){
    baie_gauche(1);
    baie_droite(1);
    baie_arriere(1);
    baie_avant(1);
    Serial.println(F("fait !"));
    
  } else if(commande == F("clapets_ouvrir")){
    baie_gauche(2);
    baie_droite(2);
    baie_arriere(2);
    baie_avant(2);
    Serial.println(F("fait !"));
    
  } else if(commande == F("clapets_relacher")){
    pwm.setPWM(port(F("Servo_baie_avant_droite")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_avant_gauche")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_arriere_droite")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_arriere_gauche")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_gauche_droite")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_gauche_gauche")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_droite_droite")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_droite_gauche")), 0, 0);
    Serial.println(F("fait !"));
    
  } else if(commande == F("stop")){
    identifiant_sequence = F("rien"); sequence_terminee = 1;
    pwm.setPWM(port(F("Servo_baie_avant_droite")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_avant_gauche")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_arriere_droite")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_arriere_gauche")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_gauche_droite")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_gauche_gauche")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_droite_droite")), 0, 0);
    pwm.setPWM(port(F("Servo_baie_droite_gauche")), 0, 0);
    pwm.setPWM(port(F("Servo_levage1")), 0, 0);
    pwm.setPWM(port(F("Servo_levage2")), 0, 0);
    pwm.setPWM(port(F("Servo_axe1")), 0, 0);
    pwm.setPWM(port(F("Servo_axe2")), 0, 0);
    pwm.setPWM(port(F("Servo_tube_cerise1")), 0, 0);
    digitalWrite(5,0);
    digitalWrite(6,0);
    digitalWrite(7,0);
    digitalWrite(8,0);
    digitalWrite(9,0);
    digitalWrite(10,0);
    digitalWrite(11,0);
    digitalWrite(12,0);
    digitalWrite(13,0);
    digitalWrite(25,0);
    digitalWrite(26,0);
    digitalWrite(27,0);
    digitalWrite(28,0);
    digitalWrite(29,0);
    digitalWrite(30,0);
    digitalWrite(31,0);
    digitalWrite(44,0);
    digitalWrite(45,0);
    Serial.println(F("Robot stoppé"));
    
  } else if(commande == F("noms")){
    Serial.println(F("Servomoteurs disponnibles : \n Servo_levage1 \n Servo_axe1 \n Servo_levage2 \n Servo_axe2 \n Servo_tube_cerise \n Servo_baie_avant_droite \n Servo_baie_avant_gauche \n Servo_baie_arriere_droite \n Servo_baie_arriere_gauche \n Servo_baie_gauche_droite \n Servo_baie_gauche_gauche \n Servo_baie_droite_droite \n Servo_baie_droite_gauche \n Servo_clapet_cerise"));
  
  } else if(commande == F("turbine")){
    changer_etat_aspiro();
    Serial.print(F("Turbine d'aspiration désormais à l'état ")); Serial.println(turbine);
    
  } else if (commande == F("bras1_haut")){
    bras1_haut();
    Serial.println(F("fait ! "));
    
  } else if (commande == F("bras1_bas")){
    bras1_bas();
    Serial.println(F("fait ! "));
    
  } else if (commande == F("bras2_haut")){
    bras2_haut();
    Serial.println(F("fait ! "));
    
  } else if (commande == F("bras2_bas")){
    bras2_bas();
    Serial.println(F("fait ! "));

  } else if (commande == F("bras1_arriere")){
    bras1_arriere();
    Serial.println(F("fait !"));

  } else if (commande == F("bras1_avant")){
    bras1_avant();
    Serial.println(F("fait !"));

  } else if (commande == F("bras2_avant")){
    bras2_avant();
    Serial.println(F("fait !"));

  } else if (commande == F("bras2_arriere")){
    bras2_arriere();
    Serial.println(F("fait !"));

  } else if(commande.substring(0,15) == F("lancer_sequence")){
    String infoCommande = (commande.substring(commande.indexOf("(") + 1 , commande.indexOf(")")));
    lancer_sequence(infoCommande);
    Serial.print(F("Séquence ")); Serial.print(infoCommande); Serial.println(F(" lancée !"));
    
  } else if (commande == F("mode_deplacement")){
    changer_mode();
    if (mode_deplacement == 1)
      Serial.println(F("Mode de déplacement en mode azimuth"));
    else
      Serial.println(F("Mode de déplacement en mode normal"));

  } else if (commande == F("calibrer_azimuth")){
    calibrer_azimuth();
    Serial.println("fait !");
    
  } else if (commande == F("deguisement")){
    changer_etat_deguisement();
    Serial.println(F("fait !"));
    
  } else if(commande.substring(0,5) == F("pompe")){
    String valeurIdPompe = (commande.substring(commande.indexOf("(") + 1 , commande.indexOf(",",commande.indexOf("(") + 1)));
    String valeurEtatPompe = (commande.substring(commande.indexOf(",") + 1 , commande.indexOf(")",commande.indexOf(",") + 1)));
    int IdPompe = valeurIdPompe.toInt();
    int EtatPompe = valeurEtatPompe.toInt();
    if (EtatPompe > 0 || EtatPompe < 3) {
      if (IdPompe == 1){
        bras1_ventouse(EtatPompe);
        Serial.print(F("Pompe 1 mis à l'état ")); Serial.println(EtatPompe);
      } else if (IdPompe == 2){
        bras2_ventouse(EtatPompe);
        Serial.print(F("Pompe 2 mis à l'état ")); Serial.println(EtatPompe);
      } else
        Serial.println(F("Numéro de pompe invalide"));
    } else 
      Serial.println(F("Etat demandé invalide"));

  } else if (commande == F("test1")){
    test1();
    Serial.println(F("Code de test 1 terminé"));

  } else if (commande == F("test2")){
    test2();
    Serial.println(F("Code de test 2 terminé"));
  
  }else 
  Serial.println(F("Commande non reconnue, tappez ''help'' pour la liste des commandes"));
}
