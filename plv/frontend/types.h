#ifndef PLV_FRONTEND_TYPES_H
#define PLV_FRONTEND_TYPES_H
#include <plv/types.h>
#include <asio/awaitable.hpp>

namespace plv
{
template <typename T>
using Awaitable = asio::awaitable<T>;
}  // namespace plv
#endif  // PLV_FRONTEND_TYPES_H