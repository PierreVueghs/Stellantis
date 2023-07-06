#pragma once

#ifdef STELLANTISDDL_EXPORTS
#define STELLANTISDDL_API __declspec(dllexport)
#else
#define STELLANTISDDL_API __declspec(dllimport)
#endif

extern "C" STELLANTISDDL_API int ComputeLevelOfDrowsiness(double* parameters, int nbParameters);