/*********************************/
/* PROGRAMME PRINCIPAL DU PROJET */
/*********************************/

#include "main.h"

/**************************************************/
/** DESTRUCTION DU MUTEX LORS D'UN SIGNAL SIGINT **/
/**************************************************/

void traitantSIGINT(int num)
{
	pthread_mutex_destroy(&mutex);
	exit(0);
	return;
}

/*************************/
/** PROGRAMME PRINCIPAL **/
/*************************/

int main(int argc, char const *argv[])
{
	srand(time(0));	// Pour le random

	signal(SIGINT,traitantSIGINT);

	/** Déclaration des threads **/
	pthread_t anneau;
	pthread_t entreeCompo;
	pthread_t sortieProduit;
	pthread_t robot1;
	pthread_t robot2;
	pthread_t robot3;
	pthread_t robot4;
	pthread_t robot5;
	pthread_t robot6;

  	/** INITIALISATION DU TABLEAU (pièces disposé de manière à lancer l'activité) **/

	contenu tab[16];

	tab[0].vide = 0;
	tab[0].identifiant = 0;
	tab[0].num = 1;
	tab[0].etapeFabrication = 0;
	tab[0].produitFinal = 0;

	tab[1].vide = 0;
	tab[1].identifiant = 0;
	tab[1].num = 4;
	tab[1].etapeFabrication = 0;
	tab[1].produitFinal = 0;

	tab[2].vide = 1;
	tab[2].identifiant = 0;
	tab[2].num = 0;
	tab[2].etapeFabrication = 0;
	tab[2].produitFinal = 0;

	tab[3].vide = 0;
	tab[3].identifiant = 0;
	tab[3].num = 1;
	tab[3].etapeFabrication = 0;
	tab[3].produitFinal = 0;

	tab[4].vide = 1;
	tab[4].identifiant = 0;
	tab[4].num = 0;
	tab[4].etapeFabrication = 0;
	tab[4].produitFinal = 0;

	tab[5].vide = 0;
	tab[5].identifiant = 0;
	tab[5].num = 4;
	tab[5].etapeFabrication = 0;
	tab[5].produitFinal = 0;

	tab[6].vide = 1;
	tab[6].identifiant = 0;
	tab[6].num = 0;
	tab[6].etapeFabrication = 0;
	tab[6].produitFinal = 0;

	tab[7].vide = 0;
	tab[7].identifiant = 0;
	tab[7].num = 2;
	tab[7].etapeFabrication = 0;
	tab[7].produitFinal = 0;

	tab[8].vide = 0;
	tab[8].identifiant = 0;
	tab[8].num = 1;
	tab[8].etapeFabrication = 0;
	tab[8].produitFinal = 0;

	tab[9].vide = 1;
	tab[9].identifiant = 0;
	tab[9].num = 0;
	tab[9].etapeFabrication = 0;
	tab[9].produitFinal = 0;

	tab[10].vide = 0;
	tab[10].identifiant = 0;
	tab[10].num = 2;
	tab[10].etapeFabrication = 0;
	tab[10].produitFinal = 0;

	tab[11].vide = 1;
	tab[11].identifiant = 0;
	tab[11].num = 0;
	tab[11].etapeFabrication = 0;
	tab[11].produitFinal = 0;

	tab[12].vide = 0;
	tab[12].identifiant = 0;
	tab[12].num = 2;
	tab[12].etapeFabrication = 0;
	tab[12].produitFinal = 0;

	tab[13].vide = 1;
	tab[13].identifiant = 0;
	tab[13].num = 0;
	tab[13].etapeFabrication = 0;
	tab[13].produitFinal = 0;

	tab[14].vide = 0;
	tab[14].identifiant = 0;
	tab[14].num = 3;
	tab[14].etapeFabrication = 0;
	tab[14].produitFinal = 0;

	tab[15].vide = 1;
	tab[15].identifiant = 0;
	tab[15].num = 0;
	tab[15].etapeFabrication = 0;
	tab[15].produitFinal = 0;

    /** CREATIONS DES THREADS **/

	pthread_create(&anneau, NULL, (void*)fonc_anneau, (void *)tab);
	pthread_create(&entreeCompo, NULL, (void*)fonc_fileEntree, (void *)tab);
	pthread_create(&sortieProduit, NULL, (void*)fonc_fileSortie, (void *)tab);
	pthread_create(&robot1, NULL, (void*)fonc_robot1, (void *)tab);
	pthread_create(&robot2, NULL, (void*)fonc_robot2, (void *)tab);
	pthread_create(&robot3, NULL, (void*)fonc_robot3, (void *)tab);
	pthread_create(&robot4, NULL, (void*)fonc_robot4, (void *)tab);
	pthread_create(&robot5, NULL, (void*)fonc_robot5, (void *)tab);
	pthread_create(&robot6, NULL, (void*)fonc_robot6, (void *)tab);

	pthread_join(anneau, NULL); 
	pthread_join(entreeCompo, NULL); 
	pthread_join(sortieProduit, NULL); 
	pthread_join(robot1, NULL); 
	pthread_join(robot2, NULL); 
	pthread_join(robot3, NULL); 
	pthread_join(robot4, NULL); 
	pthread_join(robot5, NULL); 
	pthread_join(robot6, NULL); 

	pthread_exit(NULL);

	exit(0);

	return 0;
}