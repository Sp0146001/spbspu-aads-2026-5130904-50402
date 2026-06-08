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

