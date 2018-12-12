
#include "Mesh.h"


class __CSEMeshFactory : public ISEMeshFactory
{
public:
	__CSEMeshFactory()
	{
	}

	virtual ~__CSEMeshFactory()
	{
	}

public:
	virtual ISEMesh* CreateMesh()
	{
		return _CSEMesh::Cache().Cache()->Init();
	}

public:
	_SE_SINGLETON_DECL(ISEMeshFactory, __CSEMeshFactory, SE_TEXT("ISEMeshFactory"))

private:
};


_SE_SINGLETON_IMPL(ISEMeshFactory, __CSEMeshFactory)


__CSEMeshFactory* __CSEMeshFactory::Init()
{
	return this;
}

SEVoid __CSEMeshFactory::Reinit()
{
	// ������������ʹ�õĶ���
	_CSEMesh::Cache().Free();
}

SEVoid __CSEMeshFactory::Reset()
{
}

SEVoid __CSEMeshFactory::Config(SEVoid(*Set)(SECString, ...))
{
}

SEVoid __CSEMeshFactory::Config(SECString* pEntries, SEUInt nCount)
{
}
