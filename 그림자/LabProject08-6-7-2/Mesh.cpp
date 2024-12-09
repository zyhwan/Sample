//-----------------------------------------------------------------------------
// File: CMesh.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Mesh.h"

CMesh::CMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
}

CMesh::~CMesh()
{
	if (m_pd3dVertexBuffer) m_pd3dVertexBuffer->Release();
	if (m_pd3dIndexBuffer) m_pd3dIndexBuffer->Release();
	if (m_pd3dVertexUploadBuffer) m_pd3dVertexUploadBuffer->Release();
	if (m_pd3dIndexUploadBuffer) m_pd3dIndexUploadBuffer->Release();
}

void CMesh::ReleaseUploadBuffers()
{
	if (m_pd3dVertexUploadBuffer) m_pd3dVertexUploadBuffer->Release();
	if (m_pd3dIndexUploadBuffer) m_pd3dIndexUploadBuffer->Release();
	m_pd3dVertexUploadBuffer = NULL;
	m_pd3dIndexUploadBuffer = NULL;
};

void CMesh::Render(ID3D12GraphicsCommandList *pd3dCommandList)
{
	pd3dCommandList->IASetPrimitiveTopology(m_d3dPrimitiveTopology);
	pd3dCommandList->IASetVertexBuffers(m_nSlot, 1, &m_d3dVertexBufferView);
	if (m_pd3dIndexBuffer)
	{
		pd3dCommandList->IASetIndexBuffer(&m_d3dIndexBufferView);
		pd3dCommandList->DrawIndexedInstanced(m_nIndices, 1, 0, 0, 0);
	}
	else
	{
		pd3dCommandList->DrawInstanced(m_nVertices, 1, m_nOffset, 0);
	}
}

void CMesh::CalculateBoundingBox(XMFLOAT3 *pxmf3Points, UINT nStride)
{
	BoundingBox::CreateFromPoints(m_xmBoundingBox, m_nVertices, pxmf3Points, nStride);
}

//////////////////////////////////////////////////////////////////////////////////
//
CAirplaneMeshDiffused::CAirplaneMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, float fWidth, float fHeight, float fDepth, XMFLOAT4 xmf4Color) : CMesh(pd3dDevice, pd3dCommandList)
{
	m_nVertices = 24 * 3;
	m_nStride = sizeof(CDiffusedVertex);
	m_nOffset = 0;
	m_nSlot = 0;
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	float fx = fWidth*0.5f, fy = fHeight*0.5f, fz = fDepth*0.5f;

	CDiffusedVertex pVertices[24 * 3];

	float x1 = fx * 0.2f, y1 = fy * 0.2f, x2 = fx * 0.1f, y3 = fy * 0.3f, y2 = ((y1 - (fy - y3))/ x1)* x2 + (fy - y3);
	int i = 0;

	//Upper Plane
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x2, +y2, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+fx, -y3, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x2, +y2, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-fx, -y3, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	//Lower Plane
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, 0.0f, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, 0.0f, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x2, +y2, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+fx, -y3, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x2, +y2, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-fx, -y3, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	//Right Plane
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x2, +y2, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x2, +y2, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x2, +y2, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x2, +y2, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x2, +y2, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+fx, -y3, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+fx, -y3, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x2, +y2, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+fx, -y3, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	//Back/Right Plane
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+fx, -y3, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+fx, -y3, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+fx, -y3, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, 0.0f, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	//Left Plane
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x2, +y2, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x2, +y2, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x2, +y2, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x2, +y2, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x2, +y2, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-fx, -y3, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x2, +y2, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-fx, -y3, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-fx, -y3, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	//Back/Left Plane
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, 0.0f, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-fx, -y3, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-fx, -y3, +fz), Vector4::Add(xmf4Color, RANDOM_COLOR));
	pVertices[i++] = CDiffusedVertex(XMFLOAT3(-fx, -y3, -fz), Vector4::Add(xmf4Color, RANDOM_COLOR));

	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices, m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);

	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

	CalculateBoundingBox((XMFLOAT3 *) pVertices, m_nStride);
}

CAirplaneMeshDiffused::~CAirplaneMeshDiffused()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CMeshIlluminated::CMeshIlluminated(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList) : CMesh(pd3dDevice, pd3dCommandList)
{
}

CMeshIlluminated::~CMeshIlluminated()
{
}

