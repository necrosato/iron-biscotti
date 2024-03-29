#!/bin/bash

PORT_FILE=$HOME/ports_in_use
LOG_FILE=$HOME/reverse_tunnel.log

function append () {
(
  # Lock file descriptor
  flock -n 100 || exit 1
  TEMP=$(mktemp)
  cp $PORT_FILE $TEMP
  # Once locked
  echo "$1" >> $TEMP
  cat $TEMP > $PORT_FILE
)100<>$PORT_FILE
}

function delete () {
(
  # Lock file descriptor
  flock -n 100 || exit 1
  TEMP=$(mktemp)
  cp $PORT_FILE $TEMP
  # Once locked
  sed -i "/${1}/d" $TEMP
  cat $TEMP > $PORT_FILE
)100<>$PORT_FILE
}

## Add log line
echo "$1 $2 : $(TZ="America/Los_Angeles" date)" >> $LOG_FILE

## ADD THINGS TO PORT 
append "$1 $2"
while true; do
  IN_USE=$(netstat -tuln | grep $1)
  if [[ "$IN_USE" == "" ]]; then
    delete "$1 $2"
    exit 1
  else
    sleep 1
  fi
done
