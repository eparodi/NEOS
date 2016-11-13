#!/bin/bash
#RECORDAR NEGRO QUE TENES QUE HACER ANTES sudo apt-get install uml-utilities bridge-utils
sudo tunctl -u $(whoami)
sudo tunctl -u $(whoami)
sudo tunctl -u $(whoami)
sudo ip link set dev br0 down
sudo brctl delbr br0
sudo brctl addbr br0
sudo brctl addif br0 tap0
sudo brctl addif br0 tap1
sudo brctl addif br0 tap2
sudo ip link set dev br0 up
sudo ip link set dev tap0 up
sudo ip link set dev tap1 up
sudo ip link set dev tap2 up
