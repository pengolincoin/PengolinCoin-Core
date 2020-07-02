
Debian
====================
This directory contains files used to package pengolincoind/pengolincoin-qt
for Debian-based Linux systems. If you compile pengolincoind/pengolincoin-qt yourself, there are some useful files here.

## pengolincoin: URI support ##


pengolincoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install pengolincoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your pengolincoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/pengolincoin128.png` to `/usr/share/pixmaps`

pengolincoin-qt.protocol (KDE)

