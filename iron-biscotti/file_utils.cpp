//
// file_utils.cpp
// Naookie Sato
//
// Created by Naookie Sato on 11/10/2018
// Copyright © 2018 Naookie Sato. All rights reserved.
//

#include "file_utils.h"
 
void TypeKey(int key) {
  Keyboard.press(key);
  delay(40);
  Keyboard.release(key);
}

void TypeString(String string) {
  for (auto c : string) {
    TypeKey(c);
  }
}

void EnterCommand(String command) {
  TypeString(command);
  TypeKey(KEY_RETURN);
}

void WriteToFile(String filename, String string, String permissions, String owner, String group) {
  EnterCommand("vim " + filename);
  TypeKey('i');
  TypeString(string);
  TypeKey(KEY_ESC);
  EnterCommand(":wq");
  EnterCommand("chmod " + permissions + " " + filename);
  EnterCommand("chown " + owner + ":" + group + " " + filename);
}