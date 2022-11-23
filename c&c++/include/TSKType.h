//////////////////////////////////////////////////////////////////////////////
//Filename: TSKType.h
//Description: W3FS Native SDK Library Type Description
//Author: ecore
//Reference: 
/////////////////////////////////////////////////////////////////////////////
#ifndef _TSK_TYPE_H
#define _TSK_TYPE_H

#include "TSKDefine.h"

/////////////////////////////////////////////
//Included base header files
/////////////////////////////////////////////
#ifdef _WIN32
#ifdef __APPLICATION
#include <windows.h>
#endif
#ifdef __KERNEL
#include <fltKernel.h>
#include <suppress.h>
#include <strsafe.h>
#include <dontuse.h>
#endif
#else
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#endif

/////////////////////////////////////////////
//Defining the base type
/////////////////////////////////////////////
#ifdef _WIN32
typedef char CHAR,*PCHAR;
typedef wchar_t WCHAR,*PWCHAR;
typedef unsigned char BYTE,*PBYTE;
typedef unsigned char BOOLEAN,*PBOOLEAN;
typedef short INT16;
typedef unsigned short UINT16;
typedef int INT32;
typedef unsigned int UINT32;
typedef __int64 INT64;
typedef unsigned __int64 UINT64;
typedef UINT64 QWORD,*PQWORD;
typedef void * PVOID;
#ifdef __KERNEL
typedef unsigned short WORD;
typedef unsigned long DWORD;
#endif
#else
typedef char CHAR, *PCHAR;
typedef wchar_t WCHAR, *PWCHAR;
typedef unsigned char BYTE, *PBYTE;
typedef unsigned char BOOLEAN, *PBOOLEAN;
typedef short INT16;
typedef unsigned short UINT16;
typedef int INT32;
typedef unsigned int UINT32;
typedef int64_t INT64;
typedef uint64_t UINT64;
typedef uint64_t QWORD, *PQWORD;
typedef void * PVOID;
typedef unsigned int  DWORD;
#endif


/////////////////////////////////////////////
//Defining the extension type
/////////////////////////////////////////////
// Define 32-bit and 64-bit compatible pointer types; on 32-bit platforms, 32-bit pointers are extended to 64-bit versions of this type;
typedef UINT64 InfoPointer;
// Define JIT Message ID
typedef InfoPointer JIT_ID;
// Define the storage point ID
typedef INT32 Storage_ID;
// Define the Process ID
typedef UINT32 PROC_ID;
// Define the Thread ID
typedef UINT32 THRD_ID;
//Declaring identity objects
typedef void * IdentityObject;


/////////////////////////////////////////////
//Define base constants
/////////////////////////////////////////////
//True or false representation of type BOOLEAN
#define FALSE 0
#define TRUE  1
//Invalid handle
#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE ((HANDLE)-1)
#endif
//Define the maximum character length of various names; including user name, vendor name, algorithm name, etc;
#define MAX_NAME_LEN 32
//Defines the maximum character length of the template used in the control model
#define MAX_PATH_LEN 512


/////////////////////////////////////////////
//Define algorithm-related
/////////////////////////////////////////////
/////////////////////////////////////////////
//Constants related to asymmetric encryption algorithms
//Maximum length of asymmetric algorithm cipher text
#define IDENTITY_MAX_CIPHER_LENGTH 154
//Maximum length of symmetric algorithm plaintexts:
#define IDENTITY_MAX_PLAIN_LENGTH 64
//The ecc encryption algorithm encrypts the maximum supported original data length at a time
#define ECC_MAX_PLAIN_LENGTH  64
//The ecc encryption algorithm supports the maximum length of encrypted data in one encryption.
#define ECC_MAX_CIPHER_LENGTH 154
/////////////////////////////////////////////
//Digest algorithm-related constants
//Result length of MD5 digest algorithm
#define DIGEST_MD5_LENGTH    16
//Result length of sha256 digest algorithm
#define DIGEST_SHA256_LENGTH  32
/////////////////////////////////////////////
//Key type handling options
#define IDENTITY_NULL_KEY           0
#define IDENTITY_PUBLIC_KEY     1  //public key
#define IDENTITY_PRIVATE_KEY    2  //private key
#define IDENTITY_KEY_ID   3  //identity id
/////////////////////////////////////////////
//Constants related to symmetric  encryption algorithms
//The length of the encryption algorithm tag 
#define CIPHER_TAG_LENGTH    16
//Action with the symmetric algorithm
#define ACTION_ENCRYPT       1
#define ACTION_DECRYPT       2


