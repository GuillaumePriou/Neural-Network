/*******************************************************************
                              RESEAUNEURONE.H
Definition des fonctions de gestion des "reseaux de neurones"associées

*******************************************************************/
#ifndef RESEAUNEURONE_H_INCLUDED
#define RESEAUNEURONE_H_INCLUDED

#include "constantes.h"
#include "TypeReseauNeurones.h"
#include "../InterfaceNeuroneDataSet.h"
#include "FonctionCout.h"

/***************************************************
  Initialisation d'un reseau de neurones en couches
ENTREE :
- Type de reseau (typeReseauNeurones)
- texte descriptif (pszDescription de taille TAILLE_TEXTE-20)
- taux d'apprentissage (lfTauxApprentissage)
- nombre de couches (siNbCouches), suppose au moins egal a DEUX
 (1 couche d'entree, 1 couche de sortie) :
 * la couche d'entree a pour indice ZERO,
 * les eventuelles couches cachees ont pour indice UN a (siNbCouches-1)
 * la couche de sortie a pour indice (siNbCouches-1)
- un tableau tabsiNbNeurones contenant le nombre de neurones par couche
 (tabsiNbNeurones[i] = nombre de neurones de la couche i)
- fonction d'activation vectorielle (F_ActivationVectorielle), NULL si pas de fonction
- derivee de la fonction d'activation vectirielle (F_Derivee_ActivationVectorielle)
  NULL si pas de fonction
- matrice 3D des poids (mat3DlfPoids) :
  * mat3DlfPoids[i] contient la matrice 2D des poids synaptiques entre la couche (i-1) et la couche i
  * Par exemple, mat2DlfPoids[0] contient les poids des dendrites enter la couche d'entree (0)
  et la premiere couche cachee (ou la couche de sortie si pas de couche cachee)
  * Par exemple, mat3DlfPoids[siNbCouches-2] contient les poids des dendrites entre la derniere couche
  cachee (ou la couche d'entree si pas de couche cachee) (siNbCouches-2)
  et la  couche de sortie (siNbCouches-1)
  * mat3DlfPoids[i] est tel que i = 0, ..., (siNbCouches-2)
- la fonction d'activation des neurones caches (Fonction_ActivationNeurone_Cache), NULL si pas de fonction
- la derivee de la fonction d'activation des neurones caches (Fonction_Derivee_ActivationNeurone_Cache)
  NULL si pas de fonction
- la fonction d'activation des neurones de sortie (Fonction_ActivationNeurone_Sortie), NULL si pas de fonction
- la derivee de la fonction d'activation des neurones de sortie (Fonction_Derivee_ActivationNeurone_Sortie)
  NULL si pas de foncreturn PAS_D_ERREURtion
- nombre de lot eventuel si traitement par batch pour un apprentissage stochastique  (usiNbLots)
  si usiNbLots non< 2 on traite tout le jeu de donnees dans chaque passe d'apprentissage
  si usiNbLots = 2, 3, ..., on divise le jeu de donnees en usiNbLots
     de taille = (taille du jeu de donnees) / usiNbLots
  remarque : il est preferable que usiNbLots soit un diviseur de la taille du jeu de donnees

SORTIE :
- Le reseau de neurones initialisee (pointeur pReseauNeurones)

VALEUR RETOURNEE :
PAS_D_ERREUR = tout est ok
ERREUR_NOMBRE_COUCHES_MAUVAIS = mauvais nombre de couches (<2)
ERREUR_ALLOCATION_MEMOIRE_NEURONE = pb d'allocation memoire
et toutes les erreurs declenchees par les fonctions d'initialisation de couche et de neurone

IMPORTANT : les pointeurs F_ActivationVectorielle, F_Derivee_ActivationVectorielle,
            mat3DlfPoids, Fonction_ActivationNeurone_Cache, Fonction_Derivee_ActivationNeurone_Cache,
            Fonction_ActivationNeurone_Sortie, Fonction_Derivee_ActivationNeurone_Sortie
            sont supposes valides s'ils sont utilises

NOTE :
    La creation d'un reseau de neurone se compose de ... etapes:
    1. Remplissage des parametres du reseau de neurones (hors allocation dynamique)
    2. Allocation memoire pour les couches de neurones du reseau de neurones
    3. Initialisation des couches de neurones
    4. Allocation memoire tableau prediction des valeurs finales
    5. Allocation memoire tableau des vrais valeurs finales

***************************************************/

