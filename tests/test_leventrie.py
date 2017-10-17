import pytest
from leventrie import Trie


@pytest.fixture
def trie():
    return Trie(['foo', b'bar', 'baz', 'hello'])


def test_trie(trie):
    assert trie.min_distance('', 0) == 255
    assert trie.min_distance('', 3) == 3

    assert trie.min_distance('fo', 0) == 255
    assert trie.min_distance('fo', 1) == 1

