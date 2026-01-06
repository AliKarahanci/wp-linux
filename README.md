# wp-linux
Whatsapp Webapp for Linux

<img width="1006" height="733" alt="image" src="https://github.com/user-attachments/assets/f1b28d84-7bd9-477e-8589-25965af02b04" />


## Install
### Fedora/Nobara/Bazzite
```bash
sudo dnf install
```
### Ubuntu/Debian/Mint/ZorinOS
```bash
###
```
### Arch Linux/Manjaro/CachyOS/Garuda
```bash
wget https://github.com/AliKarahanci/wp-linux/releases/download/v0.1.0/PKGBUILD
makepkg -si

# or run:
# curl -L https://github.com/AliKarahanci/wp-linux/releases/download/v0.1.0/PKGBUILD -o PKGBUILD && makepkg -si
```
or
```bash
paru -S
```

### My distro not listed in here, what should i do?
- If your distro not listed in here, you must compile on your host device. 

## Alternative to Install: 
How to compile on my host device?

### Compile 
```bash
git clone https://github.com/AliKarahanci/wp-linux
cd wp-linux
cargo build --release
```
