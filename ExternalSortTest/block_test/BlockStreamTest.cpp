#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>
#include "Block.h"
#include "BlockStream.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ExternalSortTest
{
    TEST_CLASS(BlockStreamTest)
    {
    public:
        TEST_METHOD(Stream) // �����ڴ���Ƿ�����������
        {
            // ��������
            std::string dumped = {
                1, 0, 0, 0,
                'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!',
                2, 0, 0, 0,
                'a', 'b', 'c', 'd', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                3, 0, 0, 0,
                'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0',
                4, 0, 0, 0,
                'a', 'b', 'c', 'd', 'e', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
            };
            std::istringstream input(dumped);

            // ��ʼ���ڴ����
            Block b = { 2 };
            BlockStream bs = { b, input };

            // ��ʼ����
            Assert::AreEqual(1, bs.top().getKey());
            bs.top();
            bs.pop();
            Assert::AreEqual(2, bs.top().getKey());
            bs.top();
            bs.pop(); // ��ʱӦ������һ���ڴ��

            Assert::IsFalse(bs.empty());
            Assert::AreEqual(3, bs.top().getKey());
            bs.top();
            bs.pop();
            Assert::AreEqual(4, bs.top().getKey());
            bs.top();
            bs.pop(); // ��ʱӦ�������

            Assert::IsTrue(bs.empty());
        }
    };
}
