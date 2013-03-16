// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_H_
#define _FOUNDATION_H_

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>

#include <foundation/assert.h>
#include <foundation/preprocessor.h>
#include <foundation/algorithm.h>
#include <foundation/digest.h>
#include <foundation/memory.h>

#include <foundation/allocator.h>
#include <foundation/proxy_allocator.h>
#include <foundation/scratch_allocator.h>
#include <foundation/temp_allocator.h>

#include <foundation/string.h>
#include <foundation/native_string.h>

#include <foundation/path.h>

#include <foundation/array.h>
#include <foundation/intrusive_list.h>
#include <foundation/ring_buffer.h>
#include <foundation/dictionary.h>

#include <foundation/atomics.h>
#include <foundation/thread.h>
#include <foundation/mutex.h>
#include <foundation/condition_variable.h>

#include <foundation/directory.h>
#include <foundation/mapped_file.h>

#include <foundation/debug_info.h>
#include <foundation/crash_handler.h>

#endif // _FOUNDATION_H_