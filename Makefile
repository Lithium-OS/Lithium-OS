GCC_O_FLAGS = "-mcmodel=large -fno-builtin -m32 -c"
.PHONY:build
build:
	make fat -C ./src/sys/
	make sym -C ./src/sys/
	make bootloader -C ./src/boot/
	make all -C ./build/
	make dev -C ./src/device/
	make fat32 -C ./src/fs/fat32/
	make disk -C ./src/inc/disk/
clean:
	make clean -C ./build/


	