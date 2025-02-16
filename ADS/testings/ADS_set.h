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
        KEY_NODE,
        DATA_NODE
    };
    enum class InsertState
    {
        OK,
        DUPLICATE,
        SPLIT
    };
    enum class EraseState
    {
        SUCCESS,
        NOT_FOUND,
        TRIGGER_MERGE
    };

    struct NodeBase;
    struct KeyNode;
    struct DataNode;

    using link = NodeBase *;

    static constexpr std::equal_to<key_type> eq = key_equal{};

    link root;
    size_type sz{};

public:
    ADS_set() : root{new DataNode()}, sz{0} {} // PH1
    ADS_set(std::initializer_list<key_type> ilist) : root{new DataNode()}, sz{0}
    {
        for (const key_type &elem : ilist)
        {
            insert(elem);
        }
    } // PH1
    template <typename InputIt>
    ADS_set(InputIt first, InputIt last) : root{new DataNode()}, sz{0}
    {
        for (InputIt it = first; it != last; ++it)
        {
            insert(*it);
        }
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
        {
            insert(elem);
        }
    } // PH1
    std::pair<iterator, bool> insert(const key_type &key)
    {
        std::pair<iterator, InsertState> result{root->add_elem(key)};
        switch (result.second)
        {
        case InsertState::OK:
            ++sz;
            return std::pair<iterator, bool>(result.first, true);
        case InsertState::DUPLICATE:
            return std::pair<iterator, bool>(result.first, false);
        case InsertState::SPLIT:
            std::pair<link, const key_type *> splitres{root->split()};
            const key_type &new_index{splitres.second ? *splitres.second : splitres.first->values[0]};
            root = new KeyNode(new_index, root, splitres.first);
            ++sz;
            return std::pair<iterator, bool>(root->find(key), true);
        }
        return {};
    }

    template <typename InputIt>
    void insert(InputIt first, InputIt last)
    {
        for (InputIt it = first; it != last; ++it)
        {
            insert(*it);
        }
    } // PH1

    void clear()
    {
        delete root;
        root = new DataNode();
        sz = 0;
    }
    size_type erase(const key_type &key)
    {
        EraseState result{root->remove_elem(key)};
        switch (result)
        {
        case EraseState::SUCCESS:
            --sz;
            return 1;
        case EraseState::NOT_FOUND:
            return 0;
        case EraseState::TRIGGER_MERGE:
            if (root->node_size == 0)
            {
                if (root->type() == NodeType::KEY_NODE)
                {
                    std::pair<key_type *, link *> elems = root->get_all();
                    delete root;
                    root = elems.second[0];
                    delete[] elems.first;
                    delete[] elems.second;
                }
                else
                {
                    delete root;
                    root = new DataNode();
                }
            }
            --sz;
            return 1;
        }
        return 0;
    }

    size_type count(const key_type &key) const
    {
        if (root->find(key) != end())
        {
            return 1;
        }
        else
        {
            return 0;
        }
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
        root->dump(o, 0);
        o << std::endl;
    }

    bool operator==(const ADS_set &rhs) const
    {
        if (sz != rhs.sz)
        {
            return false;
        }
        for (const_iterator itl = begin(), itr = rhs.begin(); itl != end(); ++itl, ++itr)
        {
            if (!eq(*itl, *itr))
            {
                return false;
            }
        }
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
    DataNode *current_node;
    size_type position;

public:
    Iterator() : current_node{nullptr}, position{0} {}
    explicit Iterator(DataNode *cur, size_type pos) : current_node{cur}, position{pos} {}
    reference operator*() const
    {
        return current_node->values[position];
    }
    pointer operator->() const
    {
        return current_node->values + position;
    }
    Iterator &operator++()
    {
        if (current_node)
        {
            if (position + 1 == current_node->node_size)
            {
                current_node = current_node->next_node;
                position = 0;
            }
            else
            {
                ++position;
            }
        }
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator temp{*this};
        this->operator++();
        return temp;
    }
    bool operator==(const Iterator &rhs) const
    {
        return current_node == rhs.current_node && position == rhs.position;
    }
    bool operator!=(const Iterator &rhs) const
    {
        return !(current_node == rhs.current_node && position == rhs.position);
    }
};

template <typename Key, size_t N>
void swap(ADS_set<Key, N> &lhs, ADS_set<Key, N> &rhs) { lhs.swap(rhs); }

template <typename Key, size_t N>
struct ADS_set<Key, N>::NodeBase
{
    static constexpr size_type MaxElements{N * 2};
    static constexpr std::less<key_type> compare = key_compare{};

