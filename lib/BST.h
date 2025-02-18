#pragma once
#include <iostream>

enum class TraverseTag{ In, Pre, Post, };

template<typename T>
struct Node {
    T key;
    Node* left;
    Node* right;
    Node* parent;

    Node() : left(nullptr), right(nullptr), parent(nullptr) {}
};

template<typename T, typename Allocator = std::allocator<Node<T> > > 
class BST {
public:
    typedef T value_type;
    typedef const T const_value_type;
    typedef T key_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef Allocator allocator_type;
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Node<T> node_type;
    typedef Node<T>* pointer;

    template<TraverseTag tag>
    class iterator_base {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        typedef TraverseTag value_type;
        typedef Node<T>* pointer;
        typedef Node<T>& reference;
        typedef const Node<T>* const_pointer;
        typedef const Node<T>& const_reference;

        explicit iterator_base(pointer node) : ptr_(node) {}

        iterator_base(const iterator_base& other) {
            ptr_ = other.ptr_;
        }

        ~iterator_base() = default;

        iterator_base& operator++() {
            if (tag == TraverseTag::In) {
                if (ptr_->right != nullptr) {
                    ptr_ = ptr_->right;
                    while (ptr_->left != nullptr) {
                        ptr_ = ptr_->left;
                    }
                } else {
                    pointer cur = ptr_->parent;
                    while (cur != nullptr && ptr_ == cur->right) {
                        ptr_ = cur;
                        cur = cur->parent;
                    }
                    ptr_ = cur;
                }

                return *this;
            }
            if (tag == TraverseTag::Pre) {
                if (ptr_->left != nullptr) {
                    ptr_ = ptr_->left;
                } else if (ptr_->right != nullptr) {
                    ptr_ = ptr_->right;
                } else {
                    pointer cur = ptr_->parent;
                    while (cur != nullptr && (cur->right == nullptr || cur->right == ptr_)) {
                        ptr_ = cur;
                        cur = cur->parent;
                    }
                    cur = ptr_->parent;
                    if (cur != nullptr) {
                        ptr_ = cur->right;
                    } else {
                        ptr_ = nullptr;
                    }
                }

                return *this;
            }
            if (tag == TraverseTag::Post) {
                if (ptr_->parent == nullptr) {
                    ptr_ = nullptr;
                    return *this;
                }
                pointer parent = ptr_->parent;
                if (parent->right == nullptr || parent->right == ptr_) {
                    ptr_ = parent;
                } else {
                    pointer next = parent->right;
                    while (next->left != nullptr || next->right != nullptr) {
                        next = next->left != nullptr ? next->left : next->right;
                    }
                    ptr_ = next;
                }

                return *this;
            }
            
            return *this;
        }

        iterator_base& operator--() {
            if (tag == TraverseTag::In) {
                if (ptr_->left != nullptr) {
                    ptr_ = ptr_->left;
                    while (ptr_->right != nullptr) {
                        ptr_ = ptr_->right;
                    }
                } else {
                    pointer cur = ptr_->parent;
                    while (cur != nullptr && ptr_ == cur->left) {
                        ptr_ = cur;
                        cur = cur->parent;
                    }
                    ptr_ = cur;
                }

                return *this;
            }
            if (tag == TraverseTag::Pre) {
                if (ptr_->parent == nullptr) {
                    ptr_ = nullptr;

                    return *this;
                }
                pointer cur = ptr_->parent;
                if (ptr_->parent->left != nullptr && ptr_ != ptr_->parent->left) {
                    ptr_ = ptr_->parent->left;
                    while (ptr_->right != nullptr || ptr_->left != nullptr) {
                        ptr_ = ptr_->right ? ptr_->right : ptr_->left;
                    }
                    while (ptr_->left != nullptr) {
                        ptr_ = ptr_->left;
                    }
                } else {
                    ptr_ = ptr_->parent;
                }
                
                return *this;
            }
            if (tag == TraverseTag::Post) {
                if (ptr_->right != nullptr) {
                    ptr_ = ptr_->right;
                } else if (ptr_->left != nullptr) {
                    ptr_ = ptr_->left;
                } else {
                    pointer cur = ptr_->parent;
                    while (cur != nullptr && (cur->left == nullptr || cur->left == ptr_)) {
                        ptr_ = cur;
                        cur = cur->parent;
                    }
                    cur = ptr_->parent;
                    if (cur != nullptr) {
                        ptr_ = cur->left;
                    } else {
                        ptr_ = nullptr;
                    }
                }

                return *this;
            }

            return *this;
        }

