#!/bin/bash

# Setup sshd server with the proper config.

CDIR=$(pwd)
cd $(dirname $0)

# sed handles if option is incorrect or commented out
sed -i 's/#* *PermitRootLogin .*/PermitRootLogin no/g' /etc/ssh/sshd_config
sed -i 's/#* *PasswordAuthentication .*/PasswordAuthentication no/g' /etc/ssh/sshd_config
sed -i 's/#* *ClientAliveInterval .*/ClientAliveInterval 30/g' /etc/ssh/sshd_config
sed -i 's/#* *ClientAliveCountMax .*/ClientAliveCountMax 2/g' /etc/ssh/sshd_config
# grep handles cases where our desired option is not in the file
grep -q '^PermitRootLogin ' /etc/ssh/sshd_config || echo 'PermitRootLogin no' >> /etc/ssh/sshd_config
grep -q '^PasswordAuthentication ' /etc/ssh/sshd_config || echo 'PasswordAuthentication no' >> /etc/ssh/sshd_config
grep -q '^ClientAliveInterval ' /etc/ssh/sshd_config || echo 'ClientAliveInterval 30' >> /etc/ssh/sshd_config
grep -q '^ClientAliveCountMax ' /etc/ssh/sshd_config || echo 'ClientAliveCountMax 2' >> /etc/ssh/sshd_config

mkdir -p /home/pi/.ssh/
chown pi:pi /home/pi/.ssh/
cp id_rsa /home/pi/.ssh/id_rsa
chown pi:pi /home/pi/.ssh/id_rsa
chmod 400 /home/pi/.ssh/id_rsa
cp id_rsa.pub /home/pi/.ssh/id_rsa.pub
chown pi:pi /home/pi/.ssh/id_rsa.pub
chmod 644 /home/pi/.ssh/id_rsa.pub
grep -q "$(cat ../launch-daemon/id_rsa.pub)" /home/pi/.ssh/authorized_keys || \
  echo "$(cat ../launch-daemon/id_rsa.pub)" >> /home/pi/.ssh/authorized_keys
chown pi:pi /home/pi/.ssh/authorized_keys

systemctl enable ssh
systemctl restart ssh
cd $CDIR
