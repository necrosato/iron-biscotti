//
// ssh_keys.h
// Naookie Sato
//
// Created by Naookie Sato on 11/11/2018
// Copyright © 2018 Naookie Sato. All rights reserved.
//

#ifndef _IRON_BISCOTTI_SSH_KEYS_H_
#define _IRON_BISCOTTI_SSH_KEYS_H_

#include <avr/pgmspace.h>

const char ssh_private_key[] PROGMEM = "\
-----BEGIN RSA PRIVATE KEY-----\n\
MIIEogIBAAKCAQEA3Mw6fCbimFrlVf9Q4oZr1w5zn9wfDCTiy8pEVDXFy6EUACKN\n\
H06EkDMzwg9zevJmU5zeb0e0nFtEPJf19Tv20aEGGeR9RHe8ZYfA99wGyxTyPG3g\n\
OZgtJ0UTKyzsMaNBCHr8d03aELmWF/qkmJcNfBRk7SFHG55aUQcGCAziuxLbAbGP\n\
nUUlgiH5Am1GpIEGOA+Vc2/nqRQ+QY1xc7B3KG+pIQGXcB+TQLxfaaJvlma7zTeH\n\
YPO04OQ3pCiVHBJULaaupdMlDtbBCZN0aRnVZYxgDOExQzIl+QP+7ylD+Bnp1ha1\n\
AB5BWF78aT5pOSSD7fuPAR4TKrCyTtTdcL6IRwIDAQABAoIBAGyB1TAUMAFtkgzc\n\
JxTbuH18dagXFg7yxZ4e7ctwjZ7PrzONx0qeXJk9AG+bBkZif5URn2KSm5jHZVZd\n\
25rD+Dz25DevSTxvl19SAqwMLi55Qb4exTWoqnAFCzGJpx2RvDD9t7qtwL+9ZJyu\n\
KVtvyEm1ABBk7TwOaxYs3HLyWi5SYSVOGw6J3PbsM20HomKjU35mUCBwc2Vv57U9\n\
7Qi0MlXymuLjbrnaRe4ZbCyAz+9KS81P85JKc24EPuR+dr0smHt3Mz4n0T3BbAbe\n\
Sxv01k6XFXDpdd97Ko9TQmXTfJEZdoEOnS0rU9Qkmlzw2YK+nJHhHot1qpvF1V5H\n\
wjEwpnECgYEA8hCiu7Iv6adEIxW37D1U8VuPhNAYDMiH0FtlH6Tal2oRBNV4vHBt\n\
re0sXf++mnCjoobRVuhhVWcpRjziyY8J9vfannk7mThU+U1v72qGjkTRuDcryYaK\n\
ggg2/PGv8UfTJWuuIAZwFqp1b/7zxNrDZGalpCZXkbSNjR3qUm8GXP8CgYEA6YIs\n\
VohAO0zdIiZTw9zWXOjSdLBXrGkeY1F9eHT3iTLE6uHrU1iVeznMYXsVNrMcI1VD\n\
1iQwfw84ySFIVDCeqqUOUyuCr54tkxztFHDF5G9SVIifwUc213u4OXRkwcPu2+xm\n\
EX3YadfOS/a5tkOfnMdM4mqil+26Z9rdI09WrLkCgYBRc0+OoLKGiIXg2Fn+39RJ\n\
MmnkYrD0/DTW4ynvr+Tttf7sBXiOz7XYJEodhwR3qxckhQDDoYW+2uuEetBEyiCs\n\
PVIOqPRo5g+Ro4DaqpmEHZwDxGyzbtYEUwdNrXVqVqSxnr4EgKYOumSxvrP/tSyy\n\
B+gMh+pHWN2Yckx6WGlnuQKBgDjImAGe9oe1JF1Glr4deN91GqCXtWpO0b3zNiDR\n\
yNRLTUmVEMXe19L0djgKV1lK6v/In0t213g+el+mwVD/1cXHh5lADnKoc4q/0QNU\n\
fTsUux+lbbvxlmuGQYFvRYU9IVvHu/Zq9PKgMSGV6QlinnDgoli497sca2UP+xC4\n\
HWq5AoGAQvA74pKPFy50B3XCrPX5CIcqkcJxv3CjZNlVm4Yl7AOa0SoU3VVcW+Ms\n\
5ioOXtKTfyBIb5/anMIF+Arsj9axXuc0W1mRa4oDpgv6ZWdyLkoD7OEAnmYjlvuo\n\
xgE7N3cvBoGkBU5dxHKxH5K4kK9N+sCUuL/K4HFk+7yD657OP5k=\n\
-----END RSA PRIVATE KEY-----";

const char ssh_public_key[] PROGMEM = "\
ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDczDp8JuKYWuVV/1DihmvXDnOf3B8MJOLLykRUNcXLoRQAIo0fToSQMzPCD3N68mZTnN5vR7ScW0Q8l/X1O/bRoQYZ5H1Ed7xlh8D33AbLFPI8beA5mC0nRRMrLOwxo0EIevx3TdoQuZYX+qSYlw18FGTtIUcbnlpRBwYIDOK7EtsBsY+dRSWCIfkCbUakgQY4D5Vzb+epFD5BjXFzsHcob6khAZdwH5NAvF9pom+WZrvNN4dg87Tg5DekKJUcElQtpq6l0yUO1sEJk3RpGdVljGAM4TFDMiX5A/7vKUP4GenWFrUAHkFYXvxpPmk5JIPt+48BHhMqsLJO1N1wvohH iron-biscotti";

const char ssh_tunnel_server_public_key[] PROGMEM = "\
ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQC1/io5USTOXO9kHXyfP3aH3JWSz63YaCU6xY3gJwFSQBAL+ywt8Cppkoz/3JyhLFI11pK+eMRJpbsbcMO44bLiDBWAS7N1odMqwmCpVadMbRJVe7v6M6l3Y48ypbdBB3Hed5c0w3yg8nHi8j7xTDBrNYfXZucAF5DU4ofmphyVuijezMwZZaukG3C/sbdkq9rv4UUWl0DB/19YlpQJn4ycLbV+SDe6q/K/G40+35s6XOLl+VDYcpYd9xyRQI3D7Eaptojpqcut5goqatQIwgjwzvZhBXFZu2e4JSsQSQ0WwiiBzkULchOqLY9Oq1ppEYi+vmckXIqF3hD6othADh9B iron-biscotti-tunnel-server";

const char ssh_setup[] PROGMEM = "\
sed -i '' 's/#* *PermitRootLogin .*/PermitRootLogin yes/g' /etc/ssh/sshd_config\n\
sed -i '' 's/#* *ServerAliveInterval .*/ServerAliveInterval 30/g' /etc/ssh/ssh_config\n\
sed -i '' 's/#* *ServerAliveCountMax .*/ServerAliveCountMax 2/g' /etc/ssh/ssh_config\n\
grep -q '^PermitRootLogin ' /etc/ssh/sshd_config || echo 'PermitRootLogin yes' >> /etc/ssh/sshd_config\n\
grep -q '^ServerAliveInterval ' /etc/ssh/ssh_config || echo 'ServerAliveInterval 30' >> /etc/ssh/ssh_config\n\
grep -q '^ServerAliveCountMax ' /etc/ssh/ssh_config || echo 'ServerAliveCountMax 2' >> /etc/ssh/ssh_config\n";

#endif  // _IRON_BISCOTTI_SSH_KEYS_H_
