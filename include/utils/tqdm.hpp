/**
 * @file tqdm.h
 * @brief A C++ header-only library for creating progress bars in terminal applications.
 *
 * This library provides a flexible and easy-to-use interface for creating and managing
 * progress bars in terminal applications. It includes support for iterating over
 * containers, ranges of integers, and timing-based progress bars. The progress bar
 * dynamically adjusts to the terminal width and can display a variety of symbols to
 * indicate progress.
 *
 * Key Features:
 * - Automatic adjustment to terminal width.
 * - Customizable progress bar size, prefix, and suffix.
 * - Support for iterating over containers, ranges of integers, and custom timers.
 * - Display of estimated time remaining (ETA) and elapsed time.
 * - Customizable update frequency and symbol set.
 *
 * Example Usage:
 * @code
 * #include "tqdm.h"
 *
 * int main() {
 *     std::vector<int> data(100);
 *     auto bar = tqdm::tqdm(data);
 *     for (auto& item : bar) {
 *         // Process item
 *     }
 *
 *     auto range_bar = tqdm::trange(0, 100);
 *     for (auto i : range_bar) {
 *         // Process i
 *     }
 *
 *     auto timer_bar = tqdm::tqdm(tqdm::timer(10)); // 10 seconds timer
 *     for (auto t : timer_bar) {
 *         // Do something for 10 seconds
 *     }
 *
 *     return 0;
 * }
 * @endcode
 *
 * @note This is a header-only library. To use it, simply include this header file
 * in your project.
 *
 * @version 1.0
 * @date Created on Jan 3, 2020
 *
 * @author Miguel Raggi
 * @license MIT License
 */

 #pragma once

#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <type_traits>
#include <sys/ioctl.h>
#include <unistd.h>

// -------------------- chrono stuff --------------------

namespace tqdm {
    using index = std::ptrdiff_t; // maybe std::size_t, but I hate unsigned types.
    using time_point_t = std::chrono::time_point<std::chrono::steady_clock>;

    /**
     * @brief Calculate the elapsed seconds between two time points.
     *
     * This function calculates the elapsed time in seconds between two time points.
     *
     * @param from The starting time point.
     * @param to The ending time point.
     * @return The elapsed time in seconds.
     */
    inline double elapsed_seconds(time_point_t from, time_point_t to) {
        using seconds = std::chrono::duration<double>;
        return std::chrono::duration_cast<seconds>(to - from).count();
    }

    /**
     * @brief A simple chronometer to measure elapsed time.
     */
    class Chronometer {
    public:
        /**
         * @brief Construct a new Chronometer object.
         */
        Chronometer() : start_(std::chrono::steady_clock::now()) {}

        /**
         * @brief Reset the chronometer and return the elapsed time since the last reset.
         *
         * @return The elapsed time in seconds.
         */
        double reset() {
            auto previous = start_;
            start_ = std::chrono::steady_clock::now();

            return elapsed_seconds(previous, start_);
        }

        /**
         * @brief Get the elapsed time without resetting the chronometer.
         *
         * @return The elapsed time in seconds.
         */
        [[nodiscard]] double peek() const {
            auto now = std::chrono::steady_clock::now();

            return elapsed_seconds(start_, now);
        }

        /**
         * @brief Get the starting time point.
         *
         * @return The starting time point.
         */
        [[nodiscard]] time_point_t get_start() const { return start_; }

    private:
        time_point_t start_;
    };

// -------------------- progress_bar --------------------

    /**
     * @brief Clamp a value between two bounds.
     *
     * @param x The value to clamp.
     * @param a The lower bound.
     * @param b The upper bound.
     */
    inline void clamp(double &x, double a, double b) {
        if (x < a) x = a;
        if (x > b) x = b;
    }

    /**
     * @brief Get the width of the terminal window.
     *
     * @return The width of the terminal window in columns.
     */
    inline int get_terminal_width() {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    }

    /**
     * @brief A class representing a progress bar.
     */
    class progress_bar {
    public:
        /**
         * @brief Restart the progress bar.
         */
        void restart() {
            chronometer_.reset();
            refresh_.reset();
            symbol_index_ = 0;
        }

