#include "AbstractModel.h"

AbstractModel::AbstractModel()
    : prior(std::vector<double>()), classNames(std::vector<std::string>()) {
  InitializeClassNames();
}

void AbstractModel::SetPrior(const std::vector<double> &thePrior) {
  prior = thePrior;
}

std::vector<double> AbstractModel::getPrior() const { return prior; }

double AbstractModel::getPriorForClass(size_t theClass) const {
  return prior.at(theClass);
}

void AbstractModel::InitializeClassNames() {
  classNames.reserve(5);
  classNames.push_back("A");
  classNames.push_back("SD");
  classNames.push_back("D");
  classNames.push_back("ED");
  classNames.push_back("Asl");
}

std::vector<std::string> AbstractModel::GetClassNames() const {
  return classNames;
}
