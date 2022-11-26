//
//  file_manager.h
//  quark
//
//  Created by Evan Anderson on 11/19/22.
//

#ifndef file_manager_h
#define file_manager_h

void file_manager_iterate_files(char *directory_path);
void file_manager_read_file(const char *file_name, void *pointer(char *characters, unsigned long length));

#endif /* file_manager_h */
