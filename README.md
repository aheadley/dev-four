install:
$ make
# insmod four.ko
# mknod /dev/four c $(grep four /proc/devices | cut -f1) 0

enjoy your 4s
