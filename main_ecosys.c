#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 50
#define NB_PREDATEURS 50
#define T_WAIT 40000
#define ENERGIE 100.0


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;


int main(void) {
  int monde[SIZE_X][SIZE_Y];
  for(int i=0; i<SIZE_X ; i++){
    for(int e=0; e<SIZE_Y ; e++){
      monde[i][e]=0;
    }
  }

 
  /* A completer. Part 2:
  /* exercice 4, questions 2 et 4 */
  Animal*l_proie= creer_animal(15,30,ENERGIE);;
  bouger_animaux(l_proie);

  reproduce(&l_proie,p_reproduce_proie);


  //exercice 6, question 2
  Animal*l_predateur= creer_animal((rand()%SIZE_X),(rand()%SIZE_Y),ENERGIE);

  for(int i=1; i<NB_PROIES; i++){
    ajouter_animal((rand()%SIZE_X),(rand()%SIZE_Y),ENERGIE,&l_proie);
	  }
  

  for(int e=1; e<NB_PREDATEURS; e++){
	  ajouter_animal((rand()%SIZE_X),(rand()%SIZE_Y),ENERGIE,&l_predateur);
	  }

afficher_ecosys(l_proie,l_predateur);

FILE *f= fopen("Evol_Pop.txt","w");

int i=1;
while(compte_animal_it(l_proie)>0){
  fprintf(f,"%d %d %d\n",i, compte_animal_rec(l_proie), compte_animal_rec(l_predateur));

  rafraichir_proies(&l_proie,monde);
  printf("Il y a %d animaux et %d predateurs\n",compte_animal_rec(l_proie),compte_animal_rec(l_predateur) );
  rafraichir_predateurs(&l_predateur,&l_proie);
  rafraichir_monde(monde);
  afficher_ecosys(l_proie,l_predateur);

  i++;

  usleep (1);
}
  fclose(f);


if(compte_animal_it(l_proie)==compte_animal_it(l_predateur) && compte_animal_it(l_proie)==0){
  printf("Ils sont tous morts\n");}

/*
   * exercice 7, question 3
   * exercice 8, question 1
   */

/* taper dans le terminal, les commandes :
plot "Evol_Pop.txt" using 1:2 with lines titles "proies"
replot "Evol_Pop.txt" using 1:3 with lines title "predateurs" */

  return 0;
}

