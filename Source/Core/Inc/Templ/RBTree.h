
#ifndef SE_CORE_TEMPL_RB_TREE
#define SE_CORE_TEMPL_RB_TREE


#include "../Utility.h"


template <typename NODE>
class TSERBTree
{
public:
	/// <summary>
	/// 构造函数，置零。
	/// </summary>
	TSERBTree()
		:m_pRoot(nullptr), m_nSize(0), m_nDepth(0), m_nBytes(0)
	{
	}

	/// <summary>
	/// 析构函数，置零。
	/// </summary>
	~TSERBTree()
	{
		m_pRoot = nullptr;
		m_nSize = 0;
		m_nDepth = 0;
		m_nBytes = 0;
	}

	/// <summary>
	/// 重置红黑树状态。
	/// </summary>
	SEVoid Reset()
	{
		m_pRoot = nullptr;
		m_nSize = 0;
		m_nBytes = 0;
		m_nDepth = 0;
	}

	/// <summary>
	/// 节点插入方法，应该在插入前对节点进行初始化。
	/// </summary>
	SEVoid Insert(NODE* pNode)
	{
		// 增加计数
		m_nSize++;
		m_nBytes += pNode->Size();

		// 在树不为空的情况下，在叶子节点处完成插入
		NODE* pTree = m_pRoot;
		while (nullptr != pTree)
		{
			SEUInt nSlot = pNode->Size() > pTree->Size();
			NODE* pSubTree = pTree->Child(nSlot);

			if (nullptr == pSubTree)
			{
				pNode->SetSlot(nSlot);
				pTree->SetChild(nSlot, pNode);
				pNode->SetParent(pTree);
			}

			pTree = pSubTree;
		}

		// 重建红黑树的平衡，如果其父节点为空，将节点置为树根
		InsertBalance(pNode);
	}

	/// <summary>
	/// 删除节点，删除时未对节点进行初始化。
	/// </summary>
	SEVoid Delete(NODE* pNode)
	{
		// 减少计数
		m_nSize--;
		m_nBytes -= pNode->Size();

		// 将被删除的节点
		NODE* pDelNode = nullptr;

		// 可能的单支子树所在端口
		SEUInt nSubTreeSlot = 1;

		// 无右子树，如果有左子树，直接替换成左子树，删除，如果也不存在左子树，直接删除
		if (nullptr == pNode->Child(1))
		{
			pDelNode = pNode;
			nSubTreeSlot = 0;
		}
		// 有右子树，在右子树中寻找最小替换节点，删除替换节点(必定无左子树)
		else
		{
			pDelNode = pNode->Child(1);
			while (nullptr != pDelNode->Child(0))
			{
				pDelNode = pDelNode->Child(0);
			}

			// 交换节点颜色，端口，父子关系，大小保持
			NODE mTemp;
			mTemp.SetColor(pNode->Color());
			mTemp.SetSlot(pNode->Slot());
			mTemp.SetParent(pNode->Parent());
			mTemp.SetChild(0, pNode->Child(0));
			mTemp.SetChild(1, pNode->Child(1));

			pNode->SetColor(pDelNode->Color());
			pNode->SetSlot(pDelNode->Slot());
			pNode->SetParent(pDelNode->Parent() == pNode ? pDelNode : pDelNode->Parent());
			pNode->SetChild(0, pDelNode->Child(0));
			pNode->SetChild(1, pDelNode->Child(1));

			pNode->Parent()->SetChild(pNode->Slot(), pNode);
			if (nullptr != pNode->Child(0)) pNode->Child(0)->SetParent(pNode);
			if (nullptr != pNode->Child(1)) pNode->Child(1)->SetParent(pNode);

			pDelNode->SetColor(mTemp.Color());
			pDelNode->SetSlot(mTemp.Slot());
			pDelNode->SetParent(mTemp.Parent());
			pDelNode->SetChild(0, mTemp.Child(0));
			pDelNode->SetChild(1, mTemp.Child(1) == pDelNode ? pNode : mTemp.Child(1));

			if (nullptr != pDelNode->Parent()) pDelNode->Parent()->SetChild(pDelNode->Slot(), pDelNode);
			if (nullptr != pDelNode->Child(0)) pDelNode->Child(0)->SetParent(pDelNode);
			if (nullptr != pDelNode->Child(1)) pDelNode->Child(1)->SetParent(pDelNode);

			if (nullptr == pDelNode->Parent())
			{
				m_pRoot = pDelNode;
			}

			pDelNode = pNode;
		}

		// 删除带一个子树或无子树的节点
		{
			NODE* pSubTree = pDelNode->Child(nSubTreeSlot);
			NODE* pParent = pDelNode->Parent();

			// 当前红黑树只有该一个节点，直接删除
			if (nullptr == pParent && nullptr == pSubTree)
			{
				m_pRoot = nullptr;
				return;
			}

			// 删除根，根带单支子树，将子节点作为新根并设为黑
			if (nullptr == pParent)
			{
				m_pRoot = pSubTree;
				m_pRoot->SetParent(nullptr);
				m_pRoot->SetSlot(0);
				m_pRoot->SetColor(1);
				return;
			}

			// 红-NULL：删除节点为红色，无子节点直接删除
			if (0 == pDelNode->Color())
			{
				pParent->SetChild(pDelNode->Slot(), nullptr);
			}
			// 删除节点为黑色，子节点可能为空
			else
			{
				// 黑—红
				if (nullptr != pSubTree)
				{
					pSubTree->SetColor(1);
					pSubTree->SetSlot(pDelNode->Slot());
					pSubTree->SetParent(pParent);
					pParent->SetChild(pDelNode->Slot(), pSubTree);
				}
				// 黑-NULL
				else
				{
					DeleteBalance(pDelNode);
					pParent->SetChild(pDelNode->Slot(), nullptr);
				}
			}
		}
	}

