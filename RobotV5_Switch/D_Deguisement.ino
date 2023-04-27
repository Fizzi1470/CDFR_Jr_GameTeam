unsigned long timer_bleu;
int random_bleu;
unsigned long timer_blanc;
int random_blanc;
boolean bleu;
boolean blanc;

void changer_etat_deguisement(){
  if (deguisement == 0){
    deguisement = 1;
    if(musique == 1)
      digitalWrite(3, 0);
  } else {
    deguisement = 0;
    digitalWrite(3, 1);
  }
  if (deguisement == 0) {
    digitalWrite(33-deguisement1,0);
    digitalWrite(33-deguisement2,0);
  }
}

void gestion_deguisement(){
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
