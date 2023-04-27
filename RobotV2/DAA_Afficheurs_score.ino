int score = 0;
int cut_score = 0;

int chiffre1 = -1;
int chiffre2 = -1;
int chiffre3 = -1;
int chiffre;

void actu_score(){ //ancienne version, qui ne correspond plus à l'application
        score = 0;
        cut_score = 0;
        score += ((Serial3.read()) - (48)) * (1000);
        delay(2);

        debug(2,"score : ",score);
        
        if(!(((Serial3.available())==(0)))){
            score += ((Serial3.read()) - (48)) * (100);
            delay(2);
        }else{
            cut_score += 1;
        }

        debug(2,"score : ",score);
        
        if(!(((Serial3.available())==(0)))){
            score += ((Serial3.read()) - (48)) * (10);
            delay(2);
        }else{
            cut_score += 1;
        }

        debug(2,"score : ",score);
        
        if(!(Serial3.available()==0)){
            score += (Serial3.read()) - (48);
        }else{
            cut_score += 1;
        }

        debug(2,"score : ",score);
        debug(2,"cut score :",cut_score);

        score = score / (pow(10,cut_score));
        afficheurs.showNumberDec(score, false);

        debug(2,"score final :",(score) / (pow(10,cut_score)));
        debug(2, "-----------",-99);
}

void gestion_score(){
  if(Serial3.available() != 0){
    chiffre = Serial3.read() - 48;
    if (chiffre == 12){
      if (chiffre3 != -1 && score_max == 2){
        chiffre3 = -1;
        Serial3.print(" = > ");Serial3.println((chiffre1*10) + chiffre2);
      }else if (chiffre2 != -1){
        chiffre2 = -1;
        Serial3.print(" = > ");Serial3.println(chiffre1);
      }else if (chiffre1 != -1){
        chiffre1 = -1;
        Serial3.print(" = > ");Serial3.println(" "); 
      }
    }else{
      if (chiffre1 == -1){
        chiffre1 = chiffre;
        Serial3.print(" = > ");Serial3.println(chiffre1);
      }else if (chiffre2 == -1){
        chiffre2 = chiffre;
        Serial3.print(" = > ");Serial3.println((chiffre1*10) + chiffre2);
      }else if (chiffre3 == -1 && score_max == 2){
        chiffre3 = chiffre;
        Serial3.print(" = > ");Serial3.println((chiffre1*100) + (chiffre2*10) + chiffre3);
      }else{
        chiffre2 = -1; chiffre3 = -1;
        chiffre1 = chiffre;
        Serial3.print(" = > ");Serial3.println(chiffre1);
      }
      if(chiffre3 != -1 && score_max == 2){
        score = (chiffre3 * 10) + (chiffre2 * 1) + (chiffre1 * 10);
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

void changement_manuel_score(){
  if (message == 208){
    if (score == 0)
      score = score_defaut;
    score = score - retrait_score;
    debug(2, "score diminué de ", retrait_score);
    debug(2, "nouveau score :", score);
    afficheurs.showNumberDec(score, false);
  }
  if (message == 207){
    if (score == 0)
      score = score_defaut;
    score = score + ajout_score;
    debug(2, "score augmenté de ", ajout_score);
    debug(2, "nouveau score :", score);
    afficheurs.showNumberDec(score, false);
  }
}
