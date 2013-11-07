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
wget -q https://github.com/panticz/lyc/archive/master.zip -O /tmp/master.zip
unzip -q /tmp/master.zip
cd lyc-master
make mips

# copy file to router
scp ./lyc root@openwrt:/root
