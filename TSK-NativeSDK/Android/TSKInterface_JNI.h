//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Filename:TSKInterface_JNI.h
//Description：W3FS Native SDK library interface description(JNI)
//Author：Jason
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TSKANDROIDV2_TSKINTERFACE_JNI_H
#define TSKANDROIDV2_TSKINTERFACE_JNI_H

#include <jni.h>

//////////////////////////////////////////////////////////////////////////////
//------Initialization Interface------
//To use the W3FS Native SDK library, first call the initialization interface.
//If the initialization fails, the W3FS Native SDK library will not be available.
//No longer need to use the TSK library (usually a software exit), call the reverse initialization interface.
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_Init
//Description: Initialize the W3FS Native SDK library
//Parameters:
//Return: INT32,KError_Success,Success;
//          KError_CantConnectKernel,fail;
//          KError_Other,fail;
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_Init(
        JNIEnv* env,
        jobject /* this */);

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_UnInit
//Description: UnInitialize the W3FS Native SDK library
//Parameters:
//Return:
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT void JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_UnInit(
        JNIEnv* env,
        jobject /* this */);

//////////////////////////////////////////////////////////////////////////////
//------Account Interface------
//User related; the library only supports single account login.
//
//Each identity has an identity ID.
//Each account has more than one identity, but only one identity (representing the person) can represent the user individually.
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_LoginUser
//Description: User Login
//Parameters: nIID[IN],the user's identity ID
//Return: INT32, KError_Success,success;
//          KError_MultiUser,fail;
//          KError_Other,fail;
//Remark:
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_LoginUser(
        JNIEnv* env,
        jobject /* this */,jbyteArray nIID);

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_LogoutUser
//Description: User Logout
//Parameters:
//Return: INT32, KError_Success,success;
//          KError_NoUser,fail;
//          KError_Other,fail;
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_LogoutUser(
        JNIEnv* env,
        jobject /* this */);

//////////////////////////////////////////////////////////////////////////////
//------Data Digest Interface------
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_DigestCRC32
//Description: Data Digest using CRC32 algorithm
//Parameters: nFlowLen[IN],the length of the data
//      pFlow[IN],the data
//      nCookie[IN],the cookie of the Digest process
//Return: Return digest results as a json string
//     Digest start return value {nRet=0,cookie=1000}
//     Digest in progress return value {nRet=0}
//     Digest end return value {nRet=0,nCRC32=1000}
//Remark: CRC32 digest is a high-speed but non-reliable digest algorithm that can be used to verify the W3FS header.
//      This interface performs a joint digest of multiple streams.
//      The cookie will be retrieved at the beginning of the digest and the value will remain unchanged until the end of the digest.
//      It is called as follows:
//      When nFlowLen is 0 and cookie is 0, it means start digest
//      When nFlowLen is not 0 and the cookie is not 0, it means the digest is in progress
//      When nFlowLen is 0 and the cookie is not 0, it means that the digest is over and the final digest result is returned and the digest object is cleared
//
//      INT64 cookie=0;
//      TSK_DigestCRC32(0,NULL,0);
//      TSK_DigestCRC32(nFlowLen,pFlow,cookie);
//      TSK_DigestCRC32(nFlowLen2,pFlow2,cookie);
//      TSK_DigestCRC32(0,NULL,&cookie);
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_DigestCRC32(
        JNIEnv* env,
        jobject /* this */,jint nFlowLen,jbyteArray pFlow,jlong nCookie) ;

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_DigestCRC32Single
//Description: CRC32 single digest of the data stream
//Parameters: nflowlen[IN],the buffer length of data 
//      buffer[IN],the buffer of data
//Return: the result of the CRC32 digest
//Remark: CRC32 digest is a high-speed but non-reliable digest algorithm that can be used to verify the W3FS header.
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_DigestCRC32Single(
        JNIEnv* env,
        jobject /* this */,jint nflowlen,jbyteArray buffer);

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_DigestMD5
//Description: Data Digest using MD5 algorithm
//Parameters: nFlowLen[IN],the length of the data
//      pFlow[IN],the data
//      nCookie[IN],the cookie of the Digest process
//Return: Return digest results as a json string
//     Digest start return value {nRet=0,cookie=1000}
//     Digest in progress return value {nRet=0}
//     Digest end return value {nRet=0,MD5="abcded"} MD5 is the string after base64 encoding, the original length of MD5 code is 16 bytes
//Remark: MD5 digest is a low-speed but reliable digest algorithm that can be used to verify the signature of the file data itself.
//      It is used in the same way as DigestCRC32, except that the final result is received in a 16-byte buffer.
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_DigestMD5(
        JNIEnv* env,
        jobject /* this */,jint nFlowLen,jbyteArray pFlow,jlong nCookie);

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_DigestMD5Single
//Description: MD5 single digest of the data stream
//Parameters: nflowlen[IN],the buffer length of data
//      buffer[IN],the buffer of data
//Return: the result of the MD5 digest
//Remark:
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jbyteArray JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_DigestMD5Single(
        JNIEnv* env,
        jobject /* this */,jint nflowlen,jbyteArray buffer);

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_DigestSha256
//Description: Data Digest using Sha256 algorithm
//Parameters: nFlowLen[IN],the length of the data
//      pFlow[IN],the data
//      nCookie[IN],the cookie of the Digest process
//Return: Return digest results as a json string
////     Digest start return value {nRet=0,cookie=1000}
////     Digest in progress return value {nRet=0}
//     Digest end return value {nRet=0,SHA256="abcded"} SHA256 is the string after base64 encoding, the original length of SHA256 code is 32 bytes
//Remark: SHA256 digest is a reliable digest algorithm that can be used to digest arbitrary data.
//      It is used in the same way as TSK_DigestCRC32, except that the final result is received in a 32-byte buffer.
//
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_DigestSha256(
        JNIEnv* env,
        jobject /* this */,jint nFlowLen,jbyteArray pFlow,jlong nCookie);

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_DigestSha256Single
//Description: SHA256 single digest of the data stream
//Parameters: nflowlen[IN],the buffer length of data
//      buffer[IN],the buffer of data
//Return: the result of the MD5 digest
//Remark:
//Remark: The seeds for file encryption identity generation are generated by the sha256 digest algorithm of the W3FS Native SD library
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jbyteArray JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_DigestSha256Single(
        JNIEnv* env,
        jobject /* this */,jint nflowlen,jbyteArray buffer);

