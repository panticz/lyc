all:
	gcc $(FLAGS) $(INCLUDEDIR) lyc.c -o lyc

mips:
	export STAGING_DIR=~/develop/OpenWRT/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/bin
	~/develop/OpenWRT/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/bin/mips-openwrt-linux-uclibc-gcc lyc.c -o lyc

clean:
	rm -f *~ *.o *.cgi

