unsigned long timer_bleu;
int random_bleu;
unsigned long timer_blanc;
int random_blanc;
int bleu; // pin 45
int blanc; // pin 49
int stop_musique;

void deguisement(){
  if (message == 202){
    if (stop_deguisement == 0){
      stop_deguisement = 1;
      if(musique == 1)
        digitalWrite(2, 1);
    } else {
      stop_deguisement = 0;
      digitalWrite(2, 0);
    }
    debug(6, "mode déguisement modifié, nouvelle valeur : ", stop_deguisement);
    message = -1;
    if (stop_deguisement == 0) {
      digitalWrite(33-deguisement1,0);
      digitalWrite(33-deguisement2,0);
    }
  }
  
  if (stop_deguisement == 1) {
    if ((millis() - timer_bleu) > random_bleu){
      random_bleu = random(delais_min_deguisement, delais_max_deguisement)*100;
      timer_bleu = millis();
      if (bleu == 1){
        bleu = 0;
      } else {
        bleu = 1;
      }
      digitalWrite(33-deguisement1,bleu);
    }
    if ((millis() - timer_blanc) > random_blanc){
      random_blanc = random(delais_min_deguisement, delais_max_deguisement)*100;
      timer_blanc = millis();
      if (blanc == 1){
        blanc = 0;
      } else {
        blanc = 1;
      }
      digitalWrite(33-deguisement2,bleu);
    }
  }
}
