/*++

Module Name:

	GPIO.c - GPIO routines for the UC120 driver.

Abstract:

   This file contains GPIO helper functions.

Environment:

	Kernel-mode Driver Framework

--*/

#include "Driver.h"
#include <gpio.h>
#include "GPIO.tmh"

NTSTATUS GetGPIO(PDEVICE_CONTEXT ctx, WDFIOTARGET gpio, unsigned char* value)
{
	NTSTATUS status = STATUS_SUCCESS;
	WDF_MEMORY_DESCRIPTOR outputDescriptor;

	UNREFERENCED_PARAMETER(ctx);

	WDF_MEMORY_DESCRIPTOR_INIT_BUFFER(&outputDescriptor, value, 1);

	status = WdfIoTargetSendIoctlSynchronously(gpio, NULL, IOCTL_GPIO_READ_PINS, NULL, &outputDescriptor, NULL, NULL);

	return status;
}

NTSTATUS SetGPIO(PDEVICE_CONTEXT ctx, WDFIOTARGET gpio, unsigned char* value)
{
	NTSTATUS status = STATUS_SUCCESS;
	WDF_MEMORY_DESCRIPTOR inputDescriptor, outputDescriptor;

	UNREFERENCED_PARAMETER(ctx);

	WDF_MEMORY_DESCRIPTOR_INIT_BUFFER(&inputDescriptor, value, 1);
	WDF_MEMORY_DESCRIPTOR_INIT_BUFFER(&outputDescriptor, value, 1);

	status = WdfIoTargetSendIoctlSynchronously(gpio, NULL, IOCTL_GPIO_WRITE_PINS, &inputDescriptor, &outputDescriptor, NULL, NULL);

	return status;
}