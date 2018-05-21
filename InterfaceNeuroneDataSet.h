/*******************************************************************
                        INTERFACENEURONEDATASET.H
                  Definition des fonctions d'interace
           entre le code de traitement par reseau de neurone
                         et les jeux de donnees

*******************************************************************/
#ifndef INTERFACENEURONEDATASET_H_INCLUDED
#define INTERFACENEURONEDATASET_H_INCLUDED

#include "BibliReseauNeurones/TypeReseauNeurones.h"

/****************************************************************************
 Prototype generique de la fonction qui charge les donnees en memoire
   pour chaque jeu de donnees, Il faut fournir une telle fonction pour chaque
   jeu de donnees
ENTREE :
- Nom du fichier contenant les donnees (szNomFichier)
- nombre d'elements a lire (liNbElts)
- pointeur vers le tableau qui va recevoir les donnees (TabDonnees)
VALEUR RETOURNEE :
PAS_D_ERREUR = OK
ERREUR_FICHIER_ECHEC_OUVERTURE = le fichier n'a pu etre ouvert
ERREUR_DECODAGE_JEU_DE_DONNEES = le decodage du jeu de donnees a echoue
*****************************************************************************/

typedef T_ERREUR T_CHARGEUR_JEU_DE_DONNEES ( char      * szNomFichier ,
                                             long int    liNbElts     ,
                                             void      * TabDonnees   ) ;

/****************************************************************************
 Prototype generique de la fonction qui afiche a l'ecran les donnees en memoire
   pour chaque jeu de donnees, Il faut fournir une telle fonction pour chaque
   jeu de donnees
ENTREE :
- texte libre a afficher (szTexte)
- nombre d'echnatillon a afficher (liNbElts)
- pointeur vers le tableau qui va contient les donnees (TabDonnees)
- entier qui vaut 1 si on veut aussi afficher des probabilités, = 0 sinon (AfficheProba)
- un unsigned char servant d'argument complmementaire si necessaire
VALEUR RETOURNEE :
PAS_D_ERREUR = OK
*****************************************************************************/

typedef T_ERREUR T_AFFICHEUR_JEU_DE_DONNEES ( char          * szTexte      ,
                                              long int        liNbElts     ,
                                              void          * TabDonnees   ,
                                              short int       AfficheProba ,
                                              unsigned char   cTypeCherche ) ;

/***************************************************
           InjecteDonneesDansCoucheEntree
 Injection des donnees d'un echantillon individuel
  dans la couche d'entree d'un reseau de neurones
ENTREE :
- un pointeur vers les donnees de l'echantillon (pDonnees)
- un pointeur vers le reseau de neurones
- le neurone predicteur (LeNeurone)
- un premier parametre complementaire "short int", au cas ou (siParamUn)
- un second parametre complementaire "long int", au cas ou (liParamDeux)

SORTIE :
- CR d'activite
***************************************************/

typedef T_ERREUR T_INJECTEUR_DONNEES_COUCHE_ENTREE ( void              * pDonnees        ,
                                                     T_RESEAU_NEURONES * pReseauNeurone  ,
                                                     short int           siParamUn       ,
                                                     long int            liParamDeux     ) ;

/***************************************************
                   StockePrediction
Stocke pour sauvegarde les productions du reseau de neurone
(champ plfPredictionFinale) dans les champs idoines
de la structure de stockage cree pour gere le jeu de donnees etudie
 Entree :
 - pointeur sur la donnee structuree dans laquelle
   on veut sauvegarder des informations (char * pDonnees
   a convertir dans le bon type par l'utilisateur de la bibliotheque)
- le reseau de neurones contenant les niformatinos a sauvegarder
***************************************************/

typedef T_ERREUR T_STOCKEUR_DONNEES_COUCHE_SORTIE ( char              * pDonnees         ,
                                                    T_RESEAU_NEURONES   LeReseauNeurones ) ;

/***************************************************
****************************************************
          INJECTEUR DES VRAIES VALEURS
        EN SORTIE DU RESEAU DE NEURONES
             (plfVraieValeurFinale)
RQ : prototype OK pour une tache de classification
     binaire ou multivaluee
     La fonction a fournir par l'utilisateur de la
     bibliotheque devra prevoir une fonction adaptee
     a sa situation (classification binaire ou multivaluee)
****************************************************
***************************************************/

typedef T_ERREUR T_INJECTEUR_VRAIES_VALEURS_SORTIE_RESEAU ( void              * pDonnees        ,
                                                            T_RESEAU_NEURONES * pReseauNeurone  ,
                                                            short int           siParamUn       ,
                                                            long int            liParamDeux     ) ;

#endif // INTERFACENEURONEDATASET_H_INCLUDED
