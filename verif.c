#include "verif.h"

int verifierExpression(char *chaine)
{

    return verifierSymboles(chaine)&&verifierParentheses(chaine)&&verifierPosOperateurs(chaine)&&verifierFonction(chaine);
}

int nbOccurrencesMot(char *mot,char *phrase)
{
    int nb= 0;
    char *occ=NULL;

    do
    {
        occ=strstr(phrase, mot);
        if(occ!=NULL)
        {
            nb++;

        }
        else
        {
            break;
        }
        phrase = occ + strlen(mot);
    }while(occ!=NULL);




    return nb;
}

int testNiveau(char *chaine)
{
    return 3*(nbOccurrencesMot("exp(",chaine)+nbOccurrencesMot("sin(",chaine)+nbOccurrencesMot("cos(",chaine)+nbOccurrencesMot("tan(",chaine));
}

int verifierParentheses(char *chaine)
{
    int eq=0,i,t=strlen(chaine);

    for(i=0;i<t;i++)
    {
      if(chaine[i]=='(')
      {
          eq++;
      }
      else if(chaine[i]==')')
      {
         eq--;
      }

      if(eq<0)
      {
          printf("SyntaxError:Parentheses mal placees\n");
          return 0;
      }
    }

    if(eq!=0)
    {
        printf("SyntaxError:Parentheses mal placees\n");
        return 0;
    }
    else
    {
        return 1;
    }
}

int verifierFonction(char *chaine)
{
    int i=0,compteur=0,t=strlen(chaine);

    for(i=0;i<t;i++)
    {

      if(isdigit(chaine[i])==0 && in(chaine[i],",^+*/-()")==0)
      {
          compteur++;

      }

    }



    if(compteur!=testNiveau(chaine))/// Si le nombre  de caractere alphabetique ne correspond pas au tiers du nombre de fonctions
    {
        printf("SyntaxError:Fonctions mal employees ou presence de caracteres non autorises dans la chaine.\n");
        return 0;
    }

    else
    {
        return 1;
    }
}

int verifierSymboles(char *chaine)
{
    int i,t=strlen(chaine);
    char set[]="+-*,/()^expsincota";

    for(i=0;i<t;i++)
    {
        if(isdigit(chaine[i])==0)
        {
           if(in(chaine[i],set)==0)
           {
               printf("SyntaxError:Cararctere non autorise dans l'expression\n");
               return 0;
           }
        }

        if(isalpha(chaine[i]==0))
        {
            printf("SyntaxError:Cararctere non autorise dans l'expression\n");
            return 0;
        }
    }
    return 1;


}

int in(char ch,char *set)
{//Cette fonction doit verifier que l'élément ch est dans set

    int i,t=strlen(set);

    //printf("Longueur de set:%d",t);
    for(i=0;i<t;i++)
    {
        if(set[i]==ch)
        {
            return 1;
        }

    }

    return 0;

}

int verifierPosOperateurs(char *chaine)
{
    /** le - et le + ne peuvent etre à la fin d'une expression ie
     *  "(7+8)*14-" n'est pas autorisé*/
    /** le - et le + ne peuvent etre suivi de /, ni de *,ni de ^,ni de )
        ni meme de + ou - */

    /** La virgule , doit etre encadrée par deux chiffres
     * Mais on ne doit pas pouvoir écrire 78,889,1
     * */


    int i,t=strlen(chaine),j;
    for(i=0;i<t;i++)
    {
        if(chaine[i]=='-'||chaine[i]=='+')
        {
            if(chaine[i+1]=='\0'||chaine[i+1]=='/'||chaine[i+1]=='*'||chaine[i+1]=='^'||chaine[i+1]==')'||chaine[i+1]=='+'||chaine[i+1]=='-')
            {
                printf("SyntaxError:Operateur mal place\n");
                return 0;
            }

            else if(i==0)
            {
                printf("SyntaxError:Operateur mal place\n");
                return 0;
            }

        }

        else if(chaine[i]=='(')
        {
          if(chaine[i+1]=='+' || chaine[i+1]=='*' || chaine[i+1]=='/')
          {
             printf("SyntaxError: operateur mal place");
             return 0;
          }

          else if(chaine[i]=='(')
          {
            if(chaine[i+1]==')')
            {
               printf("SyntaxError: Mettez quelque chose dans la parenthese.");
               return 0;
            }
          }
        }
        else if(chaine[i]==')')
        {
          if(chaine[i+1]=='(')
          {
             printf("SyntaxError: ()() ne signifie pas multiplication ici.");
             return 0;
          }

         if(in(chaine[i+1],"+-*/)^")==0 && chaine[i+1]!='\0')
          {
             printf("SyntaxError: utiliser * pour le produit.");
             return 0;
          }


        }


        else if(chaine[i]=='*')
        {
          if(chaine[i+1]=='/'||chaine[i+1]=='+'||chaine[i+1]=='*'||chaine[i+1]=='-'||chaine[i+1]=='^')
          {
              printf("SyntaxError:Operateur * mal place\n");
              return 0;
          }
          else if(i==0)
          {
              printf("SyntaxError:Operateur * mal place\n");
              return 0;
          }
        }

        else if(chaine[i]=='/')
        {
            if(chaine[i+1]=='/'||chaine[i+1]=='+'||chaine[i+1]=='*'||chaine[i+1]=='^'||chaine[i+1]=='-')
            {
                printf("SyntaxError:Operateur / mal place\n");
                return 0;
            }

            else if(i==0)
            {
                printf("SyntaxError:Operateur / mal place\n");
                return 0;
            }
        }

        else if(chaine[i]=='^')
        {
            if(chaine[i+1]=='/'||chaine[i+1]=='+'||chaine[i+1]=='*'||chaine[i+1]=='^'||chaine[i+1]=='^'||chaine[i+1]=='-')
            {
                printf("SyntaxError:Operateur ^ mal place\n");
                return 0;
            }

            else if(i==0)
            {
                printf("SyntaxError:Operateur ^ mal place\n");
                return 0;
            }
        }

        else if(chaine[i]==',')
        {
            if(i==0)
            {//pas de virgule en début d'espression
                return 0;
                printf("SyntaxError:Virgule  mal placee: en debut d'expression\n");
            }

            else if(chaine[i+1]=='\0')
            {// pas de virgule en fin d'expression
                printf("SyntaxError:Virgule  mal placee: en fin d'expression\n");
                return 0;
            }

            else if(isdigit(chaine[i-1])==0||isdigit(chaine[i+1])==0)
            {//la virgule doit etre encadrée par des chiffres

                printf("SyntaxError:Virgule  mal placee.\n");
                return 0;
            }

            else
            {
                j=i+1;

                while(isdigit(chaine[j])==1)
                {// tant qu'on rencontre de chiffres apres la virgule on avance
                    j++;
                }

                if(chaine[j]==',')
                {//si le premier caractere qui suit les chiffres est une virgule
                    printf("SyntaxError:Virgule  mal placee.\n");
                    return 0;
                }

            }


        }


    }

    return 1;


}
