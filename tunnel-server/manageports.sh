#!/bin/bash

PORT_FILE=/root/ports_in_use

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

## ADD THINGS TO PORT 
append "$1 $2"
while true; do
  IN_USE=$(netstat -tulnp | grep $1)
  if [[ "$IN_USE" == "" ]]; then
    delete "$1 $2"
    exit 1
  else
    sleep 1
  fi
done
