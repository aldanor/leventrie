cmake_minimum_required(VERSION 3.0)
project(leventrie)

add_library(leventrie INTERFACE)
target_sources(leventrie INTERFACE
    include/leventrie/automaton.h include/leventrie/trie.h)
target_include_directories(leventrie INTERFACE
    include/)
install(FILES
    include/leventrie/automaton.h include/leventrie/trie.h
    DESTINATION include/leventrie/)
