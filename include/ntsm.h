/*++

Copyright (C) 2011-2012 The Little Beige Box, http://www.beige-box.com

File name:

    ntsm.h

Abstract:
 
    Defines types and functions used by the Windows Session Manager.

Execution mode:

    Not Applicable

Revision History:

    rms - 16-Aug-2011 - Created.

--*/

#ifndef _NT_SESSION_MANAGER_H
#define _NT_SESSION_MANAGER_H

//
// Session Manager functions.
//

NTSTATUS
SmConnectToSm(
    IN PUNICODE_STRING SbApiPortName,
    IN HANDLE SbApiPort,
    IN ULONG ImageType,
    OUT HANDLE SmApiPort
    );

//
// Session Manager data structures.
//

typedef PVOID PUSERPROFILE;

typedef struct _SBCREATESESSION {
    ULONG SessionId;
    RTL_USER_PROCESS_INFORMATION ProcessInformation;
    PUSERPROFILE UserProfile;
    ULONG DebugSession;
    CLIENT_ID DebugUiClientId;
} SBCREATESESSION, *PSBCREATESESSION;

typedef struct _SBTERMINATESESSION {
    ULONG SessionId;
    NTSTATUS TerminationStatus;
} SBTERMINATESESSION, *PSBTERMINATESESSION;

typedef struct _SBFOREIGNSESSIONCOMPLETE {
    ULONG SessionId;
    NTSTATUS TerminationStatus;
} SBFOREIGNSESSIONCOMPLETE, *PSBFOREIGNSESSIONCOMPLETE;

typedef enum _SBAPINUMBER {
    CreateSessionApi,
    TerminateSessionApi,
    ForeignSessionCompleteApi,
    MaxApiNumber
} SBAPINUMBER;

typedef struct _SBCONNECTINFO {
    ULONG SubsystemImageType;
    WCHAR EmulationSubSystemPortName[120];
} SBCONNECTINFO, *PSBCONNECTINFO;

typedef struct _SBAPIMSG {
    PORT_MESSAGE h;
    union {
        SBCONNECTINFO ConnectionRequest;
        struct {
            SBAPINUMBER ApiNumber;
            NTSTATUS ReturnedStatus;
            union {
                SBCREATESESSION CreateSession;
                SBTERMINATESESSION TerminateSession;
                SBFOREIGNSESSIONCOMPLETE ForeignSessionComplete;
            } u;
        };
    };
} SBAPIMSG, *PSBAPIMSG;

#endif _NT_SESSION_MANAGER_H