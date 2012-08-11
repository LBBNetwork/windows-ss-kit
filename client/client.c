/*++

Copyright (C) 2011-2012 The Little Beige Box, http://www.beige-box.com

File name:

    client.c

Abstract:
 
    Main source file for the client side of the
    SAMPLE subsystem.

Execution mode:

    Win32 User Mode

Revision History:

    @LBBNetwork - 15-Aug-2011 - Created.

--*/

#include "samplesrv.h"

#define ITERATIONS  25000

ULONG Longs[32];

//
// Define local types.
//

typedef struct _SAMPLE_PERFORMANCE_INFORMATION {
    ULONG StartTime;
    ULONG EndTime;
    PCHAR Title;
    ULONG Iterations;
} SAMPLE_PERFORMANCE_INFORMATION, *PSAMPLE_PERFORMANCE_INFORMATION;

VOID
SampleClient_BenchStart(
    IN PCHAR BenchmarkTitle,
    IN ULONG BenchmarkIterations,
    IN PSAMPLE_PERFORMANCE_INFORMATION PerformanceInformation
    )
/*++

Routine Name:
 
    SampleClient_BenchStart
 
Description:
 
    Capture benchmark state, and start time.
 
Arguments:
 
    PCHAR       - Benchmark title.
    ULONG       - Benchmark test iterations.
    PSAMPLE_PERFORMANCE_INFORMATION
                - Sample test performance information.

Return Values:
 
    None.

--*/
{

    //
    // Announce ourselves to the world.
    //
    
    printf("*** Test beginning: %s\n", BenchmarkTitle);
    
    PerformanceInformation->Title = BenchmarkTitle;
    PerformanceInformation->Iterations = BenchmarkIterations;
    PerformanceInformation->StartTime = GetTickCount();
    
    return;
}

VOID
SampleClient_BenchEnd(
    IN PSAMPLE_PERFORMANCE_INFORMATION PerformanceInformation
    )
/*++

Routine Name:
 
    SampleClient_BenchEnd
 
Description:
 
    Capture end benchmark state, and print results
 
Arguments:

    PSAMPLE_PERFORMANCE_INFORMATION
                - Sample test performance information.

Return Values:
 
    None.

--*/
{
    ULONG Duration, Performance;
    
    //
    // Test ended, print results.
    //
    
    PerformanceInformation->EndTime = GetTickCount();
    Duration = PerformanceInformation->EndTime - PerformanceInformation->StartTime;
    
    printf("\tTest time in milliseconds: %lu ms\n", Duration);
    printf("\tNumber of test iterations: %lu iterations\n",
           PerformanceInformation->Iterations);
           
    Performance = PerformanceInformation->Iterations * 1000 / Duration;
    
    printf("\tIterations performed per second: %lu iteration/s\n",
           Performance);
           
    printf("** End of test %s\n\n", PerformanceInformation->Title);
    
    return;
}

VOID
SampleClient_Test1(
    VOID
    )
/*++

Routine Name:
 
    SampleClient_Test1
 
Description:
 
    Perform API test 1.
 
Arguments:

    None.

Return Values:
 
    None.

--*/
{
    ULONG Index;
    SAMPLE_PERFORMANCE_INFORMATION PerformanceInformation;
    
    //
    // Start benchmark operation.
    //
    
    SampleClient_BenchStart("SampleAPI_Test1 Benchmark",
                            ITERATIONS,
                            &PerformanceInformation
                            );
                            
    //
    // Call the system service.
    //
    
    for (Index = 0; Index < ITERATIONS; Index++) {
        SampleClient_Api1(Longs[32]);
    }
    
    //
    // End of test.
    //
    
    SampleClient_BenchEnd(&PerformanceInformation);
    
    return;
}


VOID
SampleClient_Test4(
    VOID
    )
