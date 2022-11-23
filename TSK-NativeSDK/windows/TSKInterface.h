//////////////////////////////////////////////////////////////////////////////
//Filename: TSKInferface.h
//Description: W3FS Native SDK library interface description
//Author: ecore
//Reference: 
//Remark: The return value is INT32 which returns a description of the result of the call.
//      Refer to the description of error codes in TSKType.h for details.     
/////////////////////////////////////////////////////////////////////////////
#if !defined(_TSK_INTERFACE_H)
#define _TSK_INTERFACE_H

#include "TSKType.h"

#ifdef _WIN32
#define TSK_EXPORT  1

#ifdef __APPLICATION
	#ifdef TSK_EXPORT
		#define TSK_DECLSPEC __declspec(dllexport)
	#else
		#define TSK_DECLSPEC __declspec(dllimport)
	#endif
#endif
#ifdef __KERNEL
	#define TSK_DECLSPEC 
#endif
#else
#define TSK_DECLSPEC  __attribute__ ((visibility("default")))
#define __stdcall
#endif


//////////////////////////////////////////////////////////////////////////////
//------Initializing------
//To use the W3FS Native SDK library, first call the initialization interface. If the initialization fails, the W3FS Native SDK library will not be available.
//It is no longer necessary to use the W3FS Native SDK library (e.g. software exit) to call the reverse initialization interface.
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: TSK_Init
//Description: Initialize the W3FS Native SDK library
//Parameters: 
//return: INT32,KError_Success,Success;
//          KError_CantConnectKernel,Failed to connect to the kernel;
//          KError_Other,Failed,other error                       
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_Init();

////////////////////////////////////////////////////////////////////////////
//Name: TSK_UnInit
//Description: UnInitialize the W3FS Native SDK library
//Parameters: None
//return: None
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC void __stdcall TSK_UnInit();

#ifdef _WIN32
////////////////////////////////////////////////////////////////////////////
//Name: TSK_SetController
//Description: Set/unset the current process as a kernel-driven controller
//Parameters: b[IN],TRUE:set,FALSE:unset
//return: INT32,KError_Success,Success;
//          KError_CantConnectKernel,Fail
//          KError_CantFindObject,Fail
//          KError_MultiObject,Fail
//          KError_Other,Fail                   
//Remarks: Only one control process is allowed to exist at the same time
//      Some interfaces only allow control processes to be set to the kernel
//
//      To cancel the setting when the control process exits
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_SetController(BOOLEAN b);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_Exit
//Description: Exit Kernel
//Parameters: pJitID[OUT],the exit JIT Report ID
//            pJitInfoLen[OUT],the exit JIT Report Data Length
//return: INT32,KError_Success,success,
//          KError_FileServing,fail;
//          KError_Other,fail                       
//Remarks: The W3FS kernel is a resident memory driver
//
//      This function needs to be called only when the program is updated
//      After the program update is complete, start the W3FS kernel by rebooting the system or calling the fltmc load command
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_Exit(JIT_ID * pJitID,UINT32 * pJitInfoLen);


//////////////////////////////////////////////////////////////////////////////
//------Basic Interface------
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: TSK_Debug
//Description: Debug Interface
//Parameters: nAction[IN],the debug action
//      nObject[IN],the debug object
//      nArgu1[IN],the debug Argument 1
//      pArgu2[IN],the debug Argument 2
//return: INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_Other,fail;
//Remarks: the W3FS Kernel Debugger,Refer to the debug manual
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_Debug(UINT32 nAction,UINT32 nObject,UINT32 nArgu1,InfoPointer pArgu2);
#endif

////////////////////////////////////////////////////////////////////////////
//Name: TSK_GetRandomKey
//Description: Get a random key of specified length
//Parameters: nKeyLen[IN],the length of the random key
//      pKey[IN/OUT],the buffer of the random key
//return: INT32, KError_Success,success;
//Remarks: True random keys generated by the driver kernel
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_GetRandomKey(UINT32 nKeyLen,BYTE * pKey);


#ifdef _WIN32
////////////////////////////////////////////////////////////////////////////
//Name: TSK_GetJITInfo
//Description: Get a JIT information by JIT_ID
//Parameters: JitID[IN],the JIT_ID
//      nJitInfoLen[IN],the length of the buffer
//      pJitInfo[IN/OUT],the buffer
//return: INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_Other,fail;
//Remarks: 
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_GetJITInfo(JIT_ID JitID,UINT32 nJitInfoLen,BYTE * pJitInfo);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_SetJITInfo
//Description: Save data as JIT information
//Parameters: nJitInfoLen[IN],the length of the data
//      pJitInfo[IN],the buffer of the date
//      pJitID[OUT],the cookie of the JIT information
//return:INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_Other,fail;
//Remarks: 
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_SetJITInfo(UINT32 nJitInfoLen,BYTE * pJitInfo,JIT_ID * pJitID);

#endif


//////////////////////////////////////////////////////////////////////////////
//------Digest Interface------
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: TSK_DigestCRC32
//Description: Digest using CRC32 algorithm
//Parameters: nFlowLen[IN],the length of the data
//      pFlow[IN],the data
//      pCookie[IN/OUT],the cookie of the Digest process
//      pCRC32[OUT],the final CRC32 value
//return: INT32,KError_Success,success;
//          KError_Other,fail;
//Remarks: CRC32 digest is a high-speed but non-reliable digest algorithm that can be used to verify the encrypted message block structure data itself.
//      Two methods of use are supported: digest for a single stream, and joint digest for multiple streams.
//      the pCookie is NULL means digist for a single stream
//      the pCookie is not NULL means joint digest for multiple streams
//
//      digist for a single stream:
//      UINT32 nCRC32;
//      TSK_DigestCRC32(nFlowLen,pFlow,NULL,&nCRC32);
//
//      joint digest for multiple streams
//      PVOID cookie=NULL;
//      UINT32 nCRC32;
//      TSK_DigestCRC32(0,NULL,&cookie,NULL);
//      TSK_DigestCRC32(nFlowLen,pFlow,&cookie,NULL);
//      TSK_DigestCRC32(nFlowLen2,pFlow2,&cookie,NULL);
//      TSK_DigestCRC32(0,NULL,&cookie,&nCRC32);
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_DigestCRC32(UINT32 nFlowLen,BYTE * pFlow,PVOID * pCookie,UINT32 * pCRC32);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_DigestMD5
//Description: Digest using MD5 algorithm
//Parameters: nFlowLen[IN],the length of the data
//      pFlow[IN],the data
//      pCookie[IN/OUT],the cookie of the Digest process
//      pMD5[OUT],the final MD5 value
//return: INT32,KError_Success,success;
//          KError_Other,fail;
//Remarks: MD5 digest is a low-speed but reliable digest algorithm that can be used to verify the signature of the file data itself.
//      It is used in the same way as TSK_DigestCRC32, except that the final result is received in a 16-byte buffer.
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_DigestMD5(UINT32 nFlowLen,BYTE * pFlow,PVOID * pCookie,BYTE * pMD5);

