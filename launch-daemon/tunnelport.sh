#!/bin/bash

# This script is run on the tunnel server
$TUNNELSERVER="test@test.com"

# Lockfile used to ensure only one instance of this script is running at any one time
lockfile script.lock

# Find out who logged in and from where
TARGET="$(w -sh | tail -1)"
read user tty addr rest <<< "$TARGET"
TARGET="$user@$addr"

# Get ssh port
SSH_PORT=$(python -c 'import socket; s = socket.socket(); s.bind(("", 0)); print s.getsockname()[1]; s.close()')

# Command to be run on target
SSH_COMMAND="ssh -o BatchMode=yes -o ExitOnForwardFailure=yes -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -o ConnectTimeout=5 -f -N -R $SSH_PORT:localhost:$1 $TUNNELSERVER"

# Set up reverse tunnel on target
ssh -p $1 $TARGET "echo $SSH_COMMAND"

# Save target data
echo "$user@localhost $1" >> ~/targets

# Remove lock
rm -f script.lock
