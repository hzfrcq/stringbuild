/*

Copyright (c) 2015, Mikael Krekola
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef __STRINGBUILD__H__
#define __STRINGBUILD__H__
#if __cplusplus <= 199711L
#error You need a fairly C++11 compliant compiler (mode), if you are running GCC, try using -std=c++11, gnu++11 or c++0x
#else

#include <string>
#include <sstream>
#include <functional>

namespace stringbuild {

class StreamableObject {
public:
    virtual ~StreamableObject(){};
    virtual void toStream(std::ostream & out) const = 0;
};

inline std::ostream & operator<<(std::ostream & out, const StreamableObject & obj) {
    obj.toStream(out);
    return out;
};

/** A class for temporary objects that can be streamed to just like
 *  any other std::ostringstream but when it is destroyed it will
 *  compile a string and call a user-defined callback.
 */
class stringbuilder : public std::ostringstream {
    typedef std::function<void(const std::string &)> _fn_t;
    _fn_t _fn;
    bool _do_fn;
protected:
    inline void set_fn(_fn_t fn) { _fn = fn; }
    inline void cancel_fn() { _do_fn = false; }
public:
    inline stringbuilder(_fn_t fn) : _fn(fn), _do_fn(true) {}
    inline stringbuilder(const stringbuilder & s) : _fn(s._fn), _do_fn(true) {}
    inline virtual ~stringbuilder() {
        if(_do_fn) {
            _fn( str() ); // calls backend
            cancel_fn();
        }
    }
};

/** Appends whatever you strem to the returned object to the referenced
 *  string.
 *
 * Code snippet:
 * @code{.cpp}
 *   std::string s = "My name is ";
 *   stringbuild::append_string(s) << "Mikael";
 *   // s contains "My name is Mikael"
 * @endcode
 *
 * @note dest is appended when the temporary object of append_string()
 *       is out of scope (i.e. destroyed).
 */
static inline stringbuilder
append_string(std::string & dest) {
    return stringbuilder(
        [&dest](const std::string & from){ dest.append(from); }
    );
}

/** Assign whatever you strem to the returned object to the referenced
 *  string.
 *
 * Code snippet:
 * @code{.cpp}
 *   std::string s = "My name is ";
 *   stringbuild::assign_string(s) << "Mikael";
 *   // s contains "Mikael"
 * @endcode
 *
 * @note dest is assigned when the temporary object of append_string()
 *       is out of scope (i.e. destroyed).
 */
static inline stringbuilder
assign_string(std::string & dest) {
    return stringbuilder(
        [&dest](const std::string & from){ dest.assign(from); }
    );
}

} /* ns stringbuild */

#endif /* __cplusplus */
#endif /* __STRINGBUILD__H__ */

