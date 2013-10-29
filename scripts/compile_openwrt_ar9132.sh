#/bin/bash


# install libs
apt-get update
apt-get install -y subversion build-essential subversion git-core libncurses5-dev zlib1g-dev gawk flex quilt libssl-dev xsltproc libxml-parser-perl unzip


# create OpenWrt toolchain
useradd -m openwrt
su openwrt

mkdir ~/openwrt
cd ~/openwrt

svn co svn://svn.openwrt.org/openwrt/trunk/
cd trunk

./scripts/feeds update -a
./scripts/feeds install -a

make defconfig

make -j$(cat /proc/cpuinfo | grep processor | wc -l)
#make prepare -j$(cat /proc/cpuinfo | grep processor | wc -l)


# build lyc
# export PATH=$PATH:/dev/shm/openwrt/trunk/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/bin
export STAGING_DIR=~/openwrt/trunk/staging_dir

# get source
wget https://raw.github.com/panticz/lyc/master/lyc.c -O lyc.c
wget https://raw.github.com/panticz/lyc/master/rxvx700.h -O rxvx700.h

#make CC=mips-openwrt-linux-uclibc-gcc LD=mips-openwrt-linux-uclibc-ld
~/openwrt/trunk/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/bin/mips-openwrt-linux-uclibc-gcc lyc.c -o lyc

# copy file to router
scp ./lyc root@openwrt:/root
