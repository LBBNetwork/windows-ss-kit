/*++
 
Copyright (C) 2011-2012 The Little Beige Box, http://www.beige-box.com

File name:

    APIs.C

Abstract:

    Test APIs for the SAMPLE subsystem server.

Execution mode:

    Win32 User Mode

Revision History:

    @LBBNetwork - 15-Aug-2011 - Created.

--*/

#include "samplesrv.h"

NTSTATUS
SampleServer_Message1(
    IN PSAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch
    )
/*++ 

Routine Name:
 
    SampleServer_Message1
 
Description:
 
    Message API with ULONG values in dispatch message.
    Test case.
 
Arguments:
 
    PSAMPLE_SERVER_MESSAGE_DISPATCH - Pointer to message dispatch
                                      structure.

Return Values:
 
    NTSTATUS    - STATUS_SUCCESS if successful.

--*/
{
    
    //
    // Stub function. Return SUCCESS to caller.
    //
    
    return STATUS_SUCCESS;
}

NTSTATUS
SampleServer_Message4(
    IN PSAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch
    )
/*++ 

Routine Name:
 
    SampleServer_Message4
 
Description:
 
    Message API with ULONG values in dispatch message.
    Test case.
 
Arguments:
 
    PSAMPLE_SERVER_MESSAGE_DISPATCH - Pointer to message dispatch
                                      structure.

Return Values:
 
    NTSTATUS    - STATUS_SUCCESS if successful.

--*/
{
    
    //
    // Stub function. Return SUCCESS to caller.
    //
    
    return STATUS_SUCCESS;
}

NTSTATUS
SampleServer_Message8(
    IN PSAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch
    )
/*++ 

Routine Name:
 
    SampleServer_Message8
 
Description:
 
    Message API with ULONG values in dispatch message.
    Test case.
 
Arguments:
 
    PSAMPLE_SERVER_MESSAGE_DISPATCH - Pointer to message dispatch
                                      structure.

Return Values:
 
    NTSTATUS    - STATUS_SUCCESS if successful.

--*/
{
    
    //
    // Stub function. Return SUCCESS to caller.
    //
    
    return STATUS_SUCCESS;
}

NTSTATUS
SampleServer_Message16(
    IN PSAMPLE_SERVER_MESSAGE_DISPATCH MessageDispatch
    )
/*++ 

Routine Name:
 
    SampleServer_Message16
 
Description:
 
    Message API with ULONG values in dispatch message.
    Test case.
 
Arguments:
 
    PSAMPLE_SERVER_MESSAGE_DISPATCH - Pointer to message dispatch
                                      structure.

Return Values:
 
    NTSTATUS    - STATUS_SUCCESS if successful.

--*/
{
    
    //
    // Stub function. Return SUCCESS to caller.
    //
    
    return STATUS_SUCCESS;
}