T_ERREUR InitReseauNeurone ( T_TYPE_RESEAU_NEURONES                typeReseauNeurones                        ,
                             char                                * pszDescription                            ,
                             REEL                                  lfTauxApprentissage                       ,
                             short int                             siNbCouches                               ,
                             short int                           * tabsiNbNeurones                           ,
                             T_FONCTION_ACTIVATION_VECTORIELLE   * F_ActivationVectorielle                   ,
                             T_FONCTION_ACTIVATION_VECTORIELLE   * F_Derivee_ActivationVectorielle           ,
                             REEL                              *** mat3DlfPoids                              ,
                             T_FONCTION_ACTIVATION               * Fonction_ActivationNeurone_Cache          ,
                             T_FONCTION_ACTIVATION               * Fonction_Derivee_ActivationNeurone_Cache  ,
                             T_FONCTION_ACTIVATION               * Fonction_ActivationNeurone_Sortie         ,
                             T_FONCTION_ACTIVATION               * Fonction_Derivee_ActivationNeurone_Sortie ,
                             unsigned short int                    usiNbLots                                 ,
                             T_RESEAU_NEURONES                   * pReseauNeurones                           ) ;

/***************************************************
  Desinitialisation d'un reseau de neurones en couches
ENTREE :
SORTIE :
- Le reseau de neurones desinitialise (pointeur pReseauNeurones)

VALEUR RETOURNEE :
PAS_D_ERREUR = tout est ok
ERREUR_TYPE_RESEAU_INCONNU

***************************************************/

T_ERREUR DesinitReseauNeurone ( T_RESEAU_NEURONES * pReseauNeurones ) ;

/***************************************************
    Affichage d'un reseau de neurones en couches
ENTREE :
- LeReseauNeurones a afficher

SORTIE :
PAS_D_ERREUR = OK
ERREUR_TYPE_RESEAU_INCONNU = type du reseau inconnu
***************************************************/

T_ERREUR AfficheReseauNeurone ( T_RESEAU_NEURONES LeReseauNeurones ) ;

/***************************************************
                Affichage integral
       d'un reseau de neurones en couches
ENTREE :
- LeReseauNeurones a afficher

SORTIE :
PAS_D_ERREUR = OK
ERREUR_TYPE_RESEAU_INCONNU = type du reseau inconnu
***************************************************/

T_ERREUR AfficheIntegralReseauNeurone ( T_RESEAU_NEURONES LeReseauNeurones ) ;

/***************************************************
           Sauvegarde des caracteristiques
         d'un reseau de neurones en couches
                dans un fichier texte
ENTREE :
- LeReseauNeurones a sauvegarder
- le nom du fichier texte de sauvegarde (szNomFic)
- un texte libre a sauvegarder dans le fichier avant toute chose, pour information (szTexte)
SORTIE :
PAS_D_ERREUR = OK
ERREUR_FICHIER_ECHEC_CREATION = le fichier de sauvegarde ne peut etre cree
ERREUR_FICHIER_ECHEC_ECRITURE = echec ecriture dans le fichier

Remarque : a ce stade, pErreursCumulees et pGradientsPoidsCumules
           sont pas sauvegardes
***************************************************/

T_ERREUR SauveFicTexteReseauNeurones ( T_RESEAU_NEURONES   LeReseauNeurones ,
                                       char              * szNomFic         ,
                                       char              * szTexte          ) ;

/***************************************************
    Utilitaire : sauvegarde des caracteristiques
            d'une couche de neurones
              dans un fichier texte
ENTREE :
- Le pointeur de fichier cible
- La couche de neurones a sauvegarder
SORTIE :
PAS_D_ERREUR = OK
ERREUR_POINTEUR_FICHIER_ILLICITE = le pointeur de fichier est illicite
ERREUR_FICHIER_ECHEC_ECRITURE = echec ecriture dans le fichier
***************************************************/

T_ERREUR SauveCoucheNeuronesDansFicTexte ( FILE              * pFic             ,
                                           T_COUCHE_NEURONES   LaCoucheNeurones ) ;

