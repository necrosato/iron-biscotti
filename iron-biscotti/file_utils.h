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
void TypeString(String string);

// Types a string followed by enter
void EnterCommand(String command);

// Write a string to filename using vim.
// permissions should be an octet as a string
// owner and group strings are a UNIX `owner:group` pair.
void WriteToFile(String filename, String string, String permissions, String owner, String group);

#endif  // _IRON_BISCOTTI_FILE_UTILS_H_
