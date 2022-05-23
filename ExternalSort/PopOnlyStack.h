#pragma once

#include "Record.h"

/// <summary>
/// ����push��ջ
/// </summary>
/// <typeparam name="T">ջ��Ԫ������</typeparam>
template <class T>
class PopOnlyStack
{
public:
    /// <summary>
    /// ��ջ������һ��Ԫ��
    /// </summary>
    /// <returns>ջ��Ԫ��</returns>
    virtual T top() = 0;

    /// <summary>
    /// ����ջ��Ԫ��
    /// </summary>
    virtual void pop() = 0;

    /// <summary>
    /// �鿴ջ�Ƿ�Ϊ��
    /// </summary>
    /// <returns>ջ�Ƿ�Ϊ��</returns>
    virtual bool empty() = 0;
};
