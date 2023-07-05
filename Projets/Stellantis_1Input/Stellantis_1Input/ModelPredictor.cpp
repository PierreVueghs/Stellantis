#include "ModelPredictor.h"
#include "LoadTestData.h"
#include "PressureModel.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const double SQRT_2_PI = 2.506628274631000;

ModelPredictor::ModelPredictor(/*size_t theNumberOfTestData,*/
                               AbstractModel *theModel)
    : /*myNumberOfTestData(theNumberOfTestData), */myModel(theModel) {}

int ModelPredictor::Predict(bool theHasFileName, double* parameters, int nbParameters) {
  // Compute scores
  Matrix *scores = GetScores(parameters, nbParameters);

  // Compute soft max
  Matrix *aSoftMax = GetSoftMax(scores);

  // GetCost
  Matrix *aCost = GetCost(aSoftMax);

  // Export results in CSV file
  int zozo = ExportResultsInCSV(theHasFileName, aCost);

  return zozo;
}

Matrix *ModelPredictor::GetCost(const Matrix *theSoftMax) {
  // Taking advantage of the Cost matrix, which is 1 everywhere and zero on the
  // diagonal
  Matrix *aCost = new Matrix(1, 5);
  for (size_t ii(0); ii < 5; ++ii) {
    //for (size_t jj(0); jj < myNumberOfTestData; ++jj) {
      double aTempValue(0.);
      for (size_t kk(0); kk < 5; ++kk) {
        if (kk != ii)
          aCost->Append(0, ii, theSoftMax->Get(0, kk));
      }
    //}
  }
  return aCost;
}

int ModelPredictor::ExportResultsInCSV(bool theHasFileName,
                                        const Matrix *theCost) const {
  //// Get index of highest probability class
  //std::vector<double> prior = myModel->getPrior();
  //size_t index =
  //    std::distance(begin(prior), std::max_element(begin(prior), end(prior)));

  //std::vector<size_t> labels;
  //for (size_t ii(0); ii < myNumberOfTestData; ++ii) {
  //  labels.push_back(index);
  //}

  //ofstream myfile;
  //myfile.open("results.csv");
  //std::vector<std::string> anIds =
  //    LoadTestData::getInstance()->GetInputDataForExport(
  //        InputDataForExport::IDFE_id);
  //std::vector<std::string> aTimestamps =
  //    LoadTestData::getInstance()->GetInputDataForExport(
  //        InputDataForExport::IDFE_Timestamp);
  //std::vector<std::string> aStates =
  //    LoadTestData::getInstance()->GetInputDataForExport(
  //        InputDataForExport::IDFE_State);
  //std::vector<std::string> aLoDs =
  //    LoadTestData::getInstance()->GetInputDataForExport(
  //        InputDataForExport::IDFE_LoD);
  //std::vector<std::string> aClassNames = myModel->GetClassNames();

  //myfile << "Index;id;Timestamp;Output;State;LoD\n";

  //for (size_t ii(0); ii < myNumberOfTestData; ++ii) {
    double aMinValue = theCost->Get(0, 0);
    size_t minIndex(0);
    for (size_t jj(1); jj < 5; ++jj) {
      if (theCost->Get(0, jj) < aMinValue) {
        aMinValue = theCost->Get(0, jj);
        minIndex = jj;
      }
    }
    return minIndex;
    //labels.at(ii) = minIndex;
    // cout << "labels " << ii << " " << minIndex << ";" << endl;
    //if (theHasFileName) {
    //  myfile << ii << "," << anIds.at(ii) << "," << aTimestamps.at(ii) << ","
    //         << aClassNames.at(minIndex) << "," << aStates.at(ii) << ","
    //         << aLoDs.at(ii) << "\n";
    //} else {
      //myfile << ii << ", , ," << aClassNames.at(minIndex) << ",,\n";
    //}
  //}
  //myfile.close();
}

