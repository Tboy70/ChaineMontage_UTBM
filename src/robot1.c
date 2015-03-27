/*****************************/
/* FICHIER GERANT LE ROBOT 1 */
/*****************************/

#include "main.h"

/******************************/
/** INSTANCIATION DU ROBOT 1 **/
/******************************/

robot instanciationRobot1(){	// Robot 1 effectuant l'opération 1 ayant ses réserves de composants vides au départ
	robot r1;
	r1.identifiant = 1;
	r1.numeroOperation = 1;
	r1.reserve[0].vide = 1;
	r1.reserve[1].vide = 1;
	r1.reserve[2].vide = 1;

	return r1;
}

/*************************************************************/
/** MANUFACTURER UN PRODUIT 2 QUI NECESSITE UNE OPERATION 1 **/
/*************************************************************/

void manufactureProduit2Op1(contenu tab[], robot* r2){

	if(tab[2].vide == 1){	// Si on peut placer un produit 2 sur l'anneau

		printf("DEPOT DU PRODUIT 2 NOUVELLEMENT MANUFACTURÉ A L'OPERATION 1 \n");

		tab[2].identifiant = 1;
		tab[2].num = 2;
		tab[2].vide = 0;
		tab[2].etapeFabrication = 1;
	}
}

/*************************************************************/
/** MANUFACTURER UN PRODUIT 3 QUI NECESSITE UNE OPERATION 1 **/
/*************************************************************/

void manufactureProduit3Op1(contenu tab[], robot* r2){

	if(tab[2].vide == 1){	// Si on peut placer un produit 3 sur l'anneau

		printf("DEPOT DU PRODUIT 3 NOUVELLEMENT MANUFACTURÉ A L'OPERATION 1 \n");

		tab[2].identifiant = 1;
		tab[2].num = 3;
		tab[2].vide = 0;
		tab[2].etapeFabrication = 1;
	}
}

/*************************************************************/
/** MANUFACTURER UN PRODUIT 4 QUI NECESSITE UNE OPERATION 1 **/
/*************************************************************/

void manufactureProduit4Op1(contenu tab[], robot* r2){

	if(tab[2].vide == 1){	// Si on peut placer un produit 4 sur l'anneau

		printf("DEPOT DU PRODUIT 4 NOUVELLEMENT MANUFACTURÉ A L'OPERATION 1 -> PRODUIT FINI \n");

		tab[2].identifiant = 1;
		tab[2].num = 4;
		tab[2].vide = 0;
		tab[2].etapeFabrication = 1;
		tab[2].produitFinal = 1;
	}
}

/*********************************************/
/** DEPOT DU NOUVEAU PRODUIT 1 SUR L'ANNEAU **/
/*********************************************/

void depotProduit1(contenu tab[], robot* r1){

	if(tab[2].vide == 1){				// Si on peut placer un produit sur le compartiment

		printf("DEPOT D'UN NOUVEAU PRODUIT 1\n");

		(*r1).reserve[0].vide = 1;		// On libère la réserve du robot 

		tab[2].identifiant = 1;			// Produit
		tab[2].num = 1;					// Numéro 1
		tab[2].vide = 0;				// Compartiment non vide
		tab[2].etapeFabrication = 1;	// Etape 1 de la fabrication (= Opération 1)
		tab[2].produitFinal = 0;		// Produit non fini
	}
}

/********************************/
/** CREER UN NOUVEAU PRODUIT 1 **/
/********************************/

void fabricationProduit1(contenu tab[], robot* r1){

	printf("CRÉATION D'UN PRODUIT 1 \n");

	(*r1).reserve[0].vide = 0;	// Contient le nouveau produit 1 donc pas vide
	(*r1).reserve[1].vide = 1;	// Vide (plus de composant 1 car utilisé pour la fabrication)
	(*r1).reserve[2].vide = 1;	// IDEM

	(*r1).reserve[0].identifiant = 1;	// Produit
	(*r1).reserve[0].num = 1;			// Numéro 1

	depotProduit1(tab, r1);		// Déposition du produit 1 sur l'anneau
}

/***********************************************************************************************/
/** RAMASSER LES COMPOSANT C1 OU UN PRODUIT EN COURS DE FABRICATION NECESSITANT L'OPERATION 1 **/
/***********************************************************************************************/

