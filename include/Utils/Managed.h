#ifndef MANAGED_H
#define MANAGED_H

#include <utility>

#include <memory>

template<typename... Args>
using OwnPtr = std::unique_ptr<Args...>;

#define make_ownptr std::make_unique

template<typename... Args>
using RefPtr = std::shared_ptr<Args...>;

#define make_refptr std::make_shared;

template<typename... Args>
using WeakPtr = std::weak_ptr<Args...>;

#endif // MANAGED_H
