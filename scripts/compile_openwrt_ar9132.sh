# installing required libraries 
apt-get install -y subversion build-essential subversion git-core libncurses5-dev zlib1g-dev gawk flex quilt libssl-dev xsltproc libxml-parser-perl unzip

# create user for compile process
useradd -m openwrt

# login as openwrt
su openwrt

# download OpenWrt
svn co svn://svn.openwrt.org/openwrt/trunk/
cd trunk
./scripts/feeds update -a
./scripts/feeds install -a

# configure OpenWRT
make defconfig

# compile OpenWRT
make -j$(cat /proc/cpuinfo | grep processor | wc -l)

# download lyc
wget -q https://github.com/panticz/lyc/archive/master.zip -O /tmp/master.zip
unzip -q /tmp/master.zip -d ~/trunk/staging_dir

# compile lyc
cd ~/trunk/staging_dir/lyc-master
make mips

# copy file to router
scp ./lyc root@openwrt:/root