////////////////////////////////////////////////////////////
//Define identity ID related
////////////////////////////////////////////////////////////
//the identity ID length
#define IDENTITYID_LENGTH 20
//the identity ID
typedef BYTE IDENTITY_ID[IDENTITYID_LENGTH];
//Declare a null identity ID
extern IDENTITY_ID IDENTITY_NULL;
//clear identity ID
#define ClearIdentityID(id) (memset(id,0,IDENTITYID_LENGTH))
//copy identity ID
#define CopyIdentityID(idDst,idSrc) (memcpy(idDst,idSrc,IDENTITYID_LENGTH))
//compare identity ID
#define CmpIdentityID(id1,id2) (memcmp(id1,id2,IDENTITYID_LENGTH))


/////////////////////////////////////////////
//JIT related
/////////////////////////////////////////////
//Invalid JIT
#define JIT_NULL     ((JIT_ID)0)


//////////////////////////////////////////////////////////////
//Define all macro definitions needed for file operations
//////////////////////////////////////////////////////////////
//Definition of file types for W3FS protocol:
//////////////////////////////////////////////////////////////
//Encrypt File
#define TYPE_FILE_CRYPT 0
//Non-encrypted File
#define TYPE_FILE_NORMAL 1
//Unknow File
#define TYPE_FILE_UNKNOWN 2
//Directory encryption profile
#define TYPE_FILE_DEC 3
//Can not Server File
#define TYPE_FILE_CANT_SERVE 4

//Encrypt Folder
#define TYPE_DIR_CRYPT 100
//Non-encrypt Folder
#define TYPE_DIR_NORMAL 101
//Unknow Folder
#define TYPE_DIR_UNKNOWN 102
//Can not Server Folder
#define TYPE_DIR_CANT_SERVE 103
//Define temporary file suffixes
#ifdef _WIN32
#define TSKSERVICE_TEMP_FILE L".tsk.tmp"
#else
#define TSKSERVICE_TEMP_FILE ".tsk.tmp"
#endif
//////////////////////////////////////////////////////////////////////////
//File operation results
#define FILEOP_RESULT_NOERROR  0    //Success
#define FILEOP_RESULT_IGNORE   -1   //Ignore，For example, when encrypting a file, the file itself is encrypted, when decrypting a file, the file itself is non-encrypted, and when distributing a file, the target file is not encrypted.
#define FILEOP_RESULT_FILECANTSERVER  -2  //Failed,the file could not be served
#define FILEOP_RESULT_TSKFAILED  -3    //Failed,Create PTefsInfoRef object failed
#define FILEOP_RESULT_PERMISSIONFAILED  -4  //Failed, Permission Denied
#define FILEOP_RESULT_VERSIONFAILED  -5  //Failed,Version Error
#define FILEOP_RESULT_DATAFAILED  -6  //Failed,Data validation error
////////////////////////////////////////////////////////////////////
//Define the file operation task type
#define FILEOPTASK_NULL   0  //Invalid operation
#define FILEOPTASK_ENCRYPT  1//Ecnrypt
#define FILEOPTASK_DECRYPT  2//Decrypt
#define FILEOPTASK_SHARE  3//Share
//////////////////////////////////////////////////////////////////////
//Define the file operation task status
#define FILEOPTASK_STATE_WAITING  0  //to be started
#define FILEOPTASK_STATE_PREDICT  1  //progress estimation phase
#define FILEOPTASK_STATE_PROGRESS  2  //in progress
#define FILEOPTASK_STATE_SUCCESS   3  //successfully completed
#define FILEOPTASK_STATE_CANCLE    4  //failed because the user cancelled 