/////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_DigestSha256
//Description: Digest using SHA256 algorithm
//Parameters: nFlowLen[IN],the length of the data
//      pFlow[IN],the data
//      pCookie[IN/OUT],the cookie of the Digest process
//      pMD5[OUT],the final SHA256 value
//return: INT32,KError_Success,success;
//          KError_Other,fail;
//Remarks: SHA256 digest is a reliable digest algorithm that can be used to digest arbitrary data.
//      It is used in the same way as TSK_DigestCRC32, except that the final result is received in a 32-byte buffer.
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_DigestSha256(UINT32 nFlowLen,BYTE * pFlow,PVOID * pCookie,BYTE * pSHA256);


//////////////////////////////////////////////////////////////////////////////
//------Identity(Asymmetric encryption algorithm) Interface------
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: TSK_IdentityIssue
//Description: Generate (issue) an identity object
//Parameters: pSeed[IN],the buffer of the seed,must 32-byte buffer
//      nSeedLen[IN]，the length of the sedd,must 32
//      pIdentity[OUT],the identity object
//Return:INT32, KError_Success,success;
//          KError_Other,fail;
//Remarks: Only ecc 256k1 is supported
//      The same pSeed that will generate the same identity
//      the seed information is mandatory 32 bytes long. 
//      It is also possible to have no seed and the identity object will be issued randomly
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_IdentityIssue(IdentityObject * pIdentity,BYTE* pSeed,UINT32 nSeedLen);

///////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_IdentityIssueEx
//Description: Generate (issue) an identity object，and return the public and private keys
//Parameters: pSeed[IN],the buffer of the seed,must 32-byte buffer
//      nSeedLen[IN]，the length of the sedd,must 32
//      nPublicKeyLen[IN/OUT], the length of the public key buffer
//      nPrivateKeyLen[IN/OUT], the length of the private key buffer
//      pPublicKeyBuf[IN/OUT], the public key
//      pPrivateKeyBuf[IN/OUT], the private key
//      pKeyID[IN/OUT],the identity ID,20-byte length
//return:INT32,KError_Success,success;
//          KError_Other,fail;
//Remarks: Only ecc 256k1 identity is supported
//      If the seed information is available, the generated identity object will be consistent
//      It is recommended that the buffer of public and private keys can be set to 200 bytes, and the actual length is returned by the parameter
//      pKeyID, a unique ID determined by the W3FS Native SDK library for each issued cryptographic identity key
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC INT32 __stdcall TSK_IdentityIssueEx(BYTE* pSeed, UINT32 nSeedLen,BYTE* pPublicKeyBuf, UINT32& nPublicKeyLen,BYTE* pPrivateKenBuf, UINT32& nPrivateKeyLen,BYTE* pKeyID);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_IdentityFree
//Description: free a identity object
//Parameters: identity[IN],the identity object
//return: INT32,KError_Success,success;
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_IdentityFree(IdentityObject identity);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_IdentityExport
//Description: Export a binary stream of public or private keys from an identity object
//Parameters: identity[IN],the identity object
//      nAction[IN],the action
//        IDENTITY_PUBLIC_KEY,Export the public key
//        IDENTITY_PRIVATE_KEY,Export the private key
//        IDENTITY_KEY_ID,Export the identity ID
//      BufLen[IN/OUT],the length of the buffer
//      Buf[IN/OUT],the buffer
//      pWrittenLen[OUT],the length of actual output
//return:INT32,KError_Success,success;
//          KError_Other,fail
//Remarks: the buffer length is recommended to be set to 200 bytes
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_IdentityExport(IdentityObject identity,BYTE Action,UINT32 BufLen,BYTE * Buf,UINT32 * pWrittenLen);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_IdentityImport
//Description: Import an identity object by binary public or private key data
//Parameters: nAction[IN],the action
//        IDENTITY_PUBLIC_KEY,Export the public key
//        IDENTITY_PRIVATE_KEY,Export the private key
//      BufLen[IN/OUT],the length of the buffer
//      Buf[IN/OUT],the buffer
//      pIdentity[OUT],the identity object
//return: 为INT32,KError_Success,success;
//          KError_Other,fail;
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_IdentityImport(BYTE Action,UINT32 BufLen,BYTE * Buf,IdentityObject * pIdentity);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_IdentityEncrypt
//Description: Data encryption using identity objects
//Parameters: identity[IN],the identity object
//      cryptAction[IN],the action
//        PUBLIC_KEY为,Encryption with identity public key
//        PRIVATE_KEY,Encryption with identity private key（Digital Signature）
//      nSrcFlowLen[IN],the length of the src flow
//      pSrcFlow[IN],thr src flow
//      nTarFlowLen[OUT],the length of the tar flow
//      pTarFlow[OUT],the tar flow
//return:INT32,KError_Success,success;
//          KError_Other,fail
//Remarks: Based on the characteristics of the ecc256 algorithm, each ecc256 encryption is in units of 64 bytes
//      pTarFlow should be of sufficient length and applied in the ratio of raw data/encrypted data 64/154
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_IdentityEncrypt(IdentityObject identity,BYTE cryptAction,
					UINT32 nSrcFlowLen,BYTE * pSrcFlow,
					UINT32 nTarFlowLen,BYTE * pTarFlow,
					UINT32 * pTarFlowReturnLen);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_IdentityDecrypt
