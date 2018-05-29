/*******************************************************************
                              COUCHENEURONE.C
                Definition des types "couches de neurones"
                   et des fonctions de gestion associées
*******************************************************************/
#include "CoucheNeurone.h"
#include <stdlib.h>
#include <string.h>


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
    int i,j;

    (*pCoucheNeurones).typeCoucheNeurones = typeCoucheNeurones;
     strcpy( (*pCoucheNeurones).szDescription, pszDescription);
    (*pCoucheNeurones).pCoucheNeuronesAmont = pCoucheNeuronesAmont;
    (*pCoucheNeurones).F_ActivationVectorielle = F_ActivationVectorielle;
    (*pCoucheNeurones).F_Derivee_ActivationVectorielle = F_Derivee_ActivationVectorielle;
    (*pCoucheNeurones).siNbNeurones = siNbNeurones;
    (*pCoucheNeurones).siNbDendritesParNeurone = siNbDendritesParNeurone;

    // Initialisation des neurones
    for (i=0; i<siNbNeurones; i++)
    {
        InitNeurone((*pCoucheNeurones).siNbDendritesParNeurone,
                     mat2DlfPoids[i],
                     Fonction_ActivationNeurone,
                     Fonction_Derivee_ActivationNeurone,
                    &(*pCoucheNeurones).pNeurones[i]);

        for (j=0; j<siNbDendritesParNeurone; j++)
        {
            (*pCoucheNeurones).pNeurones[i].tablfPoids[j] = mat2DlfPoids[i][j];

        }
    }

    // Allocation de plfOutputSample
    (*pCoucheNeurones).plfOutputSample = malloc(siNbNeurones*sizeof(REEL));

    if ((*pCoucheNeurones).plfOutputSample == NULL) // En cas d'echec, annuler toute l'init
    {
        for (i=0; i<siNbNeurones; i++)
            DesinitNeurone(&(*pCoucheNeurones).pNeurones[i]);

        return ERREUR_ALLOCATION_MEMOIRE_COUCHE;
    }

    // Allocationn de plfErreurDeltaSample
    (*pCoucheNeurones).plfErreurDeltaSample = malloc(siNbNeurones*sizeof(REEL));

    if ((*pCoucheNeurones).plfErreurDeltaSample == NULL) // En cas d'echec, annuler toute l'init
    {
        free((*pCoucheNeurones).plfOutputSample);
        for (i=0; i<siNbNeurones; i++)
            DesinitNeurone(&(*pCoucheNeurones).pNeurones[i]);

        return ERREUR_ALLOCATION_MEMOIRE_COUCHE;
    }


    return PAS_D_ERREUR ;
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
