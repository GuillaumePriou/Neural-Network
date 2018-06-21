/*******************************************************************
                              NEURONE.C
                 Definition des types de neurones
              et des fonctions de gestion associ�es
*******************************************************************/
#include "Neurone.h"
#include <stdlib.h>

T_ERREUR InitNeurone ( T_TYPE_NEURONES         typeNeurone                 ,
                       short int               siNbDendrites               ,
                       REEL                  * tablfPoids                  ,
                       T_FONCTION_ACTIVATION * Fonction_Activation         ,
                       T_FONCTION_ACTIVATION * Fonction_Derivee_Activation ,
                       T_NEURONE             * pNeurone                    )
{
    int i = 0;

    // Verifions que le neurone a creer est bien determine
    if (typeNeurone == NEURONE_NON_INITIALISE)
        return ERREUR_NEURONE_MAL_INITIALISE ;


    // Si c'est un neurone d'entree ou de biais, verifions que :
    // - la fonction d'activition est la fonction identite
    // - on n'essaie pas de leur donner des dendrites
    if(  typeNeurone == NEURONE_DE_BIAIS
       ||typeNeurone == NEURONE_D_ENTREE)
    {
        if (  Fonction_Activation != CalcIdentite
            ||Fonction_Derivee_Activation != CalcDeriveeIdentite)
            return ERREUR_NEURONE_MAL_INITIALISE;
        else if (siNbDendrites != 0)
            return ERREUR_NB_DENDRITES;
        else if (tablfPoids != NULL)
            return ERREUR_NEURONE_MAL_INITIALISE;
    }


    // Remplissage du neurone avec les bonnes valeurs (etape 2)
    (*pNeurone).typeNeurone = typeNeurone;
    (*pNeurone).F_Activation = Fonction_Activation;
    (*pNeurone).F_DeriveeActivation = Fonction_Derivee_Activation;
    (*pNeurone).siNbDendrites = siNbDendrites;

    //   allocation memoire pour tableau de coefficients du neurone (etape 3)
    // & allocation memoire pour tableau de gradients du neurone (etape 4)
    if(  (*pNeurone).typeNeurone == NEURONE_DE_BIAIS
       ||(*pNeurone).typeNeurone == NEURONE_D_ENTREE)
    {
        (*pNeurone).tablfPoids = NULL;
        (*pNeurone).tablfGradients = NULL;
    }
    else
    {
        (*pNeurone).tablfPoids = malloc(siNbDendrites * sizeof(REEL));

        // Si erreur allocation memoire, retourner une erreur
        if((*pNeurone).tablfPoids == NULL)
            return ERREUR_ALLOCATION_MEMOIRE_NEURONE;

        (*pNeurone).tablfGradients = malloc(siNbDendrites * sizeof(REEL));

        if((*pNeurone).tablfGradients == NULL) // En cas de probleme d'allocation de memoire,
        {
            free((*pNeurone).tablfPoids);
            return ERREUR_ALLOCATION_MEMOIRE_NEURONE;
        } // return une erreur
    }

    // Remplissage du tableau de coefficients avec les bonnes valeurs (etape 5)
    if(tablfPoids == NULL) // Donner des coeff par defaut si aucune valeur donnee en parametre
        for(i = 0; i < siNbDendrites; i++)
            (*pNeurone).tablfPoids[i] = VAL_POIDS_DEFAUT;
    else{
         //si tab != null alors on r�cup�re les coeffs
        //printf("(*pNeurone).tablfPoids = %p\n",(*pNeurone).tablfPoids);
        //printf("(*pNeurone).tablfPoids[0] = %lf\n",(*pNeurone).tablfPoids[0]);
        //printf("tablfPoids[0] = %lf\n",tablfPoids[0]);
        for(i = 0; i < siNbDendrites; i++)
            (*pNeurone).tablfPoids[i] = tablfPoids[i];
    }




    // Initialisation du tableau de gradient a 0  (etape 6)
    for(i = 0; i < siNbDendrites; i++)
        (*pNeurone).tablfGradients[i] = 0;

    return PAS_D_ERREUR;
}

