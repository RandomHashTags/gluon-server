//
//  file_manager.c
//  gluon
//
//  Created by Evan Anderson on 11/19/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "file_manager.h"

void file_manager_iterate_files(char *directory_path) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directory_path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            const char *file_name = ent->d_name;
            printf("%s\n", file_name);
        }
        closedir(dir);
    }
}

void file_manager_read_file(const char *file_name, void *pointer(char *characters, unsigned long length)) {
    FILE *file = fopen(file_name, "rb");
    fseek(file, 0, SEEK_END);
    const unsigned long file_length = ftell(file);
    rewind(file);
    
    char buffer[file_length];
    fread(buffer, file_length, 1, file);
    fclose(file);
    pointer(buffer, file_length);
    //free(buffer);
}
