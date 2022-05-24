#include <iostream>
#include <fstream>
#include <random>
#include <cassert>
#include "Block.h"
#include "SortableBlock.h"
#include "BlockStream.h"
#include "LoserTree.h"


// ��������
const int MEMORY_MAX = 1024 * 1024; // �ڴ�����Ϊ1MB
const int N = 1000000; // ������һ������

const int K = 20; // �鲢�θ���
const int N_EACH = MEMORY_MAX / (K + 1) / sizeof(Record); // ÿ�μ�¼��������ÿ���鲢�εĴ�С

const std::string SRC_FILENAME = "data.in"; // ԭ�����ļ���
const std::string TAR_FILENAME = "data.out"; // ����������ļ���
const std::string TMP_PREFIX = "tmp"; // ��ʱ�ļ���ǰ׺�����Ժ���+%d����ʽ������ʱ�ļ�

/// <summary>
/// ���������¼����
/// </summary>
/// <param name="filename">����ļ���</param>
/// <param name="n">��¼����</param>
void generateRandomData()
{
    std::ofstream fout(SRC_FILENAME, std::fstream::out | std::fstream::binary);

    for (size_t i = 0; i < N; i++)
    {
        // �����������ֵ
        int key = rand() % N;
        fout.write((char*)&key, 4);

        // �������ݶ�
        char data[13] = "Hello world!";
        fout.write(data, 12); // ���ݶι�12byte
    }

    std::cout << "Generated " << N << " records." << std::endl;
}

std::vector<std::string> firstSort()
{
    std::ifstream fin(SRC_FILENAME, std::fstream::in | std::fstream::binary); // ��ԭʼ�ļ�

    int load_total = 0; // ������ļ�¼�������������
    std::vector<std::string> tmp_namelist; // ��ʱ�ļ�������������

    Block b{ N_EACH };
    SortableBlock sort_b{ b };
    for (int i = 0; i < K; i++) // �鲢��K���ļ���
    {
        std::string tmp_filename{ TMP_PREFIX + std::to_string(i) };
        tmp_namelist.emplace_back(tmp_filename);
        std::ofstream fout(tmp_filename, std::fstream::out | std::fstream::binary); // ����ʱ�ļ�

        int tmp_total = 0; // ��ǰ��ʱ�ļ�������ļ�¼����
        while (tmp_total < N / 20)
        {
            int cnt = sort_b.load(fin);
            if (cnt == 0)
                break;

            load_total += cnt;
            tmp_total += cnt;
            sort_b.sort();
            sort_b.dump(fout);
        }

        std::cout << "Temp file \"" << tmp_filename << "\" loaded " << tmp_total << " records." << std::endl;
    }

    std::cout << "First sort finished." << "(" << load_total << " records total)" << std::endl;
    return tmp_namelist;
}

void mergeSort(std::vector<std::string>& tmp_namelist)
{
    assert(tmp_namelist.size() == K);

    /* ׼������ */
    // ��K·�ļ�
    std::ifstream tmp_stream[K];
    for (size_t i = 0; i < K; i++)
        tmp_stream[i].open(tmp_namelist[i], std::fstream::in | std::fstream::binary);

    // װ��K����¼����
    std::allocator<Block> alloc; // �������ɻ����ڴ��
    Block* b_array = alloc.allocate(K);
    for (size_t i = 0; i < K; i++)
        alloc.construct(b_array + i, N_EACH);

    IterableBlock* sb_array[K]; // װ�λ����ڴ��
    for (size_t i = 0; i < K; i++)
        sb_array[i] = new BlockStream{ b_array[i], tmp_stream[i] };

    // ���������
    std::ofstream fout(TAR_FILENAME, std::fstream::out | std::fstream::binary);
    Block output_block{ N_EACH };
    size_t ob_cnt = 0; // �����ļ�¼����

    /* ��ʼ�鲢 */
    LoserTree ltree{ K, sb_array };
    while (!ltree.empty())
    {
        // ȡ����ǰ��¼�������������
        output_block.setCount(ob_cnt + 1);
        output_block[ob_cnt] = ltree.top();
        ob_cnt++;

        if (ob_cnt == N_EACH) // ����������������
        {
            output_block.dump(fout);
            ob_cnt = 0;
        }

        ltree.pop();
    }
    output_block.dump(fout); // ���������ʣ���¼���

    // �ر�K·�ļ�
    for (size_t i = 0; i < K; i++)
        tmp_stream[i].close();

    // �ر�����ļ�
    fout.close();
}

int main()
{
    // �����������
    generateRandomData();

    // ��һ������
    auto tmp_namelist = firstSort();

    // �ڶ�������
    mergeSort(tmp_namelist);

    return 0;
}
