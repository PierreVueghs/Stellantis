// Stellantis_Client.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

#include "..\..\Stellantis_DDL\Stellantis_DDL\Stellantis.h"

int main()
{
	// LoD 0
//	double parameters[] = { -0.59416205866018 , -2.97297297297297 , 78.78538119894802 , -1370.19788999720004 ,
//-2.01732398330656 , 0.63234731005883 , -3.18918918918919 , -74.29664864864861 , 41.59427027027027 ,
//-10.40569449189752 , 1324.63154666515175 , -0.00277477477477 , -0.25643243243243 , -4.40598234234234 };


	// LoD 3
	double parameters[] = { 0.56715693753257 , -0.97297297297297 , -407.51917059907828 , 455.39890783998635 ,
	0.34947663027329 , -0.94219624880067 , -1.18918918918919 , 6.45135135135138 , -10.16439639639640 ,
	-406.61256412742659 , -210.46800635485351 , 0.04922522522523 , 1.88623423423423 , 35.33643099099099 };
	std::cout << "LoD " << ComputeLevelOfDrowsiness(parameters, 14) << std::endl;

    std::cout << "Hello World!\n";
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
