# Keyboards

This repository contains configurations of my keyboards.

## Setup

```
virtualenv env
source env/bin/activate
pip install qmkc
```

## Flashing
```
cd qmk_firmware
qmk compile -kb splitkb/kyria/rev2  -km pawka
qmk flash -kb splitkb/kyria/rev2  -km pawka
```
