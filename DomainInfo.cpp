// DomainInfo.cpp : Defines the entry point for the console application.
//

//#include "targetver.h"

#include <stdio.h>
//#include <tchar.h>

#include <Windows.h>

#include <LM.h>

#pragma comment( lib, "Netapi32" )



int main()
{
    /*
	//
// Determines whether a workstation is joined to a domain or not
//
NET_API_STATUS
NET_API_FUNCTION
NetGetJoinInformation(
    _In_opt_ LPCWSTR             lpServer,
    _Outptr_ LPWSTR             *lpNameBuffer,
    _Out_ PNETSETUP_JOIN_STATUS  BufferType
    );
	*/

	wchar_t *lpszName		= NULL;		// Pointer to string which will hold domain or workgroup name
	NETSETUP_JOIN_STATUS	joinStatus;

	DWORD dwStatus = NetGetJoinInformation(NULL, &lpszName, &joinStatus);

	if (NERR_Success == dwStatus)
	{
		switch (joinStatus)
		{
		case	NetSetupUnjoined:
			wprintf(__TEXT("Machine is not joined to a workgroup or domain.\n"));
			break;

		case	NetSetupWorkgroupName:
			wprintf(__TEXT("Machine is associated with the workgroup \"%s\"\n"), lpszName);
			break;

		case	NetSetupDomainName:
			wprintf(__TEXT("Machine is associated with the domain \"%s\"\n"), lpszName);
			break;

		case	NetSetupUnknownStatus:
		default:
			wprintf(__TEXT("Call to NetGetJoinInformation succeeded, but could not determine the status.\n"));
		};
	}
	else
	{
		wprintf(__TEXT("Call to NetGetJoinInformation failed with error code %u"), dwStatus);
	}

	if (lpszName != NULL)
		NetApiBufferFree(lpszName);

	return dwStatus;
}

