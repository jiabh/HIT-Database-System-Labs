#pragma once

#include<string>

/// <summary>
/// һ����¼
/// </summary>
class Record
{
private:
    static const size_t data_len = 12; // �����ֶ��ֽ���

public:
    /// <summary>
    /// ����һ���¼�¼
    /// </summary>
    /// <param name="key">�����ֶ�</param>
    /// <param name="data">�����ֶΣ�12�ֽ��ַ�����</param>
    Record(const int key, const char data[data_len]);

    /// <summary>
    /// ��ȡ����ֵ
    /// </summary>
    /// <returns>������¼������ֵ</returns>
    int getKey() const;

    /// <summary>
    /// ��ȡ�����ֶζ�Ӧ���ַ�����ʾ
    /// </summary>
    /// <returns>�����ֶζ�Ӧ���ַ���</returns>
    std::string getStrData() const;

    Record& operator=(const Record& other);
    bool operator==(const Record& other) const;
    bool operator!=(const Record& other) const;
    bool operator<(const Record& other) const;
    bool operator<=(const Record& other) const;
    bool operator>(const Record& other) const;
    bool operator>=(const Record& other) const;

private:
    int m_key; // A����
    char m_data[12]; // B���ԣ�12�ֽ��ַ�����
};
