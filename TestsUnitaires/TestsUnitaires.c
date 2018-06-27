#include "TestsUnitaires.h"
#include "../BibliReseauNeurones/Neurone.h"
#include "../BibliReseauNeurones/Activation.h"
#include "../BibliReseauNeurones/CoucheNeurone.h"
#include "../BibliReseauNeurones/TypeReseauNeurones.h"
#include "../BibliReseauNeurones/ReseauNeurone.h"
#include "VariableTest.h"
#include <string.h>

/*********************************************************************************
    Fonctions de test general
*********************************************************************************/
T_ERREUR executerTests (void)
{
    short i=0 ;
    T_ERREUR resultat = PAS_D_ERREUR ;

    T_GROUPE_TEST tabTest [NB_TESTS] =  {
                                          //{ &testAfficheNeurone      , "AfficheNeurone..."       , false},
                                          //{ &testAfficheCoucheNeurone, "AfficheCoucheNeurone..." , false},
                                          //{ &testAfficheReseauNeurone, "AfficheReseauNeurone..." , false},
                                          //{ &testInitNeurone         , "InitNeurone..."          , false},
                                          //{ &testDesinitNeurone      , "DesinitNeurone..."       , false},
                                          //{ &testInitCoucheNeurone   , "InitCoucheNeurone..."    , false},
                                          //{ &testDesinitCoucheNeurone, "DesinitCoucheNeurone..." , false},
                                          //{ &testInitReseauNeurone   , "InitReseauNeurone..."    , false},
                                          //{ &testDesinitReseauNeurone, "DesinitReseauNeurone..." , false},
                                          //{ &testCalcPredictionNeurone,"CalcPredictionNeurone...", false},
                                          //{ &testCalcPredictionCoucheNeuronesEntree, "CalcPredictionCoucheNeuroneEntree...", false},
                                          //{ &testCalcPredictionCoucheNeuronesCachee, "CalcPredictionCoucheNeuroneCachee...", false},
                                          //{ &testCalcPredictionCoucheNeuronesSortie, "CalcPredictionCoucheNeuroneSortie...", false},
                                          { &testCalcPredictionReseauNeurones, "CalcPredictionReseauNeurone...", false}
                                          //{ &, "Test de ..."},
                                   };


    while (resultat == PAS_D_ERREUR && i<NB_TESTS)
    {
        execTest(tabTest[i]);
        i++;
    }

    return resultat;
}

T_ERREUR execTest(T_GROUPE_TEST grp)
{
    // Affiche le test en cours
    if (grp.subFctTest == false)
    printf ("Test de %-40s", grp.descriptionTest);

    // Effectue le test
    T_ERREUR resultat = (*(grp.ptr_fct_test))();

    // Affiche le resultat : "ok" ou "Erreur : ..."
    if(resultat != PAS_D_ERREUR)
            printf("-> Echec test %s (cause %hd) \n", grp.descriptionTest, resultat);
    else if (grp.subFctTest == false)
        printf("ok\n");

    // Retourne le code d'erreur
    return resultat;
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

    T_COUCHE_NEURONES coucheNeuroneAInitialiser ;

    T_ERREUR resultat = InitCoucheNeurone ( coucheNeuroneEntree.typeCoucheNeurones,
                                            coucheNeuroneEntree.szDescription,
                                            coucheNeuroneEntree.pCoucheNeuronesAmont,
                                            coucheNeuroneEntree.F_ActivationVectorielle,
                                            coucheNeuroneEntree.F_Derivee_ActivationVectorielle,
                                            coucheNeuroneEntree.siNbNeurones,
                                            coucheNeuroneEntree.siNbDendritesParNeurone,
                                            NULL,
                                            CalcIdentite,
                                            CalcDeriveeIdentite,
                                            &coucheNeuroneAInitialiser);

    if ( resultat != PAS_D_ERREUR
        || coucheNeuroneEntree.typeCoucheNeurones != coucheNeuroneAInitialiser.typeCoucheNeurones
        || 0 != strcmp(coucheNeuroneEntree.szDescription, coucheNeuroneAInitialiser.szDescription)
        || coucheNeuroneEntree.pCoucheNeuronesAmont != coucheNeuroneAInitialiser.pCoucheNeuronesAmont
        || coucheNeuroneEntree.F_ActivationVectorielle != coucheNeuroneAInitialiser.F_ActivationVectorielle
        || coucheNeuroneEntree.F_Derivee_ActivationVectorielle != coucheNeuroneAInitialiser.F_Derivee_ActivationVectorielle
        || coucheNeuroneEntree.siNbNeurones != coucheNeuroneAInitialiser.siNbNeurones
        || coucheNeuroneEntree.siNbDendritesParNeurone != coucheNeuroneAInitialiser.siNbDendritesParNeurone
        )//|| CoucheNeuroneAInitialiser != NULL)

        return ERREUR_COUCHE_NEURONE_MAL_INITIALISEE;

    int i;
    for(i = 0; i< coucheNeuroneEntree.siNbNeurones; i++)
    {
        if(CmpNeurone(coucheNeuroneEntree.pNeurones[i], coucheNeuroneAInitialiser.pNeurones[i]) != 0)
            return ERREUR_COUCHE_NEURONE_MAL_INITIALISEE;
    }

    return PAS_D_ERREUR;
}

