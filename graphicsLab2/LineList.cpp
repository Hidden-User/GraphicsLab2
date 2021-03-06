#include "LineList.h"



LineList::LineList()
{
	this->lines = NULL;
	this->indexes = NULL;
	this->pointBuff = NULL;
	this->indexBuff = NULL;
	this->device = NULL;
	this->context = NULL;
	this->countOfLines = 0u;
}


LineList::~LineList()
{
	if (this->indexBuff != NULL) {
		(this->indexBuff)->Release();
	}
	if (this->pointBuff != NULL) {
		(this->pointBuff)->Release();
	}
	if (this->lines != NULL) {
		delete[] this->lines;
	}
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	this->device = NULL;
	this->context = NULL;
}

void LineList::setDX(ID3D11Device * device, ID3D11DeviceContext * context)
{
	this->device = device;
	this->context = context;
}

void LineList::setLinesCount(unsigned count)
{
	if (this->device == NULL || this->context == NULL) {
		return;
	}

	HRESULT hr = NULL;

	this->lines = new Line[count];
	this->indexes = new unsigned[count * 2];
	this->countOfLines = count;

	Line ll = Line();

	for (unsigned t = 0; t < this->countOfLines; t++) {
		this->lines[t] = ll;
		this->indexes[t * 2] = t * 2;
		this->indexes[(t * 2) + 1] = (t * 2) + 1;
	}

	D3D11_SUBRESOURCE_DATA _LinesSR;

	_LinesSR.pSysMem = this->lines;
	_LinesSR.SysMemPitch = 0;
	_LinesSR.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC pbd;
	pbd.Usage = D3D11_USAGE_DYNAMIC;
	pbd.ByteWidth = sizeof(Line) * this->countOfLines;
	pbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	pbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pbd.MiscFlags = 0;
	pbd.StructureByteStride = 0;

	hr = (this->device)->CreateBuffer(&pbd, &_LinesSR, &this->pointBuff);

	if (FAILED(hr)) {
		MessageBox(NULL, "error create buff", "err", MB_ICONSTOP | MB_OK);
	}

	D3D11_SUBRESOURCE_DATA _IndexesSR;

	_IndexesSR.pSysMem = this->indexes;
	_IndexesSR.SysMemPitch = 0;
	_IndexesSR.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(unsigned) * 2 * this->countOfLines;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	hr = (this->device)->CreateBuffer(&ibd, &_IndexesSR, &this->indexBuff);

	if (FAILED(hr)) {
		MessageBox(NULL, "error create buff", "err", MB_ICONSTOP | MB_OK);
	}

}

Line * LineList::getLine(unsigned pos)
{
	if (pos >= this->countOfLines) {
		return nullptr;
	}
	return &(this->lines[pos]);
}

void LineList::update()
{
	D3D11_MAPPED_SUBRESOURCE mpsr = { 0 };

	(this->context)->Map(this->pointBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mpsr);

	memcpy(mpsr.pData, this->lines, this->countOfLines * sizeof(Line));

	(this->context)->Unmap(this->pointBuff, 0);
}

void LineList::draw()
{
	UINT stride = sizeof(_POINT);
	UINT offset = 0;

	(this->context)->IASetVertexBuffers(0, 1, &this->pointBuff, &stride, &offset);
	(this->context)->IASetIndexBuffer(this->indexBuff, DXGI_FORMAT_R32_UINT, 0);

	(this->context)->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	(this->context)->DrawIndexed(this->countOfLines * 2, 0, 0);

}


