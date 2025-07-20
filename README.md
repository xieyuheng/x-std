# My Standard Library

A [scalable c](https://github.com/booksbyus/scalable-c) inspired standard C library.

## Install

Compile:

```
git clone https://github.com/xieyuheng/x-std
cd x-std
make -j
make test
```

The compiled binary `./bin/app` is the command-line program.

## Development

```shell
make -j       # compile src/ files to lib/ and bin/
make run      # compile and run the command-line program
make test     # compile and run test
make clean    # clean up compiled files
```

Using [tsan (ThreadSanitizer)](https://github.com/google/sanitizers/wiki/threadsanitizercppmanual)
to test data race in parallel program:

```shell
make clean && TSAN=true make -j
```

## License

[GPLv3](LICENSE)
