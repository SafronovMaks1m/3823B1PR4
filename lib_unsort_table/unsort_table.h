#include "..//lib_itable/itable.h"
#include "..//lib_pair/TPair.h"
#include "..//lib_list/list.h"
#include "..//lib_list/node.h"
#include "string.h"
#include "iostream"
#include "exception"

template <class Tkey>
void generate_key(Tkey& key, int val, size_t size) {
    key = val + size;
}

template <class Tkey>
void generate_key(Tkey& key, std::string val, size_t size) {
    key = val + char(size);
}


template <class Tkey, class Tval>
class Unsorted_Table : public ITable<Tkey, Tval> {
    Tlist<TPair<Tkey, Tval>> _data;
    size_t _size;
public:
    Unsorted_Table();
    Unsorted_Table(const Tlist<TPair<Tkey, Tval>>& list);
    Unsorted_Table(const Unsorted_Table<Tkey, Tval>& table);
    Unsorted_Table& operator = (const Unsorted_Table<Tkey, Tval>& table);
    Tkey insert(Tval value);
    void insert(Tkey key, Tval value);
    void erase(Tkey key);
    Tval& find(Tkey key);
    const Tval& find(Tkey key) const;
    bool search(Tkey key);
    const Tval& operator[](const Tkey key) const;
    Tval& operator[](const Tkey key);
};

template <class Tkey, class Tval>
Unsorted_Table<Tkey, Tval>::Unsorted_Table() {
    _size = 0;
}

template <class Tkey, class Tval>
Unsorted_Table<Tkey, Tval>::Unsorted_Table(const Tlist<TPair<Tkey, Tval>>& list) {
    _data = list;
    _size = list.get_size();
}

template <class Tkey, class Tval>
Unsorted_Table<Tkey, Tval>::Unsorted_Table(const Unsorted_Table<Tkey, Tval>& table) {
    _data = table._data;
    _size = table._size;
}

template <class Tkey, class Tval>
Unsorted_Table<Tkey, Tval>& Unsorted_Table<Tkey, Tval>::operator=(const Unsorted_Table<Tkey, Tval>& table) {
    if (this != &table) {
        _data = table._data;
        _size = table._size;
    }
    return *this;
}

template <class Tkey, class Tval>
Tkey Unsorted_Table<Tkey, Tval>::insert(Tval value) {
    Tkey new_key;
    generate_key(new_key, value, _size);
    TPair<Tkey, Tval> new_row(new_key, value);
    _data.push_back(new_row);
    _size++;
    return new_key;
}

template <class Tkey, class Tval>
void Unsorted_Table<Tkey, Tval>::insert(Tkey key, Tval value) {
    if (search(key))
        throw std::logic_error("such a key is already in the table.");
    TPair<Tkey, Tval> new_row(key, value);
    _data.push_back(new_row);
    _size++;
}

template <class Tkey, class Tval>
void Unsorted_Table<Tkey, Tval>::erase(Tkey key) {
    for (auto i = _data.begin(); i != _data.end(); i++) {
        if ((*i).first() == key) {
            _data.erase(i.pcur());
            break;
        }
    }
    _size--;
}

template <class Tkey, class Tval>
Tval& Unsorted_Table<Tkey, Tval>::find(Tkey key) {
    for (auto i = _data.begin(); i != _data.end(); i++) {
        if ((*i).first() == key) {
            return (*i).second();
        }
    }
    throw std::logic_error("element not found");
}

template <class Tkey, class Tval>
const Tval& Unsorted_Table<Tkey, Tval>::find(Tkey key) const{
    for (auto i = _data.begin(); i != _data.end(); i++) {
        if ((*i).first() == key) {
            return (*i).second();
        }
    }
    throw std::logic_error("element not found");
}

template <class Tkey, class Tval>
bool Unsorted_Table<Tkey, Tval>::search(Tkey key) {
    for (auto i = _data.begin(); i != _data.end(); i++) {
        if ((*i).first() == key) {
            return true;
        }
    }
    return false;
}

template<class Tkey, class Tval>
const Tval& Unsorted_Table<Tkey, Tval>::operator[](const Tkey key) const {
    return this->find(key);
}

template<class Tkey, class Tval>
Tval& Unsorted_Table<Tkey, Tval>::operator[](const Tkey key) {
    return this->find(key);
}