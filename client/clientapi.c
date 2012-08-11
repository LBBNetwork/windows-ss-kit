/*++
 
Copyright (C) 2011-2012 The Little Beige Box, http://www.beige-box.com
 
File name:

    ClientAPI.c
 
Abstract:
 
    Client API message dispatch functions.
 
Execution mode:
 
    Win32 User Mode

Revision History:
 
    @LBBNetwork - 15-Aug-2011 - Created.
 
--*/

#include "samplesrv.h"

HANDLE SampleClient_PortHandle;

NTSTATUS
SampleClient_Api1(
    IN ULONG Long1
    )
/*++

Routine Name:
 
    SampleClient_Api1
 
Description:
 
    Call server api for corresponding client API.
 
Arguments:
 
    ULONG       - Message passed to server.

Return Values:
 
    NTSTATUS    - STATUS_SUCCESS if successful.

--*/
{
    NTSTATUS Status;
    SAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch;
    PSAMPLE_MESSAGE_1 Arguments = &MessageDispatch.u.SampleServer_Message1;
    
    Arguments->Long1 = Long1;
    
    //
    // Fill out the message dispatch structure.
    //
    
    MessageDispatch.Number = 0;
    MessageDispatch.PortMessage.u1.s1.DataLength = sizeof(*Arguments) + 8;
    MessageDispatch.PortMessage.u1.s1.TotalLength = sizeof(MessageDispatch);
    MessageDispatch.PortMessage.u2.ZeroInit = 0;
    
    //
    // Connect and send the message.
    //
    
    Status = NtRequestWaitReplyPort(SampleClient_PortHandle,
                                    (PPORT_MESSAGE)&MessageDispatch,
                                    (PPORT_MESSAGE)&MessageDispatch
                                    );
                                    
    if(NT_SUCCESS(Status)) {
        Status = MessageDispatch.Status;
    } else {
        printf("Client1: NtRequestWaitReplyPort failed with status: 0x%08lx\n",
               Status);
        ExitProcess(1);
    }
    
    return Status;
    
}

NTSTATUS
SampleClient_Api4(
    IN ULONG Longs[4]
    )
/*++

Routine Name:
 
    SampleClient_Api4
 
Description:
 
    Call server api for corresponding client API.
 
Arguments:
 
    ULONG       - Message passed to server.

Return Values:
 
    NTSTATUS    - STATUS_SUCCESS if successful.

--*/
{
    NTSTATUS Status;
    SAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch;
    PSAMPLE_MESSAGE_4 Arguments = &MessageDispatch.u.SampleServer_Message4;
    
    RtlMoveMemory(&Arguments->Longs, Longs, 4 * 4);
    
    //
    // Fill out the message dispatch structure.
    //
    
    MessageDispatch.Number = 1;
    MessageDispatch.PortMessage.u1.s1.DataLength = sizeof(*Arguments) + 8;
    MessageDispatch.PortMessage.u1.s1.TotalLength = sizeof(MessageDispatch);
    MessageDispatch.PortMessage.u2.ZeroInit = 0;
    
    //
    // Connect and send the message.
    //
    
    Status = NtRequestWaitReplyPort(SampleClient_PortHandle,
                                    (PPORT_MESSAGE)&MessageDispatch,
                                    (PPORT_MESSAGE)&MessageDispatch
                                    );
                                    
    if(NT_SUCCESS(Status)) {
        Status = MessageDispatch.Status;
    } else {
        printf("Client4: NtRequestWaitReplyPort failed with status: 0x%08lx\n",
               Status);
        ExitProcess(1);
    }
    
    return Status;
    
}

NTSTATUS
SampleClient_Api8(
    IN ULONG Longs[8]
    )