	/// <summary>
	/// 查找并移除一个合适的大小符合要求的节点，参数大小以16字节为单位。
	/// </summary>
	NODE* Find(SEUInt nSize)
	{
		NODE* pNode = m_pRoot;
		while (nullptr != pNode)
		{
			if (pNode->Size() >= nSize)
			{
				NODE* pLeft = pNode->Child(0);
				if (nullptr == pLeft || pLeft->Size() < nSize)
				{
					Delete(pNode);
					break;
				}

				pNode = pLeft;
			}
			else
			{
				pNode = pNode->Child(1);
			}
		}

		return pNode;
	}

	/// <summary>
	/// 检查红黑树运行状态。
	/// </summary>
	SEError Check()
	{
		SEError nError = 0;
		SEUInt nCount = 0;

		m_nDepth = 0;

		if (nullptr == m_pRoot)
			return nError;

		if (!Check(m_pRoot, nCount, m_nDepth))
		{
			nError |= 0x1;
			return nError;
		}

		if (nCount != m_nSize)
		{
			nError |= 0x2;
			return nError;
		}

		return nError;
	}

protected:
	/// <summary>
	/// 插入节点，重新构建平衡。
	/// </summary>
	SEVoid InsertBalance(NODE* pNode)
	{
		NODE* pParent = pNode->Parent();

		// 情形1，插入根节点，设置成黑色
		if (nullptr == pParent)
		{
			m_pRoot = pNode;
			pNode->SetColor(1);

			return;
		}
		// 以下情形中，父节点为红色，存在祖父节点，黑色
		if (0 == pParent->Color())
		{
			NODE* pGrandpa = pParent->Parent();
			NODE* pUncle = pGrandpa->Child(1 - pParent->Slot());

			// 情形3，叔父节点也为红色，设置父节点和叔父节点成黑色，并将祖父节点设为红色
			// 注：如果祖父为根，变换为黑色无影响，如果祖父的父节点为黑，无影响
			// 如果祖父的父节点为红，照这个情形递归处理
			if (nullptr != pUncle && 0 == pUncle->Color())
			{
				pParent->SetColor(1);
				pUncle->SetColor(1);
				pGrandpa->SetColor(0);

				// 将祖父视为需要平衡的新插入节
				InsertBalance(pGrandpa);
			}
			// 父节点红色，叔父节点空或者黑色
			else
			{
				// 情形4，新节点在右端口，父节点在左端口，以新节点作为转轴左旋转，按情形5处理父节点
				if (1 == pNode->Slot() && 0 == pParent->Slot())
				{
					RotateLeft(pNode);
					{
						RotateRight(pNode);
						pNode->SetColor(1);
						pNode->Child(0)->SetColor(0);
						pNode->Child(1)->SetColor(0);
					}
				}
				// 情形4，新节点在左端口，父节点在右端口，以新节点作为转轴右旋转，按情形5处理父节点
				else if (0 == pNode->Slot() && 1 == pParent->Slot())
				{
					RotateRight(pNode);
					{
						RotateLeft(pNode);
						pNode->SetColor(1);
						pNode->Child(0)->SetColor(0);
						pNode->Child(1)->SetColor(0);
					}
				}
				// 情形5，新节点在左端口，父节点也在左端口，以新节点的父节点作为转轴右旋转
				else if (0 == pNode->Slot() && 0 == pParent->Slot())
				{
					pParent->SetColor(1);
					pGrandpa->SetColor(0);
					RotateRight(pParent);
				}
				// 情形5，新节点在右端口，父节点也在右端口，以新节点的父节点作为转轴左旋转
				else if (1 == pNode->Slot() && 1 == pParent->Slot())
				{
					pParent->SetColor(1);
					pGrandpa->SetColor(0);
					RotateLeft(pParent);
				}
			}
		}
	}

