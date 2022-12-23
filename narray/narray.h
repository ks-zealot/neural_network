//
// Created by zealot on 13.12.2022.
//
#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>
#include <cstring>
#include <random>
#include <stdexcept>

#include "../utils/narray_util.h"

#ifndef NEURONET_NARRAY_H
#define NEURONET_NARRAY_H

template<typename T>
class memory_policy {
public:
    virtual void free(std::allocator<T> alloc, T *mem, std::size_t size) = 0;

    virtual ~memory_policy() {};
};

template<typename T>
class standart_policy : public memory_policy<T> {
    virtual void free(std::allocator<T> alloc, T *mem, std::size_t size) {
        alloc.deallocate(mem, size);
    }
};

template<typename T>
class subnarray_policy : public memory_policy<T> {
    virtual void free(std::allocator<T> alloc, T *mem, std::size_t size) {
    }
};


template<typename T>
class filler {
public:
    virtual void fill(T *mem, int size) = 0;
};

template<typename T>
class zero_filler : public filler<T> {
public:
    static zero_filler &GetInstance() {
        static zero_filler instance;
        return instance;
    };

    virtual void fill(T *mem, int size) {
        memset(mem, 0, size);
    }
};

template<typename T>
class random_filler : public filler<T> {
public:
    static random_filler &GetInstance() {
        static random_filler<T> instance;
        return instance;
    };

    virtual void fill(T *mem, int size) {
        std::random_device r;
        std::default_random_engine generator(r());
        std::normal_distribution<float> distribution(0., 1.);
        for (int i = 0; i < size; i++) {
            T t = T(distribution(generator));
            mem[i] = t;
        }
    }
};


template<typename T>
class narray {
public:
    narray();

    narray(narray<T> &out);

    narray(narray<T> &&rhs) noexcept;

    template<class B,
            template<class...> class Container,
            class... extras>
    explicit narray(const Container<B, extras...> &source, memory_policy<T> *policy = new standart_policy<T>(),
                    std::allocator<T> alloc = std::allocator<T>()) {
        this->mem_policy = policy;
        this->allocator = alloc;
        std::vector<T> target;
        flat_transfer(target, source, sizes);
        detect_sizes(source, sizes);
        mem_size = 1;
        std::for_each(sizes.begin(), sizes.end(),
                      [this](int i) mutable {
                          mem_size *= i;
                      });
        mem = allocator.allocate(mem_size);
        for (int i = 0; i < mem_size; i++) {
            mem[i] = target[i];
        }
        std::vector<int> stride_info = sizes;
        std::reverse(stride_info.begin(), stride_info.end());
        for (int i = 0; i < stride_info.size(); i++) {
            stride_info[i] = pow(sizes[i], i);
        }
        this->stride_info = stride_info;
    };

    narray(std::vector<int> sizes, T *mem, memory_policy<T> *policy = new standart_policy<T>(),
           std::allocator<T> alloc = std::allocator<T>());

    narray(std::vector<int> sizes, std::vector<int> stride_info, T *mem,
           memory_policy<T> *policy = new standart_policy<T>(),
           std::allocator<T> alloc = std::allocator<T>());

    explicit narray(std::vector<int> sizes, filler<T> &f = zero_filler<T>::GetInstance());

    virtual ~narray();
//   narray((5, 4))

//    |1|2|3|4|5|
//    |1|2|3|4|5|
//    |1|2|3|4|5|
//    |1|2|3|4|5|



    class iterator {
    public:
        using value_type = T *;
        using difference_type = std::ptrdiff_t;
        using reference = T &;
        using pointer = T *;
        using iterator_category = std::forward_iterator_tag;

        iterator() : narray(), m_idx(0) {
            coord = narray->sizes;
            std::fill(coord.begin(), coord.end(), 0);
        }

        iterator(narray<T> *b, std::size_t idx) : narray(b), m_idx(idx) {
            coord = narray->sizes;
            std::fill(coord.begin(), coord.end(), 0);
            plus_coord(idx);
        }

        reference operator*()  { return *narray->at(coord); }

        pointer operator->()  { return &**this; }

        friend iterator &operator++(iterator &rhs) {
            rhs.m_idx += 1;// * rhs.narray->stride_info.front();
            rhs.inc_coord();
            return rhs;
        }

        iterator &operator+=(const int &rhs) {
            this->m_idx += rhs;// * this->narray->stride_info.front();
            this->plus_coord(rhs);// * this->narray->stride_info.front());
            return *this;
        }


