//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//
// interface_helpers.h: Implementation declarations/definitions for Interface helper methods and macros
//

#pragma once
#include "spxcore_common.h"
#include "shared_ptr_helpers.h"
#include "string_utils.h"


namespace Microsoft {
namespace CognitiveServices {
namespace Speech {
namespace Impl {


#ifdef SPX_CONFIG_TRACE_INTERFACE_MAP
#define SPX_DBG_TRACE_INTERFACE_MAP_BEGIN() SPX_DBG_TRACE_VERBOSE("QUERYINTERFACE: interface=%s ; looking in %s ...", interfaceName, __FUNCTION__)
#define SPX_DBG_TRACE_INTERFACE_MAP_FOUND_IT() SPX_DBG_TRACE_VERBOSE("QUERYINTERFACE: interface=%s ; looking in %s ... FOUND IT!!", interfaceName, __FUNCTION__)
#else
#define SPX_DBG_TRACE_INTERFACE_MAP_BEGIN()
#define SPX_DBG_TRACE_INTERFACE_MAP_FOUND_IT()
#endif

#define SPX_INTERFACE_MAP_BEGIN()                                                       \
    void* QueryInterface(const char* interfaceName) override                            \
    {                                                                                   \
        SPX_DBG_TRACE_INTERFACE_MAP_BEGIN();

#define SPX_INTERFACE_MAP_BEGIN_NAMED(x)                                                \
    void* x(const char* interfaceName)                                                  \
    {                                                                                   \
        SPX_DBG_TRACE_INTERFACE_MAP_BEGIN();

#define SPX_INTERFACE_MAP_ENTRY(x)                                                      \
        if (PAL::stricmp(SpxTypeName(x), interfaceName) == 0)                           \
        {                                                                               \
            SPX_DBG_TRACE_INTERFACE_MAP_FOUND_IT();                                     \
            return static_cast<x*>(this);                                               \
        }

#define SPX_INTERFACE_MAP_ENTRY2(x, y)                                                  \
        if (PAL::stricmp(SpxTypeName(x), interfaceName) == 0)                           \
        {                                                                               \
            SPX_DBG_TRACE_INTERFACE_MAP_FOUND_IT();                                     \
            return static_cast<x*>(static_cast<y*>(this));                              \
        }

#define SPX_INTERFACE_MAP_FUNC(fn)                                                      \
        {                                                                               \
            auto ptr = fn(interfaceName);                                               \
            if (ptr != nullptr)                                                         \
            {                                                                           \
                SPX_DBG_TRACE_SERVICE_MAP_FOUND_IT();                                   \
                return ptr;                                                             \
            }                                                                           \
        }

#define SPX_INTERFACE_MAP_FUNC2(x, fn)                                                  \
        if (PAL::stricmp(PAL::GetTypeName<x>().c_str(), interfaceName) == 0)            \
        SPX_INTERFACE_MAP_FUNC(fn)

#define SPX_INTERFACE_MAP_END()                                                         \
        return nullptr;                                                                 \
    };


template<typename T, typename F, typename... Args>
bool InvokeMemberIfNotNull(std::shared_ptr<T> ptr, F fn, Args&&... args)
{
    if (ptr)
    {
        (((ptr.get()))->*fn)(std::forward<Args>(args)...);
        return true;
    }
    return false;
}

template <typename I, typename F>
inline bool TryQueryInterface(std::shared_ptr<ISpxInterfaceBase> obj, F fn)
{
    auto ptr = SpxQueryInterface<I>(obj);
    if (ptr)
    {
        fn(*ptr);
        return true;
    }
    return false;
}

template<typename T, typename U, typename F, typename... Args>
void QueryAndInvokeMember(std::shared_ptr<U> ptr, F fn, Args&&... args)
{
    auto o = ptr->template QueryInterface<T>();
    SPX_DBG_ASSERT(o != nullptr);
    (((o.get()))->*fn)(std::forward<Args>(args)...);
}

} } } } // Microsoft::CognitiveServices::Speech::Impl
