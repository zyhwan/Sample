///-----------------------------------------------------------------------------
// File: Shader.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Shader.h"
#include "DDSTextureLoader12.h"
#include "Scene.h"

CShader::CShader()
{
	m_d3dSrvCPUDescriptorStartHandle.ptr = NULL;
	m_d3dSrvGPUDescriptorStartHandle.ptr = NULL;
}

CShader::~CShader()
{
	if (m_pd3dCbvSrvDescriptorHeap) m_pd3dCbvSrvDescriptorHeap->Release();
	if (m_pd3dPipelineState) m_pd3dPipelineState->Release();
}

D3D12_SHADER_BYTECODE CShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CreateGeometryShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob)
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob *pd3dErrorBlob = NULL;
	::D3DCompileFromFile(pszFileName, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, pszShaderName, pszShaderProfile, nCompileFlags, 0, ppd3dShaderBlob, NULL);
	//	char *pErrorString = (char *) pd3dErrorBlob->GetBufferPointer();

	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();

	return(d3dShaderByteCode);
}

D3D12_INPUT_LAYOUT_DESC CShader::CreateInputLayout()
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;

	return(d3dInputLayoutDesc);
}

D3D12_RASTERIZER_DESC CShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	return(d3dRasterizerDesc);
}

D3D12_DEPTH_STENCIL_DESC CShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;

	return(d3dDepthStencilDesc);
}

D3D12_BLEND_DESC CShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	return(d3dBlendDesc);
}

void CShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE d3dPrimitiveTopology, UINT nRenderTargets, DXGI_FORMAT* pdxgiRtvFormats, DXGI_FORMAT dxgiDsvFormat)
{	
	ID3DBlob *pd3dVertexShaderBlob = NULL, *pd3dGeometryShaderBlob = NULL, *pd3dPixelShaderBlob = NULL;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);
	d3dPipelineStateDesc.GS = CreateGeometryShader(&pd3dGeometryShaderBlob);
	d3dPipelineStateDesc.PS = CreatePixelShader(&pd3dPixelShaderBlob);
	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = d3dPrimitiveTopology;
	d3dPipelineStateDesc.NumRenderTargets = nRenderTargets;
	for (UINT i = 0; i < nRenderTargets; i++) d3dPipelineStateDesc.RTVFormats[i] = (pdxgiRtvFormats) ? pdxgiRtvFormats[i] : DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = dxgiDsvFormat;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	HRESULT hResult = pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc, __uuidof(ID3D12PipelineState), (void **)&m_pd3dPipelineState);

	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dGeometryShaderBlob) pd3dGeometryShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();

	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[] d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void CShader::CreateCbvSrvDescriptorHeaps(ID3D12Device *pd3dDevice, int nConstantBufferViews, int nShaderResourceViews)
{
	D3D12_DESCRIPTOR_HEAP_DESC d3dDescriptorHeapDesc;
	d3dDescriptorHeapDesc.NumDescriptors = nConstantBufferViews + nShaderResourceViews; //CBVs + SRVs 
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	d3dDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	d3dDescriptorHeapDesc.NodeMask = 0;
	pd3dDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void **)&m_pd3dCbvSrvDescriptorHeap);

	m_d3dCbvCPUDescriptorStartHandle = m_pd3dCbvSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	m_d3dCbvGPUDescriptorStartHandle = m_pd3dCbvSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
	m_d3dSrvCPUDescriptorStartHandle.ptr = m_d3dCbvCPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nConstantBufferViews);
	m_d3dSrvGPUDescriptorStartHandle.ptr = m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nConstantBufferViews);

	m_d3dSrvCPUDescriptorNextHandle = m_d3dSrvCPUDescriptorStartHandle;
	m_d3dSrvGPUDescriptorNextHandle = m_d3dSrvGPUDescriptorStartHandle;
}

void CShader::CreateConstantBufferViews(ID3D12Device *pd3dDevice, int nConstantBufferViews, ID3D12Resource *pd3dConstantBuffers, UINT nStride)
{
	D3D12_GPU_VIRTUAL_ADDRESS d3dGpuVirtualAddress = pd3dConstantBuffers->GetGPUVirtualAddress();
	D3D12_CONSTANT_BUFFER_VIEW_DESC d3dCBVDesc;
	d3dCBVDesc.SizeInBytes = nStride;
	for (int j = 0; j < nConstantBufferViews; j++)
	{
		d3dCBVDesc.BufferLocation = d3dGpuVirtualAddress + (nStride * j);
		D3D12_CPU_DESCRIPTOR_HANDLE d3dCbvCPUDescriptorHandle;
		d3dCbvCPUDescriptorHandle.ptr = m_d3dCbvCPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * j);
		pd3dDevice->CreateConstantBufferView(&d3dCBVDesc, d3dCbvCPUDescriptorHandle);
	}
}

void CShader::CreateShaderResourceViews(ID3D12Device* pd3dDevice, CTexture* pTexture, UINT nDescriptorHeapIndex, UINT nRootParameterStartIndex)
{
	m_d3dSrvCPUDescriptorNextHandle.ptr += (::gnCbvSrvDescriptorIncrementSize * nDescriptorHeapIndex);
	m_d3dSrvGPUDescriptorNextHandle.ptr += (::gnCbvSrvDescriptorIncrementSize * nDescriptorHeapIndex);

	int nTextures = pTexture->GetTextures();
	UINT nTextureType = pTexture->GetTextureType();
	for (int i = 0; i < nTextures; i++)
	{
		ID3D12Resource* pShaderResource = pTexture->GetResource(i);
		D3D12_SHADER_RESOURCE_VIEW_DESC d3dShaderResourceViewDesc = pTexture->GetShaderResourceViewDesc(i);
		pd3dDevice->CreateShaderResourceView(pShaderResource, &d3dShaderResourceViewDesc, m_d3dSrvCPUDescriptorNextHandle);
		m_d3dSrvCPUDescriptorNextHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
		pTexture->SetSrvGpuDescriptorHandle(i, m_d3dSrvGPUDescriptorNextHandle);
		m_d3dSrvGPUDescriptorNextHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
	}
	int nRootParameters = pTexture->GetRootParameters();
	for (int i = 0; i < nRootParameters; i++) pTexture->SetRootParameterIndex(i, nRootParameterStartIndex + i);
}

void CShader::CreateShaderResourceViews(ID3D12Device* pd3dDevice, int nResources, ID3D12Resource** ppd3dResources, DXGI_FORMAT *pdxgiSrvFormats)
{
	for (int i = 0; i < nResources; i++)
	{
		if (ppd3dResources[i])
		{
			D3D12_SHADER_RESOURCE_VIEW_DESC d3dShaderResourceViewDesc;
			d3dShaderResourceViewDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			d3dShaderResourceViewDesc.Format = pdxgiSrvFormats[i];
			d3dShaderResourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			d3dShaderResourceViewDesc.Texture2D.MipLevels = 1;
			d3dShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
			d3dShaderResourceViewDesc.Texture2D.PlaneSlice = 0;
			d3dShaderResourceViewDesc.Texture2D.ResourceMinLODClamp = 0.0f;
			pd3dDevice->CreateShaderResourceView(ppd3dResources[i], &d3dShaderResourceViewDesc, m_d3dSrvCPUDescriptorNextHandle);

			m_d3dSrvCPUDescriptorNextHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
			m_d3dSrvGPUDescriptorNextHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
		}
	}
}

void CShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World)
{
}

void CShader::ReleaseShaderVariables()
{
}

void CShader::ReleaseUploadBuffers()
{
}

void CShader::OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList)
{
	if (m_pd3dPipelineState) pd3dCommandList->SetPipelineState(m_pd3dPipelineState);
	if (m_pd3dCbvSrvDescriptorHeap) pd3dCommandList->SetDescriptorHeaps(1, &m_pd3dCbvSrvDescriptorHeap);

	UpdateShaderVariables(pd3dCommandList);
}

void CShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	OnPrepareRender(pd3dCommandList);
}

void CShader::OnPostRender(ID3D12GraphicsCommandList* pd3dCommandList)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CPlayerShader::CPlayerShader()
{
}

CPlayerShader::~CPlayerShader()
{
}

D3D12_INPUT_LAYOUT_DESC CPlayerShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] ={ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] ={ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CPlayerShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSPlayer", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSPlayer", "ps_5_1", ppd3dShaderBlob));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CIlluminatedShader::CIlluminatedShader()
{
}

CIlluminatedShader::~CIlluminatedShader()
{
}

D3D12_INPUT_LAYOUT_DESC CIlluminatedShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] ={ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] ={ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CIlluminatedShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSLighting", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CIlluminatedShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSLighting", "ps_5_1", ppd3dShaderBlob));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CObjectsShader::CObjectsShader()
{
}

CObjectsShader::~CObjectsShader()
{
}

BoundingBox CObjectsShader::CalculateBoundingBox()
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->CalculateBoundingBox();

	BoundingBox xmBoundingBox = m_ppObjects[0]->m_xmBoundingBox;
	for (int i = 1; i < m_nObjects; i++) BoundingBox::CreateMerged(xmBoundingBox, xmBoundingBox, m_ppObjects[i]->m_xmBoundingBox);

	return(xmBoundingBox);
}

void CObjectsShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	m_nObjects = 13;
	m_ppObjects = new CGameObject*[m_nObjects];

	CreateShaderVariables(pd3dDevice, pd3dCommandList);

	CPlaneMeshIlluminated *pPlaneMesh = new CPlaneMeshIlluminated(pd3dDevice, pd3dCommandList, _PLANE_WIDTH, 0.0f, _PLANE_HEIGHT, 0.0f, 0.0f, 0.0f);

	CMaterial *pPlaneMaterial = new CMaterial();
	pPlaneMaterial->SetReflection(1);

	m_ppObjects[0] = new CGameObject(1); //Plane
	m_ppObjects[0]->SetMesh(0, pPlaneMesh);
	m_ppObjects[0]->SetMaterial(pPlaneMaterial);
	m_ppObjects[0]->SetPosition(0.0f, 0.0f, 0.0f);

	CAirPlaneMeshIlluminated *pAirPlaneMesh = new CAirPlaneMeshIlluminated(pd3dDevice, pd3dCommandList, 40.0f, 40.0f, 4.0f);

	CMaterial *pMaterial = new CMaterial();
	pMaterial->SetReflection(2);

	CRotatingObject *pRoatingAirPlane = new CRotatingObject(1);
	pRoatingAirPlane->SetMesh(0, pAirPlaneMesh);
	pRoatingAirPlane->SetMaterial(pMaterial);
	pRoatingAirPlane->SetPosition(100.0f, 50.0f, 120.0f);
	pRoatingAirPlane->Rotate(90.0f, 0.0f, 0.0f);
	pRoatingAirPlane->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 1.0f));
	pRoatingAirPlane->SetRotationSpeed(0.0f);
	m_ppObjects[1] = pRoatingAirPlane;

	CCubeMeshIlluminated *pCubeMesh = new CCubeMeshIlluminated(pd3dDevice, pd3dCommandList, 30.0f, 30.0f, 30.0f);

	pMaterial = new CMaterial();
	pMaterial->SetReflection(3);

	CRotatingObject *pRotatingCube;

	pRotatingCube = new CRotatingObject(1);
	pRotatingCube->SetMesh(0, pCubeMesh);
	pRotatingCube->SetMaterial(pMaterial);
	pRotatingCube->SetPosition(-100.0f, 145.0f, -120.0f);
	pRotatingCube->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pRotatingCube->SetRotationSpeed(10.0f);
	m_ppObjects[2] = pRotatingCube;

	pRotatingCube = new CRotatingObject(1);
	pRotatingCube->SetMesh(0, pCubeMesh);
	pRotatingCube->SetMaterial(pMaterial);
	pRotatingCube->SetPosition(+150.0f, 40.0f, -180.0f);
	pRotatingCube->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pRotatingCube->SetRotationSpeed(20.0f);
	m_ppObjects[3] = pRotatingCube;

	pRotatingCube = new CRotatingObject(1);
	pRotatingCube->SetMesh(0, pCubeMesh);
	pRotatingCube->SetMaterial(pMaterial);
	pRotatingCube->SetPosition(+100.0f, 80.0f, -160.0f);
	pRotatingCube->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pRotatingCube->SetRotationSpeed(30.0f);
	m_ppObjects[4] = pRotatingCube;

	pRotatingCube = new CRotatingObject(1);
	pRotatingCube->SetMesh(0, pCubeMesh);
	pRotatingCube->SetMaterial(pMaterial);
	pRotatingCube->SetPosition(+130.0f, 15.0f, +170.0f);
	pRotatingCube->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pRotatingCube->SetRotationSpeed(40.0f);
	m_ppObjects[5] = pRotatingCube;

	pMaterial = new CMaterial();
	pMaterial->SetReflection(4);

	m_ppObjects[6] = new CGameObject(1);
	m_ppObjects[6]->SetMesh(0, pCubeMesh);
	m_ppObjects[6]->SetMaterial(pMaterial);
	m_ppObjects[6]->SetPosition(-330.0f, 30.0f, -305.0f);

	pMaterial = new CMaterial();
	pMaterial->SetReflection(5);

	m_ppObjects[7] = new CGameObject(1);
	m_ppObjects[7]->SetMesh(0, pAirPlaneMesh);
	m_ppObjects[7]->SetMaterial(pMaterial);
	m_ppObjects[7]->Rotate(90.0f, 0.0f, 0.0f);
	m_ppObjects[7]->SetPosition(XMFLOAT3(-(_PLANE_WIDTH * 0.15f), 60.0f, 0.0f));

	pRotatingCube = new CRotatingObject(1);
	pRotatingCube->SetMesh(0, pCubeMesh);
	pRotatingCube->SetMaterial(pMaterial);
	pRotatingCube->SetPosition(+330.0f, 15.0f, +350.0f);
	pRotatingCube->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pRotatingCube->SetRotationSpeed(10.0f);
	m_ppObjects[8] = pRotatingCube;

	pRotatingCube = new CRotatingObject(1);
	pRotatingCube->SetMesh(0, pCubeMesh);
	pRotatingCube->SetMaterial(pMaterial);
	pRotatingCube->SetPosition(-330.0f, 185.0f, +290.0f);
	pRotatingCube->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pRotatingCube->SetRotationSpeed(20.0f);
	m_ppObjects[9] = pRotatingCube;

	pRotatingCube = new CRotatingObject(1);
	pRotatingCube->SetMesh(0, pCubeMesh);
	pRotatingCube->SetMaterial(pMaterial);
	pRotatingCube->SetPosition(-130.0f, 55.0f, +200.0f);
	pRotatingCube->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pRotatingCube->SetRotationSpeed(30.0f);
	m_ppObjects[10] = pRotatingCube;

	m_ppObjects[11] = new CGameObject(1);
	m_ppObjects[11]->SetMesh(0, pCubeMesh);
	m_ppObjects[11]->SetMaterial(pMaterial);
	m_ppObjects[11]->SetPosition(XMFLOAT3(-30.0f, 15.0f, 0.0f));

	m_ppObjects[12] = new CGameObject(1);
	m_ppObjects[12]->SetMesh(0, pAirPlaneMesh);
	m_ppObjects[12]->SetMaterial(pMaterial);
	m_ppObjects[12]->Rotate(90.0f, 0.0f, 0.0f);
	m_ppObjects[12]->SetPosition(XMFLOAT3(+(_PLANE_WIDTH * 0.15f), 60.0f, 0.0f));

	pMaterial = new CMaterial();
	pMaterial->SetReflection(7);

	m_pDirectionalLight = new CGameObject(1);
	m_pDirectionalLight->SetMesh(0, pAirPlaneMesh);
	m_pDirectionalLight->SetMaterial(pMaterial);
	m_pDirectionalLight->Rotate(180.0f, 0.0f, 0.0f);
	m_pDirectionalLight->Rotate(0.0f, 0.0f, 45.0f);
	m_pDirectionalLight->SetPosition(XMFLOAT3(_PLANE_WIDTH * 0.25f, 450.0f, 0));

}

void CObjectsShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j]) delete m_ppObjects[j];
		delete[] m_ppObjects;
	}

	if (m_pDirectionalLight) delete m_pDirectionalLight;
}

void CObjectsShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}	
		
	static float fAngle = 0.0f;
	fAngle += 1.50f;
//*
	m_ppObjects[1]->m_xmf4x4World = Matrix4x4::AffineTransformation(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(-90.0f, 30.0f, -135.0f), XMFLOAT3(0.0f, fAngle * 0.5f, 0.0f), XMFLOAT3(0.0f, 120.0f, 0.0f));
	m_ppObjects[1]->Rotate(90.0f, 120.0f, 0.0f);

	m_ppObjects[7]->m_xmf4x4World = Matrix4x4::AffineTransformation(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(30.0f, 30.0f, -135.0f), XMFLOAT3(0.0f, fAngle, 0.0f), XMFLOAT3(0.0f, 60.0f, 0.0f));
	m_ppObjects[7]->Rotate(90.0f, 90.0f, 0.0f);

	m_ppObjects[12]->m_xmf4x4World = Matrix4x4::AffineTransformation(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(-130.0f, 30.0f, +135.0f), XMFLOAT3(0.0f, -fAngle * 0.25, 0.0f), XMFLOAT3(0.0f, 90.0f, 0.0f));
	m_ppObjects[12]->Rotate(90.0f, 50.0f, 0.0f);
//*/
/*??
	XMFLOAT4X4 xmf4x4Rotate = Matrix4x4::AffineTransformation(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(30.0f, 30.0f, -135.0f), XMFLOAT3(0.0f, 1.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_ppObjects[7]->m_xmf4x4World = Matrix4x4::Multiply(m_ppObjects[7]->m_xmf4x4World, xmf4x4Rotate);
//*/
/*???
	XMFLOAT4X4 xmf4x4Rotate = Matrix4x4::AffineTransformation(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(30.0f, 30.0f, -135.0f), XMFLOAT3(0.0f, 1.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_ppObjects[7]->m_xmf4x4World = Matrix4x4::Multiply(xmf4x4Rotate, m_ppObjects[7]->m_xmf4x4World);
//*/
}

void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j]) m_ppObjects[j]->ReleaseUploadBuffers();
	}

	if (m_pDirectionalLight) m_pDirectionalLight->ReleaseUploadBuffers();
}

void CObjectsShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CIlluminatedShader::Render(pd3dCommandList, pCamera);

	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			m_ppObjects[j]->UpdateShaderVariables(pd3dCommandList);
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}

	if (m_pDirectionalLight)
	{
		m_pDirectionalLight->UpdateShaderVariables(pd3dCommandList);
		m_pDirectionalLight->Render(pd3dCommandList, pCamera);
	}
}

void CObjectsShader::OnPostRender(ID3D12GraphicsCommandList* pd3dCommandList)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CDepthRenderShader::CDepthRenderShader(CObjectsShader* pObjectsShader, LIGHT *pLights)
{
	m_pObjectsShader = pObjectsShader;

	m_pLights = pLights;
	m_pToLightSpaces = new TOLIGHTSPACEINFO;

	XMFLOAT4X4 xmf4x4ToTexture = { 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f };
	m_xmProjectionToTexture = XMLoadFloat4x4(&xmf4x4ToTexture);
}

CDepthRenderShader::~CDepthRenderShader()
{
	if (m_pToLightSpaces) delete m_pToLightSpaces;
}

D3D12_SHADER_BYTECODE CDepthRenderShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDepthWriteShader", "ps_5_1", ppd3dShaderBlob));
}

D3D12_DEPTH_STENCIL_DESC CDepthRenderShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; 
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS; //D3D12_COMPARISON_FUNC_LESS_EQUAL
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;

	return(d3dDepthStencilDesc);
}

D3D12_RASTERIZER_DESC CDepthRenderShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
#ifdef _WITH_RASTERIZER_DEPTH_BIAS
	d3dRasterizerDesc.DepthBias = 250000;
#endif
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 1.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	return(d3dRasterizerDesc);
}

void CDepthRenderShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pContext)
{
	D3D12_DESCRIPTOR_HEAP_DESC d3dDescriptorHeapDesc;
	::ZeroMemory(&d3dDescriptorHeapDesc, sizeof(D3D12_DESCRIPTOR_HEAP_DESC));
	d3dDescriptorHeapDesc.NumDescriptors = MAX_DEPTH_TEXTURES; 
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	d3dDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	d3dDescriptorHeapDesc.NodeMask = 0;
	HRESULT hResult = pd3dDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void **)&m_pd3dRtvDescriptorHeap);

	m_pDepthFromLightTexture = new CTexture(MAX_DEPTH_TEXTURES, RESOURCE_TEXTURE2D_ARRAY, 0, 1);

	D3D12_CLEAR_VALUE d3dClearValue	= { DXGI_FORMAT_R32_FLOAT, { 1.0f, 1.0f, 1.0f, 1.0f } };
	for (UINT i = 0; i < MAX_DEPTH_TEXTURES; i++) m_pDepthFromLightTexture->CreateTexture(pd3dDevice, _DEPTH_BUFFER_WIDTH, _DEPTH_BUFFER_HEIGHT, DXGI_FORMAT_R32_FLOAT, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET, D3D12_RESOURCE_STATE_COMMON, &d3dClearValue, RESOURCE_TEXTURE2D, i);

	D3D12_RENDER_TARGET_VIEW_DESC d3dRenderTargetViewDesc;
	d3dRenderTargetViewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	d3dRenderTargetViewDesc.Texture2D.MipSlice = 0;
	d3dRenderTargetViewDesc.Texture2D.PlaneSlice = 0;
	d3dRenderTargetViewDesc.Format = DXGI_FORMAT_R32_FLOAT;

	D3D12_CPU_DESCRIPTOR_HANDLE d3dRtvCPUDescriptorHandle = m_pd3dRtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	for (UINT i = 0; i < MAX_DEPTH_TEXTURES; i++)
	{
		ID3D12Resource* pd3dTextureResource = m_pDepthFromLightTexture->GetResource(i);
		pd3dDevice->CreateRenderTargetView(pd3dTextureResource, &d3dRenderTargetViewDesc, d3dRtvCPUDescriptorHandle);
		m_pd3dRtvCPUDescriptorHandles[i] = d3dRtvCPUDescriptorHandle;
		d3dRtvCPUDescriptorHandle.ptr += ::gnRtvDescriptorIncrementSize;
	}

	d3dDescriptorHeapDesc.NumDescriptors = 1; 
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	hResult = pd3dDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void **)&m_pd3dDsvDescriptorHeap);

	D3D12_RESOURCE_DESC d3dResourceDesc;
	d3dResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	d3dResourceDesc.Alignment = 0;
	d3dResourceDesc.Width = _DEPTH_BUFFER_WIDTH;
	d3dResourceDesc.Height = _DEPTH_BUFFER_HEIGHT;
	d3dResourceDesc.DepthOrArraySize = 1;
	d3dResourceDesc.MipLevels = 1;
	d3dResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;
	d3dResourceDesc.SampleDesc.Count = 1;
	d3dResourceDesc.SampleDesc.Quality = 0;
	d3dResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	d3dResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_HEAP_PROPERTIES d3dHeapProperties;
	::ZeroMemory(&d3dHeapProperties, sizeof(D3D12_HEAP_PROPERTIES));
	d3dHeapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
	d3dHeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	d3dHeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	d3dHeapProperties.CreationNodeMask = 1;
	d3dHeapProperties.VisibleNodeMask = 1;

	d3dClearValue.Format = DXGI_FORMAT_D32_FLOAT;
	d3dClearValue.DepthStencil.Depth = 1.0f;
	d3dClearValue.DepthStencil.Stencil = 0;

	pd3dDevice->CreateCommittedResource(&d3dHeapProperties, D3D12_HEAP_FLAG_NONE, &d3dResourceDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &d3dClearValue, __uuidof(ID3D12Resource), (void **)&m_pd3dDepthBuffer);

	D3D12_DEPTH_STENCIL_VIEW_DESC d3dDepthStencilViewDesc;
	::ZeroMemory(&d3dDepthStencilViewDesc, sizeof(D3D12_DEPTH_STENCIL_VIEW_DESC));
	d3dDepthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	d3dDepthStencilViewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	d3dDepthStencilViewDesc.Flags = D3D12_DSV_FLAG_NONE;

	m_d3dDsvDescriptorCPUHandle = m_pd3dDsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	pd3dDevice->CreateDepthStencilView(m_pd3dDepthBuffer, &d3dDepthStencilViewDesc, m_d3dDsvDescriptorCPUHandle);

	for (int i = 0; i < MAX_DEPTH_TEXTURES; i++)
	{
		m_ppDepthRenderCameras[i] = new CCamera();
		m_ppDepthRenderCameras[i]->SetViewport(0, 0, _DEPTH_BUFFER_WIDTH, _DEPTH_BUFFER_HEIGHT, 0.0f, 1.0f);
		m_ppDepthRenderCameras[i]->SetScissorRect(0, 0, _DEPTH_BUFFER_WIDTH, _DEPTH_BUFFER_HEIGHT);
		m_ppDepthRenderCameras[i]->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	}

	CreateCbvSrvDescriptorHeaps(pd3dDevice, 0, m_pDepthFromLightTexture->GetTextures());
	CreateShaderResourceViews(pd3dDevice, m_pDepthFromLightTexture, 0, 5);

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CDepthRenderShader::ReleaseObjects()
{
	for (int i = 0; i < MAX_DEPTH_TEXTURES; i++)
	{
		if (m_ppDepthRenderCameras[i])
		{
			m_ppDepthRenderCameras[i]->ReleaseShaderVariables();
			delete m_ppDepthRenderCameras[i];
		}
	}

	if (m_pDepthFromLightTexture) m_pDepthFromLightTexture->Release();
	if (m_pd3dDepthBuffer) m_pd3dDepthBuffer->Release();

	if (m_pd3dRtvDescriptorHeap) m_pd3dRtvDescriptorHeap->Release();
	if (m_pd3dDsvDescriptorHeap) m_pd3dDsvDescriptorHeap->Release();
}

void CDepthRenderShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbDepthElementBytes;

	ncbDepthElementBytes = ((sizeof(TOLIGHTSPACEINFO) + 255) & ~255); //256�� ���
	m_pd3dcbToLightSpaces = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbDepthElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbToLightSpaces->Map(0, NULL, (void **)&m_pcbMappedToLightSpaces);
}

void CDepthRenderShader::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
	::memcpy(m_pcbMappedToLightSpaces, m_pToLightSpaces, sizeof(TOLIGHTSPACEINFO));

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbToLightGpuVirtualAddress = m_pd3dcbToLightSpaces->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(6, d3dcbToLightGpuVirtualAddress); 
}

void CDepthRenderShader::ReleaseShaderVariables()
{
	if (m_pd3dcbToLightSpaces)
	{
		m_pd3dcbToLightSpaces->Unmap(0, NULL);
		m_pd3dcbToLightSpaces->Release();
	}
}

