#ifndef TREE_NODE_HXX
#define TREE_NODE_HXX

#include <iostream>
#include <memory>

template <class T>
struct TreeNode
{
  TreeNode() : data{}, left{ nullptr }, right{ nullptr } {}
  TreeNode( T data ) : data{ data }, left{ nullptr }, right{ nullptr } {}

  // Deleting the copy constructor and copy-assign operator since a Node
  // contains a unique_ptr. Since, unique_ptr is not copy-able then logically
  // Nodes can not be copied.
  TreeNode( const TreeNode<T>& other ) = delete;
  TreeNode<T>& operator=( const TreeNode<T>& other ) = delete;

  TreeNode( TreeNode<T>&& other ) noexcept
  {
    data = std::move( other.data );
    left = std::move( other.left );
    right = std::move( other.right );
  }

  TreeNode<T>& operator=( TreeNode<T>&& other ) noexcept
  {
    data = std::move( other.data );
    left = std::move( other.left );
    right = std::move( other.right );
  }

  T data;
  std::unique_ptr<TreeNode<T>> left;
  std::unique_ptr<TreeNode<T>> right;
};

template <class T>
std::ostream& operator<<( std::ostream& os, const TreeNode<T>& node )
{
  os << "[ ";

  os << "Data: " << node.data << ", "
     << "Parent: " << node.parent << ", "
     << "Left: " << node.left.get() << ", "
     << "Right: " << node.right.get();

  os << " ]";
  return os;
}

#endif
