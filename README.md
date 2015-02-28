# stringbuild
A C++11 string utility for constructing strings using streams.

All in one small header-file released under a BSD license (see LICENSE).


## Demo snippets

Integer to string conversion (see simple_example.cpp):

    std::string score_text = "Score = ";
    append_string(score_text) << player_score;
    draw_text(context, x, y, score_text);

Logger wrapping (see logging_example.cpp):

    if( ptr == nullptr ) {
      LOG_ERROR << "Got an invalid pointer";
      exit(1);
    }


## How it works

A stringbuilder class allows the user to create temporary objects that
can be treated just like any other ostringstream.
With one major difference, when they are destroyed the will convert the
stream to a string and call a user-defined callback.

The temporary object is created with the stringbuilder constructor which
takes one parameter; a callback with the signature: void f(const std::string &)

Two functions with predefined callbacks are already provided:
 * append_string(std::string &), and
 * assign_string(std::string &)


## C++ Compatibility

The library uses C++11 move semantics and is much more usable together with
lambda expressions.

The code has only been tested with a limited set of compilers and versions.

 * GCC/Clang: need to set the -std= flag to gnu++11, c++0x or c++11
