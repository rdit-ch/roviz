#ifndef TEMPLATE_DECL_HELPERS_H
#define TEMPLATE_DECL_HELPERS_H

#ifndef ROVIZ_EXPORT
    #define INIT_STREAM_CPP(T, color) \
        STARTUP_ADD_COMPONENT(StreamInit##T) \
        void StreamInit##T::init() \
        { \
            AbstractItem::registerConnectorStyle(color, qMetaTypeId<Stream<T>*>()); \
        }
#else
    #define INIT_STREAM_CPP(T, color)
#endif

#define INSTANTIATE_ROVIZ_ITEM_P(T) \
    template Input RovizItem::addInput<T>(std::string name); \
    template Output RovizItem::addOutput<T>(std::string name); \
    template T RovizItem::next<T>(Input in); \
    template T RovizItem::newest<T>(Input in);

// The '##' is needed to prevent expansion
#define INSTANTIATE_ROVIZ_ITEM \
    DO_FOR_ALL_STREAMS(INSTANTIATE_ROVIZ_ITEM##_P)

#define INSTANTIATE_ROVIZ_BASE_P(T) \
    template Input RovizItemBase::addInputBase<T>(std::string name); \
    template Output RovizItemBase::addOutputBase<T>(std::string name);

#define INSTANTIATE_ROVIZ_BASE \
    DO_FOR_ALL_STREAMS(INSTANTIATE_ROVIZ_BASE##_P)

#define DO_FOR_ALL_CONFIG_TYPES(EXPR) \
    EXPR(int) \
    EXPR(double) \
    EXPR(bool) \
    EXPR(std::string) \
    EXPR(std::list<std::string>) \
    EXPR(FilePath)

#define INSTANTIATE_CONFIG_P(T) \
    template class Config<T>;

#define INSTANTIATE_CONFIG_PRIVATE_P(T) \
    template class ConfigPrivate<T>;

#define INSTANTIATE_CONFIG_IMPL_P(T) \
    template class ConfigImpl<T>;

#define INSTANTIATE_CONFIG \
    DO_FOR_ALL_CONFIG_TYPES(INSTANTIATE_CONFIG##_P)

#define INSTANTIATE_CONFIG_PRIVATE \
    DO_FOR_ALL_CONFIG_TYPES(INSTANTIATE_CONFIG_PRIVATE##_P)

#define INSTANTIATE_CONFIG_IMPL \
    DO_FOR_ALL_CONFIG_TYPES(INSTANTIATE_CONFIG_IMPL##_P)

#define INSTANTIATE_STREAM_P(T) \
    template class Stream<T>;

#define INSTANTIATE_STREAM \
    DO_FOR_ALL_STREAMS(INSTANTIATE_STREAM##_P)

#define MAKE_ALL_STREAMS_A_FRIEND_P(T) \
    friend class T;

#define MAKE_ALL_STREAMS_A_FRIEND \
    DO_FOR_ALL_STREAMS(MAKE_ALL_STREAMS_A_FRIEND##_P)

#endif // TEMPLATE_DECL_HELPERS_H
