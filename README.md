# Bitprim Blockchain

*Bitcoin blockchain library*

| **master(linux/osx)** | **conan-build-win(linux/osx)**   | **master(windows)**   | **conan-build-win(windows)** |
|:------:|:-:|:-:|:-:|
| [![Build Status](https://travis-ci.org/bitprim/bitprim-blockchain.svg)](https://travis-ci.org/bitprim/bitprim-blockchain)       | [![Build StatusB](https://travis-ci.org/bitprim/bitprim-blockchain.svg?branch=conan-build-win)](https://travis-ci.org/bitprim/bitprim-blockchain?branch=conan-build-win)  | [![Appveyor Status](https://ci.appveyor.com/api/projects/status/github/bitprim/bitprim-blockchain?svg=true)](https://ci.appveyor.com/project/bitprim/bitprim-blockchain)  | [![Appveyor StatusB](https://ci.appveyor.com/api/projects/status/github/bitprim/bitprim-blockchain?branch=conan-build-win&svg=true)](https://ci.appveyor.com/project/bitprim/bitprim-blockchain?branch=conan-build-win)  |

Make sure you have installed [bitprim-core](https://github.com/bitprim/bitprim-core), [bitprim-database](https://github.com/bitprim/bitprim-database) and [bitprim-consensus](https://github.com/bitprim/bitprim-consensus) (optional) beforehand according to their respective build instructions.

```
$ git clone https://github.com/bitprim/bitprim-blockchain.git
$ cd bitprim-blockchain
$ mkdir build
$ cd build
$ cmake .. -DWITH_TESTS=OFF -DWITH_TOOLS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-std=c++11"
$ make -j2 
$ sudo make install
```

bitprim-blockchain is now installed in `/usr/local/`.

## Configure Options

The default configuration requires `bitprim-consensus`. This ensures consensus parity with the Satoshi client. To eliminate the `bitprim-consensus` dependency use the `--without-consensus` option. This results in use of `bitprim-core` consensus checks.
