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

/**
 * Strips a trailing '\n' from the specified string, replaces '\n' by '\0'.
 *
 * @param str char * a zero terminated string.
 */
void strip_trailing_newline(char *str)
{
    size_t len = strlen(str);
    str[len-1] = str[len-1] == '\n' ? '\0' : str[len-1];
}
