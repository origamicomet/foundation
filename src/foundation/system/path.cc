// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/system/path.h>

#if defined(FOUNDATION_PLATFORM_WINDOWS)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif defined(FOUNDATION_PLATFORM_POSIX)
#endif

namespace foundation {
  namespace Path {
    char seperator()
    {
    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      return '\\';
    #elif defined(FOUNDATION_PLATFORM_POSIX)
      return '/';
    #endif
    }

    String basename(
      const String& path )
    {
      if (path.empty())
        return String(path.allocator());

      String::Iterator min = path.begin();
      String::Iterator max = path.end();

      // Strip the file extension:
      /* max = */ {
        String::Iterator iter = max;
        while(iter != min) {
          switch ((iter--).to_code_point()) {
            case '/':
            case '\\':
              break;
            case '.': {
              max = iter;
              iter = min;
            } break;
          }
        }
      }

      // Strip the leading directories:
      /* min = */ {
        String::Iterator iter = max;
        while (iter != min) {
          switch ((iter--).to_code_point()) {
            case '/':
            case '\\':
              min = ++iter;
              break;
          }
        }
      }

      if (min == max)
        return String(path.allocator());
      return String(path.allocator(), ++min, max);
    }

    String dirname(
      const String& path )
    {
      if (path.empty())
        return String(path.allocator());

      String::Iterator min = path.begin();
      String::Iterator max = path.end();

      // Strip the file name and file extension.
      /* max = */ {
        String::Iterator iter = max;
        while (iter != min) {
          switch ((iter--).to_code_point()) {
            case '/':
            case '\\':
              max = iter;
              iter = min;
              break;
          }
        }
      }

      return String(path.allocator(), min, max);
    }

    String extension(
      const String& path )
    {
      if (path.empty())
        return String(path.allocator());

      String::Iterator iter = path.end();
      uint32_t code_point = 0;

      do {
        code_point = iter.to_code_point();
        if ((code_point == '/') || (code_point == '\\'))
          return String(path.allocator());
        if (code_point == '.')
          break;
      } while ((iter--) != path.begin());

      return String(path.allocator(), (++iter), path.end());
    }

    String sans_extension(
      const String& path,
      const bool greedy )
    {
      if (path.empty())
        return String(path.allocator());

      String::Iterator iter = path.end();
      String::Iterator max = path.end();
      uint32_t code_point = 0;

      do {
        code_point = iter.to_code_point();
        if ((code_point == '/') || (code_point == '\\')) {
          if (greedy) break;
          else return String(path.allocator()); }
        if (code_point == '.') {
          if (greedy) max = iter--;
          else break; }
      } while((iter--) != path.begin());

      return String(path.allocator(), path.begin(), greedy ? max : iter);
    }

    String expand(
      const String& path )
    {
      if (path.empty())
        return String(path.allocator());

    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      wchar_t* native_path; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, path.raw(), path.size(), nullptr, 0);
        native_path = (wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path.raw(), path.size(), native_path, len);
      }

      String expanded_path(path.allocator()); {
        size_t expanded_path_len_ = 0;
        wchar_t* expanded_path_; {
          expanded_path_len_ = ExpandEnvironmentStringsW(native_path, NULL, 0);
          expanded_path_ = (wchar_t*)alloca(expanded_path_len_ * sizeof(wchar_t));
          ExpandEnvironmentStringsW(native_path, expanded_path_, expanded_path_len_);
        }

        const size_t len = WideCharToMultiByte(
          CP_UTF8, 0, expanded_path_, expanded_path_len_, nullptr, 0, 0, 0);
        expanded_path = String(Allocators::heap(), len);
        WideCharToMultiByte(
          CP_UTF8, 0, expanded_path_, expanded_path_len_,
          (char*)expanded_path.raw(), len, 0, 0);
      }

      return expanded_path;
    #elif defined(FOUNDATION_PLATFORM_POSIX)
    #endif
    }

    String absolute(
      const String& path )
    {
      if (path.empty())
        return String(path.allocator());

    #if defined(FOUNDATION_PLATFORM_WINDOWS)
      wchar_t* native_path; {
        const size_t len = MultiByteToWideChar(
          CP_UTF8, 0, path.raw(), path.size(), nullptr, 0);
        native_path = (wchar_t*)alloca(len * sizeof(wchar_t));
        MultiByteToWideChar(
          CP_UTF8, 0, path.raw(), path.size(), native_path, len);
      }

      String abs_path(path.allocator()); {
        size_t abs_path_len_ = 0;
        wchar_t* abs_path_; {
          abs_path_len_ = GetFullPathNameW(native_path, 0, NULL, NULL);
          abs_path_ = (wchar_t*)alloca(abs_path_len_ * sizeof(wchar_t));
          GetFullPathNameW(native_path, abs_path_len_, abs_path_, NULL);
        }

        const size_t len = WideCharToMultiByte(
          CP_UTF8, 0, abs_path_, abs_path_len_, nullptr, 0, 0, 0);
        abs_path = String(Allocators::heap(), len);
        WideCharToMultiByte(
          CP_UTF8, 0, abs_path_, abs_path_len_,
          (char*)abs_path.raw(), len, 0, 0);
      }

      return abs_path;
    #elif defined(FOUNDATION_PLATFORM_POSIX)
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
      String::Iterator iter_p = abs_path.begin();
      String::Iterator iter_r = abs_relative_to.begin();
      while ((iter_p++).to_code_point() == (iter_r++).to_code_point());

      // We could end-up in the middle of a folder name, so roll back:
      while ((--iter_p).to_code_point() != '/');
      while ((--iter_r).to_code_point() != '/');

      // "Undo" each consecutive level from |relative_to|:
      String rel_path = String(path.allocator()); {
        uint32_t code_point = 0;
        while ((code_point = (iter_r++).to_code_point()))
          if (code_point == '/')
            rel_path += "../";
      }

      // Add remaining path (because rel_path points to iter_p now):
      rel_path += String(path.allocator(), (iter_p++), abs_path.end());
      return rel_path;
    }

    String unixify(
      const String& path )
    {
      if (path.empty())
        return String(path.allocator());

      // Replace occurances of `\` with `/`:
      String unixified = path;
      for (String::Iterator iter = unixified.begin();
           iter != unixified.end(); ++iter)
      {
        if (iter.to_code_point() == '\\')
          *iter = '/';
      }

      // Replace drive letters like `C:/` with `/C/`.
      String::Iterator drive_letter = unixified.begin();

      const uint32_t drive_letter_ = drive_letter.to_code_point();
      if (!((drive_letter_ >= 'A') && (drive_letter_ <= 'Z')) &&
          !((drive_letter_ >= 'a') && (drive_letter_ <= 'z')))
        return unixified;

      String::Iterator colon = (++(unixified.begin()));
      const uint32_t colon_ = colon.to_code_point();
      if (colon_ != ':')
        return unixified;

      *colon = (drive_letter_ & 0x7F);
      *drive_letter = '/';

      return unixified;
    }
  } // Path
} // foundation
