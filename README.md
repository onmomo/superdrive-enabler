superdrive-enabler
==================

Hack for Apple's SuperDrive to work with other devices than OSX and MBA.

To unlock SuperDrive, compile superdriveEnabler.c

```
gcc -o superdriveEnabler superdriveEnabler.c
```

and execute it with the SuperDrive device path

```
./superdriveEnabler /dev/sr0
```

For a detailed usage and automation guide, check: http://techtalk.christian-moser.ch/wordpress/?p=517
