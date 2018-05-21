#ifndef TESTSUNITAIRES_H_INCLUDED
#define TESTSUNITAIRES_H_INCLUDED

#include "../BibliReseauNeurones/constantes.h"
/*********************************************************************************
    Test Activation
*********************************************************************************/

/*********************************************************************************
    CalcMax
*********************************************************************************/

/*********************************************************************************
    CoucheNeurone
*********************************************************************************/
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
T_ERREUR executerTests (void);
T_ERREUR testInitNeurone (void);
T_ERREUR testDesinitNeurone (void);
T_ERREUR testAfficheNeurone (void);
T_ERREUR testSauveFicTexteNeurone (void);
T_ERREUR testSauveFicBinaireNeurone (void);
T_ERREUR testChargeFicBinaireNeurone (void);
T_ERREUR testCalcPredictionNeurone (void);

/*********************************************************************************
    ReseauNeurone
*********************************************************************************/

#endif // TESTSUNITAIRES_H_INCLUDED
