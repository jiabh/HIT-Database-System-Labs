#pragma once

#include "AbstractBlock.h"
#include "Record.h"

/// <summary>
/// ��¼�飬��Ӧһ���ڴ��
/// </summary>
class Block :public AbstractBlock
{
public:
    /// <summary>
    /// ����һ����¼��
    /// </summary>
    /// <param name="size">���еļ�¼����</param>
    Block(const size_t size);

    ~Block();

    /// <summary>
    /// �����ж����¼�飬���ض��������
    /// </summary>
    /// <param name="stream">������</param>
    /// <returns>�����¼�ĸ���</returns>
    virtual int load(std::istream& stream) override;

    /// <summary>
    /// ����ǰ��¼�����������
    /// </summary>
    /// <param name="stream">�����</param>
    /// <returns>����ɹ�����0��ʧ�ܷ���-1</returns>
    virtual int dump(std::ostream& stream) override;

    virtual size_t count() override;

    virtual int setCount(size_t num) override;

    virtual size_t size() override;

    virtual Record& operator[](int i) override;
    
private:
    size_t m_cnt; // ���м�¼����
    const size_t m_size; // ���ܴ�С
    Record* m_record_array; // ���и�����¼
};