        iterator_base operator++(int) { iterator_base temp = *this; ++(*this); return temp; }
        iterator_base operator--(int) { iterator_base temp = *this; --(*this); return temp; }

        bool operator==(const iterator_base& other) const { return ptr_ == other.ptr_; };
        bool operator!=(const iterator_base& other) const { return ptr_ != other.ptr_; };

    protected:
        pointer ptr_;
    };

    template<TraverseTag tag>
    class iterator : public iterator_base<tag> {
    public:
        explicit iterator(BST::pointer node) : iterator_base<tag>(node) {}

        BST::value_type operator*() { return this->ptr_->key; }
        typename iterator_base<tag>::pointer operator->() { return this->ptr_; }
    };

    template<TraverseTag tag>
    class const_iterator : public iterator_base<tag> {
    public:
        explicit const_iterator(BST::pointer node) : iterator_base<tag>(node) {}

        BST::const_value_type operator*() const { return this->ptr_->key; }
        typename iterator_base<tag>::const_pointer operator->() const { return this->ptr_; }
    };

    template<TraverseTag tag>
    class reverse_iterator : public iterator_base<tag> {
    public:
        using iterator_base<tag>::operator--;
        explicit reverse_iterator(BST::pointer node) : iterator_base<tag>(node) {}

        reverse_iterator& operator++() {
            this->operator--();
            return *this;
        }
        reverse_iterator operator++(int) { reverse_iterator temp = *this; --(*this); return temp; }
        reverse_iterator operator--(int) { reverse_iterator temp = *this; ++(*this); return temp; }

        BST::value_type operator*() { return this->ptr_->key; }
        typename iterator_base<tag>::pointer operator->() { return this->ptr_; }
    };

    template<TraverseTag tag>
    class const_reverse_iterator : public iterator_base<tag> {
    public:
        using iterator_base<tag>::operator--;
        explicit const_reverse_iterator(BST::pointer node) : iterator_base<tag>(node) {}

        const_reverse_iterator& operator++() {
            this->operator--();
            return *this;
        }
        const_reverse_iterator operator++(int) { const_reverse_iterator temp = *this; --(*this); return temp; }
        const_reverse_iterator operator--(int) { const_reverse_iterator temp = *this; ++(*this); return temp; }

        BST::const_value_type operator*() const { return this->ptr_->key; }
        typename iterator_base<tag>::const_pointer operator->() const { return this->ptr_; }
    };

public:
    BST() : root_(nullptr), size_(0), allocator_(Allocator()) {}

    BST (const BST& other) 
        : root_(nullptr), size_(0), allocator_(other.allocator_) {
            if (other.root_ != nullptr) {
                root_ = Copy(nullptr, other.root_);
            }
        }

    template<typename InputIt>
    BST(InputIt i, InputIt j, const Allocator& allocator = Allocator()) 
        : root_(nullptr), size_(0), allocator_(allocator) {
            for (; i != j; ++i) {
                insert(i);
            }
        }

    BST(std::initializer_list<value_type> il, const Allocator& allocator = Allocator()) 
        : root_(nullptr), size_(0), allocator_(allocator) {
            insert(il);
        }

    ~BST() { clear(); }

    BST& operator=(const BST& other) {
        if (this == &other) {
            return *this;
        }
        clear();
        if (other.root_ != nullptr) {
            root_ = Copy(nullptr, other.root_);
        }

        return *this;
    }

    BST& operator=(std::initializer_list<value_type> il) {
        clear();
        insert(il);

        return *this;
    }

    bool operator==(const BST& other) const {
        if (this->size_ != other.size_) {
            return false;
        }
        auto this_it = this->cbegin<TraverseTag::Pre>();
        auto this_end = this->cend<TraverseTag::Pre>();
        auto other_it = other.cbegin<TraverseTag::Pre>();
        auto other_end = other.cend<TraverseTag::Pre>();
        while (this_it != this_end && other_it != this_end) {
            if (*this_it != *other_it) {
                return false;
            }
            ++this_it;
            ++other_it;
        }
        if (this_it == this_end && other_it == other_end) {
            return true;
        }

        return false;
    }

