#include "TestsUnitaires.h"
#include "../BibliReseauNeurones/Neurone.h"
#include "../BibliReseauNeurones/Activation.h"
#include "../BibliReseauNeurones/CoucheNeurone.h"
#include "../BibliReseauNeurones/TypeReseauNeurones.h"
#include "../BibliReseauNeurones/ReseauNeurone.h"
#include <string.h>

/*********************************************************************************
    Fonctions de test general
*********************************************************************************/
T_ERREUR executerTests (void)
{
    short i=3 ;
    T_ERREUR resultat = PAS_D_ERREUR ;

    T_GROUPE_TEST tabTest [NB_TESTS] =  {
                                          { &testAfficheNeurone      , "AfficheNeurone..."       , false},
                                          { &testAfficheCoucheNeurone, "AfficheCoucheNeurone..." , false},
                                          { &testAfficheReseauNeurone, "AfficheReseauNeurone..." , false},
                                          { &testInitNeurone         , "InitNeurone..."          , false},
                                          { &testDesinitNeurone      , "DesinitNeurone..."       , false},
                                          { &testInitCoucheNeurone   , "InitCoucheNeurone..."    , false},
                                          { &testDesinitCoucheNeurone, "DesinitCoucheNeurone..." , false},
                                          { &testInitReseauNeurone   , "InitReseauNeurone..."    , false}
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
    REEL tabCoef[1]={1} ;
    REEL tabGradient[1]={0};
    T_NEURONE tabNeurones[3] = {{ 1,
                                 tabCoef ,
                                 tabGradient,
                                 CalcIdentite ,
                                 CalcDeriveeIdentite
                               },
                               { 1,
                                 tabCoef ,
                                 tabGradient,
                                 CalcIdentite ,
                                 CalcDeriveeIdentite
                               },
                               { 1,
                                 tabCoef ,
                                 tabGradient,
                                 CalcIdentite ,
                                 CalcDeriveeIdentite
                               }} ;
    REEL tabOutput[3] = {1,2,3} ;
    REEL tabErreur[3] = {4,5,6} ;

    T_COUCHE_NEURONES coucheEntreeATester = {COUCHE_ENTREE,
                                             "couche d'entree",
                                             NULL,
                                             NULL,
                                             NULL,
                                             3,
                                             1,
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
                                            CalcIdentite,
                                            CalcDeriveeIdentite,
                                            &coucheNeuroneAInitialiser);

    if ( resultat != PAS_D_ERREUR
        || coucheEntreeATester.typeCoucheNeurones != coucheNeuroneAInitialiser.typeCoucheNeurones
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
    // Creation d'une couche de neurones pour tester DesInitCoucheNeurone
    REEL tabCoef[1]={1} ;
    REEL tabGradient[1]={1};
    T_NEURONE tabNeurones[3] = {{ 1,
                                 tabCoef ,
                                 tabGradient,
                                 CalcIdentite ,
                                 CalcDeriveeIdentite
                               },
                               { 1,
                                 tabCoef ,
                                 tabGradient,
                                 CalcIdentite ,
                                 CalcDeriveeIdentite
                               },
                               { 1,
                                 tabCoef ,
                                 tabGradient,
                                 CalcIdentite ,
                                 CalcDeriveeIdentite
                               }} ;
    REEL tabOutput[3] = {1,2,3} ;
    REEL tabErreur[3] = {4,5,6} ;

    T_COUCHE_NEURONES coucheEntreeADesinit = {COUCHE_ENTREE,
                                             "couche d'entree",
                                             NULL,
                                             NULL,
                                             NULL,
                                             3,
                                             1,
                                             tabNeurones,
                                             tabOutput,
                                             tabErreur};

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
    REEL tabCoef[3]={ 0.2, 0.3, 0.4 } ;
    REEL tabGradient[3] = {0,0,0};
    T_NEURONE tabNeurones[3] = {{ 3,
                                 tabCoef ,
                                 tabGradient,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               },
                               { 3,
                                 tabCoef ,
                                 tabGradient,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               },
                               { 3,
                                 tabCoef ,
                                 tabGradient,
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
T_ERREUR testInitNeurone (void)
{
    T_ERREUR resultat = PAS_D_ERREUR;
    short int i = 0;
    /*
    printf ("%-40s", "Test de InitNeuroneTabPoidsOk...");
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
    else if(monNeurone.tablfPoids == NULL   // Verifions que les coefficients sont bien alloues & initialises
       || monNeurone.tablfPoids[0] != 0.02
       || monNeurone.tablfPoids[1] != 0.03
       || monNeurone.tablfPoids[2] != 0.05
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

    InitNeurone(3, NULL, CalcLogistique,
                CalcDeriveeLogistiqueViaValLogistique, &monNeurone);


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
    REEL tabCoef[3]={ 0.2, 0.3, 0.4 } ;
    REEL tabGradient[3] = {0,0,0};
    T_NEURONE neuroneATester = { 3,
                                 tabCoef ,
                                 tabGradient,
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
    short tabSiNbNeurones[2] = {3, 2};
    REEL matPoids[2][3] = {
                            {1,1,1},
                            {11,12,13}
                          };
    // Définition des elements alloues dynamiquement par la couche d'entree à 3 neurones
    REEL tabOutputEntree[3] = {1,2,3} ;
    REEL tabErreurEntree[3] = {4,5,6} ;

    REEL tabPoidsEntree[1] = {1};
    REEL tabGradientsEntree[1] = {0};

    T_NEURONE tabNeuronesEntree[3] =  {
                                          { 1,
                                            tabPoidsEntree ,
                                            tabGradientsEntree,
                                            CalcIdentite ,
                                            CalcDeriveeIdentite
                                          },
                                          { 1,
                                            tabPoidsEntree ,
                                            tabGradientsEntree,
                                            CalcIdentite ,
                                            CalcDeriveeIdentite
                                          },
                                          { 1,
                                            tabPoidsEntree ,
                                            tabGradientsEntree,
                                            CalcIdentite ,
                                            CalcDeriveeIdentite
                                          }
                                      } ;

    // définition des elements alloues dynamiquement par la couche de sortie a 2 neurones

    REEL tabOutputSortie[2] = {22,23} ;
    REEL tabErreurSortie[2] = {25,26} ;

    REEL tabPoidsSortie[3] = {11,12,13};
    REEL tabGradientsSortie[3] = {14,15,16};

    T_NEURONE tabNeuronesSortie[3] =  {
                                          { 3,
                                            tabPoidsSortie ,
                                            tabGradientsSortie,
                                            CalcIdentite ,
                                            CalcDeriveeIdentite
                                          },
                                          { 3,
                                            tabPoidsSortie ,
                                            tabGradientsSortie,
                                            CalcIdentite ,
                                            CalcDeriveeIdentite
                                          }
                                      } ;

    // Creation des couches de neurones
    T_COUCHE_NEURONES tabCouchesNeurones [2] =
        {
            // Couche d'entree
            {
                COUCHE_ENTREE,
                "Ma couche d'entree",
                NULL,
                NULL,
                NULL,
                3,
                1,
                tabNeuronesEntree,
                tabOutputEntree,
                tabErreurEntree
            },
            // Couche de sortie
            {
                COUCHE_SORTIE,
                "Ma couche de sortie",
                tabCouchesNeurones,
                CalcSoftMax,
                CalcDeriveePartielleSoftMaxViaValSoftMax,
                2,
                3,
                tabNeuronesSortie,
                tabOutputSortie,
                tabErreurSortie
            },
        } ;

    REEL tabPredictions [2] = {0, 0};
    REEL tabVraiesValeursFinales [2] = {0, 0};

    T_RESEAU_NEURONES monRN = { RESEAU_FULLY_CONNECTED_AVEC_BIAIS,
                                "Voici un reseau de neurones",
                                0.2,
                                2,
                                tabCouchesNeurones,
                                tabPredictions,
                                tabVraiesValeursFinales,
                                0,
                                50
                                };

    T_RESEAU_NEURONES monRNAInitialiser;

    T_ERREUR resultat = InitReseauNeurone(monRN.typeReseauNeurones,
                                          monRN.szDescription,
                                          monRN.lfTauxApprentissage,
                                          monRN.siNbCouches,
                                          tabSiNbNeurones,
                                          CalcSoftMax,
                                          CalcDeriveePartielleSoftMaxViaValSoftMax,
                                          matPoids,
                                          CalcLogistique,
                                          CalcDeriveeLogistiqueViaValLogistique,
                                          CalcSoftMax,
                                          CalcDeriveePartielleSoftMaxViaValSoftMax,
                                          monRN.usiNbLots,
                                          monRNAInitialiser);

    if ( resultat != PAS_D_ERREUR
        || )//|| CoucheNeuroneAInitialiser != NULL)

        return ERREUR;


    return PAS_D_ERREUR;
}

T_ERREUR testDesinitReseauNeurone ( )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR testAfficheReseauNeurone ( )
{
    short int resultat = 0;

    REEL tabCoef[3]={ 0.2, 0.3, 0.4 } ;
    REEL tabGradient[3] = {0,0,0};
    T_NEURONE tabNeurones[3] = {{ 3,
                                 tabCoef ,
                                 tabGradient,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               },
                               { 3,
                                 tabCoef ,
                                 tabGradient,
                                 CalcLogistique ,
                                 CalcDeriveeLogistiqueViaValLogistique
                               },
                               { 3,
                                 tabCoef ,
                                 tabGradient,
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

    T_RESEAU_NEURONES reseauATester = { RESEAU_FULLY_CONNECTED_AVEC_BIAIS,
                                        "Le reseau a tester",
                                        0.2,
                                        2,
                                        tabCoucheNeurone,
                                        tabPredictionRN,
                                        tabVraiValeurRN,
                                        5.76,
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
