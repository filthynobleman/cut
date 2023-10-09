/**
 * @file        allocation.hpp
 * 
 * @brief       Low level memory handling.
 * 
 * @details     This file contains functions for low level memory handling. In particular,
 *              it offers templated variants of the STL functions or combinations of them.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-09
 */
#pragma once

#include <cstdlib>
#include <cut/excepts/excepts.hpp>

namespace cut
{
    
template<typename T>
T* Malloc(size_t numel, size_t elsize = sizeof(T))
{
    T* res = (T*)std::malloc(numel * elsize);
    CUTCheckNull(res);
    return res;
}

template<typename T>
T* Calloc(size_t numel, size_t elsize = sizeof(T))
{
    T* res = (T*)std::calloc(numel, elsize);
    CUTCheckNull(res);
    return res;
}

template<typename T>
T* Memcpy(T* dst, T* src, size_t numel, size_t elsize = sizeof(T))
{
    dst = (T*)std::memcpy(dst, src, numel * elsize);
    CUTCheckNull(dst);
    return dst;
}

template<typename T>
T* AllocCopy(T* src, size_t numel, size_t elsize = sizeof(T))
{
    T* res = cut::Malloc<T>(numel, elsize);
    return cut::Memcpy(res, src, numel, elsize);
}

template<typename T>
T* AllocInit(size_t numel, const T& value)
{
    T* res = cut::Malloc<T>(numel);
    for (size_t i = 0; i < numel; ++i)
        res[i] = value;
    // for (size_t i = 0; i < numel; ++i)
    //     std::memcpy(res + i, &value, sizeof(T));
    return res;
}

} // namespace cut
