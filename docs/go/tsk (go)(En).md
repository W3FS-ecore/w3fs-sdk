# Introduction

 	The APP development team and developers can directly learn and understand the W3FS underlying protocol, and complete the development of NativeApp by integrating the W3FS underlying Native SDK. Readers can read this development manual to understand all the interfaces open to the outside world by the W3FS underlying SDK, as well as the interface descriptions, and complete the development of Native APPs that conform to the W3FS protocol specifications.

​	W3FS-SDK is developed in C++ language and provides full platform support, including Windows, Linux, Android, iOS, Mac Operation systems.

​	W3FS-SDK uses the standard function export method of each platform to export the external interface, which can be called directly by external languages that support calling c++ modules.

​	The W3FS-SDK library also provides corresponding support for some language which does not support calling C++ modules directly. For example, for JAVA language development, the W3FS-SDK library provides special JNI interface  to support. W3FS-SDK also provides corresponding support for languages that do not support C++ specific features, such as GO language. If the development language you use has obstacles to call the W3FS-SDK library, please contact the W3FS development team, and we will develop and support  it. There will be separate SDK documentation for each language, which you can refer to accordingly.

## **API list**

### **Basic interface**

#### **TSK_Init**

Initialize the W3FS-SDK Native library.

Function prototype: 

``` c
TSK_Init() int
```

Parameters:

* none

return value:

* INT32:
   KError_Success success
   KError_CantConnectKernel, failed, unable to connect to the W3FS file system kernel (only valid for Native dapp development).
   KError_Other, failed, other errors;

Important Notes:

​	The TSK_Init interface is the W3FS-SDK initialization interface. All NativeApps that load the W3FS-SDK library should call the TSK_Init interface when the App is started or initialized . The other API calls of the W3FS-SDK library depend on the successful call of the TSK_Init interface.

#### **TSK_UnInit**

Reverse initialization of W3FS-SDK Native library

Function prototype:

``` c
TSK_UnInit() 
```

Parameters:

* none

return value:

* none

illustrate:

​	Dapp needs to call the TSK_UnInit interface to complete the reverse initialization of the W3FS Native SDK library when the program exits, so that the W3FS Native SDK library can clean up and release all occupied system resources.

### **Digest interface**


​	The W3FS-SDK library provides a variety of digest interfaces, such as fast CRC digest, secure MD5 and SHA256 digest algorithms. The W3FS-SDK library uses the MD5 digest internally to sign the required encrypted digital files. Data can be digested externally by using the digest interface provided by the W3FS-SDK library.


​	W3FS-SDK digests externally specified data through a unified data stream digest method, and supports multiple external calls to digest algorithms to jointly digest a piece of super-long data. The same digest process is identified by a specified cookie. A typical digest process is as follows:

​	Joint digests of multiple streams are supported with digest cookie pointer not NULL.
The cookie is obtained when the digest is started, and the value remains unchanged until the digest is ended.
​	In short, the judgment is based on: when the stream pointer is empty, it means the start of the digest or the end of the digest;
​	When the stream pointer is not null, the stream is digested.
​	When the stream pointer is empty, it is the start digest if the value in pCookie is also NULL, and the end digest if the value in pCookie is not NULL.


Taking the CRC digest algorithm as an example, the typical usage is as follows:

1. Call TSK_DigestCRC32(0, NULL, pCookie) to start the digest: the streams (nFlowLen and pFlow) are specified as null (nFlowLen is 0, pFlow is NULL), the digest cookie pointer (pCookie) is not NULL, where the stored cookie is 0, the interface will return a cookie to this pointer after success, and the digest result pointer (pCRC32) is specified as NULL, which means that the digest algorithm is initialized and is ready to start a unified joint digest of multiple streams.
2. Call TSK_DigestCRC32(nFlowLen, pFlow, pCookie) for each stream to indicate the digest: The stream (nFlowLen and pFlow) specifies a specific stream digest, the cookie pointer (pCookie) is not NULL, where the stored digest cookie is the digest obtained in step 1 , the cookie digest result pointer (pCRC32) is specified as NULL, which means that the digest algorithm will digest the specified stream.
3. Call TSK_DigestCRC32(0, NULL, pDigestID) to end the digest and receive the result: the streams (nFlowLen and pFlow) are specified as empty (nFlowLen is 0, pFlow is NULL), and the digest cookie pointer (pCookie) is not NULL, where The stored digest cookie is the digest cookie obtained in step 1, and the digest result pointer (pCRC32) is not NULL, which means that the digest algorithm is terminated and the current (final) digest result is returned.

#### **TSK_DigestCRC32**

Iterative support for CRC32 digests of multiple streams

function prototype:

```` c
TSK_DigestCRC32(nFlowLen uint, pFlow []byte, pCookie uint64) (uint, int) 
````

Parameters:

