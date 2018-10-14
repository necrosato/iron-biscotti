#!/bin/bash

cp iron_biscotti.sh /var/root/.iron_biscotti.sh
chown root:wheel /var/root/.iron_biscotti.sh
cp com.iron_biscotti.plist /Library/LaunchDaemons/com.iron_biscotti.plist
chown root:wheel /Library/LaunchDaemons/com.iron_biscotti.plist

launchctl load -w /Library/LaunchDaemons/com.iron_biscotti.plist
