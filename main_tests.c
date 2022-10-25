#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20
#define ENERGIE 10.0

float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;


int main(void) {
  /* A Completer. */
  /* Part 1, exercice 5, question 3 */
  //srand(time(NULL));



  Animal*l_proie= creer_animal((rand()%SIZE_X),(rand()%SIZE_Y),ENERGIE);;
  Animal*l_predateur= creer_animal((rand()%SIZE_X),(rand()%SIZE_Y),ENERGIE);
  //Animal*tmp;



  for(int i=1; i<NB_PROIES; i++){
    ajouter_animal((rand()%SIZE_X),(rand()%SIZE_Y),ENERGIE,&l_proie);
	  }
  

  for(int e=1; e<NB_PREDATEURS; e++){
	  ajouter_animal((rand()%SIZE_X),(rand()%SIZE_Y),ENERGIE,&l_predateur);
	  }


  printf("Il y a %d animaux\n",compte_animal_it(l_proie));
  printf("Il y a %d predateurs\n",compte_animal_it(l_predateur));

  enlever_animal(&l_proie,l_proie);
  printf("Il y a %d animaux\n",compte_animal_rec(l_proie));

  afficher_ecosys(l_proie,l_predateur);
  bouger_animaux(l_proie);
  bouger_animaux(l_predateur);
  afficher_ecosys(l_proie,l_predateur);

  reproduce(&l_proie,p_reproduce_proie);
  printf("Il y a %d animaux\n",compte_animal_it(l_proie));
  afficher_ecosys(l_proie,l_predateur);
  
  return 0;
}
