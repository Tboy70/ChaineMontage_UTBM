/*****************************/
/* FICHIER GERANT LE ROBOT 3 */
/*****************************/

#include "main.h"

/******************************/
/** INSTANCIATION DU ROBOT 3 **/
/******************************/

robot instanciationRobot3(){	// Robot 3 effectuant l'opération 3 ayant ses réserves de composants vides au départ
	robot r3;
	r3.identifiant = 3;
	r3.numeroOperation = 3;
	r3.reserve[0].vide = 1;
	r3.reserve[1].vide = 1;
	r3.reserve[2].vide = 1;

	return r3;
}


/*************************************************************/
/** MANUFACTURER UN PRODUIT 1 QUI NECESSITE UNE OPERATION 3 **/
/*************************************************************/

void manufactureProduit1Op3(contenu tab[], robot* r3){

	if(tab[6].vide == 1){	// Si on peut placer un produit 1 sur l'anneau

		printf("DEPOT DU PRODUIT 1 NOUVELLEMENT MANUFACTURÉ A L'OPERATION 3 \n");

		tab[6].identifiant = 1;
		tab[6].num = 1;
		tab[6].vide = 0;
		tab[6].etapeFabrication = 3;
	}
}

/*************************************************************/
/** MANUFACTURER UN PRODUIT 3 QUI NECESSITE UNE OPERATION 3 **/
/*************************************************************/

void manufactureProduit3Op3(contenu tab[], robot* r3){

	if(tab[6].vide == 1){	// Si on peut placer un produit 1 sur l'anneau

		printf("DEPOT DU PRODUIT 3 NOUVELLEMENT MANUFACTURÉ A L'OPERATION 3  -> PRODUIT FINI \n");

		tab[6].identifiant = 1;
		tab[6].num = 3;
		tab[6].vide = 0;
		tab[6].etapeFabrication = 3;
		tab[6].produitFinal = 1;
	}
}

/*********************************************/
/** DEPOT DU NOUVEAU PRODUIT 3 SUR L'ANNEAU **/
/*********************************************/

void depotProduit3(contenu tab[], robot* r3){

	if(tab[6].vide == 1){	// Si on peut placer un produit 3 sur l'anneau

		printf("DEPOT D'UN NOUVEAU PRODUIT 3 \n");

		(*r3).reserve[0].vide = 1;		// Contient le nouveau produit

		tab[6].identifiant = 1;			// Produit
		tab[6].num = 3;					// Numéro 3
		tab[6].vide = 0;				// Non Vide
		tab[6].etapeFabrication = 3;	// Etape 3 de la fabrication (Composant 3)
		tab[6].produitFinal = 0;		// Produit non fini
	}	
}

/********************************/
/** CREER UN NOUVEAU PRODUIT 3 **/
/********************************/

void fabricationProduit3(contenu tab[], robot* r3){

	printf("CRÉATION D'UN PRODUIT 3 \n");

	(*r3).reserve[0].vide = 0;	// Contient le nouveau produit
	(*r3).reserve[1].vide = 1;	// Vide (plus de composant 3 car utilisé pour la fabrication)
	(*r3).reserve[2].vide = 1;	// IDEM

	(*r3).reserve[0].identifiant = 1;	// Produit
	(*r3).reserve[0].num = 3;			// Numéro 3

	depotProduit3(tab, r3);
}

/***********************************************************************************************/
/** RAMASSER LES COMPOSANT C3 OU UN PRODUIT EN COURS DE FABRICATION NECESSITANT L'OPERATION 3 **/
/***********************************************************************************************/

