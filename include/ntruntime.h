/*++

Copyright (C) 2011-2012 The Little Beige Box, http://www.beige-box.com

File name:

    ntruntime.h

Abstract:
 
    Missing NT definitions from windows.h

Execution mode:

    Not applicable.

Revision History:

    @LBBNetwork - 15-Aug-2011 - Created.

--*/

#ifndef _NT_RUNTIME_H
#define _NT_RUNTIME_H

typedef short CSHORT;

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS 0x0
#endif

#ifndef STATUS_UNSUCCESSFUL
#define STATUS_UNSUCCESSFUL 0xC0000001
#endif

#define LPC_CLIENT_ID CLIENT_ID
#define LPC_SIZE_T SIZE_T
#define LPC_PVOID PVOID
#define LPC_HANDLE HANDLE

//
// LPC Message Types
//
typedef enum _LPC_TYPE
{
    LPC_NEW_MESSAGE,
    LPC_REQUEST,
    LPC_REPLY,
    LPC_DATAGRAM,
    LPC_LOST_REPLY,
    LPC_PORT_CLOSED,
    LPC_CLIENT_DIED,
    LPC_EXCEPTION,
    LPC_DEBUG_EVENT,
    LPC_ERROR_EVENT,
    LPC_CONNECTION_REQUEST,
    LPC_CONNECTION_REFUSED,
    LPC_MAXIMUM
} LPC_TYPE;


//
// LPC Port Message
//
typedef struct _PORT_MESSAGE
{
    union
    {
        struct
        {
            CSHORT DataLength;
            CSHORT TotalLength;
        } s1;
        ULONG Length;
    } u1;
    union
    {
        struct
        {
            CSHORT Type;
            CSHORT DataInfoOffset;
        } s2;
        ULONG ZeroInit;
    } u2;
    union
    {
        LPC_CLIENT_ID ClientId;
        double DoNotUseThisField;
    };
    ULONG MessageId;
    union
    {
        LPC_SIZE_T ClientViewSize;
        ULONG CallbackId;
    };
} PORT_MESSAGE, *PPORT_MESSAGE;


//
// Local and Remove Port Views
//
typedef struct _PORT_VIEW
{
    ULONG Length;
    LPC_HANDLE SectionHandle;
    ULONG SectionOffset;
    LPC_SIZE_T ViewSize;
    LPC_PVOID ViewBase;
    LPC_PVOID ViewRemoteBase;
} PORT_VIEW, *PPORT_VIEW;

typedef struct _REMOTE_PORT_VIEW
{
    ULONG Length;
    LPC_SIZE_T ViewSize;
    LPC_PVOID ViewBase;
} REMOTE_PORT_VIEW, *PREMOTE_PORT_VIEW;

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

#ifndef InitializeObjectAttributes
#define InitializeObjectAttributes( p, n, a, r, s ) {   \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
    (p)->RootDirectory = r;                             \
    (p)->Attributes = a;                                \
    (p)->ObjectName = n;                                \
    (p)->SecurityDescriptor = s;                        \
    (p)->SecurityQualityOfService = NULL;               \
    }
#endif

typedef struct _CURDIR
{
    UNICODE_STRING DosPath;
    HANDLE Handle;
} CURDIR, *PCURDIR;

