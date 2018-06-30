/*******************************************************************
                              COUCHENEURONE.C
                Definition des types "couches de neurones"
                   et des fonctions de gestion associ�es
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
    int cptNeurone = 0;

   /* if(mat2DlfPoids != NULL)
    {
        //for(short i = 0; i<3; i++)
            //for(short j = 0; j<3; j++)
                printf("%lf ", mat2DlfPoids[0][0]);
                printf("%lf ", mat2DlfPoids[0][1]);
                printf("%lf ", mat2DlfPoids[0][2]);
                printf("%lf ", mat2DlfPoids[1][0]);
                printf("%lf ", mat2DlfPoids[1][1]);
                printf("%lf ", mat2DlfPoids[1][2]);
                printf("%lf ", mat2DlfPoids[2][0]);
                printf("%lf ", mat2DlfPoids[2][1]);
                printf("%lf ", mat2DlfPoids[2][2]);
    }
    else
        printf("Matrice null");*/

    // Verifie la coherence des parametres d'initialisation
    if (pCoucheNeurones == NULL)
        return ERREUR_COUCHE_NEURONE_MAL_INITIALISEE;
    if (pszDescription == NULL)
            return ERREUR_AUCUNE_DESCRIPTION_COUCHE_NEURONE;
    if (siNbNeurones <= 0)
        return ERREUR_NB_NEURONES_INSUFFISANT;

    switch (typeCoucheNeurones)
    {
        case COUCHE_ENTREE :    if (   mat2DlfPoids != NULL
                                    || siNbDendritesParNeurone != 0
                                    || Fonction_ActivationNeurone != CalcIdentite
                                    || Fonction_Derivee_ActivationNeurone != CalcDeriveeIdentite)
                                    return ERREUR_COUCHE_NEURONE_MAL_INITIALISEE;
                                break;
        default:    if (mat2DlfPoids == NULL)
                        return ERREUR_COUCHE_NEURONE_MAL_INITIALISEE;
                    break;
    }


    // Initialisation des attributs de la couche (hors neurones) (etape 2)
    (*pCoucheNeurones).typeCoucheNeurones = typeCoucheNeurones;
     strcpy( (*pCoucheNeurones).szDescription, pszDescription);
    (*pCoucheNeurones).pCoucheNeuronesAmont = pCoucheNeuronesAmont;
    (*pCoucheNeurones).F_ActivationVectorielle = F_ActivationVectorielle;
    (*pCoucheNeurones).F_Derivee_ActivationVectorielle = F_Derivee_ActivationVectorielle;
    (*pCoucheNeurones).siNbNeurones = siNbNeurones;
    (*pCoucheNeurones).siNbDendritesParNeurone = siNbDendritesParNeurone;

    // Allocation memoire pour les neurones (etape 3)
    (*pCoucheNeurones).pNeurones = malloc(siNbNeurones*sizeof(T_NEURONE));

    // Initialisation des neurones (dans le cas ou ce n'est pas une couche d'entree)
    //(etape 4)

    // Initialisation du neurone de biais (exception : couche de sortie)
    if (typeCoucheNeurones != COUCHE_SORTIE)
    {
        InitNeurone (NEURONE_DE_BIAIS, 0, NULL, CalcIdentite, CalcDeriveeIdentite, &((*pCoucheNeurones).pNeurones[cptNeurone]));
        cptNeurone++;
    }

    while (cptNeurone<siNbNeurones)
    {
        switch (typeCoucheNeurones)
        {
            case COUCHE_ENTREE: //  Initialisation des neurones de la couche d'entree

                                    InitNeurone( NEURONE_D_ENTREE,
                                                 0,
                                                 NULL,
                                                 CalcIdentite,
                                                 CalcDeriveeIdentite,
                                                &((*pCoucheNeurones).pNeurones[cptNeurone]));
                                break;

            case COUCHE_CACHEE: //  Initialisation des neurones de la couche cachee
                                    InitNeurone( NEURONE_CACHE,
                                                 (*pCoucheNeurones).siNbDendritesParNeurone,
                                                 mat2DlfPoids[cptNeurone],
                                                 Fonction_ActivationNeurone,
                                                 Fonction_Derivee_ActivationNeurone,
                                                &((*pCoucheNeurones).pNeurones[cptNeurone]));
                                break;
            case COUCHE_SORTIE: //  Initialisation des neurones de la couche de sortie

                                    InitNeurone( NEURONE_DE_SORTIE,
                                                 (*pCoucheNeurones).siNbDendritesParNeurone,
                                                 mat2DlfPoids[cptNeurone],
                                                 Fonction_ActivationNeurone,
                                                 Fonction_Derivee_ActivationNeurone,
                                                &((*pCoucheNeurones).pNeurones[cptNeurone]));
                                break;
            default:    return ERREUR_TYPE_COUCHE_INCONNU ;
                            break;
        }

        cptNeurone++;
    }

    // Allocation de plfOutputSample (etape 5)
    (*pCoucheNeurones).plfOutputSample = malloc(siNbNeurones*sizeof(REEL));

    if ((*pCoucheNeurones).plfOutputSample == NULL) // En cas d'echec, annuler toute l'init
    {
        for (cptNeurone=0; cptNeurone<siNbNeurones; cptNeurone++)
            DesinitNeurone(&(*pCoucheNeurones).pNeurones[cptNeurone]);

        free ((*pCoucheNeurones).pNeurones);
        return ERREUR_ALLOCATION_MEMOIRE_COUCHE;
    }

    // Allocation de plfErreurDeltaSample (etape 6)
    (*pCoucheNeurones).plfErreurDeltaSample = malloc(siNbNeurones*sizeof(REEL));

    if ((*pCoucheNeurones).plfErreurDeltaSample == NULL) // En cas d'echec, annuler toute l'init
    {
        for (cptNeurone=0; cptNeurone<siNbNeurones; cptNeurone++)
            DesinitNeurone(&(*pCoucheNeurones).pNeurones[cptNeurone]);

        free ((*pCoucheNeurones).pNeurones);
        free((*pCoucheNeurones).plfOutputSample);

        return ERREUR_ALLOCATION_MEMOIRE_COUCHE;
    }


    return PAS_D_ERREUR ;
}