//Description: Data decryption using identity objects
//Parameters: identity[IN],the identity object
//      cryptAction[IN],the action
//        PUBLIC_KEY,Decryption with public key(verify)
//        PRIVATE_KEY,Decryption with private key
//      nSrcFlowLen[IN],the length of src flow
//      pSrcFlow[IN],the src flow buffer
//      nTarFlowLen[OUT],the length of dst flow
//      pTarFlow[OUT],the dst folw buffer
//return: INT32,KError_Success,success;
//          KError_Other,fail;
//Remarks: 
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_IdentityDecrypt(IdentityObject identity,BYTE cryptAction,
					UINT32 nSrcFlowLen,BYTE * pSrcFlow,
					UINT32 nTarFlowLen,BYTE * pTarFlow,
					UINT32 * pTarFlowReturnLen);


//////////////////////////////////////////////////////////////////////////////
//------Symmetric encryption algorithm interface------
//Symmetric algorithm for data encryption and decryption of files.
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: TSK_GetCipherDesc
//Description: Get all currently loaded algorithms
//Parameters: pDescBuf[OUT],the buffer
//      nDescBufLen[IN]，the length of pDescBuf
//return: the actual length of the report，If the return value is greater than the buffer length, then no operation will be done on the buffer，
//      You need to request a buffer large enough according to the actual length and get it again
//Remarks: Example of algorithm report format
//      Total:4 bytes length of UINT32 data
//      First algorithm description
//          tag(16-bytes)+name(string,end with 0)+desc(string,end with 0)
//      Second algorithm description
//      ......
//      More
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_GetCipherDesc(BYTE * pDescBuf,INT32 nDescBufLen);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_GetCipherInfo
//Description: Get information about the specified algorithm
//Parameters: tagCipher[IN],the tag,can be NULL,get the default item
//      pKeyLength[OUT],the length of key
//      pBlockSize[OUT],the Block Size of algorithm
//Return:INT32,KError_Success,success;
//          KError_CipherError,fail;
//          KError_Other,fail;
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_GetCipherInfo(BYTE * tagCipher,UINT16 * pKeyLength,UINT16 * pBlockSize);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_SetDefaultCipher
//Description: Set the default algorithm
//Parameters: tagCipher[IN],the tag
//Return: INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_CipherError,fail;
//          KError_Other,fail;
//Remark: 
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_SetDefaultCipher(BYTE * tagCipher);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_SetDefaultZone
//Description: Set default encrypted zone length
//Parameters: nLen[IN],the length of encrypted zone
//Return: INT32,KError_Success,success;
//          KError_CantConnectKernel,fail
//          KError_Other,fail
//Remark: Encrypt all data in a file by default
//      Reasonable encryption zone length can be set to encrypt only the data up to the set length from 
//      the file header to ensure security and efficiency.
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_SetDefaultZone(INT64 nLen);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_CreateCipherCell
//Description: Create a Cipher Cell
//Parameters: tagCipher[IN],the specified Cipher tag
//      nKeyLen[IN],the key length
//      pKey[IN],the key
//Return: INT32
//          >=0,success;the index of the cipher cell
//          KError_CipherError,fail
//          KError_CipherInnerError,fail
//          KError_Other,fail
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_CreateCipherCell(BYTE * tagCipher,UINT32 nKeyLen,BYTE * pKey);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_DeleteCipherCell
//Description: delete a cipher cell
//Parameters: nCipherCell[IN],the index of cipher cell
//Return: INT32,KError_Success,success;
//          KError_CipherError,fail;
//          KError_CipherInnerError,fail;
//          KError_Other,fail;
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_DeleteCipherCell(INT32 nCipherCell);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_ProcessCipherCell
//Description: use the cipher cell to process data flow
//Parameters: nCipherCell[IN],the index of cipher cell
//      nAction[IN],the action
//      nOffset[IN],the offset
//      nLength[IN],the data flow length
//      pFlow[IN/OUT],the data flow buffer
//Return: INT32,KError_Success,success;
//          KError_CipherError,fail
//          KError_CipherInnerError,fail
//          KError_Other,fail
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_ProcessCipherCell(INT32 nCipherCell,BYTE nAction,INT64 nOffset,UINT32 nLength,BYTE * pFlow);