* nFlowLen: is to specify the size of the stream for which the CRC32 digest is to be calculated [IN]
* pFlow: is to specify the stream for which the CRC32 digest is to be calculated [IN]
* pCookie: specify the cookie needed for iteration [IN/OUT]

return value:

- pCRC32: padded with the final result of the iterative digest, a 32-bit CRC32 value [OUT]

* KError_Success, success
* KError_Other, failed, other errors

illustrate:

CRC32 digest is a high-speed but unreliable digest algorithm that can be used to verify data that is used frequently.

#### **TSK_DigestMD5**

Iterative support for MD5 algorithm digests over multiple streams

function prototype:

```` c
TSK_DigestMD5(nFlowLen uint, pFlow []byte, pCookie uint64) ([]byte, int) 
````

Parameters:

* nFlowLen: is to specify the size of the stream for which the MD5 digest is to be calculated [IN]
* pFlow: is to specify the stream for which the MD5 digest is to be calculated [IN]
* pCookie: specify the cookie needed for iteration [IN/OUT]

return value:

- pMD5: filled with the final result of the iteration digest, as a 16-byte array [OUT]

* KError_Success, success
* KError_Other, failed, other errors

illustrate:

MD5 digest is a slow but reliable digest algorithm

#### **TSK_DigestSha256**

​	Iterative support for SHA256 algorithm digests over multiple streams

function prototype:

```` c
TSK_DigestSha256(priAddresslen uint, bytePriAddress []byte, pCookie uint64) ([]byte, int)
````

Parameters:

* nFlowLen: is to specify the size of the stream for which the SHA256 digest is to be calculated [IN]
* pFlow: is to specify the stream for which the SHA256 digest is to be calculated [IN]
* pCookie: specify the cookie needed for iteration [IN/OUT]

return value:

- pSHA256: The final result filled with the iterative digest, as a 32-byte array [OUT]

* KError_Success, success
* KError_Other, failed, other errors

illustrate:

​	SHA256 digest is a reliable digest algorithm that can be used for signature verification of arbitrary data.

### **Identity Algorithm (Asymmetric Encryption Algorithm) Interface**

The W3FS-SDK library uses the ECC256 elliptic curve encryption algorithm by default as the asymmetric encryption algorithm in the electronic envelope mode. The selected curve is the standard SECP256K1 parameter. The detailed parameters are as follows:

* prime：FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F
* A：0000000000000000000000000000000000000000000000000000000000000000
* B：0000000000000000000000000000000000000000000000000000000000000007
* order：FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141
* Gx：79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798
* Gy：483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8

#### **TSK_IdentityIssueEx**

Generate (issue) an identity object and directly return the keystream form to the outside

function prototype:

```` c
TSK_IdentityIssueEx(pSeed []byte) ([]byte, []byte, []byte, int) 
````

Parameters:

* pSeed: The seed information of the specified identity key information [IN]

return value:

* pPublicKeyBuf: identity public key information data stream [IN/OUT]
* pPrivateKeyBuf: identity private key information data stream [IN/OUT]
* pKeyID: identity key ID, fixed 20 bytes [IN/OUT]

* KError_Success, success
* KError_Other, failed, other errors

illustrate:

The function of TSK_IdentityIssueEx is the same as that of TSK_IdentityIssue. The difference is that it returns the binary stream of public and private keys that can be directly parsed and saved externally. Externally, the TSK_IdentityIssueEx interface can be used to obtain the public and private key data of the identity key and save it directly or do other processing.
In the design of the W3FS-SDK library, the buffer memory is prepared in advance by the external program, and is passed to the W3FS-SDK library together with the buffer length information. The W3FS-SDK library operates directly on the externally prepared buffer. , the release of the buffer is also the responsibility of the external program itself.

### **Symmetric encryption algorithm interface**


​	W3FS-SDK adopts the standard electronic envelope mode to protect digital files in the whole life cycle, uses symmetric encryption algorithm for file data, and uses a random key in the form of one-text-one-cipher encryption. For the random key of the symmetric encryption algorithm, use the public key of the asymmetric algorithm that represents the user's identity to encrypt it, and the encrypted data is called an eseal structure, which is stored in the eseal identity area of the file encryption header. When users use encrypted files, they must first try to decrypt each eseal structure in the eseal identity area with the private key of their own identity. After the encryption is successful, the random key of the symmetric algorithm used to encrypt the real file can be obtained. Finally get the real data of the file.

​	The electronic envelope mechanism of W3FS-SDK organically combines the high efficiency of symmetric encryption algorithm and the high security of asymmetric encryption algorithm to provide users with a high-efficiency and high-security data life-cycle protection scheme.

​	The symmetric encryption algorithm management module of the W3FS-SDK library is designed with scalable components. The library integrates AES256, DES3, GOST, MARS, SEAL and other common symmetric encryption algorithms by default to encrypt file data. APP developers or users can choose the symmetric encryption algorithm according to their needs and preferences. In addition, the W3FS-SDK library also supports adding more symmetric encryption algorithms to the library to provide users with more choices.

