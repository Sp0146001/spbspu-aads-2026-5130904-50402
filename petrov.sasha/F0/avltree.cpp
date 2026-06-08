#include "avltree.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>

#include "question.hpp"
#include "tag.hpp"

template< class Key, class Value, class Compare >
petrov::AvlTree< Key, Value, Compare >::Node::Node(
  const Key& key, const Value& value, Node* parentNode):
  data(key, value),
  parent(parentNode),
  left(nullptr),
  right(nullptr),
  height(1)
{}

template< class Key, class Value, class Compare >
petrov::AvlTree< Key, Value, Compare >::AvlTree():
  fake_(new Node(Key(), Value(), nullptr)),
  size_(0),
  compare_()
{
  fake_->left = nullptr;
  fake_->right = nullptr;
}

template< class Key, class Value, class Compare >
petrov::AvlTree< Key, Value, Compare >::AvlTree(const AvlTree& other):
  fake_(new Node(Key(), Value(), nullptr)),
  size_(other.size_),
  compare_(other.compare_)
{
  fake_->left = copy(other.root(), fake_);
  fake_->right = nullptr;
}

template< class Key, class Value, class Compare >
petrov::AvlTree< Key, Value, Compare >::AvlTree(AvlTree&& other) noexcept:
  fake_(other.fake_),
  size_(other.size_),
  compare_(other.compare_)
{
  other.fake_ = new Node(Key(), Value(), nullptr);
  other.fake_->left = nullptr;
  other.fake_->right = nullptr;
  other.size_ = 0;
}

template< class Key, class Value, class Compare >
petrov::AvlTree< Key, Value, Compare >::~AvlTree()
{
  clear(root());
  delete fake_;
}

template< class Key, class Value, class Compare >
petrov::AvlTree< Key, Value, Compare >&
petrov::AvlTree< Key, Value, Compare >::operator=(const AvlTree& other)
{
  if (this != std::addressof(other)) {
    clear(root());
    fake_->left = copy(other.root(), fake_);
    size_ = other.size_;
    compare_ = other.compare_;
  }
  return *this;
}

template< class Key, class Value, class Compare >
petrov::AvlTree< Key, Value, Compare >&
petrov::AvlTree< Key, Value, Compare >::operator=(AvlTree&& other) noexcept
{
  if (this != std::addressof(other)) {
    clear(root());
    delete fake_;
    fake_ = other.fake_;
    size_ = other.size_;
    compare_ = other.compare_;
    other.fake_ = new Node(Key(), Value(), nullptr);
    other.fake_->left = nullptr;
    other.fake_->right = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template< class Key, class Value, class Compare >
typename petrov::AvlTree< Key, Value, Compare >::Node*
petrov::AvlTree< Key, Value, Compare >::root() const noexcept
{
  return fake_->left;
}

template< class Key, class Value, class Compare >
void petrov::AvlTree< Key, Value, Compare >::setRoot(Node* node) noexcept
{
  fake_->left = node;
  if (node != nullptr) {
    node->parent = fake_;
  }
}

template< class Key, class Value, class Compare >
void petrov::AvlTree< Key, Value, Compare >::clear(Node* node) noexcept
{
  if (node == nullptr) {
    return;
  }
  clear(node->left);
  clear(node->right);
  delete node;
}

template< class Key, class Value, class Compare >
void petrov::AvlTree< Key, Value, Compare >::clear() noexcept
{
  clear(root());
  fake_->left = nullptr;
  size_ = 0;
}

template< class Key, class Value, class Compare >
typename petrov::AvlTree< Key, Value, Compare >::Node*
petrov::AvlTree< Key, Value, Compare >::copy(Node* node, Node* parent)
{
  if (node == nullptr) {
    return nullptr;
  }
  Node* newNode = new Node(node->data.first, node->data.second, parent);
  newNode->height = node->height;
  newNode->left = copy(node->left, newNode);
  newNode->right = copy(node->right, newNode);
  return newNode;
}

template< class Key, class Value, class Compare >
std::size_t petrov::AvlTree< Key, Value, Compare >::count(Node* node) const noexcept
{
  if (node == nullptr) {
    return 0;
  }
  return count(node->left) + count(node->right) + 1;
}

template< class Key, class Value, class Compare >
typename petrov::AvlTree< Key, Value, Compare >::Node*
petrov::AvlTree< Key, Value, Compare >::findNode(const Key& key) const noexcept
{
  Node* current = root();
  while (current != nullptr) {
    if (compare_(key, current->data.first)) {
      current = current->left;
    } else if (compare_(current->data.first, key)) {
      current = current->right;
    } else {
      return current;
    }
  }
  return nullptr;
}

template< class Key, class Value, class Compare >
typename petrov::AvlTree< Key, Value, Compare >::Node*
petrov::AvlTree< Key, Value, Compare >::minimum(Node* node) const noexcept
{
  if (node == nullptr) {
    return nullptr;
  }
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template< class Key, class Value, class Compare >
int petrov::AvlTree< Key, Value, Compare >::nodeHeight(Node* node) const noexcept
{
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

template< class Key, class Value, class Compare >
void petrov::AvlTree< Key, Value, Compare >::updateHeight(Node* node) noexcept
{
  const int leftHeight = nodeHeight(node->left);
  const int rightHeight = nodeHeight(node->right);
  node->height = std::max(leftHeight, rightHeight) + 1;
}

template< class Key, class Value, class Compare >
int petrov::AvlTree< Key, Value, Compare >::balanceFactor(Node* node) const noexcept
{
  if (node == nullptr) {
    return 0;
  }
  return nodeHeight(node->left) - nodeHeight(node->right);
}


