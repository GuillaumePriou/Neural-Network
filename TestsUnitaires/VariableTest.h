#include "TestsUnitaires.h"
#include "../BibliReseauNeurones/Neurone.h"
#include "../BibliReseauNeurones/Activation.h"
#include "../BibliReseauNeurones/CoucheNeurone.h"
#include "../BibliReseauNeurones/TypeReseauNeurones.h"
#include "../BibliReseauNeurones/ReseauNeurone.h"
#include <string.h>

/***********************************************************
                plfOutputSamples COUCHES NEURONES
***********************************************************/

REEL plfOutputSamplesCE[] = {0,0,0} ;
REEL plfOutputSamplesCC[] = {0,0,0,0} ;
REEL plfOutputSamplesCS[] = {0,0,0} ;

/***********************************************************
                plfErreurDeltaSample COUCHES NEURONES
***********************************************************/

REEL plfErreurDeltaSampleCE[] = {0,0,0} ;
REEL plfErreurDeltaSampleCC[] = {0,0,0,0} ;
REEL plfErreurDeltaSampleCS[] = {0,0,0} ;

/***********************************************************
                COEFFICIENTS NEURONES
***********************************************************/

// tab [couche][neurone][coefficient]
REEL tabCoefs[3][4][4]=
    {
         {  // couche ZERO (entree)
             { 0.0      , 0.0      ,  0.0      } ,
             { 0.0      , 0.0      ,  0.0      } ,
             { 0.0      , 0.0      ,  0.0      }
         } ,
           {  // couche UN (cachee)
               { 0.0      , 0.0      ,  0.0      } ,
               { 0.194711 , 0.103084 ,  0.305393 } ,
               { -0.301374 , -0.216167 ,  0.393302 }
           } ,
           {  // couche DEUX (sortie)
               { 0.431965 , 0.447154 , -0.373282 } ,
               { 0.421330 , 0.480866 , -0.406068 } ,
               {  0.352279 ,  0.576163 , -0.418742 }
           }
    } ;
        /*{
            { // Couche entree => neurones a 0 dendrites
                { 0.0,  0.0,  0.0,  0.0},
                { 0.0,  0.0,  0.0,  0.0},
                { 0.0,  0.0,  0.0,  0.0},
                { 0.0,  0.0,  0.0,  0.0}
            },
            { // Couche cachee
                { 0.0,  0.0,  0.0,  0.0}, // Neurone de biais
                {11.0, 12.0, 13.0, 14.0},
                {15.0, 16.0, 17.0, 18.0},
                {19.0, 11.0, 12.0, 13.0}
            },
            { // Couche sortie
                {21.0, 22.0, 23.0, 24.0},
                {25.0, 26.0, 27.0, 28.0},
                {29.0, 21.0, 22.0, 23.0},
                { 0.0,  0.0,  0.0,  0.0} // Seulement 3 neurones de sortie
            },
        };*/

/***********************************************************
                GRADIENTS NEURONES
***********************************************************/

// tab [couche][neurone][coefficient]
REEL tabGradients[3][4][4]= {0};
       /* {
            { // Couche entree => neurones a 0 dendrites
                { 0,  0,  0,  0},
                { 0,  0,  0,  0},
                { 0,  0,  0,  0},
                { 0,  0,  0,  0}
            },
            { // Couche cachee
                { 0,  0,  0,  0}, // Neurone de biais
                {11, 12, 13, 14},
                {15, 16, 17, 18},
                {19, 11, 12, 13}
            },
            { // Couche sortie
                {21, 22, 23, 24},
                {25, 26, 27, 28},
                {29, 21, 22, 23},
                { 0,  0,  0,  0} // Seulement 3 neurones de sortie
            },
        };*/


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
                                                &(tabCoefs[1][1][0]),
                                                &(tabGradients[1][1][0]),
                                                CalcLogistique,
                                                CalcDeriveeLogistiqueViaValLogistique
                                                //Neurone 1
                                            },
                                            {
                                                NEURONE_CACHE,
                                                3,
                                                &(tabCoefs[1][2][0]),
                                                &(tabGradients[1][2][0]),
                                                CalcLogistique,
                                                CalcDeriveeLogistiqueViaValLogistique
                                                //Neurone 2
                                            },
                                            {
                                                NEURONE_CACHE,
                                                3,
                                                &(tabCoefs[1][3][0]),
                                                &(tabGradients[1][3][0]),
                                                CalcLogistique,
                                                CalcDeriveeLogistiqueViaValLogistique
                                                //Neurone 3
                                            }
                                        };