typedef struct RTL_DRIVE_LETTER_CURDIR
{
    USHORT Flags;
    USHORT Length;
    ULONG TimeStamp;
    UNICODE_STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _SECTION_IMAGE_INFORMATION
{
    PVOID TransferAddress;
    ULONG ZeroBits;
    ULONG MaximumStackSize;
    ULONG CommittedStackSize;
    ULONG SubsystemType;
    USHORT SubSystemMinorVersion;
    USHORT SubSystemMajorVersion;
    ULONG GpValue;
    USHORT ImageCharacteristics;
    USHORT DllChracteristics;
    USHORT Machine;
    UCHAR ImageContainsCode;
    UCHAR Spare1;
    ULONG LoaderFlags;
    ULONG ImageFileSIze;
    ULONG Reserved[1];
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

//
// Structures for RtlCreateUserProcess
//
typedef struct _RTL_USER_PROCESS_PARAMETERS
{
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    HANDLE ConsoleHandle;
    ULONG ConsoleFlags;
    HANDLE StandardInput;
    HANDLE StandardOutput;
    HANDLE StandardError;
    CURDIR CurrentDirectory;
    UNICODE_STRING DllPath;
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
    PWSTR Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING WindowTitle;
    UNICODE_STRING DesktopInfo;
    UNICODE_STRING ShellInfo;
    UNICODE_STRING RuntimeData;
    RTL_DRIVE_LETTER_CURDIR CurrentDirectories[32];
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _RTL_USER_PROCESS_INFORMATION
{
    ULONG Size;
    HANDLE ProcessHandle;
    HANDLE ThreadHandle;
    CLIENT_ID ClientId;
    SECTION_IMAGE_INFORMATION ImageInformation;
} RTL_USER_PROCESS_INFORMATION, *PRTL_USER_PROCESS_INFORMATION;

//
// LPC functions
//

NTSTATUS
NTAPI
NtRequestWaitReplyPort(
    IN HANDLE PortHandle,
    OUT PPORT_MESSAGE LpcReply,
    IN PPORT_MESSAGE LpcRequest
    );

NTSTATUS
NTAPI
NtConnectPort(
    PHANDLE PortHandle,
    PUNICODE_STRING PortName,
    PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    PPORT_VIEW ClientView OPTIONAL,
    PREMOTE_PORT_VIEW ServerView OPTIONAL,
    PULONG MaxMessageLength OPTIONAL,
    PVOID ConnectionInformation OPTIONAL,
    PULONG ConnectionInformationLength OPTIONAL
    );

NTSTATUS
NTAPI
NtCreatePort(
    PHANDLE PortHandle,
    POBJECT_ATTRIBUTES ObjectAttributes,
    ULONG MaxConnectionInfoLength,
    ULONG MaxMessageLength,
    ULONG MaxPoolUsage
    );
	
NTSTATUS
NTAPI
NtRequestWaitReplyPort(
    IN HANDLE PortHandle,
    OUT PPORT_MESSAGE LpcReply,
    IN PPORT_MESSAGE LpcRequest
    );

NTSTATUS
NTAPI
NtReplyWaitReceivePort(
    IN HANDLE PortHandle,
    OUT PVOID *PortContext OPTIONAL,
    IN PPORT_MESSAGE ReplyMessage OPTIONAL,
    OUT PPORT_MESSAGE ReceiveMessage
    );	

NTSTATUS
NTAPI
NtCompleteConnectPort(
    HANDLE PortHandle
    );
	
NTSTATUS
NTAPI
NtAcceptConnectPort(
    PHANDLE PortHandle,
    PVOID PortContext OPTIONAL,
    PPORT_MESSAGE ConnectionRequest,
    BOOLEAN AcceptConnection,
    PPORT_VIEW ServerView OPTIONAL,
    PREMOTE_PORT_VIEW ClientView OPTIONAL
    );

//
// Generic functions.
//
	
ULONG
NTAPI
DbgPrint(
	PCHAR Format,
	...
	);
	
VOID
NTAPI
ExitProcess(
	ULONG ExitCode
	);
	
ULONG
NTAPI
GetTickCount(
	VOID
	);
	
typedef struct _SECURITY_ATTRIBUTES {
    ULONG  nLength;
    PVOID lpSecurityDescriptor;
    BOOLEAN bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef
ULONG
(*LPTHREAD_START_ROUTINE)(
	PVOID ThreadParameter
	);

HANDLE
NTAPI
CreateThread(
	PSECURITY_ATTRIBUTES ThreadAttributes,
	SIZE_T StackSize,
	LPTHREAD_START_ROUTINE StartRoutine,
	PVOID Parameter,
	ULONG CreationFlags,
	PULONG ThreadId
	);
	
ULONG
NTAPI
GetLastError(
	VOID
	);
	
ULONG
NTAPI
ResumeThread(
	HANDLE ThreadHandle
	);
	
#define DbgPrint printf("(%s:%d) ", __FUNCTION__, __LINE__), printf

//
// Ps functions
//

#ifndef NtCurrentProcess
#define NtCurrentProcess()                      ((HANDLE)(LONG_PTR)-1)
#endif

NTSTATUS
NTAPI
NtTerminateProcess(
    IN HANDLE ProcessHandle,
    IN NTSTATUS ExitStatus
    );
	


#endif // _NT_RUNTIME_H