T_ERREUR DesinitNeurone ( T_NEURONE * pNeurone )
{
    (*pNeurone).typeNeurone = NEURONE_NON_INITIALISE;
    free((*pNeurone).tablfPoids );
    free( (pNeurone)->tablfGradients );

    (*pNeurone).tablfPoids = NULL;
    (*pNeurone).tablfGradients = NULL;

    (*pNeurone).siNbDendrites = 0;
    (*pNeurone).F_Activation = NULL;
    (*pNeurone).F_DeriveeActivation = NULL;

    return PAS_D_ERREUR;
}

T_ERREUR AfficheNeurone ( T_NEURONE LeNeurone )
{
    int i =0;

    printf("\t\t Neurone de type ");
    switch (LeNeurone.typeNeurone)
    {
        case NEURONE_NON_INITIALISE :   printf("non initialise\n");
                                        break;
        case NEURONE_CACHE :            printf("cache\n");
                                        break;
        case NEURONE_DE_BIAIS :         printf("biais\n");
                                        break;
        case NEURONE_D_ENTREE :         printf("entree\n");
                                        break;
        case NEURONE_DE_SORTIE :        printf("sortie\n");
                                        break;
        default :                       printf("[Erreur : donnee inconnue]\n");
                                        break ;
    }

    printf("\t\t Nombre dendrites : %hd \n", LeNeurone.siNbDendrites);

    printf("\t\t Les poids sont : \n");

    for(i = 0; i< LeNeurone.siNbDendrites; i++)
    {
        printf("\t\t Coefficient N %hd : %lf \n", i, LeNeurone.tablfPoids[i]);
    }

    return PAS_D_ERREUR;
}

T_ERREUR SauveFicTexteNeurone ( T_NEURONE   LeNeurone ,
                                char      * szNomFic  ,
                                char      * szTexte   )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR SauveFicBinaireNeurone ( T_NEURONE   LeNeurone    ,
                                  char      * szNomFic     ,
                                  long int    liCleMagique )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR ChargeFicBinaireNeurone ( T_NEURONE * pNeurone     ,
                                   char      * szNomFic     ,
                                   long int    liCleMagique )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}

T_ERREUR CalcPredictionNeurone ( REEL      * tablfX        ,
                                 short int   siNbElts      ,
                                 T_NEURONE * LeNeurone     ,
                                 REEL      * plfPrediction )
{
    short int i;
    REEL somme = 0;
    if(siNbElts != LeNeurone->siNbDendrites)
        return ERREUR_NB_DENDRITES;

    switch (LeNeurone->typeNeurone)
    {
        case NEURONE_DE_BIAIS:
                                *plfPrediction = 1;
                                break;
        case NEURONE_D_ENTREE:
                                break;
        case NEURONE_CACHE:
                                 for(i = 0; i<siNbElts; i++)
                                    somme += tablfX[i] * LeNeurone->tablfPoids[i];

                                *plfPrediction = LeNeurone->F_Activation(somme);
                                break;

        case NEURONE_DE_SORTIE:
                                for(i = 0; i<siNbElts; i++)
                                    somme += tablfX[i] * LeNeurone->tablfPoids[i];

                                *plfPrediction = somme;
                                break;

        default:
            return ERREUR_TYPE_NEURONE_INCONNU;
            break;
    }

    return PAS_D_ERREUR ;
}


short CmpNeurone ( T_NEURONE   LeNeuroneA ,
                   T_NEURONE   LeNeuroneB )
{
    if(    LeNeuroneA.typeNeurone != LeNeuroneB.typeNeurone
        || LeNeuroneA.siNbDendrites != LeNeuroneB.siNbDendrites
        || LeNeuroneA.F_Activation != LeNeuroneB.F_Activation
        || LeNeuroneA.F_DeriveeActivation != LeNeuroneB.F_DeriveeActivation )
      return 1;

    return 0;
}

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
