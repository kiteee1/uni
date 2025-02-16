#ifndef ADS_SET_H
#define ADS_SET_H

#include <functional>
#include <algorithm>
#include <iostream>
#include <stdexcept>

inline int invert(int n)
{
  return -(n + 1);
}

template <typename Key, size_t N = 2>
class ADS_set
{
public:
  class Iterator;
  using value_type = Key;
  using key_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;
  using const_iterator = Iterator;
  using iterator = const_iterator;
  using key_compare = std::less<key_type>;   // B+-Tree
  using key_equal = std::equal_to<key_type>; // Hashing

private:
  enum class NodeType
  {
    INTERNAL,
    EXTERNAL
  };
  enum class InsertState
  {
    SUCCESS,
    EXISTS,
    TRIGGER_SPLIT
  };
  enum class EraseState
  {
    SUCCESS,
    NOT_FOUND,
    TRIGGER_MERGE
  };

  struct Node;
  struct InternalNode;
  struct ExternalNode;

  using link = Node *;

  static constexpr std::equal_to<key_type> eq = key_equal{};

  link root;
  size_type sz{};

public:
  ADS_set() : root{new ExternalNode()}, sz{0} {} // PH1
  ADS_set(std::initializer_list<key_type> ilist) : root{new ExternalNode()}, sz{0}
  {
    for (const key_type &elem : ilist)
      insert(elem);
  } // PH1
  template <typename InputIt>
  ADS_set(InputIt first, InputIt last) : root{new ExternalNode()}, sz{0}
  {
    for (InputIt it = first; it != last; ++it)
      insert(*it);
  } // PH1
  ADS_set(const ADS_set &other) : ADS_set(other.begin(), other.end()) {}

  ~ADS_set()
  {
    delete root;
    sz = 0;
  }

  ADS_set &operator=(const ADS_set &other)
  {
    clear();
    insert(other.begin(), other.end());
    return *this;
  }
  ADS_set &operator=(std::initializer_list<key_type> ilist)
  {
    clear();
    insert(ilist.begin(), ilist.end());
    return *this;
  }

  size_type size() const
  {
    return sz;
  } // PH1
  bool empty() const
  {
    return size() == 0;
  } // PH1

  void insert(std::initializer_list<key_type> ilist)
  {
    for (const auto &elem : ilist)
      insert(elem);
  } // PH1
  std::pair<iterator, bool> insert(const key_type &key)
  {
    std::pair<iterator, InsertState> result{root->add_elem(key)};
    switch (result.second)
    {
    case InsertState::SUCCESS:
      ++sz;
      return std::pair<iterator, bool>(result.first, true);
    case InsertState::EXISTS:
      return std::pair<iterator, bool>(result.first, false);
    case InsertState::TRIGGER_SPLIT:
      std::pair<link, const key_type *> splitres{root->split()};
      const key_type &new_index{splitres.second ? *splitres.second : splitres.first->values[0]};
      root = new InternalNode(new_index, root, splitres.first);
      ++sz;
      return std::pair(root->find(key), true);
    }
    return {};
  }

  template <typename InputIt>
  void insert(InputIt first, InputIt last)
  {
    for (InputIt it = first; it != last; ++it)
      insert(*it);
  } // PH1

  void clear()
  {
    delete root;
    root = new ExternalNode();
    sz = 0;
  }
  // size_type erase(const key_type &key);

  size_type count(const key_type &key) const
  {
    return root->find(key) != end() ? 1 : 0;
  } // PH1
  iterator find(const key_type &key) const
  {
    return root->find(key);
  }

  void swap(ADS_set &other)
  {
    std::swap(sz, other.sz);
    std::swap(root, other.root);
  }

  const_iterator begin() const
  {
    return root->begin_it();
  }
  const_iterator end() const
  {
    return Iterator();
  }

  void dump(std::ostream &o = std::cerr) const
  {
    o << "ADS_set<" << typeid(key_type).name() << ", " << N << ">, size: " << sz << "\n";
    for (iterator it = begin(); it != end(); ++it)
      o << " " << *it;
    o << "\n";
    root->dump(o, 0);
    o << std::endl;
  }

  bool operator==(const ADS_set &rhs) const
  {
    if (sz != rhs.sz)
      return false;
    for (const_iterator itl = begin(), itr = rhs.begin(); itl != end(); ++itl, ++itr)
      if (!eq(*itl, *itr))
        return false;
    return true;
  }
  bool operator!=(const ADS_set &rhs) const
  {
    return !operator==(rhs);
  }
};

