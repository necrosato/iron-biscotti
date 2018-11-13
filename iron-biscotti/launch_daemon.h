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
    <string>/var/root/.iron_biscotti.sh</string>\n\
    <key>RunAtLoad</key>\n\
    <true/>\n\
    <key>KeepAlive</key>\n\
    <true/>\n\
    <key>LaunchOnlyOnce</key>        \n\
    <true/>\n\
  </dict>\n\
</plist>";

// TODO: Fill these out once we have the actual scripts absolutely finalized
const char iron_biscotti_sh[] PROGMEM = "\
";

const char tunnel_sh[] PROGMEM = "\
";

#endif  // _IRON_BISCOTTI_LAUNCH_DAEMON_H_