/***************************************************
         Sauvegarde des caracteristiques
             d'un reseau de neurones
              dans un fichier binaire
ENTREE :
- LeReseauNeurones a sauvegarder
- le nom du fichier binaire de sauvegarde (szNomFic)
- une cle magique de 4 octets permettant de reconnaitre l'origine du fichier
SORTIE :
PAS_D_ERREUR = OK
ERREUR_FICHIER_ECHEC_CREATION = le fichier de sauvegarde ne peut etre cree
ERREUR_FICHIER_ECHEC_ECRITURE = echec ecriture dans le fichier
ERREUR_TYPE_COUCHE_INCONNU = le type de la couche est inconnu

ATTENTION : on ne sauvergarde que les informations suivantes :
1/ le cle numérique (long int)
2/ le type de reseau de neurones (T_TYPE_RESEAU_NEURONES)
3/ la description du reseau de neurones (char[TAILLE_TEXTE+1])
4/ le taux d'apprentissage (REEL)
5/ le nombre de couches (short int)
5/ les informations essentielles pour chaque couche
 (voir SauveCoucheNeuronesDansFicBinaire)

Les autres donnees contenues dans LaCoucheNeurones sont des pointeurs (pas de serialisation)
et ne sont pas sauvegardes : pErreursCumulees, pGradientsPoidsCumules
***************************************************/

T_ERREUR SauveFicBinaireReseauNeurones ( T_RESEAU_NEURONES   LeReseauNeurones ,
                                         char              * szNomFic         ,
                                         long int            liCleMagique     ) ;

/***************************************************
    Utilitaire : sauvegarde des caracteristiques
            d'une couche de neurones
              dans un fichier binaire
ENTREE :
- Le pointeur de fichier cible
- La couche de neurones a sauvegarder
SORTIE :
PAS_D_ERREUR = OK
ERREUR_POINTEUR_FICHIER_ILLICITE = le pointeur de fichier est illicite
ERREUR_FICHIER_ECHEC_ECRITURE = echec ecriture dans le fichier
***************************************************/

T_ERREUR SauveCoucheNeuronesDansFicBinaire ( FILE              * pFic             ,
                                             T_COUCHE_NEURONES   LaCoucheNeurones ) ;

/***************************************************
         Lecture des caracteristiques
             d'un reseau de neurones
              a partir d'un fichier binaire
ENTREE :
- LeReseauNeurones a lire
- le nom du fichier binaire de lecture (szNomFic)
- une cle magique de 4 octets permettant de reconnaitre l'origine du fichier
SORTIE :
PAS_D_ERREUR = OK
ERREUR_FICHIER_ECHEC_OUVERTURE = le fichier de sauvegarde ne peut etre ouvert
ERREUR_FICHIER_MAUVAISE_CLE_MAGIQUE = erreur cle magique
ERREUR_TYPE_RESEAU_MAUVAIS = mauvais type de reseau

ERREUR_FICHIER_ECHEC_ECRITURE = echec ecriture dans le fichier
ERREUR_TYPE_COUCHE_INCONNU = le type de la couche est inconnu

ATTENTION : on ne sauvergarde que les informations suivantes :
1/ le cle numérique (long int)
2/ le type de reseau de neurones (T_TYPE_RESEAU_NEURONES)
3/ la description du reseau de neurones (char[TAILLE_TEXTE+1])
4/ le taux d'apprentissage (REEL)
5/ le nombre de couches (short int)
5/ les informations essentielles pour chaque couche
 (voir SauveCoucheNeuronesDansFicBinaire)

Les autres donnees contenues dans LaCoucheNeurones sont des pointeurs (pas de serialisation)
et ne sont pas sauvegardes : pErreursCumulees, pGradientsPoidsCumules
***************************************************/

T_ERREUR ChargeFicBinaireReseauNeurones ( T_RESEAU_NEURONES * LeReseauNeurones ,
                                          char              * szNomFic         ,
                                          long int            liCleMagique     ) ;

/***************************************************
    Utilitaire : lecture des caracteristiques
            d'une couche de neurones
              a partir d'un fichier binaire
ENTREE :
- Le pointeur de fichier cible
- La couche de neurones a lire
SORTIE :
PAS_D_ERREUR = OK
ERREUR_POINTEUR_FICHIER_ILLICITE = le pointeur de fichier est illicite
ERREUR_FICHIER_ECHEC_LECTURE = echec lecture dans le fichier
***************************************************/

