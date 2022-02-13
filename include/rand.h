#ifndef REPLACEMENTALGORITHMS_RAND_H
#define REPLACEMENTALGORITHMS_RAND_H

#include "replacement_algorithms.h"

/**
 * RAND implements replacement algorithm that replaces the random loaded to RAM page
 */
class RAND : public ReplaceAlgorithm {
public:
    RAND(int num_frames, std::vector<int> req_pages) : ReplaceAlgorithm(num_frames, std::move(req_pages)) {
        _page_errors = get_num_page_errors();
    }

private:
    // pages loaded to RAM
    std::vector<int> _loaded_pages;
    // positions of loaded pages in _loaded_pages
    std::unordered_map<int, int> _loaded_pages_pos;
    std::mt19937 _rand;

    void remove_replaced_page() override {
        if (has_free_ram())
            return;
        int ind = _rand() % _loaded_pages.size();
        _loaded_pages_pos.erase(_loaded_pages[ind]);
        if (ind != _loaded_pages.size() - 1) {
            _loaded_pages_pos[_loaded_pages.back()] = ind;
            _loaded_pages[ind] = _loaded_pages.back();
        }
        _loaded_pages.pop_back();
    }

    void insert_new_page(int page) override {
        _loaded_pages.push_back(page);
        _loaded_pages_pos[page] = _loaded_pages.size() - 1;
    }

    bool has_free_ram() {
        return _loaded_pages.size() < _num_frames;
    }

    bool is_page_loaded(int page) override {
        return _loaded_pages_pos.find(page) != _loaded_pages_pos.end();
    }
};




#endif //REPLACEMENTALGORITHMS_RAND_H
