#!/bin/bash

pid=$$
ppid=$PPID

# to print the maximum processe your system can do at a time the line below does that
max_pid=$(cat /proc/sys/kernel/pid_max)

# printing them all to the terminal
echo "the PID: $pid";
echo "the PPID: $ppid";
echo "max_pid: $max_pid";

