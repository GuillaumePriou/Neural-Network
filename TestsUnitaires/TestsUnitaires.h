#ifndef TESTSUNITAIRES_H_INCLUDED
#define TESTSUNITAIRES_H_INCLUDED

#include "../BibliReseauNeurones/constantes.h"

// Le nombre de tests
#define NB_TESTS 6

// Format des fonctions de test
typedef T_ERREUR T_FONCTION_TEST(void) ;

// Definition d'un type booleen
typedef enum { false, true } bool;

/*
 Une structure contenant un pointeur vers une fonction de test
 et une description succinte de ce qui est teste
*/
typedef struct
{
    T_FONCTION_TEST* ptr_fct_test;
    char descriptionTest[50];
    bool afficherSeulementSiProbleme;
} T_GROUPE_TEST;

/*********************************************************************************
    Fonctions de test general
*********************************************************************************/
/*
    Execute tous les tests les uns apres les autres et revoie le resultat au main
    => si echec d'un test, le programme ne devrait pas aller plus loin
*/
T_ERREUR executerTests (void);

/*
    execute la fonction de test donnee en parametre et se charge d'afficher le resultat

    ENTREE :
    - grp : structure contenant un pointeur vers la fonction de test a executer
            ainsi que le teste a afficher selon le resultat
    SORTIE :
    Le code d'erreur renvoye par la fonction de test
*/
T_ERREUR execTest(T_GROUPE_TEST grp);

/*********************************************************************************
    Test Activation
*********************************************************************************/

/*********************************************************************************
    CalcMax
*********************************************************************************/

/*********************************************************************************
    CoucheNeurone
*********************************************************************************/
T_FONCTION_TEST testInitCoucheNeurone;
T_FONCTION_TEST testDesinitCoucheNeurone;
T_FONCTION_TEST testAfficheCoucheNeurone;
T_FONCTION_TEST testSauveFicTexteCoucheNeurones;
T_FONCTION_TEST testSauveNeuroneDansFicTexte;
T_FONCTION_TEST testSauveFicBinaireCoucheNeurones;
T_FONCTION_TEST testChargeFicBinaireCoucheNeurones;
T_FONCTION_TEST testCalcPredictionCoucheNeurones;


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
T_FONCTION_TEST testInitNeurone;
T_FONCTION_TEST testInitNeuroneTabPoidsOk;
T_FONCTION_TEST testInitNeuroneTabPoidsNull;
T_FONCTION_TEST testDesinitNeurone;
T_FONCTION_TEST testAfficheNeurone;
T_FONCTION_TEST testSauveFicTexteNeurone;
T_FONCTION_TEST testSauveFicBinaireNeurone;
T_FONCTION_TEST testChargeFicBinaireNeurone;
T_FONCTION_TEST testCalcPredictionNeurone;

/*********************************************************************************
    ReseauNeurone
*********************************************************************************/
T_FONCTION_TEST testInitReseauNeurone;
T_FONCTION_TEST testDesinitReseauNeurone;
T_FONCTION_TEST testAfficheReseauNeurone;
T_FONCTION_TEST testAfficheIntegralReseauNeurone;
T_FONCTION_TEST testSauveFicTexteReseauNeurones;
T_FONCTION_TEST testSauveCoucheNeuronesDansFicTexte;
T_FONCTION_TEST testSauveFicBinaireReseauNeurones;
T_FONCTION_TEST testSauveCoucheNeuronesDansFicBinaire;
T_FONCTION_TEST testChargeFicBinaireReseauNeurones;
T_FONCTION_TEST testChargeCoucheNeuronesDansFicBinaire;
T_FONCTION_TEST testCalcPredictionReseauNeurones;
T_FONCTION_TEST testRetroPropagationErreursEtGradients;
T_FONCTION_TEST testInitAZeroGradientsPoidsCumules;
T_FONCTION_TEST testCalcCorrectionPoidsSynaptiques;
T_FONCTION_TEST testPredictionJeuDeDonnees;
T_FONCTION_TEST testApprentissageJeuDeDonnees;

#endif // TESTSUNITAIRES_H_INCLUDED
