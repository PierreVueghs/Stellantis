#pragma once

#include "AbstractModel.h"

#include <vector>

class ModelPredictor {
public:
  ModelPredictor(AbstractModel *theModel);
  int Predict(bool theHasFileName, double* parameters, int nbParameters);

private:
    std::vector<double> GetScores(double* parameters, int nbParameters);
    std::vector<double> GetSoftMax(const std::vector<double>& theScores);
    std::vector<double> GetCost(const std::vector<double>& theSoftMax);
  int ExportResultsInCSV(bool theHasFileName, const std::vector<double>& theCost) const;

  AbstractModel *myModel;
};
