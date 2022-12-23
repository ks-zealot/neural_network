//
// Created by zealot on 20.12.2022.
//

#ifndef NEURONET_ZIP_ITERATOR_H
#define NEURONET_ZIP_ITERATOR_H

#include <tuple>
#include <vector>

template <typename Iter>
using select_access_type_for = std::conditional_t<
        std::is_same_v<Iter, std::vector<bool>::iterator> ||
        std::is_same_v<Iter, std::vector<bool>::const_iterator>,
        typename std::iterator_traits<Iter>::value_type,
        typename std::iterator_traits<Iter>::reference
>;

/*  The index sequence is only used to deduce the Index sequence in the template
    declaration. It uses a fold expression which is applied to the indexes,
    using each expanded value to compare tuple value at that index. If any of
    the tuple elements are equal, the function will return true. */
template <typename ... Args, std::size_t ... Index>
auto any_match_impl(std::tuple<Args...> const & lhs,
                    std::tuple<Args...> const & rhs,
                    std::index_sequence<Index...>) -> bool {
    return (... | (std::get<Index>(lhs) == std::get<Index>(rhs)));
}


/*  User function for finding any elementwise match in two tuples. Forwards to
    to the implementation the two tuples along with a generated index sequence
    which will have the same length as the tuples. */
template <typename ... Args>
auto any_match(std::tuple<Args...> const & lhs,
               std::tuple<Args...> const & rhs) -> bool {
    return any_match_impl(lhs, rhs, std::index_sequence_for<Args...>{});
}


template <typename ... Iters>
class zip_iterator
{
public:
    using value_type = std::tuple<
    select_access_type_for<Iters>...
    >;

    zip_iterator() = delete;

    zip_iterator(Iters && ... iters)
            : m_iters {std::forward<Iters>(iters)...}
    {
    }

    /* Increment all the underlying iterators */
    auto operator++() -> zip_iterator& {
        std::apply([](auto & ... args){
            ((args += 1), ...);
        }, m_iters);
        return *this;
    }

    auto operator++(int) -> zip_iterator {
        auto tmp = *this;
        ++*this;
        return tmp;
    }

    auto operator!=(zip_iterator const & other){
        return !(*this == other);
    }

    /*  Elementwise compare another iterator of this type to detect if any
        of the elements match. */
    auto operator==(zip_iterator const & other){
        return any_match(m_iters, other.m_iters);
    }

    /*  Dereference operator that constructs a tuple (`value_type`) by
        expanding and dereferencing each of the underlying iterators in */
    auto operator*() -> value_type {
        return std::apply([](auto && ... args){
            return value_type(*args...);
        }, m_iters);
    }

private:
    std::tuple<Iters...> m_iters;
};
#endif //NEURONET_ZIP_ITERATOR_H
