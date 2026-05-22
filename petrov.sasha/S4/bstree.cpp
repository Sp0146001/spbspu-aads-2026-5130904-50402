#include "bstree.hpp"
#include <algorithm>
#include <stdexcept>

template< class Key, class Value, class Compare >
petrov::BSTree< Key, Value, Compare >::Node::Node(
  const Key& key, const Value& value, Node* parentNode):
  data(key, value),
  parent(parentNode),
  left(nullptr),
  right(nullptr)
{}
