#pragma once

#include "SampleGenerator.h"
#include "random.h"

class CSampleGeneratorStratified : public CSampleGenerator
{
public:
	virtual void getSamples(int n, float* u, float* v, float* weight) const override
	{
		int m = static_cast<int>(sqrt(n));
		for (int j = 0; j < m; j++)
			for (int i = 0; i < m; i++) {
				u[j + i * m] = -0.5f + (i + DirectGraphicalModels::random::U<float>()) / m;
				v[j + i * m] = -0.5f + (j + DirectGraphicalModels::random::U<float>()) / m;
				weight[j + i * m] = 1.0f / (m * m);
			}
	}
};
