#include "pch.h"
#include "CppUnitTest.h"

#include <memory>
#include <sstream>
#include <ctime>
#include "Record.h"
#include "Block.h"
#include "IterableBlock.h"
#include "LoserTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ExternalSortTest
{
    TEST_CLASS(LoserTreeTest)
    {
    public:
        TEST_METHOD(Main)
        {
            srand((int)time(NULL));

            const int K = 5; // �鲢����
            const int N = 100; // ��¼�ܸ���
            std::string data = "Hello world!";

            // �����ڴ������
            std::allocator<Block> a1;
            Block* b_array = a1.allocate(K);
            for (size_t i = 0; i < K; i++)
                a1.construct(b_array + i, N);

            std::allocator<IterableBlock> a2;
            IterableBlock* ib_array = a2.allocate(K);
            for (size_t i = 0; i < K; i++)
                a2.construct(ib_array + i, b_array[i]);


            // ��ʼ�����ڴ���е�����
            // ÿ�����ѡ��һ���鲢�β����¼
            for (int key = 1; key <= N; key++)
            {
                Block& b = b_array[rand() % K]; // ���ѡ��һ���鲢��

                size_t cnt = b.count();
                b.setCount(cnt + 1);
                b[cnt] = { key, data.c_str() };
            }

            // �鲢������Ƿ���ȷ
            LoserTree ltree{ K, ib_array };
            int key_prev = 0;
            while (!ltree.empty())
            {
                int key_curr = ltree.top().getKey();
                Assert::AreEqual(key_prev + 1, key_curr);

                key_prev = key_curr;
                ltree.pop();
            }

            // �ͷŸ��ڴ��
            for (size_t i = 0; i < K; i++)
                a2.destroy(ib_array + i);
            a2.deallocate(ib_array, K);
            for (size_t i = 0; i < K; i++)
                a1.destroy(b_array + i);
            a1.deallocate(b_array, K);
        }
    };
}
