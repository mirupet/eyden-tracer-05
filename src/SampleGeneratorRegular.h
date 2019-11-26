#pragma once

#include "SampleGenerator.h"

class CSampleGeneratorRegular : public CSampleGenerator
{
public:
	virtual void getSamples(int n, float* u, float* v, float* weight) const override
	{
		int m = static_cast<int>(sqrt(n));
		for (int j = 0; j < m; j++)
			for (int i = 0; i < m; i++) {
				u[j + i * m] = -0.5f + (i + 0.5f) / m;
				v[j + i * m] = -0.5f + (j + 0.5f) / m;
				weight[j + i * m] = 1.0f / (m * m);
			}
	}
};
