/*******************************************************************
                              NEURONE.H
                 Definition des types de neurones
              et des fonctions de gestion associées
*******************************************************************/
#ifndef NEURONE_H_INCLUDED
#define NEURONE_H_INCLUDED

#include <stdio.h>

#include "constantes.h"
#include "Activation.h"

/***************************************************
              Definition d'un neurone
On suppose qu'il possede :
- siNbDendrites dendrites
- un vecteur des poids tablfPoids
  (en nombre egal a siNbDendrites)
- un vecteur des gradients tablfGradients
(un gradient par coefficient)
- une fonction d'activation
- une fonction donnant la valeur de la derivee de la
  fonction d'activation en fonction de la valeur de
  la fonction d'activation (et non de x)

IMPORTANT : si le neurone se trouve dans une couche de sortie,
            sa fonction d'activation n'est pas prise en compte
            (la couche de sortie garde ce parametre en son sein)
***************************************************/
typedef struct TagNeurone
{
    short int               siNbDendrites ;
    REEL                  * tablfPoids ;
    REEL                  * tablfGradients;
    T_FONCTION_ACTIVATION * F_Activation ;
    T_FONCTION_ACTIVATION * F_DeriveeActivation ;
} T_NEURONE ;

/***************************************************
           Initialisation d'un neurone
ENTREE :
- Nombre de dendrites (siNbDendrites)
    Valeur minimum : 1
- tableau des siNbDendrites poids (tablfPoids)
- la fonction d'activation (Fonction_Activation)
- la derivee de la fonction d'activation (Fonction_Derivee_Activation)
SORTIE :
- Le Neurone initialise (pointeur pNeurone)
VALEUR RETOURNEE :
PAS_D_ERREUR = tout est ok
ERREUR_ALLOCATION_MEMOIRE_NEURONE = pb d'allocation memoire

IMPORTANT : le pointeur pNeurone est suppose valide

Si le tableau tablfPoids d'initialisation des poids est NULL,
on initialise tous les poids a la valeur par defaut : VAL_POIDS_DEFAUT

Note :
    La creation d'un neurone est comosee de 4 etapes :
    1. Allouer la memoire au neurone, sauf pour ses coefficients
       (stockes dans une autre variable tableau de taille variable)
    2. Initialiser les parametres du neurone (hors coefficients)
    3. Allouer la memoire pour les coefficients du neurone
    4. Allouer la memoire pour les gradients (correction des coeffs) du neurone
    5. Initialiser les coefficients
    6. Initialisation du tableau de gradient à 0

    InitNeurones ne gère que les etapes 2 à 6. L'etape 1 est geree
    par la fonction appelant InitNeurone (InitCouche typiquement)

***************************************************/

T_ERREUR InitNeurone ( short int               siNbDendrites               ,
                       REEL                  * tablfPoids                  ,
                       T_FONCTION_ACTIVATION * Fonction_Activation         ,
                       T_FONCTION_ACTIVATION * Fonction_Derivee_Activation ,
                       T_NEURONE             * pNeurone                    ) ;

/***************************************************
           Desinitialisation d'un neurone
ENTREE :
- LeNeurone a desinitialiser :
SORTIE :
PAS_D_ERREUR = OK
***************************************************/

T_ERREUR DesinitNeurone ( T_NEURONE * pNeurone ) ;

/***************************************************
           Affichage d'un neurone
ENTREE :
- LeNeurone a afficher
SORTIE :
PAS_D_ERREUR = OK
***************************************************/

T_ERREUR AfficheNeurone ( T_NEURONE LeNeurone ) ;

/***************************************************
    Sauvegarde des caracteristiques d'un neurone
              dans un fichier texte
ENTREE :
- LeNeurone a sauvegarder
- le nom du fichier texte de sauvegarde (szNomFic)
- un texte libre a sauvegarder dans le fichier avant toute chose, pour information (szTexte)
SORTIE :
PAS_D_ERREUR = OK
ERREUR_FICHIER_ECHEC_CREATION = le fichier de sauvegarde ne peut etre cree
ERREUR_FICHIER_ECHEC_ECRITURE = echec ecriture dans le fichier
***************************************************/