/////////////////////////////////////////////
//Define event-related constants
/////////////////////////////////////////////
//--------------------------------------
//---The broad event categories range from[0,31]---
//--------------------------------------
#define EVENTCLASS_MIN                        0
#define EVENTCLASS_MAX                        31
#define EVENTCLASS_COUNT                      32
//--------------------------------------
//---3 main types of events predefined by the W3FS Native SDK library---
//--------------------------------------
//The Ack event category is reserved by the system and is not available for synchronization of event responses.
#define EVENTCLASS_ACK                        0
//Log event category is the log event category, in which you can cast various logs
#define EVENTCLASS_LOG                        1
//The DS Events category is a common class used by all versions of DS and can be used to deliver various events.
#define EVENTCLASS_DS                         2
//--------------------------------------
//---Event Feature---
//Usually, there is no need to specify any Feature;
//--------------------------------------
//Broadcast Events
#define EVENTFLAG_Broadcast                   0x1
//AutoExpect
#define EVENTFLAG_AutoExpect                  0x2
//NowConsume
#define EVENTFLAG_NowConsume                  0x4
//ControllerGlue      
#define EVENTFLAG_ControllerGlue              0x8
//ConsumeGlue
#define EVENTFLAG_ConsumeGlue                 0x10
//Important
#define EVENTFLAG_Important                   0x20
//Sync
#define EVENTFLAG_Sync                        0x40
//--------------------------------------
//---Module ID---
//--------------------------------------
//Any Module
#define MODULE_ANY                            0
//Controller
#define MODULE_Controller                     1
//--------------------------------------

//current,system
//--------------------------------------
#define MODULE_CurrentPID                    ((PROC_ID)-1)
#define MODULE_SystemPID                     ((PROC_ID)0)
//--------------------------------------
//--------------------------------------
#define EVENT_ANY                             0
//--------------------------------------
//--------------------------------------
#define EVENT_BROADCAST_ACK_SUCCESS  0
#define EVENT_BROADCAST_ACK_ERROR    -1
//--------------------------------------
//---delete event---
//--------------------------------------
//delete event by ackcookie
#define DELETEEVENT_AckCookie   1
//delete event by event type
#define DELETEEVENT_Type        2
//delete event by Consume module
#define DELETEEVENT_Consume     3


/////////////////////////////////////////////
//Defining Error Codes
//Error Code >=0,For success;
//Error Code <0,For failed;
/////////////////////////////////////////////
//success
#define KError_Success                         0
//Success, but no stream data processed
#define KError_NoDataHandled                   1
//Success, New object
#define KError_CreateObject                    10
//Success, open the object
#define KError_OpenObject                      11
//Success, open the object and overwrite it
#define KError_OverrideObject                  12

//Failed, wrong length
#define KError_LengthError                     -1
//Failed,Timeout
#define KError_TimeOut                         -2
//Failed, insufficient buffer length
#define KError_OutOfLength                     -3

//Failed to connect to the kernel
#define KError_CantConnectKernel               -10
//Failed, there is currently a file being served
#define KError_FileServing                     -11

//Failed, multiple login users
#define KError_MultiUser                       -20
//Failed, no user logged in
#define KError_NoUser                          -21

//Failure, syntax error
#define KError_SyntaxError                     -30
//Failed to find the object
#define KError_CantFindObject                  -31
//Failure, multiple objects
#define KError_MultiObject                     -32
//Failed, the object was not found at the moment
#define KError_MaybeFindObject                 -33
//Failure, generic logic error
#define KError_CommonLogic                     -34

//Failed, encryption algorithm error
#define KError_CipherError                     -40
//Failure, internal error in encryption algorithm
#define KError_CipherInnerError                -41
//Failed, insufficient permissions
#define KError_PermissionDenied                -42

//Failed,Header Crc Check Error
#define KError_HeaderCrcError                  -50
//Failed,ESealError
#define KError_IdentitySealError               -51

//Failed,Other Error
#define KError_Other                           -100


