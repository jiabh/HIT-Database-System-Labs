#include "pch.h"
#include "CppUnitTest.h"

#include <vector>
#include "Block.h"
#include "SortableBlock.h"
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ExternalSortTest
{
    TEST_CLASS(SortableBlockTest)
    {
    public:
        TEST_METHOD(Sort)
        {
            const size_t r_cnt = 10; // �ڴ���ڼ�¼��
            std::string data = "Hello"; // ÿ����¼��data�ֶξ�Ϊ��ֵ

            Block b = { r_cnt };
            SortableBlock sb = { b };

            // ����������ݲ���ӵ�Block��
            std::vector<int> key_vec = generateShuffleKey(r_cnt);
            sb.setCount(r_cnt);
            for (size_t i = 0; i < r_cnt; i++)
                sb[i] = { key_vec[i], data.c_str() };

            // ���򲢼��
            sb.sort();
            for (size_t i = 0; i < sb.count() - 1; i++)
                Assert::IsTrue(sb[i] <= sb[i + 1]);
        }
    private:
        std::vector<int> generateShuffleKey(int num)
        {
            std::vector<int> res{num};

            // ��ʼ��key
            for (int i = 1; i <= num; i++)
                res.emplace_back(i);
            
            // ����˳��
            std::random_device rd;
            std::default_random_engine rng(rd());
            shuffle(res.begin(), res.end(), rng);

            return res;
        }
    };
}
