
.PHONY:build
build:
	make fat -C ./src/sys/
	make sym -C ./src/sys/
	make bootloader -C ./src/boot/
	make all -C ./build/
	make dev -C ./src/device/
clean:
	make clean -C ./build/


	