/////////////////////////////////////////////
//SYNC Management
/////////////////////////////////////////////
#ifdef _WIN32
#ifdef __APPLICATION
//the type of lock
typedef CRITICAL_SECTION TEFS_LOCK;
typedef CRITICAL_SECTION * PTEFS_LOCK;
//initializing
inline void InitTEFSLock(PTEFS_LOCK pLock) {InitializeCriticalSection(pLock);}
//uninitializing
inline void UnInitTEFSLock(PTEFS_LOCK  pLock) {DeleteCriticalSection(pLock);}
//p operation
inline void TEFSLock(PTEFS_LOCK pLock) {EnterCriticalSection(pLock);}
//v operation
inline void TEFSUnLock(PTEFS_LOCK pLock) {LeaveCriticalSection(pLock);}
#endif
#ifdef __KERNEL
//the type of lock
typedef ERESOURCE     TEFS_LOCK;
typedef PERESOURCE   PTEFS_LOCK;
//initializing
inline void InitTEFSLock(PTEFS_LOCK pLock) {ExInitializeResourceLite(pLock);}
//uninitializing
inline void UnInitTEFSLock(PTEFS_LOCK  pLock) {ExDeleteResourceLite(pLock);}
//p operation
inline void TEFSLock(PTEFS_LOCK pLock) {FltAcquireResourceExclusive(pLock);}
//v operation
inline void TEFSUnLock(PTEFS_LOCK pLock) {FltReleaseResource(pLock);}
//reader p operation
inline void TEFSLockR(PTEFS_LOCK pLock) {FltAcquireResourceShared(pLock);}
//writer p operation
inline void TEFSLockW(PTEFS_LOCK pLock) {FltAcquireResourceExclusive(pLock);}
//standard v operation
inline void TEFSUnLockRW(PTEFS_LOCK pLock) {FltReleaseResource(pLock);}
#endif
#else
//the type of lock
typedef pthread_mutex_t TEFS_LOCK;
typedef pthread_mutex_t * PTEFS_LOCK;
//initializing
inline void InitTEFSLock(PTEFS_LOCK pLock) { pthread_mutex_init(pLock, NULL); }
//uninitializing
inline void UnInitTEFSLock(PTEFS_LOCK  pLock) { pthread_mutex_destroy(pLock); }
//p operation
inline void TEFSLock(PTEFS_LOCK pLock) { pthread_mutex_lock(pLock); }
//v operation
inline void TEFSUnLock(PTEFS_LOCK pLock) { pthread_mutex_unlock(pLock); }
#endif


/////////////////////////////////////////////
//debugger support
/////////////////////////////////////////////
#ifdef _WIN32
#ifdef __APPLICATION
extern void DbgPrint(const char * strDebug,...);
#define __dbg_print DbgPrint
#endif
#ifdef __KERNEL
#define __dbg_print DbgPrint
#endif
#endif


/////////////////////////////////////////////
//fast operation macros
/////////////////////////////////////////////
//flag exist
#define FlagOn(_F,_SF)        ((_F) & (_SF))
//flag exist return boolean
#define BooleanFlagOn(F,SF)   ((BOOLEAN)(((F) & (SF)) != 0))
//set flag
#define SetFlag(_F,_SF)       ((_F) |= (_SF))
//clear flag
#define ClearFlag(_F,_SF)     ((_F) &= ~(_SF))

//round up
#define RoundUp(x, align) (((INT32) (x) + (align - 1)) & ~(align - 1)) 
//round down
#define RoundDown(x, align) ((INT32)(x) & ~(align - 1)) 
//aligned 
#define AlignedOn(x, align) (((INT32)(x) & (align - 1)) == 0) 
//aligned return boolean
#define BooleanAlignedOn(x,align) ((BOOLEAN)(((INT32)(x) & (align - 1)) == 0))
/////////////////////////////////////////////

#define SetBit(a,b)   ((a) |= (1<<(b)))
#define ClearBit(a,b)   ((a) &= ~(1<<(b)))
/////////////////////////////////////////////

