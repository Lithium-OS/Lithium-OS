all:
	make cmp2sec
	make cmp6sec
	make cmp35sec
	make cmpfats
cmp2sec: ./mbr.bin ./fat32fsinfo.bin
	cat ./mbr.bin ./fat32fsinfo.bin > ./tmp2sec.bin
cmp6sec: ./tmp2sec.bin ./symbol.bin
	dd if=/dev/zero of=./2sector.bin bs=512 count=2
	cat ./tmp2sec.bin ./symbol.bin ./2sector.bin > ./tmp6sec.bin
cmp35sec: ./tmp6sec.bin 
	dd if=/dev/zero of=./30sector.bin bs=512 count=30
	cat ./tmp6sec.bin ./30sector.bin > ./tmp35sec.bin
cmpfats:./fat.bin ./tmp35sec.bin ./rootdir.bin
	dd if=/dev/zero of=./fat1full.bin bs=512 count=2042
	dd if=/dev/zero of=./fat2full.bin bs=512 count=2042
	dd if=./fat.bin of=./fat1full.bin conv=notrunc
	dd if=./fat.bin of=./fat2full.bin conv=notrunc
	cat ./tmp35sec.bin ./fat1full.bin ./fat2full.bin ./rootdir.bin > ./dsk.img
clean:
	rm -f ./*.bin
	rm -f ./*.img
