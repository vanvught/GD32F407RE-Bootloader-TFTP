#!/bin/bash

chmod u+x do-tftp.sh

cd ../udp_send/Release
make clean && make
chmod u+x udp_send
ls -al udp_send
cd -
