#pragma once
namespace singsing
{

/// 一个Tag类，实际没有作用，主要是用来标记那些类可以构造和析构
/// 因为在拷贝构造的时候，需要先拷贝基类，再拷贝派生类，当然这里是个空类没有意义
/// 不希望在非copyable子类中构造基类，所以放到了protected
class copyable
{
 protected:
  copyable() = default;
  ~copyable() = default;
};

}  // namespace singsing