        /**
         * @brief Update the progress bar with the current progress.
         *
         * @param progress The current progress (a value between 0 and 1).
         */
        void update(double progress) {
            clamp(progress, 0, 1);
            symbol_index_++;

            if (time_since_refresh() > min_time_per_update_ || progress == 0 ||
                progress == 1) {
                reset_refresh_timer();
                display(progress);
            }
            suffix_.str("");
        }

        /**
         * @brief Set the output stream for the progress bar.
         *
         * @param os The output stream.
         */
        void set_ostream(std::ostream &os) { os_ = &os; }

        /**
         * @brief Set the prefix string for the progress bar.
         *
         * @param s The prefix string.
         */
        void set_prefix(std::string s) { prefix_ = std::move(s); }

        /**
         * @brief Set the size of the progress bar.
         *
         * @param size The size of the progress bar in characters.
         */
        void set_bar_size(int size) { bar_size_ = size; }

        /**
         * @brief Set the minimum time between updates.
         *
         * @param time The minimum time between updates in seconds.
         */
        void set_min_update_time(double time) { min_time_per_update_ = time; }

        /**
         * @brief Append a value to the progress bar suffix.
         *
         * @param t The value to append.
         * @return A reference to the progress bar.
         */
        template<class T>
        progress_bar &operator<<(const T &t) {
            suffix_ << t;
            return *this;
        }

        /**
         * @brief Get the elapsed time since the progress bar started.
         *
         * @return The elapsed time in seconds.
         */
        double elapsed_time() const { return chronometer_.peek(); }

    private:
        /**
         * @brief Display the progress bar.
         *
         * @param progress The current progress (a value between 0 and 1).
         */
        void display(double progress) {
            auto flags = os_->flags();

            double t = chronometer_.peek();
            double eta = t / progress - t;

            std::stringstream bar;

            // Lengthy prefix
            std::stringstream temp;
            temp << prefix_ << '{' << std::fixed << std::setprecision(1)
                 << std::setw(5) << 100 * progress << "%} "
                 << " (" << t << "s < " << eta << "s) ";

            // Dynamic bar size
            int terminal_width = get_terminal_width();
            int fixed_length = temp.str().size() + suffix_.str().size();
            bar_size_ = terminal_width - fixed_length - 10; // Safety margin

            bar << '\r' << prefix_ << '{' << std::fixed << std::setprecision(1)
                << std::setw(5) << 100 * progress << "%} ";

            print_bar(bar, progress);

            bar << " (" << t << "s < " << eta << "s) ";

            std::string sbar = bar.str();
            std::string suffix = suffix_.str();

            index out_size = sbar.size() + suffix.size();
            term_cols_ = std::max(term_cols_, out_size);
            index num_blank = term_cols_ - out_size;

            (*os_) << sbar << suffix << std::string(num_blank, ' ') << std::flush;

            os_->flags(flags);
        }

        /**
         * @brief Print the progress bar with symbols.
         *
         * @param ss The stringstream to print the bar into.
         * @param filled The fraction of the bar that is filled.
         */
        void print_bar(std::stringstream &ss, double filled) const {
            auto num_filled = static_cast<index>(std::round(filled * bar_size_));
            static const char symbols[] = {'!', '@', '$', '%', '^', '&', '*', '+', '~'};
            int num_symbols = sizeof(symbols) / sizeof(symbols[0]);

            ss << '[';
            for (index i = 0; i < bar_size_; ++i) {
                if (i < num_filled) {
                    ss << '#';
                } else if (i == num_filled && num_filled > 0) {
                    ss << symbols[symbol_index_ % num_symbols]; // Use symbol_index_ for frequency
                } else {
                    ss << '.';
                }
            }
            ss << ']';
        }

        /**
         * @brief Get the time since the last refresh.
         *
         * @return The time since the last refresh in seconds.
         */
        double time_since_refresh() const { return refresh_.peek(); }

        /**
         * @brief Reset the refresh timer.
         */
        void reset_refresh_timer() { refresh_.reset(); }

        Chronometer chronometer_{};
        Chronometer refresh_{};
        double min_time_per_update_{0.15}; // found experimentally

        std::ostream *os_{&std::cerr};

        index bar_size_{40};
        index term_cols_{1};
        index symbol_index_{0};

        std::string prefix_{};
        std::stringstream suffix_{};
    };

// -------------------- iter_wrapper --------------------

