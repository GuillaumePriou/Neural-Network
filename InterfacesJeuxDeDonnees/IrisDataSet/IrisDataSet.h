/*******************************************************************
                              IRISDATASET.H
          Definition des types et des fonctions de traitement
                        dediees a l'iris data set

IRIS DATA SET : Fisher (1936)

CONTENU :
150 echantillons contenant cinq donnees :
- longueur, largeur de petale
- longueur, largeur de sepale
- type de l'iris (setosa, versicolor, virginica)

PAGE WEB : archive.ics.edu/ml/datasets/iris

*******************************************************************/

#ifndef IRISDATASET_H_INCLUDED
#define IRISDATASET_H_INCLUDED

/* nombre d'iris servant a l'apprentissage */
#define NB_IRIS_APPRENTISSAGE 120
/* nombre d'apprentissage servant au test */
#define NB_IRIS_TEST           30
/* nombre maximum de neurone par couche pour l'iris data set */
#define NB_MAX_NEURONES_PAR_COUCHE_IRIS 3

/* pas de traitement par lot */
#define TRAITEMENT_PAR_LOTS_IRIS 0

/***************************************************
    Definition d'un type structure permettant de
 stocker les informations sur l'echantillon d'iris :
double        lfLongueur     : longueur petale
double        lfLargeur      : largeur petale
unsigned char cType          : type d'iris
       (0 = setosa, 1 = versicolor , 2 = virginica)
double        lfProbabilite  : probabilité calculee
       avec le modele neuronal
***************************************************/

typedef struct TagDonneesIris
{
 REEL        lfLongueur    ;
 REEL        lfLargeur     ;
 unsigned char cType         ;
 //REEL        TabOutputCoucheCachee[NB_MAX_NEURONES_PAR_COUCHE_IRIS] ;
 //REEL        TabOutputCoucheSortie[NB_MAX_NEURONES_PAR_COUCHE_IRIS] ;
 REEL        lfProbabilite ;
 unsigned char cTypePredit   ;
} T_DONNEES_IRIS ;

/********************************************************
*********************************************************
        FONCTIONS DE CHARGEMENT ET D'AFFICHAGE
           DU JEU DE DONNEES IRIS DATA SET
*********************************************************
********************************************************/

/***************************************************
                 ChargeDonneesIris
       Chargement du jeu de donnees utilise
      pour l'apprentissage et pour les tests
ENTREE :
- Nom du fichier contenant les donnees
- nombre de valeur attendues
- pointeur sur le tableau des variables structurees stockant les donnees
VALEUR RETOURNEE :
PAS_D_ERREUR = OK
ERREUR_FICHIER_ECHEC_OUVERTURE = le fichier n'a pu etre ouvert
ERREUR_DECODAGE_JEU_DE_DONNEES = le decodage du jeu de donnees a echoue
***************************************************/

T_ERREUR ChargeDonneesIris ( char      * szNomFichier ,
                             short int   siNb_Elts    ,
                             void      * TabDonnees   ) ;

/***************************************************
                   AfficheDonneesIris
      affichage du jeu de donnees iris data set
***************************************************/

T_ERREUR AfficheDonneesIris ( char          * szTexte      ,
                              long int        liNbElts     ,
                              void          * TabDonnees   ,
                              short int       AfficheProba ,
                              unsigned char   cTypeCherche ) ;

/***************************************************
****************************************************
    TEST PREDICTION / APPRENTISSAGE NEURONE SEUL
****************************************************
***************************************************/

/***************************************************
           PredictionNeuroneJeuDeDonnees
prediction par un neurone SEUL sur un jeu de donnees
ENTREE :
- le nombre d'elements dans le jeu de donees (liNbElts)
- le jeu de donnees a tester (TabDonnees)
- le neurone predicteur (LeNeurone)
- un parametre complementaire (type d'iris cherche, cTypeCherche)

SORTIE :
- T_ERREUR :
***************************************************/

T_ERREUR PredictionNeuroneJeuDeDonnees ( long int        liNbElts     ,
                                         void          * TabDonnees   ,
                                         T_NEURONE       LeNeurone    ,
                                         unsigned char   cTypeCherche ) ;

/***************************************************
           ApprentissageNeuroneJeuDeDonnees
prediction par un neurone SEUL sur un jeu de donnees
ENTREE :
- le nombre d'elements dans le jeu de donees (liNbElts)
- le jeu de donnees a tester (TabDonnees)
- le neurone predicteur (LeNeurone)
- un parametre complementaire (type d'iris cherche, cTypeCherche)

SORTIE :
- PAS_D_ERREUR si OK
- ERREUR_POINTEUR_NON_INITIALISE si LeNeurone non alloue
***************************************************/

T_ERREUR ApprentissageNeuroneJeuDeDonnees ( long int        liNbElts     ,
                                            void          * TabDonnees   ,
                                            T_NEURONE     * pNeurone     ,
                                            unsigned char   cTypeCherche ) ;