        friend iterator operator++(iterator &lhs, int) {
            auto cp = lhs;
            ++lhs;
            return cp;
        }


        friend bool operator==(iterator lhs, iterator rhs) { return lhs.m_idx == rhs.m_idx; }

        friend bool operator!=(iterator lhs, iterator rhs) { return !(lhs == rhs); }


    private:
        narray<T> *narray;
        std::size_t m_idx;
        std::vector<int> coord;
    private:
        void inc_coord() {
            plus_coord(1);// * this->narray->stride_info.front());
        }


        void plus_coord(int val) {
            int shift = val;
            int idx = coord.size() - 1;
            std::vector<int> ref_sizes = narray->sizes;
            std::for_each(coord.rbegin(), coord.rend(),
                          [this, &idx, &shift, &ref_sizes](int i) mutable {
                              coord[idx] += shift;
                              shift = 0;
                              while (coord[idx] >= ref_sizes[idx]) {
                                  shift++;
                                  coord[idx] = -ref_sizes[idx];
                              }
                              idx--;
                          });
        }
    };

    class const_iterator {
    public:
        using value_type = T *;
        using difference_type = std::ptrdiff_t;
        using reference = const T &;
        using pointer = const T *;
        using iterator_category = std::forward_iterator_tag;


        const_iterator() : narray(), m_idx(0) {
            coord = narray->sizes;
            std::fill(coord.begin(), coord.end(), 0);
        }

        const_iterator(const narray<T> *b, std::size_t idx) : narray(b), m_idx(idx) {
            coord = narray->sizes;
            std::fill(coord.begin(), coord.end(), 0);
            plus_coord(idx);
        }

        reference operator*() {
            return *narray->at(coord);
        }

        pointer operator->() { return &**this; }

        friend const_iterator &operator++(const_iterator &rhs) {
            rhs.m_idx += 1;// * rhs.narray->stride_info.front();
            rhs.inc_coord();
            return rhs;
        }

        const_iterator &operator+=(const int &rhs) {
            this->m_idx += rhs;// * this->narray->stride_info.front();
            this->plus_coord(rhs);// * this->narray->stride_info.front());
            return *this;
        }

        friend const_iterator operator++(const_iterator &lhs, int) {
            auto cp = lhs;
            ++lhs;
            return cp;
        }

        friend bool operator==(const_iterator lhs, const_iterator rhs) { return lhs.m_idx == rhs.m_idx; }

        friend bool operator!=(const_iterator lhs, const_iterator rhs) { return !(lhs == rhs); }


    private:
        const narray<T> *narray;
        std::vector<int> coord;
        std::size_t m_idx;

    private:
        void inc_coord() {
            plus_coord(1);// * this->narray->stride_info.front());
        }

        // coord {0, 2} + 5
        // shift = 5
        // coord {0, 7}, 7 >= 3 shift = 0
        // 7 - 3 = 4 shift 1
        // 4- 3 = 1 shift 2
        // coord {0, 1} shift 2
        // coord {2, 1} shift 0


        // coord {0, 2} + 1
        // shift = 1
        // coord {0, 3} 3 >= 3, shift 0
        // 3 -3 = 0 shift 1
        // coord {0, 0} shift 1
        // coord {1, 0} shift 0

        void plus_coord(int val) {
            int shift = val;
            int idx = coord.size() - 1;
            std::vector<int> ref_sizes = narray->sizes;
            std::for_each(coord.rbegin(), coord.rend(),
                          [this, &idx, &shift, &ref_sizes](int i) mutable {
                              coord[idx] += shift;
                              shift = 0;
                              while (coord[idx] >= ref_sizes[idx]) {
                                  shift++;
                                  coord[idx] = -ref_sizes[idx];
                              }
                              idx--;
                          });
        }
    };

    iterator begin() { return {this, 0}; }

    const_iterator cbegin() const { return {this, 0}; }

    iterator end() { return {this, static_cast<std::size_t>( mem_size)}; }

