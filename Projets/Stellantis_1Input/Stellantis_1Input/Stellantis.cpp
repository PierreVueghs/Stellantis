// Stellantis.cpp : Ce fichier contient la fonction 'main'. L'exécution du
// programme commence et se termine à cet endroit.
//

#include "LoadTestData.h"
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



//#include <iostream>
//#include <string>
//
//int main(int argc, char *argv[]) {
//  bool aHasFileName(false);
//  AbstractModel *aModel = nullptr;
//  if (argc < 2) {
//    std::cout
//        << "Missing input file. Running pressure model on default test set"
//        << std::endl;
//
//    LoadTestData::getInstance()->InitializeTestData();
//    aModel = new PressureModel();
//    LoadTestData::getInstance()->SetModel(aModel);
//  } else
//  // C:\\Users\\pv2077\\Documents\\Stellantis\\Projets\\Stellantis\\x64\\Debug\\features_150s_normalized_sliding90s.csv
//  {
//    aHasFileName = true;
//    std::string aFileName(argv[1]);
//    if (aFileName.size() < 4  || aFileName.substr(aFileName.length()-4, 4) != ".csv")
//    {
//        std::cout << "Invalid first argument.\nFirst argument must be the full path to a .csv file, where separator is comma ','." << std::endl;
//        return -1;
//    }
//    LoadTestData::getInstance()->SetFileName(aFileName);
//    if (argc == 3) {
//      std::cout << "Using input file " << aFileName
//                << "\nRunning physiological model on input test set"
//                << std::endl;
//      aModel = new PhysiologicalModel();
//      LoadTestData::getInstance()->SetModel(aModel);
//    } else {
//      std::cout << "Using input file " << aFileName
//                << "\nRunning pressure model on input test set" << std::endl;
//      aModel = new PressureModel();
//      LoadTestData::getInstance()->SetModel(aModel);
//    }
//    LoadTestData::getInstance()->LoadCsvFile();
//    LoadTestData::getInstance()->ReLoadCsvFile();
//  }
//
//  size_t aNumberOfTestData(LoadTestData::getInstance()->GetNumberOfTestData());
//
//  ModelPredictor aModelPredictor(aNumberOfTestData, aModel);
//  aModelPredictor.Predict(aHasFileName);
//}

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
