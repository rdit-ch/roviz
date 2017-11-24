
#include "streams/sparse_m.h"
#include "streams/all_streams.h"

// If I just use '_this' instead of 'this->_this', the compiler complains.
// No idea why.

namespace roviz
{

template<class T>
SparseMutable<T>::SparseMutable(Image base_image, std::initializer_list<SourceID> sources)
    : Sparse<T>(base_image, sources)
{
}

template<class T>
T &SparseMutable<T>::at(unsigned int index)
{
    if(index >= this->size())
        return this->_this->default_value;
    else
        return this->_this->data[index];
}

template<class T>
T &SparseMutable<T>::operator[](unsigned int index)
{
    return this->_this->data[index];
}

template<class T>
typename std::vector<T>::iterator SparseMutable<T>::begin()
{
    return this->_this->data.begin();
}

template<class T>
typename std::vector<T>::iterator SparseMutable<T>::end()
{
    return this->_this->data.end();
}

#define INSTANTIATE_SPARSE_MUTABLE(T) template class SparseMutable<T>;

ROVIZ_DO_FOR_ALL_SPARSE_TYPES(INSTANTIATE_SPARSE_MUTABLE)

}
