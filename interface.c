#include "interface.h"


void information()
{
    printf("Bienvenue dans la mini-calculatrice\n");
    printf("Tapez aide pour voir l'aide.");

    printf("Entrez arret pour sortir.\n");
}

void aide()
{
    printf("Les operations supportees sont les suivantes:\n");
    printf("-Addition:+\n -Multiplication:*\n -Soustraction:-\n -Division:/ \n -Puissance^\n");

    printf("\n Les nombres negatifs doivent etre entre parenthese ex: (-5)*4\n");
    printf("Vous utiliserez les , pour la virgule\n");

    printf("Les fonctions supportees sont les suivantes:\n");
    printf("-exp():Exponentielle\n -sin():sinus\n -cos():cosinus:\n -tan():tangente\n");
    printf("Les fonctions trigonometriques utilisent le radian.\n");
}

void ligneCommande()
{
    char expr[TAILLE];
    int i=1;

    while(1)
    {

        printf("\nIn[%d]:",i);
        fgets(expr,TAILLE,stdin);
        strtok(expr,"\n");

        if(strcmp(expr,"arret")==0)
        {
            printf("Au revoir!!\n");
            break;
        }

        else if(strcmp(expr,"aide")==0)
        {
            aide();
        }

        else if(verifierExpression(expr)==1)
        {


            printf("\nOut[%d]:%lf\n",i,evalGeneral(expr));

        }
        i++;


    }
}
