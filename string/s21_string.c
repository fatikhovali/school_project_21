#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#if defined(__APPLE__)
#define MAX_LIST 107
#define MIN_LIST -1
#define ERROR "Unknown error: "

static const char *errorList[] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full"};

#elif defined(__linux__)
#define MAX_LIST 134
#define MIN_LIST -1
#define ERROR "Unknown error "

static const char *errorList[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};

#endif

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  if (str) {
    for (s21_size_t i = 0; str[i]; i++) {
      len = len + 1;
    }
  }
  return len;
}
/*strspn - Вычисляет длину начального сегмента str1,
kоторый полностью состоит из символов str2*/
s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  s21_size_t proverka = 0;
  if (str1 && str2) {
    for (s21_size_t i = 0; str1[i]; i++) {
      proverka = count;
      for (s21_size_t j = 0; str2[j]; j++) {
        if (str1[i] == str2[j]) {
          count++;
          break;
        }
      }
      if (proverka == count) break;
    }
  }
  return count;
}
/*s21_strcspn - Вычисляет длину начального сегмента str1,
который полностью состоит из символов, не входящих в str2*/
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  s21_size_t proverka = 0;
  if (str1 && str2) {
    for (s21_size_t i = 0; str1[i]; i++) {
      for (s21_size_t j = 0; str2[j]; j++) {
        if (str1[i] == str2[j]) {
          proverka++;
          break;
        }
      }
      if (proverka) {
        break;
      } else {
        count++;
      }
    }
  }
  return count;
}
// memcmp - cравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  s21_size_t i = 0;
  if (str1 && str2 && n) {
    while (i < n) {
      if (*(unsigned char *)(str1 + i) != *(unsigned char *)(str2 + i)) {
        result = *(unsigned char *)(str1 + i) - *(unsigned char *)(str2 + i);
        break;
      }
      i++;
    }
  }
  return result;
}
// strncmp - cравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  if (str1 && str2 && n > 0) {
    for (s21_size_t i = 0; i < n; i++) {
      if (str1[i] == '\0' || str1[i] != str2[i]) {
        result = str1[i] - str2[i];
        break;
      }
    }
  }
  return result;
}
// strcmp - cравнивает строку str1 со строкой str2.
int s21_strcmp(const char *str1, const char *str2) {
  int result = 0;
  if (str1 && str2) {
    int i = 0;
    while (str1[i] != '\0' && str1[i] == str2[i]) {
      i++;
    }
    result = str1[i] - str2[i];
  }
  return result;
}
// strtok - pазбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim) {
  static char *change = s21_NULL;
  int ch = 0;
  if (str == s21_NULL) {
    str = change;
  }
  if (str) {
    do {
      if ((ch = *str++) == '\0') {
        return 0;
      }
    } while (s21_strchr(delim, ch));
    --str;
    change = str + s21_strcspn(str, delim);
    if (*change != 0) {
      *change++ = 0;
    }
  }
  return str;
}
// strcat - Добавляет строку src, в конец строки dest
char *s21_strcat(char *dest, const char *src) {
  int i = 0;
  if (src && dest) {
    s21_size_t len_dest = s21_strlen(dest);
    while (src[i] != '\0') {
      dest[len_dest + i] = src[i];
      i++;
    }
    dest[len_dest + i] = '\0';
  }
  return dest;
}
// strncat - Добавляет строку src, в конец строки dest, длиной до n символов.
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (dest && src && n) {
    s21_size_t len_dest = s21_strlen(dest), i = 0;
    while (i < n && src[i]) {
      dest[len_dest + i] = src[i];
      i++;
    }
    dest[len_dest + i] = '\0';
  } 
  return dest;
}
// strerror - поиск во внутреннем массиве номера ошибки errnum
char *s21_strerror(int errnum) {
  static char result[512] = {'\0'};
  if (errnum <= MIN_LIST || errnum >= MAX_LIST) {
    sprintf(result, "Unknown error: %d", errnum);
  } else {
    s21_strcpy(result, ((char *)errorList[errnum]));
  }

  return result;
}
// memcpy – копирование непересекающихся массивов
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  s21_size_t i;
  char *copy_dest = (char *)dest;
  const char *copy_src = (char *)src;
  for (i = 0; i < n; ++i) {
    *copy_dest++ = *copy_src++;
  }
  return dest;
}

// strcpy – копирование строк
char *s21_strcpy(char *dest, const char *src) {
  s21_size_t i;
  for (i = 0; src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}

// memset – заполнения массива указанными символами.
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *copy_str = str;
  unsigned char copy_c = c;
  while (n != 0) {
    *copy_str++ = copy_c;
    n = n - 1;
  }
  return str;
}

// strncpy – копирование строк c ограничением длины
//
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *copy_dest = dest;
  size_t i = 0;
  while (i < n && *src != '\0') {
    *copy_dest = *src;
    src = src + 1;
    copy_dest = copy_dest + 1;
    i++;
  }
  while (i < n) {
    *copy_dest = '\0';
    copy_dest = copy_dest + 1;
    i++;
  }
  return dest;
}

