#include <stdlib.h>
#include <string.h>

/**
 * Returns whether a string starts with another string.
 *
 * Returns true if the string is as long as the prefix or longer and the first
 * characters of string are the same as the prefix.
 *
 * Code copied from stackoverflow written by T.J. Crowder:
 * https://stackoverflow.com/questions/4770985/how-to-check-if-a-string-starts-with-another-string-in-c
 */
_Bool startsWith(const char *str, const char *prefix)
{
    size_t lenprefix = strlen(prefix),
           lenstr = strlen(str);
    return lenstr < lenprefix ? 0 : strncmp(prefix, str, lenprefix) == 0;
}

