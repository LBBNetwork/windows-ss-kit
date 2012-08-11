/*++

Copyright (C) 2011-2012 The Little Beige Box, http://www.beige-box.com

File name:

    smsup.c

Abstract:
 
    Defines functions used by the Windows Session Manager.

Execution mode:

    Win32 User Mode

Revision History:

    @LBBNetwork - 16-Aug-2011 - Created.

--*/

#include <ntddk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ntruntime.h"
#include "ntsm.h"

NTSTATUS
SmConnectToSm(
    IN PUNICODE_STRING SbApiPortName,
    IN HANDLE SbApiPort,
    IN ULONG ImageType,
    OUT HANDLE SmApiPort
    )
/*++

Routine Name:

    SmConnectToSm

Description:

    Connect to the Windows Session Manager.
    
Arguments:

    PUNICODE_STRING - Pointer to the value containing the connection
                      port name.
    HANDLE          - Handle to the client connection port.
    ULONG           - Supplies the image emulation type that the subsystem
                      serves.
    HANDLE          - Returned handle to the connection port which is connected
                      to the session manager.
    
Return Value:

    STATUS_SUCCESS if successful, otherwise anything else is bad.
    
--*/
{
    SECURITY_QUALITY_OF_SERVICE DynamicQos;
    SBAPIMSG SbMessage;
    PSBCONNECTINFO SbConnectInformation;
    UNICODE_STRING SbPortName;
    ULONG ConnectionLength;
    NTSTATUS Status;
    
    //
    // Set up the QoS parameters to use dynamic tracking.
    //
    
    DynamicQos.ImpersonationLevel = SecurityImpersonation;
    DynamicQos.ContextTrackingMode = SECURITY_DYNAMIC_TRACKING;
    DynamicQos.EffectiveOnly = TRUE;
    
    RtlInitUnicodeString(&SbPortName, L"\\SmApiPort");
    ConnectionLength = sizeof(SBCONNECTINFO);
    SbConnectInformation = &SbMessage.ConnectionRequest;
    
    if(SbApiPortName) {
    
        //
        // Check for valid parameters.
        //
    
        if(!SbApiPort) {
            return STATUS_UNSUCCESSFUL;
        }
        
        if(!ImageType) {
            return STATUS_UNSUCCESSFUL;
        }
        
        RtlMoveMemory(SbConnectInformation->EmulationSubSystemPortName,
                      SbApiPortName->Buffer,
                      SbApiPortName->Length
                      );
                      
        //
        // Finish up.
        //
        
        SbConnectInformation->EmulationSubSystemPortName[SbApiPortName->Length >> 1] = UNICODE_NULL;
        SbConnectInformation->SubsystemImageType = ImageType;
    
    } else {
        
        SbConnectInformation->EmulationSubSystemPortName[0] = UNICODE_NULL;
        SbConnectInformation->SubsystemImageType = 0;
    
    }
    
    Status = NtConnectPort(SmApiPort,
                           &SbPortName,
                           &DynamicQos,
                           NULL,
                           NULL,
                           NULL,
                           SbConnectInformation,
                           &ConnectionLength);
                           
    if(!NT_SUCCESS(Status)) {
        DbgPrint("SMLIB: NtConnectPort failed with status 0x%08lx\n", Status);
        return Status;
    }
    
    return STATUS_SUCCESS;
}