#ifdef _WIN32
#ifdef __KERNEL
#define SwapEndian16(x)    RtlUshortByteSwap(x)
#define SwapEndian32(x)    RtlUlongByteSwap(x)
#define SwapEndian64(x)    RtlUlonglongByteSwap(x)
#endif
#endif


/////////////////////////////////////////////
//packet and unpacket macro
/////////////////////////////////////////////
//--------------------------------------
//---base---
//--------------------------------------
#define StringLen(p) (strlen(p)+1)
#define WStringLen(p) ((wcslen(p)+1)*sizeof(WCHAR))
#define StringFlowLen(flow,pos) (strlen((PCHAR)((BYTE*)flow+pos))+1)
#define WStringFlowLen(flow,pos) ((wcslen((PWCHAR)((BYTE*)flow+pos))+1)*sizeof(WCHAR))
//--------------------------------------
//----Locate macro----
//--------------------------------------
#define LocateFlow_SimplePointer(flow,pos,type,p) {p=(type*)((BYTE*)(flow)+pos);pos+=sizeof(type);}
#define LocateFlow_String(flow,pos,p) {p=(PCHAR)((BYTE*)(flow)+pos);pos+=(strlen(p)+1);} 
#define LocateFlow_WString(flow,pos,p) {p=(PWCHAR)((BYTE*)(flow)+pos);pos+=(wcslen(p)+1)*sizeof(WCHAR);}
#define LocateFlow_Array(flow,pos,type,p,len) {p=(type*)((BYTE*)(flow)+pos);pos+=((len)*sizeof(type));}
//--------------------------------------
//----Restore macro----
//--------------------------------------
#define RestoreFlow_Simple(flow,pos,type,d) {d=*(type*)((BYTE*)(flow)+pos);pos+=sizeof(type);}
#define RestoreFlow_SimplePointer(flow,pos,type,p) {*(type*)(p)=*(type*)((BYTE*)(flow)+pos);pos+=sizeof(type);}
#define RestoreFlow_String(flow,pos,p) {memcpy(p,(BYTE*)(flow)+pos,StringFlowLen(flow,pos));pos+=StringFlowLen(flow,pos);}
#define RestoreFlow_WString(flow,pos,p) {memcpy(p,(BYTE*)(flow)+pos,WStringFlowLen(flow,pos));pos+=WStringFlowLen(flow,pos);}
#define RestoreFlow_Array(flow,pos,type,p,len) {memcpy(p,(BYTE*)(flow)+pos,(len)*sizeof(type));pos+=((len)*sizeof(type));}
//--------------------------------------
//----Save macro----
//--------------------------------------
#define SaveFlow_Simple(flow,pos,type,d) {*(type*)((BYTE*)(flow)+pos)=(d);pos+=sizeof(type);}
#define SaveFlow_SimplePointer(flow,pos,type,p) {*(type*)((BYTE*)(flow)+pos)=*(type*)(p);pos+=sizeof(type);}
#define SaveFlow_String(flow,pos,p) {memcpy((BYTE*)(flow)+pos,p,StringLen(p));pos+=StringLen(p);}
#define SaveFlow_WString(flow,pos,p) {memcpy((BYTE*)(flow)+pos,p,WStringLen(p));pos+=WStringLen(p);}
#define SaveFlow_Array(flow,pos,type,p,len) {memcpy((BYTE*)(flow)+pos,p,(len)*sizeof(type));pos+=((len)*sizeof(type));}
//--------------------------------------
//---Set macro---
//--------------------------------------
#define SetFlow_Zero(flow,pos,len) {memset((BYTE*)(flow)+pos,0,len);pos+=(len);}
#define SetFlow_Nega(flow,pos,len) {memset((BYTE*)(flow)+pos,-1,len);pos+=(len);}


/////////////////////////////////////////////
//List operation action
/////////////////////////////////////////////
//set default
#define LIST_VERB_DEFAULT    1
//clear list
#define LIST_VERB_CLEAR      2
//add item
#define LIST_VERB_ADD        3
//delete item
#define LIST_VERB_DELETE     4
//modify item
#define LIST_VERB_MODIFY     5


