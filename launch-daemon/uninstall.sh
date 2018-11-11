#!/bin/bash

# Disable Daemon
launchctl unload -w /Library/LaunchDaemons/com.iron_biscotti.plist
# Remove Daemon Files
rm /var/root/.iron_biscotti.sh
rm /Library/LaunchDaemons/com.iron_biscotti.plist
# Disable root login
sed -i '' 's/PermitRootLogin yes/PermitRootLogin no/g' /etc/ssh/sshd_config
