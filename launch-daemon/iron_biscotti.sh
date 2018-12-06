#!/bin/bash

SSHD_STATUS=0
SSH_STATUS=1
TUNNELSERVER="test@test.com"
MAC_ADDR=$(ifconfig en0 | grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}')

function tunnel_port() {
  SSH_PORT="$(ssh $TUNNELSERVER "echo $(python -c 'import socket; s = socket.socket(); s.bind(("", 0)); print s.getsockname()[1]; s.close()')")"
  REMOTE_CMD="./manageports.sh $MAC_ADDR $SSH_PORT"
  SSH_COMMAND="ssh -o ExitOnForwardFailure=yes -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -o ConnectTimeout=5 -f -N -R $SSH_PORT:localhost:$SSHD_PORT $TUNNELSERVER $REMOTE_CMD"
}

function find_port() {
  SSHD_PORT=$(python -c 'import socket; s = socket.socket(); s.bind(("", 0)); print s.getsockname()[1]; s.close()')
  SSHD_COMMAND="/usr/sbin/sshd -p $SSHD_PORT"
}

function check_sshd() {
  SSHD_PID=$(ps -ax | grep "$SSHD_COMMAND" | grep -v "grep" | awk '{print $1}')
  if [ "$SSHD_PID" == "" ]; then
    echo restarting sshd
    $SSHD_COMMAND
    SSHD_STATUS=$?
  fi
}

function check_ssh() {
  SSH_PID=$(ps -ax | grep "$SSH_COMMAND" | grep -v "grep" | awk '{print $1}')
  if [ "$SSH_PID" == "" ]; then
    echo restarting ssh
    $SSH_COMMAND
    SSH_STATUS=$?
  fi
}

while true; do
  find_port
  check_sshd
  if [ "$SSHD_STATUS" == "0" ]; then
    until [ "$SSH_STATUS" == "0" ]; do
      tunnel_port
      check_ssh
    done
  fi
done
