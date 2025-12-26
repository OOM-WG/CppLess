//====================================================================================================
// Copyright (C) 2016-present ShIroRRen <http://shiror.ren>.                                         =
//                                                                                                   =
// Licensed under the F2DLPR License.                                                                =
//                                                                                                   =
// YOU MAY NOT USE THIS FILE EXCEPT IN COMPLIANCE WITH THE LICENSE.                                  =
// Provided "AS IS", WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,                                   =
// unless required by applicable law or agreed to in writing.                                        =
//                                                                                                   =
// For the F2DLPR License terms and conditions, visit: <http://license.fileto.download>.             =
//====================================================================================================

#pragma once

#include <initializer_list>
#include <utility>

#define __cppless_concat_impl(a, b) a##b
#define __cppless_concat(a, b)		__cppless_concat_impl(a, b)

#define defer_func(_____)                                    \
	[[maybe_unused]]                                         \
	auto const __cppless_concat(__defer_func__, __COUNTER__) \
			= [&]<typename _>(_&& __) {                      \
		struct ___ {                                         \
			_ __;                                            \
			~___() { __(); }                                 \
		} ____{ std::forward<_>(__) };                       \
		return ____;                                         \
	}([&]() _____)

#define let(_, __) ([&](auto&& it) -> decltype(auto) __(_))

#define also(__, ___)                            \
	([&]<typename _>(_&& it) -> decltype(auto) { \
		___;                                     \
		return std::forward<_>(it);              \
	}(__))

template<typename T>
class when {
   public:
	explicit when(T const& v): val(v), ok(false) {}
	template<class F>
	when& add_case(T const& target, F&& func) {
		if (!ok && val == target) ok = (func(val), true);
		return *this;
	}
	template<class F>
	when& add_case(std::initializer_list<T> targets, F&& func) {
		if (!ok)
			for (auto const& target : targets)
				if (val == target) {
					ok = (func(val), true);
					break;
				}
		return *this;
	}
	template<class F>
	void default_case(F&& func) {
		if (!ok) func(val);
	}

   private:
	T const& val;
	bool	 ok;
};