void ramasserElementRobot1(contenu tab[], robot* r1){

	pthread_mutex_lock(&mutex);		// Verrouille le MUTEX

	if (tab[2].identifiant == 0 && tab[2].num == 1 && tab[2].vide == 0)	// Si le robot 1 tombe sur un composant 1
	{
		if((*r1).reserve[0].vide == 1){			// Si la première réserve du robot 1 est vide

			printf("Le robot 1 prend un composant 1 (1)\n");

			(*r1).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r1).reserve[0].identifiant = 0; 	// COMPOSANT
			(*r1).reserve[0].num = 1;			// Numéro 1

			tab[2].vide = 1;					// Plus rien sur le compartiment 3 de l'anneau
		}

		else if((*r1).reserve[1].vide == 1){	// Si la deuxième réserve du robot 1 est vide

			printf("Le robot 1 prend un composant 1 (2)\n");

			(*r1).reserve[1].vide = 0;
			(*r1).reserve[1].identifiant = 0;
			(*r1).reserve[1].num = 1;

			tab[2].vide = 1;
		}

		else if((*r1).reserve[2].vide == 1){	// Si la troisième réserve du robot 1 est vide

			printf("Le robot 1 prend un composant 1 (3)\n");

			(*r1).reserve[2].vide = 0;
			(*r1).reserve[2].identifiant = 0;
			(*r1).reserve[2].num = 1;	

			tab[2].vide = 1;
			
			/** LE ROBOT 1 A LES TROIS COMPOSANTS NECESSAIRES POUR FABRIQUER LE PRODUIT 1 **/

			fabricationProduit1(tab, r1);	// Fonction de création du produit 1
		}
	}

	/*** Si le robot 1 tombe sur le produit 3 à l'opération 5 ***/

	if(tab[2].identifiant == 1 && tab[2].num == 3 && tab[2].vide == 0 && tab[2].etapeFabrication == 5){
		
		if((*r1).reserve[0].vide == 1){			// Si la première réserve du robot est vide

			printf("Le robot 1 prend le produit 3 \n");

			(*r1).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r1).reserve[0].identifiant = 1; 	// PRODUIT 
			(*r1).reserve[0].num = 3;			// Numéro 3

			tab[2].vide = 1;					// Plus rien sur le compartiment 3 de l'anneau

			manufactureProduit3Op1(tab, r1);

			(*r1).reserve[0].vide = 0;
		}

		else if((*r1).reserve[1].vide == 1){

			printf("Le robot 1 prend le produit 3\n");

			(*r1).reserve[1].vide = 0;
			(*r1).reserve[1].identifiant = 1;
			(*r1).reserve[1].num = 3;

			tab[2].vide = 1;

			manufactureProduit3Op1(tab, r1);

			(*r1).reserve[1].vide = 0;
		}

		else if((*r1).reserve[2].vide == 1){

			printf("Le robot 1 prend le produit 3\n");

			(*r1).reserve[2].vide = 0;
			(*r1).reserve[2].identifiant = 1;
			(*r1).reserve[2].num = 3;	

			tab[2].vide = 1;

			manufactureProduit3Op1(tab, r1);

			(*r1).reserve[2].vide = 0;
		}
	}

	/*** Si le robot 1 tombe sur le produit 2 à l'opération 4 ***/

	if(tab[2].identifiant == 1 && tab[2].num == 2 && tab[2].vide == 0 && tab[2].etapeFabrication == 4){
		
		if((*r1).reserve[0].vide == 1){	// Si la première réserve du robot est vide

			printf("Le robot 1 prend le produit 2\n");

			(*r1).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r1).reserve[0].identifiant = 1; 	// PRODUIT 
			(*r1).reserve[0].num = 2;			// Numéro 2

			tab[2].vide = 1;					// Plus rien sur le compartiment 3 de l'anneau

			manufactureProduit2Op1(tab, r1);

			(*r1).reserve[0].vide = 0;
		}

		else if((*r1).reserve[1].vide == 1){

			printf("Le robot 1 prend le produit 2\n");

			(*r1).reserve[1].vide = 0;
			(*r1).reserve[1].identifiant = 1;
			(*r1).reserve[1].num = 2;

			tab[2].vide = 1;

			manufactureProduit2Op1(tab, r1);

			(*r1).reserve[1].vide = 0;
		}

		else if((*r1).reserve[2].vide == 1){

			printf("Le robot 1 prend le produit 2\n");

			(*r1).reserve[2].vide = 0;
			(*r1).reserve[2].identifiant = 1;
			(*r1).reserve[2].num = 2;	

			tab[2].vide = 1;

			manufactureProduit2Op1(tab, r1);

			(*r1).reserve[2].vide = 0;
		}
	}

	/*** Si le robot 1 tombe sur le produit 4 à l'opération 6 ***/

	if(tab[2].identifiant == 1 && tab[2].num == 4 && tab[2].vide == 0 && tab[2].etapeFabrication == 6){
		
		if((*r1).reserve[0].vide == 1){	// Si la première réserve du robot est vide

			printf("Le robot 1 prend le produit 4\n");

			(*r1).reserve[0].vide = 0;			// Elle n'est plus vide
			(*r1).reserve[0].identifiant = 1; 	// PRODUIT 
			(*r1).reserve[0].num = 4;			// Numéro 4

			tab[2].vide = 1;					// Plus rien sur le compartiment 3 de l'anneau

			manufactureProduit4Op1(tab, r1);

			(*r1).reserve[0].vide = 0;
		}

		else if((*r1).reserve[1].vide == 1){

			printf("Le robot 1 prend le produit 4\n");

			(*r1).reserve[1].vide = 0;
			(*r1).reserve[1].identifiant = 1;
			(*r1).reserve[1].num = 4;

			tab[2].vide = 1;

			manufactureProduit4Op1(tab, r1);

			(*r1).reserve[1].vide = 0;
		}

		else if((*r1).reserve[2].vide == 1){

			printf("Le robot 1 prend le produit 4\n");

			(*r1).reserve[2].vide = 0;
			(*r1).reserve[2].identifiant = 1;
			(*r1).reserve[2].num = 4;	

			tab[2].vide = 1;

			manufactureProduit4Op1(tab, r1);

			(*r1).reserve[2].vide = 0;
		}
	}

	pthread_cond_signal(&cond_anneau);
	pthread_mutex_unlock(&mutex);	
}

/*****************************/
/** FONCTION THREAD ROBOT 1 **/
/*****************************/

void * fonc_robot1(void* tab[]){

	contenu* recup;
	recup = (contenu*) tab;

	robot r1 = instanciationRobot1();	// Robot instancié placé devant l'anneau au compartiment 3

	/** BOUCLE DE FONCTIONNEMENT ENTRE LE ROBOT ET L'ANNEAU **/

	while(1){
		ramasserElementRobot1(recup, &r1);
		usleep(1500000);
	}
}