T_ERREUR DesinitCoucheNeurone ( T_COUCHE_NEURONES * pCoucheNeurones )
{
    short i;

    // Si la couche est bizarre, revoie une erreur
    if ((*pCoucheNeurones).typeCoucheNeurones == COUCHE_NON_INITIALISEE)
        return ERREUR_TYPE_COUCHE_INCONNU ;

    for (i=0; i<(*pCoucheNeurones).siNbNeurones; i++)
        DesinitNeurone(&((*pCoucheNeurones).pNeurones[i]));

    // Mettre a zero toutes les variables
    (*pCoucheNeurones).typeCoucheNeurones = COUCHE_NON_INITIALISEE;
    strcpy((*pCoucheNeurones).szDescription, "Couche desinitialisee");
    (*pCoucheNeurones).pCoucheNeuronesAmont = NULL;
    (*pCoucheNeurones).F_ActivationVectorielle = NULL;
    (*pCoucheNeurones).F_Derivee_ActivationVectorielle = NULL;
    (*pCoucheNeurones).siNbNeurones = 0 ;
    (*pCoucheNeurones).siNbDendritesParNeurone = 0 ;

    // Desallouer les tableaux dynamiquement alloues
    if ((*pCoucheNeurones).pNeurones != NULL)		free((*pCoucheNeurones).pNeurones);
    if ((*pCoucheNeurones).plfOutputSample != NULL)		free((*pCoucheNeurones).plfOutputSample);
    if ((*pCoucheNeurones).plfErreurDeltaSample != NULL)		free((*pCoucheNeurones).plfErreurDeltaSample);

    (*pCoucheNeurones).pNeurones = NULL;
    (*pCoucheNeurones).plfOutputSample = NULL;
    (*pCoucheNeurones).plfErreurDeltaSample = NULL ;

    return PAS_D_ERREUR ;
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
    int i;

    if(pCoucheNeurones->typeCoucheNeurones != COUCHE_ENTREE)
    {
        if(pCoucheNeurones->pCoucheNeuronesAmont->siNbNeurones == pCoucheNeurones->siNbDendritesParNeurone)
        {
            for(i=0; i<pCoucheNeurones->siNbNeurones;i++)
            {
                CalcPredictionNeurone(pCoucheNeurones->pCoucheNeuronesAmont->plfOutputSample,
                                      pCoucheNeurones->pCoucheNeuronesAmont->siNbNeurones,
                                      &(pCoucheNeurones->pNeurones[i]),
                                      &(pCoucheNeurones->plfOutputSample[i]));
            }

            if(pCoucheNeurones->typeCoucheNeurones == COUCHE_SORTIE)
                pCoucheNeurones->F_ActivationVectorielle(pCoucheNeurones->pCoucheNeuronesAmont->plfOutputSample,
                                                         pCoucheNeurones->siNbNeurones,
                                                         pCoucheNeurones->plfOutputSample,
                                                         0);
        }
        else
        {
            return ERREUR_NB_DENDRITES;
        }

        AfficheCoucheNeurone(*pCoucheNeurones, 0,0 );

    }

    return PAS_D_ERREUR ;
}

short CmpCoucheNeurone ( T_COUCHE_NEURONES   coucheA ,
                         T_COUCHE_NEURONES   coucheB )
{
    if( coucheA.typeCoucheNeurones != coucheB.typeCoucheNeurones
        || strcmp(coucheA.szDescription, coucheB.szDescription)
        //|| coucheA.pCoucheNeuronesAmont != coucheB.pCoucheNeuronesAmont
        || coucheA.F_ActivationVectorielle != coucheB.F_ActivationVectorielle
        || coucheA.F_Derivee_ActivationVectorielle != coucheB.F_Derivee_ActivationVectorielle
        || coucheA.siNbNeurones != coucheB.siNbNeurones
        || coucheA.siNbDendritesParNeurone != coucheB.siNbDendritesParNeurone
    )
      return 1;

    int i;
    for (i=0; i<coucheA.siNbNeurones; i++)
        if(CmpNeurone(coucheA.pNeurones[i],coucheB.pNeurones[i]) != 0)
            return 1;
    return 0;
}

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