#ifdef _WIN32
//////////////////////////////////////////////////////////////////////////////
//------Event Interface------
//Event mechanism interface to help implement cross-process asynchronous and synchronous collaboration.
//
//Supports up to 32 broad categories of events
//
//When querying events, you can specify the range of event types to be queried as[nEventTypeLeft,nEventTypeRight].
//If the left value == the right value, then the semantics is of course to query only events of that type.
//If the left value is EVENT_ANY, then the semantics is of course <=nEventTypeRight.
//If the right value is EVENT_ANY, the semantics is of course >=nEventTypeLeft.
//If the left and right values are both EVENT_ANY, the semantics are of course all types of events.
//In the case of a delete event, the parameter also has this semantics, i.e. the range to be deleted is [nDeleteArguLeft,nDeleteArguRight].
//
//Support the module concept.
//A module can register its module ID with the kernel, and log out of the module when it exits.
//The kernel also maintains the relationship between modules and processes, and the process to which a module belongs is called an entity of the module.
//When all entities of a module exit, the kernel will automatically log out the module.
//When generating an EVENTFLAG_NowConsume event for a given consumer module, if the module does not currently have an entity, an error will be generated directly if the module does not exist.
//Using this mechanism, it is possible to detect the existence of modules.
//When specifying the consuming module of an event, it causes additional performance overhead for the kernel to find out if the module exists, so it is recommended that large numbers of events be grouped directly into a large category and that the consuming module of these events not be specified.
//For example, log events are massive events that can be grouped into one big category as log category, and a thread dedicated to log category, and all log events do not have to be specified as consumption modules.
//
//Supports synchronous and asynchronous events:
//Event consumption can support synchronous queries or asynchronous queries by specifying a timeout value.
//Generating events can be sent synchronously via Send or delivered asynchronously via Post.
//
//Support for broadcast events:
//A non-broadcast event that disappears when any module takes the event.
//A broadcast event that disappears only when all the consuming module of the event have taken the event.
//Since a broadcast event requires a module entity to be consumed, this means that the consuming module must be a specific module, not MODULE_ANY.
//Broadcast events can support synchronous events, which means that the response is complete after all consumer module entities have responded to the event.
//The kernel automatically handles sudden joins and exits of module entities, ensuring that no broadcast hangs due to a module entity not picking up or responding to an event.
//However, since multiple module entities are responding to broadcast events, this means that there may be multiple responses, so the following restrictions are placed on synchronous broadcast events:
//The response to a synchronous broadcast event can only be a value of type INT32, and it can only be specified as follows:
//0, the synchronous broadcast event was handled correctly;
//-1, The synchronous broadcast event cannot be handled correctly;
//The kernel will combine the responses of all module entities and give a final result for all module entities:
//If all module entities respond to correct processing or if they do not respond because the module entity exits, a value of 0 indicates correct processing.
//If any module entity response cannot be processed correctly, a -1 indicates that it cannot be processed correctly.
//
//An event is a data structure that describes the semantics of the event.
//Events are maintained by the kernel, and the application layer can consume events (get deleted, and react to events) through the event interface.
//Events are generated by the kernel or by other modules calling the event interface and are managed by the kernel.
//The recommended way to pack and unpack events is to use the corresponding macros provided in TSKType.h(e.g. SaveFlow_Simple,RestoreFlow_Simple)
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: TSK_CreateEventClass
//Description: Create a Event Class
//Parameters: nEventClassID[IN],the event class,Range of values[0,31]
//      nEventFlag[IN],the Event Falg;
//Return: INT32,KError_Success,sucess;
//          KError_CantConnectKernel,fail;
//          KError_Other,fail;
//Remark: 
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_CreateEventClass(UINT32 nEventClassID,UINT32 nEventFlag);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_DeleteEventClass
//Description: Delete a Event Calss
//Parameters: nEventClassID[IN],the Event class ID,Range of values[0,31]
//Return: INT32,KError_Success,sucess;
//          KError_CantConnectKernel,fail;
//          KError_Other,fail;
//Remark: 
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_DeleteEventClass(UINT32 nEventClassID);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_RegisterModule
//Description: Register a Module to Event Manager
//Parameters: nModuleID[IN],the Module ID
//      nPID[IN],the Process ID,can use MODULE_CurrentPID or MODULE_SystemPID magic word
//Return:INT32,KError_Success,sucess;
//          KError_CantConnectKernel,fail;
//          KError_Other,fail;
//Remark: 
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_RegisterModule(UINT32 nModuleID,PROC_ID nPID);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_UnRegisterModule
//Description: UnRegister a Module
//Parameters: nModuleID[IN],the Module ID
//      nPID[IN],the Process ID
//Return: INT32, KError_Success,sucess;
//          KError_CantConnectKernel,fail;
//          KError_Other,fail;
//Remark:
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_UnRegisterModule(UINT32 nModuleID,PROC_ID nPID);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_QueryEvent
//Description: Query a Event
//Parameters: nEventClassID[IN],the EventClassID,Range of values[0,31]
//      nThisModuleID[IN],the Module ID of the initiating query,can be MODULE_ANY
//      nEventTypeLeft[IN],nEventTypeRight[IN],the Range of values[nEventTypeLeft,nEventTypeRight]
//      nWaitTime,the Wait time,
//          0 means no waiting, -1(INFINITE) means permanent waiting.
//     pAckCookie[OUT],the return cookie
//      pJitID[OUT],pJitInfoLen[OUT],the JIT ID and length;
//Return:INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_TimeOut,fail;
//          KError_Other,fail;
//Remark: 
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_QueryEvent(UINT32 nEventClassID,UINT32 nThisModuleID,UINT32 nEventTypeLeft,UINT32 nEventTypeRight,
					UINT32 nWaitTime,UINT32 * pAckCookie,JIT_ID * pJitID,UINT32 * pJitInfoLen);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_PostEvent
//Description: Post a event,Asynchronous
//Parameters: nEventClassID[IN],the event class,range of values[0,31]
//      nEventFlag[IN],the event flag
//      nThatModuleID[IN],the receive event module ID,can be MODULE_ANY 
//      nEventLen[IN],pEvent[IN],the event buffer and length
//Retuen: INT32,KError_Success,sucess;
//          KError_CantConnectKernel,fail;
//          KError_CantFindObject,fail;
//          KError_Other,fail;
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_PostEvent(UINT32 nEventClassID,UINT32 nEventFlag,UINT32 nThatModuleID,
					UINT32 nEventLen,BYTE * pEvent);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_SendEvent
//Description: Send a event,Synchronized Events
//Parameters: nEventClassID[IN],the event class ID,range of values[0,31]
//      nEventFlag[IN],the event flag
//      nThatModuleID[IN],the module ID for receive event,can be MODULE_ANY
//      nWaitTime[IN],the wait time,Unit is second
//          0 means no waiting, -1(INFINITE) means permanent waiting.
//      nEventLen[IN],pEvent[IN],the event buffer length and buffer
//      pJitID[OUT],pJitInfoLen[OUT],the return value for event,JIT data mode
//Return:INT32,KError_Success,success;
//          KError_CantConnectKernel,fail
//          KError_CantFindObject,fail
//          KError_TimeOut,fail
//          KError_Other,fail
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_SendEvent(UINT32 nEventClassID,UINT32 nEventFlag,
					UINT32 nThatModuleID,UINT32 nWaitTime,
					UINT32 nEventLen,BYTE * pEvent,JIT_ID * pJitID,UINT32 * pJitInfoLen);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_AckEvent
//Description: Responding to a synchronization event
//Parameters: nAckCookie[IN],the ACK cookie(The cookie returned by the TSK_QueryEvent)
//      nResultLen[IN],pResult[IN],the result of the event
//Return: INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_Other,fail;
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_AckEvent(UINT32 nAckCookie,UINT32 nResultLen,BYTE * pResult);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_DeleteEvent
//Description: Delete an event
//Parameters: nEventClassID[IN],the ID of the Event Class(range of values[0,31])
//      nDeleteLogic[IN],the delete logic
//      nDeleteArguLeft[IN],nDeleteArguRight[IN],the range of event ID values[ nDeleteArguLeft,nDeleteArguRight].
//Return: INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_Other,fail;
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_DeleteEvent(UINT32 nEventClassID,UINT32 nDeleteLogic,UINT32 nDeleteArguLeft,UINT32 nDeleteArguRight);

#endif

//////////////////////////////////////////////////////////////////////////////
//------Account Interface------
//the library only supports single account login.
//
//Each identity has an identity ID.
//Each account may have more than one identity, but only one identity (representing the user) may represent the user of the account.
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: TSK_LoginUser
//Description: User Login
//Parameters: nIdentityID[ID],Identity ID of the logged-in user
//Return: INT32,KError_Success,sucess;
//          KError_CantConnectKernel,fail;
//          KError_MultiUser,fail;
//          KError_Other,fail;
//Remark: 
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_LoginUser(BYTE* nIdentityID);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_LogoutUser
//Description: Log out of the current account
//Parameters: 
//Return: INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_NoUser,fail;
//          KError_Other,fail;
//Remark: 
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_LogoutUser();


