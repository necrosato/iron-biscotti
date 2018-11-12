#include "launch_daemon.h"
#include "file_utils.h"

char buffer[1024];

void iron_biscotti() {
  // Mount the filesystem
  EnterCommand("mount -uw /");
  // Set the home var so vim doesn't trip
  EnterCommand("export HOME=/var/root/");
  strcpy_P(buffer, com_iron_biscotti_plist);
  WriteToFile("test", buffer, "644", "root", "wheel");
}

void setup() {
  // Begining the Keyboard stream
  Keyboard.begin();
  // pushbutton setup
  pinMode(8, INPUT);
  delay(100);
}

void loop() {
  if(digitalRead(8) == HIGH) {
    iron_biscotti();
  }
  delay(250);
}