#### **TSK_GetCipherDesc**

​	Get all currently loaded algorithm descriptions

function prototype:

```` c
TSK_GetCipherDesc(pSrcFlow []byte, nDescBufLen int) int 
````

Parameters:

* pDescBuf, an externally prepared buffer for receiving reports, it is recommended to apply for an 8K (8192) byte length buffer for the first time [IN/OUT]
* nDescBufLen, the buffer length prepared externally to receive the report, the recommended first length is 8192 bytes [IN]

return value:

* Returns the actual length of the report. If the return value is greater than the buffer length passed in from the outside, no operation will be performed on the buffer, and the outside needs to re-apply for a buffer large enough according to the actual length, and obtain it again

illustrate:

​	On the application layer interface, the loaded algorithm is obtained and displayed through this interface.

The returned data is a collection of description information of all symmetric encryption algorithms supported by the TSK platform. The main format is as follows

​	Total number of symmetric encryption algorithms supported: UINT32 data of 4 bytes length

* The first encryption algorithm description
  The 16-byte encryption algorithm tag identifier is used to uniquely identify an algorithm, and subsequent interfaces use this tag to represent the algorithm
  Algorithm name string, unlimited length, with the final trailing 0 of the string as the end identifier
  The algorithm describes the information string in one sentence, with unlimited length, with the final trailing 0 of the string as the end identifier
* Description of the second encryption algorithm
  The 16-byte encryption algorithm tag identifier is used to uniquely identify an algorithm, and subsequent interfaces use this tag to represent the algorithm
  Algorithm name string, unlimited length, with the final trailing 0 of the string as the end identifier
  The algorithm describes the information string in one sentence, with unlimited length, with the final trailing 0 of the string as the end identifier
* More encryption algorithm descriptions


​	Through the TSK_GetCipherDesc interface, the list of all symmetric encryption algorithms supported by the current W3FS-SDK library can be obtained externally. It is more often used for interface display, and all currently supported algorithms are listed and displayed, so that users can choose the encryption algorithm to be used.

#### **TSK_GetCipherInfo**

​	Get the specified algorithm details

function prototype:

```` c
TSK_GetCipherInfo(tagCipher []byte, pKeyLength int16, pBlockSize int16 ) int
````

Parameters:

* tagCipher is the algorithm tag to be obtained (that is, the GUID label of the algorithm), which is fixed to 16 bytes; this parameter can be NULL, indicating that the default algorithm is specified; [IN]

* pKeyLength returns the key length (in bytes) required by the algorithm [IN/OUT]
* pBlockSize is the block size required by the algorithm (calculated in bytes, so the sequence algorithm returns 1) [IN/OUT]

return value:

* KError_Success, success;
* KError_CipherError, failed, the algorithm could not be found;
* KError_Other, other errors, usually memory allocation errors (or insufficient buffers);

illustrate:
	The application layer can use this interface to determine the key size and packet size of the algorithm when constructing the stream processing object.
It can also be used for interface display to display the detailed information of an encryption algorithm.

#### **TSK_SetDefaultCipher**

Set the current default algorithm

function prototype:

```` c
 TSK_SetDefaultCipher(tagCipher []byte) int 
````

Parameters:

* tagCipher is the algorithm tag to be obtained (that is, the GUID label of the algorithm), which is fixed to 16 bytes; this parameter can be NULL, indicating that the default algorithm is specified; [IN]

return value:

* KError_Success, success;
* KError_CipherError, failed, the algorithm could not be found;
* KError_Other, other errors, usually memory allocation errors (or insufficient buffers);

illustrate:
The default algorithm is set through this interface on the application layer interface.

If the specified algorithm tag is NULL during encryption, the default algorithm will be used for encryption.

The default encryption algorithm set by the upper layer is valid for a single startup. After exiting the W3FS-SDK library, the user's settings will be restored after restarting. Therefore, if the external APP needs to use this function, it can record the user's settings, active call to set the default algorithm when started again.



### Account interface

User related; the library only supports single one account to login.

Each identity has a unique 20-byte identity ID, which can be generated externally to meet W3FS-SDK requirements through a specific algorithm at the time of user generation.

Each account may have multiple identities, but only one can represent the user identity of the account (representing this person).

In the W3FS protocol, identity is a very special concept. Identity is separate from account, and account represents a user. In simple terms, identity is the authority that a user has. For example, for example, a user joins group A, community B, and uses an application C. Then this user should be visible to all group A, community B, application C's internal encrypted files, and the user's own private files. Therefore, this user has at least 4 identities. Correspondingly, it can be said that the user has at least the keys of the asymmetric encryption algorithms corresponding to these 4 identities. You can use the keys of these identities to try to decrypt the encrypted files belonging to these identities. The user can then use these encrypted files.

However, when the user logs in, the user's own identity is used to log in to the W3FS-SDK library, and other identities are configured to the user through the application's own management.

