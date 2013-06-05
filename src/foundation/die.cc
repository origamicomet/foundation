// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/die.h>

#include <foundation/debug.h>

namespace foundation {
  void die(
    bool no_exception_handler )
  {
    if (no_exception_handler)
      set_exception_handler(nullptr);

    log("Abnormally terminating!");

    ExecutionState execution_state;
    get_execution_state(execution_state);

    Callstack cs;
    if (callstack(cs, execution_state)) {
      log("Callstack:");
      log("");

      for (auto iter = cs.frames.begin(); iter != cs.frames.end(); ++iter) {
        const Symbol& sym = (*iter).symbol;
        log("  %s", sym.name().raw());
        if (!sym.location().path().empty() && (sym.location().line() != Symbol::Location::line_information_unavailable))
          log("    in `%s` on line %u", sym.location().path().raw(), sym.location().line());
        log("");
      }
    }

    _Exit(EXIT_FAILURE);
  }
} // foundation

