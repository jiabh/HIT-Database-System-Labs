#include <cstring>
#include "LoserTree.h"

LoserTree::LoserTree(int k, IterableBlock* ib_array[])
    :m_k(k), m_WIN(-1)
{
    m_ib_array = new IterableBlock * [k];
    memcpy(m_ib_array, ib_array, k * sizeof(IterableBlock*));

    m_tree = new int[m_k + 1];

    this->build();
}

LoserTree::~LoserTree()
{
    delete[] m_ib_array;
    delete[] m_tree;
}

Record LoserTree::top()
{
    IterableBlock* b = m_ib_array[m_tree[0]]; // ����Ԫ�����ڹ鲢��
    return b->top();
}

void LoserTree::pop()
{
    int popping = m_tree[0]; // �������Ĺ鲢���±�
    m_ib_array[popping]->pop();
    this->adjust(popping);
}

bool LoserTree::empty()
{
    // �������ڴ�鶼�գ���˵��������
    bool all_empty = true;
    for (size_t i = 0; i < m_k; i++)
        all_empty &= m_ib_array[i]->empty();
    return all_empty;
}

void LoserTree::build()
{
    // �����нڵ��ʼ��Ϊ����ʤ��
    for (int i = 1; i < m_k; i++)
        m_tree[i] = -1;

    // ����ÿ���鲢��
    for (int i = 0; i < m_k; i++)
        this->adjust(i);

    // ��ʱ����Ϊ��һ��ʤ��
    // ԭ��Ϊ����ʱ[1]��ʤ�߲���[0]���Ƚϣ�ֱ�Ӹ���
}

void LoserTree::adjust(int b_index)
{
    // ��ʼΪ�������鲢�εĸ��ڵ��±�
    // ʼ��ָ��ǰ�ڵ��������
    int t = (b_index + m_k) / 2;

    // ������ֱ�����ڵ�
    while (t > 0) {
        // ÿ��ѭ����ʼ��b_indexָ��ǰ����ս�Ľڵ�

        // �ж��Ƿ��Ӯ
        bool winned = b_index == m_WIN; // ������Ϊ����Ӯ�����Ӯ
        if (m_tree[t] != m_WIN)
            winned |= m_ib_array[m_tree[t]]->empty(); // ������Ϊ�����Ӯ

        // �ж��Ƿ����
        bool losed = m_tree[t] == m_WIN; // ������Ϊ����Ӯ�������
        if (b_index != m_WIN)
            losed |= m_ib_array[b_index]->empty(); // ���ñȽϣ��Ѿ�����

        if (!winned)
        {
            if (losed)
            {
                std::swap(m_tree[t], b_index);
            }
            else
            {
                const Record& curr = m_ib_array[b_index]->top();
                const Record& father = m_ib_array[m_tree[t]]->top();
                if (curr >= father) // ��ǰ�ڵ����ˣ�����ԭ�أ�t����������b_index
                {
                    std::swap(m_tree[t], b_index);
                }
            }
        }

        t /= 2; // ָ����һ�ڵ㣬�����Ƚ�
    }
    m_tree[0] = b_index; // ����ʤ��
}

inline int LoserTree::father(int index)
{
    return index / 2;
}