    const_iterator cend() const { return {this, static_cast<std::size_t>( mem_size)}; }

// матрица 2 на 3 для [ 1] offset = 3
// матрица 2 на 3 транспонированная для [ 1] offset = 1
//    -0.74331 -1.00973 -1.00973
//    0.73697 2.04419 -1.00973
//    0.064087 1.15236 -1.00973
// матрица 3 на 3 транспонированная для [ 1] offset = 1
    narray<T> operator[](std::size_t idx) const {
        std::vector<int> new_sizes = sizes;
        std::vector<int> new_stride_info = stride_info;
        std::reverse(new_stride_info.begin(), new_stride_info.end());
        new_sizes.erase(new_sizes.begin());
        new_stride_info.erase(new_stride_info.begin());
        if (idx > new_sizes.front()) {
            std::string exp_message("Index out of bound exception: ");
            exp_message.append(std::to_string(idx));
            exp_message.append(" > ");
            exp_message.append(std::to_string((*new_sizes.begin())));
            throw new std::runtime_error(exp_message);
        }
        std::vector<int> offset = sizes;
        std::fill(offset.begin(), offset.end(), 0);
        offset[0] = idx;
        return narray(new_sizes, new_stride_info, at(offset), new subnarray_policy<T>(),
                      std::allocator<T>());
    }

//    narray<T> &operator[](std::size_t idx) {
//        narray<T> res = this[idx];
//        return res;
//    }

    narray<T> &operator=(narray<T> &rhs) {
        rhs.sizes = sizes;
        rhs.mem_size = mem_size;
        rhs.stride_info = stride_info;
        std::allocator<T> alloc;
        rhs.mem = alloc.allocate(rhs.mem_size);
        rhs.mem_policy = new standart_policy<T>();
        rhs.allocator = alloc;
        memcpy(rhs.mem, mem, sizeof(T) * rhs.mem_size);
        return rhs;
    }


    narray<T> &operator=(narray<T> const &&rhs) {
        sizes = rhs.sizes;
        mem_size = rhs.mem_size;
        allocator = rhs.allocator;
        mem = rhs.mem;
        stride_info = rhs.stride_info;
        return *this;
    }

    narray<T> &operator+=(narray<T> const &rhs) {
        if (sizes != rhs.sizes) {
            throw_matrix_noneq_error(sizes, rhs.sizes);
        }
        for (int i = 0; i < mem_size; i++) {
            T t = *(mem + i) + *(rhs.mem + i);
            T *ptr = mem + i;
            ptr = &t;
        }
        return *this;
    }

    narray<T> &operator+=(T const &rhs) {
        *mem += rhs;
        return *this;
    }



    friend narray<T> operator+(narray<T> lhs, narray<T> const &rhs) {
        lhs += rhs;
        return lhs;
    }

    narray<T> &operator-=(narray<T> const &rhs) {
        if (sizes != rhs.sizes) {
            throw_matrix_noneq_error(sizes, rhs.sizes);
        }
        for (int i = 0; i < mem_size; i++) {
            T t = *(mem + i) - *(rhs.mem + i);
            T *ptr = mem + i;
            ptr = &t;
        }
        return *this;
    }

    friend narray<T> operator-(narray<T> lhs, narray<T> const &rhs) {
        lhs -= rhs;
        return lhs;
    }

    narray<T> &operator*=(narray<T> const &rhs) {
        if (sizes != rhs.sizes) {
            throw_matrix_noneq_error(sizes, rhs.sizes);
        }
        for (int i = 0; i < mem_size; i++) {
            T t = *(mem + i) * *(rhs.mem + i);
            T *ptr = mem + i;
            ptr = &t;
        }
        return *this;
    }

    friend narray<T> operator*(narray<T> lhs, narray<T> const &rhs) {
        lhs *= rhs;
        return lhs;
    }


    narray<T> dot_product(narray<T> other);


    narray<T> &transpose(int axis1 = 0, int axis2 = 1);

    T *at(std::vector<int> coord) const;

protected:

private:
    T *mem;
    std::allocator<T> allocator;
    std::vector<int> sizes;
    std::vector<int> stride_info;
    int mem_size;
    memory_policy<T> *mem_policy;
public:
    //Test purpose

    inline std::vector<int> get_sizes() {
        return sizes;
    }

private:
    template<class B,
            template<class...> class Container,
            class... extras>
    void flat_transfer(std::vector<T> &target, const Container<B, extras...> &source, std::vector<int> &flat_sizes) {

        for (const auto &elem: source) {
            if constexpr (std::is_same<T, B>::value) {
                target.push_back(elem);
            } else {

                flat_transfer(target, elem, flat_sizes);
            }
        }
    };

    template<class B,
            template<class...> class Container,
            class... extras>
    void detect_sizes(const Container<B, extras...> &source, std::vector<int> &flat_sizes) {
        flat_sizes.push_back(source.size());
        if constexpr (!std::is_same<T, B>::value) {
            detect_sizes(source.front(), flat_sizes);
        }
    }
};


#endif //NEURONET_NARRAY_H
