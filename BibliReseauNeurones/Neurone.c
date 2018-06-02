/*******************************************************************
                              NEURONE.C
                 Definition des types de neurones
              et des fonctions de gestion associées
*******************************************************************/
#include "Neurone.h"
#include <stdlib.h>

T_ERREUR InitNeurone ( short int               siNbDendrites               ,
                       REEL                  * tablfPoids                  ,
                       T_FONCTION_ACTIVATION * Fonction_Activation         ,
                       T_FONCTION_ACTIVATION * Fonction_Derivee_Activation ,
                       T_NEURONE             * pNeurone                    )
{
    int i = 0;
    printf ("\nFonction activation : %p\n",Fonction_Activation);
    printf ("\n(*pNeurone).F_Activation  : %p\n",(*pNeurone).F_Activation ); // Plante aussi

    // Meme les neurones de la couche d'entree ont au moins une dendrite
    if (siNbDendrites < 1)
        return ERREUR_NB_DENDRITES ;

    // Remplissage du neurone avec les bonnes valeurs (etape 2)
    printf ("A");
    (*pNeurone).F_Activation = Fonction_Activation; // Plante ici
    printf ("B");
    (*pNeurone).F_DeriveeActivation = Fonction_Derivee_Activation;
    printf ("C");
    (*pNeurone).siNbDendrites = siNbDendrites;

    //allocation mémoire pour tableau de coefficients du neurone (etape 3)
    (*pNeurone).tablfPoids = malloc(siNbDendrites * sizeof(REEL));

    if((*pNeurone).tablfPoids == NULL) // En cas de probleme d'allocation de memoire,
        return ERREUR_ALLOCATION_MEMOIRE_NEURONE; // return une erreur

    // Remplissage du tableau de coefficients avec les bonnes valeurs (etape 4)
    if(tablfPoids == NULL) // Donner des coeff par defaut si aucune valeur donnee en parametre
        for(i = 0; i < siNbDendrites; i++)
            (*pNeurone).tablfPoids[i] = VAL_POIDS_DEFAUT;
    else
        //si tab != null alors on récupère les coeffs
        for(i = 0; i < siNbDendrites; i++)
            (*pNeurone).tablfPoids[i] = tablfPoids[i];

    return PAS_D_ERREUR;
}

T_ERREUR DesinitNeurone ( T_NEURONE * pNeurone )
{
    free( (pNeurone)->tablfPoids );

    (*pNeurone).tablfPoids = NULL;

    (*pNeurone).siNbDendrites = 0;
    (*pNeurone).F_Activation = NULL;
    (*pNeurone).F_DeriveeActivation = NULL;

    return PAS_D_ERREUR;
}

T_ERREUR AfficheNeurone ( T_NEURONE LeNeurone )
{
    int i =0;

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
                                 T_NEURONE   LeNeurone     ,
                                 REEL      * plfPrediction )
{
    return ERREUR_FONCTION_NON_DEFINIE ;
}


short CmpNeurone ( T_NEURONE   LeNeuroneA ,
                   T_NEURONE   LeNeuroneB )
{
    if( LeNeuroneA.siNbDendrites != LeNeuroneB.siNbDendrites
        || LeNeuroneA.F_Activation != LeNeuroneB.F_Activation
        || LeNeuroneA.F_DeriveeActivation != LeNeuroneB.F_DeriveeActivation )
      return 1;

    int i;
    for (i=0; i<LeNeuroneA.siNbDendrites; i++)
        if(LeNeuroneA.tablfPoids[i] != LeNeuroneB.tablfPoids[i] )
            return 1;
    return 0;
}

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
