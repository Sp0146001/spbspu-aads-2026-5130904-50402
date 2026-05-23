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

template< class Key, class Value >
petrov::BSTConstIterator< Key, Value >::BSTConstIterator() noexcept:
  m_node(nullptr),
  m_fake(nullptr)
{}

template< class Key, class Value >
petrov::BSTConstIterator< Key, Value >::BSTConstIterator(
    Node* node,
    Node* fake) noexcept:
  m_node(node),
  m_fake(fake)
{}

template< class Key, class Value >
const typename petrov::BSTConstIterator< Key, Value >::value_type &
petrov::BSTConstIterator< Key, Value >::operator*() const noexcept
{
  return m_node->data;
}

template< class Key, class Value >
const typename petrov::BSTConstIterator< Key, Value >::value_type *
petrov::BSTConstIterator< Key, Value >::operator->() const noexcept
{
  return &m_node->data;
}

template< class Key, class Value >
petrov::BSTConstIterator< Key, Value > &
petrov::BSTConstIterator< Key, Value >::operator++() noexcept
{
  if (m_node == nullptr) {
    return *this;
  }

  if (m_node->right != nullptr) {
    m_node = m_node->right;
    while (m_node->left != nullptr) {
      m_node = m_node->left;
    }
  } else {
    Node* parent = m_node->parent;
    while (parent != m_fake && m_node == parent->right) {
      m_node = parent;
      parent = parent->parent;
    }
    m_node = (parent == m_fake) ? nullptr : parent;
  }
  return *this;
}

template< class Key, class Value >
petrov::BSTConstIterator< Key, Value >
petrov::BSTConstIterator< Key, Value >::operator++(int) noexcept {
  BSTConstIterator temp(*this);
  ++(*this);
  return temp;
}

template< class Key, class Value >
bool petrov::BSTConstIterator< Key, Value >::operator==(const BSTConstIterator& other) const noexcept {
  return m_node == other.m_node;
}

template< class Key, class Value >
bool petrov::BSTConstIterator< Key, Value >::operator!=(const BSTConstIterator& other) const noexcept {
  return m_node != other.m_node;
}

template< class Key, class Value >
petrov::BSTIterator< Key, Value >::BSTIterator() noexcept:
  m_node(nullptr),
  m_fake(nullptr)
{}

template< class Key, class Value >
petrov::BSTIterator< Key, Value >::BSTIterator(Node* node, Node* fake) noexcept:
  m_node(node),
  m_fake(fake)
{}

template< class Key, class Value >
typename petrov::BSTIterator< Key, Value >::value_type& petrov::BSTIterator< Key, Value >::operator*() const noexcept {
  return m_node->data;
}

template< class Key, class Value >
typename petrov::BSTIterator< Key, Value >::value_type*
petrov::BSTIterator< Key, Value >::operator->() const noexcept {
  return &m_node->data;
}

template< class Key, class Value >
petrov::BSTIterator< Key, Value >&
petrov::BSTIterator< Key, Value >::operator++() noexcept {
  BSTConstIterator< Key, Value > temp(m_node, m_fake);
  ++temp;F
  m_node = temp.m_node;
  return *this;
}

template< class Key, class Value >
petrov::BSTIterator< Key, Value > petrov::BSTIterator< Key, Value >::operator++(int) noexcept {
  BSTIterator temp(*this);
  ++(*this);
  return temp;
}

template< class Key, class Value >
bool petrov::BSTIterator< Key, Value >::operator==(const BSTIterator& other) const noexcept {
  return m_node == other.m_node;
}

template< class Key, class Value >
bool petrov::BSTIterator< Key, Value >::operator!=(const BSTIterator& other) const noexcept {
  return m_node != other.m_node;
}

template< class Key, class Value >
petrov::BSTIterator< Key, Value >::operator petrov::BSTConstIterator< Key, Value >() const noexcept {
  return BSTConstIterator< Key, Value >(m_node, m_fake);
}

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
  if (node == nullptr) {
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
  Node* parent = m_fake;
  Node* current = root();
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

template< class Key, class Value, class Compare >
typename petrov::BSTree< Key, Value, Compare >::Node*
petrov::BSTree< Key, Value, Compare >::rotateLeftNode(Node* node) {
  Node* newRoot = node->right;
  node->right = newRoot->left;
  if (newRoot->left != nullptr) {
    newRoot->left->parent = node;
  }
  newRoot->parent = node->parent;
  if (node->parent->left == node) {
    node->parent->left = newRoot;
  } else {
    node->parent->right = newRoot;
  }
  newRoot->left = node;
  node->parent = newRoot;
  return newRoot;
}

template< class Key, class Value, class Compare >
typename petrov::BSTree< Key, Value, Compare >::Node*
petrov::BSTree< Key, Value, Compare >::rotateRightNode(Node* node)
{
  Node* newRoot = node->left;

  node->left = newRoot->right;

  if (newRoot->right != nullptr) {
    newRoot->right->parent = node;
  }
  newRoot->parent = node->parent;
  if (node->parent->left == node) {
    node->parent->left = newRoot;
  } else {
    node->parent->right = newRoot;
  }
  newRoot->right = node;
  node->parent = newRoot;
  return newRoot;
}


