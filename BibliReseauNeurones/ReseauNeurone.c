/*******************************************************************
                              RESEAUNEURONE.C
Definition des fonctions de gestion des "reseaux de neurones"associées

*******************************************************************/

#include "ReseauNeurone.h"
#include <string.h>
#include <stdlib.h>

T_ERREUR InitReseauNeurone ( T_TYPE_RESEAU_NEURONES                typeReseauNeurones                        ,
                             char                                * pszDescription                            ,
                             REEL                                  lfTauxApprentissage                       ,
                             short int                             siNbCouches                               ,
                             short int                           * tabsiNbNeurones                           ,
                             T_FONCTION_ACTIVATION_VECTORIELLE   * F_ActivationVectorielle                   ,
                             T_FONCTION_ACTIVATION_VECTORIELLE   * F_Derivee_ActivationVectorielle           ,
                             REEL                              *** mat3DlfPoids                              ,
                             T_FONCTION_ACTIVATION               * Fonction_ActivationNeurone_Cache          ,
                             T_FONCTION_ACTIVATION               * Fonction_Derivee_ActivationNeurone_Cache  ,
                             T_FONCTION_ACTIVATION               * Fonction_ActivationNeurone_Sortie         ,
                             T_FONCTION_ACTIVATION               * Fonction_Derivee_ActivationNeurone_Sortie ,
                             unsigned short int                    usiNbLots                                 ,
                             T_RESEAU_NEURONES                   * pReseauNeurones                           )
{

    short int i = 0;
    char str[TAILLE_TEXTE];
    char strCoucheCache[TAILLE_TEXTE] = "couche cachee, indice";

    if (siNbCouches < 2)
        return ERREUR_NB_COUCHES;

    //etape 1 : remplissage des paramètres du reseau neurone

    (*pReseauNeurones).typeReseauNeurones = typeReseauNeurones;
    strcpy((*pReseauNeurones).szDescription, pszDescription);
    (*pReseauNeurones).lfTauxApprentissage = lfTauxApprentissage;
    (*pReseauNeurones).siNbCouches = siNbCouches;
    (*pReseauNeurones).lfCoutCumule = 0;
    (*pReseauNeurones).usiNbLots = usiNbLots;

    //etape 2 : allocation memoire couches neurones (alloc dynamique)

    (*pReseauNeurones).pCouchesNeurones = malloc(siNbCouches*sizeof(T_COUCHE_NEURONES));

    if ((*pReseauNeurones).pCouchesNeurones == NULL)
    {
        DesInitParametresReseauNeuronesNiveauUn (pReseauNeurones);
        return ERREUR_ALLOCATION_MEMOIRE_RESEAU;
    }

    //etape 3 : parametrage des couches neurones

    InitCoucheNeurone(COUCHE_ENTREE,
                      "couche d'entree, indice 0",
                      NULL,
                      NULL,
                      NULL,
                      tabsiNbNeurones[0],
                      0,
                      NULL,
                      //QS/SS -> mat2DlfPoids doit être NULL
                      // pour les couches d'entrées
                      // ancienne valeur : (REEL**) &(mat3DlfPoids[0]),
                      CalcIdentite,
                      CalcDeriveeIdentite,
                      &(((*pReseauNeurones).pCouchesNeurones)[0])
                      );

    for(i = 1; i<siNbCouches-1; i++)
    {

        sprintf(str, "%s %hd", strCoucheCache, i);

        for(short j = 0; j<tabsiNbNeurones[i-1]; j++)
            for(short k = 0; k<3; k++)
                printf("%lf ", mat3DlfPoids[i][j][k]);

        InitCoucheNeurone(COUCHE_CACHEE,
                          str,
                          &(((*pReseauNeurones).pCouchesNeurones)[i-1]),
                          NULL,
                          NULL,
                          tabsiNbNeurones[i],
                          tabsiNbNeurones[i-1],
                          mat3DlfPoids[i],
                          Fonction_ActivationNeurone_Cache,
                          Fonction_Derivee_ActivationNeurone_Cache,
                          &(((*pReseauNeurones).pCouchesNeurones)[i])
                          );
    }

    sprintf(str, "couche de sortie, indice %hd", i);
    InitCoucheNeurone(COUCHE_SORTIE,
                      str,
                      &(((*pReseauNeurones).pCouchesNeurones)[i-1]),
                      F_ActivationVectorielle,
                      F_Derivee_ActivationVectorielle,
                      tabsiNbNeurones[i],
                      tabsiNbNeurones[i-1],
                      mat3DlfPoids[i],
                      Fonction_ActivationNeurone_Sortie,
                      Fonction_Derivee_ActivationNeurone_Sortie,
                      &(((*pReseauNeurones).pCouchesNeurones)[i])
                      );

    //etape 4 : allocation memoire tableau prediction valeurs finales

    (*pReseauNeurones).plfPredictionFinale = malloc((tabsiNbNeurones[i]) * sizeof(REEL));

    if ((*pReseauNeurones).plfPredictionFinale == NULL)
    {
        DesInitTabPredictionsNiveauDeux(pReseauNeurones, siNbCouches);
        return ERREUR_ALLOCATION_MEMOIRE_RESEAU;
    }

    //etape 5 : allocation memoire tableau vraies valeurs finales

    (*pReseauNeurones).plfVraieValeurFinale = malloc((tabsiNbNeurones[i]) * sizeof(REEL));


    if ((*pReseauNeurones).plfVraieValeurFinale == NULL)
    {
        DesInitTabVraiesValeursNiveauTrois (pReseauNeurones, siNbCouches);
        return ERREUR_ALLOCATION_MEMOIRE_RESEAU;
    }

    return PAS_D_ERREUR;
}

