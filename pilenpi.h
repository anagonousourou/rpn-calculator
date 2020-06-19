#ifndef PILENPI_H
#define PILENPI_H

#include "pileoperateur.h"

struct Opera
{
   double operande;
   char operateur;
   int type;
   struct Opera *suiv;
   //1 pour operande
   //0 pour operateur

};
typedef struct Opera Opera;

Opera *creerPileNpi();
void supprimerPileNpi(Opera *deb);
void depilerPileNpi(Opera *deb);
void empilerPileNpi(Opera *deb,Opera elt);
int longueurPileNpi(Opera *deb);
void afficherPileNpi(Opera *deb);
void supprimerDePileNpi(Opera *deb,Opera *elt);

#endif // PILENPI_H
