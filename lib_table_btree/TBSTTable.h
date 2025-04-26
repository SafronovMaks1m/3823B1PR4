#include "..//lib_dict/TDict.h"
#include "../lib_bin_tree/TBinTree.h"
#include "..//lib_bin_tree/TBinNode.h"
#include "..//lib_itable/itable.h"

template <class Tkey>
void generate_key(Tkey& key, int val, size_t size) {
    key = val + size;
}

template <class Tkey>
void generate_key(Tkey& key, std::string val, size_t size) {
    key = val + char(size);
}

template <class Tkey, class Tval>
class TBSTTable : public ITable<Tkey, Tval> {
	BSearchTree<TDict<Tkey, Tval>> _data;
	size_t _size;
	public:
        TBSTTable();
        TBSTTable(const BSearchTree<TDict<Tkey, Tval>>& tree);
        TBSTTable(const TBSTTable<Tkey, Tval>& table);
        TBSTTable& operator = (const TBSTTable<Tkey, Tval>& table);
        Tkey insert(Tval value);
        void insert(Tkey key, Tval value);
        void erase(Tkey key);
        Tval& find(Tkey key);
        const Tval& find(Tkey key) const;
        const Tval& operator[](const Tkey key) const;
        Tval& operator[](const Tkey key);
        ~TBSTTable() { };
        BSearchTree<TDict<Tkey, Tval>>& data() noexcept;
};

template <class Tkey, class Tval>
TBSTTable<Tkey, Tval>::TBSTTable() {
    _size = 0;
}

template <class Tkey, class Tval>
TBSTTable<Tkey, Tval>::TBSTTable(const BSearchTree<TDict<Tkey, Tval>>& tree) {
    _data = tree;
    _size = tree.size();
}

template <class Tkey, class Tval>
TBSTTable<Tkey, Tval>::TBSTTable(const TBSTTable<Tkey, Tval>& table) {
    _data = table._data;
    _size = table._size;
}

template <class Tkey, class Tval>
TBSTTable<Tkey, Tval>& TBSTTable<Tkey, Tval>::operator=(const TBSTTable<Tkey, Tval>& table) {
    if (this != &table) {
        _data = table._data;
        _size = table._size;
    }
    return *this;
}

template <class Tkey, class Tval>
Tkey TBSTTable<Tkey, Tval>::insert(Tval value) {
    Tkey new_key;
    generate_key(new_key, value, _size);
    TDict<Tkey, Tval> new_row(new_key, value);
    _data.insert(new_row);
    _size++;
    return new_key;
}

template <class Tkey, class Tval>
void TBSTTable<Tkey, Tval>::insert(Tkey key, Tval value) {
    TDict<Tkey, Tval> new_row(key, value);
    _data.insert(new_row);
    _size++;
}

template <class Tkey, class Tval>
void TBSTTable<Tkey, Tval>::erase(Tkey key) {
    TDict<Tkey, Tval> row(key, Tval());
    _data.erase(row);
    _size--;
}

template <class Tkey, class Tval>
Tval& TBSTTable<Tkey, Tval>::find(Tkey key) {
    TDict<Tkey, Tval> row(key, Tval());
    BTreeNode<TDict<Tkey, Tval>>* node = _data.search(row);
    if (node == nullptr)
        throw std::logic_error("element not found");
    return const_cast<Tval&>(node->value().value());
}

template <class Tkey, class Tval>
const Tval& TBSTTable<Tkey, Tval>::find(Tkey key) const {
    TDict<Tkey, Tval> row(key, 0);
    BTreeNode<TDict<Tkey, Tval>>* node = _data.search(row);
    if (node == nullptr)
        throw std::logic_error("element not found");
    return node->value().value();
}

template<class Tkey, class Tval>
const Tval& TBSTTable<Tkey, Tval>::operator[](const Tkey key) const {
    return this->find(key);
}

template<class Tkey, class Tval>
Tval& TBSTTable<Tkey, Tval>::operator[](const Tkey key) {
    return this->find(key);
}

template<class Tkey, class Tval>
BSearchTree<TDict<Tkey, Tval>>& TBSTTable<Tkey, Tval>::data() noexcept {
    return _data;
}