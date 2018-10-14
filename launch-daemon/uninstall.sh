#!/bin/bash

launchctl unload -w /Library/LaunchDaemons/com.iron_biscotti.plist
rm /var/root/.iron_biscotti.sh
rm /Library/LaunchDaemons/com.iron_biscotti.plist
