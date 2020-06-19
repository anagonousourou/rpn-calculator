#ifndef CALCUL_H
#define CALCUL_H

#define TAILLE 10000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "pileoperateur.h"
#include "pilenpi.h"
Opera placerOperateur(Opera lun,char c);
Opera placerOperande(Opera lun,double nb);
int remplirTableau(Opera lun[], int taille);
void afficherTableau(Opera *lun,int taille);
void lecture(char *chaine);
Opera *transformation(Opera lun[],int taille);
double evaluerExpression(Opera *deb);
double evalGeneral(char *chaine);///
double calculer(double a,double b,char c);
Opera *collecte(char expr[],int *taille);
void creerDebExpr(char *chaine,char *substr,int fin);
void creerFinExpr(char *chaine,char *substr,int deb);
double appliquerFonction(char *func, double nb);
#endif // CALCUL_H
