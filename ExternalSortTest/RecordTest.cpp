#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>
#include "../ExternalSort/Record.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ExternalSortTest
{
    TEST_CLASS(RecordTest)
    {
    public:
        TEST_METHOD(CreateAndGet)
        {
            const int key = 6;
            const std::string data = "Hello world!";

            auto r = Record(key, data.c_str());
            Assert::AreEqual(key, r.getKey());
            Assert::AreEqual(data, r.getStrData());
        }

        TEST_METHOD(Compare)
        {
            Record r1 = { 1, "abc" },
                r11 = { 1, "abcd" },
                r2 = { 2,"abc" };

            Assert::IsTrue(r1 == r11);
            Assert::IsTrue(r1 <= r11);
            Assert::IsTrue(r1 < r2);
            Assert::IsTrue(r1 <= r2);
            Assert::IsFalse(r1 > r2);
            Assert::IsFalse(r11 > r2);
            Assert::IsFalse(r1 >= r2);
        }

        TEST_METHOD(Assign)
        {
            Record r1 = { 1, "abc" },
                r2 = { 2, "abcd" };

            r2 = r1;
            Assert::AreEqual(r1.getKey(), r2.getKey());
            Assert::AreEqual(r1.getStrData(), r2.getStrData());
        }

        TEST_METHOD(Load)
        {
            Record r;

            // �������л�������
            std::string data = "Hello world!";
            std::string dumped = { 6, 0, 0 ,0 };
            dumped += data;

            // ���벢�ж��Ƿ���ȷ
            std::istringstream input(dumped);
            Assert::AreEqual(0, r.load(input));
            Assert::AreEqual(6, r.getKey());
            Assert::AreEqual(data, r.getStrData());
        }

        TEST_METHOD(Dump)
        {
            Record r = { 10, "hello" };

            std::ostringstream output; // dump���λ��
            Assert::AreEqual(0, r.dump(output));

            // ��λ�ж�key�ֶ��Ƿ�dump��ȷ
            Assert::AreEqual((char)10, output.str()[0]);
            Assert::AreEqual('\0', output.str()[1]);
            Assert::AreEqual('\0', output.str()[2]);
            Assert::AreEqual('\0', output.str()[3]);

            // ͨ���ַ����Ƚ��ж�data�ֶ��Ƿ���ȷ
            auto expect = r.getStrData();
            auto actual = output.str().substr(4);
            Assert::IsTrue(expect.compare(actual));
        }
    };
}
