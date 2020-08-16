all:
	dd if=/dev/zero of=./dsk.img bs=1M count=1024
	mkfs -t vfat ./dsk.img
	sudo mount ./dsk.img ./mnt/
	sudo cp ./loader.sys  ./mnt/
	sudo umount ./mnt/
	dd if=./mbr.bin of=./dsk.img bs=1 seek=106 conv=notrunc
clean:
	rm -f ./*.bin
	rm -f ./*.img
	rm -f ./*.sys
	rm -f ./*.o
	rm -f ./*.s

