#include "BlockStream.h"

BlockStream::BlockStream(AbstractBlock& block, std::istream& in)
    :IterableBlock(block), m_in(in)
{
    m_block.load(m_in); // �����һ���ڴ��
}

void BlockStream::pop()
{
    m_top_index++; // ����ջ��
    
    // ����ǰ�ڴ�������
    if (this->empty())
    {
        m_block.load(m_in); // ������һ���ڴ��
        m_top_index = 0; // ����ջ״̬
    }
}
