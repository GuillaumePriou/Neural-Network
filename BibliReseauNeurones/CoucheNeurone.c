/*******************************************************************
                              COUCHENEURONE.C
                Definition des types "couches de neurones"
                   et des fonctions de gestion associ�es
*******************************************************************/
#include "CoucheNeurone.h"

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

    short int i ;
    printf("-----------------------\n");
    printf ("\t Type couche de neurone : %hd\n", LaCoucheNeurones.typeCoucheNeurones) ;
    printf ("\t Description couche de neurone : %s\n", LaCoucheNeurones.szDescription) ;
    printf ("\t %hd neurones ayant %hd dendrites\n", LaCoucheNeurones.siNbNeurones,
                                                LaCoucheNeurones.siNbDendritesParNeurone);
    for (i=0; i<LaCoucheNeurones.siNbNeurones; i++)
    {
        printf ("\t\t Neurone N.%hd : \n", i);
        AfficheNeurone(LaCoucheNeurones.pNeurones[i]) ;
        printf("\n");
    }

    printf("-----------------------------\n");
    for (i=0; i<LaCoucheNeurones.siNbNeurones; i++)
    {
        printf ("\t Sortie du neurone N.%hd : %lf (erreur de %lf)\n",
                                            i,
                                            LaCoucheNeurones.plfOutputSample[i],
                                            LaCoucheNeurones.plfErreurDeltaSample[i]);
    }


    if(LaCoucheNeurones.typeCoucheNeurones == COUCHE_NON_INITIALISEE)
        return ERREUR_TYPE_COUCHE_INCONNU;
    else
        return PAS_D_ERREUR ;
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