void CreateFrustumPoints(XMMATRIX& xmmtxProjection, XMVECTOR* pxmvCornerPoints)
{
	BoundingFrustum xmFrustrum(xmmtxProjection);

	static const XMVECTORU32 vGrabY = { 0x00000000,0xFFFFFFFF,0x00000000,0x00000000 };
	static const XMVECTORU32 vGrabX = { 0xFFFFFFFF,0x00000000,0x00000000,0x00000000 };

	XMVECTORF32 vRightTop = { xmFrustrum.RightSlope, xmFrustrum.TopSlope, 1.0f, 1.0f };
	XMVECTORF32 vLeftBottom = { xmFrustrum.LeftSlope, xmFrustrum.BottomSlope, 1.0f, 1.0f };
	XMVECTORF32 vNear = { xmFrustrum.Near, xmFrustrum.Near, xmFrustrum.Near, 1.0f };
	XMVECTORF32 vFar = { xmFrustrum.Far, xmFrustrum.Far, xmFrustrum.Far, 1.0f };
	XMVECTOR vRightTopNear = XMVectorMultiply(vRightTop, vNear);
	XMVECTOR vRightTopFar = XMVectorMultiply(vRightTop, vFar);
	XMVECTOR vLeftBottomNear = XMVectorMultiply(vLeftBottom, vNear);
	XMVECTOR vLeftBottomFar = XMVectorMultiply(vLeftBottom, vFar);

	pxmvCornerPoints[0] = vRightTopNear;
	pxmvCornerPoints[1] = XMVectorSelect(vRightTopNear, vLeftBottomNear, vGrabX);
	pxmvCornerPoints[2] = vLeftBottomNear;
	pxmvCornerPoints[3] = XMVectorSelect(vRightTopNear, vLeftBottomNear, vGrabY);

	pxmvCornerPoints[4] = vRightTopFar;
	pxmvCornerPoints[5] = XMVectorSelect(vRightTopFar, vLeftBottomFar, vGrabX);
	pxmvCornerPoints[6] = vLeftBottomFar;
	pxmvCornerPoints[7] = XMVectorSelect(vRightTopFar, vLeftBottomFar, vGrabY);
}

struct TRIANGLECULLING
{
	XMVECTOR pt[3];
	BOOL culled;
};

void ComputeOrthographicProjectionNearAndFar(float& fNear, float& fFar, FXMVECTOR xmvLightOrthographicMin, FXMVECTOR xmvLightOrthographicMax, XMVECTOR* pxmvSceneAABBLightSpacePoints)
{
	fNear = FLT_MAX;
	fFar = -FLT_MAX;

	TRIANGLECULLING pxmvSceneAABBTriangles[16];
	int nTriangles = 1;

	static const int pnTriangleIndices[36] = { 0,1,2, 1,2,3, 4,5,6, 5,6,7, 0,2,4, 2,4,6, 1,3,5, 3,5,7, 0,1,4, 1,4,5, 2,3,6, 3,6,7 };
	int nPointPassesCollision[3];

	float fxOrthographicMin = XMVectorGetX(xmvLightOrthographicMin);
	float fxOrthographicMax = XMVectorGetX(xmvLightOrthographicMax);
	float fyOrthographicMin = XMVectorGetY(xmvLightOrthographicMin);
	float fyOrthographicMax = XMVectorGetY(xmvLightOrthographicMax);

	for (int i = 0; i < 12; i++)
	{
		pxmvSceneAABBTriangles[0].pt[0] = pxmvSceneAABBLightSpacePoints[pnTriangleIndices[i * 3 + 0]];
		pxmvSceneAABBTriangles[0].pt[1] = pxmvSceneAABBLightSpacePoints[pnTriangleIndices[i * 3 + 1]];
		pxmvSceneAABBTriangles[0].pt[2] = pxmvSceneAABBLightSpacePoints[pnTriangleIndices[i * 3 + 2]];
		pxmvSceneAABBTriangles[0].culled = false;

		nTriangles = 1;

		for (int j = 0; j < 4; j++)
		{
			float fEdge;
			int nComponent;

			if (j == 0)
			{
				fEdge = fxOrthographicMin;
				nComponent = 0;
			}
			else if (j == 1)
			{
				fEdge = fxOrthographicMax;
				nComponent = 0;
			}
			else if (j == 2)
			{
				fEdge = fyOrthographicMin;
				nComponent = 1;
			}
			else
			{
				fEdge = fyOrthographicMax;
				nComponent = 1;
			}

			for (int k = 0; k < nTriangles; k++)
			{
				if (!pxmvSceneAABBTriangles[k].culled)
				{
					int nInsideVertices = 0;
					XMVECTOR tempOrder;

					if (j == 0)
					{
						for (int m = 0; m < 3; m++)
						{
							nPointPassesCollision[m] = (XMVectorGetX(pxmvSceneAABBTriangles[k].pt[m]) > XMVectorGetX(xmvLightOrthographicMin)) ? 1 : 0;
							nInsideVertices += nPointPassesCollision[m];
						}
					}
					else if (j == 1)
					{
						for (int m = 0; m < 3; m++)
						{
							nPointPassesCollision[m] = (XMVectorGetX(pxmvSceneAABBTriangles[k].pt[m]) < XMVectorGetX(xmvLightOrthographicMax)) ? 1 : 0;
							nInsideVertices += nPointPassesCollision[m];
						}
					}
					else if (j == 2)
					{
						for (int m = 0; m < 3; m++)
						{
							nPointPassesCollision[m] = (XMVectorGetY(pxmvSceneAABBTriangles[k].pt[m]) > XMVectorGetY(xmvLightOrthographicMin)) ? 1 : 0;
							nInsideVertices += nPointPassesCollision[m];
						}
					}
					else
					{
						for (int m = 0; m < 3; m++)
						{
							nPointPassesCollision[m] = (XMVectorGetY(pxmvSceneAABBTriangles[k].pt[m]) < XMVectorGetY(xmvLightOrthographicMax)) ? 1 : 0;
							nInsideVertices += nPointPassesCollision[m];
						}
					}

					if (nPointPassesCollision[1] && !nPointPassesCollision[0])
					{
						tempOrder = pxmvSceneAABBTriangles[k].pt[0];
						pxmvSceneAABBTriangles[k].pt[0] = pxmvSceneAABBTriangles[k].pt[1];
						pxmvSceneAABBTriangles[k].pt[1] = tempOrder;
						nPointPassesCollision[0] = TRUE;
						nPointPassesCollision[1] = FALSE;
					}
					if (nPointPassesCollision[2] && !nPointPassesCollision[1])
					{
						tempOrder = pxmvSceneAABBTriangles[k].pt[1];
						pxmvSceneAABBTriangles[k].pt[1] = pxmvSceneAABBTriangles[k].pt[2];
						pxmvSceneAABBTriangles[k].pt[2] = tempOrder;
						nPointPassesCollision[1] = TRUE;
						nPointPassesCollision[2] = FALSE;
					}
					if (nPointPassesCollision[1] && !nPointPassesCollision[0])
					{
						tempOrder = pxmvSceneAABBTriangles[k].pt[0];
						pxmvSceneAABBTriangles[k].pt[0] = pxmvSceneAABBTriangles[k].pt[1];
						pxmvSceneAABBTriangles[k].pt[1] = tempOrder;
						nPointPassesCollision[0] = TRUE;
						nPointPassesCollision[1] = FALSE;
					}

					if (nInsideVertices == 0)
					{   
						pxmvSceneAABBTriangles[k].culled = true;
					}
					else if (nInsideVertices == 1)
					{
						pxmvSceneAABBTriangles[k].culled = false;

						XMVECTOR vVert0ToVert1 = pxmvSceneAABBTriangles[k].pt[1] - pxmvSceneAABBTriangles[k].pt[0];
						XMVECTOR vVert0ToVert2 = pxmvSceneAABBTriangles[k].pt[2] - pxmvSceneAABBTriangles[k].pt[0];

						float fHitPointTimeRatio = fEdge - XMVectorGetByIndex(pxmvSceneAABBTriangles[k].pt[0], nComponent);
						float fDistanceAlongVector01 = fHitPointTimeRatio / XMVectorGetByIndex(vVert0ToVert1, nComponent);
						float fDistanceAlongVector02 = fHitPointTimeRatio / XMVectorGetByIndex(vVert0ToVert2, nComponent);
						vVert0ToVert1 *= fDistanceAlongVector01;
						vVert0ToVert1 += pxmvSceneAABBTriangles[k].pt[0];
						vVert0ToVert2 *= fDistanceAlongVector02;
						vVert0ToVert2 += pxmvSceneAABBTriangles[k].pt[0];

						pxmvSceneAABBTriangles[k].pt[1] = vVert0ToVert2;
						pxmvSceneAABBTriangles[k].pt[2] = vVert0ToVert1;
					}
					else if (nInsideVertices == 2)
					{ 
						pxmvSceneAABBTriangles[nTriangles] = pxmvSceneAABBTriangles[k + 1];

						pxmvSceneAABBTriangles[k].culled = false;
						pxmvSceneAABBTriangles[k + 1].culled = false;

						XMVECTOR vVert2ToVert0 = pxmvSceneAABBTriangles[k].pt[0] - pxmvSceneAABBTriangles[k].pt[2];
						XMVECTOR vVert2ToVert1 = pxmvSceneAABBTriangles[k].pt[1] - pxmvSceneAABBTriangles[k].pt[2];

						float fHitPointTime_2_0 = fEdge - XMVectorGetByIndex(pxmvSceneAABBTriangles[k].pt[2], nComponent);
						float fDistanceAlongVector_2_0 = fHitPointTime_2_0 / XMVectorGetByIndex(vVert2ToVert0, nComponent);
						vVert2ToVert0 *= fDistanceAlongVector_2_0;
						vVert2ToVert0 += pxmvSceneAABBTriangles[k].pt[2];

						pxmvSceneAABBTriangles[k + 1].pt[0] = pxmvSceneAABBTriangles[k].pt[0];
						pxmvSceneAABBTriangles[k + 1].pt[1] = pxmvSceneAABBTriangles[k].pt[1];
						pxmvSceneAABBTriangles[k + 1].pt[2] = vVert2ToVert0;

						float fHitPointTime_2_1 = fEdge - XMVectorGetByIndex(pxmvSceneAABBTriangles[k].pt[2], nComponent);
						float fDistanceAlongVector_2_1 = fHitPointTime_2_1 / XMVectorGetByIndex(vVert2ToVert1, nComponent);
						vVert2ToVert1 *= fDistanceAlongVector_2_1;
						vVert2ToVert1 += pxmvSceneAABBTriangles[k].pt[2];
						pxmvSceneAABBTriangles[k].pt[0] = pxmvSceneAABBTriangles[k + 1].pt[1];
						pxmvSceneAABBTriangles[k].pt[1] = pxmvSceneAABBTriangles[k + 1].pt[2];
						pxmvSceneAABBTriangles[k].pt[2] = vVert2ToVert1;

						++nTriangles;
						++k;
					}
					else
					{ 
						pxmvSceneAABBTriangles[k].culled = false;
					}
				}            
			}
		}
		for (int n = 0; n < nTriangles; n++)
		{
			if (!pxmvSceneAABBTriangles[n].culled)
			{
				for (int x = 0; x < 3; x++)
				{
					float z = XMVectorGetZ(pxmvSceneAABBTriangles[n].pt[x]);
					if (fNear > z) fNear = z;
					if (fFar < z) fFar = z;
				}
			}
		}
	}
}

