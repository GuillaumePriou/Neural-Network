#ifndef TESTSUNITAIRES_H_INCLUDED
#define TESTSUNITAIRES_H_INCLUDED

#include "../BibliReseauNeurones/constantes.h"


/*********************************************************************************
    Fonctions de test general
*********************************************************************************/
/*
    Execute tous les tests les uns apres les autres et revoie le resultat au main
    => si echec d'un test, le programme ne devrait pas aller plus loin
*/
T_ERREUR executerTests (void);

/*********************************************************************************
    Test Activation
*********************************************************************************/

/*********************************************************************************
    CalcMax
*********************************************************************************/

/*********************************************************************************
    CoucheNeurone
*********************************************************************************/
T_ERREUR testInitCoucheNeurone ();
T_ERREUR testDesinitCoucheNeurone ();
T_ERREUR testAfficheCoucheNeurone ();
T_ERREUR testSauveFicTexteCoucheNeurones ();
T_ERREUR testSauveNeuroneDansFicTexte ();
T_ERREUR testSauveFicBinaireCoucheNeurones ();
T_ERREUR testChargeFicBinaireCoucheNeurones ();
T_ERREUR testCalcPredictionCoucheNeurones ();


/*********************************************************************************
    FonctionCout
*********************************************************************************/

/********************************************************************************
    Neurone
*********************************************************************************/


/*********************************************************************************
    FonctionCout
*********************************************************************************/

/********************************************************************************
    Neurone
*********************************************************************************/
T_ERREUR testInitNeurone (void);
T_ERREUR testInitNeuroneTabPoidsOk (void);
T_ERREUR testInitNeuroneTabPoidsNull(void);
T_ERREUR testDesinitNeurone (void);
T_ERREUR testAfficheNeurone (void);
T_ERREUR testSauveFicTexteNeurone (void);
T_ERREUR testSauveFicBinaireNeurone (void);
T_ERREUR testChargeFicBinaireNeurone (void);
T_ERREUR testCalcPredictionNeurone (void);

/*********************************************************************************
    ReseauNeurone
*********************************************************************************/
T_ERREUR testInitReseauNeurone (void);
T_ERREUR testDesinitReseauNeurone (void);
T_ERREUR testAfficheReseauNeurone (void);
T_ERREUR testAfficheIntegralReseauNeurone (void);
T_ERREUR testSauveFicTexteReseauNeurones (void);
T_ERREUR testSauveCoucheNeuronesDansFicTexte (void);
T_ERREUR testSauveFicBinaireReseauNeurones (void);
T_ERREUR testSauveCoucheNeuronesDansFicBinaire (void);
T_ERREUR testChargeFicBinaireReseauNeurones (void);
T_ERREUR testChargeCoucheNeuronesDansFicBinaire (void);
T_ERREUR testCalcPredictionReseauNeurones (void);
T_ERREUR testRetroPropagationErreursEtGradients (void);
T_ERREUR testInitAZeroGradientsPoidsCumules (void);
T_ERREUR testCalcCorrectionPoidsSynaptiques (void);
T_ERREUR testPredictionJeuDeDonnees (void);
T_ERREUR testApprentissageJeuDeDonnees (void);

#endif // TESTSUNITAIRES_H_INCLUDED
