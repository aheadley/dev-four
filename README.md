install:
$ make
# insmod four.ko
# mknod /dev/four c $(grep four /proc/devices | awk '{print $1}') 0

enjoy your 4s
