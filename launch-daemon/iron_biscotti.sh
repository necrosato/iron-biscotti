#!/bin/bash

SSHD_STATUS=0
SSHD_PORT=1024
SSHD_COMMAND="/usr/sbin/sshd -p $SSHD_PORT"
TUNNELSERVER="test@test.com"
while [[ "$MAC_ADDR" == "" ]]; do
  MAC_ADDR=$(networksetup -getmacaddress en0 | grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}')
  sleep 1
done

function make_tunnel() {
  SSH_PORT="$(ssh $TUNNELSERVER "echo $(python -c 'import socket; s = socket.socket(); s.bind(("", 0)); print s.getsockname()[1]; s.close()')")"
  REMOTE_CMD="/usr/local/bin/manageports.sh $SSH_PORT $MAC_ADDR"
  SSH_COMMAND="ssh -o ExitOnForwardFailure=yes -o ConnectTimeout=5 -R $SSH_PORT:localhost:$SSHD_PORT $TUNNELSERVER $REMOTE_CMD"
  $SSH_COMMAND
}

function find_sshd_port() {
  SSHD_PORT=$(python -c 'import socket; s = socket.socket(); s.bind(("", 0)); print s.getsockname()[1]; s.close()')
  SSHD_COMMAND="/usr/sbin/sshd -p $SSHD_PORT"
}

function check_sshd() {
  SSHD_PID=$(ps -ax | grep "$SSHD_COMMAND" | grep -v "grep" | awk '{print $1}')
  SSHD_STATUS=0
  if [ "$SSHD_PID" == "" ]; then
    echo restarting sshd
    $SSHD_COMMAND
    SSHD_STATUS=$?
  fi
}

find_sshd_port
while true; do
  check_sshd
  if [ "$SSHD_STATUS" == "0" ]; then
    make_tunnel
  fi
  sleep 15
done