/***************************************************
          Fonction de test d'un neurone SEUL
                  sur l'IRIS DATA SET
***************************************************/

T_ERREUR TestePredictionUnNeuroneIrisDataSet ( void ) ;

/***************************************************
          Fonction de test d'un neurone SEUL
                  sur l'IRIS DATA SET
                      Apprentissage
***************************************************/

T_ERREUR TesteApprentissageUnNeuroneIrisDataSet ( void ) ;

/***************************************************
****************************************************
    INJECTEUR DE DONNEES DANS LA COUCHE D'ENTREE
              DU RESEAU DE NEURONES
****************************************************
***************************************************/

T_ERREUR InjectionDonneesDansCoucheEntree ( void              * pDonnees        ,
                                            T_RESEAU_NEURONES * pReseauNeurone  ,
                                            short int           siParamUn       ,
                                            long int            liParamDeux     ) ;

/***************************************************
****************************************************
          INJECTEUR DES VRAIES VALEURS
        EN SORTIE DU RESEAU DE NEURONES
             (plfVraieValeurFinale)
RQ : OK pour une tache de classification multicouche
****************************************************
***************************************************/

T_ERREUR InjectionVraieValeurDansReseauNeurones ( void              * pDonnees        ,
                                                  T_RESEAU_NEURONES * pReseauNeurone  ,
                                                  short int           siParamUn       ,
                                                  long int            liParamDeux     ) ;

/***************************************************
****************************************************
          TEST PREDICTION PERCEPTRON XOR
****************************************************
***************************************************/

/***************************************************
     Fonction de test d'un perceptron multicouche
                  sur l'IRIS DATA SET
***************************************************/

T_ERREUR TestePredictionPerceptronIrisDataSet ( void ) ;

/***************************************************
           PredictionPerceptronJeuDeDonnees
prediction par un neurone SEUL sur un jeu de donnees
ENTREE :
- le nombre d'elements dans le jeu de donees (liNbElts)
- le jeu de donnees a tester (TabDonnees)
- le Perceptron XOR predicteur (LeNeurone)
- un parametre complementaire (type d'iris cherche, cTypeCherche)

SORTIE :
- PAS_D_ERREUR si OK
- ERREUR_POINTEUR_NON_INITIALISE si LeNeurone non alloue
***************************************************/

T_ERREUR PredictionPerceptronJeuDeDonnees ( long int            liNbElts     ,
                                            void              * TabDonnees   ,
                                            T_RESEAU_NEURONES   LePMC_XOR    ,
                                            unsigned char       cTypeCherche ) ;

/***************************************************
****************************************************
   TEST PREDICTION RESEAU 3 COUCHES DE 3 NEURONES
****************************************************
***************************************************/

/***************************************************
             Fonction de test d'un reseau
         de trois couches de trois neurones
                sur l'IRIS DATA SET
                     prediction
***************************************************/

T_ERREUR TestePrediction3Couches3NeuronesIrisDataSet ( void ) ;

/***************************************************
           Prediction3Couches3NeuronesJeuDeDonnees
prediction par un neurone SEUL sur un jeu de donnees
ENTREE :
- le nombre d'elements dans le jeu de donees (liNbElts)
- le jeu de donnees a tester (TabDonnees)
- le Perceptron XOR predicteur (LeReseau3c3n)

SORTIE :
- PAS_D_ERREUR si OK
- ERREUR_POINTEUR_NON_INITIALISE si LeReseau3c3n non alloue
***************************************************/

T_ERREUR Prediction3Couches3NeuronesJeuDeDonnees ( long int            liNbElts     ,
                                                   void              * TabDonnees   ,
                                                   T_RESEAU_NEURONES   LeReseau3c3n ) ;

/***************************************************
             Fonction de test d'un reseau
         de trois couches de trois neurones
                sur l'IRIS DATA SET
                     apprentissage
***************************************************/

T_ERREUR TesteApprentissage3Couches3NeuronesIrisDataSet ( void ) ;


/***************************************************
           ApprentissageReseauNeuroneJeuDeDonnees
prediction par un reseau de neurones sur un jeu de donnees
ENTREE :
- le nombre d'elements dans le jeu de donees (liNbElts)
- le jeu de donnees a tester (TabDonnees)
- le reseau de neurones predicteur (pReseauNeurones)
- un parametre complementaire non utilise (cParam)

SORTIE :
- PAS_D_ERREUR si OK
- ERREUR_POINTEUR_NON_INITIALISE si pReseauNeurones non alloue
***************************************************/

T_ERREUR Apprentissage3Couches3NeuronesJeuDeDonnees ( long int            liNbElts        ,
                                                      void              * TabDonnees      ,
                                                      T_RESEAU_NEURONES * pReseauNeurones ,
                                                      unsigned char       cParam          ) ;

#endif // IRISDATASET_H_INCLUDED

/***************************************************
                 FIN DU COMPOSANT
***************************************************/
