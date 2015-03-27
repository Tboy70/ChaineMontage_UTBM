/***********************************/
/* FICHIER GERANT LA FILE D'ENTREE */
/***********************************/

#include "main.h"

/************************************************************************/
/** REMPLISSAGE DU TABLEAU PAR RANDOM (= FILE D'ENTRÉE DES COMPOSANTS) **/
/************************************************************************/

void remplirTableau(contenu tab[]){

	pthread_mutex_lock(&mutex);		// Verrouille le MUTEX

	if(tab[0].vide == 1){

		int nombre_aleatoire;
		nombre_aleatoire = rand()%(5 - 1) + 1;
		tab[0].identifiant = 0;
		tab[0].num = nombre_aleatoire;
		tab[0].vide = 0;

		printf("Nouveau composant inséré : %d%d \n", tab[0].identifiant, tab[0].num);

		/* LA FILE D'ENTRÉE EST EN ATTENTE */
		pthread_cond_wait(&attendre_entree,&mutex);
		
		/* DIT À L'ANNEAU DE TOURNER */
		pthread_cond_signal(&cond_anneau);
	}
	pthread_cond_signal(&cond_anneau);
  	pthread_mutex_unlock(&mutex);	// On dévérouille le MUTEX
  }

/*********************************/
/** FONCTION THREAD FILE ENTREE **/
/*********************************/

  void * fonc_fileEntree(void* tab[]){
  	contenu* recup;
  	recup = (contenu*) tab;

  	while(1){
  		remplirTableau(recup);
  		usleep(1500000); 
  	}
  }