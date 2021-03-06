#pragma once

#include "Line.h"

class LineList
{
public:
	LineList();
	~LineList();

	void setDX(ID3D11Device* device, ID3D11DeviceContext* context);

	void setLinesCount(unsigned count);
	Line* getLine(unsigned);

	void update();
	void draw();

private:
	Line *lines;
	unsigned *indexes;
	unsigned countOfLines;

	ID3D11Buffer* pointBuff;
	ID3D11Buffer* indexBuff;
	ID3D11DeviceContext* context;
	ID3D11Device* device;
};