/*++

Routine Name:
 
    SampleClient_Test4
 
Description:
 
    Perform API test 4.
 
Arguments:

    None.

Return Values:
 
    None.

--*/
{
    ULONG Index;
    SAMPLE_PERFORMANCE_INFORMATION PerformanceInformation;
    
    //
    // Start benchmark operation.
    //
    
    SampleClient_BenchStart("SampleAPI_Test4 Benchmark",
                            ITERATIONS,
                            &PerformanceInformation
                            );
                            
    //
    // Call the system service.
    //
    
    for (Index = 0; Index < ITERATIONS; Index++) {
        SampleClient_Api4(&Longs[0]);
    }
    
    //
    // End of test.
    //
    
    SampleClient_BenchEnd(&PerformanceInformation);
    
    return;
}


VOID
SampleClient_Test8(
    VOID
    )
/*++

Routine Name:
 
    SampleClient_Test8
 
Description:
 
    Perform API test 8.
 
Arguments:

    None.

Return Values:
 
    None.

--*/
{
    ULONG Index;
    SAMPLE_PERFORMANCE_INFORMATION PerformanceInformation;
    
    //
    // Start benchmark operation.
    //
    
    SampleClient_BenchStart("SampleAPI_Test8 Benchmark",
                            ITERATIONS,
                            &PerformanceInformation
                            );
                            
    //
    // Call the system service.
    //
    
    for (Index = 0; Index < ITERATIONS; Index++) {
        SampleClient_Api8(&Longs[0]);
    }
    
    //
    // End of test.
    //
    
    SampleClient_BenchEnd(&PerformanceInformation);
    
    return;
}


VOID
SampleClient_Test16(
    VOID
    )
/*++

Routine Name:
 
    SampleClient_Test16
 
Description:
 
    Perform API test 16.
 
Arguments:

    None.

Return Values:
 
    None.

--*/
{
    ULONG Index;
    SAMPLE_PERFORMANCE_INFORMATION PerformanceInformation;
    
    //
    // Start benchmark operation.
    //
    
    SampleClient_BenchStart("SampleAPI_Test16 Benchmark",
                            ITERATIONS,
                            &PerformanceInformation
                            );
                            
    //
    // Call the system service.
    //
    
    for (Index = 0; Index < ITERATIONS; Index++) {
        SampleClient_Api16(&Longs[0]);
    }
    
    //
    // End of test.
    //
    
    SampleClient_BenchEnd(&PerformanceInformation);
    
    return;
}

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
    client for Windows NT.
 
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
    ULONG Index;
    
    //
    // Populate index.
    //
    
    for (Index = 0; Index < 32; Index++) {
        Longs[Index] = Index;
    }
    
    //
    // Connect to the server.
    //
    
    Status = SampleClient_Connect();
    if(!NT_SUCCESS(Status)) {
        printf("SampleClient_Connect failed with status: 0x%08lx", Status);
        ExitProcess(1);
    }
    
    printf("*** Connected to the server.\n");
    
    //
    // Test basic API.
    //
    
    Status = SampleClient_Api1(Longs[32]);
    if(!NT_SUCCESS(Status)) {
        printf("SampleClient_Api1 failed with status: 0x%08lx", Status);
        ExitProcess(1);
    }
    
    Status = SampleClient_Api4(&Longs[0]);
    if(!NT_SUCCESS(Status)) {
        printf("SampleClient_Api4 failed with status: 0x%08lx", Status);
        ExitProcess(1);
    }
    
    Status = SampleClient_Api8(&Longs[0]);
    if(!NT_SUCCESS(Status)) {
        printf("SampleClient_Api8 failed with status: 0x%08lx", Status);
        ExitProcess(1);
    }

    Status = SampleClient_Api16(&Longs[0]);
    if(!NT_SUCCESS(Status)) {
        printf("SampleClient_Api16 failed with status: 0x%08lx", Status);
        ExitProcess(1);
    }
    
    printf("*** Basic API tests completed\n");
    
    //
    // Benchmark API.
    //
    
    SampleClient_Test1();
    SampleClient_Test4();
    SampleClient_Test8();
    SampleClient_Test16();
    
    return Status;
}
