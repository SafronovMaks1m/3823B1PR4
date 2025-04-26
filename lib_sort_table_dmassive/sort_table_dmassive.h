#include "..//lib_itable/itable.h"
#include "..//lib_pair/TPair.h"
#include "..//lib_dmassive/TDmassive.h"
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
class Sorted_Table_DMassive : public ITable<Tkey, Tval> {
    TDMassive<TPair<Tkey, Tval>> _data;
    size_t _size;
public:
    Sorted_Table_DMassive();
    Sorted_Table_DMassive(const TDMassive<TPair<Tkey, Tval>>& massive);
    Sorted_Table_DMassive(const Sorted_Table_DMassive<Tkey, Tval>& table);
    Sorted_Table_DMassive& operator = (const Sorted_Table_DMassive<Tkey, Tval>& table);
    Tkey insert(Tval value);
    void insert(Tkey key, Tval value);
    void erase(Tkey key);
    Tval& find(Tkey key);
    const Tval& find(Tkey key) const;
    const Tval& operator[](const Tkey key) const;
    Tval& operator[](const Tkey key);
    TDMassive<TPair<Tkey, Tval>>& data();
};

template <class Tkey, class Tval>
Sorted_Table_DMassive<Tkey, Tval>::Sorted_Table_DMassive() {
    _size = 0;
}

template <class Tkey, class Tval>
Sorted_Table_DMassive<Tkey, Tval>::Sorted_Table_DMassive(const TDMassive<TPair<Tkey, Tval>>& massive) {
    for (size_t i = 0; i < massive.size(); i++) {
        this->insert(massive[i].first(), massive[i].second());
    }
}

template <class Tkey, class Tval>
Sorted_Table_DMassive<Tkey, Tval>::Sorted_Table_DMassive(const Sorted_Table_DMassive<Tkey, Tval>& table) {
    _data = table._data;
    _size = table._size;
}

template <class Tkey, class Tval>
Sorted_Table_DMassive<Tkey, Tval>& Sorted_Table_DMassive<Tkey, Tval>::operator=(const Sorted_Table_DMassive<Tkey, Tval>& table) {
    if (this != &table) {
        _data = table._data;
        _size = table._size;
    }
    return *this;
}

template <class Tkey, class Tval>
Tkey Sorted_Table_DMassive<Tkey, Tval>::insert(Tval value) {
    Tkey new_key;
    generate_key(new_key, value, _size);
    this->insert(new_key, value);
    return new_key;
}

template <class Tkey, class Tval>
void Sorted_Table_DMassive<Tkey, Tval>::insert(Tkey key, Tval value) {
    TPair<Tkey, Tval> new_row(key, value);
    if (_size == 0)
        _data.push_back(new_row);
    else {
        int mid, l = 0, r = _size - 1, pos = _size;
        while (l <= r) {
            mid = (l + r) / 2;
            if (_data[mid].first() == key) {
                if (_data.states()[mid] != State::deleted && _data.states()[mid] != State::empty)
                    throw std::logic_error("There is already an element with this key.");
                pos = mid;
                break;
            }
            else if (_data[mid].first() < key) {
                l = mid + 1;
            }
            else {
                r = mid - 1;
                pos = mid;
            }
        }
        _data.insert(new_row, pos);
    }
    _size++;
}

template <class Tkey, class Tval>
void Sorted_Table_DMassive<Tkey, Tval>::erase(Tkey key) {
    for (size_t i = 0; i < _size; i++) {
        if (_data.states()[i] != State::deleted && _data.states()[i] != State::empty && _data[i].first() == key) {
            _data.remove_by_index(i);
            break;
        }
    }
    _size--;
}

template <class Tkey, class Tval>
Tval& Sorted_Table_DMassive<Tkey, Tval>::find(Tkey key) {
    int mid, l = 0, r = _size - 1;
    while (l <= r) {
        mid = (l + r) / 2;
        if (_data[mid].first() == key) {
            if (_data.states()[mid] == State::deleted || _data.states()[mid] == State::empty)
                throw std::logic_error("There is no element with this key.");
            return _data[mid].second();
        }
        else if (_data[mid].first() < key) {
            l = mid + 1;
        }
        else {
            r = mid - 1;

        }
    }
    throw std::logic_error("There is no element with this key.");
}

template <class Tkey, class Tval>
const Tval& Sorted_Table_DMassive<Tkey, Tval>::find(Tkey key) const {
    int mid, l = 0, r = _size - 1;
    while (l <= r) {
        mid = (l + r) / 2;
        if (_data[mid].first() == key) {
            if (_data.states()[mid] == State::deleted || _data.states()[mid] == State::empty)
                throw std::logic_error("There is no element with this key.");
            return _data[mid].second();
        }
        else if (_data[mid].first() < key) {
            l = mid + 1;
        }
        else {
            r = mid - 1;

        }
    }
    throw std::logic_error("There is no element with this key.");
}

template<class Tkey, class Tval>
const Tval& Sorted_Table_DMassive<Tkey, Tval>::operator[](const Tkey key) const {
    return this->find(key);
}

template<class Tkey, class Tval>
Tval& Sorted_Table_DMassive<Tkey, Tval>::operator[](const Tkey key) {
    return this->find(key);
}

template<class Tkey, class Tval>
TDMassive<TPair<Tkey, Tval>>& Sorted_Table_DMassive<Tkey, Tval>::data() {
    return _data;
}

