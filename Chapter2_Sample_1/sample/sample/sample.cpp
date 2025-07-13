#include <ntddk.h>

#define DRIVER_TAG 'vDvH'

UNICODE_STRING g_RegistryPath;

void SampleUnload(_In_ PDRIVER_OBJECT DriverObject) {
  UNREFERENCED_PARAMETER(DriverObject);

  ExFreePool(g_RegistryPath.Buffer);
  KdPrint(("Sample driver Unload called\n"));
}
extern "C" NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject,
                                _In_ PUNICODE_STRING RegistryPath) {
  UNREFERENCED_PARAMETER(RegistryPath);
  DriverObject->DriverUnload = SampleUnload;

#pragma warning(push)
#pragma warning( \
    disable : 4996)  // disable deprecated warning for ExAllocatePoolWithTag

  g_RegistryPath.Buffer = (WCHAR*)ExAllocatePoolWithTag(
      PagedPool, RegistryPath->Length, DRIVER_TAG);

#pragma warning(pop)

  if (g_RegistryPath.Buffer == nullptr) {
    KdPrint(("Failed to allocate memory\n"));
    return STATUS_INSUFFICIENT_RESOURCES;
  }

  g_RegistryPath.MaximumLength = RegistryPath->Length;
  RtlCopyUnicodeString(&g_RegistryPath, (PCUNICODE_STRING)RegistryPath);
  // %wZ is for UNICODE_STRING objects
  KdPrint(("Copied registry path: %wZ\n", &g_RegistryPath));
  //...
  return STATUS_SUCCESS;
}