    bool operator!=(const BST& other) const { return !(*this == other); }

    void swap(BST& other) {
        std::swap(this->root_, other.root_);
        std::swap(this->size_, other.size_);
    }

    void swap(BST& a, BST& b) { a.swap(b); }

    size_t size() const {
        return std::distance(this->cbegin<TraverseTag::In>(), this->cend<TraverseTag::In>());
    }

    size_t max_size() const { return std::numeric_limits<difference_type>::max(); }

    bool empty() const {
        return this->cbegin<TraverseTag::In>() == this->cend<TraverseTag::In>();
    }

    template<TraverseTag tag>
    iterator<tag> begin() {
        pointer temp = root_;
        if (tag == TraverseTag::In) {
            while (temp != nullptr && temp->left != nullptr) {
                temp = temp->left;
            }
        } else if (tag == TraverseTag::Post) {
            while (temp != nullptr && (temp->left != nullptr || temp->right != nullptr)) {
                if (temp->left != nullptr) {
                    temp = temp->left;
                } else {
                    temp = temp->right;
                }
            }
        }

        return iterator<tag>(temp);
    }

    template<TraverseTag tag>
    iterator<tag> end() {
        pointer temp = root_;
        if (tag == TraverseTag::In) {
            while (temp != nullptr) {
                temp = temp->right;
            }
        } else if (tag == TraverseTag::Pre) {
            while (temp != nullptr) {
                temp = temp->right;
            }
        } else {
            temp = nullptr;
        }

        return iterator<tag>(temp);
    }

    template<TraverseTag tag>
    const_iterator<tag> cbegin() const {
        pointer temp = root_;
        if (tag == TraverseTag::In) {
            while (temp != nullptr && temp->left != nullptr) {
                temp = temp->left;
            }
        } else if (tag == TraverseTag::Post) {
            while (temp != nullptr && (temp->left != nullptr || temp->right != nullptr)) {
                if (temp->left != nullptr) {
                    temp = temp->left;
                } else {
                    temp = temp->right;
                }
            }
        }

        return const_iterator<tag>(temp);
    }

    template<TraverseTag tag>
    const_iterator<tag> cend() const {
        pointer temp = root_;
        if (tag == TraverseTag::In) {
            while (temp != nullptr) {
                temp = temp->right;
            }
        } else if (tag == TraverseTag::Pre) {
            while (temp != nullptr) {
                temp = temp->right;
            }
        } else {
            temp = nullptr;
        }

        return const_iterator<tag>(temp);
    }

    template<TraverseTag tag>
    reverse_iterator<tag> rbegin() {
        pointer temp = root_;
        if (tag == TraverseTag::In) {
            while (temp != nullptr && temp->right != nullptr) {
                temp = temp->right;
            }
        } else if (tag == TraverseTag::Pre) {
            while (temp->right != nullptr || temp->left != nullptr) {
                if (temp->right != nullptr) {
                    temp = temp->right;
                } else {
                    temp = temp->left;
                }
            }
        }

        return reverse_iterator<tag>(temp);
    }

    template<TraverseTag tag>
    reverse_iterator<tag> rend() {
        pointer temp = root_;
        if (tag == TraverseTag::In) {
            while (temp != nullptr) {
                temp = temp->left;
            }
        } else if (tag == TraverseTag::Post) {
            while (temp != nullptr) {
                temp = temp->left;
            }
        }

        return reverse_iterator<tag>(temp);
    }

    template<TraverseTag tag>
    const_reverse_iterator<tag> crbegin() const {
        pointer temp = root_;
        if (tag == TraverseTag::In) {
            while (temp != nullptr && temp->right != nullptr) {
                temp = temp->right;
            }
        } else if (tag == TraverseTag::Pre) {
            while (temp->right != nullptr || temp->left != nullptr) {
                if (temp->right != nullptr) {
                    temp = temp->right;
                } else {
                    temp = temp->left;
                }
            }
        }

        return const_reverse_iterator<tag>(temp);
    }

