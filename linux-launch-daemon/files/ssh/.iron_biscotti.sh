#!/bin/bash

SSHD_STATUS=0
SSHD_PORT=22
SSHD_COMMAND="/usr/sbin/sshd -p $SSHD_PORT"
TUNNELSERVER="pi@73.37.37.141"
while [[ "$MAC_ADDR" == "" ]]; do
  MAC_ADDR=$(cat /sys/class/net/eno1/address)
  sleep 1
done

function make_tunnel() {
  SSH_PORT="$(ssh -p 10010 $TUNNELSERVER "echo $(python -c 'import socket; s = socket.socket(); s.bind(("", 0)); print s.getsockname()[1]; s.close()')")"
  REMOTE_CMD="/usr/local/bin/manageports.sh $SSH_PORT $MAC_ADDR"
  SSH_COMMAND="ssh -p 10010 -o ExitOnForwardFailure=yes -o ConnectTimeout=5 -R $SSH_PORT:localhost:$SSHD_PORT $TUNNELSERVER $REMOTE_CMD"
  echo "Executing $SSH_COMMAND"
  $SSH_COMMAND
}

function find_sshd_port() {
  SSHD_PORT=$(python -c 'import socket; s = socket.socket(); s.bind(("", 0)); print s.getsockname()[1]; s.close()')
  SSHD_COMMAND="/usr/sbin/sshd -p $SSHD_PORT"
}

#find_sshd_port
while true; do
  #check_sshd
  #if [ "$SSHD_STATUS" == "0" ]; then
    make_tunnel
  #fi
  sleep 15
done
