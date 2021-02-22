#ifndef BACKEND_SERVICE_H
#define BACKEND_SERVICE_H

namespace backend
{
class Service
{
public:
    virtual auto loadBlockchain() -> void = 0;
};
}  // namespace backend
#endif  // BACKEND_SERVICE_H