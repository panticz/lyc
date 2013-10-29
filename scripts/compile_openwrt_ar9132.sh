#/bin/bash

sudo apt-get update
sudo apt-get install -y subversion build-essential subversion git-core libncurses5-dev zlib1g-dev gawk flex quilt libssl-dev xsltproc libxml-parser-perl unzip

su ubuntu -

mkdir /dev/shm/openwrt
cd /dev/shm/openwrt
svn co svn://svn.openwrt.org/openwrt/trunk/
cd trunk

./scripts/feeds update -a
./scripts/feeds install -a

make defconfig

make -j$(cat /proc/cpuinfo | grep processor | wc -l)
#make prepare -j$(cat /proc/cpuinfo | grep processor | wc -l)

# export PATH=$PATH:/dev/shm/openwrt/trunk/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/bin
export STAGING_DIR=/dev/shm/openwrt/trunk/staging_dir

# get source
wget https://raw.github.com/panticz/lyc/master/lyc.c -O lyc.c
wget https://raw.github.com/panticz/lyc/master/rxvx700.h -O rxvx700.h

#make CC=mips-openwrt-linux-uclibc-gcc LD=mips-openwrt-linux-uclibc-ld
/dev/shm/openwrt/trunk/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/bin/mips-openwrt-linux-uclibc-gcc lyc.c -o lyc

# copy file to router
scp ./lyc root@openwrt:/root
