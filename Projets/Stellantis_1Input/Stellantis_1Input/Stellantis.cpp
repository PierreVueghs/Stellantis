// Stellantis.cpp : Ce fichier contient la fonction 'main'. L'exécution du
// programme commence et se termine à cet endroit.
//

#include "ModelPredictor.h"
#include "PhysiologicalModel.h"
#include "PressureModel.h"

#include "Stellantis.h"

#include <iostream>

int main()
{
	//double parameters[] = { -0.59416205866018 , -2.97297297297297 , 78.78538119894802 , -1370.19788999720004 ,
	//-2.01732398330656 , 0.63234731005883 , -3.18918918918919 , -74.29664864864861 , 41.59427027027027 ,
	//-10.40569449189752 , 1324.63154666515175 , -0.00277477477477 , -0.25643243243243 , -4.40598234234234 };

	double parameters[] = { 0.56715693753257 , -0.97297297297297 , -407.51917059907828 , 455.39890783998635 ,
	0.34947663027329 , -0.94219624880067 , -1.18918918918919 , 6.45135135135138 , -10.16439639639640 ,
	-406.61256412742659 , -210.46800635485351 , 0.04922522522523 , 1.88623423423423 , 35.33643099099099 };
	int zozo = ComputeLevelOfDrowsiness(parameters, 14);

	std::cout << "LoD " << zozo << std::endl;
}

int ComputeLevelOfDrowsiness(double* parameters, int nbParameters)
{
	AbstractModel* aModel(nullptr);

	if (nbParameters == 31)
	{
		aModel = new PhysiologicalModel();
	}
	else
	{
		aModel = new PressureModel();
	}

	ModelPredictor aModelPredictor(aModel);
	int zozo = aModelPredictor.Predict(false, parameters, nbParameters);

	return zozo;
}
