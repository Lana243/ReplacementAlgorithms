#ifndef REPLACEMENTALGORITHMS_LRU_H
#define REPLACEMENTALGORITHMS_LRU_H

#include "replacement_algorithms.h"

/**
 * LRU implements the replacement algorithm where
 * replaced page is page that was least recently used
 */
class LRU : public ReplaceAlgorithm {
public:
    LRU(int num_frames, std::vector<int> req_pages) : ReplaceAlgorithm(num_frames, std::move(req_pages)) {
        _page_errors = get_num_page_errors();
    }

private:
    int _timer = 0;
    // loaded frames in a pair: first -- last time used, second -- page itself
    std::set<std::pair<int, int>> _loaded_frames;
    // map for each page: last time the page was used
    std::unordered_map<int, int> _last_time_used;

    void remove_replaced_page() override {
        if (has_free_ram())
            return;
        // get the pair (time, page) where time is the least,
        // so the page is least recently used
        std::pair<int, int> last_used_page = *_loaded_frames.begin();
        _last_time_used.erase(last_used_page.second);
        _loaded_frames.erase(last_used_page);
    }

    void insert_new_page(int page) override {
        _timer++;
        _loaded_frames.insert({_timer, page});
        _last_time_used[page] = _timer;
    }

    bool is_page_loaded(int page) override {
        auto it = _last_time_used.find(page);
        if (it == _last_time_used.end()) {
            return false;
        }

        // if page is loaded to RAM, update the last time it was used
        _timer++;
        _loaded_frames.erase({it->second, it->first});
        _last_time_used[page] = _timer;
        _loaded_frames.insert({_timer, page});
        return true;
    }

    bool has_free_ram() {
        return _loaded_frames.size() < _num_frames;
    }
};

#endif //REPLACEMENTALGORITHMS_LRU_H
