/*****************************/
/* FICHIER GERANT LE ROBOT 5 */
/*****************************/

#include "main.h"

/******************************/
/** INSTANCIATION DU ROBOT 5 **/
/******************************/

robot instanciationRobot5(){	
	robot r5;
	r5.identifiant = 5;
	r5.numeroOperation = 5;
	r5.reserve[0].vide = 1;
	r5.reserve[1].vide = 1;
	r5.reserve[2].vide = 1;

	return r5;
}

/*******************************/
/** MANUFACTURER UN PRODUIT 1 **/
/*******************************/

void manufactureProduit1Op5(contenu tab[], robot* r3){

	if(tab[10].vide == 1){	// Si on peut placer un produit 1 sur l'anneau

		printf("DEPOT DU PRODUIT 1 NOUVELLEMENT MANUFACTURÉ A L'OPERATION 5 -> PRODUIT FINI \n");

		tab[10].identifiant = 1;
		tab[10].num = 1;
		tab[10].vide = 0;
		tab[10].etapeFabrication = 5;
		tab[10].produitFinal = 1;
	}
}

/***********************************************************/
/** MANUFACTURER UN PRODUIT 3 EN EFFECTUANT L'OPERATION 5 **/
/***********************************************************/

void manufactureProduit3Op5(contenu tab[], robot* r3){

	if(tab[10].vide == 1){	// Si on peut placer un produit 3 sur l'anneau

		printf("DEPOT DU PRODUIT 3 NOUVELLEMENT MANUFACTURÉ A L'OPERATION 5 \n");

		tab[10].identifiant = 1;
		tab[10].num = 3;
		tab[10].vide = 0;
		tab[10].etapeFabrication = 5;
	}
}

/*****************************************************************************/
/** RAMASSER LES PRODUITS EN COURS DE FABRICATION NECESSITANT L'OPERATION 5 **/
/*****************************************************************************/

void ramasserElementRobot5(contenu tab[], robot* r5){

	pthread_mutex_lock(&mutex);		// Verrouille le MUTEX

	/*** Si le robot 5 tombe sur le produit 1 à l'opération 3 ***/

	if(tab[10].identifiant == 1 && tab[10].num == 1 && tab[10].vide == 0 && tab[10].etapeFabrication == 3){

		if((*r5).reserve[0].vide == 1){	// Si la première réserve du robot est vide

			printf("Le robot 5 prend le produit 1 \n");

			(*r5).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r5).reserve[0].identifiant = 1; 	// PRODUIT 
			(*r5).reserve[0].num = 1;			// Numéro 1

			tab[10].vide = 1;					// Plus rien sur le compartiment 11 de l'anneau

			manufactureProduit1Op5(tab, r5);

			(*r5).reserve[0].vide = 0;
		}

		else if((*r5).reserve[1].vide == 1){
			printf("Le robot 5 prend le produit 1 \n");

			(*r5).reserve[1].vide = 0;
			(*r5).reserve[1].identifiant = 1;
			(*r5).reserve[1].num = 1;

			tab[10].vide = 1;

			manufactureProduit1Op5(tab, r5);

			(*r5).reserve[1].vide = 0;
		}

		else if((*r5).reserve[2].vide == 1){
			printf("Le robot 5 prend le produit 1 \n");

			(*r5).reserve[2].vide = 0;
			(*r5).reserve[2].identifiant = 1;
			(*r5).reserve[2].num = 1;	

			tab[10].vide = 1;

			manufactureProduit1Op5(tab, r5);

			(*r5).reserve[2].vide = 0;
		}	
	}

	/*** Si le robot 5 tombe sur le produit 3 à l'opération 3 ***/

	if(tab[10].identifiant == 1 && tab[10].num == 3 && tab[10].vide == 0 && tab[10].etapeFabrication == 3){

		if((*r5).reserve[0].vide == 1){	// Si la première réserve du robot est vide

			printf("Le robot 5 prend le produit 3\n");

			(*r5).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r5).reserve[0].identifiant = 1; 	// PRODUIT 
			(*r5).reserve[0].num = 3;			// Numéro 3

			tab[10].vide = 1;					// Plus rien sur le compartiment 11 de l'anneau

			manufactureProduit3Op5(tab, r5);

			(*r5).reserve[0].vide = 0;
		}

		else if((*r5).reserve[1].vide == 1){

			printf("Le robot 5 prend le produit 3\n");

			(*r5).reserve[1].vide = 0;
			(*r5).reserve[1].identifiant = 1;
			(*r5).reserve[1].num = 3;

			tab[10].vide = 1;

			manufactureProduit3Op5(tab, r5);

			(*r5).reserve[1].vide = 0;
		}

		else if((*r5).reserve[2].vide == 1){

			printf("Le robot 5 prend le produit 3\n");

			(*r5).reserve[2].vide = 0;
			(*r5).reserve[2].identifiant = 1;
			(*r5).reserve[2].num = 3;	

			tab[10].vide = 1;

			manufactureProduit3Op5(tab, r5);

			(*r5).reserve[2].vide = 0;
		}
	}

	pthread_cond_signal(&cond_anneau);
	pthread_mutex_unlock(&mutex);	
}

/*****************************/
/** FONCTION THREAD ROBOT 5 **/
/*****************************/

void * fonc_robot5(void* tab[]){

	contenu* recup;
	recup = (contenu*) tab;

	robot r5 = instanciationRobot5();	// Robot instancié placé devant l'anneau au compartiment 11

	/** BOUCLE DE FONCTIONNEMENT ENTRE LE ROBOT ET L'ANNEAU **/

	while(1){
		ramasserElementRobot5(recup, &r5);
		usleep(1500000);
	}
}