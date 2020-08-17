
.PHONY:build
build:
	make bootloader -C ./src/boot/
	make all -C ./build/
	make dev -C ./src/device/
clean:
	make clean -C ./build/
run:
	qemu-system-i386 -hda ./build/dsk.img -m 1024M
debug:
	qemu-system-i386 -hda ./build/dsk.img -m 1024M -s -S

	