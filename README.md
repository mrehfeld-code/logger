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
`LOG_"LOGTYPE"` or `LOG_"LOGTYPE"_EXT`, the `_EXT` stands for extendet and allows you to pass variable length arguments to log function, 
so you can use it as a simple `printf`-function. 


## Using the `LOGGER::_log` function

