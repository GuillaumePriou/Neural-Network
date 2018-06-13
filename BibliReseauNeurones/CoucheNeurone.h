/*******************************************************************
                              COUCHENEURONE.H
                Definition des types "couches de neurones"
                   et des fonctions de gestion associ�es
*******************************************************************/
#ifndef COUCHENEURONE_H_INCLUDED
#define COUCHENEURONE_H_INCLUDED

#include <stdio.h>

#include "constantes.h"
#include "Activation.h"
#include "Neurone.h"

/* les differents types de couche de neurones */
typedef enum
{
   COUCHE_NON_INITIALISEE = -1 ,
   COUCHE_ENTREE          =  0 ,
   COUCHE_CACHEE          =  1 ,
   COUCHE_SORTIE          =  2
} T_TYPE_COUCHE_NEURONES ;

/***************************************************
              Definition d'une couche de neurones
On suppose qu'il possede :
- un type de couche (typeCoucheNeurones) :
  COUCHE_ENTREE, COUCHE_CACHEE, COUCHE_SORTIE
- une couche amont, identifee par un pointeur (pCoucheNeuronesAmont)
  NULL si pas de couche amont
- une fonction d'activation vectorielle (F_ActivationVectorielle)
  a appliquer a tous les neurones de la couche apres calculs neuronaux
  NULL si pas de fonction d'activation vectorielle
- la derivee de la fonction d'activation vectorielle (F_Derivee_ActivationVectorielle)
  NULL si pas de fonction d'activation vectorielle
- le nombre de neurones dans la couche (siNbNeurones)
  = 0 si aucun neurone,
  = nombre de donnees entrantes (les X_i) si couche d'entree
- nombre de dendrites par neurone (siNbDendritesParNeurone)
- un tableau de neurones identifie par un pointeur (pNeurone)
  NULL si pas de neurone
- un tableau plfOutputSample de taille siNbNeurones recevant, pour un echantillon donne
  du jeu de DATA, le resultat du calcul de la couche (calcul par les neurones
  ET apres application de la fonction d'activation (du neurone et vectorielle)
- un tableau plfErreurDeltaSample de taille siNbNeurones recevant, pour un echantillon donne
  du jeu de DATA, le resultat du calcul par retropropagation
  de l'erreur commise (le "delta" de la couche)
***************************************************/
typedef struct TagCoucheNeurone
{
    T_TYPE_COUCHE_NEURONES              typeCoucheNeurones              ;
    char                                szDescription[TAILLE_TEXTE+1]   ;
    struct TagCoucheNeurone           * pCoucheNeuronesAmont            ;
    T_FONCTION_ACTIVATION_VECTORIELLE * F_ActivationVectorielle         ;
    T_FONCTION_ACTIVATION_VECTORIELLE * F_Derivee_ActivationVectorielle ;
    short int                           siNbNeurones                    ;
    short int                           siNbDendritesParNeurone         ;
    T_NEURONE                         * pNeurones                       ;
    REEL                              * plfOutputSample                 ;
    REEL                              * plfErreurDeltaSample            ;
} T_COUCHE_NEURONES ;

