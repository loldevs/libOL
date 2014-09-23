// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__ParseException__
#define __libol__ParseException__

#include <stdexcept>
#include <string>

/* REQUIRE(expression)
 * Require an expression to be true to continue
 * - guarantees execution of the expression
 * - guaranteed to throw a ParseException if the expression is false
 */
#define REQUIRE(expr) ParseExceptionUtil::require(expr, #expr, __FILE__, __LINE__)

/* EXPECT(expression)
 * Expect an expression to be true but execution can continue if not
 * - guarantees execution of the expression
 * - might throw a ParseException if the expression is false, depending on configuration
 */
#define EXPECT(expr) ParseExceptionUtil::expect(expr, #expr, __FILE__, __LINE__)

namespace libol {
    class ParseException : public std::runtime_error {
    public:
        ParseException(std::string cause) : std::runtime_error(cause) {};
    };

    namespace ParseExceptionUtil {
        void require(bool result, const char* expr, const char* file, int line);
        void expect(bool result, const char* expr, const char* file, int line);
    }
}

#endif /* defined(__libol__ParseException__) */
