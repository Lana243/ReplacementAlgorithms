#ifndef REPLACEMENTALGORITHMS_FIFO_H
#define REPLACEMENTALGORITHMS_FIFO_H

#include "replacement_algorithms.h"

/**
 * FIFO implements replacement algorithm that replaces the page which
 * was added to RAM earlier than others
 */
class FIFO : public ReplaceAlgorithm {
public:
    FIFO(int num_frames, std::vector<int> req_pages) : ReplaceAlgorithm(num_frames, std::move(req_pages)) {
        _page_errors = get_num_page_errors();
    }

private:
    // set of pages that are currently loaded to RAM
    std::unordered_set<int> _loaded_pages;
    // queue of pages in RAM ordered by the time of entrance
    std::queue<int> _queue_frames;

    void remove_replaced_page() override {
        if (has_free_ram())
            return;
        int first_in_frame = _queue_frames.front();
        _queue_frames.pop();
        _loaded_pages.erase(first_in_frame);
    }

    void insert_new_page(int page) override {
        _queue_frames.push(page);
        _loaded_pages.insert(page);
    }

    bool has_free_ram() {
        return _loaded_pages.size() < _num_frames;
    }

    bool is_page_loaded(int page) override {
        return _loaded_pages.find(page) != _loaded_pages.end();
    }
};

#endif //REPLACEMENTALGORITHMS_FIFO_H
