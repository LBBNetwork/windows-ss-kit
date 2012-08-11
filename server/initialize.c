/*++

Copyright (C) 2011-2012 The Little Beige Box, http://www.beige-box.com

File name:

    Initialize.C

Abstract:
 
    Initialization functions for the SAMPLE
    subsystem.

Execution mode:

    Win32 User Mode

Revision History:

    @LBBNetwork - 15-Aug-2011 - Created.

--*/

#include "samplesrv.h"
#include "ntsm.h"

HANDLE SampleSmPort;

NTSTATUS
SampleServer_Initialize(
    VOID
    )
/*++

Routine Name:

    SampleServer_Initialize

Description:

    Main initialization function for the SAMPLE
    subsystem.

Arguments:

    None

Return Type:

    NTSTATUS    - STATUS_SUCCESS if successful.

--*/
{
    NTSTATUS Status;
    UNICODE_STRING ObjectName, SbName;
    OBJECT_ATTRIBUTES ObjectAttributes, SbAttributes;
    HANDLE Handle, ConnectionPort;
    ULONG Identifier;
    
    //
    // Initialize the basic server handle name, and object attributes.
    //
    
    RtlInitUnicodeString(&ObjectName, L"\\SampleServer");
    InitializeObjectAttributes(&ObjectAttributes,
                               &ObjectName,
                               0,
                               NULL,
                               NULL
                               );
    
    //
    // Initialize the base connection port.
    //
    
    Status = NtCreatePort(&ConnectionPort,
                          &ObjectAttributes,
                          0,
                          sizeof(SAMPLE_SERVER_MESSAGE_DISPATCH),
                          sizeof(SAMPLE_SERVER_MESSAGE_DISPATCH) * 32
                          );
    
    DbgPrint("Status of NtCreatePort is 0x%08lx\n", Status);
	
    if(!NT_SUCCESS(Status)) {
        DbgPrint("NtConnectPort failed with status: 0x%08lx\n", Status);
        NtTerminateProcess(NtCurrentProcess(),
                           Status);
    }
    
    //
    // Handle some subsystem.
    //
    
    Status = SmConnectToSm(&ObjectName,
                           ConnectionPort,
                           7,
                           &SampleSmPort);
                           
    DbgPrint("Status of SmConnectToSm is: 0x%08lx\n", Status);
                           
    
    //
    // Create execution thread.
    //
    
    Handle = CreateThread(NULL,
                          0,
                          (LPTHREAD_START_ROUTINE)SampleServer_APILoop,
                          (PVOID)ConnectionPort,
                          0,
                          &Identifier);
    
    DbgPrint("Status of CreateThread is 0x%08ld\n", GetLastError());
    DbgPrint("ThreadID: %d\n", Identifier);
	
    if(!Handle) {
        DbgPrint("CreateThread failed with Win32 Status: 0x%08lx\n",
                 GetLastError());
        NtTerminateProcess(NtCurrentProcess(),
                           Status);
    }
    
    //
    // Create one more thread.
    //
    
    Handle = CreateThread(NULL,
                          0,
                          (LPTHREAD_START_ROUTINE)SampleServer_APILoop,
                          (PVOID)ConnectionPort,
                          0,
                          &Identifier);
	
    if(!Handle) {
        DbgPrint("CreateThread failed with Win32 Status: 0x%08lx\n",
                 GetLastError());
        NtTerminateProcess(NtCurrentProcess(),
                           Status);
    }
    
    DbgPrint("Status of CreateThread is 0x%08lx\n", GetLastError());
    DbgPrint("ThreadID: %d\n", Identifier);
	
    DbgPrint("Press any key to terminate server . . .\n");
    getchar();
    return Status;
}