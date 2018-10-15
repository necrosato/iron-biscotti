#!/bin/bash

IP=127.0.0.1
PORT_BEGIN=10000
SSHD_PORT=10000
SSHD_COMMAND="/usr/sbin/sshd -p $SSHD_PORT"
SSHD_STATUS=0

function find_port() {
  for ((port=$PORT_BEGIN; port<=$PORT_BEGIN+1000; port++))
    do
      nc -z $IP $port
      if [ "$?" -eq 1 ]; then
        SSHD_PORT=$port	
	break
      fi
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

# Exits with status code '1' if the connection was not established
SSH_COMMAND="./tunnel.sh $SSHD_PORT"

function check_ssh() {
  SSH_PID=$(ps -ax | grep "$SSH_COMMAND" | grep -v "grep" | awk '{print $1}')
  if [ "$SSH_PID" == "" ]; then
    $SSH_COMMAND
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
