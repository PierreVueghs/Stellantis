#pragma once

#include "AbstractModel.h"

#include <map>
#include <string>
#include <vector>

enum TestData : size_t {
  PRES_COP_y_seat = 0,
  PRES_mov_seat,
  PRES_cp_postero,
  PRES_cp_antero,
  PRES_COP_y_back,
  PRES_COP_x_back,
  PRES_mov_back,
  PRES_cs_up,
  PRES_cs_down,
  PRES_cp_dos,
  PRES_cp_down,
  PRES_per_using_headrest,
  PRES_cs_head,
  PRES_cp_head,
  PRES_UNKNOWN
};

class PressureModel : public AbstractModel {
public:
  PressureModel();
  DistributionParameters
  getDistributionParameter(size_t theClass, size_t thePredictor) const override;
  int GetIndexForPredictorName(
      const std::string &thePredictorName) const override;
  std::map<size_t, std::vector<std::pair<size_t, double>>>
  InitializeTestData() const override;

  int GetNumberOfPredictors() const override;

private:
  void InitializePrior() override;
  void InitializePredictorNames() override;
  void InitializeDistributionParameters() override;

  // Members
  std::map<std::string, TestData> predictorNames;
  DistributionParameters distributionParameters[5][14];
};
