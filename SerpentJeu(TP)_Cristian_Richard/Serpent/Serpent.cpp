#include <iostream>
using namespace std;

#include <conio.h>	// pour _kbhit() et _getch()
#include <time.h>	// pour time(int)
#include <stdlib.h>	// pour srand(int) et rand()
#include "RockUtiles.h"	// pour la gestion de l'écran


struct coord {
	int x;
	int y;
};

enum Direction {
	DROITE,
	GAUCHE,
	HAUT,
	BAS
};

// Partie I
// --------
void afficherTerrain(unsigned short nbLignes, unsigned short nbColonnes);



//Partie II

int saisirNiveau();

void creerSouris(unsigned short nbLignes, unsigned short nbColonnes, coord sourisCoord[], unsigned short nbSouris);





//  fonction principale
//  -------------------
int main()
{
	color(3);

	int nbSouris;

	nbSouris = saisirNiveau();
	
	afficherTerrain(30, 70);

	

	// before mega loop, spawn mices, and snake
	// make a mega loop that handles the whole game (something like while(true))
		// display field
		// in that loop catpure key press, asign direction, make movement
		// grow snake if ate food
		// if gameover, shutdown loop
		// GG



	system("pause");
	return 0;
	
}









// ************
// * PARTIE I *
// ************
void afficherTerrain(unsigned short nbLignes, unsigned short nbColonnes)
/*
	Tâche: afficher le contour du terrain
	Paramètres: le nombre de lignes et de colonnes du terrain rectangulaire
*/
{
	for (int i = 0; i < nbLignes; i++) {
		
		for (int j = 0; j < nbColonnes; j++) {
			
			if (i == 0 || i == (nbLignes-1)) {

				cout << "#";
			}
			else {
				if (j == 0 || j == (nbColonnes - 1)) {
					cout << "#";
				}
				else {
					cout << " ";
				}
			}

		}
		cout << endl; 
	}


}


//PARTIE II /////////////


int saisirNiveau() {

	int niveau;

	cout << "Veuillez saisir le niveau du jeu: ";
	cin >> niveau;

	while (cin.fail() == true || cin.peek() != '\n' || niveau < 1 || niveau > 20) {
		cin.clear();
		cin.ignore(512, '\n');
		
		cout << "Attention, veuillez saisir un niveau allant de 1 à 20: ";
		cin >> niveau;
	}

	cin.ignore(512, '\n');

	return niveau;
}



void creerSouris(unsigned short nbLignes, unsigned short nbColonnes, coord sourisCoord[], unsigned short nbSouris) {

}