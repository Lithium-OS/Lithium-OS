#!/bin/bash
[ uname -n == "Ubuntu" ] && sudo apt install qemu-system-i386 gcc g++ m4 bison make
[ uname -n == "CentOS" ] && sudo yum install qemu-system-i386 gcc g++ m4 bison make
read -p "Plesase input your device that are used by testing>" kdnode
read -p "Plesase input your device_root (not include parts)" kdnoder
echo "Warning:All data on this device will be erased"
read -p "Are you sure(y/n)?" -t 15 kp
[ kp == "n" ] && exit 0
mkfs.fat $knode
mkdir build
umount $kdnode && mount $kdnode ./build || mount $kdnode ./build
sudo grub-install $kdnoder --root-dir=./build -force
echo "menuentry \"Lithium-OS\" {\n\tinsmod part_msdos\n\tinsmod msdospart\n\tinsmod multiboot\n\tmultiboot2 \\lithium.elf\n}" > build/boot/grub/grub.cfg
echo "export LOS=" `pwd` >> ~/.bashrc
echo "export MKDEV=" $kdnode >> ~/.bashrc
echo "export MKDEVROOT=" $kdnoder >> ~/.bashrc
echo "OK,run a test now"
make run
 