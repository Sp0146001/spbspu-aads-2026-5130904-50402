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

template< class Key, class Value, class Compare >
typename petrov::BSTree< Key, Value, Compare >::Node* petrov::BSTree< Key, Value, Compare >::root() const noexcept {
  return m_fake->left;
}

template< class Key, class Value, class Compare >
void petrov::BSTree< Key, Value, Compare >::setRoot(Node* node) noexcept {
  m_fake->left = node;
  if (node != nullptr) {
    node->parent = m_fake;
  }
}

template< class Key, class Value, class Compare >
petrov::BSTree< Key, Value, Compare >::BSTree():
  m_fake(new Node(Key(), Value(), nullptr)),
  m_compare()
{
  m_fake->left = nullptr;
  m_fake->right = nullptr;
}

template< class Key, class Value, class Compare >
petrov::BSTree< Key, Value, Compare >::~BSTree() {
  clear(root());
  delete m_fake;
}

template< class Key, class Value, class Compare >
void petrov::BSTree< Key, Value, Compare >::clear(Node* node) noexcept {
  if (node == nullptr)
  {
    return;
  }

  clear(node->left);
  clear(node->right);
  delete node;
}
