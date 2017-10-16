#ifndef LEVENTRIE_TRIE_H
#define LEVENTRIE_TRIE_H

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
};

}  // namespace leventrie

#endif  // LEVENTRIE_TRIE_H
