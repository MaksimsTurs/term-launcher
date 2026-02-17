#ifndef H_LAUNCHER_UTILITY
#define H_LAUNCHER_UTILITY

#define LAUNCHER_KEY_ARROW_RIGHT 67
#define LAUNCHER_KEY_ARROW_LEFT  68

int launcher_compare_names(const char* f_str, const char* s_str, int length);
unsigned char launcher_is_valid_key(char ch);

#endif
