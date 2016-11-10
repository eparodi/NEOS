#!/bin/bash
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -device rtl8139,netdev=net0 -netdev tap,id=net0
#qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -device rtl8139
#qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -device rtl8139,netdev=net0,mac=DE:AD:BE:EF:12:34 -netdev tap,id=net0
#qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -net dump,file=netdump.wcap,device=rtl8139
