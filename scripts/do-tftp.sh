#!/bin/bash
export PATH=./:../../scripts:$PATH

if [ -f "gd32f407.bin" ]; then
cp gd32f407.bin gd32f4xx.bin
else
exit
fi

echo '!tftp#1' | udp_send $1 
echo '?tftp#' | udp_send $1 

tftp $1 << -EOF
binary
put gd32f4xx.bin
quit
-EOF

rm gd32f4xx.bin

echo '!tftp#0' |udp_send $1 
echo '?tftp#' | udp_send $1 

sleep 2

echo -e "Rebooting..."
echo '?reboot##' | udp_send $1 

ON_LINE=$(echo '?list#' | udp_send $1 ) || true

while  [ "$ON_LINE" == "" ]
 do
  ON_LINE=$(echo '?list#' | udp_send $1 )  || true
done

echo -e "[$ON_LINE]"
echo -e "$(echo '?version#' | udp_send $1 )"