    key_type *values;
    size_type node_size;

    explicit NodeBase(size_type s = 0) : values{new key_type[MaxElements + 1]}, node_size{s} {}
    NodeBase(const key_type *v, size_type s) : values{new key_type[MaxElements + 1]}, node_size{s}
    {
        for (size_type i = 0; i < s; ++i)
        {
            values[i] = v[i];
        }
    }

    int find_position(const key_type &element)
    {
        if (node_size == 0 || compare(element, values[0]))
        {
            return -1;
        }
        for (size_type i = 1; i < node_size; ++i)
        {
            if (compare(element, values[i]))
            {
                if (compare(values[i - 1], element))
                {
                    return invert(static_cast<int>(i));
                }
                else
                {
                    return i - 1;
                }
            }
        }
        if (!compare(values[node_size - 1], element))
        {
            return node_size - 1;
        }
        else
        {
            return invert(node_size);
        }
    }

    inline size_type find_position_inverted(const key_type &element)
    {
        int pos{find_position(element)};
        if (pos < 0)
        {
            return invert(pos);
        }
        else
        {
            return pos;
        }
    }

    virtual void insert_at_position(const key_type &element, size_type insert_position)
    {
        for (size_type i = node_size; i > insert_position; --i)
        {
            values[i] = values[i - 1];
        }
        values[insert_position] = element;
        ++node_size;
    }

    virtual void erase_at_position(size_type at)
    {
        for (size_type i{at}; i < node_size - 1; ++i)
        {
            values[i] = values[i + 1];
        }
        --node_size;
    }

    virtual NodeType type() = 0;
    virtual iterator begin_it() = 0;
    virtual iterator find(const key_type &element) = 0;
    virtual std::pair<iterator, InsertState> add_elem(const key_type &element) = 0;
    virtual std::pair<link, const key_type *> split(size_type split_at) = 0;

    virtual EraseState remove_elem(const key_type &elem) = 0;
    virtual std::pair<key_type *, link *> get_all() = 0;
    virtual void prepare_merge(const key_type &pulled_down) = 0;
    virtual void merge(link neighbour) = 0;

    std::pair<link, const key_type *> split()
    {
        return split((node_size - 1) / 2);
    }

    virtual ~NodeBase() { delete[] values; }

    virtual void dump(std::ostream &o, size_type level)
    {
        if (level == 0)
        {
            o << "[ROOT]";
        }
        else
        {
            o << "[level " << level << "]";
        }
        o << " [";
        switch (type())
        {
        case NodeType::KEY_NODE:
            o << "KEY_NODE";
            break;
        case NodeType::DATA_NODE:
            o << "DATA_NODE";
            break;
        }
        o << "]";
        for (size_type i{0}; i < this->node_size; ++i)
        {
            o << " " << this->values[i];
        }
    }
};

template <typename Key, size_t N>
struct ADS_set<Key, N>::DataNode : public NodeBase
{
    DataNode *next_node;

    DataNode() : NodeBase(), next_node{nullptr} {}

    DataNode(const key_type *v, size_type s, DataNode *n = nullptr) : NodeBase(v, s), next_node(n) {}

    NodeType type() override
    {
        return NodeType::DATA_NODE;
    }

    iterator begin_it() override
    {
        if (this->node_size == 0)
        {
            return Iterator();
        }
        return Iterator(this, 0);
    }

    iterator find(const key_type &element) override
    {
        int pos = this->find_position(element);
        if (pos < 0)
        {
            return Iterator();
        }
        return Iterator(this, pos);
    }

    std::pair<iterator, InsertState> add_elem(const key_type &element) override
    {
        int pos = this->find_position(element);
        if (pos >= 0)
        {
            return std::pair<iterator, InsertState>(Iterator(this, pos), InsertState::DUPLICATE);
        }
        size_type insert_pos = static_cast<size_type>(invert(pos));
        this->insert_at_position(element, insert_pos);
        if (this->node_size <= NodeBase::MaxElements)
        {
            return std::pair<iterator, InsertState>(Iterator(this, insert_pos), InsertState::OK);
        }
        else
        {
            return std::pair<iterator, InsertState>(Iterator(this, insert_pos), InsertState::SPLIT);
        }
    }

    std::pair<link, const key_type *> split(size_type split_at) override
    {
        key_type right_values[NodeBase::MaxElements + 1];
        size_type right_node_size = this->node_size - split_at - 1;
        for (size_type i = 0; i < right_node_size; ++i)
        {
            right_values[i] = this->values[split_at + 1 + i];
        }
        this->node_size = split_at + 1;
        DataNode *right_node = new DataNode(right_values, right_node_size, next_node);
        next_node = right_node;
        return std::pair<link, key_type *>(right_node, nullptr);
    }

