#ifndef LEVENTRIE_TRIE_H
#define LEVENTRIE_TRIE_H

#include "automaton.h"

#include <string>
#include <vector>

namespace leventrie {

class trie {
    char ch_ = '\0';
    std::vector<trie> nodes_;
    std::string word_;

public:
    trie() = default;
    ~trie() noexcept = default;

    const std::string& word() const noexcept {
        return word_;
    }

    bool is_word() const noexcept {
        return !word_.empty();
    }

    template<typename F>
    void foreach(F&& func) const {
        for (const auto& node : nodes_) {
            func(node, node.ch_);
        }
    }

    int min_distance(const std::string& word, int max_edits) const {
        Automaton aut(word, max_edits);
        auto min_cost = min_distance_impl_(*this, aut, aut.start());
        return min_cost > max_edits ? 0xff : min_cost;
    }

    void insert(const std::string& word) noexcept {
        auto* ptr = this;
        for (auto ch : word) {
            bool found = false;
            for (auto& node : ptr->nodes_) {
                if (node.ch_ == ch) {
                    found = true;
                    ptr = &node;
                    break;
                }
            }
            if (!found) {
                ptr->nodes_.emplace_back();
                ptr = &ptr->nodes_.back();
                ptr->ch_ = ch;
            }
        }
        ptr->word_ = word;
    }

private:
    static int min_distance_impl_(const trie& tree, const Automaton& aut, const State& state) {
        int min_cost = tree.is_word() ? aut.cost(state) : 0xff;
        tree.foreach([&](const trie& node, char ch) {
            bool can_match = false;
            auto next_state = aut.step(state, ch, &can_match);
            if (can_match) {
                min_cost = std::min(min_cost, min_distance_impl_(node, aut, next_state));
            }
        });
        return min_cost;
    }
};

}  // namespace leventrie

#endif  // LEVENTRIE_TRIE_H