///////////////////////////////////////////////////////////////////
//Multiple string matching logic for matching templates
//The matching template can include multiple matching strings, each separated by |;
//Standard wildcard support
//    ? indicates any character, cannot be empty;
//    * means any string, can be empty;
//
//e.g (MULTIMATCH_OR,*.txt|*.doc)
///////////////////////////////////////////////////////////////////
//OR action
#define MULTIMATCH_OR    0
//ADN action
#define MULTIMATCH_AND   1

#define OPENER_LOCAL    0
#define OPENER_NET        1
#define OPENER_REMOTE  2

//query
#define OPEN_OPERATION_QUERY     0
//readonly
#define OPEN_OPERATION_READONLY    1
//write
#define OPEN_OPERATION_WRITE     2


/////////////////////////////////////////////
//Process control model constants
/////////////////////////////////////////////
//process type
//deny server process 
#define PROCESS_TYPE_DENY                     1
//cipher server process
#define PROCESS_TYPE_CIPHER                   2
//noauth cipher server process
#define PROCESS_TYPE_CIPHER_NOAUTH            3
//controller process(include 2)
#define PROCESS_TYPE_CONTROL                  4
//plain server process
#define PROCESS_TYPE_PLAIN                    5
//must plain server process
#define PROCESS_TYPE_PLAIN_MUST               6
//keep process
#define PROCESS_TYPE_KEEP                     7
//cache keep process
#define PROCESS_TYPE_KEEP_CACHE               11
//---process control model fast macro---
//Is the process a denial of service
#define IS_PROCESS_DENY(n)  ((n)==PROCESS_TYPE_DENY)
//Is the process a plain of service
#define IS_PROCESS_PLAIN(n) ((n)==PROCESS_TYPE_PLAIN || (n)==PROCESS_TYPE_PLAIN_MUST)
//Is the process a must plain of service
#define IS_PROCESS_MUST(n) ((n)==PROCESS_TYPE_PLAIN_MUST)
//Is the process a cipher of service
#define IS_PROCESS_CIPHER(n) ((n)==PROCESS_TYPE_CIPHER || (n)==PROCESS_TYPE_CIPHER_NOAUTH || (n)==PROCESS_TYPE_CONTROL)
//Is the process a noauth cipher of service
#define IS_PROCESS_NOAUTH_CIPHER(n) ((n)==PROCESS_TYPE_CIPHER_NOAUTH || (n)==PROCESS_TYPE_CONTROL)
//Is the process a keep of service
#define IS_PROCESS_KEEP(n) ((n)==PROCESS_TYPE_KEEP || (n)==PROCESS_TYPE_KEEP_CACHE)
//Is the process a keep cache of service
#define IS_PROCESS_KEEP_CACHE(n) ((n)==PROCESS_TYPE_KEEP_CACHE)
//---cheat level---
//No need to cheat
#define CHEAT_LEVEL_NONE                      0
//normal cheat
#define CHEAT_LEVEL_NORMAL                    1
//simple cheat
#define CHEAT_LEVEL_SIMPLE_DIR                2
//whole cheat
#define CHEAT_LEVEL_WHOLE_DIR                 3


////////////////////////////////////////////////////////////////
//Encrypted directory configuration file name
////////////////////////////////////////////////////////////////
#ifdef _WIN32
#define TEFS_CONFIG_FILENAME L"%DSK#.D!C"
#define TEFS_CONFIG_PATHNAME L"\\%DSK#.D!C"
#define TEFS_CONFIG_TEMPLATE L"*\\%DSK#.D!C"
#else
#define TEFS_CONFIG_FILENAME "%DSK#.D!C"
#define TEFS_CONFIG_PATHNAME "\\%DSK#.D!C"
#define TEFS_CONFIG_TEMPLATE "*\\%DSK#.D!C"
#endif