//////////////////////////////////////////////////////////////////////////////
//------Login user's holding identity interface-----
//User-related; since only one user can be logged in, it will be automatically processed as the current user.
//
//Each identity has an identity ID.
//
//In the W3FS Encrypt Head,The signer used to describe the file in the signature verification area is described by the internal ID of the signer (user or group) identity.
//In the W3FS Encrypt Head,The explicit description of the specific permissions of the file is also described by the internal ID of each identity in the Eseal Zone.
//
//The default configuration required for the identity mechanism needs to be set to the library (kernel).
//The algorithm provided by the identity mechanism is provided by the library.
//The identity mechanism is also managed in the kernel as a list:
//The default item is used as the user's identity; the matching item (which is a list) is used as the other identities held by the user, generally a list of group identities.
//
//The identity stored by the library is required by the library itself for automatic default operations (automatic kernel encryption and decryption, etc.), but there are actually identities that do not need to be stored by the library.
//For example, the process of distributing an encrypted file to a friend or group uses the friend's or group's public key;
//For example, the process of verifying a signature uses the public key of a friend or group;
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: TSK_SetHoldIdentity
//Description: Set the identity held by the current user to the W3FS Native SDK library
//Parameters: nListVerb[IN],the List operation verb, no LIST_VERB_MODIFY semantics
//       nIdentityID[IN],the identity ID
//       nPermission[IN],the permission of the identity
//       nLastTime[IN],the last usage time of the identity pair file,must -1;
//       pKeyBuf[IN],the buffer of the identity key
//       nKeyLen[IN],the buffer length of the identity key
//return: INT32, KError_Success,success;
//          KError_CantConnectKernel,fail
//          KError_NoUser,fail
//          KError_SyntaxError,fail
//          KError_MultiObject,fail
//          KError_CantFindObject,fail
//          KError_Other,fail
//Remark: The identities held by the current user are a list,Management via LIST_VERB_CLEAR/LIST_VERB_ADD/LIST_VERB_DELETE
//       When LIST_VERB_ADD, all parameters obviously need to be provided.
//       When LIST_VERB_DELETE, the parameters obviously only need to provide the nIdentityID.
//
//       LIST_VERB_DEFAULT is to set the user's default identity;
//       When setting (or changing) a default identity, that identity must be in the list of held identities, so the parameter only needs to provide the nIdentityID.
//       When you want to clear the default identity, you should specify nIdentityID as IDENTITY_NULL, no other parameters should be provided.
//
//       All added identities suggest that nPermission be set to maximum permissions.
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_SetHoldIdentity(UINT32 nListVerb,
					BYTE* nIdentityID, PermissionInfo nPermission, int nLastTime,BYTE * pKeyBuf,INT32 nKeyLen);

#ifdef _WIN32
//////////////////////////////////////////////////////////////////////////////
//------Hidden Folder Interface------
//User-related; since only one user can be logged in, it will be automatically processed internally as the current user.
//
//A hidden folder is a setting such as D:\My Private.
//
//Set hidden folders using the standard list action verbs.
//
//The hidden folder settings are stored and managed by the library (actually the kernel) because they are needed even when the user is not logged in or when other users are logged in.
//Since the kernel is responsible for the storage, the Get operation is provided for the application layer to get the information.
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: TSK_SetHideFolder
//Description: Set the current user's hidden folder
//Parameters: nListVerb[IN],the list operation verb,no LIST_VERB_MODIFY semantics
//      bSelfHide[IN].Set the folder itself to be hidden or not: TRUE for hidden, FALSE for not hidden
//      strUserHide[IN],the hidden folder to be set (this item is Key)
//return: INT32,KError_Success,success;
//          KError_CantConnectKernel,success
//          KError_NoUser,success
//          KError_SyntaxError,success
//          KError_CommonLogic,success
//          KError_MultiObject,success
//          KError_CantFindObject,success
//          KError_Other,success
//Remark: 
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_SetHideFolder(UINT32 nListVerb,BOOLEAN bSelfHide,WCHAR * strUserHide);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_GetHideFolder
//Description: Get the current user's hidden folder
//Parameters: pJitID[IN],pJitInfoLen[OUT]Returning hidden folder reports via the JIT interface
//Return:INT32,KError_Success,success
//          KError_CantConnectKernel,fail
//          KError_NoUser,fail
//          KError_Other,fail
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_GetHideFolder(JIT_ID * pJitID,UINT32 * pJitInfoLen);


