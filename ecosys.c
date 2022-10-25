#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y,  float energie, Animal **pt_liste_animal) {
  Animal*pt_animal=NULL;
  //assert(x<SIZE_X && y<SIZE_Y && x>0 && y>0);	
  //assert (x>=0 && y>=0 && x<=SIZE_X && y<=SIZE_Y);
	  
  pt_animal=creer_animal(x,y,energie);
  *pt_liste_animal= ajouter_en_tete_animal(*pt_liste_animal,pt_animal);
  
  return;
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **pt_liste, Animal *pt_animal) {
  Animal *liste   = *pt_liste ;
  Animal *pt_prc  = NULL      ;
  Animal *pt_nxt  = NULL      ;
  Animal *pt_head = liste     ;

  while (pt_head != NULL) {
    if (pt_head==pt_animal) {
      break;
    }
    pt_prc  = pt_head          ;
    pt_head = pt_head->suivant ;
  }

  if (pt_head != NULL) {
    pt_nxt = pt_head->suivant;
  if (pt_prc != NULL)
    pt_prc->suivant = pt_nxt;
  else
    liste = pt_nxt;
  free(pt_animal);
  }
  *pt_liste = liste;

  return ;
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
   Animal*tmp=NULL;
   while(liste!=NULL){
     tmp=liste;
     liste=liste->suivant;
	   free(tmp);
	   }
  return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}


/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  //int nbpred=0,nbproie=0;
  //Animal *pa=NULL;

  /* on initialise le tableau */
    /*A Completer*/
  for(int i=0; i<SIZE_X ; i++){
    for(int j=0;j<SIZE_Y;j++){
      ecosys[i][j]=' ';
    }
  }


  /* on ajoute les proies */
    /*A Completer*/
  Animal*t=liste_proie;
  while(t){
    ecosys[t->x][t->y]='*';
    t=t->suivant;
  }


  /* on ajoute les predateurs */
  /*A Completer*/
  t=liste_predateur;
  while(t){
    if (ecosys[t->x][t->y]=='*'){
      ecosys[t->x][t->y]='@';
    }
    else{
      ecosys[t->x][t->y]='O';
    }
  t=t->suivant;
  }


  /* on affiche le tableau */
  /*A Completer*/
    printf("+"); 
      for (int i=0; i<SIZE_Y;i++){
         printf("-");
     }
     printf("+\n"); 
    for (int i=0; i<SIZE_X; i++){
        printf("|");
        for (int j=0; j<SIZE_Y; j++){
            printf("%c", ecosys[i][j]);
        }
        printf("| \n");
    }
    printf("+"); 
      for (int i=0; i<SIZE_Y;i++){
         printf("-");
     }
     printf("+\n"); 
}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
    /*A Completer*/

void bouger_animaux(Animal *la) {
  while (la != NULL) 
  {
    if (((float) rand())/RAND_MAX < p_ch_dir ) {
    
      la->dir[0] = rand() % 3 - 1;
      la->dir[1] = rand() % 3 - 1;
    
      la->x= (la->x+la->dir[1]);   
      la->y= (la->y+la->dir[0]);   

      la->x-=la->dir[0];
      la->y-=la->dir[1];

      if(la->x>SIZE_X){
        la->x=(la->x)%SIZE_X;
      }
      if(la->x<0){
        la->x=SIZE_X-la->x;
      }
    
      if(la->y>SIZE_Y){
        (la->y)%=SIZE_Y;
      }

      if(la->y<0){
        la->y=SIZE_Y-la->y;
      }
      
    }
    la=la->suivant;
  }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
   /*A Completer*/
  Animal *tmp=*liste_animal;

  while(tmp){
  
    if((float)rand()/RAND_MAX< p_reproduce){
      ajouter_animal(tmp->x,tmp->y,(tmp->energie/=2.),liste_animal);
      printf("position (%d,%d), energie : %f\n",tmp->x,tmp->y,tmp->energie/=2.);
    }
  tmp=tmp->suivant;
  }
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    /*A Completer*/
    Animal*list=*liste_proie;
    Animal*l=list;
    bouger_animaux(l);

    while(l){
      l->energie-=1;
      if(monde[l->x][l->y] > 0){
        l->energie+=monde[l->x][l->y];
        monde[l->x][l->y]=temps_repousse_herbe;
      }

      if(l->energie<=0){
        enlever_animal(liste_proie,l);
      }
 
      l=l->suivant;
    }
    reproduce(liste_proie,p_reproduce_proie);
}
  

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    /*A Completer*/

  while(l!=NULL){
    if(l->y==y && l->x==x){
      return l;
    }
    l=l->suivant;
  }
  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
   /*A Completer*/

    Animal*list1=*liste_predateur;
    Animal*l=list1;
    bouger_animaux(l);

    while(l){
      l->energie-=1;
      if(l->energie<=0){
        enlever_animal(liste_predateur,l);

      }

      if ((animal_en_XY(*liste_proie,l->x,l->y))!=NULL){
        l->energie+=(*liste_proie)->energie;
        enlever_animal(liste_proie,l);
      }  
      l=l->suivant;
    }
    reproduce(liste_predateur,p_reproduce_predateur);
}


/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
   /*A Completer*/
  for(int i=0;i<SIZE_X;i++){
    for(int j=0;j<SIZE_Y;j++){
      monde[i][j]+=1;
    }
  }
}

