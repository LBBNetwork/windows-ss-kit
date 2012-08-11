/*++

Copyright (C) 2011-2012 The Little Beige Box, http://www.beige-box.com

File name:

    APILoop.c

Abstract:
 
    API loop functions for the SAMPLE
    subsystem.

Execution mode:

    Win32 User Mode

Revision History:

    @LBBNetwork - 15-Aug-2011 - Created.

--*/

#include "samplesrv.h"

SAMPLE_SERVER_DISPATCH SampleServerApiDispatch[4] = {
    SampleServer_Message1,
    SampleServer_Message4,
    SampleServer_Message8,
    SampleServer_Message16
};

NTSTATUS
SampleServer_APILoop(
    IN PVOID ThreadParameter
    )
/*++

Routine Name:
 
    SampleServer_APILoop
 
Description:
 
    Main loop child thread created by server initialization function.
 
Arguments:
 
    PVOID       - Typecasted thread parameter, real type is the connection
                  port (HANDLE).

Return Values:
 
    NTSTATUS    - STATUS_SUCCESS if successful.

--*/
{
    PSAMPLE_SERVER_MESSAGE_DISPATCH ApiReplyMessage;
    SAMPLE_SERVER_MESSAGE_DISPATCH ApiMessage;
    NTSTATUS Status;
    HANDLE ConnectionPort;
    HANDLE FunctionCommunicationPort;

    ConnectionPort = (HANDLE)ThreadParameter;

    ApiReplyMessage = NULL;

	DbgPrint("In API loop thread\n");
	
    for(;;) {

        //
        // Check if we're ready.
        //

        Status = NtReplyWaitReceivePort(ConnectionPort,
                                        NULL,
                                        (PPORT_MESSAGE)ApiReplyMessage,
                                        (PPORT_MESSAGE)&ApiMessage
                                        );

		
        if(!NT_SUCCESS(Status)) {
            
            ApiReplyMessage = NULL;
            continue;
            
        } else if(ApiMessage.PortMessage.u2.s2.Type == LPC_CONNECTION_REQUEST) {

            //
            // Connection requested, accept.
            //
			
            Status = NtAcceptConnectPort(&FunctionCommunicationPort,
                                         NULL,
                                         (PPORT_MESSAGE)&ApiMessage,
                                         TRUE,
                                         NULL,
                                         NULL
                                         );
            if(!NT_SUCCESS(Status)) {
                DbgPrint("NtAcceptConnectPort failed with status: 0x%08lx",
                         Status);
                NtTerminateProcess(NtCurrentProcess(),
                                   Status);
            }
            
            //
            // Complete the connection.
            //
            
            Status = NtCompleteConnectPort(FunctionCommunicationPort);
            
            if(!NT_SUCCESS(Status)) {
                DbgPrint("NtCompleteConnectPort failed with status: 0x%08lx",
                         Status);
                NtTerminateProcess(NtCurrentProcess(),
                                   Status);
            }
            
            ApiReplyMessage = NULL;
            
        } else if(ApiMessage.PortMessage.u2.s2.Type == LPC_PORT_CLOSED) {
            
            //
            // Port is closed.
            //
            
            ApiReplyMessage = NULL;
            
        } else {
            
            //
            // Dispatch the function.
            //
            
            Status = SampleServerApiDispatch[ApiMessage.Number](&ApiMessage);
            ApiMessage.Status = Status;
            ApiReplyMessage = &ApiMessage;
            
        }
        
    }
    
    //
    // Make the local C compiler less angry.
    //
    
    return STATUS_SUCCESS;
    
}
