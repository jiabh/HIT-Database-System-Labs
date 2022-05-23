#pragma once

#include "PopOnlyStack.h"
#include "BlockDecorator.h"

class IterableBlock
    :public BlockDecorator, PopOnlyStack<Record>
{
public:
    IterableBlock(AbstractBlock& block);

    virtual Record top() override;
    virtual void pop() override;
    virtual bool empty() override;

    /// <summary>
    /// ��ȡ����ʣ���¼����
    /// </summary>
    /// <returns>ʣ���¼����</returns>
    virtual size_t count() override;

protected:
    size_t m_top_index; // ջ��ָ��
};
