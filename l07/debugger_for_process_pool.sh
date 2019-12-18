#!/bin/bash

mkfifo /tmp/roura
echo "The debug fifo is named /tmp/roura"

while true; do
	read pid < /tmp/roura
	watch -n 1 pstree -p $pid
done

rm /tmp/roura
