#include "TestsUnitaires.h"
#include "../BibliReseauNeurones/Neurone.h"
#include "../BibliReseauNeurones/Activation.h"
#include "../BibliReseauNeurones/CoucheNeurone.h"
#include "../BibliReseauNeurones/TypeReseauNeurones.h"
#include "../BibliReseauNeurones/ReseauNeurone.h"
#include <string.h>


/***********************************************************
                NEURONES
***********************************************************/

T_NEURONE tabNeuroneCoucheEntree[3] = {
                                        {
                                            NEURONE_DE_BIAIS,
                                            0,
                                            NULL,
                                            NULL,
                                            CalcIdentite,
                                            CalcDeriveeIdentite
                                        },
                                        {
                                            NEURONE_D_ENTREE,
                                            0,
                                            NULL,
                                            NULL,
                                            CalcIdentite,
                                            CalcDeriveeIdentite
                                        },
                                        {
                                            NEURONE_D_ENTREE,
                                            0,
                                            NULL,
                                            NULL,
                                            CalcIdentite,
                                            CalcDeriveeIdentite
                                        }
                                    };

T_NEURONE tabNeuroneCoucheCachee[4] = {
                                            {
                                                NEURONE_DE_BIAIS,
                                                0,
                                                NULL,
                                                NULL,
                                                CalcIdentite,
                                                CalcDeriveeIdentite
                                            },
                                            {
                                                NEURONE_CACHE,
                                                3,
                                                {0,1,2},
                                                {0,0,0},
                                                CalcLogistique,
                                                CalcDeriveeLogistiqueViaValLogistique
                                                //Neurone 1
                                            },
                                            {
                                                NEURONE_CACHE,
                                                3,
                                                {4,5,6},
                                                {0,0,0},
                                                CalcLogistique,
                                                CalcDeriveeLogistiqueViaValLogistique
                                                //Neurone 2
                                            },
                                            {
                                                NEURONE_CACHE,
                                                3,
                                                {8,9,10},
                                                {0,0,0},
                                                CalcLogistique,
                                                CalcDeriveeLogistiqueViaValLogistique
                                                //Neurone 3
                                            }
                                        };
T_NEURONE tabNeuroneCoucheSortie[3] =
                                        {
                                            {
                                                NEURONE_DE_BIAIS,
                                                4,
                                                {16,17,18,19},
                                                {0,0,0,0},
                                                CalcLogistique,
                                                CalcDeriveeLogistiqueViaValLogistique
                                            },
                                            {
                                                NEURONE_DE_SORTIE,
                                                4,
                                                {20,21,22,23},
                                                {0,0,0,0},
                                                CalcLogistique,
                                                CalcDeriveeLogistiqueViaValLogistique
                                            },
                                            {
                                                NEURONE_DE_SORTIE,
                                                4,
                                                {24,25,26,27},
                                                {0,0,0,0},
                                                CalcLogistique,
                                                CalcDeriveeLogistiqueViaValLogistique
                                            }
                                        };

/***********************************************************
                COUCHES NEURONES
***********************************************************/

T_COUCHE_NEURONES coucheNeuroneEntree =  {
                                            COUCHE_ENTREE,
                                            "Couche d'entree",
                                            NULL,
                                            NULL,
                                            NULL,
                                            3,
                                            0,
                                            tabNeuroneCoucheEntree,
                                            {0,0,0},
                                            {0,0,0},
                                         };

T_COUCHE_NEURONES coucheNeuroneCachee = {
                                            COUCHE_CACHEE,
                                            "Couche cachee",
                                            &coucheNeuroneEntree,
                                            NULL,
                                            NULL,
                                            4,
                                            coucheNeuroneEntree.siNbNeurones,
                                            tabNeuroneCoucheCachee,
                                            {0,0,0,0},
                                            {0,0,0,0}
                                        };

T_COUCHE_NEURONES coucheNeuroneSortie = {
                                            COUCHE_SORTIE,
                                            "Couche sortie",
                                            &coucheNeuroneCachee,
                                            CalcSoftMax,
                                            CalcDeriveePartielleSoftMaxViaValSoftMax,
                                            3,
                                            coucheNeuroneCachee.siNbNeurones,
                                            tabNeuroneCoucheSortie,
                                            {0,0,0},
                                            {0,0,0}
                                        };

T_COUCHE_NEURONES tabCoucheNeurones[3] = {
                                            coucheNeuroneEntree,
                                            coucheNeuroneCachee,
                                            coucheNeuroneSortie
                                         };

/***********************************************************
                RESEAU NEURONES
***********************************************************/

T_RESEAU_NEURONES reseauNeurone = {
                                        RESEAU_FULLY_CONNECTED_AVEC_BIAIS,
                                        "Reseau de neurones",
                                        0.3,
                                        3,
                                        tabCoucheNeurones,
                                        {0,0,0},
                                        {0,0,0},
                                        0,
                                        3
                                  };