    void insert_at_position(const key_type &element, size_type insert_position) override
    {
        for (size_type i = this->node_size; i > insert_position; --i)
        {
            this->values[i] = this->values[i - 1];
        }
        this->values[insert_position] = element;
        ++this->node_size;
    }

    EraseState remove_elem(const key_type &elem) override
    {
        int pos{this->find_position(elem)};
        if (pos < 0)
            return EraseState::NOT_FOUND;
        this->erase_at_position(static_cast<size_type>(pos));

        return this->node_size >= N ? EraseState::SUCCESS : EraseState::TRIGGER_MERGE;
    }

    std::pair<key_type *, link *> get_all() override
    {
        key_type *vals = new key_type[this->node_size];
        for (size_type i{0}; i < this->node_size; ++i)
        {
            vals[i] = this->values[i];
        }
        return std::pair<key_type *, link *>(vals, nullptr);
    }

    void prepare_merge(const key_type &) override {}

    void merge(link neighbour) override
    {
        std::pair<key_type *, link *> elems{neighbour->get_all()};
        size_type prev_size{this->node_size};

        for (size_type i{0}; i < neighbour->node_size; ++i)
        {
            this->values[i + prev_size] = elems.first[i];
        }
        this->node_size += neighbour->node_size;
        delete[] elems.first;

        if (next_node == neighbour)
        {
            next_node = next_node->next_node;
        }
    }
};

template <typename Key, size_t N>
struct ADS_set<Key, N>::KeyNode : public NodeBase
{
    link *child_nodes;
    bool owns_children;

    KeyNode() : NodeBase(), child_nodes{new link[NodeBase::MaxElements + 2]}, owns_children{true}
    {
        child_nodes[0] = new DataNode();
    }

    KeyNode(const key_type *v, const link *ch, size_type s) : NodeBase(v, s), child_nodes{new link[NodeBase::MaxElements + 2]}, owns_children{true}
    {
        for (size_type i = 0; i <= s; ++i)
        {
            child_nodes[i] = ch[i];
        }
    }

    KeyNode(const key_type &value, link left_child, link right_child) : NodeBase(1), child_nodes{new link[NodeBase::MaxElements + 2]}, owns_children{true}
    {
        this->values[0] = value;
        child_nodes[0] = left_child;
        child_nodes[1] = right_child;
    }

    NodeType type() override
    {
        return NodeType::KEY_NODE;
    }

    inline size_type find_child_index(const key_type &element)
    {
        int pos{this->find_position(element)};
        if (pos < -1)
        {
            return invert(pos);
        }
        else
        {
            return (pos + 1);
        }
    }

    iterator begin_it() override
    {
        return child_nodes[0]->begin_it();
    }

    iterator find(const key_type &element) override
    {
        size_type child_index{find_child_index(element)};
        return child_nodes[child_index]->find(element);
    }

    std::pair<iterator, InsertState> add_elem(const key_type &element) override
    {
        size_type child_index = find_child_index(element);
        std::pair<iterator, InsertState> result = child_nodes[child_index]->add_elem(element);
        if (result.second == InsertState::SPLIT)
        {
            std::pair<link, const key_type *> split_result = child_nodes[child_index]->split();
            const key_type &new_key{split_result.second ? *split_result.second : split_result.first->values[0]};
            size_type new_position = this->find_position_inverted(new_key);
            this->insert_at_position(new_key, new_position);
            child_nodes[new_position + 1] = split_result.first;
            if (this->node_size <= NodeBase::MaxElements)
            {
                return std::pair<iterator, InsertState>(find(element), InsertState::OK);
            }
            else
            {
                return std::pair<iterator, InsertState>(find(element), InsertState::SPLIT);
            }
        }
        return result;
    }

    std::pair<link, const key_type *> split(size_type split_at) override
    {
        key_type right_keys[NodeBase::MaxElements + 1];
        link right_child_nodes[NodeBase::MaxElements + 2];
        size_type right_node_size = this->node_size - split_at - 1;
        for (size_type i = 0; i < right_node_size; ++i)
        {
            right_keys[i] = this->values[split_at + 1 + i];
            right_child_nodes[i] = child_nodes[split_at + 1 + i];
        }
        right_child_nodes[right_node_size] = child_nodes[this->node_size];
        this->node_size = split_at;
        return std::pair<link, key_type *>(new KeyNode(right_keys, right_child_nodes, right_node_size), this->values + split_at);
    }

