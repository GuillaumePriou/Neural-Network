#include "TestsUnitaires.h"
#include "../BibliReseauNeurones/Neurone.h"
#include "../BibliReseauNeurones/Activation.h"
#include "../BibliReseauNeurones/CoucheNeurone.h"
#include "../BibliReseauNeurones/TypeReseauNeurones.h"
#include "../BibliReseauNeurones/ReseauNeurone.h"
#include <string.h>

T_ERREUR executerTests (void)
{
    short flag_echec_test = 0;
    T_ERREUR resultat;

    /*resultat = testAfficheNeurone();
    if ( resultat != PAS_D_ERREUR)
        printf ("-> Echec test AfficheNeurone (cause : %hd)\n", resultat);

    resultat = testAfficheCoucheNeurone();
    if ( resultat != PAS_D_ERREUR)
        printf ("-> Echec test AfficheCoucheNeurone (cause : %hd)\n", resultat);*/

    /*resultat = testAfficheReseauNeurone();
    if( resultat != PAS_D_ERREUR)
        printf("-> Echec test AfficheReseauNeuronne (cause : %hd)\n", resultat);*/

    /*resultat = testInitNeuroneTabPoidsOk();
    if( resultat != PAS_D_ERREUR)
        printf("-> ECHEC TEST INIT NEURONE (cause %hd)\n", resultat);

    resultat = testInitNeuroneTabPoidsNull();
    if( resultat != PAS_D_ERREUR)
        printf("-> ECHEC TEST INIT NEURONE (cause %hd)\n", resultat);*/

    /*resultat = testDesinitNeurone();
    if(resultat != PAS_D_ERREUR)
            printf("-> Echec test desinit neurone (cause %hd) \n", resultat);*/

    resultat = testInitCoucheNeurone();
    if(resultat != PAS_D_ERREUR)
            printf("-> Echec test init couche neurone (cause %hd) \n", resultat);

    // Retourne le resultat des tests
    if (flag_echec_test != 0)
        return ERREUR_INDETERMINEE;
    else
        return PAS_D_ERREUR;
}

/*********************************************************************************
    Test Activation
*********************************************************************************/

/*********************************************************************************
    CalcMax
*********************************************************************************/

/*********************************************************************************
    CoucheNeurone
*********************************************************************************/

T_ERREUR testInitCoucheNeurone ()
{
    // Creation d'une couche de neurones pour tester initCoucheNeurone
    REEL tabCoef[3]={ 0.2, 0.3, 0.4 } ;
    T_NEURONE tabNeurones[3] = {{ 3,
                                 tabCoef ,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               },
                               { 3,
                                 tabCoef ,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               },
                               { 3,
                                 tabCoef ,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               }} ;
    REEL tabOutput[3] = {1,2,3} ;
    REEL tabErreur[3] = {4,5,6} ;

    T_COUCHE_NEURONES coucheEntreeATester = {COUCHE_ENTREE,
                                             "couche d'entree",
                                             NULL,
                                             NULL,
                                             NULL,
                                             3,
                                             3,
                                             tabNeurones,
                                             tabOutput,
                                             tabErreur};

    T_COUCHE_NEURONES coucheNeuroneAInitialiser ;

    T_ERREUR resultat = InitCoucheNeurone ( coucheEntreeATester.typeCoucheNeurones,
                                            coucheEntreeATester.szDescription,
                                            coucheEntreeATester.pCoucheNeuronesAmont,
                                            coucheEntreeATester.F_ActivationVectorielle,
                                            coucheEntreeATester.F_Derivee_ActivationVectorielle,
                                            coucheEntreeATester.siNbNeurones,
                                            coucheEntreeATester.siNbDendritesParNeurone,
                                            NULL,
                                            NULL,
                                            NULL,
                                            &coucheNeuroneAInitialiser);

    if (   coucheEntreeATester.typeCoucheNeurones != coucheNeuroneAInitialiser.typeCoucheNeurones
        || 0 != strcmp(coucheEntreeATester.szDescription, coucheNeuroneAInitialiser.szDescription)
        || coucheEntreeATester.pCoucheNeuronesAmont != coucheNeuroneAInitialiser.pCoucheNeuronesAmont
        || coucheEntreeATester.F_ActivationVectorielle != coucheNeuroneAInitialiser.F_ActivationVectorielle
        || coucheEntreeATester.F_Derivee_ActivationVectorielle != coucheNeuroneAInitialiser.F_Derivee_ActivationVectorielle
        || coucheEntreeATester.siNbNeurones != coucheNeuroneAInitialiser.siNbNeurones
        || coucheEntreeATester.siNbDendritesParNeurone != coucheNeuroneAInitialiser.siNbDendritesParNeurone
        )//|| CoucheNeuroneAInitialiser != NULL)

        return ERREUR_COUCHE_NEURONE_MAL_INITIALISEE;

    int i;
    for(i = 0; i< coucheEntreeATester.siNbNeurones; i++)
    {
        if(CmpNeurone(coucheEntreeATester.pNeurones[i], coucheNeuroneAInitialiser.pNeurones[i]) != 0)
            return ERREUR_COUCHE_NEURONE_MAL_INITIALISEE;
    }

    return PAS_D_ERREUR;
}

