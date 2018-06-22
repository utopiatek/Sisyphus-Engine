
#include "Stdafx.h"


#ifdef SE_TEST


#define __SE_TEST_CASE(NAME, TITLE, DESC) \
class __TEST_CASE_##NAME : public ISETestCase \
{ \
public: \
__TEST_CASE_##NAME() { ISECore::Entity()->Awake(this); } \
virtual SECString Title() { return TITLE; } \
virtual SECString Desc() { return DESC; } \
virtual SEBool Run(); \
}; \
__TEST_CASE_##NAME __TEST_CASE_##NAME##_INSTANCE = __TEST_CASE_##NAME(); \
SEBool __TEST_CASE_##NAME::Run()


__SE_TEST_CASE(LOG, "ISELog", "Log system test")
{
	srand((unsigned)time(nullptr));

	int nIndex = rand() % 5;

	switch (nIndex)
	{
	case 0:
		SE_PRINTF("Log system test %s.", SE_TEXT("succeed"));
		break;
	case 1:
		SE_INFO("Log system test succeed.");
		break;
	case 2:
		SE_INFO("Log system test succeed.", SE_TEXT("%s."), SE_TEXT("Log system test extra succeed"));
		break;
	case 3:
		SE_WARN("Log system test succeed.");
		break;
	case 4:
		SE_WARN("Log system test succeed.", SE_TEXT("%s."), SE_TEXT("Log system test extra succeed"));
		break;
	default:
		break;
	}

	return SETrue;
}


#include "../Inc/Templ/RBTree.h"

__SE_TEST_CASE(RBTREE, "TSERBTree", "Red black tree test")
{
	struct TEST_NODE
	{
		TEST_NODE()
		{
			memset(this, 0, sizeof(TEST_NODE));
		}

		SEUInt Size() { return m_nSize; }

		SEUInt Color() { return m_nColor; }

		SEVoid SetColor(SEUInt nColor) { m_nColor = nColor; }

		SEUInt Slot() { return m_nSlot; }

		SEVoid SetSlot(SEUInt nSlot) { m_nSlot = nSlot; }

		TEST_NODE* Parent() { return m_pParent; }

		SEVoid SetParent(TEST_NODE* pParent) { m_pParent = pParent; }

		TEST_NODE* Child(SEUInt nIndex) { return m_aSubTree[nIndex]; }

		SEVoid SetChild(SEUInt nIndex, TEST_NODE* pChild) { m_aSubTree[nIndex] = pChild; }


		SEUInt m_nColor : 1;

		SEUInt m_nSlot : 1;

		SEUInt m_nSize : 30;

		TEST_NODE* m_pParent;

		TEST_NODE* m_aSubTree[2];
	};

	TSERBTree<TEST_NODE> mTree;
	TSEVector<TEST_NODE*> mVector;

	srand((unsigned)time(nullptr));

	for (SEUInt i = 0; i < 256; i++)
	{
		SEUInt nSize = rand() % 1024;
		TEST_NODE* pNode = nullptr;

		if (rand() % 2)
		{
			pNode = new TEST_NODE();
			pNode->m_nSize = nSize;
			mTree.Insert(pNode);
			mVector.push_back(pNode);
		}
		else
		{
			pNode = mTree.Find(nSize);
			if (nullptr != pNode)
			{
				for (TSEVector<TEST_NODE*>::iterator iter = mVector.begin(); iter != mVector.end(); iter++)
				{
					if (*iter == pNode)
					{
						mVector.erase(iter);
						delete pNode;
						break;
					}
				}
			}
		}
	}

	SEError nError = mTree.Check();
	if (nError)
	{
		SE_ERROR(0, "Red black tree test error!", SE_TEXT("Error: %d, Size: %d, ByteSize: %d, Depth: %d!"), nError, mTree.m_nSize, mTree.m_nBytes, mTree.m_nDepth);

		return SEFalse;
	}

	for (TSEVector<TEST_NODE*>::iterator iter = mVector.begin(); iter != mVector.end(); iter++)
	{
		TEST_NODE* pNode = *iter;

		mTree.Delete(pNode);

		delete pNode;
	}

	nError = mTree.Check();
	if (mTree.Check() || mTree.m_nSize != 0)
	{
		SE_ERROR(0, "Red black tree test error!", SE_TEXT("Error: %d, Size: %d, ByteSize: %d, Depth: %d!"), nError, mTree.m_nSize, mTree.m_nBytes, mTree.m_nDepth);

		return SEFalse;
	}

	SE_INFO("Red black tree test succeed.");

	return SETrue;
}


__SE_TEST_CASE(MEMORY, "ISEMemory", "Memory test")
{
	ISEMemory* pMemoryPool = ISEMemory::Get();

#if defined(SE_EMSCRIPTEN_ASM) || defined(SE_EMSCRIPTEN_WASM)
	return SEFalse;
#endif

	{
		TSEVector<SEVoid*> mVector;

		srand((unsigned)time(nullptr));

		for (SEInt i = 0; i < 10000; i++)
		{
			SEUInt nSize = rand() % 1000000 + 10;
			SEVoid* pMemory = pMemoryPool->Malloc(nSize);

			mVector.push_back(pMemory);

			if (rand() % 2)
			{
				SEInt nIndex = rand() % mVector.size();

				pMemory = mVector.at(nIndex);
				mVector.erase(mVector.begin() + nIndex);
				pMemoryPool->Free(pMemory);
			}
		}

		if (pMemoryPool->Analyse())
		{
			return SEFalse;
		}

		for (SEUInt i = 0; i < mVector.size(); i++)
		{
			SEVoid* pMemory = mVector.at(i);
			pMemoryPool->Free(pMemory);
		}
	}

	if (pMemoryPool->Analyse())
	{
		return SEFalse;
	}

	SE_INFO("Memory pool test succeed.");

	return SETrue;
}


#endif // SE_TEST