/***************************************************
      Initialisation d'une couche de neurones
ENTREE :
- Type de couche (typeCoucheNeurones)
- texte descriptif (pszDescription)
- Pointeur sur la couche amont (pCoucheNeuronesAmont), NULL si pas de couche amont
- fonction d'activation vectorielle (F_ActivationVectorielle), NULL si pas de fonction
- derivee de la fonction d'activation vectirielle (F_Derivee_ActivationVectorielle)
  NULL si pas de fonction
- nombre de neurones dans la couche (siNbNeurones), 0 si pas de neurone
- Nombre de dendrites par neurone (siNbDendritesParNeurone), 0 si pas de dendrite
- matrice 2D des (siNbDendrites x siNbNeurones) poids (mat2DlfPoids)
  NULL si l'on initialise une matrice d'entree
- la fonction d'activation des neurones (Fonction_Activation), NULL si pas de fonction
- la derivee de la fonction d'activation des neurones (Fonction_Derivee_Activation)
  NULL si pas de fonction
SORTIE :
- La couche de neurones initialisee (pointeur pCoucheNeurones)
VALEUR RETOURNEE :
PAS_D_ERREUR = tout est ok
ERREUR_NB_NEURONES = nombre de neurones errone
ERREUR_ALLOCATION_MEMOIRE_NEURONE = pb d'allocation memoire
ERREUR_NB_DENDRITES = le nombre de dendrites souhaite pour la couche
                      differe du nombre de neurones de la couche amont
                      (le reseau n'est pas totalement connecte)

IMPORTANT : les pointeurs pCoucheNeuronesAmont, F_ActivationVectorielle,
            F_Derivee_ActivationVectorielle, mat2DlfPoids, Fonction_ActivationNeurone,
            Fonction_Derivee_ActivationNeurone sont supposes valides s'ils sont utilises

NOTE :
    La creation d'une couche de neurones se compose de 6 etapes :
    1. Allouer la memoire a la couche de neurones (n'est pas effectu�e par le InitCoucheNeurone)
    2. Initialiser les attributs de la couche de neurones, sauf :
        - tableau de neurones
        - tableau de stockage de la sortie de la couche (predictions)
        - tableau de stockage de l'erreur de prediction de la couche
    3. Allouer la memoire pour le tableau de neurones
    4. Initialiser les neurones
    5. Allouer la memoire pour les predictions de la couche (inutile d'initialiser)
    6. Allouer la memoire pour l'erreur de prediction (inutile d'initialiser)
***************************************************/

T_ERREUR InitCoucheNeurone ( T_TYPE_COUCHE_NEURONES              typeCoucheNeurones                 ,
                             char                              * pszDescription                     ,
                             T_COUCHE_NEURONES                 * pCoucheNeuronesAmont               ,
                             T_FONCTION_ACTIVATION_VECTORIELLE * F_ActivationVectorielle            ,
                             T_FONCTION_ACTIVATION_VECTORIELLE * F_Derivee_ActivationVectorielle    ,
                             short int                           siNbNeurones                       ,
                             short int                           siNbDendritesParNeurone            ,
                             REEL                             ** mat2DlfPoids                       ,
                             T_FONCTION_ACTIVATION             * Fonction_ActivationNeurone         ,
                             T_FONCTION_ACTIVATION             * Fonction_Derivee_ActivationNeurone ,
                             T_COUCHE_NEURONES                 * pCoucheNeurones                    ) ;

/***************************************************
      Desinitialisation d'une couche de neurones
ENTREE :
SORTIE :
- La couche de neurones desinitialisee (pointeur pCoucheNeurones)
VALEUR RETOURNEE :
PAS_D_ERREUR = tout est ok
ERREUR_TYPE_COUCHE_INCONNU = type de couche inconnu

***************************************************/

T_ERREUR DesinitCoucheNeurone ( T_COUCHE_NEURONES * pCoucheNeurones ) ;

/***************************************************
           Affichage d'une couche de neurones
ENTREE :
- LaCoucheNeurone a afficher
- l'indice d'un eventuel neurone de la couche a afficher
  (siIndiceNeurone)
- l'indice de la couche a afficher dans son reseau de neurones

SORTIE :
PAS_D_ERREUR = OK
ERREUR_TYPE_COUCHE_INCONNU = type de la couche inconnu
***************************************************/

T_ERREUR AfficheCoucheNeurone ( T_COUCHE_NEURONES LaCoucheNeurones ,
                                short int         siIndiceNeurone  ,
                                short int         siIndiceCouche   ) ;

/***************************************************
           Sauvegarde des caracteristiques
               d'une couche de neurones
                dans un fichier texte
ENTREE :
- LaCoucheNeurones a sauvegarder
- le nom du fichier texte de sauvegarde (szNomFic)
- un texte libre a sauvegarder dans le fichier avant toute chose, pour information (szTexte)
SORTIE :
PAS_D_ERREUR = OK
ERREUR_FICHIER_ECHEC_CREATION = le fichier de sauvegarde ne peut etre cree
ERREUR_FICHIER_ECHEC_ECRITURE = echec ecriture dans le fichier
***************************************************/