T_ERREUR DesinitReseauNeurone ( T_RESEAU_NEURONES * pReseauNeurones )
{
    //étape 1 : on désinit les couches
    int i;
    for(i=0;i<(*pReseauNeurones).siNbCouches;i++){
        DesinitCoucheNeurone(&((*pReseauNeurones).pCouchesNeurones[i]));
    }

    //étapes 2 : on vide la mémoire des tableaux
    //free((*pReseauNeurones).szDescription);
    free((*pReseauNeurones).plfPredictionFinale);
    free((*pReseauNeurones).plfVraieValeurFinale);
    free((*pReseauNeurones).pCouchesNeurones);

    //étapes 3 : on assigne des valeurs cohérente avec un RN désinit
    (*pReseauNeurones).plfPredictionFinale = NULL;
    (*pReseauNeurones).plfVraieValeurFinale = NULL;
    (*pReseauNeurones).pCouchesNeurones = NULL;

    strcpy((*pReseauNeurones).szDescription, "réseau desinit");
    (*pReseauNeurones).lfTauxApprentissage = 0;
    (*pReseauNeurones).siNbCouches = 0;
    (*pReseauNeurones).lfCoutCumule = 0;
    (*pReseauNeurones).usiNbLots = 0;

    (*pReseauNeurones).typeReseauNeurones = RESEAU_NON_INITIALISE;

    return PAS_D_ERREUR ;
}

T_ERREUR AfficheReseauNeurone ( T_RESEAU_NEURONES LeReseauNeurones )
{
    int i = 0;
    printf("Type du reseau neuronal : %hd\n", LeReseauNeurones.typeReseauNeurones);
    printf("Description reseau neuronal : %s\n", LeReseauNeurones.szDescription);
    printf("Nombre de couche : %hd \n", LeReseauNeurones.siNbCouches);
    printf("Taux d'apprentissage du RN : %lf \n", LeReseauNeurones.lfTauxApprentissage);
    printf("Cout Cumulee : %lf\n", LeReseauNeurones.lfCoutCumule);

    for(i=0; i< LeReseauNeurones.pCouchesNeurones[LeReseauNeurones.siNbCouches-1].siNbNeurones; i++)
    {
       printf("indice %d - Prediction finale : %lf, Vrai valeur : %lf\n", i,
              LeReseauNeurones.plfPredictionFinale[i], LeReseauNeurones.plfVraieValeurFinale[i]);
    }
    printf("Nombre de lot : %d", LeReseauNeurones.usiNbLots);

    return PAS_D_ERREUR ;
}

