#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "./TestsUnitaires/TestsUnitaires.h"
#include "./BibliReseauNeurones/Neurone.h"
#include "./BibliReseauNeurones/Activation.h"
#include "./BibliReseauNeurones/CoucheNeurone.h"
#include "./BibliReseauNeurones/TypeReseauNeurones.h"
#include "./BibliReseauNeurones/ReseauNeurone.h"
#include "./InterfacesJeuxDeDonnees/IrisDataSet/IrisDataSet.h"

int main()
{
    // executerTests();


    /*
        Creation reseau neuronal
    */
    T_RESEAU_NEURONES rn;
    short tabNbNeurones[3] = {3, 3, 3};

    InitReseauNeurone( RESEAU_FULLY_CONNECTED_AVEC_BIAIS,
                        "RN",
                        0.2,
                        3,
                        tabNbNeurones,
                        CalcSoftMax,CalcDeriveePartielleSoftMaxViaValSoftMax,
                        NULL,
                        CalcLogistique,
                        CalcDeriveeLogistiqueViaValLogistique,
                        CalcIdentite,
                        CalcDeriveeIdentite,
                        10,
                        &rn);

    /*
        Chargement des donnees en memoire vive
    */
    T_DONNEES_IRIS tabIris[NB_IRIS_APPRENTISSAGE];
    ChargeDonneesIris("./JeuxDeDonnees/iris_apprenti.txt", NB_IRIS_APPRENTISSAGE, tabIris);

    /*
        Lancement analyse
    */
    double seuilValCout = DBL_MAX ;
    long nbIteration = 0 ;
    long nbTotalIterations = 1000 ;



    while (rn.lfCoutCumule > seuilValCout && nbIteration < nbTotalIterations)
    {
        // Reset des variables
        InitAZeroGradientsPoidsCumules (&rn);

        // Injection d'un echantillon
        InjectionDonneesDansCoucheEntree (&(tabIris[i]))

        // Analyse predictive de l'echantillon
        CalcPredictionReseauNeurones
        RetroPropagationErreursEtGradients
        TabIrisApprentissage[liCompteurElt].cTypePredit = CalcIndiceMax
        FonctionCoutLogLoss
        CalcCorrectionPoidsSynaptiques

        nbIteration++;
    }

    return 0;
}
