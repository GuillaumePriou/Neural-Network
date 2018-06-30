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
#include "./BibliReseauNeurones/CalcMax.h"

int main()
{
    //executerTests();


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
    ChargeDonneesIris("./JeuxDeDonnees/iris/iris_apprenti.txt", NB_IRIS_APPRENTISSAGE, tabIris);

    /*
        Lancement analyse
    */
    double seuilValCout = DBL_MAX ;
    long nbIteration = 0 ;
    long nbTotalIterations = 1000 ;
	long echantillonAAnalyser;
    long echant=0; // "echantillon", iterateur pour les echantillons de donnees
    double coutLot ;


    while (rn.lfCoutCumule > seuilValCout && nbIteration < nbTotalIterations)
    {
        // Reset des variables
        InitAZeroGradientsPoidsCumules (&rn);
        rn.lfCoutCumule = 0;

        echantillonAAnalyser = nbIteration%NB_IRIS_APPRENTISSAGE;

        // Analyse d'un lot d'echantillons
        for (echant=0; echant<rn.usiNbLots; echant++)
        {
            // Injection d'un echantillon a analyser
            InjectionDonneesDansCoucheEntree (&(tabIris[echantillonAAnalyser]), &rn, 0,0);

            // Analyse predictive de l'echantillon
            CalcPredictionReseauNeurones (&rn);

            // Calcul des erreurs de prediction a partir des vraies valeurs
            InjectionVraieValeurDansReseauNeurones (&(tabIris[echantillonAAnalyser]), &rn, 0, 0);
            RetroPropagationErreursEtGradients (&rn);

            // Selection de la reponse la plus probable selon les analyses
            tabIris[echantillonAAnalyser].cTypePredit = CalcIndiceMax (rn.plfPredictionFinale, rn.pCouchesNeurones[rn.siNbCouches-1].siNbNeurones);

            // Calcul du cout des predictions
            FonctionCoutLogLoss (rn.plfVraieValeurFinale, rn.plfPredictionFinale, rn.pCouchesNeurones[rn.siNbCouches-1].siNbNeurones, &coutLot);
            rn.lfCoutCumule += coutLot;
        }

        CalcCorrectionPoidsSynaptiques (&rn, rn.usiNbLots); 


        nbIteration++;
    }

    return 0;
}