///////////////////////////////////////////
//Algorithm description report
//Report of the call to the TSK_GetCipherDesc function
///////////////////////////////////////////
typedef struct _CipherDescReportItem
{
	BYTE *  tagCipher;//tag,16 bytes
	char * strCipherName;//Name 
	char * strCipherText;//description
}CipherDescReportItem,* PCipherDescReportItem;
typedef struct _CipherDescReport
{
	UINT32 nItems;//counts
	PCipherDescReportItem arrayItem;//CipherDescReportItem Array

	_CipherDescReport() {arrayItem=NULL;}
	~_CipherDescReport() {if (arrayItem) __mem_free(arrayItem);}

	BOOLEAN UnPacket(BYTE * pFlow)
	{
		UINT32 i,nPos=0;
		RestoreFlow_Simple(pFlow,nPos,UINT32,nItems)
		if (arrayItem) {__mem_free(arrayItem);arrayItem=NULL;}
		if (nItems) 
		{	
			arrayItem=(PCipherDescReportItem)__mem_malloc(PagedPool,sizeof(CipherDescReportItem)*nItems,POOLTAG_TSK);
			if (arrayItem==NULL)  {nItems=0;return FALSE;}
		}
		for (i=0;i<nItems;i++)
		{
			LocateFlow_Array(pFlow,nPos,BYTE,arrayItem[i].tagCipher,CIPHER_TAG_LENGTH)
			LocateFlow_String(pFlow,nPos,arrayItem[i].strCipherName)
			LocateFlow_String(pFlow,nPos,arrayItem[i].strCipherText)
		}
		return TRUE;
	}
}CipherDescReport,* PCipherDescReport;


/////////////////////////////////////////////
//Report
/////////////////////////////////////////////
#ifdef _WIN32
///////////////////////////////////////////
//Kernel Exit Report
//Report of the call to the TSK_Exit function
///////////////////////////////////////////
typedef struct _ExitReportItem
{
	PROC_ID nPID;//Process ID
	WCHAR * strProcessName;//Process Name
	WCHAR * strFileName;//FileName
}ExitReportItem,* PExitReportItem;
typedef struct _ExitReport
{
	UINT32 nItems;//count
	PExitReportItem arrayItem;//ExitReportItem Array

	_ExitReport() {arrayItem=NULL;}
	~_ExitReport() {if (arrayItem) __mem_free(arrayItem);}

	BOOLEAN UnPacket(BYTE * pFlow)
	{
		UINT32 i,nPos=0;
		RestoreFlow_Simple(pFlow,nPos,UINT32,nItems)
		if (arrayItem) {__mem_free(arrayItem);arrayItem=NULL;}
		if (nItems) 
		{	
			arrayItem=(PExitReportItem)__mem_malloc(PagedPool,sizeof(ExitReportItem)*nItems,POOLTAG_TSK);
			if (arrayItem==NULL) {nItems=0;return FALSE;}
		}
		for (i=0;i<nItems;i++)
		{
			RestoreFlow_Simple(pFlow,nPos,UINT32,arrayItem[i].nPID)
			LocateFlow_WString(pFlow,nPos,arrayItem[i].strProcessName)
			LocateFlow_WString(pFlow,nPos,arrayItem[i].strFileName)
		}
		return TRUE;
	}
}ExitReport,* PExitReport;

///////////////////////////////////////////
//Hide Folder Report
//Report of the call to the TSK_GetHideFolder function
///////////////////////////////////////////
typedef struct _HideFolderReportItem
{
	BYTE nIdentityID[IDENTITYID_LENGTH];//users identity id
	BOOLEAN bHideSelf;//
	WCHAR * strHideFolder;//fullpath
}HideFolderReportItem,* PHideFolderReportItem;
typedef struct _HideFolderReport
{
	UINT32 nItems;//count
	PHideFolderReportItem arrayItem;//HideFolderReportItem Array

	_HideFolderReport() {arrayItem=NULL;}
	~_HideFolderReport() {if (arrayItem) __mem_free(arrayItem);}

	BOOLEAN UnPacket(BYTE * pFlow)
	{
		UINT32 i,nPos=0;
		RestoreFlow_Simple(pFlow,nPos,UINT32,nItems)
		if (arrayItem) {__mem_free(arrayItem);arrayItem=NULL;}
		if (nItems) 
		{	
			arrayItem=(PHideFolderReportItem)__mem_malloc(PagedPool,sizeof(HideFolderReportItem)*nItems,POOLTAG_TSK);
			if (arrayItem==NULL)  {nItems=0;return FALSE;}
		}
		for (i=0;i<nItems;i++)
		{
			RestoreFlow_Array(pFlow,nPos,BYTE,arrayItem[i].nIdentityID,IDENTITYID_LENGTH)
			RestoreFlow_Simple(pFlow,nPos,BOOLEAN,arrayItem[i].bHideSelf)
			LocateFlow_WString(pFlow,nPos,arrayItem[i].strHideFolder)
		}
		return TRUE;
	}
}HideFolderReport,* PHideFoldReport;

