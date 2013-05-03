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
        return "abnormally terminating";
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
    log("Encountered exception: %s!\n", exception_to_string(exception));

    Callstack cs;
    if (callstack(cs, execution_state)) {
      log("\nCallstack:\n\n");

      for (auto iter = cs.frames.begin(); iter != cs.frames.end(); ++iter) {
        const Symbol& sym = (*iter).symbol;
        if (sym.location().path().empty() || (sym.location().line() != Symbol::Location::line_information_unavailable))
          log("  %s\n\n", sym.name().raw());
        else
          log("  %s\n    in `%s` on line %u\n\n", sym.name(), sym.location().path(), sym.location().line());
      }
    }

    _Exit(EXIT_FAILURE);
  }
} // foundation