void ramasserElementRobot3(contenu tab[], robot* r3){

	pthread_mutex_lock(&mutex);		// Verrouille le MUTEX

	if (tab[6].identifiant == 0 && tab[6].num == 3 && tab[6].vide == 0)	// Si le robot 3 tombe sur un composant 3
	{
		if((*r3).reserve[0].vide == 1){			// Si la première réserve du robot 3 est vide

			printf("Le robot 3 prend un composant 3 (1)\n");

			(*r3).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r3).reserve[0].identifiant = 0; 	// COMPOSANT
			(*r3).reserve[0].num = 3;			// Numéro 3

			tab[6].vide = 1;					// Plus rien sur le compartiment 7 de l'anneau

			fabricationProduit3(tab, r3);	// Fonction de création du produit 3
		}

		else if((*r3).reserve[1].vide == 1){	// Si la deuxième réserve du robot 3 est vide

			printf("Le robot 3 prend un composant 3 (2)\n");

			(*r3).reserve[1].vide = 0;
			(*r3).reserve[1].identifiant = 0;
			(*r3).reserve[1].num = 3;

			tab[6].vide = 1;

			fabricationProduit3(tab, r3);
		}

		else if((*r3).reserve[2].vide == 1){	// Si la troisième réserve du robot 3 est vide

			printf("Le robot 3 prend un composant 3 (3)\n");

			(*r3).reserve[2].vide = 0;
			(*r3).reserve[2].identifiant = 0;
			(*r3).reserve[2].num = 3;	

			tab[6].vide = 1;

			fabricationProduit3(tab, r3);
		}
	}
	
	/*** Si le robot 3 tombe sur le produit 1 à l'opération 2 ***/

	if(tab[6].identifiant == 1 && tab[6].num == 1 && tab[6].vide == 0 && tab[6].etapeFabrication == 2){

		if((*r3).reserve[0].vide == 1){	// Si la première réserve du robot est vide

			printf("Le robot 3 prend le produit 1 \n");

			(*r3).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r3).reserve[0].identifiant = 1; 	// PRODUIT 
			(*r3).reserve[0].num = 1;			// Numéro 1

			tab[6].vide = 1;					// Plus rien sur le compartiment 7 de l'anneau

			manufactureProduit1Op3(tab, r3);

			(*r3).reserve[0].vide = 0;
		}

		else if((*r3).reserve[1].vide == 1){

			printf("Le robot 3 prend le produit 1 \n");

			(*r3).reserve[1].vide = 0;
			(*r3).reserve[1].identifiant = 1;
			(*r3).reserve[1].num = 1;

			tab[6].vide = 1;

			manufactureProduit1Op3(tab, r3);

			(*r3).reserve[1].vide = 0;
		}

		else if((*r3).reserve[2].vide == 1){

			printf("Le robot 3 prend le produit 1 \n");

			(*r3).reserve[2].vide = 0;
			(*r3).reserve[2].identifiant = 1;
			(*r3).reserve[2].num = 1;	

			tab[6].vide = 1;

			manufactureProduit1Op3(tab, r3);

			(*r3).reserve[2].vide = 0;
		}	
	}
	
	/*** Si le robot 3 tombe sur le produit 3 à l'opération 1 ***/

	if(tab[6].identifiant == 1 && tab[6].num == 3 && tab[6].vide == 0 && tab[6].etapeFabrication == 1){	

		if((*r3).reserve[0].vide == 1){	// Si la première réserve du robot est vide

			printf("Le robot 3 prend le produit 3 \n");

			(*r3).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r3).reserve[0].identifiant = 1; 	// PRODUIT 
			(*r3).reserve[0].num = 3;			// Numéro 3

			tab[6].vide = 1;					// Plus rien sur le compartiment 13 de l'anneau

			manufactureProduit3Op3(tab, r3);

			(*r3).reserve[0].vide = 0;
		}

		else if((*r3).reserve[1].vide == 1){

			printf("Le robot 3 prend le produit 3 \n");

			(*r3).reserve[1].vide = 0;
			(*r3).reserve[1].identifiant = 1;
			(*r3).reserve[1].num = 3;

			tab[6].vide = 1;

			manufactureProduit3Op3(tab, r3);

			(*r3).reserve[1].vide = 0;
		}

		else if((*r3).reserve[2].vide == 1){

			printf("Le robot 3 prend le produit 3 \n");

			(*r3).reserve[2].vide = 0;
			(*r3).reserve[2].identifiant = 1;
			(*r3).reserve[2].num = 3;	

			tab[6].vide = 1;

			manufactureProduit3Op3(tab, r3);

			(*r3).reserve[2].vide = 0;
		}
	}
	
	pthread_cond_signal(&cond_anneau);
	pthread_mutex_unlock(&mutex);
}

/*****************************/
/** FONCTION THREAD ROBOT 3 **/
/*****************************/

void * fonc_robot3(void* tab[]){

	contenu* recup;
	recup = (contenu*) tab;

	robot r3 = instanciationRobot3();	// Robot instancié placé devant l'anneau au compartiment 7

	/** BOUCLE DE FONCTIONNEMENT ENTRE LE ROBOT ET L'ANNEAU **/

	while(1){
		ramasserElementRobot3(recup, &r3);
		usleep(1500000);
	}
}