	/// <summary>
	/// 删除节点，重新构建平衡。
	/// </summary>
	SEVoid DeleteBalance(NODE* pNode)
	{
		NODE* pParent = pNode->Parent();

		// 情形1：顶替点将作为新的根，置颜色为黑，完成
		if (nullptr == pParent)
		{
			pNode->SetColor(1);
			pNode->SetSlot(0);

			return;
		}

		NODE* pSibling = pParent->Child(1 - pNode->Slot());

		// 情形2：S为红，P必为黑
		if (0 == pSibling->Color())
		{
			pParent->SetColor(0);
			pSibling->SetColor(1);

			if (0 == pNode->Slot())
			{
				RotateLeft(pSibling);
			}
			else
			{
				RotateRight(pSibling);
			}

			pParent = pNode->Parent();
			pSibling = pParent->Child(1 - pNode->Slot());
		}

		NODE* pSL = pSibling->Child(0);
		NODE* pSR = pSibling->Child(1);

		// 情形3：P、S、S子全黑
		if (1 == pParent->Color() && 1 == pSibling->Color() && (nullptr == pSL || 1 == pSL->Color()) && (nullptr == pSR || 1 == pSR->Color()))
		{
			pSibling->SetColor(0);
			DeleteBalance(pParent);
		}
		// 情形4：P红，S、S子全黑
		else if (0 == pParent->Color() && 1 == pSibling->Color() && (nullptr == pSL || 1 == pSL->Color()) && (nullptr == pSR || 1 == pSR->Color()))
		{
			pSibling->SetColor(0);
			pParent->SetColor(1);
		}
		// 其它情形，P颜色不论，S黑，S子不全黑
		else
		{
			// 情形5：S左/右子红，S的右/左子黑
			if (1 == pSibling->Color())
			{
				if (0 == pNode->Slot() && (nullptr != pSL && 0 == pSL->Color()) && (nullptr == pSR || 1 == pSR->Color()))
				{
					pSibling->SetColor(0);
					pSL->SetColor(1);
					RotateRight(pSL);
				}
				else if (1 == pNode->Slot() && (nullptr != pSR && 0 == pSR->Color()) && (nullptr == pSL || 1 == pSL->Color()))
				{
					pSibling->SetColor(0);
					pSR->SetColor(1);
					RotateLeft(pSR);
				}
			}

			// 情形6：P颜色不论，S黑，S右/左子红，S的左/右颜色不论
			pSibling = pParent->Child(1 - pNode->Slot());
			pSL = pSibling->Child(0);
			pSR = pSibling->Child(1);

			pSibling->SetColor(pParent->Color());
			pParent->SetColor(1);

			if (0 == pNode->Slot())
			{
				pSR->SetColor(1);
				RotateLeft(pSibling);
			}
			else
			{
				pSL->SetColor(1);
				RotateRight(pSibling);
			}
		}
	}