T_ERREUR ChargeCoucheNeuronesDansFicBinaire ( FILE              * pFic             ,
                                              T_COUCHE_NEURONES * LaCoucheNeurones ) ;

/***************************************************
                 CalcPredictionReseauNeurones
  Calcul d'une prediction grace a un reseau de neurones
  en supposant les donnees d'entree du dataset deja stockees
  dans la couche d'entree (champ plfOutputSample)

ENTREE :
- le reseau de neurones (pReseauNeurones)
SORTIE :
- les valeurs calculees, stockees dans le champ plfOutputSample
  de la couche de sortie
VALEUR RETOURNEE :
PAS_D_ERREUR = OK
ERREUR_TYPE_RESEAU_INCONNU = le reseau donne en argument est de type inconnu
et toutes les erreurs issues de CalcPredictionCouche
***************************************************/

T_ERREUR CalcPredictionReseauNeurones ( T_RESEAU_NEURONES * pReseauNeurones ) ;

/***************************************************
          RetroPropagationErreursEtGradients
            Retro-propagation des erreurs
                         et
calcul de la contribution d'un echantillon au gradient
    pour corriger les poids synaptiques du reseau

  On suppose les donnees d'entree de l'echantillon
  du dataset deja stockees dans la couche d'entree
     (champ plfOutputSample de la couche ZERO)
ainsi que les valeurs de prediction (plfPredictionFinale)
et les vraies valeurs tirees du data set (plfVraieValeurFinale)

ENTREE :
- le reseau de neurones (pReseauNeurones)
SORTIE :
- les champs plfErreurDeltaSample des differentes couches
  (valeur pour ce seul echantillon)
- la matrice des corrections de gradient cumulees sur tous les echantillons
  deja traites PLUS l'echantillon present.
  A la fin de la boucle sur les tous les echantillons du data set, la matrice contient
  la sommes des contributions au gradient pour tous les echantillons du dataset.
  Il faudra alors soustraire chacun des termes de cette matrice (multiplie par le coefficient
  d'apprentissage et divise par le nombre d'echantillon pour obtenir une correction MOYENNE)
  a chacun des poids synaptiques :
  coefficient -= coef_apprentissage * somme_contribution / nb_echantillons_analyses

VALEUR RETOURNEE :
PAS_D_ERREUR = OK
ERREUR_TYPE_RESEAU_INCONNU = le reseau donne en argument est de type inconnu
et toutes les erreurs issues de CalcPredictionCouche
***************************************************/

T_ERREUR RetroPropagationErreursEtGradients ( T_RESEAU_NEURONES * pReseauNeurones ) ;

/***************************************************
          InitAZeroGradientsPoidsCumules
         Initialisation a la valeur ZERO
de la matrice qui contiendra les valeurs cumulees
                  des gradients

ENTREE :
- le reseau de neurones (pReseauNeurones)
SORTIE :
- le champ pGradientsPoidsCumules du reseau de neurones

VALEUR RETOURNEE :
PAS_D_ERREUR = OK
ERREUR_TYPE_RESEAU_INCONNU = le reseau donne en argument est de type inconnu
***************************************************/

T_ERREUR InitAZeroGradientsPoidsCumules ( T_RESEAU_NEURONES * pReseauNeurones ) ;

/***************************************************
          CalcCorrectionPoidsSynaptiques
    Calcul des nouvelles valeurs de poids synaptiques
       (tous les tablfPoids de tous les neurones
           de toutes les couches du reseau)
           a partirdes valeurs contenues dans
           le champ pGradientsPoidsCumules

ENTREE :
- le reseau de neurones (pReseauNeurones)
- le nombre total d'enchantillons a etre passes dans la fonction
  RetroPropagationErreursEtGradients (voir REMARQUE ci-dessous)

SORTIE :
- valeur mise a jour de tous les tablfPoids de tous les neurones
  de toutes les couches du reseau

REMARQUE : Cette fonction doit etre appelee apres avoir fait passer tous
les echantillons souhaites du dataset dans la fonction
RetroPropagationErreursEtGradients

VALEUR RETOURNEE :
PAS_D_ERREUR = OK
ERREUR_TYPE_RESEAU_INCONNU = le reseau donne en argument est de type inconnu
***************************************************/

T_ERREUR CalcCorrectionPoidsSynaptiques ( T_RESEAU_NEURONES * pReseauNeurones ,
                                          long int            liNbElts        ) ;

