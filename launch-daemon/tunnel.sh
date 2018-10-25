#!/bin/bash

#TODO This shouldn't be static?
CNC="osmc@10.0.0.145"

ssh -o ExitOnForwardFailure=yes -o StrictHostKeychecking=no -o UserKnownHostsFile=/dev/null -o BatchMode=yes -o ConnectTimeout=5 -f -N -R 0:localhost:$1 $CNC 

if [ "$?" -eq 0 ]; then
  exit 0
else
  echo connection failed
  exit 1
fi