T_ERREUR testDesinitCoucheNeurone ()
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testAfficheCoucheNeurone ()
{
    short int resultat = 0;
    REEL tabCoef[3]={ 0.2, 0.3, 0.4 } ;

    T_NEURONE tabNeurones[3] = {{ 3,
                                 tabCoef ,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               },
                               { 3,
                                 tabCoef ,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               },
                               { 3,
                                 tabCoef ,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               }} ;
    REEL tabOutput[3] = {1,2,3} ;
    REEL tabErreur[3] = {4,5,6} ;

    T_COUCHE_NEURONES cn_non_initialisee = { COUCHE_NON_INITIALISEE,
                                             "Ma couche pas bien initialisee",
                                             NULL,
                                             NULL,
                                             NULL,
                                             3,
                                             3,
                                             tabNeurones,
                                             tabOutput,
                                             tabErreur
                                           };

    T_COUCHE_NEURONES cn_initialisee = { COUCHE_ENTREE,
                                             "Ma couche pas bien initialisee",
                                             NULL,
                                             NULL,
                                             NULL,
                                             3,
                                             3,
                                             tabNeurones,
                                             tabOutput,
                                             tabErreur
                                           };

    AfficheCoucheNeurone(cn_non_initialisee, 0, 2) ;
    resultat =  AfficheCoucheNeurone(cn_non_initialisee, 0, 2) ;
    if ( resultat != ERREUR_TYPE_COUCHE_INCONNU)
        printf ("-> Echec test AfficheCoucheNeurone (couche non-initialisee) (cause : %hd)\n", resultat);



    resultat = AfficheCoucheNeurone(cn_initialisee, 0, 2);
    if ( resultat != PAS_D_ERREUR)
        printf ("-> Echec test AfficheCoucheNeurone (couche initialisee) (cause : %hd)\n", resultat);

    if(resultat != 0)
        return ERREUR_FONCTION_NON_DEFINIE;
    else
        return PAS_D_ERREUR;
}

T_ERREUR testSauveFicTexteCoucheNeurones ()
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testSauveNeuroneDansFicTexte ()
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testSauveFicBinaireCoucheNeurones ()
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testChargeFicBinaireCoucheNeurones ()
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testCalcPredictionCoucheNeurones ()
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

/*********************************************************************************
    FonctionCout
*********************************************************************************/

/********************************************************************************
    Neurone
*********************************************************************************/

T_ERREUR testInitNeuroneTabPoidsOk()
{
    short int siNbDendrite = 3;
    REEL tabPoids[3] = {0.02, 0.03, 0.05};
    T_FONCTION_ACTIVATION *fonctionActivation = CalcLogistique;
    T_FONCTION_ACTIVATION *deriveeActivation = CalcDeriveeLogistiqueViaValLogistique;

    //T_NEURONE *ptrNeurone = NULL;
    T_NEURONE monNeurone ;

    InitNeurone(siNbDendrite, tabPoids, fonctionActivation,
                deriveeActivation, &monNeurone);

    if(monNeurone.siNbDendrites != 3
       || monNeurone.F_Activation != fonctionActivation
       || monNeurone.F_DeriveeActivation != deriveeActivation)
       return ERREUR_NEURONE_MAL_INITIALISE;
    else if(monNeurone.tablfPoids == NULL
       || monNeurone.tablfPoids[0] != 0.02
       || monNeurone.tablfPoids[1] != 0.03
       || monNeurone.tablfPoids[2] != 0.05)
        return ERREUR_INDETERMINEE;
    else
    {
        AfficheNeurone(monNeurone);
        return PAS_D_ERREUR;
    }
}

T_ERREUR testInitNeuroneTabPoidsNull()
{
    short int siNbDendrite = 3;
    T_FONCTION_ACTIVATION *fonctionActivation = CalcLogistique;
    T_FONCTION_ACTIVATION *deriveeActivation = CalcDeriveeLogistiqueViaValLogistique;

    //T_NEURONE *ptrNeurone = NULL;
    T_NEURONE monNeurone;

    InitNeurone(siNbDendrite, NULL, fonctionActivation,
                deriveeActivation, &monNeurone);

    if(monNeurone.siNbDendrites != 3
       || monNeurone.F_Activation != fonctionActivation
       || monNeurone.F_DeriveeActivation != deriveeActivation)
       return ERREUR_NEURONE_MAL_INITIALISE;
    else if(monNeurone.tablfPoids == NULL
       || monNeurone.tablfPoids[0] != 0.01
       || monNeurone.tablfPoids[1] != 0.01
       || monNeurone.tablfPoids[2] != 0.01)
        return ERREUR_INDETERMINEE;
    else
    {
        AfficheNeurone(monNeurone);
        return PAS_D_ERREUR;
    }
}

