#ifndef TEMPLATE_DECL_HELPERS_H
#define TEMPLATE_DECL_HELPERS_H

#include "core/export_handling.h"

#define INSTANTIATE_ROVIZ_ITEM_P(T) \
    template Input<T> RovizItem::addInput<T>(std::string name); \
    template Output<T> RovizItem::addOutput<T>(std::string name);

// The '##' is needed to prevent expansion
#define INSTANTIATE_ROVIZ_ITEM \
    DO_FOR_ALL_STREAMS(INSTANTIATE_ROVIZ_ITEM##_P)

#define INSTANTIATE_ROVIZ_BASE_P(T) \
    template Input<T> RovizItemBase::addInputBase<T>(std::string name, RovizItem *item); \
    template Output<T> RovizItemBase::addOutputBase<T>(std::string name);

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

#define INSTANTIATE_CONFIG_IMPL_P(T) \
    template class CONCAT(ConfigImpl, ROVIZ_SELECTED_BACKEND)<T>;

#define INSTANTIATE_CONFIG \
    DO_FOR_ALL_CONFIG_TYPES(INSTANTIATE_CONFIG##_P)

#define INSTANTIATE_CONFIG_IMPL \
    DO_FOR_ALL_CONFIG_TYPES(INSTANTIATE_CONFIG_IMPL##_P)

#define MAKE_ALL_STREAMS_A_FRIEND_P(T) \
    friend class T;

#define MAKE_ALL_STREAMS_A_FRIEND \
    DO_FOR_ALL_STREAMS(MAKE_ALL_STREAMS_A_FRIEND##_P)

#define INSTANTIATE_SPARSE_P(T) \
    template class Sparse<T>;

#define INSTANTIATE_SPARSE \
    DO_FOR_ALL_SPARSE(INSTANTIATE_SPARSE##_P)

#define INSTANTIATE_SPARSE_PRIVATE_P(T) \
    template class SparsePrivate<T>;

#define INSTANTIATE_SPARSE_PRIVATE \
    DO_FOR_ALL_SPARSE(INSTANTIATE_SPARSE_PRIVATE##_P)

#define INSTANTIATE_SPARSE_MUTABLE_P(T) \
    template class SparseMutable<T>;

#define INSTANTIATE_SPARSE_MUTABLE \
    DO_FOR_ALL_SPARSE(INSTANTIATE_SPARSE_MUTABLE##_P)

#define INSTANTIATE_INPUT_P(T) \
    template class Input<T >;

#define INSTANTIATE_INPUT \
    DO_FOR_ALL_STREAMS(INSTANTIATE_INPUT##_P)

#define INSTANTIATE_OUTPUT_P(T) \
    template class Output<T >;

#define INSTANTIATE_OUTPUT \
    DO_FOR_ALL_STREAMS(INSTANTIATE_OUTPUT##_P)

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#define INSTANTIATE_SPARSE_WIDGET_P(T) \
    template void SparseWidget::draw<T>(void);

#define INSTANTIATE_SPARSE_WIDGET \
    DO_FOR_ALL_SPARSE(INSTANTIATE_SPARSE_WIDGET##_P)
#endif

#endif // TEMPLATE_DECL_HELPERS_H
