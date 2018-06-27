/******************************************************
                    FONCTIONSCOUT.C
              Fonctions de cout utilisees
******************************************************/
#include "FonctionCout.h"
#include "constantes.h"

T_ERREUR FonctionCoutLogLoss ( REEL      * tablfValeursVraies   ,
                               REEL      * tablfValeursEstimees ,
                               short int   siNbElts             ,
                               REEL      * plfCout              )
{
    /* constante introduite pour eviter des valeurs trop elevees du logarithme en valeur absolue */
    #define SEUIL_MIN_LOGLOSS 1.0e-200
    T_ERREUR Err = PAS_D_ERREUR;
    short int siCompteur = 0;

    while ( ( tablfValeursVraies[siCompteur] == ZERO ) && ( siCompteur < siNbElts ) )
        siCompteur++ ;

    if ( siCompteur == siNbElts )
        Err = ERREUR_FCOUT_LOGLOSS ;
    else
    {
        if ( tablfValeursEstimees[siCompteur] < SEUIL_MIN_LOGLOSS )
            * plfCout = - log ( SEUIL_MIN_LOGLOSS ) ;
        else
            * plfCout = - log ( tablfValeursEstimees[siCompteur]) ;
    }

    return ( Err ) ;
}

T_ERREUR FonctionCoutLogLossBinaire ( REEL      * plfValeurVraie   ,
                                      REEL      * plfValeurEstimee ,
                                      short int   siParam          ,
                                      REEL      * plfCout          )
{
    /* constante introduite pour eviter des valeurs trop elevees du logarithme en valeur absolue */
    #define SEUIL_MIN_LOGLOSS 1.0e-200
    T_ERREUR Err = PAS_D_ERREUR ;

    if ( (* plfValeurVraie) == ZERO )
        (* plfCout) = 1.0 - (*plfValeurEstimee) ;
    else
        (* plfCout) = (*plfValeurEstimee) ;

    if ( (* plfCout) < SEUIL_MIN_LOGLOSS )
        (* plfCout) = - log ( SEUIL_MIN_LOGLOSS ) ;
    else
        (* plfCout) = - log ( * plfCout ) ;

    return ( Err ) ;
}

T_ERREUR FonctionCoutErrQuadra ( REEL      * tablfValeursVraies   ,
                                 REEL      * tablfValeursEstimees ,
                                 short int   siNbElts             ,
                                 REEL      * plfCout              )
{
    T_ERREUR Err = PAS_D_ERREUR ;
    REEL lfInter ;
    short int siCompteur ;

    lfInter = tablfValeursVraies[0] - tablfValeursEstimees[0] ;
    * plfCout = lfInter * lfInter ;

    for ( siCompteur = 1 ; siCompteur < siNbElts ; siCompteur++ )
    {
        lfInter = tablfValeursVraies[siCompteur] - tablfValeursEstimees[siCompteur] ;
        (* plfCout) += lfInter * lfInter ;
    }

    return ( Err ) ;
}

/******************************************************
                    FIN DU COMPOSANT
******************************************************/
