#!/bin/bash
set -e
cd $(dirname $0)
IMAGENAME=marshalfuzz
rm -rf work
mkdir -p work
sudo docker build -t $IMAGENAME .
sudo docker run -d -v work:/home/$user/work $IMAGENAME
