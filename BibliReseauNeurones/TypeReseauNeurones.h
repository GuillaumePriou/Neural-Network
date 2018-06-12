/*******************************************************************
                          TYPERESEAUNEURONE.H
                Definition des types "reseaux de neurones"

*******************************************************************/
#ifndef TYPERESEAUNEURONES_H_INCLUDED
#define TYPERESEAUNEURONES_H_INCLUDED

#include "CoucheNeurone.h"

/* les differents types de reseau de neurones */
typedef enum
{
 RESEAU_NON_INITIALISE             = -1 ,
 RESEAU_FULLY_CONNECTED_AVEC_BIAIS =  0
} T_TYPE_RESEAU_NEURONES ;

/***************************************************
              Definition d'un reseau de neurones
On suppose qu'il possede :
- un type de reseau (typeReseauNeurones) :
  RESEAU_FULLY_CONNECTED
- un texte descriptif succinct (szDescription)
- le taux d'apprentissage (lfTauxApprentissage)
- le nombre de couches (siNbCouches)
- un tableau de couches de neurones (pCouchesNeurones)
- un tableau contenant les prediction finales du reseau pour un echantillon donne
  (plfPredictionFinale), dont le nombre d'elements = nombre de neurones de la couche de sortie
- un tableau contenant, pour un echantillon donne, la liste des vraies
  valeurs associees aux donnees entrantes introduites dans la couche d'entree
  du reseau de neurones (les "y" vrais, sans chapeau : plfVraieValeurFinale).
  Leur nombre est egal au nombre de neurones de la couche de sortie
- La valeur cumulee du cout sur tous les echantillons (lfCoutCumule)
- un tableau a trois dimensions contenant les gradients cumules de la fonction d'erreur
  par rapport aux poids synaptiques :
  pGradientsPoidsCumules[iCouche][jNeurone][kDendrite]
     = gradient cumule a appliquer dans la couche iCouche, au poids de la dendrite kDendrite du neurone jNeurone
     = correction a appliquer au poids w_{kDendrite,jNeurone} reliant le neurone kDendrite de la couche (iCouche-1)
       et le neurone jNeurone de la couche iCouche. !!!!!!!!!!!!!!!!!! ATTENTION   !!!!!!!!!!!!!!!!!
  L'indice iCouche varie de 1 a (nombre de couches - 1) car la couche 0 n'a pas de poids synaptique
  pGradientsPoidsCumules[iCouche] contient les poids reliant la couche iCouche a la couche precedente (iCouche-1)
  pGradientsPoidsCumules[iCouche][0] est inutile pour iCouche = 1, ..., (nombre de couches-2)
    car le neurone ZERO de ces couches (cachees) est un neurone de biais (qui n'a pas de dendrite)
  pGradientsPoidsCumules[0] = NULL car les neurones de la couche d'entree n'ont pas de dendrite
- nombre de lot eventuel si traitement par batch pour un apprentissage stochastique  (usiNbLots)
  si usiNbLots < 2 on traite tout le jeu de donnees dans chaque passe d'apprentissage
  si usiNbLots = 2, 3, ..., on divise le jeu de donnees en usiNbLots
     de taille = (taille du jeu de donnees) / usiNbLots
  remarque : il est preferable que usiNbLots soit un diviseur de la taille du jeu de donnees
***************************************************/

typedef struct TagReseauNeurone
{
    T_TYPE_RESEAU_NEURONES              typeReseauNeurones            ;
    char                                szDescription[TAILLE_TEXTE+1] ;
    REEL                                lfTauxApprentissage           ;
    short int                           siNbCouches                   ;
    T_COUCHE_NEURONES                 * pCouchesNeurones              ;
    REEL                              * plfPredictionFinale           ;
    REEL                              * plfVraieValeurFinale          ;
    REEL                                lfCoutCumule                  ;
    unsigned short int                  usiNbLots                     ;
} T_RESEAU_NEURONES ;

#endif // TYPERESEAUNEURONES_H_INCLUDED

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
