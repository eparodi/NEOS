#!/bin/bash
#RECORDAR NEGRO QUE TENES QUE HACER ANTES sudo apt-get install uml-utilities bridge-utils
sudo tunctl -u $(whoami)
sudo tunctl -u $(whoami)
sudo brctl addbr br0
sudo brctl addif br0 tap0
sudo brctl addif br0 tap1
sudo ip link set dev br0 up
sudo ip link set dev tap0 up
sudo ip link set dev tap1 up
