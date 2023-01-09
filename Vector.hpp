#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <stdexcept>

template <class T>
class Vector {
   public:
    explicit Vector(int n = 0) : sz(n) {
        if (n >= cap) {
            cap = n * 2;
        }
        array = new T[cap]{};
    }

    Vector(const Vector &other) : Vector(other.sz) {
        sz = other.sz;
        std::copy(other.array, other.array + sz, array);
    }

    Vector(Vector &&other) noexcept {
        sz = other.sz, cap = other.cap, array = other.array;
        other.sz = 0, other.cap = 0, other.array = nullptr;
    }

    Vector &operator=(const Vector &other) {
        Vector temp(other);
        swap(*this, temp);
        return *this;
    }

    Vector &operator=(Vector &&other) noexcept {
        if (this != &other) {
            swap(*this, other);
            delete[] other.array, other.array = nullptr;
            other.sz = 0, other.cap = 0;
        }
        return *this;
    }

    T &operator[](int i) { return array[i]; }

    ~Vector() { delete[] array; }

    static int size(const Vector &other) { return other.sz; }

    void add(const Vector &other, const int &k) {
        int mn = std::min(Vector::size(other), k);
        for (int i = 0; i < mn; ++i) {
            push_back(other.array[i]);
        }
    }

    void insert(const T &d, const int &k) noexcept(false) {
        if (k == 0) {
            push_front(d);
            return;
        } else if (k == sz) {
            push_back(d);
            return;
        } else if (k > 0 && k < sz) {
            push_back(d);
            T t = array[k], p;
            for (int i = k; i < sz; ++i) {
                p = array[i], array[i] = t, t = p;
            }
            array[k] = d;
            return;
        }
        throw std::out_of_range("Vector. Method insert. Out of range");
    }

    void push_back(const T &d) {
        if (sz < cap) {
            array[sz] = d, ++sz;
            return;
        }
        T *b = array;
        array = new T[cap * 2]{};
        std::copy(b, b + sz, array);
        delete[] b;
        cap *= 2;
        array[sz] = d;
    }

    void push_front(const T &d) {
        push_back(d);
        T t = array[0], p;
        for (int i = 1; i < sz; ++i) {
            p = array[i], array[i] = t, t = p;
        }
        array[0] = d;
    }

    void clear() {
        delete[] array;
        array = new T[10]{};
        sz = 0, cap = 10;
    }

    int size() const noexcept { return sz; }

    bool empty() const noexcept { return sz == 0; }

    T erase(int i) noexcept(false) {
        if (sz > 0 && i < sz) {
            T d = array[i];
            std::copy(array + i + 1, array + sz, array + i);
            --sz;
            return d;
        }
        throw std::out_of_range("Vector. Method erase. Out of range");
    }

    T pop_front() { return erase(0); }

    T pop_back() {
        T d = T();
        if (sz > 0) {
            d = array[sz - 1], --sz;
        }
        return d;
    }

    friend void swap(Vector &first, Vector &second) noexcept {
        std::swap(first.standart, second.standart);
        std::swap(first.array, second.array);
        std::swap(first.cap, second.cap);
        std::swap(first.sz, second.sz);
    }

    class iterator {
       public:
        T *i;

        iterator() : i(0) {}
        explicit iterator(T *n) : i(n) {}
        iterator(const iterator &o) : i(o.i) {}
        T &operator*() const { return *i; }
        T *operator->() const { return i; }
        T &operator[](int j) const { return i[j]; }
        bool operator==(const iterator &o) const { return i == o.i; }
        bool operator!=(const iterator &o) const { return i != o.i; }
        bool operator<(const iterator &other) const { return i < other.i; }
        bool operator<=(const iterator &other) const { return i <= other.i; }
        bool operator>(const iterator &other) const { return i > other.i; }
        bool operator>=(const iterator &other) const { return i >= other.i; }
        iterator &operator++() {
            ++i;
            return *this;
        }
        const iterator operator++(int) {
            T *n = i;
            ++i;
            return iterator(n);
        }
        iterator &operator--() {
            i--;
            return *this;
        }
        const iterator operator--(int) {
            T *n = i;
            i--;
            return iterator(n);
        }
        iterator &operator+=(int j) {
            i += j;
            return *this;
        }
        iterator &operator-=(int j) {
            i -= j;
            return *this;
        }
        iterator operator+(int j) const { return iterator(i + j); }
        iterator operator-(int j) const { return iterator(i - j); }
        int operator-(iterator j) const { return int(i - j.i); }
    };

    Vector<T>::iterator begin() { return iterator(&array[0]); }
    Vector<T>::iterator end() { return iterator(&array[sz]); }

   private:
    int sz = 0;
    int cap = 10;
    T *array = nullptr;
};

#endif
