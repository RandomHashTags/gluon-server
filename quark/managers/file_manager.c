//
//  file_manager.c
//  quark
//
//  Created by Evan Anderson on 11/19/22.
//

#include <string.h>
#include "file_manager.h"

void file_manager_iterate_files(char *directory_path) {
    tinydir_dir dir;
    tinydir_open(&dir, directory_path);
    
    while (dir.has_next) {
        tinydir_file file;
        tinydir_readfile(&dir, &file);
        
        printf("%s\n", file.name);
        tinydir_next(&dir);
    }
    tinydir_close(&dir);
}