//////////////////////////////////////////////////////////////////////////////
//------Control Module Interface------
//User-related; since only one user can be logged in, it will be automatically processed internally as the current user.
//The control model consists of the following four components:
//1.Global Ignore List
//  All files under this model will be ignored by the kernel
//2.Global must encrypt list
//  All files (usually suffixes) under this model will be necessarily encrypted by a process of the plaintext type (reads and writes will be necessarily encrypted)
//3.Configuring the process control model
//  Configure the process type by process name
//4.Running process control model
//  Provides the results generated when the current run is performed according to the configured process control model
//
//The config control model uses standard list manipulation verbs.
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: TSK_SetCMGlobalIgnore
//Description: Set the control model for the current user - global ignore list
//Parameters: nListVerb[IN],the list operation verb,no LIST_VERB_MODIFY and LIST_VERB_DEFAULT semantics
//      strTemplate[IN],the template,support *?|wildcard,|Multiple templates connected by logical or semantic parsing (this item is Key)
//Return: INT32, KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_NoUser,fail;
//          KError_SyntaxError,fail;
//          KError_MultiObject,fail;
//          KError_CantFindObject,fail;
//          KError_Other,fail;
//Remark:The set template indicates the case that is skipped, i.e. the case that should not be encrypted.
//      The control model-global ignore list is responsible for skipping cases that should not be encrypted, such as windows directories that should not be encrypted.
//
//      The template uses a combination of path and wildcard names, and kernel-level expressions.
//      If the application layer and kernel layer expressions do not match, TSKHelp_GetKernelName should be called to translate to the kernel layer expression and combine them.
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_SetCMGlobalIgnore(UINT32 nListVerb,WCHAR * strTemplate);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_SetCMGlobalMust
//Description: Set the current user's control model - global must encrypt list
//Parameters: nListVerb[IN],the list operation verb,no LIST_VERB_MODIFY and LIST_VERB_DEFAULT semantics
//      strTemplate[IN],the template,support *?|wildcard,|Multiple templates connected by logical or semantic parsing (this item is Key)
//Return: INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_NoUser,fail;
//          KError_SyntaxError,fail;
//          KError_MultiObject,fail
//          KError_CantFindObject,fail
//          KError_Other,fail
//Remark: Templates that are set up indicate that encryption is required.
//      The control model-global must encrypt list is responsible for specifying that these files are automatically encrypted when they are accessed by processes in plaintext.
//
//      The template uses a combination of path and wildcard names, and kernel-level expressions.
//      If the application layer and kernel layer expressions do not match, TSKHelp_GetKernelName should be called to translate to the kernel layer expression and combine them.
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_SetCMGlobalMust(UINT32 nListVerb,WCHAR * strTemplate);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_SetCMConfigProcess
//Description: Set the current user's configuration process control model
//Parameters: nListVerb[IN],the list operation verb,no LIST_VERB_MODIFY semantics
//      nProcessType[IN],the process type
//      nCheatLevel[IN],the cheat level
//      bInherit[IN],the inherit Properties,The children of this process will automatically inherit the settings of this process
//      strProcessName,the process name(this item is Key)
//Return: INT32, KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_NoUser,fail;
//          KError_SyntaxError,fail;
//          KError_MultiObject,fail;
//          KError_CantFindObject,fail;
//          KError_Other,fail;
//Remark: The configuration process control model is used for software selected by the user that requires a fixed configuration, specified by the process name.
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_SetCMConfigProcess(UINT32 nListVerb,
					BYTE nProcessType,BYTE nCheatLevel,BOOLEAN bInherit,
					WCHAR * strProcessName);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_SetCMRunProcess
//Description: Set the current user's running process control model
//Parameters: nListVerb[IN],the list operation verb,no LIST_VERB_MODIFY semantics
//      nPID[IN],the process ID(index key)
//      nProcessType[IN],the process type
//      nCheatLevel[IN],the cheat level
//      bInherit[IN],the inherit Properties,The children of this process will automatically inherit the settings of this process
//      strProcessName,the process name
//Return: INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_NoUser,fail;
//          KError_SyntaxError,fail;
//          KError_MultiObject,fail;
//          KError_CantFindObject,fail;
//          KError_Other,fail;
//Remark: The running process control model is mainly generated automatically by the kernel based on the configured process control model.
//      When the application layer initializes the login, there may already be processes running that are registered in the configured process control model, which requires the application layer to call the interface to set up the kernel.
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_SetCMRunProcess(UINT32 nListVerb,
					PROC_ID nPID,BYTE nProcessType,BYTE nCheatLevel,BOOLEAN bInherit,
					WCHAR * strProcessName);

////////////////////////////////////////////////////////////////////////////
//Name: TSK_GetCMRunProcess
//Description: Get the current user's running process control model
//Parameters:  pJitID[OUT],pJitInfoLen[OUT],Running control model report returned via JIT interface
//Return:INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_Other,fail;
//Remark:  
////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" 
#endif
TSK_DECLSPEC INT32 __stdcall TSK_GetCMRunProcess(JIT_ID * pJitID,UINT32 * pJitInfoLen);

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//interface for manual operation of files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Provide file manual operation functions, including file encryption, decryption, sharing and other operations,
// and provide task operation interface to support external control of file operation tasks, including the cancellation of tasks and other operations
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//The encryption operation is done with the public key of the current default identity. Before calling the file operation interface,
//        you must have completed user login, and set the user identity and default identity operation.
//The decryption operation is done with all private keys owned by the current user. Before calling the file operation interface,
//       the user must have completed the user login and set the user's identity.
//The Sharing operation (add or remove identities) are added externally based on the objects of one sharing operation
//
//The file operation interface uses the task mechanism and should first create a file operation task and set the various parameters of the file operation task (including basic parameters, and extended parameters)
//The file operation is a time-consuming operation, which is done asynchronously inside the library using a new thread. During the execution of the file operation, the execution of the file operation can be controlled externally through the task mechanism interface
//The intermediate status information of the file operation and the final result information should be obtained externally by polling the task operation interface, and displaying the corresponding interface prompt information
//The sequence of file operations is as follows:
//    1.Initialize a file operation task: set the basic parameters of a file operation task, including the number of threads corresponding to the task, and the action of the task (encryption/decryption/share)
//    2.Set the task target for a file operation: Set the task targets (files/folders) for a file operation one by one into the W3FS SDK library via the interface
//    3.Set the identity operation action for one file sharing operation: only valid for sharing operation
//    4.Set the signature attribute for one file sharing operation: only valid for sharing operation
//    5.Start a file operation task；
//    6.Get the file operation task status:
//    7.Control file manipulation tasks (e.g. stop tasks)
//    8.Get a report on the results of the file operation task
//    9.Destroy the file operation task
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_FileOpTask_Init
//Description: Initialize a file operation task
//Parameters: nAction[IN],the Action verb，1,encrypt；2，decrypt；3，share
//      nThreadCount[IN]，the task thread count,default value is 1
//Return: Less than 0 means file operation task initialization failed
//        Greater than or equal to 0 means success, the return value is the task ID, and the subsequent operations are indexed by ID
//Remark: Multi-threaded execution on a file-by-file basis
//        The number of multithreads can be set according to the current number of cpu
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC INT32 __stdcall TSK_FileOpTask_Init(INT32 nAction,INT32 nThreadCount);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_FileOpTask_PushAFileToTask
//Description: Add a full path to the file/folder awaiting operation to the specified file operation task
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//      pSrcFullPath[IN]，the source file/folder path
//      pDstFullPath[IN],the target file/folder path
//Return:INT32, KError_Success,success;
//Remark: Multiple files/folders can be processed in a single file operation task
//      This interface can be called multiple times
//      This function is only valid until the task is actually started, when the task state has been started, including when the task is suspended, it is not possible to call this interface again to finish adding the operation target
//
//      pSrcFullPath and pDstFullPath must be not the same path, and pSrcFullPath must be real
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
#ifdef _WIN32
TSK_DECLSPEC INT32 __stdcall TSK_FileOpTask_PushAFileToTask(INT32 nTaskID, WCHAR* pSrcFullPath,WCHAR* pDstFullPath);
#else
TSK_DECLSPEC INT32 __stdcall TSK_FileOpTask_PushAFileToTask(INT32 nTaskID, char* pSrcFullPath, char* pDstFullPath);
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_FileOpTask_PushAAction
//Description: Add a identity to the specified file share task
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//      bDelAdd[IN],the action,true is add,false is delete
//      IID[IN]，the identity ID
//      nPermission,the permission of the identity
//      nLastTime, the identity of the file last used time 
//      pKeyBuf[IN]，the buffer of the identity key
//      nKeyBufLen，the buffer length of the identity key
//Return:INT32, KError_Success,success;
//Remark: This interface is only available for file sharing
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC INT32 __stdcall TSK_FileOpTask_PushAAction(INT32 nTaskID, BOOLEAN bDelAdd,
	BYTE* IID, PermissionInfo nPermission, int nLastTime, BYTE* pKeyBuf, DWORD nKeyBufLen);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_FileOpTask_SetShareSign
