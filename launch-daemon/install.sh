#!/bin/bash

# Install iron biscotti launch daemon on host

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
mkdir -p /var/root/.iron_biscotti/
cp iron_biscotti.sh /var/root/.iron_biscotti/iron_biscotti.sh
chown root:wheel /var/root/.iron_biscotti/iron_biscotti.sh
cp tunnel.sh /var/root/.iron_biscotti/tunnel.sh
chown root:wheel /var/root/.iron_biscotti/tunnel.sh
cp com.iron_biscotti.plist /Library/LaunchDaemons/com.iron_biscotti.plist
chown root:wheel /Library/LaunchDaemons/com.iron_biscotti.plist
mkdir -p /var/root/.ssh/
cp id_rsa /var/root/.ssh/id_rsa
chown root:root /var/root/.ssh/id_rsa
cp config /var/root/.ssh/config
chown root:root /var/root/.ssh/config
chmod 400 /var/root/.ssh/id_rsa
cp id_rsa.pub /var/root/.ssh/id_rsa.pub
chown root:root /var/root/.ssh/id_rsa.pub
chmod 644 /var/root/.ssh/id_rsa.pub
grep -q "$(cat ../tunnel-server/id_rsa.pub)" /var/root/.ssh/authorized_keys || \
  echo "$(cat ../tunnel-server/id_rsa.pub)" >> /var/root/.ssh/authorized_keys
chown root:root /var/root/.ssh/authorized_keys

# Enable daemon
launchctl load -w /Library/LaunchDaemons/com.iron_biscotti.plist
cd $CDIR
