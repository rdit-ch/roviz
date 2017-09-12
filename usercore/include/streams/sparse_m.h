#ifndef SPARSE_M_H
#define SPARSE_M_H

#include <vector>
#include "streams/sparse.h"

template<class T>
class ROVIZ_EXPORT SparseMutable : public Sparse<T>
{
public:
    SparseMutable(Image base_image = Image(), std::initializer_list<SourceID> sources = {});
    T &at(unsigned int index);
    T &operator[](unsigned int index);
    typename std::vector<T>::iterator begin(void);
    typename std::vector<T>::iterator end(void);
};

#endif // SPARSE_M_H
