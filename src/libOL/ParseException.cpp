#include "ParseException.h"

#include <sstream>
#include <iostream>

namespace libol {
    namespace ParseExceptionUtil {
        void require(bool result, const char *expr, const char *file, int line) {
            if(result) return;
            std::stringstream msg;
            msg << "Requirement not met: " << expr << " in " << file << ":" << line;
            throw ParseException(msg.str());
        }

        void expect(bool result, const char *expr, const char *file, int line) {
            if(result) return;
            std::stringstream msg;
            msg << "Expectation not met: " << expr << " in " << file << ":" << line;
            std::cout << msg.str() << std::endl;
        }
    }
}
