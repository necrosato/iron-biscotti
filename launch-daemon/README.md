Launch daemons for macOS are similar to systemd daemons on Linux.
We want to use a launch daemon and not launch agent because agents run on a per user basis once one logs in,
while daemons are run as `root` as soon as the system boots.

A launch daemon is comprised of two parts:
1. A script which will run at startup.
2. A job description stored as an apple property list (.plist) in `/Library/LaunchDaemons/`.
This must be owned by `root`.

It will do the following things:
1. Start and monitor `/usr/sbin/sshd` to an unbound port.
2. Continually attempt to initiate an ssh reverse tunnel to a tunnel server.