#### **TSK_LoginUser**

* Login account

  function prototype:

  ```` c
  TSK_LoginUser(userid []byte) int 
  ````

  Parameters:

  * nIdentityID is the corresponding internal ID representing the unique identity of the user

  return value:

  * KError_Success, success;
  * KError_MultiUser, failed, there are other login users;
  * KError_Other, other errors, usually memory allocation errors (or insufficient buffers);
#### **TSK_LogoutUser**

* log out of current account

  function prototype:

  ```` c
  TSK_LogoutUser() int
  ````

  Parameters:

  * none

  return value:

  * KError_Success, success;
#### **TSK_SetHoldIdentity**

Set the identity held by the current user of the W3FS-SDK library

function prototype:

```` c
TSK_SetHoldIdentity(nListVerb int, nIdentityID []byte, nPermission int16, pKeyBuf []byte, nKeyLen int) int 
````

Parameters:

* nListVerb is a standard list manipulation verb, no LIST_VERB_MODIFY semantics [IN]
* nIdentityID is the ID of this identity [IN]
* nPermission is the permission corresponding to the identity, the identity held by the user has all permissions by default, and needs to be set externally [IN]
* pKeyBuf is the key binary format information of the identity, byte unit [IN]
* nKeyLen is the length of the key binary format information of the identity, in bytes [IN]

return value:

* KError_Success, success;
* KError_NoUser, failed, there is no currently logged in user;
* KError_SyntaxError, failure, syntax error (such as unsupported verb, etc.);
* KError_MultiObject, failure, semantic error, the Key already exists (the identity ID already exists);
* KError_CantFindObject, failure, semantic error, delete the key that does not exist (the identity ID does not exist);
* KError_Other, other errors, usually memory allocation errors (or insufficient buffers);

illustrate:

The W3FS-SDK library uses a linked list structure for user identity management, and external user identity operations are essentially various operations on the management linked list.

The identity held by the former user is a list, which is usually managed by LIST_VERB_CLEAR/LIST_VERB_ADD/LIST_VERB_DELETE.

When LIST_VERB_ADD all parameters obviously need to be supplied.

When LIST_VERB_DELETE, the parameter obviously only needs to provide nIdentityID.

LIST_VERB_DEFAULT is to set user identity;

When wishing to set (or change) a default identity, the identity should already be in the list of held identities, so the parameter only needs to provide nIdentityID.

When you want to clear the default identity, you should specify nIdentityID as IDENTITY_NULL, and other parameters do not need to be provided.

```` c
//The actions of nListVerb are defined as follows:
#define LIST_VERB_DEFAULT 1 //Set the default default behavior
#define LIST_VERB_CLEAR 2 //Clear the match list
#define LIST_VERB_ADD 3 //Add matching items
#define LIST_VERB_DELETE 4 //Delete matches
#define LIST_VERB_MODIFY 5 //Modify matches
````


The PermissionInfo structure is the definition of identity permissions by the W3FS-SDK library. In essence, a 2-byte integer is used to represent the permissions owned by an identity. Currently, the W3FS-SDK library defines the following two permissions:

```` c
typedef struct _PermissionInfo{
    UINT16 bOwner : 1;//Whether it is Owner: 0 means non-Owner, 1 means Owner
    UINT16 bAdjust : 1;//Whether it has distribution permission: 0 means no, 1 means yes.
    }PermissionInfo, *PPermissionInfo;
````

In the W3FS-SDK library, bOwner means that the user is the owner of the encrypted digital file, and has all permissions to the encrypted digital file, including file reading, writing, sharing, decryption, etc.

Other non-Owner identities have only read access to encrypted digital files.

bAdjust is a special permission that allows identities with this permission to share encrypted files. That is, it has the right to add another identity to the ESeal identity area of the encrypted digital file to construct a new ESeal structure, and also has the right to delete or modify the eseal structure in the existing ESeal identity area.

In language development that does not support structures, you can simply pass in a 2-byte integer as a permission. -1 means the identity has all permissions, 1 means Owner permissions, 2 means share permissions.

#### **TSK_SetDefaultZone**

Set default encrypted paragraphs(zone)

function prototype:

```` c
TSK_SetDefaultZone(nLen int64) int 
````

Parameters:

* nLen is the size (byte count) of the default encrypted paragraph to set [IN]

return value:

* KError_Success, success;
* KError_Other, other errors, usually memory allocation errors (or insufficient buffers);

illustrate:

The default encrypted paragraph is fixed from the file header to the specified size of the file paragraphs.

The paragraph size is 0, which is effectively equal to unencrypted; the paragraph size is -1, which is effectively equal to encrypting the entire file.

Specifying the default encryption section is not necessary in some scenarios , but it is necessary in scenarios that require the library to automatically perform certain encryption and decryption actions (such as automatic file system encryption and decryption).