	/// <summary>
	/// 子树的左旋转，转轴为旋转后成为父节点的节点。
	/// </summary>
	SEVoid RotateLeft(NODE* pPivot)
	{
		NODE* pParent = pPivot->Parent();

		// 转轴为根节点，直接返回
		if (nullptr == pParent)
		{
			pPivot->SetSlot(0);
			m_pRoot = pPivot;
			return;
		}

		SEUInt nPivotSlot = pParent->Slot();
		NODE* pGrandpa = pParent->Parent();
		NODE* pLeftTree = pPivot->Child(0);

		// 转轴的左子作为父节点的右子，父节点左子不变
		pParent->SetChild(1, pLeftTree);
		if (nullptr != pLeftTree)
		{
			pLeftTree->SetSlot(1);
			pLeftTree->SetParent(pParent);
		}

		// 转轴的左子转变为父节点，转轴右子不变
		pPivot->SetChild(0, pParent);
		pParent->SetSlot(0);
		pParent->SetParent(pPivot);

		// 转换后，转轴的新父节点为祖父节点
		pPivot->SetParent(pGrandpa);

		// 转轴原先父节点为根，转换后转轴为根
		if (nullptr == pGrandpa)
		{
			pPivot->SetSlot(0);
			m_pRoot = pPivot;
		}
		// 转换后，祖父节点的新子节点为转轴
		else
		{
			pGrandpa->SetChild(nPivotSlot, pPivot);
			pPivot->SetSlot(nPivotSlot);
		}
	}

	/// <summary>
	/// 子树的右旋转，转轴为旋转后成为父节点的节点。
	/// </summary>
	SEVoid RotateRight(NODE* pPivot)
	{
		NODE* pParent = pPivot->Parent();

		// 转轴为根节点，直接返回
		if (nullptr == pParent)
		{
			pPivot->SetSlot(0);
			m_pRoot = pPivot;
			return;
		}

		SEUInt nPivotSlot = pParent->Slot();
		NODE* pGrandpa = pParent->Parent();
		NODE* pRightTree = pPivot->Child(1);

		// 转轴的右子作为父节点的左子，父节点右子不变
		pParent->SetChild(0, pRightTree);
		if (nullptr != pRightTree)
		{
			pRightTree->SetSlot(0);
			pRightTree->SetParent(pParent);
		}

		// 转轴的右子转变为父节点，转轴左子不变
		pPivot->SetChild(1, pParent);
		pParent->SetSlot(1);
		pParent->SetParent(pPivot);

		// 转换后，转轴的新父节点为祖父节点
		pPivot->SetParent(pGrandpa);

		// 转轴原先父节点为根，转换后转轴为根
		if (nullptr == pGrandpa)
		{
			pPivot->SetSlot(0);
			m_pRoot = pPivot;
		}
		// 转换后，祖父节点的新子节点为转轴
		else
		{
			pGrandpa->SetChild(nPivotSlot, pPivot);
			pPivot->SetSlot(nPivotSlot);
		}
	}

	/// <summary>
	/// 检验红黑树当前是否正确。
	/// </summary>
	SEBool Check(NODE* pNode, SEUInt& nCount, SEUInt nDepth)
	{
		if (pNode == nullptr)
		{
			if (m_nDepth == 0) m_nDepth = nDepth;
			if (m_nDepth != nDepth) return SEFalse;

			return SETrue;
		}

		if (1 == pNode->Color())
		{
			nDepth++;
		}

		if (!Check(pNode->Child(0), nCount, nDepth)) return SEFalse;

		nCount++;

		if (!Check(pNode->Child(1), nCount, nDepth)) return SEFalse;

		return SETrue;
	}

public:
	/// <summary>
	/// 红黑树根节点。
	/// </summary>
	NODE* m_pRoot;

	/// <summary>
	/// 红黑树节点数量。
	/// </summary>
	SEUInt m_nSize;

	/// <summary>
	/// 红黑树深度。
	/// </summary>
	SEUInt m_nDepth;

	/// <summary>
	/// 红黑树节点总字节大小，以16字节对齐。
	/// </summary>
	SEULong m_nBytes;
};


#endif // !SE_CORE_TEMPL_RB_TREE
