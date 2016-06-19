#!/bin/bash
echo -n $'\xFF' > 0001-sampleDataModule.bin
echo -n $'\x00' >> 0001-sampleDataModule.bin
dd if=/dev/zero oflag=append conv=notrunc of=0001-sampleDataModule.bin bs=1c count=1
echo -n $'\xFF' >> 0001-sampleDataModule.bin 