Paragraph encryption is W3FS-SDK's special support for file encryption. By default, W3FS-SDK's encryption of digital files is full-text encryption, that is, re-encoding and encryption according to the specified algorithm is performed on all data of the file.

But the outside can set the paragraph encryption configuration according to the needs, so that the W3FS-SDK can be more efficient in the process of encrypting or decrypting the file data. The basis of paragraph encryption is that almost all formats of digital files currently have format requirements for file data. By encrypting the data with a specified length starting from the file header, it is possible to re-encode only a part of the data, which can destroy the application software's requirements for the data file format. It is recommended that if you use the paragraph encryption function provided by W3FS-SDK, the paragraph configuration should not be less than 1MB, or should be even higher to achieve more security.

### **File operation task module interface**

The W3FS-SDK library provides digital file encryption, decryption and sharing function interfaces.

In the W3FS-SDK library, file encryption includes actively changing a file from an unencrypted state to a secure encrypted state by calling the file task operation interface. And the W3FS-SDK real-time file system kernel encrypts a file through sensorless encryption according to the configured rules.

Correspondingly, file decryption includes externally calling the file task operation interface to actively decrypt an encrypted file into an unencrypted plaintext state, as well as W3FS-SDK real-time file system kernel driver and W3FS LocalServer module to decrypt file data in memory without feeling, Provide data to applications in real time.

The file operation task module only contains external modules, or the user actively operates to encrypt, decrypt, or distribute a file. It does not include the senseless encryption and decryption provided by the W3FS-SDK real-time file system kernel driver and the W3FS LocalServer module.

The file operation task module operates the user-specified file through asynchronous multi-threading, and in order to ensure the security of the file data in the file recoding operation stage during the file encryption and decryption process, the file operation task module operates the user-specified file through the copy operation mode uniformly. In the file data re-encoding stage, all modifications to the file data are performed in the externally specified file. After the operation is completed, the external decides whether to delete the source file or backup the source file. This is a disaster tolerance mechanism generated by W3FS-SDK to prevent problems caused by sudden power failure or program abnormalities that may occur during the encoding process.

W3FS-SDK provides file manual operation functions, including file encryption, decryption, sharing and other operations, and provides task operation interfaces to support external control of file operation tasks, including task cancellation and other operations.

The encryption operation is only completed using the public key of the default identity currently specified by the user. The external should confirm that the user login has been completed before calling the file operation interface, and the operation of setting the user identity and default identity
The decryption operation is only completed using all the private keys owned by the current user. The external should confirm that the user login and the operation of setting the user's identity have been completed before calling the file operation interface.
The identities and actions (adding or removing identities) used by the distribution operation are externally added according to the objects of a distribution operation

The file operation interface uses the task mechanism. An external file operation task should be created first, and various parameters of the file operation task (including basic parameters and extended parameters) should be set.
The file operation is a time-consuming operation. The library uses a new thread to complete it asynchronously. During the execution of the file operation, the outside can control the execution of the file operation through the task mechanism interface.
The intermediate status information and final result information of the file operation should be obtained by polling through the task operation interface, and the corresponding interface prompt information should be displayed.
The standard flow of file manipulation tasks is as follows:

1. Initialize a file operation task: set the basic parameter attributes of a file operation task, including the number of threads corresponding to the task, and the action of the task (encryption/decryption/distribution)

2. Set the task target of a file operation: set the task target (file/folder) corresponding to a file operation one by one into the W3FS-SDK library through the interface
3. Set the identity operation action of a file distribution operation: only for the file distribution operation, the interface call will take effect, and the identity addition and deletion operation will be performed on the identity area of the file.
4. Set the signature attribute of a file distribution operation: only for the file distribution operation, the interface call will take effect
5. Start the file operation task;
6. Get file operation task status:
7. Control the file operation task (including the suspension of the file operation task, etc.), because the file operation task is an asynchronous multi-threaded task, so the control of a file operation task will not be reflected immediately, and the final result should be obtained by obtaining the file operation. Get task status interface
8. Get the file operation task result report
9. Reversely initialize a file operation task and destroy various objects created in a file operation task.

#### **TSK_FileOpTask_Init**

Initialize a file operation task

function prototype:

```` c
TSK_FileOpTask_Init(nAction int, nThreadCount int) int
````

Parameters:

* nAction, the specific operation corresponding to this file operation task, 1, encryption; 2, decryption; 3, distribution [IN]
* nThreadCount, the number of threads to be started for this file operation task, the default value is 1[IN]

return value:

* Less than 0 indicates that the initialization of the file operation task failed, and no subsequent operations are required. Greater than or equal to 0 indicates that the initialization was successful, and the task ID corresponding to the file operation task is returned. All subsequent operations and control of the file operation task are performed through the task ID.


illustrate:

nThreadCount, manual file operation is a time-consuming and computationally intensive operation. It is recommended to achieve a balance between performance and user experience by setting a reasonable number of multi-threads, such as the maximum number of threads set to (number of cpu cores/2+1)

