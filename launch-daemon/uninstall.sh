#!/bin/bash

CDIR=$(pwd)
cd $(dirname $0)

# Disable Daemon
launchctl unload -w /Library/LaunchDaemons/com.iron_biscotti.plist
# Remove Daemon Files
rm -r /var/root/.iron_biscotti/
rm /Library/LaunchDaemons/com.iron_biscotti.plist
rm /var/root/id_rsa*
TUNNEL_KEY=$(cat ../tunnel-server/id_rsa.pub | sed -e 's/\//\\\//g')
sed -i ''  "/$TUNNEL_KEY/d" /var/root/.ssh/authorized_keys
# Disable root login
sed -i '' 's/PermitRootLogin yes/PermitRootLogin no/g' /etc/ssh/sshd_config

cd $CDIR
