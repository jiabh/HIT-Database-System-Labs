#pragma once

#include <iostream>

class Serializable
{
public:
    /// <summary>
    /// ������������
    /// </summary>
    /// <param name="stream">������</param>
    virtual int load(std::istream& stream) = 0;

    /// <summary>
    /// �������������
    /// </summary>
    /// <param name="stream">�����</param>
    virtual int dump(std::ostream& stream) = 0;
};

