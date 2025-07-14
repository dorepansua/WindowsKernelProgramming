#include <ntddk.h>

// prototypes
void PriorityBoosterUnload(_In_ PDRIVER_OBJECT DriverObject);

NTSTATUS PriorityBoosterCreateClose(_In_ PDEVICE_OBJECT DeviceObject,
                                    _In_ PIRP Irp);

// DriverEntry
extern "C" NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject,
                                _In_ PUNICODE_STRING RegistryPath) {
  DriverObject->DriverUnload = PriorityBoosterUnload;

  DriverObject->MajorFunction[IRP_MJ_CREATE] = PriorityBoosterCreateClose;
  DriverObject->MajorFunction[IRP_MJ_CLOSE] = PriorityBoosterCreateClose;
  DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] =
      PriorityBoosterDeviceControl;

  return STATUS_SUCCESS;
}
void PriorityBoosterUnload(_In_ PDRIVER_OBJECT DriverObject) {}