/***************************************************
             PredictionJeuDeDonnees
      prediction par un reseau de neurones
        sur un jeu de donnees quelconque
ENTREE :
- le nombre d'elements dans le jeu de donees (liNbElts)
- le jeu de donnees a tester (TabDonnees)
- le reseau de neurones predicteur (LeReseauBankMarketing)
- la taille du type structure utilise pour stocker les data du jeu de donnees
  (siTailleStructData)
- un pointeur vers la fonction chargee d'injecter les data du jeu de donnees
  dans la coiche d'entree du reseau de neurones (InjectionDonneesDansCoucheEntree)
- un pointeur vers la fonction chargee de transferer pour stockage final, dans le
  type structure defini pour le jeu de donnees, les informations produites
  en sortie du reseau de neurones (StockePrediction)

SORTIE :
- PAS_D_ERREUR si OK
- ERREUR_POINTEUR_NON_INITIALISE si LeReseauBankMarketing non alloue
***************************************************/

T_ERREUR PredictionJeuDeDonnees ( long int                            liNbElts                         ,
                                  char                              * TabDonnees                       ,
                                  T_RESEAU_NEURONES                   LeReseauNeurones                 ,
                                  short int                           siTailleStructData               ,
                                  T_INJECTEUR_DONNEES_COUCHE_ENTREE * InjectionDonneesDansCoucheEntree ,
                                  T_STOCKEUR_DONNEES_COUCHE_SORTIE  * StockePrediction                 ) ;

/***************************************************
             ApprentissageJeuDeDonnees
prediction par un reseau de neurones sur un jeu de donnees
ENTREE :
- le nombre d'elements dans le jeu de donees (liNbElts)
- le jeu de donnees a tester (TabDonnees)
- le reseau de neurones predicteur (pReseauNeurones)
- la valeur seuil du cout a atteindre pour arreter l'apprentissage
  (lfSeuilValCout)
- le nombre maximum d'iteration pour l'apprentissage (uliNbMaxIter)
- la taille du type structure utilise pour stocker les data du jeu de donnees
  (siTailleStructData)
- un pointeur vers la fonction chargee d'injecter les data du jeu de donnees
  dans la couche d'entree du reseau de neurones (InjectionDonneesDansCoucheEntree)
- un pointeur vers la fonction chargee de transferer pour stockage final, dans le
  type structure defini pour le jeu de donnees, les informations produites
  en sortie du reseau de neurones (StockePrediction)
- un pointeur vers la fonction chargee d'injecter le vrai resultat que l'on
  cherche a predire (fourni dans le jeu de donnees) dans le champ idoine
  du reseau de neurones (InjectionVraieValeurDansReseauNeurones)
- un pointeur vers la fonction de cout (FonctionDeCout)
- un parametre complementaire non utilise (cParam)

SORTIE :
- PAS_D_ERREUR si OK
- ERREUR_POINTEUR_NON_INITIALISE si pReseauNeurones non alloue
***************************************************/

T_ERREUR ApprentissageJeuDeDonnees ( long int                                   liNbElts                               ,
                                     char                                     * TabDonnees                             ,
                                     T_RESEAU_NEURONES                        * pReseauNeurones                        ,
                                     REEL                                       lfSeuilValCout                         ,
                                     unsigned long int                          uliNbMaxIter                           ,
                                     short int                                  siTailleStructData                     ,
                                     T_INJECTEUR_DONNEES_COUCHE_ENTREE        * InjectionDonneesDansCoucheEntree       ,
                                     T_STOCKEUR_DONNEES_COUCHE_SORTIE         * StockePrediction                       ,
                                     T_INJECTEUR_VRAIES_VALEURS_SORTIE_RESEAU * InjectionVraieValeurDansReseauNeurones ,
                                     T_FONCTION_COUT                          * FonctionDeCout                         ,
                                     unsigned char                              cParam                                 ) ;

void DesInitParametresReseauNeuronesNiveauUn (T_RESEAU_NEURONES * pReseauNeurones);
void DesInitTabPredictionsNiveauDeux (T_RESEAU_NEURONES * pReseauNeurones, short siNbCouches);
void DesInitTabVraiesValeursNiveauTrois (T_RESEAU_NEURONES * pReseauNeurones, short siNbCouches);


#endif // RESEAUNEURONE_H_INCLUDED

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
