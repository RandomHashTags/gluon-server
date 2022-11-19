//
//  file_manager.h
//  quark
//
//  Created by Evan Anderson on 11/19/22.
//

#ifndef file_manager_h
#define file_manager_h

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "../../deps/tinydir/tinydir.h"

void file_manager_iterate_files(char *directory_path);

#endif /* file_manager_h */
