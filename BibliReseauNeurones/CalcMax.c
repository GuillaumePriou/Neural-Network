/*******************************************************************
                              CALCMAX.C
        Fonction de calcul de l'indice du maximum dans un tableau
*******************************************************************/
#include "CalcMax.h"

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

void AfficheTab ( double    * TabVal ,
                  short int   NbElts )
{
}

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
