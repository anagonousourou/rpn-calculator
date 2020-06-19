#ifndef VERIF_H
#define VERIF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int verifierExpression(char *chaine);
int verifierParentheses(char *chaine);
int verifierSymboles(char *chaine);
int verifierFonction(char *chaine);
int verifierPosOperateurs(char *chaine);

int nbOccurrencesMot(char *mot,char *phrase);
int in(char ch,char *set);


int testNiveau(char *chaine);

#endif // VERIF_H