T_ERREUR AfficheIntegralReseauNeurone ( T_RESEAU_NEURONES LeReseauNeurones )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR SauveFicTexteReseauNeurones ( T_RESEAU_NEURONES   LeReseauNeurones ,
                                       char              * szNomFic         ,
                                       char              * szTexte          )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR SauveCoucheNeuronesDansFicTexte ( FILE              * pFic             ,
                                           T_COUCHE_NEURONES   LaCoucheNeurones )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR SauveFicBinaireReseauNeurones ( T_RESEAU_NEURONES   LeReseauNeurones ,
                                         char              * szNomFic         ,
                                         long int            liCleMagique     )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR SauveCoucheNeuronesDansFicBinaire ( FILE              * pFic             ,
                                             T_COUCHE_NEURONES   LaCoucheNeurones )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR ChargeFicBinaireReseauNeurones ( T_RESEAU_NEURONES * LeReseauNeurones ,
                                          char              * szNomFic         ,
                                          long int            liCleMagique     )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR ChargeCoucheNeuronesDansFicBinaire ( FILE              * pFic             ,
                                              T_COUCHE_NEURONES * LaCoucheNeurones )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR CalcPredictionReseauNeurones ( T_RESEAU_NEURONES * pReseauNeurones )
{
    short int i;
    short int y;

    if(pReseauNeurones->typeReseauNeurones == RESEAU_NON_INITIALISE)
        return ERREUR_TYPE_RESEAU_INCONNU;

    for(i = 0; i<pReseauNeurones->siNbCouches; i++)
    {
        CalcPredictionCoucheNeurones(&(pReseauNeurones->pCouchesNeurones[i]));
    }

    for(y = 0; y < pReseauNeurones->pCouchesNeurones[i-1].siNbNeurones; y++)
        pReseauNeurones->plfPredictionFinale[y] = pReseauNeurones->pCouchesNeurones[i-1].plfOutputSample[y];


    return PAS_D_ERREUR ;
}

