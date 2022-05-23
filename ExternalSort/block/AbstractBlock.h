#pragma once

#include "Serializable.h"
#include "Record.h"

class AbstractBlock :public Serializable
{
public:
    /// <summary>
    /// �����ж����¼�飬���ض��������
    /// </summary>
    /// <param name="stream">������</param>
    /// <returns>�����¼�ĸ���</returns>
    virtual int load(std::istream& stream) override = 0;

    /// <summary>
    /// ����ǰ��¼�����������
    /// </summary>
    /// <param name="stream">�����</param>
    /// <returns>����ɹ�����0��ʧ�ܷ���-1</returns>
    virtual int dump(std::ostream& stream) override = 0;

    /// <summary>
    /// ��ȡ���м�¼����
    /// </summary>
    /// <returns>��¼����</returns>
    virtual size_t count() = 0;

    /// <summary>
    /// ���ÿ�����Ч��¼����
    /// </summary>
    /// <returns>�ɹ�����0��ʧ�ܷ���-1</returns>
    virtual int setCount(size_t num) = 0;

    /// <summary>
    /// ��ȡ��Ŀ����ɼ�¼����
    /// </summary>
    /// <returns>�����ɼ�¼����</returns>
    virtual size_t size() = 0;

    /// <summary>
    /// ��ȡ����ָ��λ�õļ�¼
    /// </summary>
    /// <param name="i">ƫ����</param>
    /// <returns>���ڵ�i����¼</returns>
    virtual Record& operator[](int i) = 0;
};