The internal library will use the file as the unit, and the internal library will start the task thread number threshold that does not exceed the externally set threshold for multi-threaded processing of multiple files in one task. Of course, if the number of target files of a file operation task is less than the set number of threads, the Turn on multithreading with the actual number of files

#### **TSK_FileOpTask_PushAFileToTask**

Add a full path of the file/folder to be operated to the specified file operation task

function prototype:

```` c
TSK_FileOpTask_PushAFileToTask(nTaskID int, pSrcFilePath []byte, pDstFilePath []byte) int 
````

Parameters:

* nTaskID, the specified file operation task ID[IN]
* pSrcFullPath, the full path information of the source file/folder to be operated [IN]
* pDstFullPath, the full path information of the target file/folder to be operated [IN]

return value:

* KError_Success, success;

illustrate:

​	pSrcFullPath, pDstFullPath use OS native way to process string type data, in windows operating system, use Unicode character set, in Linux, Mac, IOS, Android and other operating systems, use UTF-8 character set.

One file operation task can be operated to process multiple files/folders at the same time, and the external can call this function multiple times during one file operation task to set the target full path of one file operation task

​	This function is only valid before the task is actually started. After the task state has been started, including the task is in the suspended state, the interface cannot be called again to complete the addition of the operation target.

​	Only the encryption and decryption operations need to pass in two paths. In most cases, distribution operations are performed on the source file because the reserved header space is sufficient. Therefore, the distribution operation only needs to pass in the source file path, and the target file can be passed NULL, The source file and the target file must not be the same path, and the source file must exist.

#### **TSK_FileOpTask_PushAAction**

Add a pending identity item action to the specified file operation task

function prototype:

```` c
TSK_FileOpTask_PushAAction(nTaskID int, bDelAdd bool,IID []byte, nPermission int16, nLastTime int, pKeyBuf []byte, nKeyBufLen int) int
````

Parameters:

* nTaskID, the specified file operation task ID[IN]
* bDelAdd, add or delete an identity in the identity area, true, add, false, delete [IN]IID, the 20-byte identity ID information of the identity to be operated [IN]
* nPermission, the permission information of the identity to be operated, when deleting the identity action, this parameter is meaningless, you can pass an empty permission [IN]
* nLastTime, the last use time limit information of the identity to be operated, when deleting the identity action, this parameter is meaningless, you can pass 0 [IN]
* pKeyBuf, the public key information of the identity to be operated, when deleting the identity action, this parameter is meaningless, you can pass NULL [IN]
* nKeyBufLen, the public key length information of the identity to be operated, when deleting the identity action, this parameter is meaningless, you can pass 0 [IN]

return value:

* KError_Success, success;
* Others are failures, please refer to the standard return value definition of the W3FS Native SDK library


illustrate:

This interface is only valid for file distribution. The identity area adjustment of the TSK library uses the action restoration method to perform the addition or deletion of identities.

The user's distribution actions to the specified files or folders should be recorded externally, and sent to the TSK library as an action list one by one, and the library will restore the actions in the order of the user's distribution actions, and finally complete the distribution operation.

This function is only valid before the task is actually started. After the task state has been started, including the task is in the suspended state, the interface cannot be called again to complete the addition of the operation target.

#### **TSK_FileOpTask_SetShareSign**

Set a file operation task signature action

function prototype:

```` c
TSK_FileOpTask_SetShareSign(nTaskID int, nSignAction int ) int
````

Parameters:

* nTaskID, the specified file operation task ID[IN]
* nSignAction is the signature action information, 0 is to keep the signature information, 1 is to set the signature information, 2 is to clear the signature information [IN]

return value:

* KError_Success, success;
* Others are failures, please refer to the standard return value definition of the W3FS Native SDK library


illustrate:

Set the signature action only for file distribution operations. The default value in the library is 0, and the current signature information is maintained.

This function is only valid before the task is actually started. After the task state has been started, including the task is in the suspended state, the interface cannot be called again to complete the addition of the operation target.

#### **TSK_FileOpTask_StartATask**

Start a file operation task

function prototype:

```` c
TSK_FileOpTask_StartATask(nTaskID int) int 
````

Parameters:

* nTaskID, the specified file operation task ID[IN]

return value:

* KError_Success, success;
* Others are failures, please refer to the standard return value definition of the W3FS Native SDK library


illustrate:

After the file operation task starts, you cannot call the setting parameter interface again, modify the properties of the file operation task, and perform asynchronous operations. Asynchronous multi-threading will be started internally to complete the real transaction.

#### **TSK_FileOpTask_CancelATask**

Abort a file operation task

function prototype:

```` c
TSK_FileOpTask_CancelATask(nTaskID int) int 
````

Parameters:

* nTaskID, the specified file operation task ID[IN]

return value:

* KError_Success, success;
* Others are failures, please refer to the standard return value definition of the W3FS Native SDK library


illustrate:

