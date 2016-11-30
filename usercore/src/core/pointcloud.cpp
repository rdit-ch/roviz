
#include "core/pointcloud.h"
#include "core/pointcloud_p.h"

Pointcloud::Pointcloud(std::initializer_list<SourceID> sources)
    : _this(new PointcloudPrivate(this, -1))
{
    if(sources.size() == 0)
    {
        _this->id = nullptr;
    }
    else
    {
        _this->id = std::make_shared<ImageSrcTreeNode>();
        _this->id->sources = std::vector<SourceID>(sources);
    }
}

Pointcloud::~Pointcloud()
{
}

Pointcloud::Pointcloud(const int dim)
    : _this(new PointcloudPrivate(this, dim))
{
    _this->id = nullptr;
}

Pointcloud::Pointcloud(const int dim, SourceID id)
    : _this(new PointcloudPrivate(this, dim))
{
    _this->id = id;
}

Pointcloud::Pointcloud(const Pointcloud &other)
    : _this(new PointcloudPrivate(this, _this->dim))
{
    *_this = *other._this;
}

Pointcloud &Pointcloud::operator =(const Pointcloud &other)
{
    *_this = *other._this;
    return *this;
}

Point Pointcloud::first()
{
    return _this->raw_points.data();
}

Point Pointcloud::last()
{
    return _this->raw_points.data() + _this->raw_points.size();
}

size_t Pointcloud::size()
{
    return _this->raw_points.size() / _this->dim;
}

Point Pointcloud::operator[](unsigned int i)
{
    return this->at(i);
}

int Pointcloud::dimension()
{
    return _this->dim;
}

Point Pointcloud::at(unsigned int i)
{
    return _this->raw_points.data() + (i * _this->dim);
}

SourceID Pointcloud::id()
{
    return _this->id;
}
