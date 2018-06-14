/*******************************************************************
                              ACTIVATION.H
                 Definition des fonctions d'activation
                       scalaires et vectorielles
                 utilisees par les reseaux de neurones
*******************************************************************/

#ifndef ACTIVATION_H_INCLUDED
#define ACTIVATION_H_INCLUDED

#include "constantes.h"

/***************************************************
         Fonctions d'activation scalaires
***************************************************/

/***************************************************
      Definition du type fonction d'activation
 Cette fonction prend un argument lfX (REEL) et
 retourne un resultat de type REEL

 **************************************************/
typedef REEL T_FONCTION_ACTIVATION ( REEL lfX ) ;

/***************************************************
                 Fonction logistique
          sortie comprise entre 0.0 et +1.0
***************************************************/
T_FONCTION_ACTIVATION CalcLogistique ;
T_FONCTION_ACTIVATION CalcDeriveeLogistiqueViaValLogistique ;

/***************************************************
            Fonction tangente hyperbolique
          sortie comprise entre -1.0 et +1.0
***************************************************/
T_FONCTION_ACTIVATION CalcTanHyperbolique ;
T_FONCTION_ACTIVATION CalcDeriveeTanHyperboliqueViaValTanHyperbolique ;

/***************************************************
                 Fonction ReLU
          sortie comprise entre 0.0 et +1.0
***************************************************/
T_FONCTION_ACTIVATION CalcReLU ;
T_FONCTION_ACTIVATION CalcDeriveeReLU ;

/***************************************************
                 Fonction Identite
***************************************************/
T_FONCTION_ACTIVATION CalcIdentite ;
T_FONCTION_ACTIVATION CalcDeriveeIdentite ;

/***************************************************
         Fonction "echelon" de HeavisideZero
       sortie comprise entre 0.0 et +1.0
***************************************************/
T_FONCTION_ACTIVATION CalcHeavisideZero ;
T_FONCTION_ACTIVATION CalcDeriveeHeavisideZero ;

/***************************************************
         Fonction "echelon" de HeavisideMoinsUn
       sortie comprise entre -1.0 et +1.0
***************************************************/
T_FONCTION_ACTIVATION CalcHeavisideMoinsUn ;
T_FONCTION_ACTIVATION CalcDeriveeHeavisideMoinsUn ;

/***************************************************
         Fonctions d'activation vectorielles
***************************************************/
/***************************************************
      Definition du type fonction d'activation
 Cette fonction prend en argument :
 * un tableau TablfX (REEL) comportant siNbElts
 * il faut fournir (si on calcule une derivee partielle)
   un autre indice (siIndiceDeriveePartielle) identifiant
   la variable par rapport a laquelle il faut deriver

 La fonction calcule l'image de tablfX[i] par application
 de SoftMax (ou de sa derivee partielle par rapport a l'element
 d'indice siIndiceDeriveePartielle) et la stocke dans tablfResult[i]

 Cette fonction retourne un resultat de type ERREUR
 (0 = tout est OK)
 **************************************************/
typedef T_ERREUR T_FONCTION_ACTIVATION_VECTORIELLE ( REEL      * tablfX                   ,
                                                     short int   siNbElts                 ,
                                                     REEL      * tablfResult              ,
                                                     short int   siIndiceDeriveePartielle ) ;

/***************************************************
                 Fonction SoftMax
         sortie comprise entre 0.0 et +1.0
***************************************************/
T_FONCTION_ACTIVATION_VECTORIELLE CalcSoftMax ;
T_FONCTION_ACTIVATION_VECTORIELLE CalcDeriveePartielleSoftMaxViaValSoftMax ;
/*
T_ERREUR CalcSoftMax( REEL      * tablfX                   ,
                      short int   siNbElts                 ,
                      REEL      * tablfResult              ,
                      short int   siIndiceDeriveePartielle ) ;

T_ERREUR CalcDeriveePartielleSoftMaxViaValSoftMax ( REEL      * tablfX                   ,
                                                    short int   siNbElts                 ,
                                                    REEL      * tablfResult              ,
                                                    short int   siIndiceDeriveePartielle ) ;
*/
#endif // ACTIVATION_H_INCLUDED

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