T_ERREUR SauveFicTexteCoucheNeurones ( T_COUCHE_NEURONES   LaCoucheNeurones ,
                                       char              * szNomFic         ,
                                       char              * szTexte          ) ;

/***************************************************
    Utilitaire : sauvegarde des caracteristiques
            d'un neurone d'une couche
              dans un fichier texte
ENTREE :
- Le pointeur de fichier cible
- Le neurone a sauvegarder
SORTIE :
PAS_D_ERREUR = OK
ERREUR_POINTEUR_FICHIER_ILLICITE = le pointeur de fichier est illicite
ERREUR_FICHIER_ECHEC_ECRITURE = echec ecriture dans le fichier
***************************************************/

T_ERREUR SauveNeuroneDansFicTexte ( FILE      * pFic      ,
                                    T_NEURONE   LeNeurone ) ;

/***************************************************
         Sauvegarde des caracteristiques
             d'une couche de neurones
              dans un fichier binaire
ENTREE :
- LaCoucheNeurones a sauvegarder
- le nom du fichier binaire de sauvegarde (szNomFic)
- une cle magique de 4 octets permettant de reconnaitre l'origine du fichier
SORTIE :
PAS_D_ERREUR = OK
ERREUR_FICHIER_ECHEC_CREATION = le fichier de sauvegarde ne peut etre cree
ERREUR_FICHIER_ECHEC_ECRITURE = echec ecriture dans le fichier
ERREUR_TYPE_COUCHE_INCONNU = le type de la couche est inconnu

ATTENTION : on ne sauvergarde que les informations suivantes :
1/ le cle num�rique (long int)
2/ le type de neurone (T_TYPE_COUCHE_NEURONES)
3/ la description de la couche de neurones (char[TAILLE_TEXTE+1])
4/ le nombre de neurones (short int)
5/ le nombre de dendrites par neurones (short int)
3/ les tableaux des poids synaptiques, de premier au dernier neurone
   en tenant compte de la la nature de la couche :
   Si COUCHE_ENTREE : pas de neurone donc pas de poids
   Si COUCHE_CACHEE : on sauve les poids des neurones UN a (siNbNeurones-1)
                      car le neurone ZERO est le neurone de biais (donc sans poids)
   Si COUCHE_SORTIE : on sauve les poids des neurones ZERO a (siNbNeurones-1)
                      car le neurone ZERO n'est pas un neurone de biais
soit au total : 4 + 2 x 2 + sizeof(T_TYPE_COUCHE_NEURONES) + TAILLE_TEXTE+1 octets
        PLUS  : 0 si couche d'entree OU
                LaCoucheNeurones.siNbDendritesParNeurone x (LaCoucheNeurones.siNbNeurones-1) x sizeof(REEL)
                  si couche cachee OU
                LaCoucheNeurones.siNbDendritesParNeurone x LaCoucheNeurones.siNbNeurones x sizeof(REEL)
                  si couche de sortie

Les autres donnees contenues dans LaCoucheNeurones sont des pointeurs (pas de serialisation)
et ne sont pas sauvegardes :
pCoucheNeuronesAmont , F_ActivationVectorielle , F_Derivee_ActivationVectorielle ,
pNeurones , plfOutputSample ,plfErreurDeltaSample
***************************************************/

T_ERREUR SauveFicBinaireCoucheNeurones ( T_COUCHE_NEURONES   LaCoucheNeurones ,
                                         char              * szNomFic         ,
                                         long int            liCleMagique     ) ;

