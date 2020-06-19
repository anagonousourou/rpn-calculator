#include "calcul.h"
#include "pilenpi.h"
#include "verif.h"
#include "pilenpi.h"




Opera placerOperateur(Opera lun,char c)
{
   lun.operateur=c;
   lun.type=0;

   return lun;
}



void creerDebExpr(char *chaine,char *substr,int fin)
{
    int i=0;


        for(i=0;i<fin;i++)
        {
            substr[i]=chaine[i];
        }
        substr[i]='\0';


}

void creerFinExpr(char *chaine,char *substr,int deb)
{
    int i=0,y=0,t=strlen(chaine);


        for(i=deb;i<t;i++)
        {

            substr[y]=chaine[i];
            y++;
        }
        substr[y]='\0';


}

void normaliser(char *chaine)
{
    int i=0;
    while(chaine[i]!='\0')
    {
       if(chaine[i]=='.')
       {
           chaine[i]=',';
       }
       i++;
    }
}


double evalGeneral(char *chaine)
{
    Opera *otmp=NULL;
    Opera *pt=NULL;
    char fonction[10];
    char subexpr[TAILLE];
    char newexpr[TAILLE];
    char finexpr[TAILLE];
    char debexpr[TAILLE];
    int comptbracket;
    int taille,i,j,t=strlen(chaine),k;
    double tmp=0;
   if(testNiveau(chaine)==0)
   {
           otmp=collecte(chaine,&taille);
           pt=transformation(otmp,taille);

           free(otmp);
           tmp=evaluerExpression(pt);
           supprimerPileNpi(pt);
           return tmp;
   }

   else
   {

       for(i=0;i<t;i++)
       {

           if(chaine[i]=='e'||chaine[i]=='s'||chaine[i]=='t'||chaine[i]=='c')
           {

               j=0;
               k=i;
               while(chaine[i]!='(')
               {
                 fonction[j]=chaine[i];
                 j++;
                 i++;
               }

               fonction[j]='\0';

               j=0;
               comptbracket=0;

               do
               {
                   if(chaine[i]=='(')
                   {
                       comptbracket++;
                   }

                   else if(chaine[i]==')')
                   {
                       comptbracket--;
                   }

                   subexpr[j]=chaine[i];
                   i++;
                   j++;


               }while(comptbracket!=0);
               subexpr[j]='\0';

               creerDebExpr(chaine,debexpr,k);

               creerFinExpr(chaine,finexpr,i);



               sprintf(newexpr,"(%s(%lf)%s)",debexpr,appliquerFonction(fonction,evalGeneral(subexpr)),finexpr);

               normaliser(newexpr);


               return evalGeneral(newexpr);



           }

       }

       return 0;

}
}


int estPrioritaire(char a,char b)
{//cette fonction renvoie 1 si l'operateur a est plus prioritaire que b et 0 dans le
    //cas contraire

    if(a=='-'&& b=='-')
    {
        return 1;
    }

    else if(a=='-'&& b=='+')
    {//☻
        return 1;
    }

    else if(a=='+'|| a=='-')
    {
        return 0;
    }
    else if(a=='*' && (b=='-'||b=='+'))
    {
       return 1;
    }

    else if(a=='^')
    {
        return 1;
    }

    else if(a=='/' && b!='^')
    {
        return 1;
    }

    return 0;


}

Opera placerOperande(Opera lun,double nb)
{
    lun.operande=nb;
    lun.type=1;

    return lun;

}

int remplirTableau(Opera lun[], int taille)
{
    char str[20];
    char set[]="+-*/)(^";
    int i=0;

   do
    {
        printf(">Votre entree:");
        scanf("%s",str);
        //printf("appartenance:%d\n",in(str[0],set));
        //printf("%s\n",str);


        if(strcmp(str,"arret")==0)
        {
            return i;
        }


        else if(strlen(str)==1 && in(str[0],set)==1)
        {

            //printf("Operateur!!\n");
           lun[i]=placerOperateur(lun[i],str[0]);
        }

        else
        {

            lun[i]=placerOperande(lun[i],atof(str));
            //printf("Operande!!\n");

            //printf("OK-2");
        }
        i++;

    }while(i<taille);

    return i;
}

void afficherTableau(Opera *lun,int taille)
{
    int i;
    for(i=0;i<taille;i++)
    {
        if(lun[i].type==0)
        {
            printf("%c",lun[i].operateur);
        }
        else if(lun[i].type==1)
        {
            printf("%.2lf ",lun[i].operande);
        }
    }

}