Matrix *ModelPredictor::GetSoftMax(const Matrix *theScores) {
  double aTemparray[5] = {0.};

  // ArrayStruct *aSoftMax = new ArrayStruct();
  Matrix *aSoftMax = new Matrix(1, 5);

  // Soft max on scores
  //for (size_t ii(0); ii < myNumberOfTestData; ++ii) {
    double aMaxValue(theScores->Get(0, 0));
    for (size_t jj(1); jj < 5; ++jj) {
      if (theScores->Get(0, jj) > aMaxValue)
        aMaxValue = theScores->Get(0, jj);
    }

    for (size_t jj(0); jj < 5; ++jj) {
      aTemparray[jj] = std::exp(theScores->Get(0, jj) - aMaxValue);
    }

    double aLValue = aTemparray[0];
    for (size_t jj(1); jj < 5; ++jj)
      aLValue += aTemparray[jj];

    aLValue = std::log(aLValue) + aMaxValue;

    for (size_t jj(0); jj < 5; ++jj) {
      aSoftMax->Set(0, jj, std::exp(theScores->Get(0, jj) - aLValue));
    }
  //}
  return aSoftMax;
}

size_t findNextGreaterOrEqual(const std::vector<double> &data, double value,
                              size_t startId) {
  size_t idx(startId);
  while (idx < data.size() - 1 && data.at(idx) < value) {
    ++idx;
  }
  return idx;
}

size_t findNextGreaterThan(const std::vector<double> &data, double value,
                           size_t startId) {
  size_t idx(startId);
  while (idx < data.size() - 1 && data.at(idx) <= value) {
    ++idx;
  }
  return idx;
}

Matrix *ModelPredictor::GetScores(double* parameters, int nbParameters) {
  Matrix *score = new Matrix(1, 5);

  int aNumberOfPredictors(myModel->GetNumberOfPredictors());

  // Loop on classes (5)
  for (size_t ii(0); ii < 5; ++ii) {
    double aLogPrior = std::log(myModel->getPriorForClass(ii));
    // Loop on predictors (14 for pressure model, 31 for physiological model)
    for (size_t jj(0); jj < aNumberOfPredictors; ++jj) {
      // logPxdgc(:, d) = classreg.learning.nbutils.univariateLogP(X(:, d),
      // model.DistributionNames{ d }, ... 	distparams{ c,d }, catlevels{ d
      // });%
      // Fill in column d.

      // logPx = log(DistParams.pdf(x));% DistParams is a
      // prob.KernelDistribution object.
      DistributionParameters distributionParameters =
          myModel->getDistributionParameter(ii, jj);
      // Calcul de la fonction, ceci pourrait etre encapsule dans une classe
      // DistributionParameters, plus dans une struct
      size_t jstart(0), jend(0);
      double halfWidth = 4. * distributionParameters.bandWidth;

      double aPredictorTestInput = parameters[jj];

      //std::vector<std::pair<size_t, double>> aPredictorTestInput(
      //    LoadTestData::getInstance()->GetTestDataForPredictor(jj));

      //std::stable_sort(begin(aPredictorTestInput), end(aPredictorTestInput),
      //                 [](const auto &val1, const auto &val2) {
      //                   return val1.second < val2.second;
      //                 });

      //for (size_t ll(0); ll < aPredictorTestInput.size(); ++ll) {
        // Add log prior to corresponding score, but only once
        if (jj == 0)
            score->Append(0, ii, aLogPrior);
        //score->Append(aPredictorTestInput.at(ll).first - 1, ii, aLogPrior);
        //double xi = aPredictorTestInput.at(ll).second;
        double xi = aPredictorTestInput;

        double aLowValue(xi - halfWidth);
        jstart = findNextGreaterOrEqual(distributionParameters.inputData,
                                        aLowValue, jstart);

        double aHighValue(xi + halfWidth);
        jend = findNextGreaterThan(distributionParameters.inputData, aHighValue,
                                   jend);

        double fk(0.);
        for (size_t kk(jstart);
             kk <= jend && kk < distributionParameters.inputData.size(); ++kk) {
          double z = (xi - distributionParameters.inputData.at(kk)) /
                     distributionParameters.bandWidth;
          fk += std::exp(-0.5 * z * z) / SQRT_2_PI;
        }

        // Ici, fk correspond a DistParams.pdf(x)
        fk /= double(distributionParameters.inputData.size());

        // In statkscompute, in compute_pdf_cdf, close to the end, returned f
        // (fk) is divided by u
        fk /= distributionParameters.bandWidth;

        // Ici, fk correspond a la sortie de univariateLogP : function logPx =
        // univariateLogP (x, DistName, DistParams, CategoricalLevels)
        fk = std::log(fk);

        // Add log(fk) to corresponding score
        score->Append(0, ii, fk);
      //}
    }
  }

  return score;
}