/***************************************************
         Lecture des caracteristiques
             d'une couche de neurones
              a partir d'un fichier binaire
ENTREE :
- LaCoucheNeurones qui recoit les donnees
- le nom du fichier binaire a lire (szNomFic)
- une cle magique de 4 octets permettant de reconnaitre l'origine du fichier
SORTIE :
PAS_D_ERREUR = OK
ERREUR_FICHIER_ECHEC_OUVERTURE = le fichier ne peut etre ouvert
ERREUR_FICHIER_MAUVAISE_CLE_MAGIQUE = la cle magique n'est pas la bonne
ERREUR_FICHIER_ECHEC_LECTURE = echec de lecture du fichier
ERREUR_TYPE_COUCHE_MAUVAIS = mauvais type de couche
ERREUR_NB_NEURONES = mauvais nombre de neurones
ERREUR_NB_DENDRITES = mauvais nombre de dendrites par neurone
ERREUR_POINTEUR_NON_INITIALISE = pointeur non initialise

ATTENTION : on ne recupere que les informations suivantes :
1/ le cle numerique (long int)
2/ le type de neurone (T_TYPE_COUCHE_NEURONES)
3/ la description de la couche de neurones (char[TAILLE_TEXTE+1])
4/ le nombre de neurones (short int)
5/ le nombre de dendrites par neurones (short int)
3/ les tableaux des poids synaptiques, de premier au dernier neurone
   en tenant compte de la la nature de la couche :
   Si COUCHE_ENTREE : pas de neurone donc pas de poids
   Si COUCHE_CACHEE : on sauve les poids des neurones UN a (siNbNeurones-1)
                      car le neurone ZERO est le neurone de biais (donc sans poids)
   Si COUCHE_SORTIE : on sauve les poids des neurones ZERO a (siNbNeurones-1)
                      car le neurone ZERO n'est pas un neurone de biais
soit au total : 4 + 2 x 2 + sizeof(T_TYPE_COUCHE_NEURONES) + TAILLE_TEXTE+1 octets
        PLUS  : 0 si couche d'entree OU
                LaCoucheNeurones.siNbDendritesParNeurone x (LaCoucheNeurones.siNbNeurones-1) x sizeof(REEL)
                  si couche cachee OU
                LaCoucheNeurones.siNbDendritesParNeurone x LaCoucheNeurones.siNbNeurones x sizeof(REEL)
                  si couche de sortie

Les autres donnees contenues dans LaCoucheNeurones sont des pointeurs (pas de serialisation)
et ne sont pas sauvegardes :
pCoucheNeuronesAmont , F_ActivationVectorielle , F_Derivee_ActivationVectorielle ,
pNeurones , plfOutputSample ,plfErreurDeltaSample
***************************************************/

T_ERREUR ChargeFicBinaireCoucheNeurones ( T_COUCHE_NEURONES * LaCoucheNeurones ,
                                          char              * szNomFic         ,
                                          long int            liCleMagique     ) ;

/***************************************************
                 CalcPredictionCoucheNeurones
  Calcul d'une prediction grace a une couche de neurones
  a partir des resultats calcules par la couche precedente

ENTREE :
- la couche de neurones (pCoucheNeurones)
SORTIE :
- les valeurs calculees, stockees dans le champ plfOutputSample
  de la couche de neurone
VALEUR RETOURNEE :
PAS_D_ERREUR = OK
ERREUR_NB_DENDRITES = la taille du tableau des donnees d'entree
                      differe du nombre de dendrites de neurones
                      de la couche
ERREUR_TYPE_COUCHE_INCONNU = la couche est de type "inconnu"
                             (i.e. inadaptee pour ce calcul)
***************************************************/

T_ERREUR CalcPredictionCoucheNeurones ( T_COUCHE_NEURONES * pCoucheNeurones ) ;

/***************************************************
                 CmpCoucheNeurone
  Compare deux couches de neurones

ENTREE :
- Couche_Neurone 1
- Couche_Neurone 2
SORTIE :
- short 0 si égale, 1 sinon

***************************************************/

short CmpCoucheNeurone ( T_COUCHE_NEURONES   coucheA ,
                         T_COUCHE_NEURONES   coucheB );

#endif // COUCHENEURONE_H_INCLUDED

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
