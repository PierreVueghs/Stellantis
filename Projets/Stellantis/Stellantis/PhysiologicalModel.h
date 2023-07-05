#pragma once
#include "AbstractModel.h"

#include <map>
#include <string>

enum PhysiologicalTestData : size_t {
  PTD_COP_y_seat = 0,
  PTD_mov_seat,
  PTD_cp_postero,
  PTD_cp_antero,
  PTD_COP_y_back,
  PTD_COP_x_back,
  PTD_mov_back,
  PTD_cs_up,
  PTD_cs_down,
  PTD_cp_dos,
  PTD_cp_down,
  PTD_per_using_headrest,
  PTD_cs_head,
  PTD_cp_head,
  PTD_HR_Mean,
  PTD_HRV_MedianNN,
  PTD_HRV_Prc80NN,
  PTD_HRV_pNN50,
  PTD_HRV_HF,
  PTD_HRV_IALS,
  PTD_HRV_PI,
  PTD_HRV_SD1d,
  PTD_HRV_SampEn,
  PTD_HRV_HFD,
  PTD_RSP_Phase_Duration_Expiration,
  PTD_RSP_Phase_Duration_Ratio,
  PTD_RRV_RMSSD,
  PTD_RRV_SDSD,
  PTD_RRV_LF,
  PTD_RRV_HF,
  PTD_RSA_Gates_Mean,
  PTD_UNKNOWN
};

class PhysiologicalModel : public AbstractModel {
public:
  PhysiologicalModel();
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

  std::map<std::string, PhysiologicalTestData> predictorNames;
  DistributionParameters distributionParameters[5][31];
};
