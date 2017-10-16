#include <leventrie/automaton.h>
#include <leventrie/trie.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(leventrie, m) {
    m.attr("test") = 1;
}
