# Foundation

Foundation is a highly configurable and minimalistic library that provides
various functions, classes, macros, and preprocessor definitions to handle:

  * Compiler, platform, and architecture detection. See [include/foundation/detect.h](include/foundation/detect.h).
  * Compiler uniformity across partially implemented standards and various extensions. See [include/foundation/compat.h](include/foundation/compat.h).
  * Stateful memory allocation and tracking. See [include/foundation/allocator.h](include/foundation/allocator.h).
  * Type-safe algorithms (and wrappers around stdlib implementations). See [include/foundation/algorithm.h](include/foundation/algorithm.h).
  * Detailed assertions. See [include/foundation/assert.h](include/foundation/assert.h), and [include/foundation/crash_handler.h](include/foundation/crash_handler.h).
  * Various hashes and checksum functions. See [include/foundation/digest.h](include/foundation/digest.h).
  * Debugging and symbol look-up information. See [include/foundation/debug_info.h](include/foundation/debug_info.h).
  * Detailed crash handling and reportin. See [include/foundation/crash_handler.h](include/foundation/crash_handler.h).
  * Cross-platform wrappers around threading. See [include/foundation/thread.h](include/foundation/thread.h), [include/foundation/mutex.h](include/foundation/mutex.h), [include/foundation/condition_variable.h](include/foundation/condition_variable.h), and [include/foundation/atomics.h](include/foundation/atomics.h).
  * Arrays, Dictionaries, Instrusive Lists, Ring Buffers, Queues, etc. See [include/foundation/array.h](include/foundation/array.h), [include/foundation/dictionary.h](include/foundation/dictionary.h), [include/foundation/string.h](include/foundation/string.h).

Contributing
---

Fork and submit a pull request. Just make sure your pull requests:

  * Are scoped to one specific issue.
  * Update any relevant documentation or build scripts.
  * Don't break the build.
  * Match (roughly) the coding style.

Building
---

Make sure you have the following:

  * A brain;
  * A C++ compiler (gcc, clang, msvc);
  * Ruby;
  * and [Tup](https://github.com/gittup/tup).

Then shell-fu:

```
$ ruby configure {debug,release}
$ build.bat (Windows) or ./build.sh (POSIX)
$ tup init
$ tup upd
```

**Note:** if you're using Windows you'll need to make sure you set `VCINSTALLDIR` to something like `C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC`.

License
---

Public domain, or MIT.
