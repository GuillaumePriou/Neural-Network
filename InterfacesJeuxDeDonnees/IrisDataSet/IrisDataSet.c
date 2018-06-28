/*******************************************************************
                              IrisDataSet.C
               Definition des types et des fonctions de traitement
                        dediees a l'iris data set

                        IRIS DATA SET : Fisher (1936)

CONTENU :
150 echantillons contenant cinq donnees :
- longueur, largeur de petale
- longueur, largeur de sepale
- type de l'iris (setosa, versicolor, virginica)

PAGE WEB : archive.ics.edu/ml/datasets/iris
*******************************************************************/

#include "IrisDataSet.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

T_ERREUR ChargeDonneesIris ( char      * szNomFichier ,
                             short int   siNb_Elts    ,
                             void      * TabDonnees   )
{
    T_DONNEES_IRIS* tabIris = (T_DONNEES_IRIS*)TabDonnees;
    FILE* fichier = NULL;
    fichier = fopen(szNomFichier, "r");
    if (fichier != NULL)
    {
        char ligne[TAILLE_TEXTE];
        int numLigneLu = 0;
        char classeIris[20];

        while (fgets(ligne, TAILLE_TEXTE, fichier) != NULL)
        {
            sscanf(ligne,
                   "%lf,%lf,%lf,%lf,%s",
                   &(tabIris[numLigneLu].lfLongueur),
                   &(tabIris[numLigneLu].lfLargeur),
                   &(tabIris[numLigneLu].lfLongueurSepal),
                   &(tabIris[numLigneLu].lfLargeurSepal),
                   classeIris
                   );
            if(strcmp(classeIris, "Iris-setosa") == 0)
                tabIris[numLigneLu].cType = 0;
            else if(strcmp(classeIris, "Iris-versicolor") == 0)
                tabIris[numLigneLu].cType = 1;
            else if(strcmp(classeIris, "Iris-virginica") == 0)
                tabIris[numLigneLu].cType = 2;
            else
                tabIris[numLigneLu].cType = 25;

            numLigneLu++;
        }
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier test.txt \n");
        return ERREUR_FICHIER_ECHEC_OUVERTURE;
    }
    return PAS_D_ERREUR;
}



T_ERREUR AfficheDonneesIris ( char          * szTexte      ,
                              long int        liNbElts     ,
                              void          * TabDonnees   ,
                              short int       AfficheProba ,
                              unsigned char   cTypeCherche )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR PredictionNeuroneJeuDeDonnees ( long int        liNbElts     ,
                                         void          * TabDonnees   ,
                                         T_NEURONE       LeNeurone    ,
                                         unsigned char   cTypeCherche )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR ApprentissageNeuroneJeuDeDonnees ( long int        liNbElts     ,
                                            void          * TabDonnees   ,
                                            T_NEURONE     * pNeurone     ,
                                            unsigned char   cTypeCherche )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR TestePredictionUnNeuroneIrisDataSet ( void )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR TesteApprentissageUnNeuroneIrisDataSet ( void )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR InjectionDonneesDansCoucheEntree ( void              * pDonnees        ,
                                            T_RESEAU_NEURONES * pReseauNeurone  ,
                                            short int           siParamUn       ,
                                            long int            liParamDeux     )
{
    T_DONNEES_IRIS * pDonneesIris ;
    pDonneesIris = (T_DONNEES_IRIS *) pDonnees ;

    /* neurone de biais */
    pReseauNeurone->pCouchesNeurones[0].plfOutputSample[0] = 1.0 ;
    /* longueur petale Iris */
    pReseauNeurone->pCouchesNeurones[0].plfOutputSample[1] = pDonneesIris->lfLongueur ; /* L petale */ /* data retenu comme premiere variable */
    /* largeur petale iris */
    pReseauNeurone->pCouchesNeurones[0].plfOutputSample[2] = pDonneesIris->lfLargeur ; /* l petale */ /* data retenu comme seconde variable */

    return PAS_D_ERREUR ;
}

T_ERREUR InjectionVraieValeurDansReseauNeurones ( void              * pDonnees        ,
                                                  T_RESEAU_NEURONES * pReseauNeurone  ,
                                                  short int           siParamUn       ,
                                                  long int            liParamDeux     )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR TestePredictionPerceptronIrisDataSet ( void )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR PredictionPerceptronJeuDeDonnees ( long int            liNbElts     ,
                                            void              * TabDonnees   ,
                                            T_RESEAU_NEURONES   LePMC_XOR    ,
                                            unsigned char       cTypeCherche )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR TestePrediction3Couches3NeuronesIrisDataSet ( void )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR Prediction3Couches3NeuronesJeuDeDonnees ( long int            liNbElts     ,
                                                   void              * TabDonnees   ,
                                                   T_RESEAU_NEURONES   LeReseau3c3n )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR TesteApprentissage3Couches3NeuronesIrisDataSet ( void )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR Apprentissage3Couches3NeuronesJeuDeDonnees ( long int            liNbElts        ,
                                                      void              * TabDonnees      ,
                                                      T_RESEAU_NEURONES * pReseauNeurones ,
                                                      unsigned char       cParam          )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}
