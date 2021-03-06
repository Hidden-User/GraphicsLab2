#include "Line.h"

Line::Line()
{
	this->a = { 0 };
	this->b = { 0 };
}

Line::~Line()
{
	this->a = { 0 };
	this->b = { 0 };
}

void Line::buildFromPointAndVector(F4 posA, F2 vecToB, F4 lCol)
{
	this->a.pos = posA;
	this->a.col = lCol;
	this->b.pos.x = ((float)cos(vecToB.x) * vecToB.y) + this->a.pos.x;
	this->b.pos.y = ((float)sin(vecToB.x) * vecToB.y) + this->a.pos.y;
	this->b.pos.z = this->a.pos.z;
	this->b.pos.w = this->a.pos.w;
	this->b.col = lCol;
}

void Line::setLine(F4 aPos, F4 bPos, F4 lCol)
{
	this->a.pos = aPos;
	this->b.pos = bPos;
	this->a.col = lCol;
	this->b.col = lCol;
}

void Line::setFromAToVec(F2 vecToB)
{
	this->b.pos.x = ((float)cos(vecToB.x) * vecToB.y) + this->a.pos.x;
	this->b.pos.y = ((float)sin(vecToB.x) * vecToB.y) + this->a.pos.y;
}

void Line::setFromBToVec(F2 vecToA)
{
	this->a.pos.x = ((float)cos(vecToA.x) * vecToA.y) + this->b.pos.x;
	this->a.pos.y = ((float)sin(vecToA.x) * vecToA.y) + this->b.pos.y;
}

_POINT Line::getA()
{
	return this->a;
}

_POINT Line::getB()
{
	return this->b;
}
