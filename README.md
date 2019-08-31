# strongswan-eap-5g-plugin
## Build with StrongSwan

### Download source

First download StrongSwan source code from official [site](https://www.strongswan.org/download.html).
Extract source code tarball to directory `strongswan/`

### Configure strongswan autoconf to compile plugin

`vim strongswan/configure.ac`

Around Line 200:
```c
ARG_ENABL_SET([eap-5g], [enable EAP 5G authentication module.])
```
Around Line 1480:
```c
ADD_PLUGIN([eap-5g], [c charon nm cmd])
``` 
Around Line 1650:
```c
AM_CONDITIONAL(USE_EAP_5G, test x$eap_5g = xtrue)
```
Around Line 1930:
```c
AM_CONDITIONAL(USE_EAP_5G, test x$eap_5g = xtrue)
```

### Build

```shell
cd strongswan/
git clone https://github.com/syujy/strongswan-eap-5g-plugin.git src/libcharon/plugin/eap_5g
autoreconf -i
./configure --prefix=/usr --sysconfdir=/etc --enable-eap-mschapv2 --enable-kernel-libipsec --enable-swanctl --enable-unity  --enable-vici --enable-xauth-eap --enable-xauth-noauth --enable-eap-identity --enable-md4 --enable-pem --enable-openssl --enable-pubkey --enable-farp --enable-eap-gtc --enable-eap-5g
make
sudo make install
```

### Configure the StrongSwan daemon

You can reference this [site](https://www.digitalocean.com/community/tutorials/how-to-set-up-an-ikev2-vpn-server-with-strongswan-on-ubuntu-18-04-2).
