/*++

Copyright (C) 2011-2012 The Little Beige Box, http://www.beige-box.com

File name:

    Server.C

Abstract:

    Main source file for SAMPLE subsystem server
    in the Windows Subsystem Server Kit

Execution mode:

    Win32 User Mode

Revision History:

    @LBBNetwork - 15-Aug-2011 - Created.

--*/

#include "samplesrv.h"

int
__cdecl
main(
     int argc,
     char* argv[],
     char* envp[]
     )
/*++
 
Routine Name:
 
    main
 
Description:
 
    Main entry function for the SAMPLE subsystem
    server for Windows NT.
 
Arguments:
 
    argc    - Argument Count
    argv    - Pointer to array of character variables
              which are the execution parameters.
    envp    - Pointer to array of character variables
              which are the current user's environment
              variables.

Return Type:
 
    int     - 0 if OK, anything else is bad.
 
--*/
{
    NTSTATUS Status;
    
    //
    // Start up the sample server.
    //
    
    DbgPrint("Starting sample server...\n");
	
    Status = SampleServer_Initialize();
    
    if(!NT_SUCCESS(Status)) { 
        DbgPrint("Server failed to initialize: Status: 0x%08lx\n", Status);
        NtTerminateProcess(NtCurrentProcess(),
                           Status);
    }
    
    return 0;
}
