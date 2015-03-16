#include <stdio.h>
#include <libusb-1.0/libusb.h>

/* This program was written by Luigi Lorenzo Martinesi
 * If some asshole tries to steal it, I have given you the right to punch them in the face
 * This is licensed under CC 2.0
 */

void getDeviceInfo(libusb_device * device, int deviceNumber) {
	struct libusb_device_descriptor descriptor;
	libusb_get_device_descriptor(device, &descriptor);

	printf("Device %d:\n", deviceNumber);
	printf("Vendor ID: %X\n", descriptor.idVendor);
	printf("Product ID: %X\n", descriptor.idProduct);
	printf("USB release number: %X\n", descriptor.bcdUSB);
	printf("USB-IF class code: %d\n\n", descriptor.bDeviceClass);
}

int main(int argc, char ** argv) {
	/* ONLY WORKS WITH USB.H

	usb_init();									// initialise libusb

	int totalBusses = usb_find_busses();		// find and count all usb busses
	int totalDevices = usb_find_devices();		// find and count all usb devices
	struct usb_bus * bus = usb_get_busses();	// get a usb bus
	struct usb_device * device = bus->devices;

	printf("Number of busses: %d\nNumber of devices: %d\n", totalBusses, totalDevices);

	int i;
	for (bus = usb_get_busses(); bus; bus = bus->next) {
		printf("\nBus directory name: %s\n", bus->dirname);

		for (device = bus->devices; device; device = device->next) {
			printf("Device filename: %s\n", device->filename);
		}
	}*/

	libusb_context * context;
	libusb_device ** list;
	libusb_init(&context);

	ssize_t deviceList = libusb_get_device_list(context, &list);

	printf("Number of devices: %d\n\n", deviceList);

	int i;
	for (i = 0; i < deviceList; i++) {
		getDeviceInfo(list[i], i);
	}

	libusb_exit(context);

	return 0;
}
