#!/bin/bash

CDIR=$(pwd)
cd $(dirname $0)

# Generate Host Keys
ssh-keygen -A
# Enable root login
sed -i '' 's/PermitRootLogin no/PermitRootLogin yes/g' /etc/ssh/sshd_config
# Setup files for daemon
cp iron_biscotti.sh /var/root/.iron_biscotti.sh
chown root:wheel /var/root/.iron_biscotti.sh
cp com.iron_biscotti.plist /Library/LaunchDaemons/com.iron_biscotti.plist
chown root:wheel /Library/LaunchDaemons/com.iron_biscotti.plist

# Enable daemon
launchctl load -w /Library/LaunchDaemons/com.iron_biscotti.plist
cd $CDIR