​	The file operation task is an asynchronous multi-threaded operation. The return value of the interface call to abort a task is simply to return whether the interface call is successful. The cancellation status of the task is ultimately based on the result of the file operation task status interface call.

​	After the file operation task is canceled, it cannot be opened again. The external interface should also call the delete file operation task interface to release various system resources occupied by the file operation task.

​	If the file operation task is canceled, the file status of the completed operation will not be rolled back. Externally, the Get File Operation Task Result Report API can be called to obtain the operation result of the file operation task.

#### **TSK_FileOpTask_UnInitATask**

Delete a file operation task

function prototype:

```` c
 TSK_FileOpTask_UnInitATask(nTaskID int) int
````

Parameters:

* nTaskID, the specified file operation task ID[IN]

return value:

* KError_Success, success;
* Others are failures, please refer to the standard return value definition of the W3FS Native SDK library


illustrate:

After a file operation task is completed (including active cancellation), the external should call this interface to release various system resources occupied by the file operation task

The task status is estimated and in progress. It is not allowed to delete. It needs to wait for completion, or actively cancel the task before it can be deleted.

#### **TSK_FileOpTask_GetATaskState**

Get the status of a file operation task

function prototype:

```` c
TSK_FileOpTask_GetATaskState(nTaskID int) (int, int64, int64, int) 
````

Parameters:

* nTaskID, the specified file operation task ID[IN]

return value:

* nTotalLength, specifies the total length of data to be processed (in bytes) for file operation tasks [OUT]
* nCurrentLength, specifies the currently processed data length (in bytes) of the file operation task [out]
* nState, the current state of the specified file operation task [OUT]

* KError_Success, success;
* Others are failures, please refer to the standard return value definition of the W3FS Native SDK library


illustrate:

In the W3FS-SDK library, the file operation task status is defined as follows:

* 0--to be started, nTotalLength, nCurrentLength data is invalid
* 1--Data processing is in progress (estimating data length stage), nTotalLength, nCurrentLength data are invalid, and the external interface prompt can simply indicate that the time is being estimated
* 2--Data processing is in progress (data processing stage), external can use nTotalLength, nCurrentLength to convert percentage, or directly display data length
* 3--Data processing is completed (all data processing is successful), nTotalLength, nCurrentLength data is invalid
* 4--Data processing is completed (external active cancellation), nTotalLength, nCurrentLength data is invalid

If the task status is successful, it does not mean that the file is processed successfully. The file processing result needs to be obtained by calling the Get File Operation Task Result Report.

The file operation task is an asynchronous multi-threaded task. The external can periodically obtain the task status through the operation task ID through a worker thread polling method. To avoid frequent refresh of the interface, it is recommended not to set the timing too short, and it is recommended to obtain it at a time of 500ms.

There is an abnormal situation to be processed outside the conversion percentage. The length of the total data to be obtained is 0, and the length of the processed data is also 0 for a long time. For example, a large number of empty files are encrypted.

#### **TSK_FileOpTask_GetATaskReport**

Get a file operation task report of final result 

function prototype:

```` c
TSK_FileOpTask_GetATaskReport(nTaskID int,nReportMode int,reportLen int) ([]byte, int, int) 
````

Parameters:

* nTaskID, the specified file operation task ID[IN]
* nReportMode, result report mode [IN]

return value:

* pReportBuf, the buffer area of the externally prepared reception result report [IN/OUT]
* nReportBufLength, the buffer length of the externally prepared reception result report [IN/OUT]

* KError_Success, success;
* Others are failures, please refer to the standard return value definition of the W3FS Native SDK library


illustrate:

The result report is returned as a memory stream (each element is placed in the externally provided memory buffer in the form of direct memory copy)

An example of a minimalist mode report is as follows:
4-byte integer count+4-byte integer success+4-byte integer fail+4-byte integer ignore

An example of a full mode report is as follows:
4-byte integer count + 4-byte integer success + 4-byte integer fail + 4-byte integer ignore + file operation results one by one


The result of a single file operation is packaged into a stream and the structure is as follows
4 bytes nAction + 4 bytes nResult + 4 bytes source file full path length (including trailing 0 length) + source file full path (including trailing 0) + 4 bytes target file full path length (including trailing 0) + The full path of the target file (including the trailing 0), the full path of the target file may be empty, then the length is parsed as 0, and the next field can be read directly according to the offset

Externally, you can first parse out the total number of file elements in count, and cyclically parse the file operation result through the memory offset.

