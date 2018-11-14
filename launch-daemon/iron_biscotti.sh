#!/bin/bash

SSHD_COMMAND="/usr/sbin/sshd -p $SSHD_PORT"
SSHD_STATUS=0


function find_port() {
  SSHD_PORT=$(python -c 'import socket; s = socket.socket(); s.bind(("", 0)); print s.getsockname()[1]; s.close()')
  SSHD_COMMAND="/usr/sbin/sshd -p $SSHD_PORT"
  SSH_COMMAND="./tunnel.sh $SSHD_PORT"
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
    # Exits with status code '1' if the connection was not established
    $SSH_COMMAND
    SSH_STATUS=$?
    echo "Status Code: $SSH_STATUS"
  fi
}

while true; do
  find_port
  check_sshd
  if [ "$SSHD_STATUS" == "0" ]; then
    check_ssh
  fi
  sleep 15
done
