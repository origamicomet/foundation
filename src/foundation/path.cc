// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/path.h>
#include <foundation/memory.h>
#include <foundation/string.h>
#include <foundation/native_string.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  namespace Path {
    // TODO: Handle UTF-8 code points, perhaps use classes like String8,
    //       String16, String32 and remove NativeString. Also, add code-point
    //       based iterators? String::begin() / String::end().
    //       The same goes for other string functions.

    String basename(
      const String& path )
    {
      if (path.empty())
        return String(path.allocator());

      const char* min = path.to_ptr();
      const char* max = path.to_ptr() + path.length_in_bytes();

      // Strip the file extension.
      /* max = */ {
        const char* iter = max;
        while (*(--iter) != '.' && (iter != path.to_ptr()));
        if (iter != path.to_ptr())
          max = iter;
      }

      // Strip the leading directories.
      /* min = */ {
        char ch;
        const char* iter = max;
        while ((ch = (*(--iter))) && (iter != path.to_ptr()))
          if ((ch == '\\') || (ch == '/'))
            break;
        if (iter != path.to_ptr())
          min = iter;
      }

      const size_t len = (size_t)(max - min);
      String basename = String(path.allocator(), len + 1);
      copy((void*)basename.to_ptr(), (const void*)min, len);
      basename[len] = '\0';
      return basename;
    }

    String dirname(
      const String& path )
    {
      if (path.empty())
        return String(path.allocator());

      const char* min = path.to_ptr();
      const char* max = path.to_ptr() + path.length_in_bytes();

      // Strip the file name and file extension.
      /* max = */ {
        char ch;
        const char* iter = max;
        while ((ch = (*(--iter))), (iter != path.to_ptr()))
          if ((ch == '\\') || (ch == '/'))
            break;
        if (iter != path.to_ptr())
          max = iter;
      }

      const size_t len = (size_t)(max - min);
      String dirname = String(path.allocator(), len + 1);
      copy((void*)dirname.to_ptr(), (const void*)min, len);
      dirname[len] = '\0';
      return dirname;
    }

    String extension(
      const String& path )
    {
      if (path.empty())
        return String(path.allocator());

      const char* iter =
        path.to_ptr() + path.length_in_bytes();

      while (*(--iter) != '.' && (iter != path.to_ptr()));

      if (iter == path.to_ptr())
        return String();

      return String(path.allocator(), iter + 1);
    }

    String absolute(
      const String& path )
    {
      if (path.empty())
        return String(path.allocator());

    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      const NativeString native_path(path);

      const size_t abs_path_len =
        GetFullPathNameW(native_path.to_ptr(), 0, NULL, NULL);

      NativeString native_abs_path(path.allocator(), abs_path_len);
        GetFullPathNameW(native_path.to_ptr(), abs_path_len,
                         native_abs_path.to_ptr(), NULL);

      return unixify(String(native_abs_path));
    #elif defined(FOUNDATION_PLATFORM_POSIX)
      return String(path.allocator());
    #endif
    }

    String relative_to(
      const String& path,
      const String& relative_to )
    {
      // TODO: Fix breakage on different drive letters.

      if (path.empty() || relative_to.empty())
        return String(path.allocator());

      const String abs_path = absolute(path);
      const String abs_relative_to = absolute(relative_to);

      // Determine where the paths diverge:
      const char* iter_p = abs_path.to_ptr();
      const char* iter_r = abs_relative_to.to_ptr();
      while (*(iter_p++) == *(iter_r++));

      // We could end-up in the middle of a folder name, so roll back:
      while (*(--iter_p) != '/');
      while (*(--iter_r) != '/');

      // "Undo" each consecutive level from |relative_to|:
      String rel_path = String(path.allocator()); {
        char ch;
        while (ch = *(iter_r++))
          if (ch == '/') rel_path += "../";
      }

      // Add remaining path (because rel_path points to iter_p now):
      rel_path += (iter_p + 1);

      return rel_path;
    }

    String unixify(
      const String& path )
    {
      if (path.empty())
        return String(path.allocator());

      // Replace occurances of `\` with `/`. 
      String unixified = String(path.allocator(), path.length_in_bytes());
      for (size_t i = 0; i < path.length_in_bytes(); ++i) {
        if (path[i] == '\\') unixified[i] = '/';
        else unixified[i] = path[i];
      }

      // Replace drive letters like `C:/` with `/C/`.
      if (unixified.length_in_bytes() >= 2) {
        if (!((unixified[0] >= 'A') && (unixified[0] <= 'Z')) &&
            !((unixified[0] >= 'a') && (unixified[0] <= 'z')) )
          return unixified;

        if (unixified[1] != ':')
          return unixified;

        unixified[1] = unixified[0];
        unixified[0] = '/';
      }

      return unixified;
    }
  } // Path
} // foundation