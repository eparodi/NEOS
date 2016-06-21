#!/bin/bash
#581dbf
dd if=/dev/zero oflag=append conv=notrunc of=0001-sampleDataModule.bin bs=1c count=1
echo -n $'\x58' > 0001-sampleDataModule.bin
echo -n $'\x1D' >> 0001-sampleDataModule.bin
echo -n $'\xBF' >> 0001-sampleDataModule.bin
dd if=/dev/zero oflag=append conv=notrunc of=0001-sampleDataModule.bin bs=1c count=1

