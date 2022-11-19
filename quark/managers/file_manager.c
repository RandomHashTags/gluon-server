//
//  file_manager.c
//  quark
//
//  Created by Evan Anderson on 11/19/22.
//

#include <stdio.h>
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
