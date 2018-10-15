#!/bin/bash

#TODO This shouldn't be static?
CNC="osmc@10.0.0.145"

echo $1
ssh -f -N -T -R $1:localhost:22 $CNC

if [ "$?" -eq 0 ]; then
  exit 0
else
  echo connection failed
  exit 1
fi

