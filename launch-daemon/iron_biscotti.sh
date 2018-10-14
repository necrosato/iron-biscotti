#!/bin/bash

SSHD_PORT=10000
SSHD_COMMAND="/usr/sbin/sshd -p $SSHD_PORT"
SSHD_STATUS=0

function check_sshd() {
  SSHD_PID=$(ps -ax | grep "$SSHD_COMMAND" | grep -v "grep" | awk '{print $1}')
  if [ "$SSHD_PID" == "" ]; then
    echo restarting sshd
    $SSHD_COMMAND
    SSHD_STATUS=$?
  fi
}

# TODO: This should be the ssh command script which take the sshd port as an argument
SSH_COMMAND=

function check_ssh() {
  SSH_PID=$(ps -ax | grep "$SSH_COMMAND" | grep -v "grep" | awk '{print $1}')
  if [ "$SSH_PID" == "" ]; then
    $SSH_COMMAND
  fi
}

while true; do
  check_sshd
  if [ "$SSHD_STATUS" == "0" ]; then
    check_ssh
  fi
  sleep 15
done
