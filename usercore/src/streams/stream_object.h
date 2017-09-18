#ifndef STREAM_OBJECT_H
#define STREAM_OBJECT_H

#include <memory>
#include <vector>
#include "core/template_decl.h"
#include "core/export_handling.h"

#define MAKE_ALL_STREAMS_A_FRIEND(T) friend class T;

struct SrcTreeNode;
class StreamObjectPrivate;

/**
 * @brief The ID and source tree of an image
 *
 * Every time an object is created, you have to say where the origins of
 * that object lie. If you create an object which is constructed from
 * another image, you tell the object that this image is its source. For
 * example, image1 is at the input of a filter item and image2 is at its
 * output. Then the source of image2 would be image1.  That way, you can
 * easily recover a source tree and determine the original image after a
 * long filtering pipeline.
 *
 * \sa Stream
 * \sa StreamObjectPrivate
 */
typedef std::shared_ptr<SrcTreeNode> SourceID;

/**
 * @brief A node of the source-tree
 */
struct SrcTreeNode
{
    std::vector<SourceID> sources;
};

/**
 * @brief Base class of all objects that can be transported with a stream
 */
class ROVIZ_EXPORT StreamObject
{
// Needed because we have to access the protected members of a StreamObject
// which is not 'this' in the conversion constructors of the derived classes.
DO_FOR_ALL_STREAMS(MAKE_ALL_STREAMS_A_FRIEND)

COPY_DEFAULT(StreamObject)
MOVE_DEFAULT(StreamObject)

public:
    StreamObject() = default;
    virtual ~StreamObject() = default;

    /**
     * @brief Get the SourceID of the object
     * @return The SourceID
     */
    SourceID id(void) const;

protected:
    std::shared_ptr<StreamObjectPrivate> _this_base;

    // Cannot be done in the constructer, because the derived class has to
    // initialize the private data first.
    void initSources(std::initializer_list<SourceID> sources = {});

    // C++ doesn't allow this, just make sure the object implements such a
    // function.
//  virtual static QWidget *initWidget(StreamBase *stream);
};

DECLARE_STREAM_OBJECT(StreamObject)

#endif // STREAM_OBJECT_H
