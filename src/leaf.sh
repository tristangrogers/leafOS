RUN_T=$1

CPUS=1
MEM=512M

echo Running LeafOS on qemu-system-i386 with following params:
echo CPUS = $CPUS
echo MEM = $MEM

if $RUN_T == '-k'; then
	qemu-system-i386 -kernel leaf.bin -smp $CPUS -m $MEM
elif $RUN_T == '-i'; then
	qemu-system-i386 -cdrom leaf.iso -smp $CPUS -m $MEM
fi
