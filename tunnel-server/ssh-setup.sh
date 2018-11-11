#!/bin/bash

# Setup sshd server with the proper config.

# grep handles cases where our desired option is not in the file
# sed handles if option is incorrect or commented out
grep -q -F 'PermitRootLogin' /etc/ssh/sshd_config || echo 'PermitRootLogin no' >> /etc/ssh/sshd_config
sed -i '' 's/.*PermitRootLogin.*/PermitRootLogin no/g' /etc/ssh/sshd_config
grep -q -F 'PasswordAuthentication' /etc/ssh/sshd_config || echo 'PasswordAuthentication no' >> /etc/ssh/sshd_config
sed -i '' 's/.*PasswordAuthentication.*/PasswordAuthentication no/g' /etc/ssh/sshd_config
grep -q -F 'ClientAliveInterval' /etc/ssh/sshd_config || echo 'ClientAliveInterval 30' >> /etc/ssh/sshd_config
sed -i '' 's/.*ClientAliveInterval.*/ClientAliveInterval 30/g' /etc/ssh/sshd_config
grep -q -F 'ClientAliveCountMax' /etc/ssh/sshd_config || echo 'ClientAliveCountMax 2' >> /etc/ssh/sshd_config
sed -i '' 's/.*ClientAliveMaxCount.*/ClientAliveMaxCount 2/g' /etc/ssh/sshd_config
systemctl restart ssh
