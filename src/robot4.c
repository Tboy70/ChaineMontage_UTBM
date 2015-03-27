/*****************************/
/* FICHIER GERANT LE ROBOT 4 */
/*****************************/

#include "main.h"

/******************************/
/** INSTANCIATION DU ROBOT 4 **/
/******************************/

robot instanciationRobot4(){	// Robot 4 effectuant l'opération 4 ayant ses réserves de composants vides au départ
	robot r4;
	r4.identifiant = 4;
	r4.numeroOperation = 4;
	r4.reserve[0].vide = 1;
	r4.reserve[1].vide = 1;
	r4.reserve[2].vide = 1;

	return r4;
}

/*************************************************************/
/** MANUFACTURER UN PRODUIT 2 QUI NECESSITE UNE OPERATION 4 **/
/*************************************************************/

void manufactureProduit2Op4(contenu tab[], robot* r4){

	if(tab[8].vide == 1){	// Si on peut placer un produit 2 sur l'anneau

		printf("DEPOT DU PRODUIT 2 NOUVELLEMENT MANUFACTURÉ A L'OPERATION 4 \n");

		tab[8].identifiant = 1;
		tab[8].num = 2;
		tab[8].vide = 0;
		tab[8].etapeFabrication = 4;
	}
}

/********************************/
/** DEPOT DU NOUVEAU PRODUIT 4 **/
/********************************/

void depotProduit4(contenu tab[], robot* r3){

	if(tab[8].vide == 1){	// Si on peut placer un produit 3 sur l'anneau

		printf("DEPOT D'UN NOUVEAU PRODUIT 4 \n");

		(*r3).reserve[0].vide = 1;		// Contient le nouveau produit

		tab[8].identifiant = 1;			// Produit
		tab[8].num = 4;					// Numéro 4
		tab[8].vide = 0;				// Non Vide
		tab[8].etapeFabrication = 4;	// Etape 4 de la fabrication
		tab[8].produitFinal = 0;		// Produit non fini
	}	
}

/********************************/
/** CREER UN NOUVEAU PRODUIT 4 **/
/********************************/

void fabricationProduit4(contenu tab[], robot* r4){

	printf("CRÉATION D'UN PRODUIT 4 \n");

	(*r4).reserve[0].vide = 0;	// Contient le nouveau produit
	(*r4).reserve[1].vide = 1;	// Vide (plus de composant 3 car utilisé pour la fabrication)
	(*r4).reserve[2].vide = 1;	// IDEM

	(*r4).reserve[0].identifiant = 1;	// Produit
	(*r4).reserve[0].num = 4;			// Numéro 4

	depotProduit4(tab, r4);
}

/*****************************************************************************/
/** RAMASSER LES PRODUITS EN COURS DE FABRICATION NECESSITANT L'OPERATION 4 **/
/*****************************************************************************/

void ramasserElementRobot4(contenu tab[], robot* r4){

	pthread_mutex_lock(&mutex);		// Verrouille le MUTEX

	if (tab[8].identifiant == 0 && tab[8].num == 4 && tab[8].vide == 0)	// Si c'est le composant 4
	{
		if ((*r4).reserve[0].vide == 1) // Si la première réserve est vide
		{
			printf("Le robot 4 prend un composant 4 (1)\n");

			(*r4).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r4).reserve[0].identifiant = 0; 	// COMPOSANT
			(*r4).reserve[0].num = 4;			// Numéro 3

			tab[8].vide = 1;					// Plus rien sur le compartiment 9 de l'anneau

		}

		else if ((*r4).reserve[1].vide == 1)
		{
			printf("Le robot 4 prend un composant 4 (2)\n");

			(*r4).reserve[1].vide = 0;			
			(*r4).reserve[1].identifiant = 0; 	
			(*r4).reserve[1].num = 4;			

			tab[8].vide = 1;					

		}

		else if ((*r4).reserve[2].vide == 1)
		{
			printf("Le robot 4 prend un composant 4 (3)\n");

			(*r4).reserve[2].vide = 0;			
			(*r4).reserve[2].identifiant = 0; 	
			(*r4).reserve[2].num = 4;			

			tab[8].vide = 1;					

		}

		if ( ( (*r4).reserve[0].vide == 0 && (*r4).reserve[1].vide == 0 ) || ( (*r4).reserve[1].vide == 0 && (*r4).reserve[2].vide == 0 ) || ( (*r4).reserve[0].vide == 0 && (*r4).reserve[2].vide == 0 ))
		{
			fabricationProduit4(tab, r4);
		}

	}

	/*** Si le robot 4 tombe sur un produit 2 à l'opération 2 ***/

	if (tab[8].identifiant == 1 && tab[8].num == 2 && tab[8].vide == 0 && tab[8].etapeFabrication == 2)	
	{
		if((*r4).reserve[0].vide == 1){	// Si la première réserve du robot est vide

			printf("Le robot 4 prend le produit 2\n");

			(*r4).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r4).reserve[0].identifiant = 1; 	// PRODUIT 
			(*r4).reserve[0].num = 4;			// Numéro 4

			tab[8].vide = 1;	// Plus rien sur le compartiment 13 de l'anneau

			manufactureProduit2Op4(tab, r4);

			(*r4).reserve[0].vide = 0;
		}

		else if((*r4).reserve[1].vide == 1){

			printf("Le robot 4 prend le produit 2\n");

			(*r4).reserve[1].vide = 0;
			(*r4).reserve[1].identifiant = 1;
			(*r4).reserve[1].num = 4;

			tab[8].vide = 1;

			manufactureProduit2Op4(tab, r4);

			(*r4).reserve[1].vide = 0;
		}

		else if((*r4).reserve[2].vide == 1){

			printf("Le robot 4 prend le produit 2\n");

			(*r4).reserve[2].vide = 0;
			(*r4).reserve[2].identifiant = 1;
			(*r4).reserve[2].num = 4;	

			tab[8].vide = 1;

			manufactureProduit2Op4(tab, r4);

			(*r4).reserve[2].vide = 0;
		}
	}

	pthread_cond_signal(&cond_anneau);
	pthread_mutex_unlock(&mutex);	
}

/*****************************/
/** FONCTION THREAD ROBOT 4 **/
/*****************************/

void * fonc_robot4(void* tab[]){

	contenu* recup;
	recup = (contenu*) tab;

	robot r4 = instanciationRobot4();	// Robot instancié placé devant l'anneau au compartiment 9

	/** BOUCLE DE FONCTIONNEMENT ENTRE LE ROBOT ET L'ANNEAU **/

	while(1){
		ramasserElementRobot4(recup, &r4);
		usleep(1500000);
	}
}