/*******************************************************************
                              CALCMAX.C
        Fonction de calcul de l'indice du maximum dans un tableau
*******************************************************************/
#include "CalcMax.h"
#include "string.h"
#include <stdio.h>

/**
*   Retourne l'indice du plus grand élément d'un tableau
*/
short int CalcIndiceMax ( double    * TabVal ,
                          short int   NbElts )
{
    double valeurMax = TabVal[0];
    short indiceValMax = 0;
    short i;

    for (i=1; i<NbElts; i++)
        if (valeurMax < TabVal[i])
        {
            indiceValMax = i;
            valeurMax=TabVal[i];
        }

    return indiceValMax ;
}

/**
*   Affiche le contenu d'un tableau dans la console
*/
void AfficheTab ( double    * TabVal ,
                  short int   NbElts )
{
    short i;
    printf(" \r\n[ ");
    if(NbElts<1)
         printf(" tableau vide ! ");
    else{
        NbElts = NbElts-1;
        for (i=0; i<NbElts; i++)
           printf("%lf, ",TabVal[i]);
        printf("%lf ",TabVal[i]);
    }
    printf("] \r\n");
}

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
