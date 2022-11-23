/////////////////////////////////////////////////////////////////////////////////////////
//Filename: TSKInterface_GO.h
//Description：W3FS Native SDK library interface description(GO)
//Author：Jason
/////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined(_TSK_INTERFACE_GO_H)
#define _TSK_INTERFACE_GO_H

#ifdef _WIN32
#define TSK_DECLSPEC __declspec(dllexport)
#else
#define TSK_DECLSPEC  __attribute__ ((visibility("default")))
#define __stdcall
#endif

//refer to TSK_Init
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_Init();

//refer to TSK_UnInit
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC void __stdcall TSK_GO_UnInit();

//refer to TSK_DigestCRC32
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_DigestCRC32(unsigned int nFlowLen, unsigned char * pFlow, UINT64* pCookieID, unsigned int * pCRC32);

//refer to TSK_DigestMD5
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_DigestMD5(unsigned int nFlowLen, unsigned char * pFlow, UINT64* pCookieID, unsigned char * pMD5);

//refer to TSK_DigestSha256
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_DigestSha256(unsigned int nFlowLen, unsigned char * pFlow, UINT64* pCookieID, unsigned char * pSHA256);

//refer to TSK_IdentityIssueEx
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_IdentityIssueEx(unsigned char* pSeed, unsigned int nSeedLen, unsigned char* pPublicKeyBuf, unsigned int* nPublicKeyLen, unsigned char* pPrivateKeyBuf, unsigned int* nPrivateKeyLen,unsigned char* pKeyID);

#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_IdentityGetPublicKeyByPrivateKey(unsigned char* pPrivateKeyBuf, unsigned int nPrivateKeyLen, unsigned char* pPublicKeyBuf,unsigned int* nPublicKeyLen);

#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_IdentityGetKeyIDByPublicKey(unsigned char* pPublicKeyBuf, unsigned int nPublicKeyLen, unsigned char* pKeyIDBuf, unsigned int* nKeyIDLen);

//refer to TSK_IdentityEncrypt
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_IdentityEncrypt(void* identity, unsigned char cryptAction,
	unsigned int nSrcFlowLen, unsigned char * pSrcFlow,
	unsigned int nTarFlowLen, unsigned char * pTarFlow,
	unsigned int * pTarFlowReturnLen);

//refer to TSK_IdentityDecrypt
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_IdentityDecrypt(void* identity, unsigned char cryptAction,
	unsigned int nSrcFlowLen, unsigned char * pSrcFlow,
	unsigned int nTarFlowLen, unsigned char * pTarFlow,
	unsigned int * pTarFlowReturnLen);

//refer to TSK_GetCipherDesc
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_GetCipherDesc(unsigned char * pDescBuf, int nDescBufLen);

//refer to TSK_GetCipherInfo
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_GetCipherInfo(unsigned char * tagCipher, unsigned short * pKeyLength, unsigned short * pBlockSize);

//refer to TSK_SetDefaultCipher
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_SetDefaultCipher(unsigned char * tagCipher);

//refer to TSK_SetDefaultZone
#ifdef __cplusplus
extern "C"
#endif
#ifdef _WIN32
TSK_DECLSPEC int __stdcall TSK_GO_SetDefaultZone(signed long long nLen);
#else
TSK_DECLSPEC int  __stdcall TSK_GO_SetDefaultZone(int64_t nLen);
#endif

//refer to TSK_CreateCipherCell
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_CreateCipherCell(unsigned char * tagCipher, unsigned short nKeyLen, unsigned char * pKey);

//refer to TSK_DeleteCipherCell
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_DeleteCipherCell(int nCipherCell);

//refer to TSK_ProcessCipherCell
#ifdef __cplusplus
extern "C"
#endif
#ifdef _WIN32
TSK_DECLSPEC int __stdcall TSK_GO_ProcessCipherCell(int nCipherCell, unsigned char nAction, signed long long nOffset, unsigned int nLength, unsigned char * pFlow);
#else
TSK_DECLSPEC int __stdcall TSK_GO_ProcessCipherCell(int nCipherCell, unsigned char nAction, int64_t nOffset, unsigned int nLength, unsigned char * pFlow);
#endif

