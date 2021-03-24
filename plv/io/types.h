#ifndef PLV_IO_TYPES_H
#define PLV_IO_TYPES_H
#include <plv/types.h>
#include <asio/awaitable.hpp>

namespace plv
{
template <typename T>
using Awaitable = asio::awaitable<T>;
}  // namespace plv
#endif  // PLV_IO_TYPES_H