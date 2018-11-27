//
// file_utils.cpp
// Naookie Sato
//
// Created by Naookie Sato on 11/10/2018
// Copyright © 2018 Naookie Sato. All rights reserved.
//

#include <avr/pgmspace.h>

#include "file_utils.h"
 
void TypeKey(int key) {
  Keyboard.press(key);
  delay(40);
  Keyboard.release(key);
}

void TypeString(const char* string) {
  Keyboard.print(string);
}

void EnterCommand(const char* command, int dcount) {
  TypeString(command);
  TypeKey(KEY_RETURN);
  delay(dcount);
}

void WriteToFile(const char* filename, const char* string, const char* permissions, const char* owner, const char* group, int dcount) {
  TypeString("vim ");
  EnterCommand(filename, 500);
  TypeKey('i');
  TypeString(string);
  delay(dcount);
  TypeKey(KEY_ESC);
  EnterCommand(":wq", 500);
  TypeString("chmod ");
  TypeString(permissions);
  TypeString(" ");
  EnterCommand(filename, 0);
  TypeString("chown ");
  TypeString(owner);
  TypeString(":");
  TypeString(group);
  TypeString(" ");
  EnterCommand(filename, 0);
}