template <typename Key, size_t N>
class ADS_set<Key, N>::Iterator
{
public:
  using value_type = Key;
  using difference_type = std::ptrdiff_t;
  using reference = const value_type &;
  using pointer = const value_type *;
  using iterator_category = std::forward_iterator_tag;

private:
  ExternalNode *current;
  size_type pos;

public:
  Iterator() : current{nullptr}, pos{0} {}
  explicit Iterator(ExternalNode *cur, size_type p) : current{cur}, pos{p} {}
  reference operator*() const
  {
    return current->values[pos];
  }
  pointer operator->() const
  {
    return current->values + pos;
  }
  Iterator &operator++()
  {
    if (current)
    {
      if (pos + 1 == current->size)
      {
        current = current->next;
        pos = 0;
      }
      else
        ++pos;
    }
    return *this;
  }
  Iterator operator++(int)
  {
    Iterator old{*this};
    this->operator++();
    return old;
  }
  bool operator==(const Iterator &rhs) const
  {
    return current == rhs.current && pos == rhs.pos;
  }
  bool operator!=(const Iterator &rhs) const
  {
    return current != rhs.current || pos != rhs.pos;
  }
};

template <typename Key, size_t N>
void swap(ADS_set<Key, N> &lhs, ADS_set<Key, N> &rhs) { lhs.swap(rhs); }

template <typename Key, size_t N>
struct ADS_set<Key, N>::Node
{
  static constexpr size_type M{N * 2};
  static constexpr std::less<key_type> compare = key_compare{};

  key_type *values;
  size_type size;
  int findpos(const key_type &elem)
  {
    if (size == 0 || compare(elem, values[0]))
      return -1;
    for (size_type i = 1; i < size; ++i)
      if (compare(elem, values[i]))
        return compare(values[i - 1], elem) ? invert(static_cast<int>(i)) : i - 1;
    return !compare(values[size - 1], elem) ? size - 1 : invert(size);
  }
  inline size_type findpos_autoinvert(const key_type &elem)
  {
    int pos{findpos(elem)};
    return pos < 0 ? invert(pos) : pos;
  }
  virtual void insert_at(const key_type &elem, size_type ins)
  {
    for (size_type i = size; i > ins; --i)
      values[i] = values[i - 1];
    values[ins] = elem;
    ++size;
  }
  explicit Node(size_type s = 0) : values{new key_type[M + 1]}, size{s} {}
  Node(const key_type *v, size_type s) : values{new key_type[M + 1]}, size{s}
  {
    for (size_type i = 0; i < s; ++i)
      values[i] = v[i];
  }

  virtual NodeType type() = 0;
  virtual iterator begin_it() = 0;
  virtual iterator find(const key_type &elem) = 0;
  virtual std::pair<iterator, InsertState> add_elem(const key_type &elem) = 0;
  virtual std::pair<link, const key_type *> split(size_type split_at) = 0;
  std::pair<link, const key_type *> split()
  {
    return split((size - 1) / 2);
  }
  virtual ~Node() { delete[] values; }
  virtual void dump(std::ostream &o, size_type level)
  {
    if (level == 0)
      o << "[ROOT]";
    else
      o << "[" << level << "]";
    o << " [";
    switch (type())
    {
    case NodeType::INTERNAL:
      o << "INTERNAL";
      break;
    case NodeType::EXTERNAL:
      o << "EXTERNAL";
      break;
    }
    o << " <" << this->size << "/" << Node::M << "> (" << (this->size * 100.0) / Node::M << "%)]";
    for (size_type i{0}; i < this->size; ++i)
      o << " (" << i << ")" << this->values[i];
  }
};
template <typename Key, size_t N>
struct ADS_set<Key, N>::InternalNode : public Node
{
  link *children;
  bool ownership;

