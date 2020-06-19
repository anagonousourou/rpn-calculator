#ifndef PILEOPERATEUR_H
#define PILEOPERATEUR_H

#include <stdlib.h>
#include <stdio.h>


#define OPERATEUR 0
#define OPERANDE 1


struct PileOperateur
{
  char op;
  struct PileOperateur *suiv;

};

typedef struct PileOperateur OpPile;

OpPile *creerPile();

void supprimerOpPile(OpPile *deb);
void empilerOpPile(OpPile *deb,char c);
char depilerOpPile(OpPile *deb);



#endif // PILEOPERATEUR_H
