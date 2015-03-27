/************************************/
/* FICHIER GERANT LA FILE DE SORTIE */
/************************************/

#include "main.h"

/*************************/
/** SORTIE DES PRODUITS **/
/*************************/

void sortieAnneau(contenu tab[]){

	pthread_mutex_lock(&mutex);		// Verrouille le MUTEX

	if(tab[14].identifiant == 1 && tab[14].vide == 0 && tab[14].produitFinal == 1){ // Si le produit est fini

		tab[14].vide = 1;

		printf("Produit retiré : %d%d \n", tab[14].identifiant, tab[14].num);

		/* LA FILE DE SORTIE EST EN ATTENTE */
		pthread_cond_wait(&attendre_sortie,&mutex);
	}

	pthread_cond_signal(&cond_anneau); // dit à l'anneau de tourner
 	pthread_mutex_unlock(&mutex);	// On dévérouille le MUTEX

 }

/*********************************/
/** FONCTION THREAD FILE SORTIE **/
/*********************************/

 void * fonc_fileSortie(void* tab[]){
 	contenu* recup;
 	recup = (contenu*) tab;

 	while(1){
 		sortieAnneau(recup);
 		usleep(1500000); 
 	}
 }