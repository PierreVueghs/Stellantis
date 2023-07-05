#pragma once

#ifdef STELLANTISDDL_EXPORTS
#define STELLANTISDDL_API __declspec(dllexport)
#else
#define STELLANTISDDL_API __declspec(dllimport)
#endif

int ComputeLevelOfDrowsiness(double* parameters, int nbParameters);