#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <cstddef>
#include <functional>
#include <utility>

namespace petrov
{
  template< class Key, class Value >
  class AvlConstIterator;

  template< class Key, class Value >
  class AvlIterator;

  template< class Key, class Value, class Compare = std::less< Key > >
  class AvlTree
  {
  public:
    using value_type = std::pair< const Key, Value >;
    using iterator = AvlIterator< Key, Value >;
    using const_iterator = AvlConstIterator< Key, Value >;

    AvlTree();
    AvlTree(const AvlTree& other);
    AvlTree(AvlTree&& other) noexcept;
    ~AvlTree();

    AvlTree& operator=(const AvlTree& other);
    AvlTree& operator=(AvlTree&& other) noexcept;

    void push(const Key& key, const Value& value);
    Value& get(const Key& key);
    const Value& get(const Key& key) const;
    Value drop(const Key& key);

    bool has(const Key& key) const noexcept;
    bool empty() const noexcept;
    std::size_t size() const noexcept;
    void clear() noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    iterator find(const Key& key) noexcept;
    const_iterator find(const Key& key) const noexcept;

    std::size_t height() const noexcept;

  private:
    struct Node
    {
      value_type data;
      Node* parent;
      Node* left;
      Node* right;
      int height;

      Node(const Key& key, const Value& value, Node* parentNode);
    };

    Node* fake_;
    std::size_t size_;
    Compare compare_;

    Node* root() const noexcept;
    void setRoot(Node* node) noexcept;

    Node* findNode(const Key& key) const noexcept;
    Node* minimum(Node* node) const noexcept;

    void clear(Node* node) noexcept;
    Node* copy(Node* node, Node* parent);
    std::size_t count(Node* node) const noexcept;

    int nodeHeight(Node* node) const noexcept;
    void updateHeight(Node* node) noexcept;
    int balanceFactor(Node* node) const noexcept;

    Node* rotateLeftNode(Node* node);
    Node* rotateRightNode(Node* node);
    void rebalanceFrom(Node* node);

    template< class K, class V >
    friend class AvlConstIterator;

    template< class K, class V >
    friend class AvlIterator;
  };
}
#endif
