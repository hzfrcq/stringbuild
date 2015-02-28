# stringbuild
A C++11 string utility for constructing strings using streams.

All in one small header-file released under a BSD license (see <tt>LICENSE</tt>).


## Demo snippets

Integer to string conversion (see <tt>simple_example.cpp</tt>):

```c++
std::string score_text = "Score = ";
append_string(score_text) << player_score();
```

Logger wrapping of a C-styled <tt>log(... , char \* str)</tt> backend (see <tt>logging_example.cpp</tt>):

```c++
if ( var > LIMIT ) {
  LOG_ERROR << "var = " << var << ", exceeded " << LIMIT;
}
```
With an example output of:

    Sat Feb 28 18:47:25 2015 [ logging_example.cpp:93 ] ERROR var = 103, exceeded 100


## How it works

A <tt>stringbuilder</tt> class allows the user to create temporary objects that
can be treated just like any other <tt>ostringstream</tt>.
With one major difference, when they are destroyed they will convert the
stream to a string and call a user-defined callback.

The temporary object is created with the <tt>stringbuilder</tt> constructor which
takes one parameter; a callback with the signature: <tt>void f(const std::string &)</tt>.

Two functions with predefined callbacks are already provided:
 * <tt>append_string(std::string &)</tt>, and
 * <tt>assign_string(std::string &)</tt>


## C++ Compatibility

The library uses C++11 move semantics and is much more usable together with
lambda expressions.

The code has only been tested with a limited set of compilers and versions.

 * GCC/Clang: need to set the <tt>-std=</tt> flag to <tt>gnu++11</tt>, 
   <tt>c++0x</tt> or <tt>c++11</tt>.
