#ifndef _SYS_CDEFS_H
#define _SYS_CDEFS_H

#ifndef __has_attribute
#define __has_attribute(foo) 0
#endif

#ifndef __cplusplus
#define __THROW
#define __BEGIN_DECLS
#define __END_DECLS
#else
#define __THROW throw ()
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#endif

#ifndef __GNUC__
#define __attribute__(xyz)
#define __extension__
#endif

#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6))
#define __leaf , __leaf__
#else
#define __leaf
#endif

#if defined(__clang__) && __has_attribute(leaf)
#undef __leaf
#define __leaf
#endif

#if !defined(__cplusplus) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3)))
#undef __THROW
#define __THROW __attribute__((__nothrow__ __leaf))
#define __THROWNL __attribute__((__nothrow__))
#endif

#ifndef __THROWNL
#define __THROWNL __THROW
#endif

#if (__GNUC__ > 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 96))
#define __pure __attribute__ ((__pure__))
#else
#define __pure
#endif

#if (__GNUC__ == 2) && (__GNUC_MINOR__ < 95)
#define __restrict__
#endif

#ifndef __STRICT_ANSI__
#define restrict __restrict__
#if __GNUC__ < 3
#define __builtin_expect(foo,bar) (foo)
#define __expect(foo,bar) (foo)
#define __malloc__
#else
#define __expect(foo,bar) __builtin_expect((long)(foo),bar)
#define __attribute_malloc__ __attribute__((__malloc__))
#if __GNUC__ < 11
#define __attribute_specific_free__(a,b) __attribute_malloc__
#else
#define __attribute_specific_free__(func,argpos) __attribute__((malloc, malloc(func,argpos)))
#endif
#endif
#else
#define __attribute_specific_free__(a,b)
#endif

/* idea for these macros taken from Linux kernel */
#define __likely(foo) __builtin_expect((foo),1)
#define __unlikely(foo) __builtin_expect((foo),0)

#ifndef __attribute_malloc__
#define __attribute_malloc__
#endif

#define __P(x) x

#define __ptr_t void*

#if defined(__STRICT_ANSI__) && __STDC_VERSION__ + 0 < 199900L
#define inline
#endif

#ifndef __i386__
#define __regparm__(x)
#endif

#if (__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 2))
#define __attribute_dontuse__ __attribute__((__deprecated__))
#else
#define __attribute_dontuse__
#define __deprecated__
#endif

#if (__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3))
# define __nonnull(params) __attribute__ ((__nonnull__ params))
#else
# define __nonnull(params)
#endif

#if (__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 4))
# define __attribute_used __attribute__ ((__used__))
#else
# define __attribute_used
# define __warn_unused_result__
#endif

#if (__GNUC__ >= 4)
#define __needsNULL__(x) __sentinel__(x)
#else
#define __needsNULL__(x)
#define __sentinel__
#endif

#if (__GNUC__ < 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ < 3))
# define __cold__
# define __hot__
#endif

#if (__GNUC__ < 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ < 3))
#define __attribute_alloc__(x)
#define __attribute_alloc2__(x,y)
#else
#define __attribute_alloc__(x) __attribute__((alloc_size(x)))
#define __attribute_alloc2__(x,y) __attribute__((alloc_size(x,y)))
#endif

#if (__GNUC__ < 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ < 5))
#define __attribute_const__
#else
#define __attribute_const__ __attribute__((const))
#endif

#if (__GNUC__ < 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ < 8))
#define __attribute_formatarg__(x)
#else
#define __attribute_formatarg__(x) __attribute__((format_arg(x)))
#endif

#if (__GNUC__ < 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ < 1))
#define __dontinline__
#else
#define __dontinline__ __attribute__((noinline))
#endif

#if (__GNUC__ < 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ < 6))
#define __hidden__
#else
#define __hidden__ __attribute__((visibility("hidden")))
#endif

#if (__GNUC__ < 10)
#define __readmem__(argno_ptr)
#define __readmemsz__(argno_ptr, argno_size)
#define __writemem__(argno_ptr)
#define __writememsz__(argno_ptr, argno_size)
#define __readwritemem__(argno_ptr)
#define __readwritememsz__(argno_ptr, argno_size)
#else
#define __readmem__(argno_ptr) __attribute__((access(read_only, argno_ptr)))
#define __readmemsz__(argno_ptr, argno_size) __attribute__((access(read_only, argno_ptr, argno_size)))
#define __writemem__(argno_ptr) __attribute__((access(write_only, argno_ptr)))
#define __writememsz__(argno_ptr, argno_size) __attribute__((access(write_only, argno_ptr, argno_size)))
#define __readwritemem__(argno_ptr) __attribute__((access(read_write, argno_ptr)))
#define __readwritememsz__(argno_ptr, argno_size) __attribute__((access(read_write, argno_ptr, argno_size)))
#endif

#if (__GNUC__ < 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ < 3))
#define __warn(message)
#define __error(message)
#else
#define __warn(message) __attribute__((warning(message)))
#define __error(message) __attribute__((error(message)))
#endif

#if __has_attribute(diagnose_if)
#define __condwarn(condition, message) diagnose_if(condition, message, "warning")
#define __conderr(condition, message) diagnose_if(condition, message, "error")
#else
#define __condwarn(condition, message)
#define __conderr(condition, message)
#endif

#if __has_attribute(enable_if)
#endif

#if __has_attribute(callback)
#define __callback(...) callback(__VA_ARGS__)
#else
#define __callback(...)
#endif

#if !__has_attribute(null_terminated_string_arg)
#define null_terminated_string_arg(x)
#endif

#if __has_attribute(access)
#define __access(a,b) access(a,b)
#define __access3(a,b,c) access(a,b,c)
#else
#define __access(a,b)
#define __access3(a,b,c)
#endif
#define __strin(idx) __attribute__((nonnull(idx),__access(read_only,idx),null_terminated_string_arg(idx)))
#define __strnin(idx,szidx) __attribute__((nonnull(idx),__access3(read_only,idx,szidx),null_terminated_string_arg(idx)))
#define __bufin(bufidx,szidx) __attribute__((nonnull(bufidx),__access3(read_only,bufidx,szidx)))
#define __strout(idx) __attribute__((nonnull(idx),__access(write_only,idx)))
#define __strnout(idx,szidx) __attribute__((nonnull(idx),__access3(write_only,idx,szidx)))
#define __bufout(bufidx,szidx) __attribute__((nonnull(bufidx),__access3(write_only,bufidx,szidx)))
#define __strinout(idx) __attribute__((nonnull(idx),__access(read_write,idx)))
#define __strninout(idx,szidx) __attribute__((nonnull(idx),__access3(read_write,idx,szidx),null_terminated_string_arg(idx)))
#define __bufinout(bufidx,szidx) __attribute__((nonnull(bufidx),__access3(read_write,bufidx,szidx)))

#if __has_attribute(ownership_takes)
#define __new __attribute__((ownership_returns(malloc)))
#define __free(idx) __attribute__((ownership_takes(malloc, idx)))
#define __holds(idx) __attribute__((ownership_holds(malloc, idx)))
#else
#define __new
#define __free(idx)
#define __holds(idx)
#endif

#endif