// strstr – поиск первого вхождения строки А в строку В
char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t i;
  char *result = s21_NULL;
  int u;
  // n = s21_s21_strlen(haystack);
  u = s21_strlen(needle);
  char *copy_haystack = (char *)haystack;
  char *copy_needle = (char *)needle;
  if (*copy_needle == '\0') {
    result = copy_haystack;
  } else {
    for (i = 0; i < s21_strlen(haystack); i++) {
      if (copy_haystack[i] == *copy_needle) {
        char *tmp = &copy_haystack[i];
        int result_tmp = s21_strncmp(tmp, copy_needle, u);
        if (result_tmp == 0) {
          result = &copy_haystack[i];
          break;
        }
      }
    }
  }
  return result;
}
// strchr – поиск последнего вхождения символа в строку
char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  s21_size_t i;
  s21_size_t n = s21_strlen(str) + 1;
  for (i = 0; i < n; i++) {
    if (str[i] == c) {
      result = (char *)(str + i);
    }
  }
  return result;
}

// strchr – поиск первого вхождения символа в строку
char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  s21_size_t i;
  s21_size_t n = s21_strlen(str) + 1;
  for (i = 0; i < n; i++) {
    if (str[i] == c) {
      result = (char *)(str + i);
      break;
    }
  }
  return result;
}

// strpbrk – поиск первого вхождения в строку символа из указанного множества.
char *s21_strpbrk(const char *str1, const char *str2) {
  int fl = 0;
  char *result = s21_NULL;
  for (int i = 0; str1[i] != '\0'; i++) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        fl = 1;
      }
      if (fl == 1) break;
    }
    if (fl == 1) {
      result = ((char *)str1 + i);
      break;
    } else {
      result = 0;
    }
  }
  return result;
}

// memchr – поиск первого вхождения указанного символа в массиве
void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *copy_str = (unsigned char *)str;
  int fl = 0;
  char *result = s21_NULL;
  unsigned char copy_c = c;
  s21_size_t i;
  for (i = 0; i < n && copy_str; i++) {
    if (*copy_str == copy_c) {
      fl = 1;
      break;
    }
    copy_str++;
  }
  if (fl == 1) {
    result = (void *)copy_str;
  } else {
    result = s21_NULL;
  }
  return result;
}
// memmove-eще одна функция для копирования n символов из src в dest
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  unsigned char *copy_dest = (unsigned char *)dest;
  unsigned char *copy_src = (unsigned char *)src;
  s21_size_t i;
  if (copy_dest < copy_src) {
    for (i = 0; i < n; i++) {
      copy_dest[i] = copy_src[i];
    }
  } else if (copy_dest > copy_src) {
    for (i = n; i > 0; i--) {
      copy_dest[i - 1] = copy_src[i - 1];
    }
  }
  return dest;
}

void *s21_to_upper(const char *str) {
  char *buf = s21_NULL;
  s21_size_t i = 0;
  s21_size_t length = s21_strlen(str);
  if (str) {
    buf = (char *)calloc(length, sizeof(char));
  }
  if (buf) {
    while (i <= length) {
      if (str[i] > 96 && str[i] < 123) {
        buf[i] = str[i] - 32;
      } else {
        buf[i] = str[i];
      }
      i++;
    }
  }
  return buf;
}

void *s21_to_lower(const char *str) {
  char *buf = s21_NULL;
  s21_size_t i = 0;
  s21_size_t length = s21_strlen(str);
  if (str) {
    buf = (char *)calloc(length, sizeof(char));
  }
  if (buf) {
    while (i <= length) {
      if (str[i] > 64 && str[i] < 91) {
        buf[i] = str[i] + 32;
      } else {
        buf[i] = str[i];
      }
      i++;
    }
  }
  return buf;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *result = s21_NULL;
    int proverka = start_index;
    s21_size_t length_src = s21_strlen(src);
    s21_size_t length_str = s21_strlen(str);
    int prov = length_src;
    if (proverka < 0){
        result = s21_NULL;
    } else if(str == s21_NULL && src != s21_NULL) {
        result = calloc(s21_strlen(src) + 1, sizeof(char));
        s21_strcpy(result, src);
    } else if (src != s21_NULL && str != s21_NULL) {
        result = calloc(length_src + length_str + 1, sizeof(char));
        if (result!= s21_NULL) {
            s21_size_t length_all = length_src + length_str;
            for (size_t i = 0, m = 0, n = 0; i < length_all; i++) {
                if (i < start_index || i >= start_index + length_str) {
                    result[i] = src[n];
                    n++;
                } else {
                    result[i] = str[m];
                    m++;
                }
            }
            result[length_all] = '\0';
        }
    } else if (prov <= proverka) {
        result = s21_NULL;
    }
    return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
    s21_size_t length_src = 0;
    s21_size_t first_length = 0;
    s21_size_t last_length = 0;
    s21_size_t res_length = 1;
    char* space = " ";
    const char* copy_trim = space;
    if (src != s21_NULL) {
        length_src = s21_strlen(src);
    }
    char* inverse = (char*)malloc(sizeof(char) * (length_src + 1));
    for (s21_size_t i = 0; i < length_src; i++) {
        inverse[i] = src[length_src - i - 1];
    }
    inverse[length_src] = '\0';
    if (trim_chars) {
        copy_trim = trim_chars;
    }
    if (src) {
        first_length = s21_strspn(src, copy_trim);
        last_length = s21_strspn(inverse, copy_trim);
    }
    if (first_length != length_src) {
        res_length = length_src - first_length - last_length + 1;
    }
    char *result = (char *)malloc(res_length);
    if (!src || !trim_chars) {
        result = s21_NULL;
    }
    if (result != s21_NULL) {
        for (s21_size_t i = 0; i < (res_length); i++) {
            result[i] = src[first_length + i];
        }
        result[res_length - 1] = '\0';
    }
    free(inverse);
    return result;
}
