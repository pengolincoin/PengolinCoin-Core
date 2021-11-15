PENGOLINCOIN Core version v3.0.0 is now available from: https://github.com/pengolincoin/PengolinCoin-Core/releases

This is an important release for stakers and Masternodes: including several tier two synchronization, GUI and build system bug fixes.
We recommend everyone to update your node/wallet.

Please report bugs using the issue tracker at github: https://github.com/pengolincoin/PengolinCoin-Core/issues

How to Upgrade
==============

If you are running an older version, shut it down. Wait until it has completely shut down, then run the installer (on Windows) or just copy over /Applications/PENGOLINCOIN-Qt (on Mac) or pengolincoind/pengolincoin-qt (on Linux).

Notable Changes
==============

### GUI

* Duplicate transaction records bug fixed.
* Not visible shield and/or cold staking contacts addresses list bug fixed

### Tier Two Network

* Not advancing (stalled) tier two synchronization bug fixed.
* Spork signer not persisting new spork value to DB bug fixed.

### Build system

* "dirty" release build version name bug fixed.

As well as everyone that helped translating on [Transifex](https://www.transifex.com/projects/p/pengolincoin-project-translations/), the QA team during Testing and the node hosts supporting our Testnet.