  InternalNode() : Node(), children{new link[Node::M + 2]}, ownership{true}
  {
    children[0] = new ExternalNode();
  }
  InternalNode(const key_type *v, const link *ch, size_type s) : Node(v, s), children{new link[Node::M + 2]}, ownership{true}
  {
    for (size_type i = 0; i <= s; ++i)
      children[i] = ch[i];
  }
  InternalNode(const key_type &value, link left, link right) : Node(1), children{new link[Node::M + 2]}, ownership{true}
  {
    this->values[0] = value;
    children[0] = left;
    children[1] = right;
  }
  inline size_type find_child_pos(const key_type &elem)
  {
    int pos{this->findpos(elem)};
    return static_cast<size_type>(pos < -1 ? invert(pos) : (pos + 1));
  }
  void insert_at(const key_type &elem, size_type ins) override
  {
    for (size_type i = this->size; i > ins; --i)
    {
      this->values[i] = this->values[i - 1];
      this->children[i + 1] = this->children[i];
    }
    this->values[ins] = elem;
    ++this->size;
  }
  NodeType type() override
  {
    return NodeType::INTERNAL;
  }
  iterator begin_it() override
  {
    return children[0]->begin_it();
  }
  iterator find(const key_type &elem) override
  {
    size_type childpos{find_child_pos(elem)};
    return children[childpos]->find(elem);
  }
  std::pair<iterator, InsertState> add_elem(const key_type &elem) override
  {
    size_type childpos = find_child_pos(elem);
    std::pair<iterator, InsertState> result = children[childpos]->add_elem(elem);
    if (result.second == InsertState::TRIGGER_SPLIT)
    {
      std::pair<link, const key_type *> splitres = children[childpos]->split();
      const key_type &new_index{splitres.second ? *splitres.second : splitres.first->values[0]};
      size_type new_pos = this->findpos_autoinvert(new_index);
      this->insert_at(new_index, new_pos);
      children[new_pos + 1] = splitres.first;
      return std::pair<iterator, InsertState>(find(elem), this->size <= Node::M ? InsertState::SUCCESS : InsertState::TRIGGER_SPLIT);
    }
    return result;
  }
  std::pair<link, const key_type *> split(size_type split_at) override
  {
    key_type right[Node::M + 1];
    link right_children[Node::M + 2];
    size_type right_size = this->size - split_at - 1;
    for (size_type i = 0; i < right_size; ++i)
    {
      right[i] = this->values[split_at + 1 + i];
      right_children[i] = children[split_at + 1 + i];
    }
    right_children[right_size] = children[this->size];
    this->size = split_at;
    return std::pair<link, key_type *>(new InternalNode(right, right_children, right_size), this->values + split_at);
  }
  ~InternalNode() override
  {
    if (ownership)
      for (size_type i = 0; i <= this->size; ++i)
        delete children[i];
    delete[] children;
  }
  void dump(std::ostream &o, size_type level) override
  {
    Node::dump(o, level);
    for (size_type i = 0; i <= this->size; ++i)
    {
      o << "\n\t" << i << ". ";
      children[i]->dump(o, level + 1);
    }
  }
};
template <typename Key, size_t N>
struct ADS_set<Key, N>::ExternalNode : public Node
{
  ExternalNode *next;

  ExternalNode() : Node(), next{nullptr} {}
  ExternalNode(const key_type *v, size_type s, ExternalNode *n = nullptr) : Node(v, s), next(n) {}

  NodeType type() override
  {
    return NodeType::EXTERNAL;
  }
  iterator begin_it() override
  {
    if (this->size == 0)
      return Iterator();
    return Iterator(this, 0);
  }
  iterator find(const key_type &elem) override
  {
    int pos = this->findpos(elem);
    if (pos < 0)
      return Iterator();
    return Iterator(this, pos);
  }
  std::pair<iterator, InsertState> add_elem(const key_type &elem) override
  {
    int pos = this->findpos(elem);
    if (pos >= 0)
      return std::pair<iterator, InsertState>(Iterator(this, pos), InsertState::EXISTS);
    size_type inv_pos = static_cast<size_type>(invert(pos));
    this->insert_at(elem, inv_pos);
    return std::pair<iterator, InsertState>(Iterator(this, inv_pos), this->size <= Node::M ? InsertState::SUCCESS : InsertState::TRIGGER_SPLIT);
  }
  std::pair<link, const key_type *> split(size_type split_at) override
  {
    key_type right[Node::M + 1];
    size_type right_size = this->size - split_at - 1;
    for (size_type i = 0; i < right_size; ++i)
      right[i] = this->values[split_at + 1 + i];
    this->size = split_at + 1;
    ExternalNode *right_node = new ExternalNode(right, right_size, next);
    next = right_node;
    return std::pair<link, key_type *>(right_node, nullptr);
  }
};
#endif // ADS_SET_H
