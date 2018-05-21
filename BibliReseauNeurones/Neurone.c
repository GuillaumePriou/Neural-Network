/*******************************************************************
                              NEURONE.C
                 Definition des types de neurones
              et des fonctions de gestion associées
*******************************************************************/

T_ERREUR InitNeurone ( short int               siNbDendrites               ,
                       REEL                  * tablfPoids                  ,
                       T_FONCTION_ACTIVATION * Fonction_Activation         ,
                       T_FONCTION_ACTIVATION * Fonction_Derivee_Activation ,
                       T_NEURONE             * pNeurone                    )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR DesinitNeurone ( T_NEURONE * pNeurone )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR AfficheNeurone ( T_NEURONE LeNeurone )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR SauveFicTexteNeurone ( T_NEURONE   LeNeurone ,
                                char      * szNomFic  ,
                                char      * szTexte   )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR SauveFicBinaireNeurone ( T_NEURONE   LeNeurone    ,
                                  char      * szNomFic     ,
                                  long int    liCleMagique )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR ChargeFicBinaireNeurone ( T_NEURONE * pNeurone     ,
                                   char      * szNomFic     ,
                                   long int    liCleMagique )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR CalcPredictionNeurone ( REEL      * tablfX        ,
                                 short int   siNbElts      ,
                                 T_NEURONE   LeNeurone     ,
                                 REEL      * plfPrediction )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
