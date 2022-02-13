#ifndef REPLACEMENTALGORITHMS_REPLACEMENT_ALGORITHMS_H

#include <time.h>

/**
 * ReplaceAlgorithm is a base class for different implementations
 * of replacement algorithms
 */
class ReplaceAlgorithm {
public:

    ReplaceAlgorithm(int num_frames, std::vector<int> req_pages) :
            _num_frames(num_frames), _req_pages(std::move(req_pages)) {
        assert(num_frames > 0);
    }

    int get_num_page_errors() {
        clock_t start_time = clock();

        int num_page_errors = 0;

        for (int page : _req_pages) {
            // if current page is uploaded then no page error
            if (is_page_loaded(page))
                continue;

            // there is a page error
            num_page_errors++;
            // if there is no free space for new page in RAM, delete first-in page,
            // otherwise this function does nothing
            remove_replaced_page();
            insert_new_page(page);
        }

        clock_t end_time = clock();
        _algorithm_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        return num_page_errors;
    }

protected:
    virtual bool is_page_loaded(int page) = 0;

    virtual void remove_replaced_page() = 0;

    // this function should be used only when
    // the page need to be added to RAM
    virtual void insert_new_page(int page) = 0;

    const int _num_frames;
    const std::vector<int> _req_pages;

    // time get_num_pages_errors runs
    double _algorithm_time = 0;
    int _page_errors = 0;

    friend std::ostream& operator<< (std::ostream& out, const ReplaceAlgorithm& algorithm);
};

std::ostream& operator<< (std::ostream& out, const ReplaceAlgorithm& algorithm) {
    out << algorithm._page_errors << ',' << (int)(algorithm._algorithm_time * 1000);
    return out;
}

#define REPLACEMENTALGORITHMS_REPLACEMENT_ALGORITHMS_H

#endif //REPLACEMENTALGORITHMS_REPLACEMENT_ALGORITHMS_H