void CMeshIlluminated::CalculateTriangleListVertexNormals(XMFLOAT3 *pxmf3Normals, XMFLOAT3 *pxmf3Positions, int nVertices)
{
	int nPrimitives = nVertices / 3;
	UINT nIndex0, nIndex1, nIndex2;
	for (int i = 0; i < nPrimitives; i++)
	{
		nIndex0 = i*3+0;
		nIndex1 = i*3+1;
		nIndex2 = i*3+2;
		XMFLOAT3 xmf3Edge01 = Vector3::Subtract(pxmf3Positions[nIndex1], pxmf3Positions[nIndex0]);
		XMFLOAT3 xmf3Edge02 = Vector3::Subtract(pxmf3Positions[nIndex2], pxmf3Positions[nIndex0]);
		pxmf3Normals[nIndex0] = pxmf3Normals[nIndex1] = pxmf3Normals[nIndex2] = Vector3::CrossProduct(xmf3Edge01, xmf3Edge02, true);
	}
}

void CMeshIlluminated::CalculateTriangleListVertexNormals(XMFLOAT3 *pxmf3Normals, XMFLOAT3 *pxmf3Positions, UINT nVertices, UINT *pnIndices, UINT nIndices)
{
	UINT nPrimitives = (pnIndices) ? (nIndices / 3) : (nVertices / 3);
	XMFLOAT3 xmf3SumOfNormal, xmf3Edge01, xmf3Edge02, xmf3Normal;
	UINT nIndex0, nIndex1, nIndex2;
	for (UINT j = 0; j < nVertices; j++)
	{
		xmf3SumOfNormal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		for (UINT i = 0; i < nPrimitives; i++)
		{
			nIndex0 = pnIndices[i*3+0];
			nIndex1 = pnIndices[i*3+1];
			nIndex2 = pnIndices[i*3+2];
			if (pnIndices && ((nIndex0 == j)|| (nIndex1 == j)|| (nIndex2 == j)))
			{
				xmf3Edge01 = Vector3::Subtract(pxmf3Positions[nIndex1], pxmf3Positions[nIndex0]);
				xmf3Edge02 = Vector3::Subtract(pxmf3Positions[nIndex2], pxmf3Positions[nIndex0]);
				xmf3Normal = Vector3::CrossProduct(xmf3Edge01, xmf3Edge02, false);
				xmf3SumOfNormal = Vector3::Add(xmf3SumOfNormal, xmf3Normal);
			}
		}
		pxmf3Normals[j] = Vector3::Normalize(xmf3SumOfNormal);
	}
}

void CMeshIlluminated::CalculateTriangleStripVertexNormals(XMFLOAT3 *pxmf3Normals, XMFLOAT3 *pxmf3Positions, UINT nVertices, UINT *pnIndices, UINT nIndices)
{
	UINT nPrimitives = (pnIndices) ? (nIndices - 2) : (nVertices - 2);
	XMFLOAT3 xmf3SumOfNormal(0.0f, 0.0f, 0.0f);
	UINT nIndex0, nIndex1, nIndex2;
	for (UINT j = 0; j < nVertices; j++)
	{
		xmf3SumOfNormal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		for (UINT i = 0; i < nPrimitives; i++)
		{
			nIndex0 = ((i % 2)== 0) ? (i + 0) : (i + 1);
			if (pnIndices)nIndex0 = pnIndices[nIndex0];
			nIndex1 = ((i % 2)== 0) ? (i + 1) : (i + 0);
			if (pnIndices)nIndex1 = pnIndices[nIndex1];
			nIndex2 = (pnIndices) ? pnIndices[i + 2] : (i + 2);
			if ((nIndex0 == j)|| (nIndex1 == j)|| (nIndex2 == j))
			{
				XMFLOAT3 xmf3Edge01 = Vector3::Subtract(pxmf3Positions[nIndex1], pxmf3Positions[nIndex0]);
				XMFLOAT3 xmf3Edge02 = Vector3::Subtract(pxmf3Positions[nIndex2], pxmf3Positions[nIndex0]);
				XMFLOAT3 xmf3Normal = Vector3::CrossProduct(xmf3Edge01, xmf3Edge02, true);
				xmf3SumOfNormal = Vector3::Add(xmf3SumOfNormal, xmf3Normal);
			}
		}
		pxmf3Normals[j] = Vector3::Normalize(xmf3SumOfNormal);
	}
}

