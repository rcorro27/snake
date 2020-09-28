#include <iostream>
using namespace std;

#include <conio.h>	// pour _kbhit() et _getch()
#include <time.h>	// pour time(int)
#include <stdlib.h>	// pour srand(int) et rand()
#include "RockUtiles.h"	// pour la gestion de l'�cran


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
int recupererTouche();
Direction calculerDirectionTouche(int touche);
void positionAleatoire(unsigned short nbLignes, unsigned short nbColonnes, coord &coord);
void deplacerSerpentI(Direction direction, coord &teteSerpentCoord);

// Partie II
// ---------
int saisirNiveau();
void creerSouris(unsigned short nbLignes, unsigned short nbColonnes,
	coord sourisCoord[], unsigned short nbSouris);
void afficherSouris(coord sourisCoord[], unsigned short nbSouris);
void deplacerSerpentII(Direction direction,
	coord serpentCoord[], unsigned short &tailleSerpent,
	coord sourisCoord[], unsigned short &nbSouris);
/*	ou	*/
void deplacerSerpentII(Direction direction, coord serpentCoord[],
	unsigned short &indiceTete, unsigned short &indiceQueue,
	coord sourisCoord[], unsigned short &nbSouris);
bool testerCollision(coord teteSerpentCoord, coord sourisCoord[], unsigned short &nbSouris);


// Partie III (BONUS)
// ------------------
void deplacerSouris(coord sourisCoord[], unsigned short nbSouris);
void placerMurs(unsigned short nbLignes, unsigned short nbColonnes, unsigned short nbMurs);


//  fonction principale
//  -------------------
int main()
{

	srand(time(0));

	curseurVisible(false);
	Direction mouvement = DROITE;

	unsigned short niveau = saisirNiveau();

	coord souris[20];
	coord serpent[20];

	bool won = false;

	const int LIGNES = 70;
	const int COLONNES = 30;

	unsigned short tailleSerpent = 1;

	//Direction mouvement = DROITE;
	coord o; // tete du serpent
	positionAleatoire(LIGNES, COLONNES, o);
	gotoXY(o.x, o.y);
	cout << "O";
	serpent[0] = o;
	creerSouris(LIGNES, COLONNES, souris, niveau);

	//mouvement = calculerDirectionTouche(4);
	afficherTerrain(LIGNES, COLONNES);
	afficherSouris(souris, niveau);
	do {
		int touche = recupererTouche();
		if (touche != -1 && (touche == 'a' || touche == 'd' || touche == 's' || touche == 'w'))
		{
			mouvement = calculerDirectionTouche(touche);
		}


		//deplacerSerpentI(mouvement, o);

		deplacerSerpentII(mouvement, serpent, tailleSerpent, souris, niveau);

		if (tailleSerpent > niveau)
		{
			won = true;
			break;
		}
		//serpent[tailleSerpent - 1] = coord y;

		if (serpent[0].x == 10 || serpent[0].x == 70 || serpent[0].y == 10 || serpent[0].y == 30 || niveau == USHRT_MAX)
		{
			break;
		}

		Sleep(80);
	} while (true);
	if (won)
		cout <<"Bravo! Tu es le gagnant!";
	else
		cout << "Game Over";


	system("pause");
}

// ************
// * PARTIE I *
// ************
void afficherTerrain(unsigned short nbLignes, unsigned short nbColonnes)
/*
	T�che: afficher le contour du terrain
	Param�tres: le nombre de lignes et de colonnes du terrain rectangulaire
*/
{
	cadre(10, 10, nbLignes, nbColonnes, 6);
}

int recupererTouche()
/*
	T�che: tester si le joueur a appuy� sur une touche
	Retour: retourner le code ASCII de la touche press�e, -1 sinon
*/
{
	int touche = -1;
	if (_kbhit())
	{
		touche = _getch();
	}
	return touche;
	// 	utiliser la fonction _kbhit() de conio.h qui retourne une valeur non 
	//	nulle si une touche a �t� press�e
}

Direction calculerDirectionTouche(int touche)
/*
	T�che: calculer la direction correspondant � une touche ou -1
	Param�tre: le code d'une touche (w, a, s ou d)
	Retour: la direction qui correspond � la touche
		(a: droite, d: gauche, w: haut, s: bas)
*/
{
	Direction mouvement = DROITE;
	switch (touche)
	{
	case(int)'a':
		mouvement = GAUCHE;
		break;
	case(int)'d':
		mouvement = DROITE;
		break;
	case(int)'w':
		mouvement = HAUT;
		break;
	case(int)'s':
		mouvement = BAS;
		break;
	}
	return mouvement;
}

void positionAleatoire(unsigned short nbLignes, unsigned short nbColonnes, coord &coord)
/*
	T�che: calculer une position al�atoire sur le terrain
	Param�tres: les dimensions du terrain en entr�e et les coordonn�es de la position al�atoire en sortie
*/
{
	coord.x = (rand() % (nbLignes - 11)) + 11;
	coord.y = (rand() % (nbColonnes - 11)) + 11;

}

void deplacerSerpentI(Direction direction, coord &teteSerpentCoord)
/*
	T�che: d�placer le serpent dans la direction
	Param�tres: la direction du serpent en entr�e, et la position du serpent en 			entr�e / sortie.
*/
{
	gotoXY(teteSerpentCoord.x, teteSerpentCoord.y);
	cout << " ";

	switch (direction)
	{
	case DROITE:
		teteSerpentCoord.x++;
		break;
	case GAUCHE:
		teteSerpentCoord.x--;
		break;
	case HAUT:
		teteSerpentCoord.y--;
		break;
	case BAS:
		teteSerpentCoord.y++;
		break;
	}
	gotoXY(teteSerpentCoord.x, teteSerpentCoord.y);
	cout << "O";
}









