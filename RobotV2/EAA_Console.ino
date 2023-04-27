const String Commandes = " help \n servo(nom,angle) \n ping \n clapets_ouvrir \n clapets_fermer \n clapets_relacher";

void console(String commande){
  if(commande == "help"){
    Serial.println("======= Commandes : =======");
    Serial.println(Commandes);
    Serial.println("===========================");
  } else
  if(commande == "ping"){
    Serial.println("pong !");
  } else
  if(commande.substring(0,5) == "servo"){
    String moteur_console = (commande.substring(commande.indexOf("(") + 1 , commande.indexOf(",",commande.indexOf("(") + 1)));
    int angle_console = ((commande.substring(commande.indexOf(",") + 1 , commande.indexOf(")",commande.indexOf(",") + 1))),DEC);
    Serial.println(moteur_console);
    Serial.println(angle_console);
  } else
  if(commande == "clapets_fermer"){
    baie_gauche(0);
    baie_droite(0);
    baie_arriere(0);
    baie_avant(0);
    Serial.println("fait !");
  } else
  if(commande == "clapets_ouvrir"){
    baie_gauche(1);
    baie_droite(1);
    baie_arriere(1);
    baie_avant(1);
    Serial.println("fait !");
  } else
  if(commande == "clapets_relacher"){
    pwm.setPWM(port("Servo_baie_avant_droite"), 0, 0);
    pwm.setPWM(port("Servo_baie_avant_gauche"), 0, 0);
    pwm.setPWM(port("Servo_baie_arriere_droite"), 0, 0);
    pwm.setPWM(port("Servo_baie_arriere_gauche"), 0, 0);
    pwm.setPWM(port("Servo_baie_gauche_droite"), 0, 0);
    pwm.setPWM(port("Servo_baie_gauche_gauche"), 0, 0);
    pwm.setPWM(port("Servo_baie_droite_droite"), 0, 0);
    pwm.setPWM(port("Servo_baie_droite_gauche"), 0, 0);
    Serial.println("fait !");
  }
  else Serial.println("Commande non reconnue, tappez ''help'' pour la liste des commandes");

}
