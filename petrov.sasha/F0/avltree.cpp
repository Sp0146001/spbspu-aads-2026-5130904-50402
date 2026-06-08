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

