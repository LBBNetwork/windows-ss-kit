/*++

Copyright (C) 2011-2012 The Little Beige Box, http://www.beige-box.com

File name:

    SampleSrv.h

Abstract:
 
    Main header for the SAMPLE subsystem.

Execution mode:

    Win32 User Mode

Revision History:

    @LBBNetwork - 15-Aug-2011 - Created.

--*/

#ifndef _SAMPLE_SERVER_H
#define _SAMPLE_SERVER_H

#include <ntddk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ntruntime.h"

//
// Data structures.
//

typedef struct _SAMPLE_MESSAGE_1 {
    ULONG Long1;
} SAMPLE_MESSAGE_1, *PSAMPLE_MESSAGE_1;

typedef struct _SAMPLE_MESSAGE_4 {
    ULONG Longs[4];
} SAMPLE_MESSAGE_4, *PSAMPLE_MESSAGE_4;

typedef struct _SAMPLE_MESSAGE_8 {
    ULONG Longs[8];
} SAMPLE_MESSAGE_8, *PSAMPLE_MESSAGE_8;

typedef struct _SAMPLE_MESSAGE_16 {
    ULONG Longs[16];
} SAMPLE_MESSAGE_16, *PSAMPLE_MESSAGE_16;

typedef struct _SAMPLE_SERVER_MESSAGE_DISPATCH {
    PORT_MESSAGE PortMessage;
    ULONG Number;
    NTSTATUS Status;
    union {
        SAMPLE_MESSAGE_1 SampleServer_Message1;
        SAMPLE_MESSAGE_4 SampleServer_Message4;
        SAMPLE_MESSAGE_8 SampleServer_Message8;
        SAMPLE_MESSAGE_16 SampleServer_Message16;
    } u;
} SAMPLE_SERVER_MESSAGE_DISPATCH, *PSAMPLE_SERVER_MESSAGE_DISPATCH;

//
// Typedef'd functions pointer calls.
// 

typedef
NTSTATUS
(*SAMPLE_SERVER_DISPATCH)(
    IN PSAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch
    );

//
// Server functions.
//

NTSTATUS
SampleServer_APILoop(
    IN PVOID ThreadParameter
    );

NTSTATUS
SampleServer_Initialize(
    VOID
    );

//
// Client functions.
//

NTSTATUS
SampleClient_Api1(
    IN ULONG Long1
    );
    
NTSTATUS
SampleClient_Api4(
    IN ULONG Longs[4]
    );
    
NTSTATUS
SampleClient_Api8(
    IN ULONG Longs[8]
    );
    
NTSTATUS
SampleClient_Api16(
    IN ULONG Longs[16]
    );
    
NTSTATUS
SampleClient_Connect(
    VOID
    );

//
// API dispatch functions.
//

NTSTATUS
SampleServer_Message1(
    IN PSAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch
    );

NTSTATUS
SampleServer_Message4(
    IN PSAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch
    );

NTSTATUS
SampleServer_Message8(
    IN PSAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch
    );

NTSTATUS
SampleServer_Message16(
    IN PSAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch
    );

#define MAX_API 32
	
#endif // SAMPLE_SERVER_H