///////////////////////////////////////////
//ControlModel Report
//Report of the call to the TSK_GetRunProcessControlModel function
///////////////////////////////////////////
typedef struct _RunProcessReportItem
{
	PROC_ID nPID;//Process ID
	BYTE nProcessType;//Type
	BYTE nCheatLevel;//CheatLevel
	BOOLEAN bInherit;//Inherit
	WCHAR * strProcessName;//ProcessName
}RunProcessReportItem,* PRunProcessReportItem;
typedef struct _RunProcessReport
{
	UINT32 nItems;//counts
	PRunProcessReportItem arrayItem;//RunProcessReportItem Array

	_RunProcessReport() {arrayItem=NULL;}
	~_RunProcessReport() {if (arrayItem) __mem_free(arrayItem);}

	BOOLEAN UnPacket(BYTE * pFlow)
	{
		UINT32 i,nPos=0;
		RestoreFlow_Simple(pFlow,nPos,UINT32,nItems)
		if (arrayItem) {__mem_free(arrayItem);arrayItem=NULL;}
		if (nItems) 
		{	
			arrayItem=(PRunProcessReportItem)__mem_malloc(PagedPool,sizeof(RunProcessReportItem)*nItems,POOLTAG_TSK);
			if (arrayItem==NULL)  {nItems=0;return FALSE;}
		}
		for (i=0;i<nItems;i++)
		{
			RestoreFlow_Simple(pFlow,nPos,PROC_ID,arrayItem[i].nPID)
			RestoreFlow_Simple(pFlow,nPos,BYTE,arrayItem[i].nProcessType)
			RestoreFlow_Simple(pFlow,nPos,BYTE,arrayItem[i].nCheatLevel)
			RestoreFlow_Simple(pFlow,nPos,BOOLEAN,arrayItem[i].bInherit)
			LocateFlow_WString(pFlow,nPos,arrayItem[i].strProcessName)
		}
		return TRUE;
	}
}RunProcessReport,* PRunProcessReport;
#endif


/////////////////////////////////////////////////////////////////////
//the permission structure
//
//Description of the permissions defined for each identity in the ESeal zone
//1.Permission field length  2 bytes
//  PermissionInfo,UINT6,Each bit indicates a permission switch.
/////////////////////////////////////////////
//Permission field length  2 bytes
#define PERMISSION_INFO_LENGTH     2

//Permission
typedef struct _PermissionInfo
{
	UINT16    bOwner : 1;//is owner?
	UINT16    bAdjust : 1;//can share the file?
}PermissionInfo, *PPermissionInfo;

//Fast Permission Operation maroc
//Set All
#define SetPermission(a) *(UINT16*)(a)=(UINT16)-1;
//Clear
#define ClearPermission(a) *(UINT16*)(a)=(UINT16)0;
//Copy
#define CopyPermission(a,b) *(UINT16*)(a)=*(UINT16*)(b);
//And
#define AndPermission(a,b) *(UINT16*)(a)=(*(UINT16*)(a)) & (*(UINT16*)(b))
//Or
#define OrPermission(a,b) *(UINT16*)(a)=(*(UINT16*)(a)) | (*(UINT16*)(b))

#endif
