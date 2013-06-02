// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/debug/crash_handler.h>

#include <foundation/logger.h>
#include <foundation/debug/callstack.h>

namespace foundation {
  static const char* exception_to_string( Exception exception ) {
    switch (exception) {
      case EXCEPTION_TERMINATION_REQUESTED:
        return "graceful termination requested";
      case EXCEPTION_ACCESS_VIOLATION:
        return "access violation";
      case EXCEPTION_EXTERNAL_INTERRUPT:
        return "external interrupt";
      case EXCEPTION_INVALID_INSTRUCTION:
        return "invalid or privledged instruction";
      case EXCEPTION_ABNORMAL_PROGRAM_TERMINATION:
        return "abnormal termination";
      case EXCEPTION_ERRONEOUS_ARITHMETIC_OPERATION:
        return "erroneous arithmetic operation";
      case EXCEPTION_MEMORY_ALLOCATION_FAILED:
        return "memory exhaustion";
      case EXCEPTION_PURE_VIRTUAL_FUNCTION_CALLED:
        return "pure virtual function called";
      case EXCEPTION_MISALIGNED_READ_OR_WRITE:
        return "misaligned read or write";
      case EXCEPTION_STACK_OVERFLOW:
        return "stack overflow"; }
    return "unknown";
  }

  void crash_handler(
    Exception exception,
    ExecutionState& execution_state )
  {
    static size_t recursion = 0;

    if (++recursion > 1)
      _Exit(EXIT_FAILURE);

    log("Encountered exception: %s!", exception_to_string(exception));

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