T_ERREUR testDesinitCoucheNeurone ()
{
    // Creation d'une couche de neurones pour tester DesInitCoucheNeurone

    T_COUCHE_NEURONES coucheEntreeADesinit;

    InitCoucheNeurone ( coucheNeuroneEntree.typeCoucheNeurones,
                        coucheNeuroneEntree.szDescription,
                        coucheNeuroneEntree.pCoucheNeuronesAmont,
                        coucheNeuroneEntree.F_ActivationVectorielle,
                        coucheNeuroneEntree.F_Derivee_ActivationVectorielle,
                        coucheNeuroneEntree.siNbNeurones,
                        coucheNeuroneEntree.siNbDendritesParNeurone,
                        NULL,
                        CalcIdentite,
                        CalcDeriveeIdentite,
                        &coucheEntreeADesinit);

    T_ERREUR resultat = DesinitCoucheNeurone(&coucheEntreeADesinit);

    if ( resultat != PAS_D_ERREUR
        || coucheEntreeADesinit.typeCoucheNeurones != COUCHE_NON_INITIALISEE
        || 0 != strcmp(coucheEntreeADesinit.szDescription, "Couche desinitialisee")
        || coucheEntreeADesinit.pCoucheNeuronesAmont != NULL
        || coucheEntreeADesinit.F_ActivationVectorielle != NULL
        || coucheEntreeADesinit.F_Derivee_ActivationVectorielle != NULL
        || coucheEntreeADesinit.siNbNeurones != 0
        || coucheEntreeADesinit.siNbDendritesParNeurone != 0
        || coucheEntreeADesinit.pNeurones != NULL
        || coucheEntreeADesinit.plfOutputSample != NULL
        || coucheEntreeADesinit.plfErreurDeltaSample != NULL
        )
        return ERREUR_POINTEUR_NON_INITIALISE ;
    else

        return PAS_D_ERREUR;
}

