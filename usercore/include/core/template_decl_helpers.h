#ifndef TEMPLATE_DECL_HELPERS_H
#define TEMPLATE_DECL_HELPERS_H

#include "core/export_handling.h"

#define INSTANTIATE_ROVIZ_ITEM_P(T) \
    template Input<T> RovizItem::addInput<T>(std::string name); \
    template Output<T> RovizItem::addOutput<T>(std::string name); \
    template Config<int> RovizItem::addConfig<int>(const std::string &name, const typename ConfigStorageType<int>::type &default_value, int min, int max, bool restart_when_changed); \
    template Config<double> RovizItem::addConfig<double>(const std::string &name, const typename ConfigStorageType<double>::type &default_value, double min, double max, bool restart_when_changed); \
    template Config<std::string> RovizItem::addConfig<std::string>(const std::string &name, const typename ConfigStorageType<std::string>::type &default_value, std::function<bool (std::string&)> checker, bool restart_when_changed); \
    template Config<std::vector<std::string> > RovizItem::addConfig<std::vector<std::string> >(const std::string &name, const typename ConfigStorageType<std::vector<std::string> >::type &default_index, const std::vector<std::string> &possibilities, bool restart_when_changed); \
    template Config<bool> RovizItem::addConfig<bool>(const std::string &name, const typename ConfigStorageType<bool>::type &default_value, bool restart_when_changed); \
    template Config<FilePath> RovizItem::addConfig<FilePath>(const std::string &name, const typename ConfigStorageType<FilePath>::type &default_value, enum FilePath::Mode file_mode, const std::string &filter, bool restart_when_changed);

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
    EXPR(std::vector<std::string>) \
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
