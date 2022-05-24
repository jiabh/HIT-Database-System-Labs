#pragma once

#include "PopOnlyStack.h"
#include "Record.h"
#include "IterableBlock.h"

class LoserTree :public PopOnlyStack<Record>
{
public:
    /// <summary>
    /// ����һ�ð�����
    /// </summary>
    /// <param name="k">�鲢����</param>
    /// <param name="ib_array">���鲢����ɵ�����</param>
    LoserTree(int k, IterableBlock* ib_array[]);

    ~LoserTree();

    virtual Record top() override;
    virtual void pop() override;
    virtual bool empty() override;

private:
    /// <summary>
    /// ����������
    /// </summary>
    void build();

    /// <summary>
    /// ��ָ���鲢�ο�ʼ����������
    /// </summary>
    /// <param name="b_index">��ʼ�鲢��</param>
    void adjust(int b_index);

    static inline int father(int index);

private:
    /// <summary>
    /// �鲢����
    /// </summary>
    const int m_k;

    /// <summary>
    /// ������,[0]���ʤ�߹鲢�Σ������Ű��߹鲢��
    /// -1��ʾ����ʤ�ߣ�m_k��ʾ���԰���
    /// </summary>
    int* m_tree;

    /// <summary>
    /// ���鲢��
    /// </summary>
    IterableBlock** m_ib_array;

    /// <summary>
    /// ����Ӯ�Ĺ鲢��
    /// </summary>
    const int m_WIN;
};