#define _WITH_ORTHOGRAPHIC_PROJECT_SCENE
//#define _WITH_ORTHOGRAPHIC_PROJECT_CAMERA_FRUSTUM
//#define _WITH_ORTHOGRAPHIC_PROJECT_CAMERA_FRUSTUM_SCENE

XMMATRIX CreateOrthographicProjectionMatrix(XMMATRIX& xmmtxLightView, CCamera *pSceneCamera, BoundingBox* pxmSceneBoundingBox)
{
	XMMATRIX xmmtxProjection;

#ifdef _WITH_ORTHOGRAPHIC_PROJECT_SCENE
	XMFLOAT3 pxmf3SceneAABBPoints[8];
	pxmSceneBoundingBox->GetCorners(pxmf3SceneAABBPoints);

	XMVECTOR xmvLightSpaceSceneAABBMin = g_XMFltMax;
	XMVECTOR xmvLightSpaceSceneAABBMax = g_XMFltMin;

	XMVECTOR pxmvLightSpaceSceneAABBPoints[8];
	for (int i = 0; i < 8; i++)
	{
		XMFLOAT4 xmf4SceneAABBPoint = XMFLOAT4(pxmf3SceneAABBPoints[i].x, pxmf3SceneAABBPoints[i].y, pxmf3SceneAABBPoints[i].z, 1.0f);
		pxmvLightSpaceSceneAABBPoints[i] = XMVector4Transform(XMLoadFloat4(&xmf4SceneAABBPoint), xmmtxLightView);
		xmvLightSpaceSceneAABBMin = XMVectorMin(pxmvLightSpaceSceneAABBPoints[i], xmvLightSpaceSceneAABBMin);
		xmvLightSpaceSceneAABBMax = XMVectorMax(pxmvLightSpaceSceneAABBPoints[i], xmvLightSpaceSceneAABBMax);
	}

	float fNearPlaneDistance = XMVectorGetZ(xmvLightSpaceSceneAABBMin);
	float fFarPlaneDistance = XMVectorGetZ(xmvLightSpaceSceneAABBMax);
	xmmtxProjection = XMMatrixOrthographicOffCenterLH(XMVectorGetX(xmvLightSpaceSceneAABBMin), XMVectorGetX(xmvLightSpaceSceneAABBMax), XMVectorGetY(xmvLightSpaceSceneAABBMin), XMVectorGetY(xmvLightSpaceSceneAABBMax), fNearPlaneDistance, fFarPlaneDistance);
#endif

#ifdef _WITH_ORTHOGRAPHIC_PROJECT_CAMERA_FRUSTUM
	XMFLOAT3 pxmf3CameraFrustumPoints[8];
	BoundingFrustum xmFrustrum(XMLoadFloat4x4(&pSceneCamera->m_xmf4x4Projection));
	xmFrustrum.GetCorners(pxmf3CameraFrustumPoints);

	XMMATRIX xmmtxInverseCameraView = XMMatrixInverse(NULL, XMLoadFloat4x4(&pSceneCamera->m_xmf4x4View));

	XMVECTOR xmvLightSpaceCameraFrustumAABBMin = g_XMFltMax;
	XMVECTOR xmvLightSpaceCameraFrustumAABBMax = g_XMFltMin;
	XMVECTOR xmvLightSpaceCameraFrustumPoint;
	XMVECTOR pxmvCameraFrustumPoints[8];
	for (int i = 0; i < 8; i++)
	{
		XMFLOAT4 xmf4CameraFrustumPoint = XMFLOAT4(pxmf3CameraFrustumPoints[i].x, pxmf3CameraFrustumPoints[i].y, pxmf3CameraFrustumPoints[i].z, 1.0f);
		pxmvCameraFrustumPoints[i] = XMLoadFloat4(&xmf4CameraFrustumPoint); //Camera Space
		xmvLightSpaceCameraFrustumPoint = XMVector4Transform(XMVector4Transform(pxmvCameraFrustumPoints[i], xmmtxInverseCameraView), xmmtxLightView); //Camera Space to World space, World space to Light Space
		xmvLightSpaceCameraFrustumAABBMin = XMVectorMin(xmvLightSpaceCameraFrustumPoint, xmvLightSpaceCameraFrustumAABBMin);
		xmvLightSpaceCameraFrustumAABBMax = XMVectorMax(xmvLightSpaceCameraFrustumPoint, xmvLightSpaceCameraFrustumAABBMax);
	}

	float fNearPlaneDistance = XMVectorGetZ(xmvLightSpaceCameraFrustumAABBMin);
	float fFarPlaneDistance = XMVectorGetZ(xmvLightSpaceCameraFrustumAABBMax);
	xmmtxProjection = XMMatrixOrthographicOffCenterLH(XMVectorGetX(xmvLightSpaceCameraFrustumAABBMin), XMVectorGetX(xmvLightSpaceCameraFrustumAABBMax), XMVectorGetY(xmvLightSpaceCameraFrustumAABBMin), XMVectorGetY(xmvLightSpaceCameraFrustumAABBMax), fNearPlaneDistance, fFarPlaneDistance);
#endif

#ifdef _WITH_ORTHOGRAPHIC_PROJECT_CAMERA_FRUSTUM_SCENE
/*Fit to Scene*/
	XMFLOAT3 pxmf3CameraFrustumPoints[8];
	BoundingFrustum xmFrustrum(XMLoadFloat4x4(&pSceneCamera->m_xmf4x4Projection));
	xmFrustrum.GetCorners(pxmf3CameraFrustumPoints);

	XMMATRIX xmmtxInverseCameraView = XMMatrixInverse(NULL, XMLoadFloat4x4(&pSceneCamera->m_xmf4x4View));

	XMVECTOR xmvLightSpaceCameraFrustumAABBMin = g_XMFltMax;
	XMVECTOR xmvLightSpaceCameraFrustumAABBMax = g_XMFltMin;
	XMVECTOR xmvLightSpaceCameraFrustumPoint;
	XMVECTOR pxmvCameraFrustumPoints[8];
	for (int i = 0; i < 8; i++)
	{
		XMFLOAT4 xmf4CameraFrustumPoint = XMFLOAT4(pxmf3CameraFrustumPoints[i].x, pxmf3CameraFrustumPoints[i].y, pxmf3CameraFrustumPoints[i].z, 1.0f);
		pxmvCameraFrustumPoints[i] = XMLoadFloat4(&xmf4CameraFrustumPoint); //Camera Space
		xmvLightSpaceCameraFrustumPoint = XMVector4Transform(XMVector4Transform(pxmvCameraFrustumPoints[i], xmmtxInverseCameraView), xmmtxLightView); //Camera Space to World space, World space to Light Space
		xmvLightSpaceCameraFrustumAABBMin = XMVectorMin(xmvLightSpaceCameraFrustumPoint, xmvLightSpaceCameraFrustumAABBMin);
		xmvLightSpaceCameraFrustumAABBMax = XMVectorMax(xmvLightSpaceCameraFrustumPoint, xmvLightSpaceCameraFrustumAABBMax);
	}

	XMVECTOR xmvLightOrthographicMin = xmvLightSpaceCameraFrustumAABBMin;
	XMVECTOR xmvLightOrthographicMax = xmvLightSpaceCameraFrustumAABBMax;

	XMVECTOR xmvDiagonal = XMVector3Length(pxmvCameraFrustumPoints[0] - pxmvCameraFrustumPoints[6]);
	float fBound = XMVectorGetX(xmvDiagonal);
	XMVECTOR xmvBoarderOffset = (xmvDiagonal - (xmvLightSpaceCameraFrustumAABBMax - xmvLightSpaceCameraFrustumAABBMin)) * g_XMOneHalf;
	XMVectorSetZ(xmvBoarderOffset, 0.0f);
	XMVectorSetW(xmvBoarderOffset, 0.0f);
	xmvLightOrthographicMax += xmvBoarderOffset;
	xmvLightOrthographicMin -= xmvBoarderOffset;

	float fLightCameraOrthographicMinZ = XMVectorGetZ(xmvLightOrthographicMin);

///*Move Light Texel Size
	XMVECTOR xmvUnitsPerTexel = g_XMZero;
	float fUnitsPerTexel = fBound / (float)_DEPTH_BUFFER_HEIGHT;
	xmvUnitsPerTexel = XMVectorSet(fUnitsPerTexel, fUnitsPerTexel, 0.0f, 0.0f);

	xmvLightOrthographicMin /= xmvUnitsPerTexel;
	xmvLightOrthographicMin = XMVectorFloor(xmvLightOrthographicMin);
	xmvLightOrthographicMin *= xmvUnitsPerTexel;

	xmvLightOrthographicMax /= xmvUnitsPerTexel;
	xmvLightOrthographicMax = XMVectorFloor(xmvLightOrthographicMax);
	xmvLightOrthographicMax *= xmvUnitsPerTexel;
//*/

	XMFLOAT3 pxmf3SceneAABBPoints[8];
	pxmSceneBoundingBox->GetCorners(pxmf3SceneAABBPoints);

	XMVECTOR pxmvLightSpaceSceneAABBPoints[8];
	for (int i = 0; i < 8; i++)
	{
		XMFLOAT4 xmf4SceneAABBPoint = XMFLOAT4(pxmf3SceneAABBPoints[i].x, pxmf3SceneAABBPoints[i].y, pxmf3SceneAABBPoints[i].z, 1.0f);
		pxmvLightSpaceSceneAABBPoints[i] = XMVector4Transform(XMLoadFloat4(&xmf4SceneAABBPoint), xmmtxLightView);
	}

	float fNearPlaneDistance = 0.0f;
	float fFarPlaneDistance = 10000.0f;

	ComputeOrthographicProjectionNearAndFar(fNearPlaneDistance, fFarPlaneDistance, xmvLightOrthographicMin, xmvLightOrthographicMax, pxmvLightSpaceSceneAABBPoints);
	if (fLightCameraOrthographicMinZ > fNearPlaneDistance) fNearPlaneDistance = fLightCameraOrthographicMinZ; //Pan Caking

	xmmtxProjection = XMMatrixOrthographicOffCenterLH(XMVectorGetX(xmvLightOrthographicMin), XMVectorGetX(xmvLightOrthographicMax), XMVectorGetY(xmvLightOrthographicMin), XMVectorGetY(xmvLightOrthographicMax), fNearPlaneDistance, fFarPlaneDistance);
#endif

	return(xmmtxProjection);
}

