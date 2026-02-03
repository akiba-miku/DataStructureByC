#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_buffer.h"

#define DEFAULT_STRING_BUFFER_CAPACITY 16 
#define DEFAULT_STRING_BUFFER_EXPAND_FACTOR 1.5

void ds_string_init(ds_string *sb){
    sb->str = (char *)malloc(sizeof(char) * DEFAULT_STRING_BUFFER_CAPACITY);
    if (sb->str) {
        sb->str[0] = '\0';
    }
    sb->length = 0;
    sb->capacity = DEFAULT_STRING_BUFFER_CAPACITY;
}

void ds_string_free(ds_string *sb){
    if (sb->str) {
        free(sb->str);
        sb->str = NULL;
    }
    sb->length = 0;
    sb->capacity = 0;
}

static void resize(ds_string *sb, size_t min_expand_capacity){
    size_t new_capacity = (size_t)(sb->capacity * DEFAULT_STRING_BUFFER_EXPAND_FACTOR);
    
    if(new_capacity < min_expand_capacity){
        new_capacity = min_expand_capacity;
    }

    char *new_str = realloc(sb->str, new_capacity);
    if (new_str == NULL) {
        perror("Error: String buffer realloc failed!");
        exit(1);
    }
    
    sb->str = new_str;
    sb->capacity = new_capacity;
}

// append string
void ds_string_append(ds_string *sb, const char *str){
    if (str == NULL) return;

    size_t str_len = strlen(str);
    size_t required_capacity = sb->length + str_len + 1;
    
    if(required_capacity > sb->capacity){
        resize(sb, required_capacity);
    }
    
    memcpy(sb->str + sb->length, str, str_len);
    
    sb->length += str_len;
    
    sb->str[sb->length] = '\0';
}

// append char
void ds_string_append_char(ds_string *sb, char c){
    size_t required_capacity = sb->length + 2;
    if(required_capacity > sb->capacity){
        resize(sb, required_capacity);
    }
    
    sb->str[sb->length] = c;
    sb->length++;
    sb->str[sb->length] = '\0';
}

// append int
void ds_string_append_int(ds_string *sb, int n){
    char buffer[32];
    snprintf(buffer, 32, "%d", n);
    ds_string_append(sb, buffer);
}

const char *ds_string_c_str(ds_string *sb){
    return sb->str;
}

size_t ds_string_length(ds_string *sb){
    return sb->length;
}

void ds_string_clear(ds_string *sb){
    sb->length = 0;
    if (sb->str) {
        sb->str[0] = '\0';
    }
}