/*++

Routine Name:
 
    SampleClient_Api8
 
Description:
 
    Call server api for corresponding client API.
 
Arguments:
 
    ULONG       - Message passed to server.

Return Values:
 
    NTSTATUS    - STATUS_SUCCESS if successful.

--*/
{
    NTSTATUS Status;
    SAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch;
    PSAMPLE_MESSAGE_8 Arguments = &MessageDispatch.u.SampleServer_Message8;
    
    RtlMoveMemory(&Arguments->Longs, Longs, 8 * 4);
    
    //
    // Fill out the message dispatch structure.
    //
    
    MessageDispatch.Number = 2;
    MessageDispatch.PortMessage.u1.s1.DataLength = sizeof(*Arguments) + 8;
    MessageDispatch.PortMessage.u1.s1.TotalLength = sizeof(MessageDispatch);
    MessageDispatch.PortMessage.u2.ZeroInit = 0;
    
    //
    // Connect and send the message.
    //
    
    Status = NtRequestWaitReplyPort(SampleClient_PortHandle,
                                    (PPORT_MESSAGE)&MessageDispatch,
                                    (PPORT_MESSAGE)&MessageDispatch
                                    );
                                    
    if(NT_SUCCESS(Status)) {
        Status = MessageDispatch.Status;
    } else {
        printf("Client8: NtRequestWaitReplyPort failed with status: 0x%08lx\n",
               Status);
        ExitProcess(1);
    }
    
    return Status;
    
}

NTSTATUS
SampleClient_Api16(
    IN ULONG Longs[16]
    )
/*++

Routine Name:
 
    SampleClient_Api4
 
Description:
 
    Call server api for corresponding client API.
 
Arguments:
 
    ULONG       - Message passed to server.

Return Values:
 
    NTSTATUS    - STATUS_SUCCESS if successful.

--*/
{
    NTSTATUS Status;
    SAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch;
    PSAMPLE_MESSAGE_16 Arguments = &MessageDispatch.u.SampleServer_Message16;
    
    RtlMoveMemory(&Arguments->Longs, Longs, 16 * 4);
    
    //
    // Fill out the message dispatch structure.
    //
    
    MessageDispatch.Number = 3;
    MessageDispatch.PortMessage.u1.s1.DataLength = sizeof(*Arguments) + 8;
    MessageDispatch.PortMessage.u1.s1.TotalLength = sizeof(MessageDispatch);
    MessageDispatch.PortMessage.u2.ZeroInit = 0;
    
    //
    // Connect and send the message.
    //
    
    Status = NtRequestWaitReplyPort(SampleClient_PortHandle,
                                    (PPORT_MESSAGE)&MessageDispatch,
                                    (PPORT_MESSAGE)&MessageDispatch
                                    );
                                    
    if(NT_SUCCESS(Status)) {
        Status = MessageDispatch.Status;
    } else {
        printf("Client16: NtRequestWaitReplyPort failed with status: 0x%08lx\n",
               Status);
        ExitProcess(1);
    }
    
    return Status;
    
}

NTSTATUS
SampleClient_Connect(
    VOID
    )
/*++

Routine Name:
 
    SampleClient_Connect
 
Description:
 
    Client function for connecting to server
 
Arguments:
 
    None.

Return Values:
 
    NTSTATUS    - STATUS_SUCCESS if successful.

--*/
{
    NTSTATUS Status;
    UNICODE_STRING PortName;
    SECURITY_QUALITY_OF_SERVICE DynamicQos;

    //
    // Set up the QoS parameters to use dynamic tracking.
    //
    
    DynamicQos.ImpersonationLevel = SecurityImpersonation;
    DynamicQos.ContextTrackingMode = SECURITY_DYNAMIC_TRACKING;
    DynamicQos.EffectiveOnly = TRUE;
    
    //
    // Connect to the server port.
    //
    
    RtlInitUnicodeString(&PortName, L"\\SampleServer");

    Status = NtConnectPort(&SampleClient_PortHandle,
                           &PortName,
                           &DynamicQos,
                           NULL,
                           NULL,
                           NULL,
                           NULL,
                           0
                           );
                           
    if(!NT_SUCCESS(Status)) {
        printf("Client: NtConnectPort failed with status: 0x%08lx\n", Status);
        return Status;
    }

    return Status;
}