void CDepthRenderShader::PrepareShadowMap(ID3D12GraphicsCommandList *pd3dCommandList, CCamera* pCamera)
{
	BoundingBox xmBoundingBox = m_pObjectsShader->CalculateBoundingBox();

	for (int j = 0; j < MAX_LIGHTS; j++)
	{
		if (m_pLights[j].m_bEnable)
		{
			XMFLOAT3 xmf3Position = m_pLights[j].m_xmf3Position;
			XMFLOAT3 xmf3Look = m_pLights[j].m_xmf3Direction; 
			XMFLOAT3 xmf3Up = XMFLOAT3(0.0f, +1.0f, 0.0f);

			XMMATRIX xmmtxLightView = XMMatrixLookToLH(XMLoadFloat3(&xmf3Position), XMLoadFloat3(&xmf3Look), XMLoadFloat3(&xmf3Up));

			XMMATRIX xmmtxProjection;
			if (m_pLights[j].m_nType == DIRECTIONAL_LIGHT)
			{
				xmmtxProjection = CreateOrthographicProjectionMatrix(xmmtxLightView, pCamera, &xmBoundingBox);
			}
			else if (m_pLights[j].m_nType == SPOT_LIGHT)
			{
				float fFovAngle = 60.0f; // m_pLights->m_pLights[j].m_fPhi = cos(60.0f);
				float fAspectRatio = float(_DEPTH_BUFFER_WIDTH) / float(_DEPTH_BUFFER_HEIGHT);
				float fNearPlaneDistance = 10.0f, fFarPlaneDistance = m_pLights[j].m_fRange;

				xmmtxProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(fFovAngle), fAspectRatio, fNearPlaneDistance, fFarPlaneDistance);
			}
			else if (m_pLights[j].m_nType == POINT_LIGHT)
			{
				//ShadowMap[6]
			}

			m_ppDepthRenderCameras[j]->SetPosition(xmf3Position);
			XMStoreFloat4x4(&m_ppDepthRenderCameras[j]->m_xmf4x4View, xmmtxLightView);
			XMStoreFloat4x4(&m_ppDepthRenderCameras[j]->m_xmf4x4Projection, xmmtxProjection);

			XMMATRIX xmmtxToTexture = XMMatrixTranspose(xmmtxLightView * xmmtxProjection * m_xmProjectionToTexture);
			XMStoreFloat4x4(&m_pToLightSpaces->m_pxmf4x4ToTextures[j], xmmtxToTexture);
			m_pToLightSpaces->m_pxmf4LightPositions[j] = XMFLOAT4(xmf3Position.x, xmf3Position.y, xmf3Position.z, 1.0f);

			::SynchronizeResourceTransition(pd3dCommandList, m_pDepthFromLightTexture->GetResource(j), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_RENDER_TARGET);

			float pfClearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			pd3dCommandList->ClearRenderTargetView(m_pd3dRtvCPUDescriptorHandles[j], pfClearColor, 0, NULL);
			pd3dCommandList->ClearDepthStencilView(m_d3dDsvDescriptorCPUHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, NULL);
			pd3dCommandList->OMSetRenderTargets(1, &m_pd3dRtvCPUDescriptorHandles[j], TRUE, &m_d3dDsvDescriptorCPUHandle);

			Render(pd3dCommandList, m_ppDepthRenderCameras[j]);

			::SynchronizeResourceTransition(pd3dCommandList,  m_pDepthFromLightTexture->GetResource(j), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_COMMON);
		}
		else
		{
			m_pToLightSpaces->m_pxmf4LightPositions[j].w = 0.0f;
		}
	}
}

void CDepthRenderShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);

	for (int i = 0; i < m_pObjectsShader->m_nObjects; i++)
	{
		if (m_pObjectsShader->m_ppObjects[i])
		{
			m_pObjectsShader->m_ppObjects[i]->UpdateShaderVariables(pd3dCommandList);
			m_pObjectsShader->m_ppObjects[i]->Render(pd3dCommandList, pCamera);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CShadowMapShader::CShadowMapShader(CObjectsShader* pObjectsShader)
{
	m_pObjectsShader = pObjectsShader;
}

CShadowMapShader::~CShadowMapShader()
{
}

D3D12_DEPTH_STENCIL_DESC CShadowMapShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;

	return(d3dDepthStencilDesc);
}

D3D12_SHADER_BYTECODE CShadowMapShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSShadowMapShadow", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CShadowMapShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSShadowMapShadow", "ps_5_1", ppd3dShaderBlob));
}

void CShadowMapShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CShadowMapShader::ReleaseShaderVariables()
{
}

void CShadowMapShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	if (m_pDepthFromLightTexture) m_pDepthFromLightTexture->UpdateShaderVariables(pd3dCommandList);
}

void CShadowMapShader::ReleaseUploadBuffers()
{
}

void CShadowMapShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, void* pContext)
{
	m_pDepthFromLightTexture = (CTexture *)pContext;
	m_pDepthFromLightTexture->AddRef();

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CShadowMapShader::ReleaseObjects()
{
	if (m_pDepthFromLightTexture) m_pDepthFromLightTexture->Release();
}

void CShadowMapShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);

	UpdateShaderVariables(pd3dCommandList);

	for (int i = 0; i < m_pObjectsShader->m_nObjects; i++)
	{
		if (m_pObjectsShader->m_ppObjects[i])
		{
			m_pObjectsShader->m_ppObjects[i]->UpdateShaderVariables(pd3dCommandList);
			m_pObjectsShader->m_ppObjects[i]->Render(pd3dCommandList, pCamera);
		}
	}
	m_pObjectsShader->m_pDirectionalLight->UpdateShaderVariables(pd3dCommandList);
	m_pObjectsShader->m_pDirectionalLight->Render(pd3dCommandList, pCamera);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CTextureToViewportShader::CTextureToViewportShader()
{
}

CTextureToViewportShader::~CTextureToViewportShader()
{
}

D3D12_DEPTH_STENCIL_DESC CTextureToViewportShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = FALSE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;

	return(d3dDepthStencilDesc);
}

D3D12_SHADER_BYTECODE CTextureToViewportShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSTextureToViewport", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CTextureToViewportShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSTextureToViewport", "ps_5_1", ppd3dShaderBlob));
}

void CTextureToViewportShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	if (m_pDepthFromLightTexture) m_pDepthFromLightTexture->UpdateShaderVariables(pd3dCommandList);
}

void CTextureToViewportShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, void* pContext)
{
	m_pDepthFromLightTexture = (CTexture*)pContext;
	m_pDepthFromLightTexture->AddRef();

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CTextureToViewportShader::ReleaseObjects()
{
	if (m_pDepthFromLightTexture) m_pDepthFromLightTexture->Release();
}

void CTextureToViewportShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	D3D12_VIEWPORT d3dViewport = { 0.0f, 0.0f, FRAME_BUFFER_WIDTH * 0.25f, FRAME_BUFFER_HEIGHT * 0.25f, 0.0f, 1.0f };
	D3D12_RECT d3dScissorRect = { 0, 0, FRAME_BUFFER_WIDTH / 4, FRAME_BUFFER_HEIGHT / 4 };
	pd3dCommandList->RSSetViewports(1, &d3dViewport);
	pd3dCommandList->RSSetScissorRects(1, &d3dScissorRect);

	CShader::Render(pd3dCommandList, pCamera);

	UpdateShaderVariables(pd3dCommandList);

	pd3dCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pd3dCommandList->DrawInstanced(6, 1, 0, 0);
}