T_ERREUR RetroPropagationErreursEtGradients ( T_RESEAU_NEURONES * pReseauNeurones )
{
    long int i , jNeurone , kDendrite ;

    if ( pReseauNeurones->typeReseauNeurones != RESEAU_FULLY_CONNECTED_AVEC_BIAIS )
        return ERREUR_TYPE_RESEAU_INCONNU ;

    /* calcul de l'erreur en sortie du reseau de neurone */
    for ( i = 0 ; i < pReseauNeurones->pCouchesNeurones[pReseauNeurones->siNbCouches-1].siNbNeurones ; i++ )
    {
        pReseauNeurones->pCouchesNeurones[pReseauNeurones->siNbCouches-1].plfErreurDeltaSample[i]
            = (pReseauNeurones->plfPredictionFinale[i] - pReseauNeurones->plfVraieValeurFinale[i]) ;
        // penser a intgrer la derivee pour que la formule soit generale !!!!!!!!!!!!!
    }

    /* retro-propagation des erreurs et calcul de la contribution aux corrections de gradient :
    boucle sur la couche de sortie et sur toutes les couches cachees */
    for ( i = pReseauNeurones->siNbCouches - 1 ; i > 0 ; i-- )
    {
        /* contribution a la correction de gradient :
        - si c'est la couche de sortie, jNeurone varie de ZERO a (NbNeurones-1) car pas de neurone de biais.
        - si c'est une couche cachee, jNeurone varie de UN a (NbNeurones-1) car il y a un neurone de biais (d'indice ZERO). */
        for ( jNeurone = ( (i == (pReseauNeurones->siNbCouches - 1)) ? 0 : 1 ) ;
        jNeurone < pReseauNeurones->pCouchesNeurones[i].siNbNeurones ;
        jNeurone ++ )
        {
            for ( kDendrite = 0 ; kDendrite < pReseauNeurones->pCouchesNeurones[i-1].siNbNeurones ; kDendrite++ )
                pReseauNeurones->pCouchesNeurones[i].pNeurones[jNeurone].tablfGradients[kDendrite] +=
                    pReseauNeurones->pCouchesNeurones[i].plfErreurDeltaSample[jNeurone]
                    * pReseauNeurones->pCouchesNeurones[i-1].plfOutputSample[kDendrite] ;

        }

        /* retro-propagation de l'erreur vers la couche precedent d'indice i > 0
        car on retro-propage vers la couche cachee precedente (inutile pour la couche d'entree) */
        if ( i != 1 )
        {
            /* on ne retro-propage que vers une couche cachee :
            si la couche precedente est la couche d'entree (i vaut 1), on ne retro-propage pas */
            for ( kDendrite = 1 ; kDendrite < pReseauNeurones->pCouchesNeurones[i-1].siNbNeurones ; kDendrite ++ )
            { /* kDendrite debute a UN car le neurone d'indice ZERO est de biais */
                pReseauNeurones->pCouchesNeurones[i-1].plfErreurDeltaSample[kDendrite] = 0.0 ;
                for (   jNeurone = ( (i == (pReseauNeurones->siNbCouches - 1)) ? 0 : 1 ) ;
                        jNeurone < pReseauNeurones->pCouchesNeurones[i].siNbNeurones ;
                        jNeurone ++ )
                {
                    pReseauNeurones->pCouchesNeurones[i-1].plfErreurDeltaSample[kDendrite] +=
                        pReseauNeurones->pCouchesNeurones[i].plfErreurDeltaSample[jNeurone]
                        * pReseauNeurones->pCouchesNeurones[i].pNeurones[jNeurone].tablfPoids[kDendrite] ;
                }

                pReseauNeurones->pCouchesNeurones[i-1].plfErreurDeltaSample[kDendrite] *=
                //                        pReseauNeurones->pCouchesNeurones[i-1].plfOutputSample[kDendrite]
                //                        * ( 1.0 - pReseauNeurones->pCouchesNeurones[i-1].plfOutputSample[kDendrite] ) ;
                // penser a remplacer par l'expression de la derivee generale !!!!!!!!!!!
                // CAD (verifier!!!) :
                pReseauNeurones->pCouchesNeurones[i-1].pNeurones[kDendrite].F_DeriveeActivation
                    ( pReseauNeurones->pCouchesNeurones[i-1].plfOutputSample[kDendrite] ) ;
            }
        }
    }

    return PAS_D_ERREUR ;
}

T_ERREUR InitAZeroGradientsPoidsCumules ( T_RESEAU_NEURONES * pReseauNeurones )
{
    short couche, neurone, dendrite;

    for (couche=0; couche<pReseauNeurones->siNbCouches; couche++)
        for (neurone=0; neurone<pReseauNeurones->pCouchesNeurones[couche].siNbNeurones; neurone++)
            for (dendrite=0; dendrite<pReseauNeurones->pCouchesNeurones[couche-1].siNbNeurones; dendrite++)
                pReseauNeurones->pCouchesNeurones[couche].pNeurones[neurone].tablfGradients[dendrite] = 0;

    return PAS_D_ERREUR ;
}