// *************
// * PARTIE II *
// *************


int saisirNiveau() {
	/*
	T�che: lire le niveau de difficult� avec tests de validation d'entr�e
	Retour: le niveau (= le nombre de souris initialement sur le terrain)
	*/

	int niveau;

	cout << "Veuillez saisir le niveau du jeu: ";
	cin >> niveau;

	while (cin.fail() == true || cin.peek() != '\n' || niveau < 1 || niveau > 20) {
		cin.clear();
		cin.ignore(512, '\n');

		cout << "Attention, veuillez saisir un niveau allant de 1 � 20: ";
		cin >> niveau;
	}

	cin.ignore(512, '\n');

	return niveau;
}

void creerSouris(unsigned short nbLignes, unsigned short nbColonnes,
	coord sourisCoord[], unsigned short nbSouris)
	/*
		T�che: g�n�rer les nbSouris al�atoirement sur le terrain
		Param�tres: les dimensions du terrain, le tableau de coordonn�es et le
				nombre de souris
	*/
{


	for (int i = 0; i < nbSouris; i++) {

		coord souris2;
		positionAleatoire(nbLignes, nbColonnes, souris2);
		sourisCoord[i] = souris2;
	}


}

void afficherSouris(coord sourisCoord[], unsigned short nbSouris)
/*
	T�che: afficher les souris
	Param�tres: le tableau de coordonn�es et le nombre de souris
*/
{
	for (int i = 0; i < nbSouris; i++) {

		gotoXY(sourisCoord[i].x, sourisCoord[i].y);
		cout << "$";
	}

}

void deplacerSerpentII(Direction direction,
	coord serpentCoord[], unsigned short &tailleSerpent,
	coord sourisCoord[], unsigned short &nbSouris)
	/*
		T�che: d�placer le serpent dans la direction
		Param�tres: en entr�e : 	la direction du serpent, le tableau de coordonn�es et le nombre de souris
				en entr�e/sortie :	le tableau de coordonn�es du serpent et
					la taille du serpent.
	*/
{
	coord newCoord = serpentCoord[0];
	coord prevCoord = serpentCoord[0];
	bool increased = false;

	if ((testerCollision(serpentCoord[0], sourisCoord, nbSouris)) == true)
	{
		++tailleSerpent;
		increased = true;
	}
	//gotoXY(serpentCoord[0].x, serpentCoord[0].y);
	//cout << "O";

	switch (direction)
	{
	case DROITE:
		serpentCoord[0].x++;
		break;
	case GAUCHE:
		serpentCoord[0].x--;
		break;
	case HAUT:
		serpentCoord[0].y--;
		break;
	case BAS:
		serpentCoord[0].y++;
		break;
	}

	gotoXY(serpentCoord[0].x, serpentCoord[0].y);
	cout << "O";

	for (unsigned int i = 1; i < tailleSerpent; ++i)
	{
		prevCoord = serpentCoord[i];
		serpentCoord[i] = newCoord;
		newCoord = prevCoord;

		gotoXY(serpentCoord[i].x, serpentCoord[i].y);
		cout << "O";
	}

	if (!increased)
	{
		gotoXY(prevCoord.x, prevCoord.y);
		cout << " ";
	}

	for (unsigned int i = 1; i < tailleSerpent; ++i)
	{
		if ((serpentCoord[0].x == serpentCoord[i].x) && (serpentCoord[0].y == serpentCoord[i].y)) {
			nbSouris = USHRT_MAX;
		}
	}
}

/*	ou	*/

void deplacerSerpentII(Direction direction, coord serpentCoord[],
	unsigned short &indiceTete, unsigned short &indiceQueue,
	coord sourisCoord[], unsigned short &nbSouris)
	/*
		T�che: d�placer le serpent dans la direction
		Param�tres: en entr�e :	la direction du serpent,
				en entr�e/sortie :	le tableau de coordonn�es du serpent, les indices de t�te et de queue du serpent.
	*/
{

}

bool testerCollision(coord teteSerpentCoord,
	coord sourisCoord[], unsigned short &nbSouris)
	/*
		T�che: tester si (posX, posY) est la position d'une souris. Si oui, retirer
			la souris de la population de souris
		Param�tres: la position de la t�te du serpent, le tableau de coordonn�es et
			le nombre de souris
		Retour: true si collision, false sinon
	*/
{
	for (int i = 0; i < nbSouris; i++) {
		if ((teteSerpentCoord.x == sourisCoord[i].x) && (teteSerpentCoord.y == sourisCoord[i].y)) {
			
			sourisCoord[i].x = 0;
			sourisCoord[i].y = 0;

			return true;
		}

	}

	return false;
}
















// **********************
// * PARTIE III : BONUS *
// **********************

void deplacerSouris(coord sourisCoord[], unsigned short nbSouris)
/*
	T�che: d�placer les souris (al�atoirement ou intelligemment)
	Param�tres: le tableau de coordonn�es et le nombre de souris
*/
{
}

void placerMurs(unsigned short nbLignes, unsigned short nbColonnes, unsigned short nbMurs)
/*
	T�che: placer des murs al�atoirement sur le terrain de jeu
	Param�tres: les dimensions du terrain et le nombre de murs � placer
*/
{
}
