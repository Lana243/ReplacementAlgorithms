#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cassert>
#include <random>
#include <rand.h>

#include "fifo.h"
#include "lru.h"
#include "opt.h"
#include "clock.h"

template<typename T>
class TestReplaceAlgorithm {
public:
    void run(int num_frames, const std::vector<int> &req_pages, int exp_num_page_errors) {
        assert(T(num_frames, req_pages).get_num_page_errors() == exp_num_page_errors);
    }
};

void testReplaceAlgorithm() {
    TestReplaceAlgorithm<OPT>().run(3, {1, 2, 3, 4, 2, 3, 1}, 5);
    TestReplaceAlgorithm<FIFO>().run(3, {1, 2, 3, 4, 2, 3, 1}, 5);
    TestReplaceAlgorithm<LRU>().run(3, {1, 2, 3, 4, 2, 3, 1}, 5);
    TestReplaceAlgorithm<CLOCK>().run(3, {1, 2, 3, 4, 2, 3, 1}, 5);

    TestReplaceAlgorithm<OPT>().run(3, {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}, 7);
    TestReplaceAlgorithm<FIFO>().run(3, {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}, 9);
    TestReplaceAlgorithm<LRU>().run(3, {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}, 10);
    TestReplaceAlgorithm<CLOCK>().run(3, {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}, 9);

    TestReplaceAlgorithm<OPT>().run(4, {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}, 6);
    TestReplaceAlgorithm<FIFO>().run(4, {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}, 10);
    TestReplaceAlgorithm<LRU>().run(4, {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}, 8);
    TestReplaceAlgorithm<CLOCK>().run(4, {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}, 10);

    TestReplaceAlgorithm<OPT>().run(5, {100000, 3000, 50000}, 3);
    TestReplaceAlgorithm<FIFO>().run(5, {100000, 3000, 50000}, 3);
    TestReplaceAlgorithm<LRU>().run(5, {100000, 3000, 50000}, 3);
    TestReplaceAlgorithm<CLOCK>().run(5, {100000, 3000, 50000}, 3);
    TestReplaceAlgorithm<RAND>().run(5, {100000, 3000, 50000}, 3);

    TestReplaceAlgorithm<OPT>().run(3, {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1}, 9);
    TestReplaceAlgorithm<FIFO>().run(3, {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1}, 15);
    TestReplaceAlgorithm<LRU>().run(3, {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1}, 12);
    TestReplaceAlgorithm<CLOCK>().run(3, {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1}, 14);
}

void genBenchmark(std::mt19937 &rand) {
    int num_frames = 1 + rand() % 1000;
    int num_req = 1 + rand() % 100000;
    std::vector<int> req_pages(num_req);
    for (int i = 0; i < num_req; i++)
        req_pages[i] = rand() % 10000;

    std::cout << num_frames << ',';
    std::cout << num_req << ',';

    std::cout << OPT(num_frames, req_pages) << ',';
    std::cout << FIFO(num_frames, req_pages) << ',';
    std::cout << LRU(num_frames, req_pages) << ',';
    std::cout << CLOCK(num_frames, req_pages) << ',';
    std::cout << RAND(num_frames, req_pages) << '\n';
}

int main() {
#ifdef _DEBUG
    testReplaceAlgorithm();
#endif

    std::ios_base::sync_with_stdio(false);
    freopen("../benchmarks.csv", "w", stdout);

    std::cout << "num frames,num requests,OPT errors,OPT time,FIFO errors,FIFO time,LRU errors,LRU time,";
    std::cout<< "CLOCK errors,CLOCK time,RAND errors,RAND time\n";
    std::mt19937 rand(5);
    for (int i = 0; i < 300; i++) {
        genBenchmark(rand);
    }
    return 0;
}
