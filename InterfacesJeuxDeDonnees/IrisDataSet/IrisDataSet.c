/*******************************************************************
                              IrisDataSet.C
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

#include "IrisDataSet.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

T_ERREUR ChargeDonneesIris ( char      * szNomFichier ,
                             short int   siNb_Elts    ,
                             void      * TabDonnees   )
{
	T_DONNEES_IRIS * TabIrisApprentissage ;
	FILE * ficIris ;
	char Ligne[81] ;
	char NomIris[20] ;
	short int NbLignes = 0 ;
	T_ERREUR Err = PAS_D_ERREUR ;

	TabIrisApprentissage = (T_DONNEES_IRIS *) TabDonnees ;

	printf ( " Lecture du fichier %s..." , szNomFichier ) ;
	ficIris = fopen ( szNomFichier , "rt" ) ;
	
	if ( ficIris == NULL ) /* le fichier ne peut être ouvert */
		Err = ERREUR_FICHIER_ECHEC_OUVERTURE ;
	else
	{
		while ( fgets ( Ligne , 81 , ficIris) != NULL )
		{
			if ( ( Err == PAS_D_ERREUR )
				&& ( NbLignes < siNb_Elts  )
				&& ( 5 == sscanf ( Ligne , "%lf,%lf,%lf,%lf,%s", &(TabIrisApprentissage[NbLignes].lfLongueurSepale),
								   							     &(TabIrisApprentissage[NbLignes].lfLargeurSepale) ,
													   		     &(TabIrisApprentissage[NbLignes].lfLongueurPetale),
															     &(TabIrisApprentissage[NbLignes].lfLargeurPetale) ,
															     NomIris))
			   )
			{
				if ( strcmp ( NomIris , "Iris-setosa" ) == 0)          TabIrisApprentissage[NbLignes].cType = 0 ;
				else if ( strcmp ( NomIris , "Iris-versicolor" ) == 0) TabIrisApprentissage[NbLignes].cType = 1 ;
				else if ( strcmp ( NomIris , "Iris-virginica" ) == 0)  TabIrisApprentissage[NbLignes].cType = 2 ;
				else TabIrisApprentissage[NbLignes].cType = 255 ;
				//       printf ( "i = %hd, Ligne = |%s|\n" , NbLignes , Ligne ) ;
				NbLignes++ ;
			}
			else if ( NbLignes != siNb_Elts )    /* probleme de decodage de ligne */
				Err = ERREUR_DECODAGE_JEU_DE_DONNEES ;
		}
		fclose ( ficIris ) ;
	}
	
	printf ( "Nombre de lignes lues : %hd\n" , NbLignes ) ;

	return ( Err ) ;
}



T_ERREUR AfficheDonneesIris ( char          * szTexte      ,
                              long int        liNbElts     ,
                              void          * TabDonnees   ,
                              short int       AfficheProba ,
                              unsigned char   cTypeCherche )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR PredictionNeuroneJeuDeDonnees ( long int        liNbElts     ,
                                         void          * TabDonnees   ,
                                         T_NEURONE       LeNeurone    ,
                                         unsigned char   cTypeCherche )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR ApprentissageNeuroneJeuDeDonnees ( long int        liNbElts     ,
                                            void          * TabDonnees   ,
                                            T_NEURONE     * pNeurone     ,
                                            unsigned char   cTypeCherche )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR TestePredictionUnNeuroneIrisDataSet ( void )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR TesteApprentissageUnNeuroneIrisDataSet ( void )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR InjectionDonneesDansCoucheEntree ( void              * pDonnees        ,
                                            T_RESEAU_NEURONES * pReseauNeurone  ,
                                            short int           siParamUn       ,
                                            long int            liParamDeux     )
{
    T_DONNEES_IRIS * pDonneesIris ;
    pDonneesIris = (T_DONNEES_IRIS *) pDonnees ;

    /* neurone de biais */
    pReseauNeurone->pCouchesNeurones[0].plfOutputSample[0] = 1.0 ;
    /* longueur petale Iris */
    pReseauNeurone->pCouchesNeurones[0].plfOutputSample[1] = pDonneesIris->lfLongueurPetale ; /* L petale */ /* data retenu comme premiere variable */
    /* largeur petale iris */
    pReseauNeurone->pCouchesNeurones[0].plfOutputSample[2] = pDonneesIris->lfLargeurPetale ; /* l petale */ /* data retenu comme seconde variable */

    return PAS_D_ERREUR ;
}

T_ERREUR InjectionVraieValeurDansReseauNeurones ( void              * pDonnees        ,
                                                  T_RESEAU_NEURONES * pReseauNeurone  ,
                                                  short int           siParamUn       ,
                                                  long int            liParamDeux     )
{
    short int i ;
    T_DONNEES_IRIS * pDonneesIris ;

    if ( pReseauNeurone->typeReseauNeurones == RESEAU_FULLY_CONNECTED_AVEC_BIAIS )
    {
        pDonneesIris = (T_DONNEES_IRIS *) pDonnees ;

        for ( i = 0 ; i < pReseauNeurone->pCouchesNeurones[pReseauNeurone->siNbCouches-1].siNbNeurones ; i++ )
            pReseauNeurone->plfVraieValeurFinale[i] = ZERO ;

        pReseauNeurone->plfVraieValeurFinale[pDonneesIris->cType] = UN ;
    }
    else
        return ERREUR_TYPE_RESEAU_MAUVAIS ;

    return PAS_D_ERREUR ;
}

T_ERREUR TestePredictionPerceptronIrisDataSet ( void )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR PredictionPerceptronJeuDeDonnees ( long int            liNbElts     ,
                                            void              * TabDonnees   ,
                                            T_RESEAU_NEURONES   LePMC_XOR    ,
                                            unsigned char       cTypeCherche )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR TestePrediction3Couches3NeuronesIrisDataSet ( void )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR Prediction3Couches3NeuronesJeuDeDonnees ( long int            liNbElts     ,
                                                   void              * TabDonnees   ,
                                                   T_RESEAU_NEURONES   LeReseau3c3n )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR TesteApprentissage3Couches3NeuronesIrisDataSet ( void )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}

T_ERREUR Apprentissage3Couches3NeuronesJeuDeDonnees ( long int            liNbElts        ,
                                                      void              * TabDonnees      ,
                                                      T_RESEAU_NEURONES * pReseauNeurones ,
                                                      unsigned char       cParam          )
{
    return ERREUR_FONCTION_NON_DEFINIE;
}