T_ERREUR testDesinitNeurone ()
{
    T_ERREUR resultat;
    T_NEURONE monNeurone;

    InitNeurone(3, NULL, CalcLogistique,
                CalcDeriveeLogistiqueViaValLogistique, &monNeurone);


    resultat = DesinitNeurone(&monNeurone);

    if(monNeurone.siNbDendrites != 0
       || monNeurone.F_Activation != NULL
       || monNeurone.F_DeriveeActivation != NULL
       || monNeurone.tablfPoids != NULL)
       return ERREUR_POINTEUR_NON_INITIALISE;
    else if(resultat != 0)
        return ERREUR_INDETERMINEE;
    else
        return PAS_D_ERREUR;
}

T_ERREUR testAfficheNeurone ()
{
    REEL tabCoef[3]={ 0.2, 0.3, 0.4 } ;

    T_NEURONE neuroneATester = { 3,
                                 tabCoef ,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               };

    return AfficheNeurone(neuroneATester);
}

T_ERREUR testSauveFicTexteNeurone ()
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testSauveFicBinaireNeurone ()
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testChargeFicBinaireNeurone ()
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testCalcPredictionNeurone ()
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

/*********************************************************************************
    ReseauNeurone
*********************************************************************************/

T_ERREUR testInitReseauNeurone ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testDesinitReseauNeurone ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testAfficheReseauNeurone ( )
{
    short int resultat = 0;

    REEL tabCoef[3]={ 0.2, 0.3, 0.4 } ;
    T_NEURONE tabNeurones[3] = {{ 3,
                                 tabCoef ,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               },
                               { 3,
                                 tabCoef ,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               },
                               { 3,
                                 tabCoef ,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               }} ;
    REEL tabOutput[3] = {1,2,3} ;
    REEL tabErreur[3] = {4,5,6} ;

    T_COUCHE_NEURONES coucheEntreeATester = {COUCHE_ENTREE,
                                             "couche d'entree",
                                             NULL,
                                             NULL,
                                             NULL,
                                             3,
                                             3,
                                             tabNeurones,
                                             tabOutput,
                                             tabErreur};
    T_COUCHE_NEURONES coucheSortieATester = {COUCHE_SORTIE,
                                             "couche de sortie",
                                             &coucheEntreeATester,
                                             CalcSoftMax,
                                             CalcDeriveePartielleSoftMaxViaValSoftMax,
                                             3,
                                             3,
                                             tabNeurones,
                                             tabOutput,
                                             tabErreur};
    T_COUCHE_NEURONES tabCoucheNeurone[2] = {coucheEntreeATester,
                                             coucheSortieATester };

    REEL tabPredictionRN[3] = {0.1, 0.3, 0.6};
    REEL tabVraiValeurRN[3] = {1,0,0};

    REEL putainDeTabA3Dimension[2][3][3] = {
                                    {
                                        {0.1, 0.2, 0.3},
                                        {0.1, 0.2, 0.3},
                                        {0.1, 0.2, 0.3}
                                    },
                                    {
                                        {0.1, 0.2, 0.3},
                                        {0.1, 0.2, 0.3},
                                        {0.1, 0.2, 0.3}
                                    }
                                  };

    T_RESEAU_NEURONES reseauATester = { RESEAU_FULLY_CONNECTED_AVEC_BIAIS,
                                        "Le reseau a tester",
                                        0.2,
                                        2,
                                        tabCoucheNeurone,
                                        tabPredictionRN,
                                        tabVraiValeurRN,
                                        5.76,
                                        (REEL***)putainDeTabA3Dimension,
                                        5};
    resultat = AfficheReseauNeurone(reseauATester);
    if (resultat != PAS_D_ERREUR)
        printf ("-> Echec test AfficheReseauNeurone (cause : %hd)\n", resultat);

    if(resultat != 0)
        return ERREUR_FONCTION_NON_DEFINIE;
    else
        return PAS_D_ERREUR;
}

T_ERREUR testAfficheIntegralReseauNeurone (  )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testSauveFicTexteReseauNeurones ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testSauveCoucheNeuronesDansFicTexte ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testSauveFicBinaireReseauNeurones ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testSauveCoucheNeuronesDansFicBinaire ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testChargeFicBinaireReseauNeurones ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testChargeCoucheNeuronesDansFicBinaire ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testCalcPredictionReseauNeurones ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testRetroPropagationErreursEtGradients ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testInitAZeroGradientsPoidsCumules ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testCalcCorrectionPoidsSynaptiques ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testPredictionJeuDeDonnees ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testApprentissageJeuDeDonnees ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}