T_NEURONE tabNeuroneCoucheSortie[3] =
                                        {
                                            {
                                                NEURONE_DE_SORTIE,
                                                4,
                                                &(tabCoefs[2][0][0]),
                                                &(tabGradients[2][0][0]),
                                                CalcLogistique,
                                                CalcDeriveeLogistiqueViaValLogistique
                                            },
                                            {
                                                NEURONE_DE_SORTIE,
                                                4,
                                                &(tabCoefs[2][1][0]),
                                                &(tabGradients[2][1][0]),
                                                CalcLogistique,
                                                CalcDeriveeLogistiqueViaValLogistique
                                            },
                                            {
                                                NEURONE_DE_SORTIE,
                                                4,
                                                &(tabCoefs[2][2][0]),
                                                &(tabGradients[2][2][0]),
                                                CalcLogistique,
                                                CalcDeriveeLogistiqueViaValLogistique
                                            }
                                        };

/***********************************************************
                COUCHES NEURONES
***********************************************************/

#define VAR_COUCHE_ENTREE {                                             \
                                            COUCHE_ENTREE,          \
                                            "couche d'entree, indice 0",      \
                                            NULL,\
                                            NULL,\
                                            NULL,\
                                            3,\
                                            0,\
                                            tabNeuroneCoucheEntree,\
                                            plfOutputSamplesCE,\
                                            plfErreurDeltaSampleCE,\
                                         }

#define VAR_COUCHE_CACHEE {\
                                            COUCHE_CACHEE,\
                                            "couche cachee, indice 1",\
                                            &coucheNeuroneEntree,\
                                            NULL,\
                                            NULL,\
                                            4,\
                                            3,\
                                            tabNeuroneCoucheCachee,\
                                            plfOutputSamplesCC,\
                                            plfErreurDeltaSampleCC\
                                        }

#define VAR_COUCHE_SORTIE  {\
                                            COUCHE_SORTIE,\
                                            "couche de sortie, indice 2",\
                                            &coucheNeuroneCachee,\
                                            CalcSoftMax,\
                                            CalcDeriveePartielleSoftMaxViaValSoftMax,\
                                            3,\
                                            4,\
                                            tabNeuroneCoucheSortie,\
                                            plfOutputSamplesCS,\
                                            plfErreurDeltaSampleCS\
                                        }


T_COUCHE_NEURONES coucheNeuroneEntree = VAR_COUCHE_ENTREE ;
T_COUCHE_NEURONES coucheNeuroneCachee = VAR_COUCHE_CACHEE ;
T_COUCHE_NEURONES coucheNeuroneSortie = VAR_COUCHE_SORTIE ;

T_COUCHE_NEURONES tabCoucheNeurones[3] = {
                                            VAR_COUCHE_ENTREE,
                                            VAR_COUCHE_CACHEE,
                                            VAR_COUCHE_SORTIE
                                         };

/***********************************************************
                RESEAU NEURONES
***********************************************************/

REEL plfPredictionFinaleRN[] = {0,0,0};
REEL plfVraieValeurFinaleRN[] = {0,0,0};
short int tabsiNbNeuronesRN[3] = {3,4,3};
T_RESEAU_NEURONES reseauNeurone = {
                                        RESEAU_FULLY_CONNECTED_AVEC_BIAIS,
                                        "Reseau de neurones",
                                        0.3,
                                        3,
                                        tabCoucheNeurones,
                                        plfPredictionFinaleRN,
                                        plfVraieValeurFinaleRN,
                                        0,
                                        3
                                  };
