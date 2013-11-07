STAGING_DIR=~/trunk/staging_dir/toolchain-mips_34kc_gcc-4.6-linaro_uClibc-0.9.33.2/bin
export STAGING_DIR

all:
	gcc $(FLAGS) $(INCLUDEDIR) lyc.c -o lyc

mips:
	$(STAGING_DIR)/mips-openwrt-linux-uclibc-gcc lyc.c -o lyc
        
clean:
	rm -f *~ *.o *.cgi lyc