    /**
     * @brief A wrapper class for iterators to update the progress bar.
     *
     * @tparam ForwardIter The type of the underlying iterator.
     * @tparam Parent The type of the parent progress bar.
     */
    template<class ForwardIter, class Parent>
    class iter_wrapper {
    public:
        using iterator_category = typename ForwardIter::iterator_category;
        using value_type = typename ForwardIter::value_type;
        using difference_type = typename ForwardIter::difference_type;
        using pointer = typename ForwardIter::pointer;
        using reference = typename ForwardIter::reference;

        iter_wrapper(ForwardIter it, Parent *parent) : current_(it), parent_(parent) {}

        auto operator*() { return *current_; }

        void operator++() { ++current_; }

        template<class Other>
        bool operator!=(const Other &other) const {
            parent_->update(); // here and not in ++ because I need to run update
            // before first advancement!
            return current_ != other;
        }

        bool operator!=(const iter_wrapper &other) const {
            parent_->update(); // here and not in ++ because I need to run update
            // before first advancement!
            return current_ != other.current_;
        }

        [[nodiscard]] const ForwardIter &get() const { return current_; }

    private:
        friend Parent;
        ForwardIter current_;
        Parent *parent_;
    };

// -------------------- tqdm_for_lvalues --------------------

    /**
     * @brief A class for progress bars that iterate over lvalues.
     *
     * @tparam ForwardIter The type of the forward iterator.
     * @tparam EndIter The type of the end iterator.
     */
    template<class ForwardIter, class EndIter = ForwardIter>
    class tqdm_for_lvalues {
    public:
        using this_t = tqdm_for_lvalues<ForwardIter, EndIter>;
        using iterator = iter_wrapper<ForwardIter, this_t>;
        using value_type = typename ForwardIter::value_type;
        using size_type = index;
        using difference_type = index;

        tqdm_for_lvalues(ForwardIter begin, EndIter end)
                : first_(begin, this), last_(end), num_iters_(std::distance(begin, end)) {}

        tqdm_for_lvalues(ForwardIter begin, EndIter end, index total)
                : first_(begin, this), last_(end), num_iters_(total) {}

        template<class Container>
        explicit tqdm_for_lvalues(Container &C)
                : first_(C.begin(), this), last_(C.end()), num_iters_(C.size()) {}

        template<class Container>
        explicit tqdm_for_lvalues(const Container &C)
                : first_(C.begin(), this), last_(C.end()), num_iters_(C.size()) {}

        tqdm_for_lvalues(const tqdm_for_lvalues &) = delete;

        tqdm_for_lvalues(tqdm_for_lvalues &&) = delete;

        tqdm_for_lvalues &operator=(tqdm_for_lvalues &&) = delete;

        tqdm_for_lvalues &operator=(const tqdm_for_lvalues &) = delete;

        ~tqdm_for_lvalues() = default;

        template<class Container>
        tqdm_for_lvalues(Container &&) = delete; // prevent misuse!

        iterator begin() {
            bar_.restart();
            iters_done_ = 0;
            return first_;
        }

        EndIter end() const { return last_; }

        void update() {
            ++iters_done_;
            bar_.update(calc_progress());
        }

        void set_ostream(std::ostream &os) { bar_.set_ostream(os); }

        void set_prefix(std::string s) { bar_.set_prefix(std::move(s)); }

        void set_bar_size(int size) { bar_.set_bar_size(size); }

        void set_min_update_time(double time) { bar_.set_min_update_time(time); }

        template<class T>
        tqdm_for_lvalues &operator<<(const T &t) {
            bar_ << t;
            return *this;
        }

        void manually_set_progress(double to) {
            clamp(to, 0, 1);
            iters_done_ = std::round(to * num_iters_);
        }

    private:
        double calc_progress() const {
            double denominator = num_iters_;
            if (num_iters_ == 0) denominator += 1e-9;
            return iters_done_ / denominator;
        }

        iterator first_;
        EndIter last_;
        index num_iters_{0};
        index iters_done_{0};
        progress_bar bar_;
    };

    template<class Container>
    tqdm_for_lvalues(Container &) -> tqdm_for_lvalues<typename Container::iterator>;

    template<class Container>
    tqdm_for_lvalues(const Container &)
    -> tqdm_for_lvalues<typename Container::const_iterator>;

// -------------------- tqdm_for_rvalues --------------------

