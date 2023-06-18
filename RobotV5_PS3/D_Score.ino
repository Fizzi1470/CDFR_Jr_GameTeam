int score = 0;
byte cut_score = 0;

int chiffre1 = -1;
int chiffre2 = -1;
int chiffre3 = -1;
int chiffre;

void gestion_score(){
  if(Serial3.available() != 0){
    chiffre = Serial3.read() - 48;
    if (chiffre==-5) resettrigger=1;
    if (chiffre == 12){
      if (chiffre3 != -1 && score_max == 2){
        chiffre3 = -1;
        Serial3.print(F(" = > "));Serial3.println((chiffre1*10) + chiffre2);
      }else if (chiffre2 != -1){
        chiffre2 = -1;
        Serial3.print(F(" = > "));Serial3.println(chiffre1);
      }else if (chiffre1 != -1){
        chiffre1 = -1;
        Serial3.print(F(" = > "));Serial3.println(F(" ")); 
      }
    }else{
      if (chiffre1 == -1){
        chiffre1 = chiffre;
        Serial3.print(F(" = > "));Serial3.println(chiffre1);
      }else if (chiffre2 == -1){
        chiffre2 = chiffre;
        Serial3.print(F(" = > "));Serial3.println((chiffre1*10) + chiffre2);
      }else if (chiffre3 == -1 && score_max == 2){
        chiffre3 = chiffre;
        Serial3.print(F(" = > "));Serial3.println((chiffre1*100) + (chiffre2*10) + chiffre3);
      }else{
        chiffre2 = -1; chiffre3 = -1;
        chiffre1 = chiffre;
        Serial3.print(F(" = > "));Serial3.println(chiffre1);
      }
      if(chiffre3 != -1 && score_max == 2){
        score = (chiffre3 * 1) + (chiffre2 * 10) + (chiffre1 * 100);
        afficheurs.showNumberDec(score, false);
        Serial3.println(score);
      }
      if(chiffre2 != -1 && score_max == 1){
        score = (chiffre2 * 1) + (chiffre1 * 10);
        afficheurs.showNumberDec(score, false);
        Serial3.println(score);
      }
    }
  }   
}

void diminuer_score(){
  if (score == 0)
    score = score_defaut;
  score = score - retrait_score;
  if (score < 0) score = 0;
  //debug(2,F("score diminué de "), retrait_score);
  //debug(2,F("nouveau score :"), score);
  afficheurs.showNumberDec(score, false);
}
void augmenter_score(){
  if (score == 0)
    score = score_defaut;
  score = score + ajout_score;
  if (score > 9999) score = 9999;
  //debug(2,F("score augmenté de "), ajout_score);
  //debug(2,F("nouveau score :"), score);
  afficheurs.showNumberDec(score, false);
}