//////////////////////////////////////////////////////////////////////////////
//------Identity(Asymmetric encryption algorithm) Interface------
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_IdentityIssueExBase64
//Description: Generate (issue) an identity object,BASE64 string format
//Parameters: pSeed[IN],the buffer of the seed,must 32-byte buffer
//      nSeedLen[IN]，the length of the sedd,must 32
//Return: Returns a json object string in the following format:
//     {nRet:0,PublicKey:"abcd",PublicKeyLen:78,PrivateKey:"abcd",PrivateKeyLen:112,KeyID:"abcd",KeyIDLen:20}
//     nRet is 0, the interface call is successful, other result values are valid
//     PublicKey,PrivateKey is the key information base64 encoded data，Must be decoded to be usable
//     PublicKeyLen,PrivateKeyLen,the length of the PublicKey and PrivateKey
//     KeyID, the identity ID of the generated key used for file encryption, which is uniquely bound to the identity key
//     KeyID, 20 bytes in length
//Remark: Only ecc 256k1 algorithm is supported
//      If the seed information is specified, the generated identity information will be consistent,
//      and the seed information is required to be 32 bytes long.
//      Can not be specified, will be randomly issued ID certificate
//      The public key can be derived from the private key
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_IdentityIssueExBase64(
        JNIEnv* env,
        jobject /* this */,jbyteArray pSeed,jint nSeedLen);

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_IdentityIssueGetPrivateKey
//Description: Generate (issue) an identity object
//Parameters: pSeed[IN],the buffer of the seed,must 32-byte buffer
//      nSeedLen[IN]，the length of the sedd,must 32
//Return: the privatekey
//Remark: Get the corresponding public key and call the GetPublicKeyByPrivateKey interface with the returned private key.
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jbyteArray JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_IdentityIssueGetPrivateKey(
        JNIEnv* env,
        jobject /* this */ ,jbyteArray pSeed,jint nSeedLen);

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_IdentityGetPublicKeyByPrivateKey
//Description: Deriving the public key from the private key
//Parameters: pPrivateKey[IN],the buffer of the private key
//      nPrivateKeyLen[IN]，the buffer length of the privatekey
//Return: the publickey
//Remark:
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jbyteArray JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_IdentityGetPublicKeyByPrivateKey(
        JNIEnv* env,
        jobject /* this */ ,jbyteArray pPrivateKey,jint nPrivateKeyLen);

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_IdentityGetKeyIDByPublicKey
//Description: Deriving the identity id from the public key
//Parameters: pPublicKey[IN],the buffer of public key
//      nPublicKeyLen[IN]，the buffer length of public key
//Return: the identity id,20 bytes length
//Remark:
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jbyteArray JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_IdentityGetKeyIDByPublicKey(
        JNIEnv* env,
        jobject /* this */ ,jbyteArray pPublicKey,jint nPublicKeyLen);