    template<TraverseTag tag>
    const_reverse_iterator<tag> crend() const {
        pointer temp = root_;
        if (tag == TraverseTag::In) {
            while (temp != nullptr) {
                temp = temp->left;
            }
        } else if (tag == TraverseTag::Post) {
            while (temp != nullptr) {
                temp = temp->left;
            }
        }

        return const_reverse_iterator<tag>(temp);
    }

    void clear() {
        deep_clear(root_);
        root_ = nullptr;
        size_ = 0;
    }

    std::pair<iterator<TraverseTag::In>, bool> insert_check(const value_type& value) {
        pointer temp = exist_node(root_, value);
        if (temp != nullptr) {
            return {iterator<TraverseTag::In>(temp), false};
        } else {
            root_ = insert_node(root_, nullptr, value);
            temp = exist_node(root_, value);
            ++size_;

            return {iterator<TraverseTag::In>(temp), true};
        }
    }

    iterator<TraverseTag::In> insert(const value_type& value) {
        pointer temp = exist_node(root_, value);
        if (temp != nullptr) {
            return iterator<TraverseTag::In>(temp);
        } else {
            root_ = insert_node(root_, nullptr, value);
            temp = exist_node(root_, value);
            ++size_;

            return iterator<TraverseTag::In>(temp);
        }
    }

    void insert(std::initializer_list<value_type> il) {
        for (const auto& value : il) {
            insert(value);
        }
    }

    template<class InputIt>
    void insert(InputIt i, InputIt j) {
        for (; i != j; ++i) {
            insert(i);
        }
    }

    node_type extract(const value_type& value) {
        pointer temp = exist_node(root_, value);
        if (temp == nullptr) {
            return Node<T>();
        }
        node_type extracted;
        extracted.key = temp->key;
        extracted.left = nullptr;
        extracted.right = nullptr;
        extracted.parent = nullptr;
        delete_node(root_, value);
        --size_;

        return extracted;
    }

    void merge(BST& other) {
        if (this->allocator_ != other.allocator_) {
            std::cerr << "..error";
            std::exit(EXIT_FAILURE);
        }
        for (auto it = other.begin<TraverseTag::In>(); it != other.end<TraverseTag::In>(); ++it) {
            auto result = this->insert(*it);
        }
        other.clear();
    }

    size_type erase(const value_type& value) {
        if (exist_node(root_, value) != nullptr) {
            delete_node(root_, value);
            --size_;

            return 1;
        }

        return 0;
    }

    template<TraverseTag tag>
    iterator<tag> erase(iterator<tag> q) {
        if (q == end<tag>()) {
            return end<tag>();
        }
        value_type value = *q;
        iterator<tag> next = q;
        if (tag != TraverseTag::In) {
            ++next;
            delete_node(root_, value);
            --size_;
        } else {
            delete_node(root_, value);
            --size_;
            next = iterator<tag>(next_node(root_, value));
        }

        return next;
    }

    template<TraverseTag tag>
    const_iterator<tag> erase(const_iterator<tag> r) {
        if (r == cend<tag>()) {
            return cend<tag>();
        }
        value_type value = *r;
        const_iterator<tag> next = r;
        if (tag != TraverseTag::In) {
            ++next;
            delete_node(root_, value);
            --size_;
        } else {
            delete_node(root_, value);
            --size_;
            next = const_iterator<tag>(next_node(root_, value));
        }

        return next;
    }

    iterator<TraverseTag::In> find(const value_type& k) {
        pointer temp = exist_node(root_, k);
        if (temp == nullptr) {
            return end<TraverseTag::In>();
        }
        
        return iterator<TraverseTag::In>(temp);
    }

    const_iterator<TraverseTag::In> find(const value_type& k) const {
        pointer temp = exist_node(root_, k);
        if (temp == nullptr) {
            return cend<TraverseTag::In>();
        }
        
        return const_iterator<TraverseTag::In>(temp);
    }

    iterator<TraverseTag::In> lower_bound(const value_type& k) {
        if (exist_node(root_, k) == nullptr) {
            return end<TraverseTag::In>();
        }
        pointer temp = prev_node(root_, k);
        if (temp == nullptr) {
            return end<TraverseTag::In>();
        }
        
        return iterator<TraverseTag::In>(temp);
    }

