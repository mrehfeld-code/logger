#ifdef __cplusplus
#ifndef LOGGER_HPP
#define LOGGER_HPP

#ifndef _IOSTREAM_
#include <iostream>
#endif // _IOSTREAM_

#ifndef _CSTDARG_
#include <cstdarg>
#endif // _CSTDARG_


#if defined(__linux__) || defined(__APPLE_CC__)
#define USE_COLOR true
#else 
#define USE_COLOR false
#endif 


namespace LOGGER {
	enum LOGTYPE {
		INFO = 0xA,
		SUCCESS = 0xB,
		WARNING = 0xC,
		ERROR = 0xD
	};

	std::string getColor(LOGTYPE lt) {
	#if USE_COLOR == true
		switch (lt) {
		case INFO:
			return "\033[1;36m";
		case SUCCESS:
			return "\033[1;32m";
		case WARNING:
			return "\033[1;33m";
		case ERROR:
			return "\033[1;31m";
		default:
			return "\033[0m";
		}
	
	#else 
		return "";
	#endif
	}

	std::string logtypeToString(LOGTYPE lt) {
		switch (lt) {
		case INFO:
			return "[INFO]";
		case SUCCESS:
			return "[SUCCESS]";
		case WARNING:
			return "[WARNING]";
		case ERROR:
			return "[ERROR]";
		default:
			return "";
		}
	}

	int _log(LOGTYPE lt, const char* file, const long line, const char* format, ...) {
		std::cout << file << ":" << line << ": " << getColor(lt) << logtypeToString(lt) << " ";

		int exitCode = 0;
		bool exitAfter = false;
		if (lt == ERROR) {
			exitCode = -1;
			exitAfter = true;
		}

		va_list args;
		va_start(args, format);

		long chrPos = 0;
		while (format[chrPos] != EOF && format[chrPos] != 0) {
			if (format[chrPos] == '%') {
				chrPos++;
				switch (format[chrPos]) {
				case 'a':
				case 'A':
					exitAfter = va_arg(args, bool);
					break;

				case 'E':
				case 'e':
					exitCode = va_arg(args, int);
					break;

				case 's':
					printf("%s", va_arg(args, char*));
					break;

				case 'c':
					printf("%c", va_arg(args, char));
					break;

				case 'd':
					printf("%d", va_arg(args, int));
					break;

				case 'f':
					printf("%f", va_arg(args, double));
					break;

				case '%':
					printf("%%");
					break;

				case 'b':
					if (va_arg(args, bool))
						printf("TRUE");
					else
						printf("FALSE");
					break;
				}
			} else
				printf("%c", format[chrPos]);

			chrPos++;
		}

		std::cout << std::endl;
		va_end(args);

		if (exitAfter)
			exit(exitCode);

		return exitCode;
	}
}


#define LOG_INFO(format)				LOGGER::_log(LOGGER::INFO, __FILE__, __LINE__, #format)
#define LOG_INFO_EXT(format, ...)		LOGGER::_log(LOGGER::INFO, __FILE__, __LINE__, #format, __VA_ARGS__)

#define LOG_SUCCESS(format)				LOGGER::_log(LOGGER::SUCCESS, __FILE__, __LINE__, #format)
#define LOG_SUCCESS_EXT(format, ...)	LOGGER::_log(LOGGER::SUCCESS, __FILE__, __LINE__, #format, __VA_ARGS__)

#define LOG_WARN(format)				LOGGER::_log(LOGGER::WARNING, __FILE__, __LINE__, #format)
#define LOG_WARN_EXT(format, ...)		LOGGER::_log(LOGGER::WARNING, __FILE__, __LINE__, #format, __VA_ARGS__)

#define LOG_ERROR(format)				LOGGER::_log(LOGGER::ERROR, __FILE__, __LINE__, #format)
#define LOG_ERROR_EXT(format, ...)		LOGGER::_log(LOGGER::ERROR, __FILE__, __LINE__, #format, __VA_ARGS__)


#endif // LOGGER_HPP
#endif // __cplusplus
