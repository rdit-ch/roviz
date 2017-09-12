#ifndef SPARSE_H
#define SPARSE_H

#include <memory>
#include <vector>
#include <list>
#include "streams/stream_object.h"
#include "streams/sparse_p.h"
#include "streams/image.h"
#include "streams/sparse_types.h"
#include "core/template_decl.h"

class OutputPrivate;
class StreamWidget;

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include <QColor>

#define POINT_RECT_SIZE   4
#define SPARSE_LINE_WIDTH 1

// If we do this within Sparse<T>, it will get instantiated multiple times
extern const QColor SparseColor[10];
#endif

template<class T> class SparsePrivate;

template<class T>
class ROVIZ_EXPORT Sparse : public StreamObject
{
public:
    Sparse(Image base_image = Image(), std::initializer_list<SourceID> sources = {});
    Sparse(const StreamObject &base);
    void add(const T &obj);
    void add(const std::list<T> &objs);
    void add(const std::vector<T> &objs);
    std::size_t size(void);
    const T &at(unsigned int index);
    const T &operator[](unsigned int index);
    Image baseImage(void);
    typename std::vector<T>::const_iterator begin(void) const;
    typename std::vector<T>::const_iterator end(void) const;

protected:
    SparsePrivate<T> *_this;

// Handle the displaying of the image
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
public:
    /**
     * @brief initWidget Returns a ImageWidget to display the image
     * @param stream The asocciated stream
     * @return The QWidget to show
     *
     * See 'How to create your own streams'
     */
    static StreamWidget *initWidget(OutputPrivate *out);
#endif
};

DO_FOR_ALL_SPARSE(DECLARE_STREAM_OBJECT)
DO_FOR_ALL_SPARSE_TEMPLATES(DECLARE_STREAM_OBJECT)

#endif // SPARSE_H
