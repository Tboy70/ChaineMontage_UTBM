/*****************************/
/* FICHIER GERANT LE ROBOT 2 */
/*****************************/

#include "main.h"

/******************************/
/** INSTANCIATION DU ROBOT 2 **/
/******************************/

robot instanciationRobot2(){	// Robot 2 effectuant l'opération 2 ayant ses réserves de composants vides au départ
	robot r2;
	r2.identifiant = 2;
	r2.numeroOperation = 2;
	r2.reserve[0].vide = 1;
	r2.reserve[1].vide = 1;
	r2.reserve[2].vide = 1;

	return r2;
}

/*************************************************************/
/** MANUFACTURER UN PRODUIT 1 QUI NECESSITE UNE OPERATION 2 **/
/*************************************************************/

void manufactureProduit1Op2(contenu tab[], robot* r2){

	if(tab[4].vide == 1){	// Si on peut placer un produit 1 sur l'anneau

		printf("DEPOT DU PRODUIT 1 NOUVELLEMENT MANUFACTURÉ A L'OPERATION 2 \n");

		tab[4].identifiant = 1;
		tab[4].num = 1;
		tab[4].vide = 0;
		tab[4].etapeFabrication = 2;
	}
}

/*********************************************/
/** DEPOT DU NOUVEAU PRODUIT 2 SUR L'ANNEAU **/
/*********************************************/

void depotProduit2(contenu tab[], robot* r2){

	if(tab[4].vide == 1){	// Si on peut placer un produit 2 sur l'anneau

		printf("DEPOT D'UN NOUVEAU PRODUIT 2\n");

		(*r2).reserve[0].vide = 1;		// Contient le nouveau produit

		tab[4].identifiant = 1;			// Produit
		tab[4].num = 2;					// Numéro 2
		tab[4].vide = 0;				// Non Vide
		tab[4].etapeFabrication = 2;	// Etape 2 de la fabrication (Composant 2)
		tab[4].produitFinal = 0;		// Produit non fini
	}
}

/********************************/
/** CREER UN NOUVEAU PRODUIT 2 **/
/********************************/

void fabricationProduit2(contenu tab[], robot* r2){

	printf("CRÉATION D'UN PRODUIT 2 \n");

	(*r2).reserve[0].vide = 0;	// Contient le nouveau produit
	(*r2).reserve[1].vide = 1;	// Vide (plus de composant 2 car utilisé pour la fabrication)
	(*r2).reserve[2].vide = 1;	// IDEM

	(*r2).reserve[0].identifiant = 1;	// Produit
	(*r2).reserve[0].num = 2;			// Numéro 2

	depotProduit2(tab, r2);
}

/************************************************************************************************/
/** RAMASSER LES COMPOSANTS C2 OU UN PRODUIT EN COURS DE FABRICATION NECESSITANT L'OPERATION 2 **/
/************************************************************************************************/

void ramasserElementRobot2(contenu tab[], robot* r2){

	pthread_mutex_lock(&mutex);		// Verrouille le MUTEX

	if (tab[4].identifiant == 0 && tab[4].num == 2 && tab[4].vide == 0)	// Si le robot 2 tombe sur un composant 2
	{
		if((*r2).reserve[0].vide == 1){			// Si la première réserve du robot 2 est vide

			printf("Le robot 2 prend un composant 2 (1)\n");

			(*r2).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r2).reserve[0].identifiant = 0; 	// COMPOSANT
			(*r2).reserve[0].num = 2;			// Numéro 2

			tab[4].vide = 1;					// Plus rien sur le compartiment 5 de l'anneau
		}

		else if((*r2).reserve[1].vide == 1){	// Si la deuxième réserve du robot 2 est vide

			printf("Le robot 2 prend un composant 2 (2)\n");

			(*r2).reserve[1].vide = 0;
			(*r2).reserve[1].identifiant = 0;
			(*r2).reserve[1].num = 2;

			tab[4].vide = 1;

		}

		else if((*r2).reserve[2].vide == 1){	// Si la troisième réserve du robot 2 est vide

			printf("Le robot 2 prend un composant 2 (3)\n");

			(*r2).reserve[2].vide = 0;
			(*r2).reserve[2].identifiant = 0;
			(*r2).reserve[2].num = 2;	

			tab[4].vide = 1;

			/** LE ROBOT 2 A LES TROIS COMPOSANTS NECESSAIRES POUR FABRIQUER LE PRODUIT 2 **/

			fabricationProduit2(tab, r2);	// Fonction de création du produit

		}
	}

	/*** Si le robot 2 tombe sur le produit 1 à l'opération 1***/

	else if(tab[4].identifiant == 1 && tab[4].num == 1 && tab[4].vide == 0 && tab[4].etapeFabrication == 1){	

		if((*r2).reserve[0].vide == 1){			// Si la première réserve du robot est vide

			printf("Le robot 2 prend le produit 1 \n");

			(*r2).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r2).reserve[0].identifiant = 1; 	// PRODUIT 
			(*r2).reserve[0].num = 1;			// Numéro 1

			tab[4].vide = 1;					// Plus rien sur le compartiment 13 de l'anneau

			manufactureProduit1Op2(tab, r2);

			(*r2).reserve[0].vide = 1;

		}

		else if((*r2).reserve[1].vide == 1){

			printf("Le robot 2 prend le produit 1 \n");

			(*r2).reserve[1].vide = 0;
			(*r2).reserve[1].identifiant = 1;
			(*r2).reserve[1].num = 1;

			tab[4].vide = 1;

			manufactureProduit1Op2(tab, r2);

			(*r2).reserve[1].vide = 0;

		}

		else if((*r2).reserve[2].vide == 1){

			printf("Le robot 2 prend le produit \n");

			(*r2).reserve[2].vide = 0;
			(*r2).reserve[2].identifiant = 1;
			(*r2).reserve[2].num = 1;	

			tab[4].vide = 1;

			manufactureProduit1Op2(tab, r2);

			(*r2).reserve[2].vide = 0;
		}
	}

	pthread_cond_signal(&cond_anneau);
	pthread_mutex_unlock(&mutex);	
}

/*****************************/
/** FONCTION THREAD ROBOT 2 **/
/*****************************/

void * fonc_robot2(void* tab[]){

	contenu* recup;
	recup = (contenu*) tab;

	robot r2 = instanciationRobot2();	// Robot instancié placé devant l'anneau au compartiment 5

	/** BOUCLE DE FONCTIONNEMENT ENTRE LE ROBOT ET L'ANNEAU **/

	while(1){
		ramasserElementRobot2(recup, &r2);
		usleep(1500000);
	}
}