T_ERREUR CalcCorrectionPoidsSynaptiques ( T_RESEAU_NEURONES * pReseauNeurones ,
                                          long int            liNbElts        )
{
    long int i , j , k ;

    if ( pReseauNeurones->typeReseauNeurones != RESEAU_FULLY_CONNECTED_AVEC_BIAIS )
        return ERREUR_TYPE_RESEAU_INCONNU ;

    for ( i = 1 ; i < pReseauNeurones->siNbCouches ; i++ )
        for (   j = ( (i == (pReseauNeurones->siNbCouches - 1)) ? 0 : 1 ) ;
                j < pReseauNeurones->pCouchesNeurones[i].siNbNeurones ;
                j++ )
            for ( k = 0 ; k < pReseauNeurones->pCouchesNeurones[i-1].siNbNeurones ; k++ )
                pReseauNeurones->pCouchesNeurones[i].pNeurones[j].tablfPoids[k] +=
                    - pReseauNeurones->lfTauxApprentissage * pReseauNeurones->pCouchesNeurones[i].pNeurones[j].tablfGradients[k] / liNbElts ;

    return PAS_D_ERREUR ;
}

T_ERREUR PredictionJeuDeDonnees ( long int                            liNbElts                         ,
                                  char                              * TabDonnees                       ,
                                  T_RESEAU_NEURONES                   LeReseauNeurones                 ,
                                  short int                           siTailleStructData               ,
                                  T_INJECTEUR_DONNEES_COUCHE_ENTREE * InjectionDonneesDansCoucheEntree ,
                                  T_STOCKEUR_DONNEES_COUCHE_SORTIE  * StockePrediction                 )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR ApprentissageJeuDeDonnees ( long int                                   liNbElts                               ,
                                     char                                     * TabDonnees                             ,
                                     T_RESEAU_NEURONES                        * pReseauNeurones                        ,
                                     REEL                                       lfSeuilValCout                         ,
                                     unsigned long int                          uliNbMaxIter                           ,
                                     short int                                  siTailleStructData                     ,
                                     T_INJECTEUR_DONNEES_COUCHE_ENTREE        * InjectionDonneesDansCoucheEntree       ,
                                     T_STOCKEUR_DONNEES_COUCHE_SORTIE         * StockePrediction                       ,
                                     T_INJECTEUR_VRAIES_VALEURS_SORTIE_RESEAU * InjectionVraieValeurDansReseauNeurones ,
                                     T_FONCTION_COUT                          * FonctionDeCout                         ,
                                     unsigned char                              cParam                                 )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

void DesInitParametresReseauNeuronesNiveauUn (T_RESEAU_NEURONES * pReseauNeurones)
{
    (*pReseauNeurones).typeReseauNeurones = RESEAU_NON_INITIALISE;
    strcpy((*pReseauNeurones).szDescription, "");
    (*pReseauNeurones).lfTauxApprentissage = 0;
    (*pReseauNeurones).siNbCouches = 0;
    (*pReseauNeurones).lfCoutCumule = 0;
    (*pReseauNeurones).usiNbLots = 0;
}

void DesInitTabPredictionsNiveauDeux (T_RESEAU_NEURONES * pReseauNeurones, short siNbCouches)
{
    short i ;

    for(i = 1; i<siNbCouches-1; i++)
        DesinitCoucheNeurone(&(((*pReseauNeurones).pCouchesNeurones)[i]));

    free((*pReseauNeurones).pCouchesNeurones);
    (*pReseauNeurones).pCouchesNeurones = NULL;

    DesInitParametresReseauNeuronesNiveauUn (pReseauNeurones);
}

void DesInitTabVraiesValeursNiveauTrois (T_RESEAU_NEURONES * pReseauNeurones, short siNbCouches)
{
    free((*pReseauNeurones).plfPredictionFinale);
    (*pReseauNeurones).plfPredictionFinale = NULL ;

    DesInitTabPredictionsNiveauDeux(pReseauNeurones, siNbCouches);
}

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
