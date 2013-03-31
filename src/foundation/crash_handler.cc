// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/crash_handler.h>
#include <foundation/debug_info.h>

#include <stdlib.h>

namespace foundation {
  namespace {
    void _on_signal( int sig ) {
      switch (sig) {
        case SIGTERM: FOUNDATION_LOG("\nRecieved a termination request!\n\n"); break;
        case SIGSEGV: FOUNDATION_LOG("\nEncountered a segmentation fault!\n\n"); break;
        case SIGINT: FOUNDATION_LOG("\nRecieved an external interrupt!\n\n"); break;
        case SIGILL: FOUNDATION_LOG("\nEncountered an invalid instruction!\n\n"); break;
        case SIGABRT: FOUNDATION_LOG("\nAbnormal program termination!\n\n"); break;
        case SIGFPE: FOUNDATION_LOG("\nEncountered a floating-point exception!\n\n"); break;
      }

      Callstack cs;

      if (!callstack(cs)) {
        FOUNDATION_LOG("  Unable to generate callstack!\n");
        exit(EXIT_FAILURE);
      }

      for (size_t f = 0; f < cs.frames.size(); ++f) {
        Callstack::Frame& frame = cs.frames[f];

        FOUNDATION_LOG(
          "  %s\n    in `%s` on line %u\n\n",
          &frame.name[0],
          &frame.file[0],
          frame.line
        );
      }

      _exit(EXIT_FAILURE);
    }
  }
} // foundation

#include <signal.h>

namespace foundation {
  bool install_crash_handler()
  {
    signal(SIGTERM, &_on_signal);
    signal(SIGSEGV, &_on_signal);
    signal(SIGINT, &_on_signal);
    signal(SIGILL, &_on_signal);
    signal(SIGABRT, &_on_signal);
    signal(SIGFPE, &_on_signal);
    return true;
  }

  bool uninstall_crash_handler()
  {
    signal(SIGTERM, SIG_DFL);
    signal(SIGSEGV, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    signal(SIGILL, SIG_DFL);
    signal(SIGABRT, SIG_DFL);
    signal(SIGFPE, SIG_DFL);
    return true;
  }
} // foundation