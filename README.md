# UART-driver
A Linux UART device driver for an emulated ARM Versatile PB board


Steps to build and compile the linux kernel
In linux-x.x folder, do the following
$ make ARCH=arm versatile_defconfig
$ make ARCH=arm menuconfig (Enable EABI support, )
$ make ARCH=arm CROSS_COMPILE=arm-none-eabi- all
This will start the building of the kernel using the ARM cross compiler; the build will create,
among
other binaries, a compressed kernel in a file called zImage located in “arch/arm/boot”
The driver code is compiled using the make file and we obtain a memory.ko module .
The driver module(memory.ko) and the test application(mem_test.o) is loaded onto
_install/home/ directory of the BusyBox.
From the _install directory
$ find . | cpio -o --format=newc > ../rootfs.img
$ cd ..
$ gzip -c rootfs.img > rootfs.img.gz
The cpio tool makes a list of files and outputs an archive; the newc format is the format of the
initramfs
file system that the Linux kernel recognizes.
The busybox install/home/your_name directory has the files mem_test and the kernel object
memory.ko. Now launch Linux under QEMU.
From the qemu-x.x directory launch qemu
$ ./arm-softmmu/qemu-system-arm -M versatilepb -m 128M -kernel
linux-3.14.31/arch/arm/boot/zImage
-initrd /path-to/rootfs.img.gz -append "root=/dev/ram rdinit=/sbin/init"
A shell is loaded and can be used normally, for example you can run ls command to
find the same directory structure as the Busybox _install directory .
In Linux, devices are accessed from user space in exactly the same way as files are accessed.
These device files are normally subdirectories of the /dev directory. To link normal files with a
kernel module two numbers are used: major number and minor number. The major number is the
one the kernel uses to link a file with its driver. The minor number is for internal use of the
device.
To access the device, a file (which will be used to access the device driver) must be created, by
typing the following command at the QEMU Linux prompt.
# mknod /dev/memory c 60 0
In the above, c means that a char device is to be created, 60 is the major number and 0 is the
minor number.
Now load the module,
 # insmod memory.ko
and unprotect the device with
# chmod 666 /dev/memory
Execute test to check all the file operations done from user land (see mem_test.c)
# test
