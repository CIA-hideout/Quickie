#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <random>
#include <d3dx9.h>


bool randBool();
int randInt(int start, int end);
float randFloat(float start, float end);

std::vector<D3DXVECTOR3> rand3DVector(std::vector<D3DXVECTOR3> vector);
std::vector<int> randIntVector(std::vector<int> vector);

#endif