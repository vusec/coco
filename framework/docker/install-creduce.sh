ARCH=$(dpkg --print-architecture)
wget "https://download.vusec.net/vms/coco/creduce_2.11.0~20240312-1build1_${ARCH}.deb" -O "/creduce.deb"
dpkg -i "/creduce.deb"
rm "/creduce.deb"