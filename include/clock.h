#ifndef REPLACEMENTALGORITHMS_CLOCK_H
#define REPLACEMENTALGORITHMS_CLOCK_H

#include "replacement_algorithms.h"

/**
 * CLOCK implements CLOCK replacement algorithm
 * To learn more see: https://stepik.org/lesson/633809/step/4?unit=630582
 */
class CLOCK : public ReplaceAlgorithm {
public:
    CLOCK(int num_frames, std::vector<int> req_pages) : ReplaceAlgorithm(num_frames, std::move(req_pages)) {
        _clock.resize(num_frames);
        std::pair<int, bool> default_val = {-1, false};
        std::fill(_clock.begin(), _clock.end(), default_val);
        _page_errors = get_num_page_errors();
    }

private:
    // the cyclic buffer, containing pairs, where
    // first -- the page, second -- usage bit
    std::vector<std::pair<int, bool>> _clock;
    // current position on the clock
    int it = -1;
    // for each page in RAM map the position in the clock
    std::unordered_map<int, int> _clock_pos;

    void remove_replaced_page() override {
        while (true) {
            it = (it + 1) % _num_frames;
            // if the usage bit is 0, we found the page for replacement
            if (!_clock[it].second)
                break;
            // change the usage bit
            _clock[it].second = false;
        }
        _clock_pos.erase(_clock[it].first);
    }

    void insert_new_page(int page) override {
        _clock[it] = {page, true};
        _clock_pos[page] = it;
    }

    bool is_page_loaded(int page) override {
        auto iter = _clock_pos.find(page);
        if (iter == _clock_pos.end())
            return false;
        // if the page is in RAM update the usage bit
        _clock[iter->second].second = true;
        return true;
    }
};

#endif //REPLACEMENTALGORITHMS_CLOCK_H
