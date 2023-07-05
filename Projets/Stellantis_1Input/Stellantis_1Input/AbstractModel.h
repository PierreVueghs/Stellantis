#pragma once

#include <map>
#include <string>
#include <vector>

struct DistributionParameters {
  double bandWidth;
  std::vector<double> inputData;
};

class AbstractModel {
public:
  AbstractModel();
  std::vector<double> getPrior() const;
  double getPriorForClass(size_t theClass) const;
  virtual DistributionParameters
  getDistributionParameter(size_t theClass, size_t thePredictor) const = 0;
  std::vector<std::string> GetClassNames() const;
  virtual int
  GetIndexForPredictorName(const std::string &thePredictorName) const = 0;
  virtual std::map<size_t, std::vector<std::pair<size_t, double>>>
  InitializeTestData() const = 0;
  virtual int GetNumberOfPredictors() const = 0;

protected:
  void SetPrior(const std::vector<double> &thePrior);

private:
  virtual void InitializePrior() = 0;
  void InitializeClassNames();
  virtual void InitializeDistributionParameters() = 0;
  virtual void InitializePredictorNames() = 0;

  // Members
  std::vector<double> prior;
  std::vector<std::string> classNames;
};
