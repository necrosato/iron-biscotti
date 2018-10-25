#!/bin/bash

SSHD_PORT=10000
SSHD_COMMAND="/usr/sbin/sshd -p $SSHD_PORT"
SSHD_STATUS=0

function find_port() {
  read lower_port upper_port < /proc/sys/net/ipv4/ip_local_port_range

  while :; do
    for ((port = lower_port; port <= upper_port; port++)); do
      nc -z 127.0.0.1 $port
      if [ "$?" -eq 1 ]; then
        SSHD_PORT=$port	
        SSHD_COMMAND="/usr/sbin/sshd -p $SSHD_PORT"
        SSH_COMMAND="./tunnel.sh $SSHD_PORT"
        break 2
      fi
    done
  done
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
    # If successful saves the port allocated message to file
    $SSH_COMMAND > port 2>&1
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