Opera *transformation(Opera lun[],int taille)
{
    Opera *result=creerPileNpi();

    OpPile *pile=creerPile();

    Opera tmp;
    char a;
    int i;


    for(i=0;i<taille;i++)
    {
        if(lun[i].type==OPERANDE)
        {
            empilerPileNpi(result,lun[i]);

        }

        else if(lun[i].type==OPERATEUR && lun[i].operateur=='(')
        {
           empilerOpPile(pile,'(');

        }

        else if(lun[i].type==OPERATEUR && lun[i].operateur!=')')
        {
            if(pile->suiv==NULL)
            {
                empilerOpPile(pile,lun[i].operateur);

            }

            else if(estPrioritaire(pile->suiv->op,lun[i].operateur)==1)
            {//si l'operateur de la pileOp  est plus prioritaire que le nouveau

                do
                {

                    tmp=placerOperateur(tmp,depilerOpPile(pile));

                    empilerPileNpi(result,tmp);
                }
                while( pile->suiv !=NULL && estPrioritaire(pile->suiv->op,lun[i].operateur)==1);
                empilerOpPile(pile,lun[i].operateur);

            }

            else if(estPrioritaire(pile->suiv->op,lun[i].operateur)==0)
            {
                empilerOpPile(pile,lun[i].operateur);
            }
        }

        else if(lun[i].type==OPERATEUR && lun[i].operateur==')')
        {
            while(pile->suiv->op!='(')
            {
                a=depilerOpPile(pile);
                tmp=placerOperateur(tmp,a);
                empilerPileNpi(result,tmp);
            }

            if(pile->suiv->op=='(')
            {
                depilerOpPile(pile);
                //printf("verif %d:%c\n",i,lun[i].operateur);


            }
        }

    }

    while(pile->suiv!=NULL)
    {
        a=depilerOpPile(pile);
        //printf("Operateur:%c\n",a);
        tmp=placerOperateur(tmp,a);

        empilerPileNpi(result,tmp);


    }

    supprimerOpPile(pile);

    return result;
}

double evaluerExpression(Opera *deb)
{
    Opera *a,*b,*sent=deb->suiv;
    double tmp;
    if(deb->suiv==NULL)
    {
        printf("ValueError:il n'y a rien a evaluer\n");
        return 0;
    }
    else if(longueurPileNpi(deb)==1)
    {
        return deb->suiv->operande;
    }
    else
    {
       while(sent->type!=OPERATEUR)
       {
           a=b;
           b=sent;
           sent=sent->suiv;
       }
       tmp=calculer(a->operande,b->operande,sent->operateur);
       supprimerDePileNpi(deb,a);
       supprimerDePileNpi(deb,b);
       sent->operande=tmp;
       sent->type=OPERANDE;
       return evaluerExpression(deb);
    }
}

double appliquerFonction(char *func,double nb)
{
   if(strcmp(func,"sin")==0)
   {
       return sin(nb);
   }
   else if(strcmp(func,"cos")==0)
   {
       return cos(nb);
   }
   else if(strcmp(func,"exp")==0)
   {
       return exp(nb);
   }
   else if(strcmp(func,"tan")==0)
   {


        return tan(nb);

   }


       printf("Erreur lors de l'application de fonction\n");
       return 0;



}

double calculer(double a,double b,char c)
{
    if(c=='-')
    {
        return a-b;
    }
    else if(c=='+')
    {
        return a+b;
    }

    else if(c=='/')
    {
        if(b==0)
        {
            printf("ZeroDivisionError:La division par zero n'est pas possible.\n");
            printf("Le résultat qui sera affiche ne doit pas etre pris en compte.\n");
            return -1;
        }
        else
        {
           return a/b;
        }

    }

    else if(c=='*')
    {
        return a*b;
    }

    else if(c=='^')
    {
        if(b==0.5 && a<0)
        {
            printf(":La racine carre d'un nombre negatif n'est pas definie.\n");
            printf("Le résultat qui sera affiche ne doit pas etre pris en compte.\n");
            return 0;
        }
        else
        {
           return pow(a,b);
        }

    }

    else
    {
        printf("Erreur dans la fonction calculer\n");
        exit(0);
    }

}

Opera *collecte(char expr[],int *taille)
{
    int t=strlen(expr),i=0,j=0,k=0;


    char chaine[TAILLE];//pour collecter un nombre

    Opera *resp=(Opera*)malloc(sizeof(Opera)*t);
    while(i<t)
    {


        if(in(expr[i],"+-*/)(^")==1)
        {
            resp[j]=placerOperateur(resp[j],expr[i]);
            j++;
            i++;

            if(expr[i-1]=='(' && expr[i]=='-')
            {
               k=0;
               chaine[k]='-';
               i++;
               k++;

               while(isdigit(expr[i])||expr[i]==',')
               {
                   if(expr[i]==',')
                   {
                       chaine[k]='.';
                       k++;
                       i++;

                   }
                   else
                   {
                       chaine[k]=expr[i];
                       k++;
                       i++;
                   }

               }

               chaine[k]='\0';
               resp[j]=placerOperande(resp[j],atof(chaine));
               j++;

            }

        }
        else if(isdigit(expr[i]))
        {

            k=0;
            while(isdigit(expr[i])||expr[i]==',')
            {
                if(expr[i]==',')
                {
                    chaine[k]='.';
                    k++;
                    i++;

                }
                else
                {
                    chaine[k]=expr[i];
                    k++;
                    i++;
                }

            }
           chaine[k]='\0';
           resp[j]=placerOperande(resp[j],atof(chaine));
           j++;

        }
        else{
            printf("Why in else \n");
        }

    }  
    (*taille)=j;
    return resp;
}
