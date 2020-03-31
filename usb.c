#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>

/* This program was written by Luigi Martinesi
 * It is licensed under the MIT license
 */

void getDeviceInfo(libusb_device * device, int device_number) {
	struct libusb_device_descriptor descriptor;
	libusb_get_device_descriptor(device, &descriptor);

	printf("Device %d:\n", device_number);
	printf("Vendor ID: %X\n", descriptor.idVendor);
	printf("Product ID: %X\n", descriptor.idProduct);
	printf("USB release number: %X\n", descriptor.bcdUSB);
	printf("USB-IF class code: %d\n", descriptor.bDeviceClass);
}

int main(int argc, char ** argv) {
	libusb_context * context;
	libusb_device ** list;
	libusb_device_handle * handle;
	libusb_init(&context);

	ssize_t device_list = libusb_get_device_list(context, &list);

	printf("Number of devices: %d\n", device_list);

	int i;
	for (i = 0; i < deviceList; i++) {
        puts("");
		getDeviceInfo(list[i], i);
	}

	printf("\n\nWhich device would you like to read from?  ");
	scanf("%d", &i);

	libusb_open(list[i], &handle);
	libusb_close(handle);

	libusb_exit(context);

	return 0;
}
