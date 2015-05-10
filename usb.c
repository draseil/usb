#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>

/* This program was written by Luigi Martinesi
 * It is licensed under the MIT license
 */

void lookup(char * type, uint16_t id) {
    char * command = malloc(sizeof(char) * 32);
    sprintf(command, "./search_%s %X", type, id);
    system(command);
}

void getDeviceInfo(libusb_device * device, int deviceNumber) {
	struct libusb_device_descriptor descriptor;
	libusb_get_device_descriptor(device, &descriptor);

	printf("Device %d:\n", deviceNumber);
	printf("Vendor ID: %X\n", descriptor.idVendor);
    lookup("vendor", descriptor.idVendor);
	printf("Product ID: %X\n", descriptor.idProduct);
    lookup("device", descriptor.idProduct);
	printf("USB release number: %X\n", descriptor.bcdUSB);
	printf("USB-IF class code: %d\n", descriptor.bDeviceClass);
}

int main(int argc, char ** argv) {
	libusb_context * context;
	libusb_device ** list;
	libusb_init(&context);

	ssize_t deviceList = libusb_get_device_list(context, &list);

	printf("Number of devices: %d\n", deviceList);

	int i;
	for (i = 0; i < deviceList; i++) {
        puts("");
		getDeviceInfo(list[i], i);
	}

	libusb_exit(context);

	return 0;
}
