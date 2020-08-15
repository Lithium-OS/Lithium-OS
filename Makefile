.PHONY:build
build:
	make fat -C ./src/sys/
	make sym -C ./src/sys/
	make bootloader -C ./src/boot/
	make all -C ./build/
clean:
	make clean -C ./build/


	