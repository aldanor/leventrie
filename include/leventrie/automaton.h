#ifndef LEVENTRIE_AUTOMATON_H
#define LEVENTRIE_AUTOMATON_H

#include <algorithm>
#include <array>
#include <string>

namespace leventrie {

constexpr static size_t MAX_WORD_LENGTH = 32;

struct State {
    State() = default;

    uint8_t& operator[](int index) {
        return data_[index];
    }

    uint8_t operator[](int index) const {
        return data_[index];
    }

private:
    std::array<uint8_t, MAX_WORD_LENGTH> data_ = {};
};

struct Automaton {
    Automaton(std::string word, int max_edits)
        : word(std::move(word))
        , length(static_cast<uint8_t>(this->word.size()))
        , max_edits(max_edits)
    {}

    State start() const {
        State state {};
        for (uint8_t i = 0; i < length + 1; ++i) {
            state[i] = i;
        }
        return state;
    }

    State step(const State& state, char ch, bool* can_match = nullptr) const noexcept {
        State new_state {};
        constexpr static uint8_t one = 1;
        uint8_t val = state[0] + one;
        new_state[0] = val;
        bool cm = val <= max_edits;
        for (uint8_t i = 0; i < length; ++i) {
            ++val;
            uint8_t v1 = state[i] + (word[i] != ch);
            if (v1 < val) {
                val = v1;
            }
            uint8_t v2 = state[i + 1] + one;
            if (v2 < val) {
                val = v2;
            }
            new_state[i + 1] = val;
            cm = cm || val <= max_edits;
        }
        if (can_match != nullptr) {
            *can_match = cm;
        }
        return new_state;
    }

    int cost(const State& state) const {
        return state[length];
    }

private:
    std::string word;
    uint8_t length;
    int max_edits;
};

}  // namespace leventrie

#endif  // LEVENTRIE_AUTOMATON_H