void CMeshIlluminated::CalculateVertexNormals(XMFLOAT3 *pxmf3Normals, XMFLOAT3 *pxmf3Positions, int nVertices, UINT *pnIndices, int nIndices)
{
	switch (m_d3dPrimitiveTopology)
	{
		case D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
			if (pnIndices)
				CalculateTriangleListVertexNormals(pxmf3Normals, pxmf3Positions, nVertices, pnIndices, nIndices);
			else
				CalculateTriangleListVertexNormals(pxmf3Normals, pxmf3Positions, nVertices);
			break;
		case D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
			CalculateTriangleStripVertexNormals(pxmf3Normals, pxmf3Positions, nVertices, pnIndices, nIndices);
			break;
		default:
			break;
	}
}

//////////////////////////////////////////////////////////////////////////////////
//
CCubeMeshIlluminated::CCubeMeshIlluminated(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, float fWidth, float fHeight, float fDepth) : CMeshIlluminated(pd3dDevice, pd3dCommandList)
{
	m_nVertices = 36;
	m_nStride = sizeof(CIlluminatedVertex);
	m_nOffset = 0;
	m_nSlot = 0;
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	float fx = fWidth*0.5f, fy = fHeight*0.5f, fz = fDepth*0.5f;

	XMFLOAT3 pxmf3Positions[36];
	int i = 0;
	pxmf3Positions[i++] = XMFLOAT3(-fx, +fy, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, +fy, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -fy, -fz);

	pxmf3Positions[i++] = XMFLOAT3(-fx, +fy, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -fy, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -fy, -fz);

	pxmf3Positions[i++] = XMFLOAT3(-fx, +fy, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, +fy, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, +fy, -fz);

	pxmf3Positions[i++] = XMFLOAT3(-fx, +fy, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, +fy, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, +fy, -fz);

	pxmf3Positions[i++] = XMFLOAT3(-fx, -fy, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -fy, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, +fy, +fz);

	pxmf3Positions[i++] = XMFLOAT3(-fx, -fy, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, +fy, +fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, +fy, +fz);

	pxmf3Positions[i++] = XMFLOAT3(-fx, -fy, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -fy, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -fy, +fz);

	pxmf3Positions[i++] = XMFLOAT3(-fx, -fy, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -fy, +fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -fy, +fz);

	pxmf3Positions[i++] = XMFLOAT3(-fx, +fy, +fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, +fy, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -fy, -fz);

	pxmf3Positions[i++] = XMFLOAT3(-fx, +fy, +fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -fy, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -fy, +fz);

	pxmf3Positions[i++] = XMFLOAT3(+fx, +fy, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, +fy, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -fy, +fz);

	pxmf3Positions[i++] = XMFLOAT3(+fx, +fy, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -fy, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -fy, -fz);

	XMFLOAT3 pxmf3Normals[36];
	CalculateVertexNormals(pxmf3Normals, pxmf3Positions, m_nVertices, NULL, 0);

	CIlluminatedVertex pVertices[36];
	for (int i = 0; i < 36; i++) pVertices[i] = CIlluminatedVertex(pxmf3Positions[i], pxmf3Normals[i]);

	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices, m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);

	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

	CalculateBoundingBox((XMFLOAT3 *) pxmf3Positions, sizeof(XMFLOAT3));
}

CCubeMeshIlluminated::~CCubeMeshIlluminated()
{
}

