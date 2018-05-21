/**********************************************************
                         CONSTANTES.H

                  version 1.1 (29/04/2018)
**********************************************************/

#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/* taille d'un texte descriptif */
#define TAILLE_TEXTE 80

/* valeur par defaut d'un poids synaptique */
#define VAL_POIDS_DEFAUT 0.01

/* type reel qui sera utilise dans les traitements */
typedef double REEL ;

/* type utilise pour transmettre les erreurs eventuelles de traitement */
typedef enum
{
  PAS_D_ERREUR                         =   0 ,
  ERREUR_INDETERMINEE                  =   1 ,
  ERREUR_FICHIER_ECHEC_CREATION        =  50 ,
  ERREUR_FICHIER_ECHEC_ECRITURE        =  51 ,
  ERREUR_FICHIER_ECHEC_OUVERTURE       =  52 ,
  ERREUR_FICHIER_ECHEC_LECTURE         =  53 ,
  ERREUR_FICHIER_MAUVAISE_CLE_MAGIQUE  =  54 ,
  ERREUR_POINTEUR_FICHIER_ILLICITE     =  55 ,
  ERREUR_ALLOCATION_MEMOIRE_NEURONE    = 100 ,
  ERREUR_NB_DENDRITES                  = 101 ,
  ERREUR_NB_NEURONES                   = 102 ,
  ERREUR_POINTEUR_NON_INITIALISE       = 150 ,
  ERREUR_DECODAGE_JEU_DE_DONNEES       = 200 ,
  ERREUR_TYPE_COUCHE_INCONNU           = 300 ,
  ERREUR_TYPE_COUCHE_MAUVAIS           = 301 ,
  ERREUR_ALLOCATION_MEMOIRE_COUCHE     = 400 ,
  ERREUR_TYPE_RESEAU_INCONNU           = 500 ,
  ERREUR_NOMBRE_COUCHES_MAUVAIS        = 501 ,
  ERREUR_ALLOCATION_MEMOIRE_RESEAU     = 502 ,
  ERREUR_TYPE_RESEAU_MAUVAIS           = 503 ,
  ERREUR_NB_COUCHES                    = 504 ,
  ERREUR_FCOUT_LOGLOSS                 = 600 ,
  ERREUR_NB_MAX_ITER                   = 700 ,
  ERREUR_MNIST_TAILLE_BLOC             = 750 ,
  ERREUR_MNIST_ALLOCATION_MEMOIRE      = 751 ,
  ERREUR_BANK_MARKETING_ALLOCATION_MEMOIRE = 752 ,
  ERREUR_FONCTION_NON_DEFINIE          = 800
} T_ERREUR ;

#endif // CONSTANTES_H_INCLUDED
