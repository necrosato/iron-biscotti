#!/bin/bash

TUNNELSERVER="test@test.com"

# Start local forward and run script on tunnel server
ssh -f -N -L $1:localhost:22 $TUNNELSERVER
ssh $TUNNELSERVER "echo bash ~/tunnelport.sh $1"

if [ "$?" -eq 0 ]; then
  exit 0
else
  echo connection failed
  exit 1
fi

