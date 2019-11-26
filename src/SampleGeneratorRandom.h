#pragma once

#include "SampleGenerator.h"
#include "random.h"

class CSampleGeneratorRandom : public CSampleGenerator
{
public:
	virtual void getSamples(int n, float* u, float* v, float* weight) const override
	{
		for (int i = 0; i < n; i++) {
			u[i] = -0.5f + DirectGraphicalModels::random::U<float>();
			v[i] = -0.5f + DirectGraphicalModels::random::U<float>();
			weight[i] = 1.0f / n;
		}
	}
};
