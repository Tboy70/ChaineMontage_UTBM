/***************************/
/* FICHIER GERANT L'ANNEAU */
/***************************/

#include "main.h"

/*************************************/
/** AFFICHER LE CONTENU DE L'ANNEAU **/
/*************************************/

contenu *afficherAnneau(contenu tab[]){

	int j;

	for(j = 0; j <= 15; ++j){
		if (tab[j].vide == 1)
		{
			printf("Compartiment %d : VIDE\n", j+1);
		}
		else
		{
			if(tab[j].identifiant == 0)
			{
				printf("Compartiment %d : Composant%d\n", j+1, tab[j].num );
			}
			else
			{
				printf("Compartiment %d : Produit%d\n", j+1, tab[j].num );
			}
		}

	}

	return tab;
}

/**********************/
/** TOURNER L'ANNEAU **/    
/**********************/

void tourner(contenu tab[]){

	pthread_mutex_lock(&mutex);		// Verrouille le MUTEX

	if ((tab[0].vide == 1))	// Si le compartiment 1 est vide -> On ajoute un composant sur l'anneau
	{
		/* PREVIENT LA FILE D'ENTREE QU'ELLE A DU TRAVAIL */
		pthread_cond_signal(&attendre_entree);	// On envoie un signal à la file d'entrée pour ammener un élément

		/* L'ANNEAU DORT */ 
		pthread_cond_wait(&cond_anneau,&mutex);
	}

	else if (tab[14].identifiant == 1 && tab[14].vide == 0 && tab[14].produitFinal == 1)	// Si un produit est prêt -> On le retire
	{
		printf("SORTIE D'UN PRODUIT \n");

		 /* PREVIENT LA FILE DE SORTIE QU'ELLE A DU TRAVAIL */
		pthread_cond_signal(&attendre_sortie);	// On envoie un signal à la file de sortie pour retirer

		/* L'ANNEAU DORT */ 
		pthread_cond_wait(&cond_anneau,&mutex);
	}

	else // Si aucune file ne doit travailler -> L'anneau tourne
	{	
		contenu temp;
		int i;

		for(i = 0; i < 15; ++i)
		{
			temp = tab[i];
			tab[i] = tab[i+(15-i)];
			tab[i+(15-i)] = temp; 
		}

	}
	pthread_mutex_unlock(&mutex);	// On dévérouille le MUTEX 
}

/******************************/
/*** FONCTION THREAD ANNEAU ***/
/******************************/

void * fonc_anneau(contenu tab[]){
	contenu* recup;
	recup = (contenu*) tab;
	while(1){
		afficherAnneau(recup);
		tourner(recup);
		printf("\n");
		usleep(1500000);
	}
}