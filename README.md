# wp-linux
Whatsapp Webapp for Linux

## Install
```bash

```


## Alternative to Install: 
How to compile on my host device?

### Install requirements
```bash
gtk3-devel webkit2gtk4.1-devel pkgconf-pkg-config
```
### Compile 
```bash
gcc main.c -o whatsapp-native `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`
```
