/*******************************************************************
                              RESEAUNEURONE.C
Definition des fonctions de gestion des "reseaux de neurones"associées

*******************************************************************/

#include "ReseauNeurone.h"

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
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR DesinitReseauNeurone ( T_RESEAU_NEURONES * pReseauNeurones )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR AfficheReseauNeurone ( T_RESEAU_NEURONES LeReseauNeurones )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
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
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR RetroPropagationErreursEtGradients ( T_RESEAU_NEURONES * pReseauNeurones )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR InitAZeroGradientsPoidsCumules ( T_RESEAU_NEURONES * pReseauNeurones )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR CalcCorrectionPoidsSynaptiques ( T_RESEAU_NEURONES * pReseauNeurones ,
                                          long int            liNbElts        )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
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

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