//refer to TSK_LoginUser
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_LoginUser(unsigned char* nIdentityID);

//refer to TSK_LogoutUser
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_LogoutUser();

//refer to TSK_SetHoldIdentity
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_SetHoldIdentity(unsigned int nListVerb,
	unsigned char* nIdentityID, unsigned short nPermission, int nLastTime, unsigned char * pKeyBuf, int nKeyLen);

//refer to TSK_FileOpTask_Init
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_FileOpTask_Init(int nAction, int nThreadCount);

//refer to TSK_FileOpTask_PushAFileToTask
#ifdef __cplusplus
extern "C"
#endif
#ifdef _WIN32
TSK_DECLSPEC int __stdcall TSK_GO_FileOpTask_PushAFileToTask(int nTaskID, wchar_t* pSrcFilePath, wchar_t* pDstFilePath);
#else
TSK_DECLSPEC int __stdcall TSK_GO_FileOpTask_PushAFileToTask(int nTaskID, char* pSrcFilePath, char* pDstFilePath);
#endif

//refer to TSK_FileOpTask_PushAAction
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_FileOpTask_PushAAction(int nTaskID, bool bDelAdd,
	unsigned char * IID, unsigned short nPermission, int nLastTime, unsigned char* pKeyBuf, int nKeyBufLen);

//refer to TSK_FileOpTask_SetShareSign
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_FileOpTask_SetShareSign(int nTaskID, unsigned char nSignAction);

//refer to TSK_FileOpTask_StartATask
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_FileOpTask_StartATask(int nTaskID);

//refer to TSK_FileOpTask_CancelATask
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_FileOpTask_CancelATask(int nTaskID);

//refer to TSK_FileOpTask_UnInitATask
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_FileOpTask_UnInitATask(int nTaskID);

//refer to TSK_FileOpTask_GetATaskState
#ifdef __cplusplus
extern "C"
#endif
#ifdef _WIN32
TSK_DECLSPEC int __stdcall TSK_GO_FileOpTask_GetATaskState(int nTaskID, int* nState, long long * nTotalLength, long long * nCurrentLength);
#else
TSK_DECLSPEC int __stdcall TSK_GO_FileOpTask_GetATaskState(int nTaskID, int* nState, int64_t * nTotalLength, int64_t * nCurrentLength);
#endif

//refer to TSK_FileOpTask_GetATaskReport
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_FileOpTask_GetATaskReport(int nTaskID, int nReportMode, unsigned char* pReportBuf, int* nReportBufLength);

//refer to TSK_FileOpTask_CanExit
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_FileOpTask_CanExit();

//refer to TSK_FileOp_AdjustByFlow
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_Go_FileOp_AdjustByFlow(unsigned char* pHeadSrc, int nHeadFlowSrcLen, unsigned char* pHeadFlowDst, int* nHeadFlowDstLen,
	bool bDelAdd, unsigned char* nIID, unsigned short nPermission, int nLastTime, unsigned char* pKeyBuf, int nKeyBufLen);

//refer to TSK_FileOp_GetESealInfo
#ifdef __cplusplus
extern "C"
#endif
#ifdef _WIN32
TSK_DECLSPEC int __stdcall TSK_GO_FileOp_GetESealInfo(wchar_t* strFilePath, unsigned char* pIdentityIDArray, int* nArrayLength);
#else
TSK_DECLSPEC int __stdcall TSK_GO_FileOp_GetESealInfo(char* strFilePath, unsigned char* pIdentityIDArray, int* nArrayLength);
#endif

//refer to TSK_LocalServer_Start
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC int __stdcall TSK_GO_LocalServer_Start(int nPort);

//refer to TSK_LocalServer_Stop
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC void __stdcall TSK_GO_LocalServer_Stop();

//refer to TSK_LocalServer_SetSystemTime
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC void __stdcall TSK_GO_LocalServer_SetSystemTime(int nTime);

//refer to TSK_LocalServer_GetSessionKey
#ifdef __cplusplus
extern "C"
#endif
TSK_DECLSPEC bool __stdcall TSK_GO_LocalServer_GetSessionKey(char pSessionKey[20]);


#endif
