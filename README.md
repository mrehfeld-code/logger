# logger
A simple, header-only C++ logger.

# Usage
## Using the macros
There are eight different macros defined in `logger.hpp`:
```cpp
LOG_INFO(format);
LOG_INFO_EXT(format, ...);

LOG_SUCCESS(format);
LOG_SUCCESS_EXT(format, ...);

LOG_WARN(format);
LOG_WARN_EXT(format, ...);

LOG_ERROR(format);
LOG_ERROR_EXT(format, ...);
```
They basically do all work the same way:
`LOG_"LOGTYPE"` or `LOG_"LOGTYPE"_EXT`, the `_EXT` stands for extendet and allows you to pass variable length arguments to the log function, 
so you can use it as a simple `printf`-function. 


## Using the `LOGGER::_log` function
This function requieres the following arguments:
* `LOGTYPE`: an enum defined in the namespace `LOGGER` wich is setting ... well it's setting the log type
* `file`: this argument is the file from which the function is called (the macros use `__FILE__` to set it)
* `line`: nearly the same as `file` but the line (the macros are using `__LINE__`)
* `format`: is the format string for the variable length arguments
* `...`: the va_list (doesn't need to be set)

## Useful information
### variable length argument specifier
specifier scien is `%` like printf
| specifier | what it does |
|-----------|--------------|
| `a` or `A` | a boolean setting if the function should execute `exit()` after printing (when `LOGTYPE=ERROR` set to `true` by default, otherwise `false`) |
| `e` or `E` | an integer setting the return value of `LOGGER::_log` and if activated exit code used by `exit()` (when `LOGTYPE=ERROR` set to -1 by default, otherwise 0) |
| `s` | print a string (char*) |
| `c` | print a single char |
| `d` | print an integer |
| `f` | print a float |
| `%` | print the charecter `%` |
| `b` | print the value of a boolean `TRUE` or `FALSE` |

### NOTE
The logger has a color support on Linux and MacOS, thought that feature is deactivated on Windows due to the fact that the escape sequence color support is limited to Powershell and Windows Terminal the original Windows Console doesn't support them. Maybe I will implement the color support on Windows with `Windows.h` in a future version.