//////////////////////////////////////////////////////////////////////////////
//------Login user's holding identity interface------
//User-related; since only one user can be logged in, it will be automatically processed as the current user.
//
//Each identity has an identity ID.
//
//In the W3FS Encrypt Head,The signer used to describe the file in the signature verification area is described by the internal ID of the signer (user or group) identity.
////In the W3FS Encrypt Head,The explicit description of the specific permissions of the file is also described by the internal ID of each identity in the Eseal Zone.
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
//Name: Java_io_W3FS_tskandroidv2_TSKJni_SetHoldIdentity
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
extern "C" JNIEXPORT jint JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_SetHoldIdentity(
        JNIEnv* env,
        jobject /* this */,jint nListVerb,jbyteArray nIdentityID,jshort nPermissionInfo,jint nLastTime,jbyteArray pKeyBuf,jint nKeyBufLen );

//////////////////////////////////////////////////////////////////////////////
//------Symmetric encryption algorithm interface------
//Symmetric algorithm for data encryption and decryption of files.
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_GetCipherDesc
//Description: Get all currently loaded algorithms
//Parameters:
//return: Return a description report of all symmetric encryption algorithms supported by the library for data encryption
//     The json format is returned in the following format:
//     [{tag:xxx,name:xxx,desc:xxxx},...]
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_GetCipherDesc(
        JNIEnv* env,
        jobject /* this */);

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_GetCipherInfo
//Description: Get information about the specified algorithm
//Parameters: strciphertag[IN],the tag,can be NULL,get the default item
//Return: he json format is returned in the following format:
//     {nRet:0,pKeyLength:16,pBlockSize:1}
//     nRet is 0 for other fields to be valid, pKeyLength returns the length (in bytes) of the secret key required by the algorithm
//      pBlockSize returns the group size required by the algorithm (in bytes, the sequence algorithm returns 1)
//Remark: This interface can be used to determine the secret key size and group size of the algorithm when constructing the stream processing object.
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_GetCipherInfo(
        JNIEnv* env,
        jobject /* this */,jstring strciphertag);

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_SetDefaultCipher
//Description: set the default algorithm
//Parameters: strciphertag[IN],the tag of algorithm
//Return: INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_CipherError,fail;
//          KError_Other,fail;
//Remark:
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_SetDefaultCipher(
        JNIEnv* env,
        jobject /* this */,jstring strciphertag);

////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_SetDefaultZone
//Description: set the default encrypt zone length
//Parameters: nLen[IN],the length of encrypt zone(in bytes)
//Return: INT32,KError_Success,success;
//          KError_CantConnectKernel,fail;
//          KError_Other,fail;
//Remark: Encrypt all data in a file by default
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_SetDefaultZone(
        JNIEnv* env,
        jobject /* this */,jlong nLen) ;

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
////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskInit
//Description: Initialize a file operation task
//Parameters: nAction[IN],the Action verb，1,encrypt；2，decrypt；3，share
//      nThreadCount[IN]，the task thread count,default value is 1
//Return: Less than 0 means file operation task initialization failed
//        Greater than or equal to 0 means success, the return value is the task ID, and the subsequent operations are indexed by ID
//Remark: Multi-threaded execution on a file-by-file basis
//        The number of multithreads can be set according to the current number of cpu
/////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskInit(
        JNIEnv* env,
        jobject /* this */,jint nAction,jint nThreadCount);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskPushAFileToTask
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
extern "C" JNIEXPORT jint JNICALL
        Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskPushAFileToTask(
                JNIEnv* env,
                jobject /* this */,jint nTaskID, jstring strSrcFilePath,jstring strDstFilePath);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskPushAAction
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
extern "C" JNIEXPORT jint JNICALL
        Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskPushAAction(
                JNIEnv* env,
                jobject /* this */,jint nTaskID, jboolean bDelAdd,
                jbyteArray IID, jshort nPermission, jint nLastTime, jbyteArray pKeyBuf, jint nKeyBufLen);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskSetShareSign
//Description: Set a file operation task signature action
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//      nSignAction[IN],the signature action，0 means keep，1 means set，2 means clear
//Return： INT32,KError_Success,success;
//Remark: This interface is only available for file sharing
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
        Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskSetShareSign(
                JNIEnv* env,
                jobject /* this */,jint nTaskID, jbyte nSignAction);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskStartATask
//Description: Start a file operation task
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//Return:INT32,KError_Success,
//Remark: The Set Parameters interface cannot be called after the task has started. Asynchronous operation, by starting an asynchronous multithread to complete the transaction
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
        Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskStartATask(JNIEnv* env,
                                                               jobject /* this */,jint nTaskID);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskCancelATask
//Description: Stop a file operation task
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//Return: INT32,KError_Success,success
//Remark: The file operation task is an asynchronous multi-threaded operation, the return value of the interface call to abort a task simply returns whether the interface call was successful or not,
//        and the state of the task is based on the result of the TSK_FileOpTask_GetATaskState interface call
//      After the file operation task is cancelled, it cannot be opened again and the TSK_FileOpTask_UnInitATask interface should be called to destroy the task
//      The file operation task is cancelled, the status of the completed operation will not be rolled back, and the task report is obtained through the TSK_FileOpTask_GetATaskReport interface
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
        Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskCancelATask(JNIEnv* env,
                                                                jobject /* this */,jint nTaskID);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskUnInitATask
//Description: Destroy a file operation task
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//Return: INT32,KError_Success,success
//Remark:  Tasks whose status is estimated and in progress are not allowed to be deleted, but have to wait for completion or be actively cancelled before they are allowed to be deleted
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskUnInitATask(JNIEnv* env,
                                                        jobject /* this */,jint nTaskID);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskGetATaskState
//Description: Get a task state
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//Return: The return value is passed as a json string，e.g.{nRet:0,nState:0,nTotalLength:1000,nCurrentLength:900},
//      nTotalLength and nCurrentLength are 64-bit integers, in bytes
//      nRet, the return value, only for KError_Success, the other fields are valid, otherwise the function call failed
//      nTotalLength, the total data length of the file operation task (in bytes)
//      nCurrentLength, the length of processed data (in bytes)
//      nState, the current state of the task, 0 to be started, nTotalLength,nCurrentLength data is invalid
//                                        1 Data processing is in progress (estimated data length stage), nTotalLength,nCurrentLength data is invalid
//                                        2 Data processing in progress (processing data phase)
//                                        3 data processing completed (all data processing successful), nTotalLength,nCurrentLength data invalid
//                                        4 data processing completed (active cancellation), nTotalLength,nCurrentLength data invalid
//Remark: The success of the task status does not mean that the file processing is successful. The file processing result is obtained through TSK_FileOpTask_GetATaskReport
//      Once the task starts, it is recommended that 500ms is acquired in one cycle
//      The conversion percentage has to handle an anomaly where nTotalLength is 0 and nCurrentLength is also 0. For example, the case of encrypting a large batch of empty files
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
        Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskGetATaskState(JNIEnv* env,
                                                                  jobject /* this */,jint nTaskID);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskCanExit
//Description: the file operation module can exit
//Parameters:
//Return: 0 means that there is currently a task being executed and cannot be exited, 1 means that all tasks are currently executed and the program can be exited
////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskCanExit(JNIEnv* env,
                                                         jobject /* this */);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskGetATaskReport
//Description: Get a task result report
//Parameters: nTaskID[IN],the task id,returned by TSK_FileOpTask_Init
//      nReportMode[IN],thr report mode，1Minimalist mode, the result report only returns the total number of files, the number of processed files, the number of successful files, the number of failed files, and the number of ignored files
//                                  2Full mode, the result report includes specific document processing status in addition to returning the contents of the simple mode
//Return: The return value is passed as a json string，
//      e.g.:
//     Minimalist mode:{ret:0,count：10，success：4，fail:1,ignore:5}
//     Full mode:{ret:0,count：10，success：4，fail:1,ignore:5,
//                   filelist:[{srcpath：c:\\1.txt,dstpath：d:\\1.txt,action:1,result：0}.。。]}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
        Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskGetATaskReport(JNIEnv* env,
                                                                   jobject /* this */,jint nTaskID, jint nReportMode);