    /**
     * @brief A class for progress bars that iterate over rvalues.
     *
     * @tparam Container The type of the container.
     */
    template<class Container>
    class tqdm_for_rvalues {
    public:
        using iterator = typename Container::iterator;
        using const_iterator = typename Container::const_iterator;
        using value_type = typename Container::value_type;

        explicit tqdm_for_rvalues(Container &&C)
                : C_(std::forward<Container>(C)), tqdm_(C_) {}

        auto begin() { return tqdm_.begin(); }

        auto end() { return tqdm_.end(); }

        void update() { return tqdm_.update(); }

        void set_ostream(std::ostream &os) { tqdm_.set_ostream(os); }

        void set_prefix(std::string s) { tqdm_.set_prefix(std::move(s)); }

        void set_bar_size(int size) { tqdm_.set_bar_size(size); }

        void set_min_update_time(double time) { tqdm_.set_min_update_time(time); }

        template<class T>
        auto &operator<<(const T &t) {
            return tqdm_ << t;
        }

        void advance(index amount) { tqdm_.advance(amount); }

        void manually_set_progress(double to) { tqdm_.manually_set_progress(to); }

    private:
        Container C_;
        tqdm_for_lvalues<iterator> tqdm_;
    };

    template<class Container>
    tqdm_for_rvalues(Container &&) -> tqdm_for_rvalues<Container>;

// -------------------- tqdm --------------------

    /**
     * @brief Create a tqdm progress bar for a range of iterators.
     *
     * @tparam ForwardIter The type of the forward iterator.
     * @param first The beginning of the range.
     * @param last The end of the range.
     * @return A tqdm progress bar.
     */
    template<class ForwardIter>
    auto tqdm(const ForwardIter &first, const ForwardIter &last) {
        return tqdm_for_lvalues(first, last);
    }

    /**
     * @brief Create a tqdm progress bar for a range of iterators with a specified total size.
     *
     * @tparam ForwardIter The type of the forward iterator.
     * @param first The beginning of the range.
     * @param last The end of the range.
     * @param total The total size of the range.
     * @return A tqdm progress bar.
     */
    template<class ForwardIter>
    auto tqdm(const ForwardIter &first, const ForwardIter &last, index total) {
        return tqdm_for_lvalues(first, last, total);
    }

    /**
     * @brief Create a tqdm progress bar for a container.
     *
     * @tparam Container The type of the container.
     * @param C The container.
     * @return A tqdm progress bar.
     */
    template<class Container>
    auto tqdm(const Container &C) {
        return tqdm_for_lvalues(C);
    }

    /**
     * @brief Create a tqdm progress bar for a container.
     *
     * @tparam Container The type of the container.
     * @param C The container.
     * @return A tqdm progress bar.
     */
    template<class Container>
    auto tqdm(Container &C) {
        return tqdm_for_lvalues(C);
    }

    /**
     * @brief Create a tqdm progress bar for a container (rvalue reference).
     *
     * @tparam Container The type of the container.
     * @param C The container.
     * @return A tqdm progress bar.
     */
    template<class Container>
    auto tqdm(Container &&C) {
        return tqdm_for_rvalues(std::forward<Container>(C));
    }

// -------------------- int_iterator --------------------

    /**
     * @brief A random access iterator for integers.
     *
     * @tparam IntType The type of the integer.
     */
    template<class IntType>
    class int_iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = IntType;
        using difference_type = IntType;
        using pointer = IntType *;
        using reference = IntType &;

        explicit int_iterator(IntType val) : value_(val) {}

        IntType &operator*() { return value_; }

        int_iterator &operator++() {
            ++value_;
            return *this;
        }

        int_iterator &operator--() {
            --value_;
            return *this;
        }

        int_iterator &operator+=(difference_type d) {
            value_ += d;
            return *this;
        }

        difference_type operator-(const int_iterator &other) const {
            return value_ - other.value_;
        }

        bool operator!=(const int_iterator &other) const {
            return value_ != other.value_;
        }

    private:
        IntType value_;
    };

