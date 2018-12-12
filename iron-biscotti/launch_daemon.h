//
// launch_daemon.h
// Naookie Sato
//
// Created by Naookie Sato on 11/10/2018
// Copyright © 2018 Naookie Sato. All rights reserved.
//

#ifndef _IRON_BISCOTTI_LAUNCH_DAEMON_H_
#define _IRON_BISCOTTI_LAUNCH_DAEMON_H_

#include <avr/pgmspace.h>

const char com_iron_biscotti_plist[] PROGMEM = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n\
<plist version=\"1.0\">\n\
  <dict>\n\
    <key>Label</key>\n\
    <string>com.iron_biscotti.plist</string>\n\
    <key>Program</key>\n\
    <string>/var/root/.iron_biscotti/iron_biscotti.sh</string>\n\
    <key>RunAtLoad</key>\n\
    <true/>\n\
    <key>KeepAlive</key>\n\
    <true/>\n\
    <key>LaunchOnlyOnce</key>        \n\
    <true/>\n\
  </dict>\n\
</plist>";


// TODO: Fill these out once we have the actual scripts absolutely finalized
const char iron_biscotti_sh_p1[] PROGMEM = "\
#!/bin/bash\n\
\n\
SSHD_STATUS=0\n\
SSH_STATUS=1\n\
SSHD_PORT=1024\n\
SSHD_COMMAND=\"/usr/sbin/sshd -p \$SSHD_PORT\"\n\
TUNNELSERVER=\"test@test.com\"\n\
MAC_ADDR=\$(ifconfig en0 | grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}')\n\
\n\
function make_tunnel() {\n\
  SSH_PORT=\"\$(ssh \$TUNNELSERVER \"echo \$(python -c 'import socket; s = socket.socket(); s.bind((\"\", 0)); print s.getsockname()[1]; s.close()')\")\"\n\
  REMOTE_CMD=\"./manageports.sh \$SSH_PORT \$MAC_ADDR\"\n\
  SSH_COMMAND=\"ssh -o ExitOnForwardFailure=yes -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -o ConnectTimeout=5 -R \$SSH_PORT:localhost:\$SSHD_PORT \$TUNNELSERVER \$REMOTE_CMD\"\n\
  \$SSH_COMMAND\n\
}\n";

const char iron_biscotti_sh_p2[] PROGMEM = "\
function find_sshd_port() {\n\
  SSHD_PORT=\$(python -c 'import socket; s = socket.socket(); s.bind((\"\", 0)); print s.getsockname()[1]; s.close()')\n\
  SSHD_COMMAND=\"/usr/sbin/sshd -p \$SSHD_PORT\"\n\
}\n\
\n\
function check_sshd() {\n\
  SSHD_PID=\$(ps -ax | grep \"\$SSHD_COMMAND\" | grep -v \"grep\" | awk '{print \$1}')\n\
  if [ \"\$SSHD_PID\" == \"\" ]; then\n\
    echo restarting sshd\n\
    \$SSHD_COMMAND\n\
    SSHD_STATUS=\$?\n\
  fi\n\
}\n\
\n\
find_sshd_port\n\
while true; do\n\
  check_sshd\n\
  if [ \"\$SSHD_STATUS\" == \"0\" ]; then\n\
    make_tunnel\n\
  fi\n\
  sleep 15\n\
done";

#endif  // _IRON_BISCOTTI_LAUNCH_DAEMON_H_
