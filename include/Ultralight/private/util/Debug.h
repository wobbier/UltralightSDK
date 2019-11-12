#pragma once

#include <iostream>
#include <Ultralight/Defines.h>
#include <Ultralight/private/util/DebugBreak.h>

#define CHECK_1(condition) { \
  if (!(condition)) { \
    std::cerr << "Check Failed: " << #condition << \
    " @ " << __FILE__ << \
    " (" << __LINE__ << ")" << std::endl; \
    debug_break(); \
  } \
}

#define CHECK_2(condition, message) { \
  if (!(condition)) { \
    std::cerr << "Check Failed: " << #condition << \
    " @ " << __FILE__ << \
    " (" << __LINE__ << ")" << std::endl; \
    std::cerr << "\tMessage: " << message << std::endl; \
    debug_break(); \
  } \
}

#define GET_3RD_ARG(arg1, arg2, arg3, ...) arg3
#define CHECK_CHOOSER(...) \
    GET_3RD_ARG(__VA_ARGS__, CHECK_2, CHECK_1, )
#define CHECK(...) CHECK_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#ifdef NDEBUG
#define DCHECK(...)
#define NOTREACHED()
#define NOTIMPLEMENTED()
#else

#define DCHECK_1(condition) { \
  if (!(condition)) { \
    std::cerr << "Check Failed: " << #condition << \
    " @ " << __FILE__ << \
    " (" << __LINE__ << ")" << std::endl; \
    debug_break(); \
  } \
}

#define DCHECK_2(condition, message) { \
  if (!(condition)) { \
    std::cerr << "Check Failed: " << #condition << \
    " @ " << __FILE__ << \
    " (" << __LINE__ << ")" << std::endl; \
    std::cerr << "\tMessage: " << message << std::endl; \
    debug_break(); \
  } \
}

#define DCHECK_CHOOSER(...) \
    GET_3RD_ARG(__VA_ARGS__, DCHECK_2, DCHECK_1, )
#define DCHECK(...) DCHECK_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#define NOTREACHED() { \
  std::cerr << "NOTREACHED() Hit: " << \
  " @ " << __FILE__ << \
  " (" << __LINE__ << ")" << std::endl; \
  debug_break(); \
}

#define NOTIMPLEMENTED() { \
  std::cerr << "NOTIMPLEMENTED() Hit: " << \
  " @ " << __FILE__ << \
  " (" << __LINE__ << ")" << std::endl; \
  debug_break(); \
}

#endif