T_ERREUR testAfficheCoucheNeurone ()
{
    short int resultat = 0;

    T_COUCHE_NEURONES cn_initialisee = coucheNeuroneEntree;

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

T_ERREUR testCalcPredictionCoucheNeuronesEntree()
{
    short int resultat = 0;
    short int i;

    resultat = CalcPredictionCoucheNeurones(&coucheNeuroneEntree);

    for(i = 0; i<coucheNeuroneEntree.siNbNeurones; i++)
        printf("\n plfOutputSample %lf ", coucheNeuroneEntree.plfOutputSample[i]);

    if (resultat != PAS_D_ERREUR)
        printf ("-> Echec test CalcPredictionCoucheNeurones (couche entrée) (cause : %hd)\n", resultat);

    if(resultat != 0)
        return ERREUR_FONCTION_NON_DEFINIE;
    else
        return PAS_D_ERREUR;
}

T_ERREUR testCalcPredictionCoucheNeuronesCachee ()
{
    short int resultat = 0;
    short int i;

    resultat = CalcPredictionCoucheNeurones(&coucheNeuroneCachee);

    for(i = 0; i<coucheNeuroneCachee.siNbNeurones; i++)
        printf("\n plfOutputSample %lf ", coucheNeuroneCachee.plfOutputSample[i]);

    if (resultat != PAS_D_ERREUR)
        printf ("-> Echec test CalcPredictionCoucheNeurones (couche cachée) (cause : %hd)\n", resultat);

    if(resultat != 0)
        return ERREUR_FONCTION_NON_DEFINIE;
    else
        return PAS_D_ERREUR;
}

T_ERREUR testCalcPredictionCoucheNeuronesSortie ()
{
    short int resultat = 0;
    short int i;

    resultat = CalcPredictionCoucheNeurones(&coucheNeuroneSortie);

    for(i = 0; i<coucheNeuroneSortie.siNbNeurones; i++)
        printf("\n plfOutputSample %lf ", coucheNeuroneSortie.plfOutputSample[i]);

    if (resultat != PAS_D_ERREUR)
        printf ("-> Echec test CalcPredictionCoucheNeurones (couche sortie) (cause : %hd)\n", resultat);

    if(resultat != 0)
        return ERREUR_FONCTION_NON_DEFINIE;
    else
        return PAS_D_ERREUR;
}

/*********************************************************************************
    FonctionCout
*********************************************************************************/

/********************************************************************************
    Neurone
*********************************************************************************/
T_ERREUR testInitNeurone (void)
{
    T_ERREUR resultat = PAS_D_ERREUR;
    short int i = 0;
    /*
    printf ("%-40s", "Test de InitNeuroneTabPoidsOk..");
    resultat = testInitNeuroneTabPoidsOk();
    if( resultat != PAS_D_ERREUR)
        printf("-> ECHEC TEST INIT NEURONE (cause %hd)\n", resultat);
    else
        printf("ok\n");

    printf ("%-40s", "Test de InitNeuroneTabPoidsNull...");
    resultat = testInitNeuroneTabPoidsNull();
    if( resultat != PAS_D_ERREUR)
        printf("-> ECHEC TEST INIT NEURONE (cause %hd)\n", resultat);
    else
        printf("ok\n");

    */

    T_GROUPE_TEST tabTest [2] =  {
                                  {&testInitNeuroneTabPoidsOk, "InitNeuroneTabPoidsOk", true},
                                  {&testInitNeuroneTabPoidsNull, "InitNeuroneTabPoidsNull", true}
                                };

    while (resultat == PAS_D_ERREUR && i<2)
    {
        execTest(tabTest[i]);
        i++;
    }

    return resultat;

}
T_ERREUR testInitNeuroneTabPoidsOk()
{
    /*short int siNbDendrite = 3;
    REEL tabPoids[3] = {0.02, 0.03, 0.05};
    T_FONCTION_ACTIVATION *fonctionActivation = CalcLogistique;
    T_FONCTION_ACTIVATION *deriveeActivation = CalcDeriveeLogistiqueViaValLogistique;
*/
    //T_NEURONE *ptrNeurone = NULL;
    T_NEURONE monNeurone ;

    InitNeurone(tabNeuroneCoucheCachee[1].typeNeurone,
                tabNeuroneCoucheCachee[1].siNbDendrites,
                tabNeuroneCoucheCachee[1].tablfPoids,
                tabNeuroneCoucheCachee[1].F_Activation,
                tabNeuroneCoucheCachee[1].F_DeriveeActivation,
                &monNeurone);

    if(monNeurone.siNbDendrites != tabNeuroneCoucheCachee[1].siNbDendrites
       || monNeurone.F_Activation != tabNeuroneCoucheCachee[1].F_Activation
       || monNeurone.F_DeriveeActivation != tabNeuroneCoucheCachee[1].F_DeriveeActivation)
       return ERREUR_NEURONE_MAL_INITIALISE;
    else if(monNeurone.tablfPoids == NULL   // Verifions que les coefficients sont bien alloues & initialises
       || monNeurone.tablfPoids[0] != tabNeuroneCoucheCachee[1].tablfPoids[0]
       || monNeurone.tablfPoids[1] != tabNeuroneCoucheCachee[1].tablfPoids[1]
       || monNeurone.tablfPoids[2] != tabNeuroneCoucheCachee[1].tablfPoids[2]
       || monNeurone.tablfGradients == NULL // Verifions que les gradients sont bien alloues & initialises
       || monNeurone.tablfGradients[0] != tabNeuroneCoucheCachee[1].tablfGradients[0]
       || monNeurone.tablfGradients[1] != tabNeuroneCoucheCachee[1].tablfGradients[1]
       || monNeurone.tablfGradients[2] != tabNeuroneCoucheCachee[1].tablfGradients[2] )
        return ERREUR_INDETERMINEE;
    else
    {
        //AfficheNeurone(monNeurone);
        return PAS_D_ERREUR;
    }
}

T_ERREUR testInitNeuroneTabPoidsNull()
{
    /*short int siNbDendrite = 3;
    T_FONCTION_ACTIVATION *fonctionActivation = CalcLogistique;
    T_FONCTION_ACTIVATION *deriveeActivation = CalcDeriveeLogistiqueViaValLogistique;*/

    //T_NEURONE *ptrNeurone = NULL;
    T_NEURONE monNeurone;

    InitNeurone(tabNeuroneCoucheCachee[1].typeNeurone,
                tabNeuroneCoucheCachee[1].siNbDendrites,
                NULL,
                tabNeuroneCoucheCachee[1].F_Activation,
                tabNeuroneCoucheCachee[1].F_DeriveeActivation,
                &monNeurone);

    if(monNeurone.siNbDendrites != 3
       || monNeurone.F_Activation != tabNeuroneCoucheCachee[1].F_Activation
       || monNeurone.F_DeriveeActivation != tabNeuroneCoucheCachee[1].F_DeriveeActivation)
       return ERREUR_NEURONE_MAL_INITIALISE;
    else if(monNeurone.tablfPoids == NULL   // Verifions que les coefficients sont bien alloues & initialises
       || monNeurone.tablfPoids[0] != 0.01
       || monNeurone.tablfPoids[1] != 0.01
       || monNeurone.tablfPoids[2] != 0.01
       || monNeurone.tablfGradients == NULL // Verifions que les gradients sont bien alloues & initialises
       || monNeurone.tablfGradients[0] != 0
       || monNeurone.tablfGradients[1] != 0
       || monNeurone.tablfGradients[2] != 0 )
        return ERREUR_INDETERMINEE;
    else
    {
        //AfficheNeurone(monNeurone);
        return PAS_D_ERREUR;
    }
}

T_ERREUR testDesinitNeurone ()
{
    T_ERREUR resultat;
    T_NEURONE monNeurone;

    InitNeurone(tabNeuroneCoucheCachee[1].typeNeurone,
                tabNeuroneCoucheCachee[1].siNbDendrites,
                tabNeuroneCoucheCachee[1].tablfPoids,
                tabNeuroneCoucheCachee[1].F_Activation,
                tabNeuroneCoucheCachee[1].F_DeriveeActivation,
                &monNeurone);

    resultat = DesinitNeurone(&monNeurone);

    if(monNeurone.siNbDendrites != 0
       || monNeurone.F_Activation != NULL
       || monNeurone.F_DeriveeActivation != NULL
       || monNeurone.tablfPoids != NULL
       || monNeurone.tablfGradients != NULL)
       return ERREUR_POINTEUR_NON_INITIALISE;
    else if(resultat != 0)
        return ERREUR_INDETERMINEE;
    else
        return PAS_D_ERREUR;
}

T_ERREUR testAfficheNeurone (void)
{
    return AfficheNeurone(tabNeuroneCoucheCachee[1]);
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
    short int resultat = 0;

    REEL plfPrediction[1] = {0};

    resultat = CalcPredictionNeurone(plfOutputSamplesCC,
                                     4,
                                     &(tabNeuroneCoucheSortie[2]),
                                     &(plfPrediction[0]));

    if (resultat != PAS_D_ERREUR)
        printf ("-> Echec test CalcPredictionNeurone (couche sortie) (cause : %hd)\n", resultat);

    if(resultat != 0)
        return ERREUR_FONCTION_NON_DEFINIE;
    else
        return PAS_D_ERREUR;
}

/*********************************************************************************
    ReseauNeurone
*********************************************************************************/

T_ERREUR testInitReseauNeurone ( )
{
    T_RESEAU_NEURONES monRNAInitialiser;



    T_ERREUR resultat = InitReseauNeurone(reseauNeurone.typeReseauNeurones,
                                          reseauNeurone.szDescription,
                                          reseauNeurone.lfTauxApprentissage,
                                          reseauNeurone.siNbCouches,
                                          tabsiNbNeuronesRN,
                                          CalcSoftMax,
                                          CalcDeriveePartielleSoftMaxViaValSoftMax,
                                          (REEL ***) tabCoefs,
                                          CalcLogistique,
                                          CalcDeriveeLogistiqueViaValLogistique,
                                          CalcLogistique,
                                          CalcDeriveeLogistiqueViaValLogistique,
                                          reseauNeurone.usiNbLots,
                                          &monRNAInitialiser);


    if ( resultat != PAS_D_ERREUR
        || monRNAInitialiser.typeReseauNeurones != reseauNeurone.typeReseauNeurones
        || strcmp(monRNAInitialiser.szDescription, reseauNeurone.szDescription) != 0
        || monRNAInitialiser.lfTauxApprentissage != reseauNeurone.lfTauxApprentissage
        || monRNAInitialiser.siNbCouches != reseauNeurone.siNbCouches
        || monRNAInitialiser.lfCoutCumule != reseauNeurone.lfCoutCumule
        || monRNAInitialiser.usiNbLots != reseauNeurone.usiNbLots
      //   A voir plus tard, faut il vérifier le contenu des tabz'
      //  || monRNAInitialiser.plfPredictionFinale[0] != 1
      //  || monRNAInitialiser.plfVraieValeurFinale != NULL
    )
        return ERREUR_RESEAU_NEURONE_MAL_INITIALISEE;

    //Comparaison des couches de neurones
    for(int i = 0; i<reseauNeurone.siNbCouches; i++)
        if(CmpCoucheNeurone(monRNAInitialiser.pCouchesNeurones[i], reseauNeurone.pCouchesNeurones[i]) != 0)
            return ERREUR_RESEAU_NEURONE_MAL_INITIALISEE;


    return PAS_D_ERREUR;
}

T_ERREUR testDesinitReseauNeurone()
{
    T_RESEAU_NEURONES monReseauTest;
    T_ERREUR resultatInit =InitReseauNeurone(reseauNeurone.typeReseauNeurones,
                                             reseauNeurone.szDescription,
                                             reseauNeurone.lfTauxApprentissage,
                                             reseauNeurone.siNbCouches,
                                             tabsiNbNeuronesRN,
                                             CalcSoftMax,
                                             CalcDeriveePartielleSoftMaxViaValSoftMax,
                                             (REEL ***) tabCoefs,
                                             CalcLogistique,
                                             CalcDeriveeLogistiqueViaValLogistique,
                                             CalcLogistique,
                                             CalcDeriveeLogistiqueViaValLogistique,
                                             reseauNeurone.usiNbLots,
                                             &monReseauTest);


    T_ERREUR resultat = DesinitReseauNeurone(&monReseauTest);
    if (resultat != PAS_D_ERREUR
        ||strcmp(monReseauTest.szDescription,"réseau desinit")!=0
        ||monReseauTest.plfPredictionFinale!=NULL
        ||monReseauTest.plfVraieValeurFinale!=NULL
        ||monReseauTest.pCouchesNeurones!=NULL
        ||monReseauTest.siNbCouches!=0
        ||monReseauTest.lfCoutCumule!=0
        ||monReseauTest.usiNbLots!=0)
        return ERREUR_INDETERMINEE;
    return PAS_D_ERREUR;

}

T_ERREUR testAfficheReseauNeurone ( )
{
    short int resultat = 0;

    resultat = AfficheReseauNeurone(reseauNeurone);
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
    short int resultat = 0;
    short int i;
    T_RESEAU_NEURONES LeReseau3c3n;

    short int tabsiNbNeuroneParCouche[3] = {3, 3, 3};

  InitReseauNeurone ( RESEAU_FULLY_CONNECTED_AVEC_BIAIS  ,
                    "Reseau de 3 couches de 3 neurones" ,
                    0.2 , // 0.2
                    3 , // 3
                    tabsiNbNeuroneParCouche , // {3, 3, 3}
                    CalcSoftMax ,
                    CalcDeriveePartielleSoftMaxViaValSoftMax ,
                    tabCoefs,
                    CalcLogistique ,
                    CalcDeriveeLogistiqueViaValLogistique ,
                    CalcIdentite ,
                    CalcDeriveeIdentite ,
                    0 , // 0
                    &LeReseau3c3n );

    LeReseau3c3n.pCouchesNeurones[0].plfOutputSample[0] = 1;
    LeReseau3c3n.pCouchesNeurones[0].plfOutputSample[1] = 1.4;
    LeReseau3c3n.pCouchesNeurones[0].plfOutputSample[2] = 0.2;

    AfficheReseauNeurone(LeReseau3c3n);

    resultat = CalcPredictionReseauNeurones(&LeReseau3c3n);

    for(i = 0; i<LeReseau3c3n.siNbCouches; i++)
    {
        for(int y = 0; y<LeReseau3c3n.pCouchesNeurones[i].siNbNeurones; y++)
            printf("\n output couche %hd, value %lf", i, LeReseau3c3n.pCouchesNeurones[i].plfOutputSample[y]);
    }

    if (resultat != PAS_D_ERREUR)
        printf ("-> Echec test CalcPredictionReseauNeurones (cause : %hd)\n", resultat);

    if(resultat != 0)
        return ERREUR_FONCTION_NON_DEFINIE;
    else
        return PAS_D_ERREUR;
}

T_ERREUR testRetroPropagationErreursEtGradients ( )
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

short cmpMatrice1(int taille, REEL* matA, REEL* matB){
    for(int i=0;i<taille;i++)
        if(matA[i]!=matB[i])
            return 1;
    return 0;
}

short cmpMatrice2(int taille1D,int taille2D, REEL** matA, REEL** matB){
    for(int i=0;i<taille1D;i++)
        if(cmpMatrice1(taille2D, matA[i], matB[i]) != 0)
            return 1;
    return 0;
}

short cmpMatrice3(int taille1D,int taille2D,int taille3D, REEL*** matA, REEL*** matB){
    for(int i=0;i<taille1D;i++)
        if(cmpMatrice2(taille2D,taille3D, matA[i], matB[i]) != 0)
            return 1;
    return 0;
}
