/***************************/
/**** HEADER DU PROJET *****/
/***************************/

/**************************************/
/*** FICHIERS D'EN-TETE NECESSAIRES ***/
/**************************************/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

/**********************************************************************/
/*** STRUCTURE DEFINISSANT LE CONTENU D'UN COMPARTIMENT DE L'ANNEAU ***/
/**********************************************************************/

typedef struct contenuCompartement {
    int identifiant; // 0-> composant, 1-> produit
    int num;  // numéro du produit ou du composant (produit1, composant2 ...) 
    int vide; // 0-> NonVide, 1 -> vide
    int etapeFabrication;	// Numéro correspondant à l'étape de fabrication
    int produitFinal; 	// 0 -> Produit non fini; 1 -> Produit fini
}contenu; 

/**************************************/
/*** STRUCTURE DEFINISSANT UN ROBOT ***/
/**************************************/

typedef struct defRobot{
	int identifiant; // Identifiant du robot
	contenu reserve[3];	// Liste de composants (3 composants par robot)
	int numeroOperation;	// Quelle opération le robot execute t-il ?
}robot;

/*********************************************/
/*** VARIABLES UTILISEES DANS LES FICHIERS ***/
/*********************************************/

pthread_mutex_t mutex; // Un MUTEX

pthread_cond_t attendre_entree;	// Condition de synchronisation de la file d'entrée des composants
pthread_cond_t attendre_sortie;	// Condition de synchronisation de la file de sortie des produits
pthread_cond_t cond_anneau;			// Condition de synchronisation de l'anneau
pthread_cond_t cond_robot1;			// Condition de synchronisation du robot 1 
pthread_cond_t cond_robot2;			// Condition de synchronisation du robot 2
pthread_cond_t cond_robot3;			// Condition de synchronisation du robot 3
pthread_cond_t cond_robot4;			// Condition de synchronisation du robot 4
pthread_cond_t cond_robot5;			// Condition de synchronisation du robot 5
pthread_cond_t cond_robot6;			// Condition de synchronisation du robot 6

/********************************************/
/*** FONCTIONS UTILISEES POUR LES THREADS ***/
/********************************************/

	/* FONCTIONS POUR L'ANNEAU */
	void * fonc_anneau(contenu tab[]);

	/* FONCTIONS POUR LA FILE D'ENTREE */
	void * fonc_fileEntree(void* tab[]);

	/* FONCTIONS POUR LA FILE DE SORTIE */
	void * fonc_fileSortie(void* tab[]);

	/* FONCTIONS POUR LE ROBOT 1 */
	void * fonc_robot1(void* tab[]);

	/* FONCTIONS POUR LE ROBOT 2 */
	void * fonc_robot2(void* tab[]);

	/* FONCTIONS POUR LE ROBOT 3 */
	void * fonc_robot3(void* tab[]);

	/* FONCTIONS POUR LE ROBOT 4 */
	void * fonc_robot4(void* tab[]);

	/* FONCTIONS POUR LE ROBOT 5 */
	void * fonc_robot5(void* tab[]);

	/* FONCTIONS POUR LE ROBOT 6 */
	void * fonc_robot6(void* tab[]);

