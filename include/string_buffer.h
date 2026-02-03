#ifndef DS_STRING_BUFFER_H
#define DS_STRING_BUFFER_H

#include <stddef.h> // for size_t

typedef struct {
    char *str;       
    size_t length;   
    size_t capacity; 
} ds_string;

// init
void ds_string_init(ds_string *sb);

// destroy
void ds_string_free(ds_string *sb);

// append the other string
void ds_string_append(ds_string *sb, const char *str);

// append the character
void ds_string_append_char(ds_string *sb, char c);

// append the interger
void ds_string_append_int(ds_string *sb, int n);

// get c_str
const char *ds_string_c_str(ds_string *sb);

// get_length
size_t ds_string_length(ds_string *sb);

// clear but no free memory
void ds_string_clear(ds_string *sb);

#endif