//////////////////////////////////////////////////////////////////////////////////
//
CAirPlaneMeshIlluminated::CAirPlaneMeshIlluminated(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, float fWidth, float fHeight, float fDepth) : CMeshIlluminated(pd3dDevice, pd3dCommandList)
{
	m_nVertices = 24 * 3;
	m_nStride = sizeof(CIlluminatedVertex);
	m_nOffset = 0;
	m_nSlot = 0;
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	float fx = fWidth*0.5f, fy = fHeight*0.5f, fz = fDepth*0.5f;

	float x1 = fx * 0.2f, y1 = fy * 0.2f, x2 = fx * 0.1f, y3 = fy * 0.3f, y2 = ((y1 - (fy - y3))/ x1)* x2 + (fy - y3);
	int i = 0;

	XMFLOAT3 pxmf3Positions[72];

	//Upper Plane
	pxmf3Positions[i++] = XMFLOAT3(0.0f, +(fy + y3), -fz);
	pxmf3Positions[i++] = XMFLOAT3(+x1, -y1, -fz);
	pxmf3Positions[i++] = XMFLOAT3(0.0f, 0.0f, -fz);

	pxmf3Positions[i++] = XMFLOAT3(0.0f, +(fy + y3), -fz);
	pxmf3Positions[i++] = XMFLOAT3(0.0f, 0.0f, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-x1, -y1, -fz);

	pxmf3Positions[i++] = XMFLOAT3(+x2, +y2, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -y3, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+x1, -y1, -fz);

	pxmf3Positions[i++] = XMFLOAT3(-x2, +y2, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-x1, -y1, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -y3, -fz);

	//Lower Plane
	pxmf3Positions[i++] = XMFLOAT3(0.0f, +(fy + y3), +fz);
	pxmf3Positions[i++] = XMFLOAT3(0.0f, 0.0f, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+x1, -y1, +fz);

	pxmf3Positions[i++] = XMFLOAT3(0.0f, +(fy + y3), +fz);
	pxmf3Positions[i++] = XMFLOAT3(-x1, -y1, +fz);
	pxmf3Positions[i++] = XMFLOAT3(0.0f, 0.0f, +fz);

	pxmf3Positions[i++] = XMFLOAT3(+x2, +y2, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+x1, -y1, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -y3, +fz);

	pxmf3Positions[i++] = XMFLOAT3(-x2, +y2, +fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -y3, +fz);
	pxmf3Positions[i++] = XMFLOAT3(-x1, -y1, +fz);

	//Right Plane
	pxmf3Positions[i++] = XMFLOAT3(0.0f, +(fy + y3), -fz);
	pxmf3Positions[i++] = XMFLOAT3(0.0f, +(fy + y3), +fz);
	pxmf3Positions[i++] = XMFLOAT3(+x2, +y2, -fz);

	pxmf3Positions[i++] = XMFLOAT3(+x2, +y2, -fz);
	pxmf3Positions[i++] = XMFLOAT3(0.0f, +(fy + y3), +fz);
	pxmf3Positions[i++] = XMFLOAT3(+x2, +y2, +fz);

	pxmf3Positions[i++] = XMFLOAT3(+x2, +y2, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+x2, +y2, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -y3, -fz);

	pxmf3Positions[i++] = XMFLOAT3(+fx, -y3, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+x2, +y2, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -y3, +fz);

	//Back/Right Plane
	pxmf3Positions[i++] = XMFLOAT3(+x1, -y1, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -y3, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -y3, +fz);

	pxmf3Positions[i++] = XMFLOAT3(+x1, -y1, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+fx, -y3, +fz);
	pxmf3Positions[i++] = XMFLOAT3(+x1, -y1, +fz);

	pxmf3Positions[i++] = XMFLOAT3(0.0f, 0.0f, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+x1, -y1, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+x1, -y1, +fz);

	pxmf3Positions[i++] = XMFLOAT3(0.0f, 0.0f, -fz);
	pxmf3Positions[i++] = XMFLOAT3(+x1, -y1, +fz);
	pxmf3Positions[i++] = XMFLOAT3(0.0f, 0.0f, +fz);

	//Left Plane
	pxmf3Positions[i++] = XMFLOAT3(0.0f, +(fy + y3), +fz);
	pxmf3Positions[i++] = XMFLOAT3(0.0f, +(fy + y3), -fz);
	pxmf3Positions[i++] = XMFLOAT3(-x2, +y2, -fz);

	pxmf3Positions[i++] = XMFLOAT3(0.0f, +(fy + y3), +fz);
	pxmf3Positions[i++] = XMFLOAT3(-x2, +y2, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-x2, +y2, +fz);

	pxmf3Positions[i++] = XMFLOAT3(-x2, +y2, +fz);
	pxmf3Positions[i++] = XMFLOAT3(-x2, +y2, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -y3, -fz);

	pxmf3Positions[i++] = XMFLOAT3(-x2, +y2, +fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -y3, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -y3, +fz);

	//Back/Left Plane
	pxmf3Positions[i++] = XMFLOAT3(0.0f, 0.0f, -fz);
	pxmf3Positions[i++] = XMFLOAT3(0.0f, 0.0f, +fz);
	pxmf3Positions[i++] = XMFLOAT3(-x1, -y1, +fz);

	pxmf3Positions[i++] = XMFLOAT3(0.0f, 0.0f, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-x1, -y1, +fz);
	pxmf3Positions[i++] = XMFLOAT3(-x1, -y1, -fz);

	pxmf3Positions[i++] = XMFLOAT3(-x1, -y1, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-x1, -y1, +fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -y3, +fz);

	pxmf3Positions[i++] = XMFLOAT3(-x1, -y1, -fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -y3, +fz);
	pxmf3Positions[i++] = XMFLOAT3(-fx, -y3, -fz);

	XMFLOAT3 pxmf3Normals[72];
	CalculateVertexNormals(pxmf3Normals, pxmf3Positions, m_nVertices, NULL, 0);

	CIlluminatedVertex pVertices[72];
	for (int i = 0; i < 72; i++) pVertices[i] = CIlluminatedVertex(pxmf3Positions[i], pxmf3Normals[i]);

	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices, m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);

	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

	CalculateBoundingBox((XMFLOAT3 *) pxmf3Positions, sizeof(XMFLOAT3));
}

