#pragma once

#include "Windows.h"
#include "d3d11.h"
#include "DirectXMath.h"

struct F2
{
	float x;
	float y;
};

struct F3
{
	float x;
	float y;
	float z;
};

struct F4
{
	float x;
	float y;
	float z;
	float w;
};

struct _POINT
{
	F4 pos;
	F4 col;
};

struct cBuffer
{
	DirectX::XMMATRIX projection;
};

class Line
{
public:
	
	Line();
	~Line();

	void buildFromPointAndVector(F4, F2, F4 = { 0 });
	void setLine(F4, F4, F4 = { 0 });
	void setFromAToVec(F2);
	void setFromBToVec(F2);

	_POINT getA();
	_POINT getB();

private:

	_POINT a;
	_POINT b;

};

