
#include "streams/sparse.h"
#include "core/template_decl.h"
#include "core/logger.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    #include "gui/sparse_widget.h"
#endif

namespace roviz
{

// TODO Make this dynamic
// If we do this within Sparse<T>, it will get instantiated multiple times
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
const QColor SparseColor[] =
{
    Qt::red,
    Qt::blue,
    Qt::green,
    Qt::magenta,
    Qt::cyan,
    Qt::darkRed,
    Qt::darkBlue,
    Qt::darkGreen,
    Qt::darkMagenta,
    Qt::darkCyan
};
#endif

template<class T>
Sparse<T>::Sparse(Image base_image, std::initializer_list<SourceID> sources)
    : _this(new SparsePrivate<T>)
{
    this->_this_base.reset(_this);
    this->initSources(sources);
    _this->base_image = base_image;
}

template<class T>
Sparse<T>::Sparse(const StreamObject &base)
{
    this->_this_base = base._this_base;
    _this = dynamic_cast<SparsePrivate<T>*>(this->_this_base.get());
    logger->critical_if(_this == nullptr, "Trying to construct a Sparse form a StreamObject that isn't a Sparse or has the wrong type");
}

template<class T>
void Sparse<T>::add(const T &obj)
{
    _this->data.push_back(obj);
}

template<class T>
void Sparse<T>::add(const std::list<T> &objs)
{
    _this->data.reserve(this->size() + objs.size());
    for(const auto &obj : objs)
        _this->data.push_back(obj);
}

template<class T>
void Sparse<T>::add(const std::vector<T> &objs)
{
    _this->data.reserve(this->size() + objs.size());
    for(const auto &obj : objs)
        _this->data.push_back(obj);
}

template<class T>
std::size_t Sparse<T>::size()
{
    return _this->data.size();
}

template<class T>
const T &Sparse<T>::at(unsigned int index)
{
    if(index < this->size())
        return _this->data[index];

    logger->error("Sparse entry index out of bounds ({})", index);
    return _this->default_value;
}

template<class T>
const T &Sparse<T>::operator[](unsigned int index)
{
    return _this->data[index];
}

template<class T>
Image Sparse<T>::baseImage()
{
    return _this->base_image;
}

template<class T>
typename std::vector<T>::const_iterator Sparse<T>::begin() const
{
    return _this->data.cbegin();
}

template<class T>
typename std::vector<T>::const_iterator Sparse<T>::end() const
{
    return _this->data.cend();
}

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
template<class T>
StreamWidget *Sparse<T>::initWidget(OutputPrivate *out)
{
    return new SparseWidget(&SparseWidget::draw<T>, Sparse<T>(),
                            [](StreamObject obj){Sparse<T> s(obj); return s.baseImage();},
                            out);
}
#endif

#define INSTANTIATE_SPARSE(T)          template class Sparse<T>;
#define INSTANTIATE_SPARSE_PRIVATE(T)  template class SparsePrivate<T>;

ROVIZ_DO_FOR_ALL_SPARSE_TYPES(INSTANTIATE_SPARSE)
ROVIZ_DO_FOR_ALL_SPARSE_TYPES(INSTANTIATE_SPARSE_PRIVATE)

}