//Description: Set a file operation task signature action
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//      nSignAction[IN],the signature action，0 means keep，1 means set，2 means clear
//Return： INT32,KError_Success,success;
//Remark: This interface is only available for file sharing
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC INT32 __stdcall TSK_FileOpTask_SetShareSign(INT32 nTaskID, BYTE nSignAction);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_FileOpTask_StartATask
//Description: Start a file operation task
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//Return:INT32,KError_Success,
//Remark: The Set Parameters interface cannot be called after the task has started. Asynchronous operation, by starting an asynchronous multithread to complete the transaction
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC INT32 __stdcall TSK_FileOpTask_StartATask(INT32 nTaskID);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_FileOpTask_CancelATask
//Description: Stop a file operation task
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//Return: INT32,KError_Success,success
//Remark: The file operation task is an asynchronous multi-threaded operation, the return value of the interface call to abort a task simply returns whether the interface call was successful or not,
//        and the state of the task is based on the result of the TSK_FileOpTask_GetATaskState interface call
//      After the file operation task is cancelled, it cannot be opened again and the TSK_FileOpTask_UnInitATask interface should be called to destroy the task
//      The file operation task is cancelled, the status of the completed operation will not be rolled back, and the task report is obtained through the TSK_FileOpTask_GetATaskReport interface
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC INT32 __stdcall TSK_FileOpTask_CancelATask(INT32 nTaskID);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_FileOpTask_UnInitATask
//Description: Destroy a file operation task
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//Return: INT32,KError_Success,success
//Remark:  Tasks whose status is estimated and in progress are not allowed to be deleted, but have to wait for completion or be actively cancelled before they are allowed to be deleted
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC INT32 __stdcall TSK_FileOpTask_UnInitATask(INT32 nTaskID);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_FileOpTask_GetATaskState
//Description: Get a task state
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//      nTotalLength[IN/OUT]，Total data length (in bytes)
//      nCurrentLength[IN/OUT]，Length of processed data (in bytes)
//      nState[IN/OUT],the task current state，0 wait for start, nTotalLength,nCurrentLength data invalid
//                                        1 Data processing is in progress (estimated data length stage), nTotalLength,nCurrentLength data is invalid
//                                        2 data processing in progress (processing data phase), can use nTotalLength,nCurrentLength to convert the percentage
//                                        3 data processing completed (all data processing successful), nTotalLength,nCurrentLength data invalid
//                                        4 data processing completed (task cancelled), nTotalLength,nCurrentLength data invalid
//Remark: The success of the task status does not mean that the file processing is successful. The file processing result is obtained through TSK_FileOpTask_GetATaskReport
//      Once the task starts, it is recommended that 500ms is acquired in one cycle
//      The conversion percentage has to handle an anomaly where nTotalLength is 0 and nCurrentLength is also 0. For example, the case of encrypting a large batch of empty files
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC INT32 __stdcall TSK_FileOpTask_GetATaskState(INT32 nTaskID,INT32* nState,INT64* nTotalLength,INT64* nCurrentLength);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_FileOpTask_GetATaskReport
//Description: Get a task result report
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//      nReportMode[IN],thr report mode，1Minimalist mode, the result report only returns the total number of files, the number of processed files, the number of successful files, the number of failed files, and the number of ignored files
//                                  2Full mode, the result report includes specific document processing status in addition to returning the contents of the simple mode
//      pReportBuf[OUT],the buffer of the result report
//      nReportBufLength[IN/OUT],the buffer length of the result report
//Remark: The result report is returned as a stream (direct value copy of each element is placed in the memory buffer)
//      An example of a minimalist model report is as follows.
//           4 bytes count+4 bytes success+4 bytes fail+4 bytes ignore
//      An example of a full model report is as follows:
//            bytes count+4 bytes success+4 bytes fail+4 bytes ignore+One by one file operation results
//           The result of a single file operation is packaged into a stream with the following structure
//                4 bytes nAction + 4 bytes nResult + 4 bytes source file full path length (including the length of the trailing 0) + source file full path (including the trailing 0) + 4 bytes target file full path length (including the trailing 0) + target file full path (including the trailing 0), the target file full path may be empty, then the length parsed out to 0, directly read the next field according to the offset can
//      The result of the file operation can be parsed by first parsing the total number of file elements by count, and then parsing the result by memory offset loop
//      The pseudo-code is as follows.
//           INT32 nPos = 0;
//           memcpy(&count,pBuf+nPos,sizeof(INT32));//get the count
//           nPos += sizoef(INT32);
//           memcpy(&success,pBuf+nPos,sizeof(INT32));//get the success
//           nPos += sizeof(INT32);
//           memcpy(&fail,pBuf+nPos,sizeof(INT32));//get the fail
//           nPos += sizeof(INT32);
//           memcpy(&ignore,pBuf+nPos,sizeof(INT32));//get the ignore
//           nPos += sizeof(INT32);
//           for(int i=0;i<count;i++)//Circulation
//           {
//               memcpy(&nAction,pBuf+nPos,sizeof(INT32));//get the nAction
//               nPos += sizeof(INT32);
//               memcpy(&nResult,pBuf+nPos,sizeof(INT32));//get the nResult
//               nPos += sizeof(INT32);
//               memcpy(&nSrcPathLen,pBuf+nPos,sizeof(INT32));//get the nSrcPathLen
//               nPos += sizeof(INT32);
//               memcpy(strSrcPath,pBuf+nPos,nSrcPathLen);//get the strSrcPath
//               nPos += nSrcPathLen;
//               memcpy(&nDstPathLen, pBuf + nPos, sizeof(INT32));//get the nDstPathLen
//               nPos += sizeof(INT32);
//               memcpy(strDstPath,pBuf+nPos,nDstPathLen);//get the strDstPath
//               nPos += nDstPathLen;
//           }
//      If the buffer length is not enough, the call fails and the actual required memory length is returned by nReportBufLength, which can be obtained again by applying for a memory buffer of sufficient length again.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC INT32 __stdcall TSK_FileOpTask_GetATaskReport(INT32 nTaskID, INT32 nReportMode,BYTE* pReportBuf,INT32* nReportBufLength);

