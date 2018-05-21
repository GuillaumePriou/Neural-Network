/*******************************************************************
                              COUCHENEURONE.C
                Definition des types "couches de neurones"
                   et des fonctions de gestion associées
*******************************************************************/

T_ERREUR InitCoucheNeurone ( T_TYPE_COUCHE_NEURONES              typeCoucheNeurones                 ,
                             char                              * pszDescription                     ,
                             T_COUCHE_NEURONES                 * pCoucheNeuronesAmont               ,
                             T_FONCTION_ACTIVATION_VECTORIELLE * F_ActivationVectorielle            ,
                             T_FONCTION_ACTIVATION_VECTORIELLE * F_Derivee_ActivationVectorielle    ,
                             short int                           siNbNeurones                       ,
                             short int                           siNbDendritesParNeurone            ,
                             REEL                             ** mat2DlfPoids                       ,
                             T_FONCTION_ACTIVATION             * Fonction_ActivationNeurone         ,
                             T_FONCTION_ACTIVATION             * Fonction_Derivee_ActivationNeurone ,
                             T_COUCHE_NEURONES                 * pCoucheNeurones                    )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR DesinitCoucheNeurone ( T_COUCHE_NEURONES * pCoucheNeurones )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR AfficheCoucheNeurone ( T_COUCHE_NEURONES LaCoucheNeurones ,
                                short int         siIndiceNeurone  ,
                                short int         siIndiceCouche   )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR SauveFicTexteCoucheNeurones ( T_COUCHE_NEURONES   LaCoucheNeurones ,
                                       char              * szNomFic         ,
                                       char              * szTexte          )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR SauveNeuroneDansFicTexte ( FILE      * pFic      ,
                                    T_NEURONE   LeNeurone )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR SauveFicBinaireCoucheNeurones ( T_COUCHE_NEURONES   LaCoucheNeurones ,
                                         char              * szNomFic         ,
                                         long int            liCleMagique     )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR ChargeFicBinaireCoucheNeurones ( T_COUCHE_NEURONES * LaCoucheNeurones ,
                                          char              * szNomFic         ,
                                          long int            liCleMagique     )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR CalcPredictionCoucheNeurones ( T_COUCHE_NEURONES * pCoucheNeurones )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
