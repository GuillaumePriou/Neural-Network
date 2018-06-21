/*******************************************************************
                              ACTIVATION.c
                 Definition des fonctions d'activation
                       scalaires et vectorielles
                 utilisees par les reseaux de neurones
*******************************************************************/

#include "Activation.h"
#include <math.h>

REEL CalcLogistique (REEL lfX)
{
    return (1/(1+exp(-lfX)));
}

REEL CalcDeriveeLogistiqueViaValLogistique (REEL lfX)
{
    return ((lfX)*(1-lfX)) ;
}

REEL CalcTanHyperbolique (REEL lfX)
{
    return tanh(lfX);
    //return ( 2.0 / ( 1.0 + exp(-2.0 * lfX)) - 1.0 ) ;
}

REEL CalcDeriveeTanHyperboliqueViaValTanHyperbolique (REEL lfValTanHyperbolique)
{
    return ( 1.0 - lfValTanHyperbolique * lfValTanHyperbolique );
}

REEL CalcReLU (REEL lfX)
{
    if(lfX>=0)
        return lfX;
    else
        return 0;
}

REEL CalcDeriveeReLU (REEL lfX)
{
    if(lfX>=0)
        return 1;
    else
        return 0;
}

REEL CalcIdentite (REEL lfX)
{
    return lfX ;
}

REEL CalcDeriveeIdentite (REEL lfX)
{
    return 1 ;
}

REEL CalcHeavisideZero (REEL lfX)
{
    return ( lfX > 0.0 ? 1.0 : 0.0 ) ;
}

REEL CalcDeriveeHeavisideZero (REEL lfX)
{
    return ( 0.0 ) ;
}

REEL CalcHeavisideMoinsUn (REEL lfX)
{
    return ( lfX > 0.0 ? 1.0 : -1.0 ) ;
}

REEL CalcDeriveeHeavisideMoinsUn (REEL lfX)
{
    return ( 0.0 ) ;
}

/***************************************************
                 Fonction SoftMax
         sortie comprise entre 0.0 et +1.0
***************************************************/
T_ERREUR CalcSoftMax( REEL      * tablfX                   ,
                      short int   siNbElts                 ,
                      REEL      * tablfResult              ,
                      short int   siIndiceDeriveePartielle )
{
    REEL somme = 0;

    // Calcul de exponentielles pour chaque element
    for(int i = 0; i< siNbElts; i++)
    {
        tablfResult[i] = exp(tablfX[i]);
        somme += tablfResult[i];
    }
    if(somme == 0)
        return ERREUR_DIVISION_ZERO_SOFT_MAX;

    // Division par la somme des exponentielles
    for(int i = 0; i<siNbElts; i++)
    {
        tablfResult[i] /= somme;
    }

    return PAS_D_ERREUR;
}

T_ERREUR CalcDeriveePartielleSoftMaxViaValSoftMax ( REEL      * tablfX                   ,
                                                    short int   siNbElts                 ,
                                                    REEL      * tablfResult              ,
                                                    short int   siIndiceDeriveePartielle )
{
    REEL lfDenom , lfInter ;
    short int siCompteur ;
    T_ERREUR Err = PAS_D_ERREUR ;

    lfInter = exp(tablfX[siIndiceDeriveePartielle]) ;
    lfDenom = 0.0 ;
    for ( siCompteur = 0 ; siCompteur < siNbElts ; siCompteur++ )
    {
        tablfResult[siCompteur] = exp(tablfX[siCompteur]) ;
        lfDenom += tablfResult[siCompteur] ;
    }

    for ( siCompteur = 0 ; siCompteur < siNbElts ; siCompteur++ )
    {
        if ( siIndiceDeriveePartielle == siCompteur )
        {
        tablfResult[siCompteur] /= lfDenom ;
        tablfResult[siCompteur] *= (1.0 - tablfResult[siCompteur]) ;
        }
        else
        {
            tablfResult[siCompteur] *= - lfInter / lfDenom / lfDenom ;
        }
    }

    return ( Err ) ;
}
/***************************************************
                 FIN DU COMPOSANT
***************************************************/
