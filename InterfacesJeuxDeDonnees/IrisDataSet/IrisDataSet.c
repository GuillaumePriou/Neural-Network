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
        char* ligne[TAILLE_TEXTE];
        int numLigneLu = 0;
        char* classeIris[20];

        while (fgets(ligne, TAILLE_TEXTE, fichier) != NULL)
        {
            sscanf(ligne,
                   "%lf,%lf,%lf,%lf,%s",
                   &(tabIris[numLigneLu].lfLongueur),
                   &(tabIris[numLigneLu].lfLargeur),
                   &(tabIris[numLigneLu].lfLongueurSepal),
                   &(tabIris[numLigneLu].lfLargeurSepal),
                   &classeIris
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
