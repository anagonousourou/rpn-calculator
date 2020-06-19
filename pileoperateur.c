#include "pileoperateur.h"

OpPile *creerPile()
{
    OpPile *pt=(OpPile*)malloc(sizeof(OpPile));

    pt->suiv=NULL;

    return pt;

}

void empilerOpPile(OpPile *deb,char c)
{
    OpPile *tmp=(OpPile*)malloc(sizeof(OpPile));

    tmp->op=c;
    tmp->suiv=deb->suiv;
    deb->suiv=tmp;
}

char depilerOpPile(OpPile *deb)
{
    OpPile *pt=deb->suiv;
    char tmp;


    if(pt!=NULL)
    {
        deb->suiv=pt->suiv;
        tmp=pt->op;
        free(pt);
        return tmp;
    }

    else
    {
        printf("Pile vide :Rien à dépiler");
        return '\0';
    }
}

void supprimerOpPile(OpPile *deb)
{
    OpPile *tmp;
    while(deb->suiv!=NULL)
    {
       tmp=deb->suiv;
       deb->suiv=tmp->suiv;
       free(tmp);
    }

    free(deb);
}