///////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskAdjustByFlow
//Description: Adjusts the specified encrypted header stream data by the given identity and related attributes to return the new encrypted header stream data
//Parameters: pHeadFlowSrc[IN],the source head flow
//      nHeadFlowSrcLen[IN],the source head flow length
//      nIID[IN],the identity id
//      nPermission[IN]，the permission of the identity
//      nLastTime[IN],the identity of the file last used time
//      pKeyBuf[IN],the buffer of the identity key
//      nKeyBufLen[IN],the buffer length of the identity key
//      bAdd[IN],the action of the operation，true add a identity，false delete a identity
//Return: Return the serialized binary memory result：
//      The memory structure is as follows:4-byte operation result(ret)+4-byte new header data length(nHeadFlowDstLen)+header data(pHeadFlowDst)
//      The returned memory array should be parsed according to the format, and only if ret is KError_Success does the data that follows make sense
//////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jbyteArray JNICALL
        Java_io_W3FS_tskandroidv2_TSKJni_FileOpTaskAdjustByFlow(
                JNIEnv* env,
                jobject /* this */,jbyteArray pHeadSrc, jint nHeadFlowSrcLen,
                                            jboolean bDelAdd, jbyteArray  nIID, jshort nPermission, jint nLastTime, jbyteArray pKeyBuf, jint nKeyBufLen);

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_FileOpGetESealInfoByPath
//Parameters: Get all identity information in the eseal area of the specified file
//Parameters: strFilePath[IN],the file path
//Return: Returns an array of all identity IDs in the ESeal section of the file, 20 bytes per identity ID
///////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jbyteArray JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_FileOpGetESealInfoByPath(
        JNIEnv* env,
        jobject /* this */,jstring strFilePath);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LocalService Interface
//W3FS Native SDK integrates a HttpLocalSerer module to support the use of http requests to obtain the real data of an encrypted file and to support the senseless decryption of an encrypted file through the browser route in a kernel-less environment.
///////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_LocalServerStart
//Description:Start the HttpLocalServer module
//Parameters: nPort[IN],The port specified by LocalServer
////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
        Java_io_W3FS_tskandroidv2_TSKJni_LocalServerStart(JNIEnv* env,
                                                          jobject /* this */,jint nPort);

///////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_LocalServerStop
//Description: Stop the HttpLocalServer module
////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_LocalServerStop(JNIEnv* env,
                                                 jobject /* this */);

///////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_LocalServerSetSystemTime
//Description: Set the current system time
//Parameters: nTime[IN],the current system time
////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
        Java_io_W3FS_tskandroidv2_TSKJni_LocalServerSetSystemTime(JNIEnv* env,
                                                                  jobject /* this */,jint nTime);

///////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_LocalServerGetSessionKey
//Description: Get the current random key
//Parameters:
//Return:the random key
//Remark:SessionKey is a fixed 20-byte length information, used for LocalSever authentication, after the library is started, the current SessionKey must be obtained, and the request to LocalServer must bring the obtained SessionKey.
//     Used by LocalServer to determine if the request is valid
////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
        Java_io_W3FS_tskandroidv2_TSKJni_LocalServerGetSessionKey(JNIEnv* env,
                                                                  jobject /* this */);

///////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Java_io_W3FS_tskandroidv2_TSKJni_LocalServerSetCurrentDappParam
//Description: Set the basic parameters of the current service dapp site
//Parameters: strRootDir[IN],Full path information of the root directory of the current dapp site
//      strDynamicFlag[IN]，Dynamic request identification, LocalServer will use this identification to determine whether to forward the request to the corresponding server, if you want to support the local LocalServer dynamic request forwarding, dapp development process should strictly adhere to their own definition of the request specification
//                      There can be multiple dynamic request identifiers, separated by | signs, such as /d|/api|/opt, localserver requires that the dynamic request identifier must be at the beginning of the requested Uri
//      strRemoteServer[IN],Dynamic request forwarding to remote servers.
//      strIndexFileName[IN],Home page of local dapp, can pass NULL, default use index.html as home page
//      strPemFilePath[IN],If the remote server address is configured as https, the SSL public key of the server should be provided to LocalServer in the form of a standard pem certificate file
////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_W3FS_tskandroidv2_TSKJni_LocalServerSetCurrentDappParam(JNIEnv* env,
                                                          jobject /* this */,jstring strDappRootDir,jstring strDynamicFlag,jstring strRemoteServer,jstring strIndexFileName,jstring strPemFilePath);
#endif