    void insert_at_position(const key_type &element, size_type insert_position) override
    {
        for (size_type i = this->node_size; i > insert_position; --i)
        {
            this->values[i] = this->values[i - 1];
            this->child_nodes[i + 1] = this->child_nodes[i];
        }
        this->values[insert_position] = element;
        ++this->node_size;
    }

    void erase_at_position(size_type at) override
    {
        delete child_nodes[at + 1];
        for (size_type i{at}; i < this->node_size - 1; ++i)
        {
            this->values[i] = this->values[i + 1];
            this->child_nodes[i + 1] = this->child_nodes[i + 2];
        }
        --this->node_size;
    }

    EraseState remove_elem(const key_type &elem) override
    {
        size_type childpos{find_child_index(elem)};

        EraseState result{child_nodes[childpos]->remove_elem(elem)};
        if (result == EraseState::TRIGGER_MERGE)
        {
            if constexpr (N > 1)
            {
                childpos = childpos < 1 ? 1 : childpos;
                key_type &id = this->values[childpos - 1];
                link left{child_nodes[childpos - 1]};
                link right{child_nodes[childpos]};
                size_type totalsize{left->node_size + right->node_size + (right->type() == NodeType::KEY_NODE ? 1 : 0)};
                if (totalsize > NodeBase::MaxElements)
                {
                    size_type split_at{(totalsize - 1) / 2};
                    std::pair<link, const key_type *> splitres;
                    if (split_at < left->node_size)
                    {
                        splitres = left->split(split_at);
                        splitres.first->prepare_merge(id);
                        splitres.first->merge(right);
                    }
                    else
                    {
                        splitres = right->split(split_at - left->node_size);
                        left->prepare_merge(id);
                        left->merge(right);
                    }
                    key_type new_index{splitres.second ? *splitres.second : splitres.first->values[0]};
                    delete child_nodes[childpos];
                    child_nodes[childpos] = splitres.first;
                    id = new_index;
                }
                else
                {
                    left->prepare_merge(id);
                    left->merge(right);

                    this->erase_at_position(childpos - 1);
                }
            }
            else
            {
                if (childpos == 0)
                {
                    ++childpos;
                }

                child_nodes[childpos - 1]->prepare_merge(this->values[childpos - 1]);
                child_nodes[childpos - 1]->merge(child_nodes[childpos]);
                if (child_nodes[childpos - 1]->node_size > NodeBase::MaxElements)
                {
                    std::pair<link, const key_type *> splitres{child_nodes[childpos - 1]->split(1)};
                    delete child_nodes[childpos];
                    child_nodes[childpos] = splitres.first;
                    this->values[childpos - 1] = splitres.second ? *splitres.second : splitres.first->values[0];
                }
                else
                {
                    this->erase_at_position(childpos - 1);
                }
            }
            return this->node_size >= N ? EraseState::SUCCESS : EraseState::TRIGGER_MERGE;
        }

        return result;
    }

    std::pair<key_type *, link *> get_all() override
    {
        key_type *vals = new key_type[this->node_size];
        link *links = new link[this->node_size + 1];
        for (size_type i{0}; i < this->node_size; ++i)
        {
            vals[i] = this->values[i];
            links[i] = child_nodes[i];
        }
        links[this->node_size] = child_nodes[this->node_size];
        owns_children = false;

        return std::pair<key_type *, link *>(vals, links);
    }

    void prepare_merge(const key_type &pulled_down) override
    {
        this->values[this->node_size] = pulled_down;
        ++this->node_size;
    }

    void merge(link neighbour) override
    {
        std::pair<key_type *, link *> elems{neighbour->get_all()};
        size_type prev_size{this->node_size};
        for (size_type i{0}; i < neighbour->node_size; ++i)
        {
            child_nodes[i + prev_size] = elems.second[i];
            this->values[i + prev_size] = elems.first[i];
        }
        this->node_size += neighbour->node_size;
        child_nodes[this->node_size] = elems.second[neighbour->node_size];

        delete[] elems.first;
        delete[] elems.second;
    }

    ~KeyNode() override
    {
        if (owns_children)
        {
            for (size_type i = 0; i <= this->node_size; ++i)
            {
                delete child_nodes[i];
            }
        }
        delete[] child_nodes;
    }

    void dump(std::ostream &o, size_type level) override
    {
        NodeBase::dump(o, level);
        for (size_type i = 0; i <= this->node_size; ++i)
        {
            o << "\n\t";
            child_nodes[i]->dump(o, level + 1);
        }
    }
};

#endif // ADS_SET_H
