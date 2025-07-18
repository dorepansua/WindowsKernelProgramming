#include <ntddk.h>

// prototypes
void PriorityBoosterUnload(_In_ PDRIVER_OBJECT DriverObject);
NTSTATUS PriorityBoosterCreateClose(_In_ PDEVICE_OBJECT DeviceObject,
                                    _In_ PIRP Irp);
NTSTATUS PriorityBoosterDeviceControl(_In_ PDEVICE_OBJECT DeviceObject,
                                      _In_ PIRP Irp);

// DriverEntry
extern "C" NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject,
                                _In_ PUNICODE_STRING RegistryPath) {
  DriverObject->DriverUnload = PriorityBoosterUnload;

  DriverObject->MajorFunction[IRP_MJ_CREATE] = PriorityBoosterCreateClose;
  DriverObject->MajorFunction[IRP_MJ_CLOSE] = PriorityBoosterCreateClose;
  DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] =
      PriorityBoosterDeviceControl;

  UNICODE_STRING devName = RTL_CONSTANT_STRING(L"\\Device\\PriorityBooster");
  // RtlInitUnicodeString(&devName, L"\\Device\\ThreadBoost");

  PDEVICE_OBJECT DeviceObject;

  UNICODE_STRING devName = RTL_CONSTANT_STRING(L"\\Device\\PriorityBooster");
  // RtlInitUnicodeString(&devName, L"\\Device\\ThreadBoost");
  PDEVICE_OBJECT DeviceObject;
  NTSTATUS status = IoCreateDevice(
      DriverObject, 0, &devName, FILE_DEVICE_UNKNOWN, 0, FALSE, &DeviceObject);
  if (!NT_SUCCESS(status)) {
    KdPrint(("Failed to create device (0x%08X)\n", status));
    return status;
  }

  UNICODE_STRING symLink = RTL_CONSTANT_STRING(L"\\??\\PriorityBooster");
  status = IoCreateSymbolicLink(&symLink, &devName);
  if (!NT_SUCCESS(status)) {
    KdPrint(("Failed to create symbolic link (0x%08X)\n", status));
    IoDeleteDevice(DeviceObject);
    return status;
  }

  KdPrint(("PriorityBooster DriverEntry completed successfully\n"));

  return STATUS_SUCCESS;
}

void PriorityBoosterUnload(_In_ PDRIVER_OBJECT DriverObject) {
  UNICODE_STRING symLink = RTL_CONSTANT_STRING(L"\\??\\PriorityBooster");
  // delete symbolic link
  IoDeleteSymbolicLink(&symLink);

  // delete device object
  IoDeleteDevice(DriverObject->DeviceObject);

  KdPrint(("PriorityBooster unloaded\n"));
}