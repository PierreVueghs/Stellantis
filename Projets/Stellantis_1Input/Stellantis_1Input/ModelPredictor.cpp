#include "ModelPredictor.h"
#include "PressureModel.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const double SQRT_2_PI = 2.506628274631000;

ModelPredictor::ModelPredictor(AbstractModel *theModel)
    : myModel(theModel) {}

int ModelPredictor::Predict(bool theHasFileName, double* parameters, int nbParameters) {
    // Compute scores
    std::vector<double> scores = GetScores(parameters, nbParameters);

    // Compute soft max
    std::vector<double> aSoftMax = GetSoftMax(scores);

    // GetCost
    std::vector<double> aCost = GetCost(aSoftMax);

    // Export results in CSV file
    return ExportResultsInCSV(theHasFileName, aCost);
}

std::vector<double> ModelPredictor::GetCost(const std::vector<double>& theSoftMax) {
  // Taking advantage of the Cost matrix, which is 1 everywhere and zero on the
  // diagonal
  std::vector<double> aCost = { 0., 0., 0., 0., 0. };
  for (size_t ii(0); ii < 5; ++ii) {
      double aTempValue(0.);
      for (size_t kk(0); kk < 5; ++kk) {
          if (kk != ii)
              aCost[ii] += theSoftMax[kk];
      }
  }
  return aCost;
}

int ModelPredictor::ExportResultsInCSV(bool theHasFileName,
                                        const std::vector<double>& theCost) const {
  //// Get index of highest probability class
    double aMinValue = theCost[0];// ->Get(0, 0);
    int minIndex(0);
    for (int jj(1); jj < 5; ++jj) {
      if (theCost[jj] < aMinValue) {
        aMinValue = theCost[jj];
        minIndex = jj;
      }
    }
    return minIndex;
}

std::vector<double> ModelPredictor::GetSoftMax(const std::vector<double>& theScores) {
  double aTemparray[5] = {0.};

  std::vector<double> aSoftMax;

  // Soft max on scores
    double aMaxValue(theScores[0]);
    for (size_t jj(1); jj < 5; ++jj) {
      if (theScores[jj] > aMaxValue)
        aMaxValue = theScores[jj];
    }

    for (size_t jj(0); jj < 5; ++jj) {
      aTemparray[jj] = std::exp(theScores[jj] - aMaxValue);
    }

    double aLValue = aTemparray[0];
    for (size_t jj(1); jj < 5; ++jj)
      aLValue += aTemparray[jj];

    aLValue = std::log(aLValue) + aMaxValue;

    for (size_t jj(0); jj < 5; ++jj) {
        aSoftMax.push_back(std::exp(theScores[jj] - aLValue));
    }
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

std::vector<double> ModelPredictor::GetScores(double* parameters, int nbParameters) {
  std::vector<double> scores = { 0., 0., 0., 0., 0. };

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

        // Add log prior to corresponding score, but only once
      if (jj == 0)
          scores[ii] = aLogPrior;
        double xi = parameters[jj];

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
        scores[ii] += fk;
    }
  }

  return scores;
}
