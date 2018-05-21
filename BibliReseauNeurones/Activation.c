/*******************************************************************
                              ACTIVATION.c
                 Definition des fonctions d'activation
                       scalaires et vectorielles
                 utilisees par les reseaux de neurones
*******************************************************************/

#include "Activation.h"

REEL CalcLogistique (REEL lfX)
{
    return 0 ;
}

REEL CalcDeriveeLogistiqueViaValLogistique (REEL lfX)
{
    return 0 ;
}

REEL CalcTanHyperbolique (REEL lfX)
{
    return 0 ;
}

REEL CalcDeriveeTanHyperboliqueViaValTanHyperbolique (REEL lfX)
{
    return 0 ;
}

REEL CalcReLU (REEL lfX)
{
    return 0 ;
}

REEL CalcDeriveeReLU (REEL lfX)
{
    return 0 ;
}

REEL CalcIdentite (REEL lfX)
{
    return 0 ;
}

REEL CalcDeriveeIdentite (REEL lfX)
{
    return 0 ;
}

REEL CalcHeavisideZero (REEL lfX)
{
    return 0 ;
}

REEL CalcDeriveeHeavisideZero (REEL lfX)
{
    return 0 ;
}

REEL CalcHeavisideMoinsUn (REEL lfX)
{
    return 0 ;
}

REEL CalcDeriveeHeavisideMoinsUn (REEL lfX)
{
    return 0 ;
}

/***************************************************
         Fonctions d'activation vectorielles
***************************************************/
typedef T_ERREUR T_FONCTION_ACTIVATION_VECTORIELLE ( REEL      * tablfX                   ,
                                                     short int   siNbElts                 ,
                                                     REEL      * tablfResult              ,
                                                     short int   siIndiceDeriveePartielle ) ;

/***************************************************
                 Fonction SoftMax
         sortie comprise entre 0.0 et +1.0
***************************************************/
T_ERREUR CalcSoftMax( REEL      * tablfX                   ,
                      short int   siNbElts                 ,
                      REEL      * tablfResult              ,
                      short int   siIndiceDeriveePartielle ) ;

T_ERREUR CalcDeriveePartielleSoftMaxViaValSoftMax ( REEL      * tablfX                   ,
                                                    short int   siNbElts                 ,
                                                    REEL      * tablfResult              ,
                                                    short int   siIndiceDeriveePartielle ) ;
/***************************************************
                 FIN DU COMPOSANT
***************************************************/
