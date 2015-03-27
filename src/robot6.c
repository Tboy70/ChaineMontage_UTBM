/*****************************/
/* FICHIER GERANT LE ROBOT 6 */
/*****************************/

#include "main.h"

/******************************/
/** INSTANCIATION DU ROBOT 6 **/
/******************************/

robot instanciationRobot6(){	// Robot 6 effectuant l'opération 6 ayant ses réserves de composants vides au départ
	robot r6;
	r6.identifiant = 6;
	r6.numeroOperation = 6;
	r6.reserve[0].vide = 1;
	r6.reserve[1].vide = 1;
	r6.reserve[2].vide = 1;

	return r6;
}

/*************************************************************/
/** MANUFACTURER UN PRODUIT 2 QUI NECESSITE UNE OPERATION 6 **/
/*************************************************************/

void manufactureProduit2Op6(contenu tab[], robot* r6){

	if(tab[12].vide == 1){	// Si on peut placer un produit 2 sur l'anneau

		printf("DEPOT DU PRODUIT 2 NOUVELLEMENT MANUFACTURÉ A L'OPERATION 6 -> PRODUTI FINI \n");

		tab[12].identifiant = 1;
		tab[12].num = 2;
		tab[12].vide = 0;
		tab[12].etapeFabrication = 6;
		tab[12].produitFinal = 1;
	}
}

/*************************************************************/
/** MANUFACTURER UN PRODUIT 4 QUI NECESSITE UNE OPERATION 6 **/
/*************************************************************/

void manufactureProduit4Op6(contenu tab[], robot* r6){

	if(tab[12].vide == 1){	// Si on peut placer un produit 4 sur l'anneau

		printf("DEPOT DU PRODUIT 4 NOUVELLEMENT MANUFACTURÉ A L'OPERATION 6 \n");

		tab[12].identifiant = 1;
		tab[12].num = 4;
		tab[12].vide = 0;
		tab[12].etapeFabrication = 6;
	}
}

/*****************************************************************t************/
/** RAMASSER LES PRODUITS EN COURS DE FABRICATION NECESSITANT L'OPERATION 5 **/
/*****************************************************************************/

void ramasserElementRobot6(contenu tab[], robot* r6){

	pthread_mutex_lock(&mutex);		// Verrouille le MUTEX

	/*** Si le robot 6 tombe sur le produit 2 à l'opération 1 ***/

	if(tab[12].identifiant == 1 && tab[12].num == 2 && tab[12].vide == 0 && tab[12].etapeFabrication == 1){

		if((*r6).reserve[0].vide == 1){	// Si la première réserve du robot est vide

			printf("Le robot 6 prend le produit 2\n");

			(*r6).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r6).reserve[0].identifiant = 1; 	// PRODUIT 
			(*r6).reserve[0].num = 2;			// Numéro 2

			tab[12].vide = 1;					// Plus rien sur le compartiment 13 de l'anneau

			manufactureProduit2Op6(tab, r6);

			(*r6).reserve[0].vide = 0;
		}

		else if((*r6).reserve[1].vide == 1){

			printf("Le robot 6 prend le produit 2\n");

			(*r6).reserve[1].vide = 0;
			(*r6).reserve[1].identifiant = 1;
			(*r6).reserve[1].num = 2;

			tab[12].vide = 1;

			manufactureProduit2Op6(tab, r6);

			(*r6).reserve[1].vide = 0;
		}

		else if((*r6).reserve[2].vide == 1){

			printf("Le robot 6 prend le produit 2\n");

			(*r6).reserve[2].vide = 0;
			(*r6).reserve[2].identifiant = 1;
			(*r6).reserve[2].num = 2;	

			tab[12].vide = 1;

			manufactureProduit2Op6(tab, r6);

			(*r6).reserve[2].vide = 0;
		}
	}

	/*** Si le robot 6 tombe sur le produit 4 à l'opération 4 ***/

	if(tab[12].identifiant == 1 && tab[12].num == 4 && tab[12].vide == 0 && tab[12].etapeFabrication == 4){

		if((*r6).reserve[0].vide == 1){	// Si la première réserve du robot est vide

			printf("Le robot 6 prend le produit 4\n");

			(*r6).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r6).reserve[0].identifiant = 1; 	// PRODUIT 
			(*r6).reserve[0].num = 4;			// Numéro 4

			tab[12].vide = 1;					// Plus rien sur le compartiment 13 de l'anneau

			manufactureProduit4Op6(tab, r6);

			(*r6).reserve[0].vide = 0;
		}

		else if((*r6).reserve[1].vide == 1){

			printf("Le robot 6 prend le produit 4\n");

			(*r6).reserve[1].vide = 0;
			(*r6).reserve[1].identifiant = 1;
			(*r6).reserve[1].num = 4;

			tab[12].vide = 1;

			manufactureProduit4Op6(tab, r6);

			(*r6).reserve[1].vide = 0;
		}

		else if((*r6).reserve[2].vide == 1){

			printf("Le robot 6 prend le produit 4\n");

			(*r6).reserve[2].vide = 0;
			(*r6).reserve[2].identifiant = 1;
			(*r6).reserve[2].num = 4;	

			tab[12].vide = 1;

			manufactureProduit4Op6(tab, r6);

			(*r6).reserve[2].vide = 0;
		}
	}

	pthread_cond_signal(&cond_anneau);
	pthread_mutex_unlock(&mutex);	
}

/*****************************/
/** FONCTION THREAD ROBOT 6 **/
/*****************************/

void * fonc_robot6(void* tab[]){

	contenu* recup;
	recup = (contenu*) tab;

	robot r6 = instanciationRobot6();	// Robot instancié placé devant l'anneau au compartiment 13

	/** BOUCLE DE FONCTIONNEMENT ENTRE LE ROBOT ET L'ANNEAU **/

	while(1){
		ramasserElementRobot6(recup, &r6);
		usleep(1500000);
	}
}