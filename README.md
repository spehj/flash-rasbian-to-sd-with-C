# Flash Raspbian image to the SD card using C programming language
A short C program to copy raspbian image file to the sd card.

First make sure which drive is your SD card. In my case it was /dev/sda. You can use one of these commands:
```console
ls -l /dev/sda*
lsblk -p
sudo fdisk -l
/dev/sda
```

first compile main.c
```console
make
```

Before you try to copy .img file to SD card, make sure your SD card is formatted properly and has only one partition.

Run the compiled file as:
```console
./copy <path to your original file> <path to your SD card device file>
```

Example:
```console
./copy raspbian.img /dev/sda
```

Use sync command afterwards.
```console
sync
```

Process should take a while.
<br>

Some useful commands when working with Raspberry:

Get image from the RPi:

```console
scp pi@192.168.1.166:image.jpg /home/spehj/Desktop/
```

Copy main.c to the RPi:
```console
scp main.c pi@192.168.1.166:/home/pi
```


Compile a C file on the RPi using gcc:
```console
gcc main.c -Wall -o opt
```





