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

#include <ctime>
#include <stdio.h>
#include <cstring>
#include <stringbuild>
using namespace std;
using namespace stringbuild;


/** log()
 * Example backend logging function.
 * This one writes to stderr and takes the logging
 * message as a C string.
 */
void log( char const * const file,
          int                line,
          char const * const severity,
          char const * const msg) {
    time_t t = time(0);
    char * t_str = asctime(localtime(&t));
    t_str[strlen(t_str) - 1] = 0;
    fprintf(stderr, "%s [%20s:%-3d] %s %s\n",
                    t_str,
                    file,
                    line,
                    severity,
                    msg);
}


/** log_builder()
 * Returns a stringbuilder that enables piping to costruct the msg argument
 * of the log() function which is called when the stringbuilder object
 * is destroyed.
 */
static stringbuilder
log_builder(char const * const type, int line, char const * const file) {
    return stringbuilder(
        [type,line,file](const string & str){
            log(file,line,type,str.c_str());
        }
    );
}
#define LOG_ERROR log_builder("ERROR"  ,__LINE__,__FILE__)
#define LOG_WRN   log_builder("WARNING",__LINE__,__FILE__)
#define LOG_DBG   log_builder("DEBUG"  ,__LINE__,__FILE__)



/** @struct MyData
 * Stupid example struct that can be piped directly to the logger.
 */
struct MyData : public StreamableObject {
    int x, y;
    MyData(int init_x, int init_y) : x(init_x), y(init_y) {}
    /* for debugging purposes */
    void toStream(ostream & out) const {
        out << "myDataT(x=" << x << ", y=" << y << ")";
    };
};

/* logger example */
int main() {
    MyData d(5,10);

    LOG_ERROR << "something went horribly wrong";

    LOG_DBG << "d=" << d;

    return 0;
}

