#pragma once

#include "AbstractModel.h"

#include <vector>

class Matrix {
public:
  Matrix(size_t theRowNumber, size_t theColumnNumber) {
    for (size_t ii(0); ii < theColumnNumber; ++ii) {
      std::vector<double> aColumn;
      aColumn.resize(theRowNumber);
      myMatrix.push_back(aColumn);
    }
  }

  void Set(size_t theRowNumber, size_t theColumnNumber, double theValue) {
    myMatrix[theColumnNumber][theRowNumber] = theValue;
  }

  double Get(size_t theRowNumber, size_t theColumnNumber) const {
    return myMatrix[theColumnNumber][theRowNumber];
  }

  void Append(size_t theRowNumber, size_t theColumnNumber, double theValue) {
    myMatrix[theColumnNumber][theRowNumber] += theValue;
  }

private:
  std::vector<std::vector<double>> myMatrix;
};

class ModelPredictor {
public:
  ModelPredictor(/*size_t theNumberOfTestData, */AbstractModel *theModel);
  int Predict(bool theHasFileName, double* parameters, int nbParameters);

private:
  Matrix *GetScores(double* parameters, int nbParameters);
  Matrix *GetSoftMax(const Matrix *theScores);
  Matrix *GetCost(const Matrix *theSoftMax);
  int ExportResultsInCSV(bool theHasFileName, const Matrix *theCost) const;

  //size_t myNumberOfTestData;
  AbstractModel *myModel;
};
