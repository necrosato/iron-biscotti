//
// file_utils.h
// Naookie Sato
//
// Created by Naookie Sato on 11/10/2018
// Copyright © 2018 Naookie Sato. All rights reserved.
//

#ifndef _IRON_BISCOTTI_FILE_UTILS_H_
#define _IRON_BISCOTTI_FILE_UTILS_H_

#include "Keyboard.h"

// Types a single key and releases it.
void TypeKey(int key);

// Types a string, one char at a time
void TypeString(const char* string);

// Types a string followed by enter
// wait for dcount milliseconds before returning to allow type time
void EnterCommand(const char* command, int dcount);

// Write a string to filename using vim.
// permissions should be an octet as a string
// owner and group strings are a UNIX `owner:group` pair.
// NOTE: Using const char* to avoid memory issues with large string in flash memory
void WriteToFile(const char* filename, const char* string, const char* permissions, const char* owner, const char* group, int dcount);

#endif  // _IRON_BISCOTTI_FILE_UTILS_H_