    const_iterator<TraverseTag::In> lower_bound(const value_type& k) const {
        if (exist_node(root_, k) == nullptr) {
            return end<TraverseTag::In>();
        }
        pointer temp = prev_node(root_, k);
        if (temp == nullptr) {
            return cend<TraverseTag::In>();
        }
        
        return const_iterator<TraverseTag::In>(temp);
    }

    iterator<TraverseTag::In> upper_bound(const value_type& k) {
        if (exist_node(root_, k) == nullptr) {
            return end<TraverseTag::In>();
        }
        pointer temp = next_node(root_, k);
        if (temp == nullptr) {
            return end<TraverseTag::In>();
        }
        
        return iterator<TraverseTag::In>(temp);
    }

    const_iterator<TraverseTag::In> upper_bound(const value_type& k) const {
        if (exist_node(root_, k) == nullptr) {
            return end<TraverseTag::In>();
        }
        pointer temp = next_node(root_, k);
        if (temp == nullptr) {
            return cend<TraverseTag::In>();
        }
        
        return const_iterator<TraverseTag::In>(temp);
    }
    
private:

    pointer root_;
    size_t size_;
    allocator_type allocator_;

    pointer Copy(pointer par, pointer cur) {
        if (cur == nullptr) {
            return nullptr;
        }
        pointer new_node = allocator_.allocate(1);
        new_node->key = cur->key;
        new_node->parent = par;
        new_node->parent = par;
        new_node->left = Copy(new_node, cur->left);
        new_node->right = Copy(new_node, cur->right);

        return new_node;
    }

    void deep_clear(pointer temp) {
        if (temp == nullptr) {
            return;
        }
        deep_clear(temp->left);
        deep_clear(temp->right);
        allocator_.deallocate(temp, 1);
    }

    pointer next_node(pointer temp, value_type x) {
        pointer next = nullptr;
        while (temp != nullptr) {
            if (temp->key > x) {
                next = temp;
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        return next;
    }

    pointer prev_node(pointer temp, value_type x) {
        pointer prev = nullptr;
        while (temp != nullptr) {
            if (temp->key < x) {
                prev = temp;
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        return prev;
    }

    void delete_node(pointer& root, T x) {
        pointer temp = exist_node(root, x);
        if (temp == nullptr) {
            return;
        }
        if (temp->left == nullptr && temp->right == nullptr) {
            if (temp != root) {
                swap_nodes(temp, nullptr);
            } else {
                root = nullptr;
            }
            allocator_.deallocate(temp, 1);
        } else if (temp->left == nullptr || temp->right == nullptr) {
            pointer kid = temp->left == nullptr ? temp->right : temp->left;
            if (temp != root) {
                swap_nodes(temp, kid);
            } else {
                root = kid;
            }
            kid->parent = temp->parent;
            allocator_.deallocate(temp, 1);
        } else {
            pointer successor = minimum_node(temp->right);
            value_type key =  successor->key;
            delete_node(root, successor->key);
            temp->key = key;
        }
    }

    pointer insert_node(pointer temp, pointer parent, value_type x) {
        if (temp == nullptr) {
            temp = allocator_.allocate(1);
            temp->key = x;
            temp->parent = parent;
        } else if (x > temp->key) {
            pointer right = insert_node(temp->right, temp, x);
            temp->right = right;
        } else if (x < temp->key) {
            pointer left = insert_node(temp->left, temp, x);
            temp->left = left;
        }
        return temp;
    }

    pointer exist_node(pointer temp, value_type x) {
        if (temp == nullptr) {
            return nullptr;
        }
        if (x == temp->key) {
            return temp;
        } else if (x < temp->key) {
            return exist_node(temp->left, x);
        } else {
            return exist_node(temp->right, x);
        }
    }

    void swap_nodes(pointer root, pointer temp) {
        if (root->parent != nullptr) {
            if (root != root->parent->left) {
                root->parent->right = temp;
            } else {
                root->parent->left = temp;
            }
        }
    }

    pointer minimum_node(pointer temp) {
        if (temp->left == nullptr) {
            return temp;
        }
        return minimum_node(temp->left);
    }
};
