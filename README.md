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
<br>

##Some useful commands when working with Raspberry:
We can take a picture with the same program we've used for copying .img file to SD.

Copy main.c to the RPi:
```console
scp main.c pi@192.168.1.166:/home/pi
```

Compile a C file on the RPi using gcc:
```console
pi@raspberrypi:~$ gcc main.c -Wall -o opt
```

Take an image from video0 (RPi camera) and save it in home folder.
```console
pi@raspberrypi:~$  ./copy /dev/video0 image.jpg
```

Get image from the RPi to your PC. Run 

```console
scp pi@192.168.1.166:image.jpg /home/spehj/Desktop/
```