// -------------------- range --------------------

    /**
     * @brief A range of integers represented by iterators.
     *
     * @tparam IntType The type of the integer.
     */
    template<class IntType>
    class range {
    public:
        using iterator = int_iterator<IntType>;
        using const_iterator = iterator;
        using value_type = IntType;

        range(IntType first, IntType last) : first_(first), last_(last) {}

        explicit range(IntType last) : first_(0), last_(last) {}

        [[nodiscard]] iterator begin() const { return first_; }

        [[nodiscard]] iterator end() const { return last_; }

        [[nodiscard]] index size() const { return last_ - first_; }

    private:
        iterator first_;
        iterator last_;
    };

    /**
     * @brief Create a tqdm progress bar for a range of integers.
     *
     * @tparam IntType The type of the integer.
     * @param first The first integer.
     * @param last The last integer.
     * @return A tqdm progress bar.
     */
    template<class IntType>
    auto trange(IntType first, IntType last) {
        return tqdm(range(first, last));
    }

    /**
     * @brief Create a tqdm progress bar for a range of integers.
     *
     * @tparam IntType The type of the integer.
     * @param last The last integer.
     * @return A tqdm progress bar.
     */
    template<class IntType>
    auto trange(IntType last) {
        return tqdm(range(last));
    }

// -------------------- timing_iterator --------------------

    /**
    * @brief An end sentinel for timing iterators.
    */
    class timing_iterator_end_sentinel {
    public:
        explicit timing_iterator_end_sentinel(double num_seconds)
                : num_seconds_(num_seconds) {}

        [[nodiscard]] double num_seconds() const { return num_seconds_; }

    private:
        double num_seconds_;
    };

    /**
     * @brief A forward iterator that returns the elapsed time.
     */
    class timing_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = double;
        using difference_type = double;
        using pointer = double *;
        using reference = double &;

        double operator*() const { return chrono_.peek(); }

        timing_iterator &operator++() { return *this; }

        bool operator!=(const timing_iterator_end_sentinel &other) const {
            return chrono_.peek() < other.num_seconds();
        }

    private:
        tqdm::Chronometer chrono_;
    };

// -------------------- timer -------------------

    /**
     * @brief A timer that can be used to create a timing iterator.
     */
    struct timer {
    public:
        using iterator = timing_iterator;
        using end_iterator = timing_iterator_end_sentinel;
        using const_iterator = iterator;
        using value_type = double;

        explicit timer(double num_seconds) : num_seconds_(num_seconds) {}

        [[nodiscard]] static iterator begin() { return iterator(); }

        [[nodiscard]] end_iterator end() const {
            return end_iterator(num_seconds_);
        }

        [[nodiscard]] double num_seconds() const { return num_seconds_; }

    private:
        double num_seconds_;
    };

    /**
     * @brief A progress bar for a timer.
     */
    class tqdm_timer {
    public:
        using iterator = iter_wrapper<timing_iterator, tqdm_timer>;
        using end_iterator = timer::end_iterator;
        using value_type = typename timing_iterator::value_type;
        using size_type = index;
        using difference_type = index;

        explicit tqdm_timer(double num_seconds) : num_seconds_(num_seconds) {}

        tqdm_timer(const tqdm_timer &) = delete;

        tqdm_timer(tqdm_timer &&) = delete;

        tqdm_timer &operator=(tqdm_timer &&) = delete;

        tqdm_timer &operator=(const tqdm_timer &) = delete;

        ~tqdm_timer() = default;

        template<class Container>
        tqdm_timer(Container &&) = delete; // prevent misuse!

        iterator begin() {
            bar_.restart();
            return iterator(timing_iterator(), this);
        }

        end_iterator end() const { return end_iterator(num_seconds_); }

        void update() {
            double t = bar_.elapsed_time();

            bar_.update(t / num_seconds_);
        }

        void set_ostream(std::ostream &os) { bar_.set_ostream(os); }

        void set_prefix(std::string s) { bar_.set_prefix(std::move(s)); }

        void set_bar_size(int size) { bar_.set_bar_size(size); }

        void set_min_update_time(double time) { bar_.set_min_update_time(time); }

        template<class T>
        tqdm_timer &operator<<(const T &t) {
            bar_ << t;
            return *this;
        }

    private:
        double num_seconds_;
        progress_bar bar_;
    };

    /**
     * @brief Create a tqdm progress bar for a timer.
     *
     * @param t The timer.
     * @return A tqdm progress bar.
     */
    inline auto tqdm(timer t) { return tqdm_timer(t.num_seconds()); }

} // namespace tqdm