```` c
//The result of a single file operation is defined as follows:
#define FILEOP_RESULT_NOERROR 0 //The file operation is successful
#define FILEOP_RESULT_IGNORE -1 //The file operation is ignored. For example, when encrypting a file, it is an encrypted file. When decrypting a file, it is a non-encrypted file. The target file of the distribution file is not encrypted.
#define FILEOP_RESULT_FILECANTSERVER -2 //The file operation failed because the file could not be served, such as file open failure or read and write failure, and the final file post-processing failure
#define FILEOP_RESULT_TSKFAILED -3 //The file operation failed because the TSK library returned a failure, such as failure to create a TEFS structure
#define FILEOP_RESULT_PERMISSIONFAILED -4 //The file operation failed because of permission issues, such as the source file does not allow decryption or distribution is not allowed
#define FILEOP_RESULT_VERSIONFAILED -5 ////Encrypted files, but the version does not support, reject
#define FILEOP_RESULT_DATAFAILED -6 //Encrypt the file, but the key area check error, reject
````

#### **TSK_FileOpTask_CanExit**

Whether the file operation task module can exit

function prototype:

```` c
TSK_FileOpTask_CanExit() int 
````

Parameters:

* none

return value:

* 0 means that there is currently a task being executed and cannot be exited, 1 means that all the current tasks are executed and the program can be exited

illustrate:

It is recommended that external users call this interface when the application exits or the user logs out to check whether there are still file operation tasks in progress.

#### **TSK_FileOp_AdjustByFlow**

Adjust the specified encrypted header stream data through the given identity and related attributes, and return the new encrypted header stream data to the outside

function prototype:

```` c
TSK_FileOp_AdjustByFlow(headSrc []byte, srcLen int,bDelAdd bool, userid []byte, nPermission int16, lasttime int, pubkey []byte, pubkeylen int) ([]byte, C.int, int) 
````

Parameters:

* pHeadFlowSrc, external incoming raw encrypted header flow data [IN]
* nHeadFlowSrcLen, the length information of the original encrypted header flow data incoming from the outside [IN]
* nIID, the identity ID to be modified [IN]
* nPermission, the permission corresponding to the identity to be modified [IN]
* nLastTime, the last file usage time of the identity to be modified [IN]
* pKeyBuf, the key buffer of the identity to be modified [IN]
* nKeyBufLen, the key buffer length of the identity to be modified [IN]
* bAdd, whether to add or delete the envelope to the encrypted header identity area, true to add, false to delete [IN]

return value:

* pHeadFlowDst, externally prepared to receive the adjusted encrypted header flow data buffer [OUT]
* nHeadFlowDstLen, the adjusted length of encrypted header flow data [OUT]

* Return the result of the operation, refer to the definition of the return result of the TSK library


illustrate:

The buffer area prepared externally for receiving new encrypted header stream data must be large enough. A new identity in the encrypted header envelope area occupies 154 bytes in the current version. It is recommended that the buffer area prepared externally be 1024 bytes larger than the original envelope. The actual adjusted header data length will be returned by nHeadFlowDstLen

The special interface is generally called during the development of APPs that have proxy file sharing requirements. The client can complete the file sharing operation locally through the regular file sharing task interface.

### **LocalService part of the interface**

The W3FS-SDK library is embedded a local HttpLocalSerer module, which supports external use of standard http requests to obtain the real data of an encrypted file, and supports insensitive decryption of an encrypted file through the browser without the W3FS-SDK real-time file system kernel driver environment.

#### **TSK_LocalServer_Start**

Start the HttpLocalServer module inside W3FS-SDK

function prototype:

```` c
TSK_LocalServer_Start(port int) int 
````

Parameters:

* nPort, the port specified by LocalServer [IN]

return value:

* Return the result of the operation, refer to the definition of the return result of the TSK library

illustrate: 
In the development of NativeAPP without integrated W3FS kernel driver module, the local LocalServer is the only way to provide transparent and insensitive use of encrypted data files.

#### **TSK_LocalServer_Stop**

* Stop HttpLocalServer module inside W3FS-SDK

  function prototype:

  ```` c
  TSK_LocalServer_Stop() 
  ````

  Parameters:

  * none

  return value:

  * none
#### **TSK_LocalServer_SetSystemTime**

Set the current system time

function prototype:

```` c
TSK_LocalServer_SetSystemTime(nTime int) 
````

Parameters:

* nTime, the system time set externally

return value:

* none

illustrate:

Set the time as the number of seconds since midnight on January 1, 1970 (4-byte integer)

#### **TSK_LocalServer_GetSessionKey**

Get the current random key

function prototype:

```` c
TSK_LocalServer_GetSessionKey(pSessionKey []byte) bool
````

Parameters:

* pSessionKey, externally prepared buffer area for receiving SessionKey [IN/OUT]

return value:

* bool

illustrate:

​	The SessionKey is a fixed 20-byte length information, which is used for LocalSever verification. After the library is started, the external must obtain the current SessionKey. The request to the LocalServer must bring the obtained SessionKey for the LocalServer to determine whether the request is valid.

For the convenience of external use, pSessionKey has been fixed as a visible string, and a trailing 0 has been added, so the actual sessionkey is only 19 bytes.



## Instructions for use 

Unzip the tsk package 

Authorize  chmod +x libTSKLinux.so 

copy cp libTSKLinux.so /usr/lib/ 

interface test go test









