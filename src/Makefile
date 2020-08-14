build:./sys/symtable.asm ./boot/boot.asm
	nasm ./sys/symtable.asm -o ../build/symbol.bin
	nasm ./boot/boot.asm -o ../build/mbr.bin
	nasm ./sys/fat32fsinfo.asm -o ../build/fat32fsinfo.bin
	nasm ./sys/fat.asm -o ../build/fat.bin
	nasm ./sys/rootdir.asm -o ../build/rootdir.bin

	cat ../build/mbr.bin ../build/fat32fsinfo.bin > ../build/tmp2sec.bin

	dd if=/dev/zero of=../build/2sector.bin bs=512 count=2
	cat ../build/tmp2sec.bin ../build/symbol.bin ../build/2sector.bin > ../build/tmp6sec.bin

	dd if=/dev/zero of=../build/29sector.bin bs=512 count=30
	cat ../build/tmp6sec.bin ../build/29sector.bin > ../build/tmp35sec.bin

	dd if=/dev/zero of=../build/fat1full.bin bs=512 count=2042
	dd if=/dev/zero of=../build/fat2full.bin bs=512 count=2042
	dd if=../build/fat.bin of=../build/fat1full.bin conv=notrunc
	dd if=../build/fat.bin of=../build/fat2full.bin conv=notrunc

	cat ../build/tmp35sec.bin ../build/fat1full.bin ../build/fat2full.bin ../build/rootdir.bin > ../build/dsk.img

