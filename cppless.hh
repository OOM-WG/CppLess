//====================================================================================================
// Copyright (C) 2016-present Anne Sakitin (Tianwan Ayana).                                          =
//                                                                                                   =
// Licensed under the F2DLPR License.                                                                =
//                                                                                                   =
// YOU MAY NOT USE THIS FILE EXCEPT IN COMPLIANCE WITH THE LICENSE.                                  =
// Provided "AS IS", WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,                                   =
// unless required by applicable law or agreed to in writing.                                        =
//                                                                                                   =
// For details about the F2DLPR License terms and conditions, visit: http://license.fileto.download. =
//====================================================================================================

#pragma once

#include <utility>

#define __cppless_concat_impl(a, b) a##b
#define __cppless_concat(a, b)      __cppless_concat_impl(a, b)

#define defer_func(_____)                                                                 \
    [[maybe_unused]] auto const __cppless_concat(__defer_func__,                          \
                                                 __COUNTER__) = [&]<typename _>(_&& __) { \
        struct ___ {                                                                      \
            _ __;                                                                         \
            ~___() { __(); }                                                              \
        } ____{std::forward<_>(__)};                                                      \
        return ____;                                                                      \
    }([&]() _____)

#define let(_, __) ([&](auto&& it) -> decltype(auto) __(_))

#define also(__, ___)                            \
    ([&]<typename _>(_&& it) -> decltype(auto) { \
        ___;                                     \
        return std::forward<_>(it);              \
    }(__))
