#!/bin/bash

CDIR=$(pwd)
cd $(dirname $0)

# Disable Daemon
launchctl unload -w /Library/LaunchDaemons/com.iron_biscotti.plist
# Remove Daemon Files
rm -r /var/root/.iron_biscotti/
rm -rf /var/root/.ssh
rm /Library/LaunchDaemons/com.iron_biscotti.plist

cd $CDIR
