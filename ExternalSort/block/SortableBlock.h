#pragma once
#include "BlockDecorator.h"

class SortableBlock :public BlockDecorator
{
public:
    SortableBlock(AbstractBlock& block);

    /// <summary>
    /// Ϊ���ڴ���еļ�¼����
    /// </summary>
    void sort();

private:
    void qsort(size_t begin, size_t end);
};