CAirPlaneMeshIlluminated::~CAirPlaneMeshIlluminated()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CPlaneMeshIlluminated::CPlaneMeshIlluminated(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, float fWidth, float fHeight, float fDepth, float fxPosition, float fyPosition, float fzPosition) : CMeshIlluminated(pd3dDevice, pd3dCommandList)
{
	m_nVertices = 6;
	m_nStride = sizeof(CIlluminatedVertex);
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	CIlluminatedVertex pVertices[6];

	float fx = (fWidth * 0.5f) + fxPosition, fy = (fHeight * 0.5f) + fyPosition, fz = (fDepth * 0.5f) + fzPosition;

	if (fWidth == 0.0f)
	{
		if (fxPosition > 0.0f)
		{
			pVertices[0] = CIlluminatedVertex(XMFLOAT3(fx, +fy, -fz), XMFLOAT3(-1.0f, 0.0f, 0.0f));
			pVertices[1] = CIlluminatedVertex(XMFLOAT3(fx, -fy, -fz), XMFLOAT3(-1.0f, 0.0f, 0.0f));
			pVertices[2] = CIlluminatedVertex(XMFLOAT3(fx, -fy, +fz), XMFLOAT3(-1.0f, 0.0f, 0.0f));
			pVertices[3] = CIlluminatedVertex(XMFLOAT3(fx, -fy, +fz), XMFLOAT3(-1.0f, 0.0f, 0.0f));
			pVertices[4] = CIlluminatedVertex(XMFLOAT3(fx, +fy, +fz), XMFLOAT3(-1.0f, 0.0f, 0.0f));
			pVertices[5] = CIlluminatedVertex(XMFLOAT3(fx, +fy, -fz), XMFLOAT3(-1.0f, 0.0f, 0.0f));
		}
		else
		{
			pVertices[0] = CIlluminatedVertex(XMFLOAT3(fx, +fy, +fz), XMFLOAT3(+1.0f, 0.0f, 0.0f));
			pVertices[1] = CIlluminatedVertex(XMFLOAT3(fx, -fy, +fz), XMFLOAT3(+1.0f, 0.0f, 0.0f));
			pVertices[2] = CIlluminatedVertex(XMFLOAT3(fx, -fy, -fz), XMFLOAT3(+1.0f, 0.0f, 0.0f));
			pVertices[3] = CIlluminatedVertex(XMFLOAT3(fx, -fy, -fz), XMFLOAT3(+1.0f, 0.0f, 0.0f));
			pVertices[4] = CIlluminatedVertex(XMFLOAT3(fx, +fy, -fz), XMFLOAT3(+1.0f, 0.0f, 0.0f));
			pVertices[5] = CIlluminatedVertex(XMFLOAT3(fx, +fy, +fz), XMFLOAT3(+1.0f, 0.0f, 0.0f));
		}
	}
	else if (fHeight == 0.0f)
	{
		if (fyPosition > 0.0f)
		{
			pVertices[0] = CIlluminatedVertex(XMFLOAT3(+fx, fy, -fz), XMFLOAT3(0.0f, -1.0f, 0.0f));
			pVertices[1] = CIlluminatedVertex(XMFLOAT3(+fx, fy, +fz), XMFLOAT3(0.0f, -1.0f, 0.0f));
			pVertices[2] = CIlluminatedVertex(XMFLOAT3(-fx, fy, +fz), XMFLOAT3(0.0f, -1.0f, 0.0f));
			pVertices[3] = CIlluminatedVertex(XMFLOAT3(-fx, fy, +fz), XMFLOAT3(0.0f, -1.0f, 0.0f));
			pVertices[4] = CIlluminatedVertex(XMFLOAT3(-fx, fy, -fz), XMFLOAT3(0.0f, -1.0f, 0.0f));
			pVertices[5] = CIlluminatedVertex(XMFLOAT3(+fx, fy, -fz), XMFLOAT3(0.0f, -1.0f, 0.0f));
		}
		else
		{
			pVertices[0] = CIlluminatedVertex(XMFLOAT3(+fx, fy, +fz), XMFLOAT3(0.0f, +1.0f, 0.0f));
			pVertices[1] = CIlluminatedVertex(XMFLOAT3(+fx, fy, -fz), XMFLOAT3(0.0f, +1.0f, 0.0f));
			pVertices[2] = CIlluminatedVertex(XMFLOAT3(-fx, fy, -fz), XMFLOAT3(0.0f, +1.0f, 0.0f));
			pVertices[3] = CIlluminatedVertex(XMFLOAT3(-fx, fy, -fz), XMFLOAT3(0.0f, +1.0f, 0.0f));
			pVertices[4] = CIlluminatedVertex(XMFLOAT3(-fx, fy, +fz), XMFLOAT3(0.0f, +1.0f, 0.0f));
			pVertices[5] = CIlluminatedVertex(XMFLOAT3(+fx, fy, +fz), XMFLOAT3(0.0f, +1.0f, 0.0f));
		}
	}
	else if (fDepth == 0.0f)
	{
		if (fzPosition > 0.0f)
		{
			pVertices[0] = CIlluminatedVertex(XMFLOAT3(+fx, +fy, fz), XMFLOAT3(0.0f, 0.0f, -1.0f));
			pVertices[1] = CIlluminatedVertex(XMFLOAT3(+fx, -fy, fz), XMFLOAT3(0.0f, 0.0f, -1.0f));
			pVertices[2] = CIlluminatedVertex(XMFLOAT3(-fx, -fy, fz), XMFLOAT3(0.0f, 0.0f, -1.0f));
			pVertices[3] = CIlluminatedVertex(XMFLOAT3(-fx, -fy, fz), XMFLOAT3(0.0f, 0.0f, -1.0f));
			pVertices[4] = CIlluminatedVertex(XMFLOAT3(-fx, +fy, fz), XMFLOAT3(0.0f, 0.0f, -1.0f));
			pVertices[5] = CIlluminatedVertex(XMFLOAT3(+fx, +fy, fz), XMFLOAT3(0.0f, 0.0f, -1.0f));
		}
		else
		{
			pVertices[0] = CIlluminatedVertex(XMFLOAT3(-fx, +fy, fz), XMFLOAT3(0.0f, 0.0f, +1.0f));
			pVertices[1] = CIlluminatedVertex(XMFLOAT3(-fx, -fy, fz), XMFLOAT3(0.0f, 0.0f, +1.0f));
			pVertices[2] = CIlluminatedVertex(XMFLOAT3(+fx, -fy, fz), XMFLOAT3(0.0f, 0.0f, +1.0f));
			pVertices[3] = CIlluminatedVertex(XMFLOAT3(+fx, -fy, fz), XMFLOAT3(0.0f, 0.0f, +1.0f));
			pVertices[4] = CIlluminatedVertex(XMFLOAT3(+fx, +fy, fz), XMFLOAT3(0.0f, 0.0f, +1.0f));
			pVertices[5] = CIlluminatedVertex(XMFLOAT3(-fx, +fy, fz), XMFLOAT3(0.0f, 0.0f, +1.0f));
		}
	}

	m_pd3dVertexBuffer = CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices, m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);

	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

	CalculateBoundingBox((XMFLOAT3 *) pVertices, m_nStride);
}

CPlaneMeshIlluminated::~CPlaneMeshIlluminated()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CGeometryShadowMesh::CGeometryShadowMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, CGeometryShadowVertex* pGeometryShadowVertices, UINT nGeometryShadowVertices) : CMesh(pd3dDevice, pd3dCommandList)
{
	m_nVertices = nGeometryShadowVertices;
	m_nStride = sizeof(CGeometryShadowVertex);
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
	m_pd3dVertexBuffer = CreateBufferResource(pd3dDevice, pd3dCommandList, pGeometryShadowVertices, m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);

	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;
}

CGeometryShadowMesh::~CGeometryShadowMesh()
{
}