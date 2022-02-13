#ifndef REPLACEMENTALGORITHMS_OPT_H
#define REPLACEMENTALGORITHMS_OPT_H

#include <climits>
#include "replacement_algorithms.h"

/**
 * OPT implements optimal replacement algorithm
 */
class OPT : public ReplaceAlgorithm {
public:
    OPT(int num_frames, std::vector<int> req_pages) : ReplaceAlgorithm(num_frames, std::move(req_pages)) {
        for (size_t i = 0; i < _req_pages.size(); i++) {
            _timestamps_page_used[_req_pages[i]].push(i);
        }
        for (auto &it : _timestamps_page_used) {
            it.second.push(INT_MAX);
        }
        _page_errors = get_num_page_errors();
    }

private:
    // loaded frames pairs where first -- next time the page
    // will be requested, second - page number
    std::set<std::pair<int, int>> _loaded_frames;
    // _timestamps_page_used maps the page number
    // and the queue of timestamps when this page
    // was requested
    std::unordered_map<int, std::queue<int>> _timestamps_page_used;

    void remove_replaced_page() override {
        if (has_free_ram())
            return;
        // remove the page with oldest next time the page will be used in future
        _loaded_frames.erase(prev(_loaded_frames.end()));
    }

    void insert_new_page(int page) override {
        _loaded_frames.insert({_timestamps_page_used[page].front(), page});
    }

    bool is_page_loaded(int page) override {
        bool ans;
        auto it = _loaded_frames.find({_timestamps_page_used[page].front(), page});
        // if current page is not loaded ans = false, otherwise true
        if (it == _loaded_frames.end())
            ans = false;
        else
            ans = true;

        // update next time the page will be used in future
        _timestamps_page_used[page].pop();
        if (it != _loaded_frames.end()) {
            _loaded_frames.erase(it);
            _loaded_frames.insert({_timestamps_page_used[page].front(), page});
        }
        return ans;
    }

    bool has_free_ram() {
        return _loaded_frames.size() < _num_frames;
    }
};

#endif //REPLACEMENTALGORITHMS_OPT_H
