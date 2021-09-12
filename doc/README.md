PENGOLINCOIN Core
=============

Setup
---------------------
[PENGOLINCOIN Core](http://pengolincoin.xyz/wallet) is the original PENGOLINCOIN client and it builds the backbone of the network. However, it downloads and stores the entire history of PENGOLINCOIN transactions; depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more. Thankfully you only have to do this once.

Running
---------------------
The following are some helpful notes on how to run PENGOLINCOIN Core on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/pengolincoin-qt` (GUI) or
- `bin/pengolincoind` (headless)

If this is the first time running PENGOLINCOIN Core (since v5.0.0), you'll need to install the sapling params by running the included `install-params.sh` script, which copies the two params files to `$HOME/.pengolincoin-params`

### Windows

Unpack the files into a directory, and then run pengolincoin-qt.exe.

### macOS

Drag PENGOLINCOIN-Qt to your applications folder, and then run PENGOLINCOIN-Qt.

### Need Help?

* See the documentation at the [PENGOLINCOIN Wiki](https://github.com/PENGOLINCOIN-Project/PENGOLINCOIN/wiki)
for help and more information.
* Ask for help on [BitcoinTalk](https://bitcointalk.org/index.php?topic=1262920.0) or on the [PENGOLINCOIN Forum](http://forum.pengolincoin.xyz/).
* Join our Discord server [Discord Server](https://discord.pengolincoin.xyz)

Building
---------------------
The following are developer notes on how to build PENGOLINCOIN Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The PENGOLINCOIN repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://www.fuzzbawls.pw/pengolincoin/doxygen/)
- [Translation Process](translation_process.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Dnsseed Policy](dnsseed-policy.md)

### Resources
* Discuss on the [BitcoinTalk](https://bitcointalk.org/index.php?topic=1262920.0) or the [PENGOLINCOIN](http://forum.pengolincoin.xyz/) forum.
* Join the [PENGOLINCOIN Discord](https://discord.pengolincoin.xyz).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Memory](reduce-memory.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