//////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_FileOpTask_CanExit
//Description: the file operation module can exit
//Parameters:
//Return: 0 means that there is currently a task being executed and cannot be exited, 1 means that all tasks are currently executed and the program can be exited
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC INT32 __stdcall TSK_FileOpTask_CanExit();

///////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_FileOp_AdjustByFlow
//Description: Adjusts the specified encrypted header stream data by the given identity and related attributes to return the new encrypted header stream data
//Parameters: pHeadFlowSrc[IN],the source head flow
//      nHeadFlowSrcLen[IN],the source head flow length
//      nIID[IN],the identity id
//      nPermission[IN]，the permission of the identity
//      nLastTime[IN],the identity of the file last used time 
//      pKeyBuf[IN],the buffer of the identity key
//      nKeyBufLen[IN],the buffer length of the identity key
//      bAdd[IN],the action of the operation，true add a identity，false delete a identity
//      pHeadFlowDst[OUT],the buffer of the new head flow
//      nHeadFlowDstLen[IN/OUT]，the buffer length of the new head flow
//Return: Reference TSK library return result definition
//        KError_OutOfLength（-3），The ESeal Zone is adjusted successfully, but the length of pHeadFlowDs is not enough, prepare a large enough buffer again, and call again
//Remark: 
//////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC INT32 __stdcall TSK_FileOp_AdjustByFlow(BYTE* pHeadSrc, INT32 nHeadFlowSrcLen, BYTE* pHeadFlowDst, INT32* nHeadFlowDstLen,
	BOOLEAN bDelAdd, BYTE* nIID, PermissionInfo nPermission, int nLastTime, BYTE* pKeyBuf, DWORD nKeyBufLen);

///////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_FileOp_GetESealInfo
//Description: Get all identity information in the eseal area of the specified file
//Parameters: strFilePath[IN],the file path
//      pIdentityIDArray[IN/OUT],An array of identity IDs for all identities in the eseal zone
//      nArrayLength[IN/OUT],Total number of identities in the eseal zone
//Return: Reference TSK library return result definition
//Remark: pIdentityIDArray is a BYTE array pointer, the length should be nArrayLength*IDENTITYID_LENGTH
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
#ifdef _WIN32
TSK_DECLSPEC INT32 __stdcall TSK_FileOp_GetESealInfo(WCHAR* strFilePath, BYTE* pIdentityIDArray,INT32* nArrayLength);
#else
TSK_DECLSPEC INT32 __stdcall TSK_FileOp_GetESealInfo(char* strFilePath, BYTE* pIdentityIDArray, INT32* nArrayLength);
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LocalService Interface
//W3FS Native SDK integrates a HttpLocalSerer module to support the use of http requests to obtain the real data of an encrypted file and to support the senseless decryption of an encrypted file through the browser route in a kernel-less environment.
///////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_LocalServer_Start
//Description:Start the HttpLocalServer module
//Parameters: nPort[IN],The port specified by LocalServer
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC INT32 __stdcall TSK_LocalServer_Start(INT32 nPort);

///////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_LocalServer_Stop
//Description: Stop the HttpLocalServer module
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC void __stdcall TSK_LocalServer_Stop();

///////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_LocalServer_SetSystemTime
//Description: Set the current system time
//Parameters: nTime[IN],the current system time
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC void __stdcall TSK_LocalServer_SetSystemTime(INT32 nTime);

///////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_LocalServer_GetSessionKey
//Description: Get the current random key
//Parameters: :pSessionKey[out],the random key,20 bytes in length
//Remark:SessionKey is a fixed 20-byte length information, used for LocalSever authentication, after the library is started, the current SessionKey must be obtained, and the request to LocalServer must bring the obtained SessionKey.
//     Used by LocalServer to determine if the request is valid
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC bool __stdcall TSK_LocalServer_GetSessionKey(char pSessionKey[20]);

///////////////////////////////////////////////////////////////////////////////////////////////////
//Name: TSK_LocalServer_SetCurrentWebSiteParam
//Description: Set the basic parameters of the current service dapp site
//Parameters: strRootDir[IN],Full path information of the root directory of the current dapp site
//      strDynamicFlag[IN]，Dynamic request identification, LocalServer will use this identification to determine whether to forward the request to the corresponding server, if you want to support the local LocalServer dynamic request forwarding, dapp development process should strictly adhere to their own definition of the request specification
//                      There can be multiple dynamic request identifiers, separated by | signs, such as /d|/api|/opt, localserver requires that the dynamic request identifier must be at the beginning of the requested Uri
//      strRemoteServer[IN],Dynamic request forwarding to remote servers.
//      strIndexFileName[IN],Home page of local dapp, can pass NULL, default use index.html as home page
//      strPemFilePath[IN],If the remote server address is configured as https, the SSL public key of the server should be provided to LocalServer in the form of a standard pem certificate file
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
#ifdef _WIN32
TSK_DECLSPEC void __stdcall TSK_LocalServer_SetCurrentWebSiteParam(WCHAR* strRootDir,WCHAR* strDynamicFlag,WCHAR* strRemoteServer,WCHAR* strIndexFileName,WCHAR* strPemFilePath);
#else
TSK_DECLSPEC void __stdcall TSK_LocalServer_SetCurrentWebSiteParam(char* strRootDir, char* strDynamicFlag, char* strRemoteServer,char* strIndexFileName,char* strPemFilePath);
#endif

#endif
