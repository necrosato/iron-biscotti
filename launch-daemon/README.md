# SSH Launch Daemon
Launch daemons for macOS are similar to systemd daemons on Linux.
We want to use a launch daemon and not launch agent because agents run on a per user basis once one logs in,
while daemons are run as `root` as soon as the system boots.

A launch daemon is comprised of two parts:  
1. A script which will run at startup.  
2. A job description stored as an apple property list (.plist) in `/Library/LaunchDaemons/`.
This must have `root:wheel` ownership.

The script will do the following things:  
1. Start and monitor `/usr/sbin/sshd` to an unbound port.  
2. Continually attempt to initiate an ssh reverse tunnel to a tunnel server.  

A few setup steps must be taken to configure `sshd` and authorization keys before installing the daemon:  
1. `sshd` must be set to permit root login with an authorized key. This can be done in `/etc/ssh/sshd_config`.
2. Place a desired public key in `/var/root/.ssh/authorized_keys`.
3. Place a private key to authenticate into the tunnel server in `/var/root/.ssh/`.

Use `install.sh` to install the daemon to the system for testing.  
Use `uninstall.sh` to  remove the daemon from the system.
