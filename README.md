# Foundation

Foundation is a highly configurable and minimalistic library that provides:

  * [Compiler, architecture, platform, and supported standards detection;](include/foundation/detect.h)
  * [Compiler uniformity across partially implemented standards and varying extensions;](include/foundation/compat.h)
  * [Stateful memory allocation and tracking, with various allocation strategies implemented;](include/foundation/allocator.h)
  * [Fast implementations of common containers (and thread safe variants);](include/foundation/containers.h)
  * [Robust exception and crash handling with detailed error reporting;](include/foundation/debug)
  * [Along with detailed assertions;](include/foundation/assert.h)
  * [Low-overhead cross-platform wrappers around concurrency primitives;](include/foundation/system/concurrency.h)
  * [Cross-platform debugging and symbol information wrappers;](include/foundation/debug)
  * [Cross-platform low and high level networking;](include/foundation/system/network.h)
  * [and more.](docs/)

Contributing
---

Fork and submit a pull request. Just make sure your pull requests:

  * Are scoped to one specific issue;
  * Update any relevant documentation or build scripts;
  * Don't break the build;
  * and roughly match the coding style.

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

Linking Against
---

Use `include deps.tup` if linking with Tup, otherwise link against what deps.tup does (for the appropriate platform, of course).

License
---

Public domain, or MIT.
See [LICENSE.md](LICENSE.md) for more details.
