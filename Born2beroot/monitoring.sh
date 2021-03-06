#!/bin/sh
echo "  #Architecture: $(uname -a)"
echo "  #CPU Physical : $(cat /proc/cpuinfo | grep "physical id" | sort | uniq | wc -l)"
echo "  #vCPU : $(cat /proc/cpuinfo | grep "^processor" | wc -l)"
echo "  #Memory usage: $(free --mega | grep Mem | awk '{printf "%d/%dMb (%.2f%%)", $3, $2, ($3/$2*100)}')"
echo "  #Disk Usage: $(df | tail -n +2 | awk '{total+=$2} {inuse+=$3} END {printf "%d/%dGB (%d%%)", inuse/1000000, total/1000000, inuse/total*100}')"
echo "  #CPU Load: $(cat <(grep 'cpu ' /proc/stat) <(sleep 0.1 && grep 'cpu ' /proc/stat) | awk -v RS="" '{printf "%.1f%%", ($13-$2+$15-$4)*100/($13-$2+$15-$4+$16-$5)}')"
echo "  #Last boot: $(who  | awk '{print $3, $4}')"
echo "  #LVM use: $([ $(lsblk | grep lvm | wc -l) == 0 ] && echo "no" || echo "yes")" 
echo "  #Connexions TCP : $(ss -s | grep estab | awk '{printf "%d", $4}') ESTABLISHED"
echo "  #User log: $(users | wc -w)"
echo "  #Network: IP $(hostname -I)($(ip a | grep -m 1 ether | awk '{print $2}'))"
echo "  #Sudo: $(journalctl -q _COMM=sudo | grep COMMAND | wc -l) cmd"
