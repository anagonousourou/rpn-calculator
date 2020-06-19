#include "pilenpi.h"

Opera* creerPileNpi()
{
    Opera *pt=(Opera*)malloc(sizeof(Opera));

    pt->suiv=NULL;

    return pt;
}

void empilerPileNpi(Opera *deb,Opera elt)
{
    Opera *tmp=(Opera*)malloc(sizeof(Opera));
    Opera *sent=deb->suiv;

    *tmp=elt;
    tmp->suiv=NULL;

    if(deb->suiv==NULL)
    {
        deb->suiv=tmp;
    }

    else
    {
      while(sent->suiv!=NULL)
      {
          sent=sent->suiv;
      }
      sent->suiv=tmp;
    }

}

void depilerPileNpi(Opera *deb)
{
    Opera *tmp;
   if(deb->suiv==NULL)
   {
       printf("Il n'y rien dans la pile");
   }

   else
   {
       tmp=deb->suiv;

       deb->suiv=tmp->suiv;
       free(tmp);

   }
}

void supprimerPileNpi(Opera *deb)
{
    Opera *tmp;
    while(deb->suiv!=NULL)
    {
       tmp=deb->suiv;
       deb->suiv=tmp->suiv;
       free(tmp);
    }

    free(deb);
}

int longueurPileNpi(Opera *deb)
{
   int compt=0;
   Opera *sent=deb->suiv;

   while(sent!=NULL)
   {
       sent=sent->suiv;
       compt++;
   }

   return compt;

}

void afficherPileNpi(Opera *deb)
{
    Opera *sent=deb->suiv;
    printf("Affichage de la pile Npi:");
    while(sent!=NULL)
    {
        if(sent->type==OPERATEUR)
        {
            printf("%c ",sent->operateur);
        }

        else if(sent->type==OPERANDE)
        {
            printf("%.3lf ",sent->operande);
        }
       sent=sent->suiv;
    }
}

void supprimerDePileNpi(Opera *deb,Opera *elt)
{
    Opera *sent=deb->suiv;

    if(sent==elt)
    {
        deb->suiv=sent->suiv;
        free(elt);
    }
    else
    {
        while(sent->suiv!=elt)
        {
           sent=sent->suiv;
        }

        sent->suiv=elt->suiv;
        free(elt);
    }

}

