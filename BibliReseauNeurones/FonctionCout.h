/******************************************************
                    FONCTIONSCOUT.H
              Fonctions de cout utilisees
******************************************************/

#ifndef FONCTIONCOUT_H_INCLUDED
#define FONCTIONCOUT_H_INCLUDED

#include "constantes.h"

/*****************************************************
defintions explicites du ZERO et du UN utilise dans ce code
car on procedera a des tests d'egalite entre REEL ce qui n'est
pas souhaitable en general mais semble acceptable ici
*****************************************************/
#define ZERO ((REEL) 0.0)
#define UN   ((REEL) 1.0)

/****************************************************
      Definition d'un type de fonction de cout
****************************************************/

typedef T_ERREUR T_FONCTION_COUT ( REEL      * tablfValeursVraies   ,
                                   REEL      * tablfValeursEstimees ,
                                   short int   siNbElts             ,
                                   REEL      * plfCout              ) ;

/******************************************************
                    FonctionCoutLogLoss
    Fonction de cout Log Loss utilisee pour determiner
    a quelle une classe parmi siNbElts possibilites
               appartient un echantillon
(utilisation conjointe a la fonction d'activation SoftMax)
ENTREE :
- tableau contenant les vraies valeurs :
  tablfValeursVraies[i] = 1.0 si vraie valeur = i
                        = 0.0 sinon
- tableau des probabilites pour que l'echantillon appartienne
  a la classe i (tablfValeursEstimees[i])
- nombre de classes possibles (siNbElts), egal a la taille
  des deux vecteurs tablfValeursVraies et tablfValeursEstimees
SORTIE :
- le cout associe logloss (*plfCout)
ERREUR :
PAS_D_ERREUR = ok
ERREUR_LOGLOSS = toutes les composantes du vecteur des vraies valeurs
sont nulles (il en faudrait une seule non nulle et meme egale a UN)
******************************************************/

T_ERREUR FonctionCoutLogLoss ( REEL      * tablfValeursVraies   ,
                               REEL      * tablfValeursEstimees ,
                               short int   siNbElts             ,
                               REEL      * plfCout              ) ;

/******************************************************
                    FonctionCoutLogLossBinaire
    Fonction de cout Log Loss utilisee pour determiner
    si un echantillon appartient bie na une classe binaire

ENTREE :
- la vraie valeur :
  *lfValeursVraies = 1.0 si vraie valeur = i
                   = 0.0 sinon
- probabilite pour que l'echantillon appartienne
  a la classe binaire recherchee (*plfValeursEstimees)
SORTIE :
- le cout associe logloss (*plfCout)
ERREUR :
PAS_D_ERREUR = ok
******************************************************/

T_ERREUR FonctionCoutLogLossBinaire ( REEL      * plfValeurVraie   ,
                                      REEL      * plfValeurEstimee ,
                                      short int   siParam          ,
                                      REEL      * plfCout          ) ;

/******************************************************
                    FonctionCoutErrQuadra
        Fonction de cout Erreur quadratique utilisee
                       pour determiner
      a quelle une classe parmi siNbElts possibilites
                  appartient un echantillon
(utilisation conjointe a la fonction d'activation SoftMax)
ENTREE :
- tableau contenant les vraies valeurs (tablfValeursVraies)
- tableau des probabilites pour que l'echantillon appartienne
  a la classe i (tablfValeursEstimees[i])
- nombre de classes possibles (siNbElts), egal a la taille
  des deux vecteurs tablfValeursVraies et tablfValeursEstimees
SORTIE :
- le cout quadratique associe (*plfCout)
ERREUR :
PAS_D_ERREUR = ok
******************************************************/

T_ERREUR FonctionCoutErrQuadra ( REEL      * tablfValeursVraies   ,
                                 REEL      * tablfValeursEstimees ,
                                 short int   siNbElts             ,
                                 REEL      * plfCout              ) ;


#endif // FONCTIONCOUT_H_INCLUDED

/******************************************************
                    FIN DU COMPOSANT
******************************************************/
