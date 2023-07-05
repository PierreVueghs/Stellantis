// Stellantis.cpp : Ce fichier contient la fonction 'main'. L'exécution du
// programme commence et se termine à cet endroit.
//

#include "LoadTestData.h"
#include "ModelPredictor.h"
#include "PhysiologicalModel.h"
#include "PressureModel.h"

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  bool aHasFileName(false);
  AbstractModel *aModel = nullptr;
  if (argc < 2) {
    std::cout
        << "Missing input file. Running pressure model on default test set"
        << std::endl;

    LoadTestData::getInstance()->InitializeTestData();
    aModel = new PressureModel();
    LoadTestData::getInstance()->SetModel(aModel);
  } else
  // C:\\Users\\pv2077\\Documents\\Stellantis\\Projets\\Stellantis\\x64\\Debug\\features_150s_normalized_sliding90s.csv
  {
    aHasFileName = true;
    std::string aFileName(argv[1]);
    if (aFileName.size() < 4  || aFileName.substr(aFileName.length()-4, 4) != ".csv")
    {
        std::cout << "Invalid first argument.\nFirst argument must be the full path to a .csv file, where separator is comma ','." << std::endl;
        return -1;
    }
    LoadTestData::getInstance()->SetFileName(aFileName);
    if (argc == 3) {
      std::cout << "Using input file " << aFileName
                << "\nRunning physiological model on input test set"
                << std::endl;
      aModel = new PhysiologicalModel();
      LoadTestData::getInstance()->SetModel(aModel);
    } else {
      std::cout << "Using input file " << aFileName
                << "\nRunning pressure model on input test set" << std::endl;
      aModel = new PressureModel();
      LoadTestData::getInstance()->SetModel(aModel);
    }
    LoadTestData::getInstance()->LoadCsvFile();
    LoadTestData::getInstance()->ReLoadCsvFile();
  }

  size_t aNumberOfTestData(LoadTestData::getInstance()->GetNumberOfTestData());

  ModelPredictor aModelPredictor(aNumberOfTestData, aModel);
  aModelPredictor.Predict(aHasFileName);
}
