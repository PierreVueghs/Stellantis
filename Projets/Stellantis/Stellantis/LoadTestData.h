#pragma once

#include "AbstractModel.h"

#include <map>
#include <string>
#include <vector>

enum InputDataForExport : size_t {
  IDFE_id = 0,
  IDFE_Timestamp,
  IDFE_State,
  IDFE_LoD,
  IDFE_UNKNOWN
};

class LoadTestData {
public:
  static LoadTestData *getInstance();
  std::vector<std::pair<size_t, double>>
  GetTestDataForPredictor(size_t thePredictor) const;
  std::vector<std::string> GetInputDataForExport(size_t theInputData) const;
  size_t GetNumberOfTestData() const;

  bool LoadCsvFile();
  bool ReLoadCsvFile();
  void InitializeTestData();

  void SetFileName(const std::string &theFileName);
  void SetModel(AbstractModel *theModel);

private:
  LoadTestData();
  InputDataForExport
  GetIndexForInputData(const std::string &theInputDataName) const;

  // Members
  std::map<size_t, std::vector<std::pair<size_t, double>>> myTestData;
  std::map<size_t, std::vector<std::string>> myInputValuesForExport;
  size_t myNumberOfTestData;
  std::string myFileName;
  AbstractModel *myModel;
};