T_ERREUR SauveFicTexteNeurone ( T_NEURONE   LeNeurone ,
                                char      * szNomFic  ,
                                char      * szTexte   ) ;

/***************************************************
    Sauvegarde des caracteristiques d'un neurone
              dans un fichier binaire
ENTREE :
- LeNeurone a sauvegarder
- le nom du fichier binaire de sauvegarde (szNomFic)
- une cle 4 octets permettant de reconnaitre l'origine du fichier
SORTIE :
PAS_D_ERREUR = OK
ERREUR_FICHIER_ECHEC_CREATION = le fichier de sauvegarde ne peut etre cree
ERREUR_FICHIER_ECHEC_ECRITURE = echec ecriture dans le fichier

ATTENTION : on ne sauvergarde que les informations suivantes :
1/ le cle numérique (long int)
2/ le nombre de dendrites (short int)
3/ le tableau des poids synaptiques
soit au total : 4 + 2 + (nombre de dendrites) * sizeof(REEL)
Les autres donnees contenues dans LeNeurone sont des pointeurs (pas de serialisation)
***************************************************/

T_ERREUR SauveFicBinaireNeurone ( T_NEURONE   LeNeurone    ,
                                  char      * szNomFic     ,
                                  long int    liCleMagique ) ;

/***************************************************
    Lecture des caracteristiques d'un neurone
              dans un fichier binaire
ENTREE :
- LeNeurone a initialiser
- le nom du fichier binaire de lecture (szNomFic)
- une cle magique de 4 octets permettant de reconnaitre l'origine du fichier
SORTIE :
PAS_D_ERREUR = OK
ERREUR_FICHIER_ECHEC_OUVERTURE = le fichier a lire ne peut etre ouvert
ERREUR_FICHIER_ECHEC_LECTURE = echec lecture dans le fichier
ERREUR_FICHIER_MAUVAISE_CLE_MAGIQUE = la cle magique n'est pas la bonne
ERREUR_NB_DENDRITES = nombre de dendrites incorrect
ERREUR_POINTEUR_NON_INITIALISE = pointeur sur le tableau des poids non initialise

ATTENTION : on ne lit que les informations suivantes :
1/ le cle numérique (long int)
2/ le nombre de dendrites (short int)
3/ le tableau des poids synaptiques
soit au total : 4 + 2 + (nombre de dendrites) * sizeof(REEL)
Les autres donnees contenues dans LeNeurone sont des pointeurs et supposees
etre valides (pas de serialisation)
On suppose que le tableau des poids a la bonne taille par rapport au nombre
de dendrites lu dans la fichier (information 2/)
***************************************************/

T_ERREUR ChargeFicBinaireNeurone ( T_NEURONE * pNeurone     ,
                                   char      * szNomFic     ,
                                   long int    liCleMagique ) ;

/***************************************************
                 CalcPredictionNeurone
  Calcul d'une prediction grace a UN SEUL neurone

ENTREE :
- tableau des valeurs d'entree (tablfX), de taille siNbElts
- le neurone utilise pour la prediction (LeNeurone)
SORTIE :
- valeur predite (plfPrediction)
VALEUR RETOURNEE :
PAS_D_ERREUR = OK
ERREUR_NB_DENDRITES = la taille du tableau tablfX
                      differe du nombre de dendrites
***************************************************/

T_ERREUR CalcPredictionNeurone ( REEL      * tablfX        ,
                                 short int   siNbElts      ,
                                 T_NEURONE   LeNeurone     ,
                                 REEL      * plfPrediction ) ;



/***************************************************
                 CmpNeurone
  Compare deux neurones

ENTREE :
- Neurone 1
- Neurone 2
SORTIE :
- Int 0 si égale, 1 sinon
VALEUR RETOURNEE :
PAS_D_ERREUR = OK
ERREUR_NB_DENDRITES = la taille du tableau tablfX
                      differe du nombre de dendrites
***************************************************/

short CmpNeurone ( T_NEURONE   LeNeuroneA ,
                   T_NEURONE   LeNeuroneB );

#endif // NEURONE_H_INCLUDED

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
