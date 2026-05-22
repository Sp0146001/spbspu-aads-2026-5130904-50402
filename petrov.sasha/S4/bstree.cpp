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

template< class Key, class Value, class Compare >
std::size_t petrov::BSTree< Key, Value, Compare >::height(Node* node) const noexcept {
  if (node == nullptr) {
    return 0;
  }

  std::size_t leftHeight = height(node->left);
  std::size_t rightHeight = height(node->right);

  return std::max(leftHeight, rightHeight) + 1;
}

template< class Key, class Value, class Compare >
std::size_t petrov::BSTree< Key, Value, Compare >::height() const noexcept {
  return height(root());
}

template< class Key, class Value, class Compare >
void petrov::BSTree< Key, Value, Compare >::push(const Key& key, const Value& value) {
  if (root() == nullptr)
  {
    setRoot(new Node(key, value, m_fake));
    return;
  }
  Node * parent = m_fake;
  Node * current = root();
  while (current != nullptr) {
    parent = current;
    if (m_compare(key, current->data.first)) {
      current = current->left;
    } else if (m_compare(current->data.first, key)) {
      current = current->right;
    } else {
      current->data.second = value;
      return;
    }
  }
  Node* newNode = new Node(key, value, parent);
  if (m_compare(key, parent->data.first)) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }
}
template< class Key, class Value, class Compare >
typename petrov::BSTree< Key, Value, Compare >::Node*
petrov::BSTree< Key, Value, Compare >::findNode(const Key& key) const noexcept {
  Node* current = root();
  while (current != nullptr){
    if (m_compare(key, current->data.first)) {
      current = current->left;
    } else if (m_compare(current->data.first, key)) {
      current = current->right;
    } else {
      return current;
    }
  }
  return nullptr;
}

template< class Key, class Value, class Compare >
Value& petrov::BSTree< Key, Value, Compare >::get(const Key& key) {
  Node* node = findNode(key);
  if (node == nullptr) {
    throw std::out_of_range("Key not found");
  }
  return node->data.second;
}

template< class Key, class Value, class Compare >
const Value& petrov::BSTree< Key, Value, Compare >::get(const Key& key) const {
  Node* node = findNode(key);
  if (node == nullptr) {
    throw std::out_of_range("Key not found");
  }
  return node->data.second;
}


