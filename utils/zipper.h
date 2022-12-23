//
// Created by zealot on 20.12.2022.
//

#ifndef NEURONET_ZIPPER_H
#define NEURONET_ZIPPER_H

#include <utility>
#include "zip_iterator.h"

template <typename T>
using select_iterator_for = std::conditional_t<
        std::is_const_v<std::remove_reference_t<T>>,
        typename std::decay_t<T>::const_iterator,
        typename std::decay_t<T>::iterator>;


template <typename ... T>
class zipper
{
public:
    using zip_type = zip_iterator<select_iterator_for<T> ...>;

    /*  std::forward is used to preserve the value category of the
        containers */
    template <typename ... Args>
    zipper(Args && ... args)
            : m_args{std::forward<Args>(args)...}
    {
    }

    auto begin() -> zip_type {
        return std::apply([](auto && ... args){
            return zip_type(std::begin(args)...);
        }, m_args);
    }

    auto end() -> zip_type {
        return std::apply([](auto && ... args){
            return zip_type(std::end(args)...);
        }, m_args);
    }

private:
    std::tuple<T ...> m_args;
};

#endif //NEURONET_ZIPPER_H
