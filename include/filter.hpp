#ifndef FILTER_H
#define FILTER_H

#include <M5Stack.h>

class Filter {
private:
	float Q_angle, Q_bias, R_measure;
	float K_angle, K_bias, K_rate;
	float P[2][2], K[2];
	float S, y;
	float dt, kt;

public:
	Filter(float angle = 0.001, float bias = 0.003, float measure = 0.03);
	float update(float newValue, float newRate);
};

#endif
