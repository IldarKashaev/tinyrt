#ifndef TINYRT_COMMON_H_
#define TINYRT_COMMON_H_

namespace tinyrt {

#if defined(_MSC_VER)  // Microsoft Visual Studio
#define TINYGRAD_INLINE __forceinline
#elif defined(__GNUC__)  // GCC
#define TINYGRAD_INLINE inline __attribute__((always_inline))
#elif defined(__clang__)  // Clang
#define TINYGRAD_INLINE inline __attribute__((always_inline))
#elif defined(__INTEL_COMPILER)  // Intel compiler
#define TINYGRAD_INLINE __forceinline
#else
#define TINYGRAD_INLINE inline  // Other compilers, use standard inline
#endif

}  // namespace tinyrt

#endif  // TINYRT_COMMON_H_
