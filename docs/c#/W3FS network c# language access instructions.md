[TOC]

# W3FS network c# language access instructions

The W3FS network provides its users with powerful and practical capabilities, including relevant technical capabilities in the blockchain field, unrestricted types of file encryption and decryption processing capabilities, and file decentralized storage capabilities. The collection of these technical capabilities can be applied to many real-world scenarios, such as in the field of NFT, which will enable NFT to carry out various forms of circulation without file type restrictions and no security risks under specific rules. You can also combine These capabilities create any form of Dapp you can imagine.
The following three technology integrations are described in detail in this document.

* Instructions for accessing the W3FS file encryption and decryption SDK.
* Code samples related to W3FS network access.
* W3FS network decentralized storage access instructions.

Developers or development teams can select targeted technologies to access according to their customized Dapps.



***



## 1.W3FS-SDK C# access instructions

### 1.Function introduction

W3FS is a dynamic link library provided by W3FS-SDK for windows system.This document uses C# as an example to introduce the use of W3FSTSK.dll.

Through simple integration, you can use the SDK\'s functions of encrypting and decrypting files, sharing encrypted files, and transparently using files.

**Encrypted file:** It consists of encrypted envelope header (encrypted header length, encrypted header padding area), actual encrypted file body, and two parts.

**Decrypted file:** Also called file decryption, that is, the decrypted file is a new unencrypted file.

**Share files:** Share encrypted files (unencrypted files cannot be shared), and then add/delete the identity to be operated from the original encrypted file.

**Transparent use of files:** files will not be decrypted (unencrypted files will not be generated). By enabling LocalServer and using WebView, encrypted files can be used directly and transparently without decryption.

### 2. Definition of terms


| noun        | Paraphrase                                                   |
| ----------- | ------------------------------------------------------------ |
| Head        | It consists of the length of the encryption header and the filling area of the encryption header, including the information of the file operator, operation permission, operation period and so on (with Body to form a complete encrypted file) |
| Body        | Actual encrypted file contents (with Head to form a complete encrypted file) |
| Seed        | The seed, which is defined by the user to generate the public and private keys for file encryption and decryption |
| KeyId       | Unique ID                                                    |
| LocalServer | After enabling LocalServer, you can use WebView to decrypt encrypted files directly and transparently. |
| SessionKey  | Used for LocalServer transparent decryption verification     |

### 3.C# integrated W3FSTSK.DLL

Take Console Application as an example，Open VS2019->Create->Console Application(Target framework need to higher than .Net framework 4.6.1):

![image](images\image1.png)

After creating,Right click on the project->Add->existing items->TSK.DLL and W3FSTSK.dll (Depend your project solution platforms to choose x86 or x64).

![image](images\image1-1.png)

![image](images\image2.png)

Right click TSK.dll->properties->Copy to Output Directory->Copy Always；Build Action ->Content

![image](images\image3.png)

Right click on the project->Add->Project Reference->browse->W3FSTSK.dll：

![image](images\image2-1.png)

Edit Program.cs and change solution Platforms to x86:

```C#
using System;
using W3FS;
namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            var a = TSKInterface.TSK_Init();

            Console.WriteLine(a);
        }
    }
}
```

Run the project ,Success:

![image](images\image4.png)

All interface,more details write in Chapter 6 :

![image](images\image4-1.png)

### 4.Flow chart

![image](images\image6.jpg)

### 5.Status code

```C#
//TEFS INFO TAG LENGTH
public const int TEFS_INFO_TAG_LENGTH = 32;

//Encrypted Information Block Tag
public static byte[] g_TEFStag = new byte[TEFS_INFO_TAG_LENGTH] {0xb2,0x85,0x3f,0x82,0xe3,0xf8,0x11,0xd6,0x82,0xb8,0x00,0x80,0x38,0x80,0xab,0x36,0x40,0x69,0xd1,0x7e,0x07,0x19,0xee,0x29,0x7d,0x47,0xff,0xaf,0xb3,0x7f,0x5d,0xc7};

///Action constant when calling symmetric algorithm to encrypt and decrypt
/// <summary>
/// encrypt
/// </summary>
public const byte ACTION_ENCRYPT = 1;

/// <summary>
/// decrypt
/// </summary>
public const byte ACTION_DECRYPT = 2;

/// <summary>
/// decrypt
/// </summary>
public const byte ACTION_ADJUST = 3;

/////////////////////////
///Interface error code
///>=0,Success;
///<0,Error;
/////////////////////////
/// <summary>
/// Success
/// </summary>
public const int KError_Success = 0;

/// <summary>
/// Success, but no streaming data was processed
/// </summary>
public const int KError_NoDataHandled = 1;

/// <summary>
/// Success, create the object
/// </summary>
public const int KError_CreateObject = 10;

/// <summary>
/// Success, open the object
/// </summary>
public const int KError_OpenObject = 11;

/// <summary>
/// Success, open the object and overwrite the object
/// </summary>
public const int KError_OverrideObject = 12;

/// <summary>
/// Error，Wrong length
/// </summary>
public const int KError_LengthError = -1;

/// <summary>
/// Error，time out
/// </summary>
public const int KError_TimeOut = -2;

/// <summary>
/// Error,out of length
/// </summary>
public const int KError_OutOfLength = -3;

/// <summary>
/// Error，Cant Connect Kernel
/// </summary>
public const int KError_CantConnectKernel = -10;

/// <summary>
/// Error，File Serving
/// </summary>
public const int KError_FileServing = -11;

/// <summary>
/// Error，Multi-user login
/// </summary>
public const int KError_MultiUser = -20;

/// <summary>
/// Error，No logged in user
/// </summary>
public const int KError_NoUser = -21;

/// <summary>
/// Error，Grammatical errors
/// </summary>
public const int KError_SyntaxError = -30;

/// <summary>
/// Error，Cannot find the specified object
/// </summary>
public const int KError_CantFindObject = -31;

/// <summary>
/// Error，Multiple specified objects
/// </summary>
public const int KError_MultiObject = -32;

/// <summary>
/// Error，The specified object cannot be found temporarily
/// </summary>
public const int KError_MaybeFindObject = -33;

/// <summary>
/// Error，Common logic error
/// </summary>
public const int KError_CommonLogic = -34;

/// <summary>
/// Error，Encryption algorithm error (usually no encryption algorithm)
/// </summary>
public const int KError_CipherError = -40;

/// <summary>
/// Error，Encryption algorithm internal error
/// </summary>
public const int KError_CipherInnerError = -41;

/// <summary>
/// Error，Failed to process encrypted header structure ，CRC error
/// </summary>
public const int KError_HeaderCrcError = -50;

/// <summary>
/// Error，Identity Seal Error
/// </summary>
public const int KError_IdentitySealError = -51;

/// <summary>
/// Error，Other errors (usually memory allocation errors)
/// </summary>
public const int KError_Other = -100;

/// <summary>
/// Error，Expired
/// </summary>
public const int KError_Expired = -500;

/////////////////////////////////////////////
///Verb constant when calling list operations
/////////////////////////////////////////////

/// <summary>
/// Set default identity
/// </summary>
public const int LIST_VERB_DEFAULT = 1;

/// <summary>
/// Clear identity list
/// </summary>
public const int LIST_VERB_CLEAR = 2;

/// <summary>
/// Add identity
/// </summary>
public const int LIST_VERB_ADD = 3;

/// <summary>
/// Delete identity
/// </summary>
public const int LIST_VERB_DELETE = 4;

public const int FILEOPTASK_STATE_WAITING = 0; //waitting

public const int FILEOPTASK_STATE_PREDICT = 1; //calculate

public const int FILEOPTASK_STATE_PROGRESS = 2; //processing

public const int FILEOPTASK_STATE_SUCCESS = 3; //success

public const int FILEOPTASK_STATE_CANCLE = 4; //cancel

public const int FILEOP_RESULT_NOERROR = 0;//success

public const int FILEOP_RESULT_IGNORE = -1;//ignore

public const int FILEOP_RESULT_FILECANTSERVER = -2;//fail,can\'t server

public const int FILEOP_RESULT_TSKFAILED = -3; //fail,TSK return error

public const int FILEOP_RESULT_PERMISSIONFAILED = -4; //fail,permission

public const int FILEOP_RESULT_VERSIONFAILED = -5; //fail,version

public const int FILEOP_RESULT_DATAFAILED = -6; //fail,data
```

### 6.Interface

**TSK_Init **

Initialize the W3FS-SDK Native library.

Function prototype: 

```C#
public static extern int TSK_Init();
```

Parameters:

* none

return value:

* int:
  KError_Success success
  KError_CantConnectKernel, failed, unable to connect to the W3FS file system kernel (only valid for Native dapp development).
  KError_Other, failed, other errors;

Important Notes:

​	The TSK_Init interface is the W3FS-SDK initialization interface. All NativeApps that load the W3FS-SDK library should call the TSK_Init interface when the App is started or initialized . The other API calls of the W3FS-SDK library depend on the successful call of the TSK_Init interface.

**TSK_UnInit **

Reverse initialization of W3FS-SDK Native library

Function prototype:

```C#
public static extern int TSK_UnInit();
```

Parameters:

* none

return value:

* none

illustrate:

​	Dapp needs to call the TSK_UnInit interface to complete the reverse initialization of the W3FS Native SDK library when the program exits, so that the W3FS Native SDK library can clean up and release all occupied system resources.

**TSK_GetRandomKey**

​	Get an array of random numbers of a specified length

function prototype:

```C#
 public static int TSK_GetRandomKey(uint nKeyLen, byte[] pKey);
```

return value:

* KError_Success, success

illustrate:

​	The W3FS Native SDK library has a built-in random number generator, which can generate random numbers of the required length according to external business needs. In the apps with the W3FS kernel driver loaded, the random numbers generated by the W3FS-SDK library are True random numbers generated by the SDK driver kernel. In other ways of APP , the obtained number is a pseudo-random number generated by the W3FS-SDK library based on the current system time and some other factors.

**TSK_IdentityIssueEx **

Generate (issue) an identity object and directly return the keystream form to the outside

function prototype:

```C#
public static extern int TSK_IdentityIssueEx(byte[] pSeed, int nSeedLen, byte[] pPublicKeyBuf, ref int nPublicKeyLen, byte[] pPrivateKenBuf, ref int nPrivateKeyLen, byte[] pKeyID);
```

Parameters:

* pSeed: The seed information of the specified identity key information [IN]
* nSeedLen: The length of the seed information of the specified identity key information, in bytes [IN]
* nPublicKeyLen: The length of the external public key buffer [IN/OUT]
* nPrivateKeyLen: The length of the private key buffer passed in from the outside [IN/OUT]
* pPublicKeyBuf: identity public key information data stream [IN/OUT]
* pPrivateKeyBuf: identity private key information data stream [IN/OUT]
* pKeyID: identity key ID, fixed 20 bytes [IN/OUT]

return value:

* KError_Success, success
* KError_Other, failed, other errors

illustrate:

The function of TSK_IdentityIssueEx is the same as that of TSK_IdentityIssue. The difference is that it returns the binary stream of public and private keys that can be directly parsed and saved externally. Externally, the TSK_IdentityIssueEx interface can be used to obtain the public and private key data of the identity key and save it directly or do other processing.
In the design of the W3FS-SDK library, the buffer memory is prepared in advance by the external program, and is passed to the W3FS-SDK library together with the buffer length information. The W3FS-SDK library operates directly on the externally prepared buffer. , the release of the buffer is also the responsibility of the external program itself.

**TSK_DigestCRC32 **

Iterative support for CRC32 digests of single streams.

function prototype:

```C#
public static extern int TSK_DigestCRC32(UInt32 nFlowLen, byte[] pFlow, IntPtr pCookie, ref UInt32 pCRC32);
```

Iterative support for CRC32 digests of multiple streams.

function prototype:

```C#
public static extern int TSK_DigestCRC32(UInt32 nFlowLen, byte[] pFlow, IntPtr pCookie, IntPtr pCRC32);
```

Parameters:

* nFlowLen: is to specify the size of the stream for which the CRC32 digest is to be calculated [IN]
* pFlow: is to specify the stream for which the CRC32 digest is to be calculated [IN]
* pCookie: specify the cookie needed for iteration [IN/OUT]
* pCRC32: padded with the final result of the iterative digest, a 32-bit CRC32 value [OUT]

return value:

* KError_Success, success
* KError_Other, failed, other errors

illustrate:

CRC32 digest is a high-speed but unreliable digest algorithm that can be used to verify data that is used frequently.

1\. Call TSK_DigestCRC32(0,NULL,pCookie,NULL) This means to initialize the digest algorithm, ready to start processing multiple streams Unified joint digest. And return the cookie value of the digest process, the cookie value uniquely corresponds to this joint digest.

2.Call TSK_DigestCRC32(nFlowLen,pFlow,pCookie,NULL) for each stream to indicate that the digest algorithm is used for the specified stream Digest, where cookie is the digest cookie obtained in step 1

3.Call TSK_DigestCRC32(0,NULL,pDigestID,pCRC32) to end the digest and return the final digest result，The stored digest cookie is the digest cookie obtained in step 1.

**TSK_DigestMD5 **

Iterative support for MD5 algorithm digests over multiple streams,Multiple stream digests can refer to TSK_DigestCRC32.

function prototype:

```C#
public static extern int TSK_DigestMD5(UInt32 nFlowLen, byte[] pFlow, IntPtr pCookie, byte[] pMD5);
```

Parameters:

* nFlowLen: is to specify the size of the stream for which the MD5 digest is to be calculated [IN]
* pFlow: is to specify the stream for which the MD5 digest is to be calculated [IN]
* pCookie: specify the cookie needed for iteration [IN/OUT]
* pMD5: filled with the final result of the iteration digest, as a 16-byte array [OUT]

return value:

* KError_Success, success
* KError_Other, failed, other errors

illustrate:

MD5 digest is a slow but reliable digest algorithm

**TSK_DigestSha256**

​	Iterative support for SHA256 algorithm digests over multiple streams,Multiple stream digests can refer to TSK_DigestCRC32.

function prototype:

```C#
public static extern int TSK_DigestSha256(UInt32 nFlowLen, byte[] pFlow, IntPtr pCookie, byte[] pSHA256);
```

Parameters:

* nFlowLen: is to specify the size of the stream for which the SHA256 digest is to be calculated [IN]
* pFlow: is to specify the stream for which the SHA256 digest is to be calculated [IN]
* pCookie: specify the cookie needed for iteration [IN/OUT]
* pSHA256: The final result filled with the iterative digest, as a 32-byte array [OUT]

return value:

* KError_Success, success
* KError_Other, failed, other errors

illustrate:

​	SHA256 digest is a reliable digest algorithm that can be used for signature verification of arbitrary data.

**TSK_GetCipherDesc **

​	Get all currently loaded algorithm descriptions

function prototype:

```C#
public static extern int TSK_GetCipherDesc(byte[] pDescBuf, int nDescBufLen);
```

Parameters:

* pDescBuf, an externally prepared buffer for receiving reports, it is recommended to apply for an 8K (8192) byte length buffer for the first time [IN/OUT]
* nDescBufLen, the buffer length prepared externally to receive the report, the recommended first length is 8192 bytes [IN]

return value:

* Returns the actual length of the report. If the return value is greater than the buffer length passed in from the outside, no operation will be performed on the buffer, and the outside needs to re-apply for a buffer large enough according to the actual length, and obtain it again

illustrate:

​	On the application layer interface, the loaded algorithm is obtained and displayed through this interface.

Parse the code described by the algorithm:

```C#
byte[] buf = new byte[8192];//Request an array of 8192 bytes in length
int len = 8192;

//dataLen is actual data length
int dataLen = TSKInterface.TSK_GetCipherDesc(buf, len);

//4 bytes data is total number of cipher.
byte[] numBuf= new byte[4];

memcpy(numBuf, buf, 4);

int num = System.BitConverter.ToInt32(numBuf,0);

UInt16 length = 0, size = 0;

//Parse the code buffer to string
string strData = ““;

int count = 2;

//tag list
List<byte[]> list = new List<byte[]>();

for (int i = 4; i < dataLen; i++)
{

    if (count == 2)
    {
        //get tag，16 bytes.
        byte[] tagBuf= new byte[16];
        memcpy(tagBuf, buf.Skip(i).ToArray(), 16);
        list.Add(tagBuf);
        count = 0;
        i += 16;
    }

    string b = System.Text.Encoding.UTF8.GetString(buf, i, 1);

    if (buf[i] == 0)//0 is the end flag
    {
        if(count == 0)//cipher name
            Console.WriteLine(“name：“ + strData);//name
        else if(count == 1)//cipher description
            Console.WriteLine(“description：“ + strData);//description
        strData = ““;
        count += 1;
        continue;
    }
    strData += b;
}
```

**TSK_GetCipherInfo **

​	Get the specified algorithm details

function prototype:

```C#
public static extern int TSK_GetCipherInfo(byte[] tagCipher, ref UInt16 pKeyLength, ref UInt16 pBlockSize);
```

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

**TSK_SetDefaultCipher **

Set the current default algorithm

function prototype:

```C#
public static extern int TSK_SetDefaultCipher(byte[] tagCipher);
```

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

**TSK_SetDefaultZone **

Set default encrypted paragraphs(zone)

function prototype:

```C#
public static extern int TSK_SetDefaultZone(Int64 nLen);
```

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

**TSK_LoginUser **

Login account

function prototype:

```C#
public static extern int TSK_LoginUser(byte[] pKeyID);
```

Parameters:

* pKeyIDis the corresponding internal ID representing the unique identity of the user

return value:

* KError_Success, success;
* KError_MultiUser, failed, there are other login users;
* KError_Other, other errors, usually memory allocation errors (or insufficient buffers);

**TSK_LogoutUser **

log out of current account

function prototype:

```C#
public static extern int TSK_LogoutUser();
```

Parameters:

* none

return value:

* KError_Success, success;

**TSK_SetHoldIdentity **

Set the identity held by the current user of the W3FS-SDK library

function prototype:

```C#
public static extern int TSK_SetHoldIdentity(UInt32 nListVerb, byte[] pKeyID, Int16 nPermission, Int32 nLastTime, byte[] pKeyBuf, int nKeyLen);
```

Parameters:

* nListVerb is a standard list manipulation verb, no LIST_VERB_MODIFY semantics [IN]
* pKeyID is the ID of this identity [IN]
* nPermission is the permission corresponding to the identity, the identity held by the user has all permissions by default, and needs to be set externally [IN]
* nLastTime is the expiration date of the file when the public key of the identity is used for default encryption, please be sure to pass in -1, the creator of the file has the permission to use it indefinitely [IN]
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

When you want to clear the default identity, you should specify pKeyID as IDENTITY_NULL, and other parameters do not need to be provided.

**TSK_IdentityImport**

Recover identity objects from reading information from a data

function prototype:

```C#
public static extern int TSK_IdentityImport(byte Action, UInt32 BufLen, byte[] Buf, ref IntPtr pIdentity);
```

Parameters:

* nAction is the action selection: [IN] 1 means public key, 2 means private key
* BufLen is the externally prepared buffer size [IN]
* Buf is an externally prepared identity key binary stream data [IN]
* Return the restored identity object in pIdentity (opaque semantics) [OUT]

return value:

* KError_Success, success
* KError_Other, other errors, usually memory allocation errors (or insufficient buffers);


illustrate:

Corresponding to the TSK_IdentityExport interface, import the binary stream data of a key passed in from the outside and restore it to an identity object with opaque semantics.

**TSK_IdentityExport**

Export an identity object in binary form according to the specified nAction(public or private key)

function prototype:

```C#
public static extern int TSK_IdentityExport(IntPtr Identity, byte Action, UInt32 BufLen, byte[] Buf, ref UInt32 pWrittenLen);
```

Parameters:

* identity is the target identity object (opaque semantics) [IN]
* nAction is the action selection: [IN] 1 means public key, 2 means private key, 3 means key identity ID
* BufLen is the receive buffer size of the data to output [IN]
* Buf is the receive buffer of the data to be output [OUT]
* pWrittenLen is the size of the actual output data returned [IN/OUT]

return value:

* KError_Success, success
* KError_Other, other errors, usually memory allocation errors (or insufficient buffers);


illustrate:

​	Externally, the public key or private key corresponding to the identity can be exported from the specified user identity object with opaque semantics through the TSK_IdentityExport interface. However, the prerequisite is that the opaque semantic object itself contains two kinds of information. According to the rules of the ECC encryption algorithm, if the identity object contains private key information, the binary stream data of the public key or private key can be arbitrarily derived. If the identity object only contains public key information, only the binary stream data of the public key can be exported.



**TSK_FileOpTask_Init **

Initialize a file operation task

function prototype:

```C#
public static extern int TSK_FileOpTask_Init(int nAction, int nThreadCount);
```

Parameters:

* nAction, the specific operation corresponding to this file operation task, 1, encryption; 2, decryption; 3, distribution [IN]
* nThreadCount, the number of threads to be started for this file operation task, the default value is 1[IN]

return value:

* Less than 0 indicates that the initialization of the file operation task failed, and no subsequent operations are required. Greater than or equal to 0 indicates that the initialization was successful, and the task ID corresponding to the file operation task is returned. All subsequent operations and control of the file operation task are performed through the task ID.


illustrate:

nThreadCount, manual file operation is a time-consuming and computationally intensive operation. It is recommended to achieve a balance between performance and user experience by setting a reasonable number of multi-threads, such as the maximum number of threads set to (number of cpu cores/2+1)

The internal library will use the file as the unit, and the internal library will start the task thread number threshold that does not exceed the externally set threshold for multi-threaded processing of multiple files in one task. Of course, if the number of target files of a file operation task is less than the set number of threads, the Turn on multithreading with the actual number of files



**TSK_FileOpTask_PushAFileToTask **

Add a full path of the file/folder to be operated to the specified file operation task

function prototype:

```C#
public static extern int TSK_FileOpTask_PushAFileToTask(int nTaskID, string pSrcFullPath, string pDstFullPath);
```

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



**TSK_FileOpTask_PushAAction **

Add a pending identity item action to the specified file operation task

function prototype:

```C#
public static extern int TSK_FileOpTask_PushAAction(int nTaskID, bool bDelAdd, byte[] IID, Int16 nPermission, int nLastTime, byte[] pKeyBuf, UInt32 nKeyBufLen);
```

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



**TSK_FileOpTask_SetShareSign **

Set a file operation task signature action

function prototype:

```C#
public static extern int TSK_FileOpTask_SetShareSign(int nTaskID, byte nSignAction);
```

Parameters:

* nTaskID, the specified file operation task ID[IN]
* nSignAction is the signature action information, 0 is to keep the signature information, 1 is to set the signature information, 2 is to clear the signature information [IN]

return value:

* KError_Success, success;
* Others are failures, please refer to the standard return value definition of the W3FS Native SDK library


illustrate:

Set the signature action only for file distribution operations. The default value in the library is 0, and the current signature information is maintained.

This function is only valid before the task is actually started. After the task state has been started, including the task is in the suspended state, the interface cannot be called again to complete the addition of the operation target.



**TSK_FileOpTask_StartATask **

Start a file operation task

function prototype:

```C#
public static extern int TSK_FileOpTask_StartATask(int nTaskID);
```

Parameters:

* nTaskID, the specified file operation task ID[IN]

return value:

* KError_Success, success;
* Others are failures, please refer to the standard return value definition of the W3FS Native SDK library


illustrate:

After the file operation task starts, you cannot call the setting parameter interface again, modify the properties of the file operation task, and perform asynchronous operations. Asynchronous multi-threading will be started internally to complete the real transaction.

**TSK_FileOpTask_CancelATask **

Abort a file operation task

function prototype:

```C#
public static extern int TSK_FileOpTask_CancelATask(int nTaskID);
```

Parameters:

* nTaskID, the specified file operation task ID[IN]

return value:

* KError_Success, success;
* Others are failures, please refer to the standard return value definition of the W3FS Native SDK library


illustrate:

​	The file operation task is an asynchronous multi-threaded operation. The return value of the interface call to abort a task is simply to return whether the interface call is successful. The cancellation status of the task is ultimately based on the result of the file operation task status interface call.

​	After the file operation task is canceled, it cannot be opened again. The external interface should also call the delete file operation task interface to release various system resources occupied by the file operation task.

​	If the file operation task is canceled, the file status of the completed operation will not be rolled back. Externally, the Get File Operation Task Result Report API can be called to obtain the operation result of the file operation task.



**TSK_FileOpTask_GetATaskState **

Get the status of a file operation task

function prototype:

```C#
public static extern int TSK_FileOpTask_GetATaskState(int nTaskID, ref int nState, ref Int64 nTotalLength, ref Int64 nCurrentLength);
```

Parameters:

* nTaskID, the specified file operation task ID[IN]
* nTotalLength, specifies the total length of data to be processed (in bytes) for file operation tasks [OUT]
* nCurrentLength, specifies the currently processed data length (in bytes) of the file operation task [out]
* nState, the current state of the specified file operation task [OUT]


return value:

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



**TSK_FileOpTask_GetATaskReport **

Get a file operation task report of final result 

function prototype:

```C#
public static extern int TSK_FileOpTask_GetATaskReport(int nTaskID, int nReportMode, byte[] pReportBuf, ref Int32 nReportBufLength);
```

Parameters:

* nTaskID, the specified file operation task ID[IN]
* nReportMode, result report mode [IN]
* pReportBuf, the buffer area of the externally prepared reception result report [IN/OUT]
* nReportBufLength, the buffer length of the externally prepared reception result report [IN/OUT]

return value:

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

Parsed byte array:

```C#
byte[] vs = new byte[8192];

int length = 8192;

var code = TSKInterface.TSK_FileOpTask_GetATaskReport(iTaskId, 2, vs, ref length);

int offset = 0;

//file count
int count = BitConverter.ToInt32(vs, offset);

offset += 4;

//success number
int success = BitConverter.ToInt32(vs, offset);

offset += 4;

//fail number
int fail = BitConverter.ToInt32(vs, offset);

offset += 4;

//ignore number
int ignore = BitConverter.ToInt32(vs, offset);

offset += 4;

for (int j = 0; j < count; j++)
{
    //action
    int nAction = BitConverter.ToInt32(vs, offset);

    offset += 4;

    //result
    int nResult = BitConverter.ToInt32(vs, offset);

    offset += 4;

    //source file path length
    int nPathLen = BitConverter.ToInt32(vs, offset);

    offset += 4;

    //source file path
    string path = System.Text.Encoding.Unicode.GetString(vs.Skip(offset).Take(nPathLen).ToArray()).Replace(“\\0“, ““);

    offset += nPathLen;

    //target file path length
    int nToPathLen = BitConverter.ToInt32(vs, offset);

    offset += 4;

    //target file path
    string topath = System.Text.Encoding.Unicode.GetString(vs.Skip(offset).Take(nToPathLen).ToArray()).Replace(“\\0“, ““);

    offset += nToPathLen;
}

```

**TSK_FileOpTask_UnInitATask **

Delete a file operation task

function prototype:

```C#
public static extern int TSK_FileOpTask_UnInitATask(int nTaskID);
```

Parameters:

* nTaskID, the specified file operation task ID[IN]

return value:

* KError_Success, success;
* Others are failures, please refer to the standard return value definition of the W3FS Native SDK library


illustrate:

After a file operation task is completed (including active cancellation), the external should call this interface to release various system resources occupied by the file operation task

The task status is estimated and in progress. It is not allowed to delete. It needs to wait for completion, or actively cancel the task before it can be deleted.

**TSK_FileOpTask_CanExit **

Whether the file operation task module can exit

function prototype:

```C#
public static extern int TSK_FileOpTask_CanExit();
```

Parameters:

* none

return value:

* 0 means that there is currently a task being executed and cannot be exited, 1 means that all the current tasks are executed and the program can be exited

illustrate:

It is recommended that external users call this interface when the application exits or the user logs out to check whether there are still file operation tasks in progress.

**TSK_LocalServer_Start **

Start the HttpLocalServer module inside W3FS-SDK

function prototype:

```C#
public static extern int TSK_LocalServer_Start(int nPort);
```

Parameters:

* nPort, the port specified by LocalServer [IN]

return value:

* Return the result of the operation, refer to the definition of the return result of the TSK library

illustrate: 
In the development of NativeAPP without integrated W3FS kernel driver module, the local LocalServer is the only way to provide transparent and insensitive use of encrypted data files.

**TSK_LocalServer_SetSystemTime **

Set the current system time

function prototype:

```C#
public static extern void TSK_LocalServer_SetSystemTime(int nTime);
```

Parameters:

* nTime, the system time set externally

return value:

* none

illustrate:

Set the time as the number of seconds since midnight on January 1, 1970 (4-byte integer)

**TSK_LocalServer_GetSessionKey **

Get the current random key

function prototype:

```C#
public static extern bool TSK_LocalServer_GetSessionKey(byte[] pSessionKey);
```

Parameters:

* pSessionKey, externally prepared buffer area for receiving SessionKey [IN/OUT]

return value:

* none

illustrate:

​	The SessionKey is a fixed 20-byte length information, which is used for LocalSever verification. After the library is started, the external must obtain the current SessionKey. The request to the LocalServer must bring the obtained SessionKey for the LocalServer to determine whether the request is valid.

For the convenience of external use, pSessionKey has been fixed as a visible string, and a trailing 0 has been added, so the actual sessionkey is only 19 bytes.

code：

```C#
byte[] vs = new byte[20];

TSKInterface.TSK_LocalServer_GetSessionKey(vs);

//0 is the end flag

string sessionKey = System.Text.Encoding.Default.GetString(vs).Replace(“\\0“, ““);
```



**TSK_LocalServer_Stop **

Stop HttpLocalServer module inside W3FS-SDK

function prototype:

```C#
public static extern int TSK_LocalServer_Stop();
```

Parameters:

* none

return value:

* none



**TSK_LocalServer_SetCurrentWebSiteParam**

Set the basic parameters of the current service dapp website

function prototype:

```C#
public static extern int TSK_LocalServer_SetCurrentWebSiteParam(string strRootDir, string strDynamicFlag, string strRemoteServer, string strIndexFileName, string strPemFilePath);
```

Parameters:

* strRootDir, the full path information of the root directory of the current dapp website [IN]
* strDynamicFlag, dynamic request flag, LocalServer will use this flag to determine whether to forward the request to the corresponding server. If you need to support local LocalServer dynamic request forwarding, the dapp development process should strictly abide by the request specification defined by itself. The dynamic request flag can have Multiple, separated by |, for example /d|/api|/opt, localserver requires that the dynamic request ID must be at the beginning of the requested Uri
* strRemoteServer, dynamic request forwarding remote server
* strIndexFileName, the home page of the local dapp, NULL can be passed, and index.html is used as the home page by default
* strPemFilePath, if the remote server address is configured as https, the SSL public key of the server needs to be provided to LocalServer in the form of a standard pem certificate file

return value:

* none

illustrate:
The built-in LocalServer in the W3FS Native SDK library can be used as a local HttpServer server. It supports downloading and opening the website data of dapps locally, providing dapps with a faster startup and use experience. Dapps can store all static Resources are uploaded to distributed storage or other types of network storage in the form of compressed packages. When NativeApp opens the dapp, it can download the compressed package to the local and decompress it. Access to all static resources of the dapp can be performed locally through the LocalServer. Dynamic The request can be forwarded to the real server of the dapp for processing, relying on distributed storage or other third-party storage to provide a better solution for the operation of the dapp.
At present, the built-in LocalServer in the W3FS Native SDK library only supports services for one dapp website at the same time. The open window of the dapp should be managed externally, and the local parameters of the website should be updated in time every time the dapp is opened.
LocalServer currently only supports the acquisition of dapp static data and the forwarding of dynamic requests. To support dynamic request forwarding, the external configuration should be done.
External can pass NULL through all three parameters, which means to clear the previous configuration data

### 7.Supplementary Instructions

**7.1 Parsed file head**

```C#
var srcfilePath = ""//file path

//get file stream

FileStream fsReader = new FileStream(srcfilePath, FileMode.Open, FileAccess.Read);

long fileLen = 0;

int flowId = 0;

//64 bytes buffer

byte[] head = new byte[TSKType.TEFS_INFO_TAG_LENGTH + 32];

//get 64 bytes data

fsReader.Read(head, 0, TSKType.TEFS_INFO_TAG_LENGTH + 32);

//compare date

if (memcmp(head, TSKType.g_TEFStag, TSKType.TEFS_INFO_TAG_LENGTH) == 0)

{

byte[] Buf = new byte[sizeof(UInt16) + sizeof(UInt32) + sizeof(UInt32)];

memcpy(Buf, head.Skip(32 + sizeof(byte) + sizeof(UInt32)).ToArray(), sizeof(UInt16) + sizeof(UInt32) + sizeof(UInt32));

//version

UInt16 ver = BitConverter.ToUInt16(Buf, 0);

//head actual data

uint pContentLen = BitConverter.ToUInt32(Buf, sizeof(UInt16));

//fill data length

uint pFillLen = BitConverter.ToUInt32(Buf, sizeof(UInt16) + sizeof(UInt32));

}
```



**7.2 LocalSever**



```C#
//start local server,set ip port

int code = TSKInterface.TSK_LocalServer_Start(8080);

//获set system time

TimeSpan ts = DateTime.Now - new DateTime(1970, 1, 1, 0, 0, 0, 0);

int iTime = Convert.ToInt32(ts.TotalSeconds);

TSKInterface.TSK_LocalServer_SetSystemTime(iTime);

//get session key

byte[] vs = new byte[20];

TSKInterface.TSK_LocalServer_GetSessionKey(vs);

string sessionKey= System.Text.Encoding.Default.GetString(vs).Replace(“\\0“, ““);

var path = ““//file path

string requestUrl = “http://127.0.0.1:8080/w3fsapi/openfile?key=“ + sessionKey + “&path=“ + path;

//CefSharp，can download from NuGet

var setting = new CefSettings(); setting.CefCommandLineArgs.Add(“disable-gpu“, “1“);

Cef.Initialize(setting);

//url

ChromiumWebBrowser browser = new ChromiumWebBrowser(requestUrl);

browser.Dock = DockStyle.Fill;

//load chromiumWebBrowser

Form form2 = new Form();

form2.StartPosition = FormStartPosition.CenterParent;

form2.Controls.Add(browser);

form2.ShowDialog();

//free

form2.Dispose();

browser.Dispose();

//close local server

code = TSKInterface.TSK_LocalServer_Stop();
```

***



## W3FS network transaction related access example (Windows-c# version)



### 1. Introduction

The purpose of this document is to help the development team understand the process and implementation methods related to W3FS's interaction with the chain. This document uses the C# code on the Windows platform to use the Ethereum Web3 library as an example to introduce the implementation of functions related to accounts, assets, transactions, and smart contract calls.



### 2.Resource reference

VS2019 creates a c# -Winform project, click Project -> Manage Nuget Packages, search for NBitcoin and Nethereum to download related packages.



### 3.process introduction

**1. Account related**

![image](images\p1.png)

**2. Transaction related**

![image](images\p2.png)

### 4. related function code examples and instructions

**1. Account related**
Account information includes private key, public key, address, and create related objects



```
string privateKey; //private key

string publicKey; //public key

string address; //address

```

 

* 1.1 Generate mnemonic
  The mnemonic is generated by randomly selecting 12 permutations of specific 1024 English words. It is an important means of generating an account. The code for generating the mnemonic is as follows:

```
Mnemonic mnemonic = new Mnemonic(Wordlist.English, WordCount.Twelve);

return mnemonic.ToString();

```

 

* 1.2 Generate account by mnemonic
  One mnemonic can generate N wallet accounts, and the specified account can be generated by specifying the index. code show as below:

```
//index starts from 0, and an infinite number of accounts can be generated.

Nethereum.HdWallet.Wallet wallet = new Nethereum.HdWallet.Wallet("Mnemonic", "");

address = wallet.GetAccount(index).Address;

private key = wallet.GetAccount(index).PrivateKey;

public key = wallet.GetAccount(index).PublicKey;

```

 

* 1.3 Generate account through private key
  When you have generated a wallet account, you can obtain the relevant information of the account corresponding to the private key through the private key of the account.

code show as below:

```
Nethereum.Web3.Accounts.Account myAccount = new Nethereum.Web3.Accounts.Account("Private key");

address = myAccount.Address;

private key = myAccount.PrivateKey;

public key = myAccount.PublicKey;

```

 

**2. Transaction related**
parameter configuration

| noun             | definition                   |
| ---------------- | ---------------------------- |
| mUrl             | The domain name of the chain |
| mChainId         | chain id                     |
| mContractAddress | Contract Address             |
| mContractAbi     | Locally store ABI files      |

* 2.1 Import ABI document
  Through the ABI document, you can view the name of the contract method, input parameters and return parameters. This document takes the balance query and transfer as an example. The ABI document is as follows, and it is added to the project project:

```
[{"inputs":[{"internalType":"address","name":"account","type":"address"}],"name":"balanceOf","outputs":[{"internalType ":"uint256","name":"","type":"uint256"}],"stateMutability":"view","type":"function"},

{"inputs":[{"internalType":"address","name":"to","type":"address"},{"internalType":"uint256","name":"amount"," type":"uint256"}],"name":"transfer","outputs":[{"internalType":"bool","name":"","type":"bool"}],"stateMutability ":"nonpayable","type":"function"}]

```

* 2.2 Check balance

 

For all query interfaces of Web3.js, you can view related documents of Web3.js.

Contract query can query related information, such as token balance, token name, token symbol, etc., through the contract method without consuming gas. 

 

```
//Query W3FS balance 

Nethereum.Web3.Web3 web3 = new Web3(mUrl);

HexBigInteger balance = web3.Eth.GetBalance.SendRequestAsync("Address").Result;

 

//Query the token balance, the method name is balanceOf, and the parameter is the account address

//Other queries of the contract and so on, enter the method name and parameters

Nethereum.Web3.Web3 web3 = new Web3(mUrl);

var myContract = web3.Eth.GetContract(mContractAbi, mContractAddress);

Sting balance = myContract.GetFunction("balanceOf").CallAsync<String>("address");

```

 

* 2.3 Transactions
  Before formally initiating a contract transaction, you need to obtain the minimum gas to be paid for the transaction according to the transaction parameters. Through the contract ABI, we know that the transfer method is called transfer, the input parameters are to and amount, the types are address and uint256 respectively, and the output parameter is bool , the implementation code and the code for obtaining gas are as follows:

```
 

//Initialize Web3

Nethereum.Web3.Web3 web3 = new Web3(mUrl);

 

 

//Get the data of the transaction

var myContract = web3.Eth.GetContract(mContractAbi, mContractAddress);

string data = myContract.GetFunction("transfer").GetData("Receiver address", "Transfer amount");

//data: "0xa9059cbb00000000000000000000000c3a6aff8275ce26dd1a2666624300015a027709

//400000000000000000000000000000000000000000000000002aa1efb94e0000"

 

 

//Estimate the amount of gas

TransactionInput tsInput = new TransactionInput();

tsInput.From = "Sender address";

tsInput.To = "Receiver address";

//If it is a token transfer or a contract transaction (such as minting), the address of the token contract is passed here,

//If it is W3FS coin transfer, pass the address of the other party

tsInput.Data = "0xa9059cbb0000………2aa1efb94e0000"; //If it is a transfer of W3FS coins, no need to pass

tsInput.Value = new HexBigInteger(1250000000000000000); //transfer 1.25 coins

CallInput callInput = (CallInput)tsInput;

tsInput.Gas = web3.Eth.TransactionManager.EstimateGasAsync(callInput).Result;

 

 

//Estimate the price of gas, the unit is GWei

tsInput.GasPrice = web3.Eth.GasPrice.SendRequestAsync().Result;

 

 

//Get Nonce

var txCount = web3.Eth.Transactions.GetTransactionCount.SendRequestAsync("Sender address").Result;

tsInput.Nonce = txCount;

 

 

// Calculate transaction code

Nethereum.Web3.Accounts.Account myAccount = new Nethereum.Web3.Accounts.Account("Sender's Private Key");

Nethereum.Web3.Accounts.AccountOfflineTransactionSigner tx = new Nethereum.Web3.Accounts.AccountOfflineTransactionSigner();

string encoded = tx.SignTransaction(myAccount, tsInput, mChainId); //mChainId is W3FS's chain Id

 

 

//Calculate transaction hash

string transactionHash = web3.Client.SendRequestAsync<string>("web3_sha3", null, "0x" + encoded).Result;

 

 

// initiate transaction

var hash = web3.Eth.Transactions.SendRawTransaction.SendRequestAsync("0x" + encoded).Result;

```

* 2.4 View transaction status

```
//After initiating the transaction, check the transaction receipt

Nethereum.Web3.Web3 web3 = new Web3(mUrl);

 

TransactionReceipt receipt = web3.Eth.Transactions.GetTransactionReceipt.SendRequestAsync("Transaction hash").Result;

if (receipt == null)

{

//in transaction

}

else

{

//Get the actual amount of gas consumed

int gasUsed = receipt.GasUsed.Value.ToString();

if (receipt.Logs != null && receipt.Logs.Count >= 2 && receipt.Status.Value == 1)

{

//The transaction is successful

}

else

{

//transaction failed

}

}

```

 



***

## W3FS decentralized storage development documentation

### 1. Background introduction

As an important module of the W3FS network, W3FS decentralized storage is an efficient decentralized file storage system. It is technically combined with the DSCAN (proxy cdn) technology system to further improve the efficiency of file storage and download. His launch has greatly lowered the threshold for the use of decentralized storage, allowing everyone to easily get started and have an excellent user experience. The purpose of this document is to introduce to developers or development teams how to integrate and use W3FS network decentralized storage related services.

The following will explain in detail how to integrate the relevant functions of the decentralized storage of the W3FS network (please replace the example domain name (http://W3FSMainNet:8545) used in the following with the actual network of W3FS).

***

 

**Reading prerequisites**

* Have read the relevant documents of W3FS-SDK encryption and decryption.

* Familiar with web3js and smart contract function calls.

* Have read the code related to W3FS network transaction access.

* Understand the basic request and response messages of the http protocol.

* Understand the basic request and response messages of the RPC protocol.

 

***

### 2. Definition of nouns



| noun          | explain                                                      |
| ------------- | ------------------------------------------------------------ |
| Entire file   | When a file is stored, whether it is an encrypted file or not, it is uploaded and stored in the form of the entire file, which is called the entire file |
| Separate file | When the file is stored, first use the encryption interface in W3FS-SDK to encrypt the file, and then generate the file head and body, and upload and store the file separately, which is called separate file |
| oriHash       | Use the sha256 hash algorithm to calculate the 32-byte oriHash of the entire original file (unencrypted), starting with "0x", a total of 66 hexadecimal characters |
| storeKey      | The current user's account address (EOA) is spelled with oriHash (remove 0x) and the value obtained is called storeKey, which starts with "0x", a total of 106 hexadecimal characters |
| storeKeyHash  | Perform sha256 algorithm operation on storeKey again to get a 32-byte storeKeyHash, starting with "0x", a total of 66 hexadecimal characters |
| headHash      | The head (electronic envelope area) is encrypted and generated by W3FS-SDK, and the hash value obtained by the "SHA-256" digest algorithm of the head file starts with "0x", a total of 66 hexadecimal characters |
| bodyHash      | The hash value of the body part of the ciphertext encrypted by W3FS-SDK is obtained by the "SHA-256" digest algorithm, starting with "0x", a total of 66 hexadecimal characters |
| minerId       | Id of the storage node, starting with "0x", a total of 66 hexadecimal characters |
| fileExt       | File extension information                                   |
| fileSize      | File size                                                    |



 

***

 

### 3. Two usage scenarios of decentralized storage

In the decentralized storage file system of the W3FS network, two usage scenarios are designed in order to meet the needs of diversified users. 

1. Ordinary decentralized storage scenarios with data backup as the main purpose,Called **Entire File Storage**. 
2. The transaction scenario with the characteristics of file ownership and the security control of file permissions is called **separate file storage**. Users can choose which storage scenario to use according to their customized business needs.

It needs to be clear that the entire file and the separate file are two independent API implementations stored in the same decentralized storage file system, and the files stored in the two storage methods are unrelated to each other, that is to say,  a file file1 that has already stored the entire file in the storage node can also use the method of separate file to initiate storage again without being rejected in the same decentralized storage file system.

 

#### 3.1. Entire file storage ( ordinary decentralized storage scenario )

Like most decentralized storage, we offer to store a file directly into the W3FS network's decentralized storage file system. And before storage, according to different business requirements, the storage initiator can decide whether to encrypt and then store the file.

 

Before initiating the storage of a entire file, the following concepts need to be clarified:

* **address**: The EOA address of the user in the W3FS network, a 20-byte 16-mechanism string. For example: 0x687b5a626340EFfE324118F172092344Dd7FcB49.

* **oriHash**: Use the sha256 hash algorithm to calculate the 32-byte oriHash for the entire file to be stored (whether the file itself is encrypted or not). Such as: 0xe8452fc5541baa5c085455ba769cd163542cc491d05c721682153fde149bda22

* **storeKey**: Add oriHash to address (oriHash removes 0x during splicing) to get storeKey. For example: 0x687b5a626340EFfE324118F172092344Dd7FcB49e8452fc5541baa5c085455ba769cd163542cc491d05c721682153fde149bda22

* **storeKeyHash**: Perform the sha256 algorithm operation on the storeKey again to obtain a 32-byte storeKeyHash. For example: 0x5a31eb46ec62617cc4416746f14b7a777007441a477d1e87344a65ae35460c10

 

##### entire file storage core process

* a.**Calculation file storage information**

Dapp selects the file file1 to be stored (whether the file is encrypted or not), and calculates the oriHash, storeKey, and storeKeyHash of file1. And get the file size and file type of file1.

***

 

* b. **Select the target node for file storage**.

Call the json-rpc interface (w3fs_getMiners4Entire) provided by the decentralized storage to obtain the node list. Select a node as the storage destination node. It should be reminded that for the same file, when the entire file is used for storage, each node can only successfully store it once, unless the same file is stored on different nodes to achieve the purpose of multi-node backup.

```
curl -H "Content-Type:application/json" -X POST --data '{"jsonrpc":"2.0","method":"w3fs_getMiners4Entire","params":[{ "minerNum":4,"storeKey ":" 0x687b5a626340EFfE324118F172092344Dd7FcB49e8452fc5541baa5c085455ba769cd163542cc491d05c721682153fde149bda22 "}],"id":1}'

http://w3fsMainNet:8545

Parameter Description:
minerNum: Specifies the number of storage nodes returned.
storeKey: The storeKey is obtained by spelling the address with oriHash (oriHash without 0x) .
type: The returned node list type. stored (default), unstored, both.
 

Return data description:

{"jsonrpc":"2.0","id":1,"result":[{"minerId":"0x741e86df5954cab0ffa480085c18c1e23ab0958851caa89e5e38adad9bcf5f16","status":false,"publicKey":"304d03020700020120022100f863e92900a68cf033f253be61f80e188ecf41b3032544fd72c069995ec8d2b4022100e29346cfe14f1d7ba9e3685cf5e2d59c0cd75aba6f64ea533f1d62c7d9881eee","freeSpaceRatio":0.33}]}

Parameter Description:

minerId : Node Id.
status : Whether the file corresponding to the storeKey has a storage record on this node. In actual use, which nodes can be stored and which nodes have been stored can be selected according to the field value.
publicKey: The public key for encryption and decryption of the file corresponding to the node. (Required for separate file storage scenarios)
freeSpaceRatio: The free space ratio. (The ratio of the free storage space of each node in the returned list)

Absenteeism selection recommendation algorithm: the value of freeSpaceRatio in the node list returned by the requester calling the interface is accumulated in sequence, and the value is 1. Dapp can generate a random number with a value of 0 to 1 locally, which is decremented in the order of the returned node list. Go to the freeSpaceRatio value of each node until the generated random number is less than or equal to 0, the current node is the hit storage node.
   

 

```

***

 

* c. **Call the storage contract to save the storage information**.

In order to ensure the purity of the decentralized storage environment, it is necessary to register the file information in the smart contract associated with the decentralized storage before initiating storage.

The called **storage smart contract address is fixed as: 0x000000000000000000000000000000000003002**. The contract function for file information registration is defined as follows:

```
To ensure the purity of the W3FS storage environment, a small amount of value and gas needs to be paid before storing files.First call the function in the following contract to obtain the cost of the file to be stored this time.

function getFileCost(
uint256 fileSize, //The size of the file
)

After calling this function,You can obtain a value of type Uint256 stored this time.

Contract file information registration function and related parameters,At the same time, you need to pay the value of the file store obtained in the previous step

function createFileStoreInfo4Entire(

bytes32 storeKeyHash, //storeKey is the 32-byte value calculated by sha256, starting with 0x

uint256 fileSize, //The size of the file

   string calldata fileExt, //type of file

bytes32 minerId //Selected storage node Id

)

The event emitted after the contract invocation is successful

event newFileStoreEvt(

bytes oriHash, // for the entire file: oriHash, for the separate file: storeKeyHash

address userAddr, // user address

uint256 fileSize, // fileSize

string fileExt,

bytes minerId, // minerId

bytes headHash, // headHash

bytes bodyHash, // bodyHash

uint256 operTime // operTime

);

```

Wait for the transaction to return to the logs log to make sure the message has been processed. If the registration is completed, proceed to the following steps. Otherwise continue to wait or exit. Storage requests that have not yet registered the file information in the storage contract will be rejected by the system.

***

 

* d. **Start file upload**

File upload can decide which upload method to use according to the size of the file to be uploaded. There are two ways of uploading small files and uploading large files in slices. Small files and large files are generally limited to 30M. Dapp can decide which upload method to use according to its own needs and scenarios.

For the specific upload implementation, please refer to the detailed introduction to file upload in Chapter 4.

***

 

* e. **call file storage**

After the file is uploaded, you can call the json-rpc interface (w3fs_clientSend4Entire) of the entire file storage to start the storage.

**Request data**

```
 curl -H "Content-Type:application/json" -X POST --data '{"jsonrpc":"2.0","method":"w3fs_clientSend4Entire","params":[{"storeKey":"0x211fA1DDbE3d000e1a42921eC56bBE7A923A6BeDe8452fc5541baa5c085455ba769cd163542cc491d05c721682153fde149bda22", "minerId":"0x0ffeb2e287089058b7b7e93284c8107cef04b3ac693e826233aa0c2b802a42a2","file":"0xe8452fc5541baa5c085455ba769cd163542cc491d05c721682153fde149bda22"}],"id":1}' http://w3fsMainNet:8545

```

| parameter name | type   | description                                                  |
| -------------- | ------ | ------------------------------------------------------------ |
| storeKey       | String | Hexadecimal string starting with 0x, a total of 106 characters, composed of user EOA address + oriHash (without 0x) |
| minerId        | string | hexadecimal string starting with 0x, a total of 66 characters, must be the same minerId provided when calling the storage contract to save the information |
| file           | String | The result of the sha256 algorithm calculation of the uploaded file, the hexadecimal string starting with 0x, a total of 66 characters |

**Return value description**

Status: 200- means the submission is successful, 500 means the submission fails, and the specific error information is given in the Message

 

 

***

 

* f. **Query file storage status**

After calling the file storage rpc interface and returning successfully, you need to query the storage status. Only the files that have been stored can be downloaded normally. It is recommended to poll the json-rpc interface (w3fs_getStorageStatus4Entire) for querying the storage status.

**Request data**

 

```
curl -H "Content-Type:application/json" -X POST --data '{"jsonrpc":"2.0","method":"w3fs_getStorageStatus4Entire","params":[{ "storeKey":"0x211fA1DDbE3d000e1a42921eC56bBE7A923A6BeDe8452fc5541baa5c085455ba769cd163542cc491d05c721682153fde149bda22", "minerId":"0x0ffeb2e287089058b7b7e93284c8107cef04b3ac693e826233aa0c2b802a42a2"}],"id":1}' http://w3fsMainNet:8545

```

| parameter name | type   | description                                                  |
| -------------- | ------ | ------------------------------------------------------------ |
| storeKey       | String | A hexadecimal string starting with 0x, a total of 106 characters, composed of user EOA address + oriHash (without 0x) |
| minerId        | string | A hexadecimal string starting with 0x, a total of 66 characters, must be the same as the minerId provided when calling the start storage |

**Return value description**

   

```
{"jsonrpc":"2.0","id":1,"result":{"Status":200,"Message":"success","Timestamp":"2022-03-28T05:51:11.711594603Z" }}

```

​      

 

Status: 0 means initial, 100 means being processed, 200- means submission is successful, 400 means timeout, 500 means storage failure, and Message gives specific error information.

In particular, if it is 200, it means that the storage is complete. If it is 100, when submitting clientSend with the same parameters again, the request will be ignored.

Status: 200- means the submission is successful, 500 means the submission fails, and the specific error information is given in the Message

 

***

 

##### Download process of the entire file

A file can be downloaded if it has been stored normally in the decentralized storage of the w3fs network and the storage status is completed. Downloads for w3fs Network Decentralized Storage are free. The download is divided into two steps: 1. Retrieve the file, 2. Download the file.

* **Call the retrieval json-rpc interface (w3fs_clientRetrieval4Entire) of the entire file to retrieve the file**.

**Request data**

```
curl -H "Content-Type:application/json" -X POST --data '{"jsonrpc":"2.0","method":"w3fs_clientRetrieval4Entire","params":[{ "storeKey":"0xcdd122382f79686f9a46c37a899f2a6c5ff119097ef938e3998f3a32a7774 ],"id":1}' http://w3fsMainNet:8545

```

| parameter name | type   | description                                                  |
| -------------- | ------ | ------------------------------------------------------------ |
| storeKey       | String | A hexadecimal string starting with 0x, a total of 106 characters, composed of user EOA address + oriHash (without 0x) |

 

**Return value description**

Status: 200- means the submission is successful, 500 means the submission fails, and the specific error information is given in the Message

       If 200 is returned, Message is a json string in the format of the example below.

```
{"jsonrpc":"2.0","id":1,"result":{"Status":200,"Message":"{\"FileExt\":\"txt\",\"FileSize\": 1234}","Timestamp":"2022-06-02T07:04:44.244707303Z"}}

```

**Query file retrieval status (w3fs_clientRetrieval4Status)**

**Request data**

```
curl -H "Content-Type:application/json" -X POST --data '{"jsonrpc":"2.0","method":"w3fs_clientRetrieval4Status","params":[{ "storeKey":"0xcdd122382f79686f9a46c37a899f2a6c5ff119097ef938e3998f3a32a774 ],"id":1}'

```

| parameter name | type   | description                                                  |
| -------------- | ------ | ------------------------------------------------------------ |
| storeKey       | String | A hexadecimal string starting with 0x, a total of 106 characters, composed of user EOA address + oriHash (without 0x) |

 

**Return value description**

Status: 0 means initial, 100 means being retrieved, 200- means successful submission, 400 means timeout, 500 means submission failure, and Message gives specific error information.

In particular, if it is 200, further downloads can be made. If it is 100, submitting clientRetrieval4Entire again will be ignored.

 

```
{"jsonrpc":"2.0","id":1,"result":{"Status":200,"Message":"","Timestamp":"2022-03-25T09:22:38.542321127Z"} }

```

 

 

 

***

  

* Start file download

If the file retrieval status returns Completed. You can start the download of the file. For the specific download implementation, please refer to the detailed introduction to the entire file download in Chapter 4.

 

 

***




#### 3.2 separate file storage

Different from the storage of the entire file, the separate file storage refers to the file storage type that conforms to the W3FS protocol specification. Its core is an encrypted file. In order to facilitate access control and distribution, the file is split into a file header and a file body, and the two files are uploaded, stored, retrieved, downloaded, and then spliced into a single file for use.

The separate file must be encrypted, and the encryption method provided by the W3FS protocol is required to generate the file head and the file body.

Separate file storage is suitable for some scenarios where Dapp needs to adjust the file authorization. The core of his operation is to call the authorization interface of W3FS-SDK before storing the file after the file is encrypted to grant the identity managed by Dapp the permission to operate the file. After the file is downloaded, the identity managed by Dapp has been granted modification before storage. Therefore, the file head can be dynamically adjusted, and finally assembled with the file body into a complete file with new identity information. The core purpose of this operation process is that when some uploaded separate files need to be authorized to modify the identity, there is no need to re-store a new complete encrypted file after adjusting the file permissions every time.

##### Separate file storage core process

**a. Encryption**. The dapp calls the encryption interface of W3FS-SDK (for the specific implementation, please refer to the W3FS-SDK access documentation) to encrypt the files to be stored and generate the file head and body. There is only one Owner authority by default in the head. The dapp side decides whether to add other identity accounts for adjusting the file head according to its own business needs, such as the identity managed by the central server or the identity of the storage node (which requires the auxiliary authorization of the decentralized storage system). The identity of the storage node can be added to the separate file). 

 

***

* **b. Select the target node for storage**.

Call the json-rpc interface (w3fs_getMiners) provided by the decentralized storage to obtain the node list. Select a node as the storage destination node. It should be reminded that the same file can be stored on different nodes multiple times, but a separate file in each node can only be successfully stored once.

```
curl -H "Content-Type:application/json" -X POST --data '{"jsonrpc":"2.0","method":"w3fs_getMiners","params":[{ "minerNum":50,"oriHash ":"0x687b5a626340EFfE324118F172092344Dd7FcB49e8452fc5541baa5c085455ba769cd163542cc491d05c721682153fde149bda22"}],"id":1}'

http://w3fsMainNet:8545

Parameter Description:
minerNum: Specifies the number of storage nodes returned.
oriHash: The hexadecimal string of the sha256 value of the plaintext of the file.
type: The returned node list type. stored (default), unstored, both.
 

Return data description:

{"jsonrpc":"2.0","id":1,"result":[{"minerId":"0x741e86df5954cab0ffa480085c18c1e23ab0958851caa89e5e38adad9bcf5f16","status":false,"publicKey":"304d03020700020120022100f863e92900a68cf033f253be61f80e188ecf41b3032544fd72c069995ec8d2b4022100e29346cfe14f1d7ba9e3685cf5e2d59c0cd75aba6f64ea533f1d62c7d9881eee","freeSpaceRatio":0.33}]}

 

Parameter Description:
minerId: Node Id.
status: Whether the file corresponding to the storeKey has a storage record on the node.
publicKey: The public key for encryption and decryption of the file corresponding to the node.
freeSpaceRatio: The free space ratio. (The ratio of the free storage space of each node in the returned list)

Absenteeism selection recommendation algorithm: the value of freeSpaceRatio in the node list returned by the requester calling the interface is accumulated in sequence, and the value is 1. Dapp can generate a random number with a value of 0 to 1 locally, which is decremented in the order of the returned node list. Go to the freeSpaceRatio value of each node until the generated random number is less than or equal to 0, the current node is the hit storage node.
 

```

 

***

* **c. Invoke the storage contract to save the storage related information of the separate file**.

Like the entire file storage, the information of the separate files needs to be registered in the storage smart contract before starting the storage. The smart contract registration function is defined as follows:

```
Separate file registration file information contract method and parameters

function createFileStoreInfo(

bytes32 oriHash,//The 32-byte hexadecimal string calculated by the sha256 algorithm of the plaintext state of the file

uint256 fileSize, //The size of the encrypted file. (total size of head and body)

string calldata fileExt,//type of file

bytes32 minerId,//Storage node Id

bytes32 headHash,//The 32-byte hexadecimal string calculated by the sha256 algorithm of the head part of the file

bytes32 bodyHash //The 32-byte hexadecimal string calculated by the sha256 algorithm of the body part of the file

)

The event emitted after the contract invocation is successful

event newFileStoreEvt(

bytes oriHash, // for the entire file: storeKeyHash, for the separate file: oriHash

address userAddr, // user address

uint256 fileSize, // fileSize

string fileExt,

bytes minerId, // minerId

bytes headHash, // headHash

bytes bodyHash, // bodyHash

uint256 operTime // operTime

);

```

Wait for the transaction to return to the logs log to make sure the message has been processed. If the registration is completed, proceed to the following steps. Otherwise continue to wait or exit.

 

***

* **d. upload files (head and body are uploaded separately)**.

When uploading a separate file, you need to divide it into two separate files, head and body, for uploading. File upload can decide which upload method to use according to the size of the file to be uploaded. There are two ways of uploading small files and uploading slices of large files. There are no fixed restrictions on the definition of small files and large files, and Dapp can decide which upload method to use according to its own special scenarios.

For the specific upload implementation, please refer to the detailed introduction to the separate file upload in Chapter 4.

***

* **e.store separate files (head and body are stored separately)**.

Like uploading, the storage of separate files also needs to be divided into two parts for storage calls.

**Request data**

```
curl -H "Content-Type:application/json" -X POST --data '{"jsonrpc":"2.0","method":"w3fs_clientSend","params":[{"oriHash":"0x211fA1DDbE3d000e1a42921eC56bBE7A923A6BeDe8452fc5541baa5c085455ba769cd163542cc491d05c721682153fde149bda22", "minerId":"0x0ffeb2e287089058b7b7e93284c8107cef04b3ac693e826233aa0c2b802a42a2","headFlag":true,"file":"0xe8452fc5541baa5c085455ba769cd163542cc491d05c721682153fde149bda22"}],"id":1}' http://w3fsMainNet:8545

```

| parameter name | type    | description                                                  |
| -------------- | ------- | ------------------------------------------------------------ |
| oriHash        | String  | A 32-byte hexadecimal string with a 0x prefix calculated by the sha256 algorithm of the source file, a total of 66 characters |
| minerId        | string  | A hexadecimal string starting with 0x, a total of 66 characters, must be the same minerId |
| headFlag       | boolean | Whether the uploaded file part is the file header            |
| file           | string  | A 32-byte hexadecimal string with a 0x prefix calculated by the sha256 digest algorithm for the head or body of the file, a total of 66 characters |

**Return value description**

Status: 200 means the submission is successful, 500 means the submission fails, and the specific error information is given in the Message

 

***

* **f. query file storage status**

After calling the storage rpc interface of the separate file and returning successfully, you need to query the storage status. Only the files that have been stored can be downloaded normally. Don't remind me that the retrieval of a separate file also requires two file parts to be retrieved separately. Only when both parts are stored can the storage of the separate file be completed. It is recommended to call the rpc interface (getStorageStatus) for querying the storage status by polling.

**Request data**

 

```
curl -H "Content-Type:application/json" -X POST --data '{"jsonrpc":"2.0","method":"w3fs_getStorageStatus","params":[{ "oriHash":"0x211fA1DDbE3d000e1a42921eC56bBE7A923A6BeDe8452fc5541baa5c085455ba769cd163542cc491d05c721682153fde149bda22", "minerId":"0x0ffeb2e287089058b7b7e93284c8107cef04b3ac693e826233aa0c2b802a42a2","headFlag":true}],"id":1}' http://w3fsMainNet:8545

```

| parameter name | type    | description                                                  |
| -------------- | ------- | ------------------------------------------------------------ |
| oriHash        | String  | A 32-byte hexadecimal string with a 0x prefix calculated by the sha256 algorithm of the source file, a total of 66 characters |
| minerId        | string  | A hexadecimal string starting with 0x, a total of 66 characters, must be the same minerId |
| headFlag       | boolean | Whether the uploaded file part is the file header            |

​       

**Return value description**

  

```
{"jsonrpc":"2.0","id":1,"result":{"Status":200,"Message":"success","Timestamp":"2022-03-28T05:51:11.711594603Z" }}

```

​     

 

Status: 0 means initial, 100 means being processed, 200- means submission is successful, 400 means timeout, 500 means storage failure, and Message gives specific error information.

In particular, if it is 200, it can indicate that the storage is complete. If it is 100, when submitting clientSend with the same parameters again, the request will be ignored.

Status: 200- means the submission is successful, 500 means the submission fails, and the specific error information is given in the Message

 

***

  

##### Separate file download

Like the entire file download process, the separate file download process is also divided into two parts: file retrieval and file download. The difference from the entire file is that the retrieval and download of the separate file are divided into two independent files.

**File retrieval (head or body) (w3fs_clientRetrieval)**.

**Request data**

```
curl -H "Content-Type:application/json" -X POST --data '{"jsonrpc":"2.0","method":"w3fs_clientRetrieval","params":[{ "oriHash":"0xcdd122382f79686f9a46c37a899f2a6c5ff119097ef938e3998f3a32a7774d8" "headFlag":true}],"id":1}'

```

| parameter name | type    | description                                                  |
| -------------- | ------- | ------------------------------------------------------------ |
| oriHash        | String  | A 32-byte hexadecimal string with a 0x prefix calculated by the sha256 algorithm of the source file, a total of 66 characters |
| headFlag       | boolean | Whether the uploaded file part is the file header            |

 

**Return value description**

Status: 200- means the submission is successful, 500 means the submission fails, and the specific error information is given in the Message

If it returns 200, the Message is a json string in the format of the example below.

```
{"jsonrpc":"2.0","id":1,"result":{"Status":200,"Message":"{\"FileExt\":\"txt\",\"FileSize\": 1234}","Timestamp":"2022-06-02T07:04:44.244707303Z"}}

```

***

 

* **Query file retrieval status (head or body) (w3fs_getRetrievalStatus)**.

  

```
curl -H "Content-Type:application/json" -X POST --data '{"jsonrpc":"2.0","method":"w3fs_getRetrievalStatus","params":[{ "oriHash":"0xcdd122382f79686f9a46c37a899f2a6c5ff119097ef938e3998f3a32a7774d" "headFlag":true}],"id":1}' http://w3fsMainNet:8545

```

| parameter name | type    | description                                                  |
| -------------- | ------- | ------------------------------------------------------------ |
| oriHash        | String  | A 32-byte hexadecimal string with a 0x prefix calculated by the sha256 algorithm of the source file, a total of 66 characters |
| headFlag       | boolean | Is the retrieved file part a file header                     |

 

**Return value description**

Status: 0 means initial, 100 means being retrieved, 200- means successful submission, 400 means timeout, 500 means submission failure, and Message gives specific error information.

In particular, if it is 200, further downloads can be made. If it is 100, submitting clientRetrieval again will be ignored.

```
{"jsonrpc":"2.0","id":1,"result":{"Status":200,"Message":"","Timestamp":"2022-03-25T09:22:38.542321127Z"} }

```

 

***

  

* Separate file download

separate file also needs to be divided into two files to be downloaded independently, and finally assembled into one file for use. For the specific download implementation, please refer to the detailed introduction to the separate file download in Chapter 4.

 

***

#### 3.3. Separate file storage process assisted by the decentralized storage system

The W3FS encryption protocol ensures the security of the entire life cycle of the file. The combination of the characteristics of W3FS and the decentralized storage of the w3fs network is used in scenarios that require file copyright management (including but not limited to NFT transactions), so that the viewing rights or ownership rights of stored files can also be safely managed.

The w3fs network decentralized storage system cooperates with the W3FS protocol to provide special support for scenarios that require file copyright management. This technology enables files to be dynamically and securely granted or modified without Dapp participation (including but not limited to NFT lease or transfer scenarios).

After the developer completes the integration of the relevant steps, the following points can be achieved:

* 1. The first storage caller of the NFT file is the default Owner of the file in the storage system.

* 2. When the owner of the file leases or sells the file (including but not limited to NFT scenarios), the owner of the file in the storage system will have the corresponding authorization to modify it.

* 3. When the file purchaser or renter downloads the file, the storage system will dynamically obtain the corresponding file operation authority according to the user's authorization record and the purchase record in the transaction, without the need for additional authorization by the DAPP.

 

In order to achieve the above points, the following integration steps need to be completed.

 

 

* **a. Authorization**, the realization of the dynamic modification process of the file header is based on the storage of separate files. After selecting the target node to be stored, the file storer needs to add the corresponding authority for file operation in the file head to the file encryption/decryption identity corresponding to the target node.

(For the specific implementation, please refer to the corresponding authorization interface of W3FS-SDK). Make the stored target node have permission to perform corresponding operations on the file.

In the rpc interface for obtaining the node list of the separate file, the publicKey field in the obtained node list object is the file encryption and decryption identity public key of the node. Before the user performs separate storage, the identity needs to be granted the permission to operate the file.

***

* **b. When NFT is listed, set the smart contract address corresponding to the designated Dapp as a trusted address**, so that the authorized contract address has the authority to modify the file Owner.

When the NFT corresponding to the separate file is minted and listed in the dapp smart contract, the owner of the separate file in the storage system (the owner of the file currently in the decentralized storage) needs to call the registration authorization function of the storage smart contract. Set the smart contract address corresponding to the Dapp as a trusted address.

 

```
A function for smart contracts to register trusted Dapp addresses

function regDappContractAddr(

bytes32 oriHash,//The 32-byte hexadecimal string with 0x prefix calculated by the sha256 algorithm of the source file, a total of 66 characters

address dappContractAddr // set to the address of the trusted Dapp

) external;

//When the address of a contract is set to be trusted, the address will have the right to modify the Owner of an NFT file in the storage system, and the contract events sent by the address are also trusted.

```

***

* **c. Dapp modifies the file Owner and emits standard events**.

In the smart contract corresponding to the NFT, the standard events defined in the storage contract must be issued when a lease or transfer action occurs. If the current NFT transaction event is the Owner's transfer event, it is necessary to additionally call the permission transfer interface provided by the storage contract to change the Owner of the file in the storage system to the Owner of the new purchaser.

```
//Standard events in decentralized storage contracts. All smart contracts that need to implement the storage system to dynamically adjust the header of the separate file must follow this interface, and issue a PurchaseVoucher event when transferring permissions or leasing transactions.

//This event is an authentication event for the storage system. When a user leases or buys an NFT, the Dapp where the NFT is located sends out this event after the owner transfer within the platform. Once the user needs to download the separate file corresponding to the NFT, the storage system will

//The relevant total segment value in the standard event is authenticated. For retrieval and download requests that meet the rules, the file head is dynamically adjusted and returned to the requester directly.

interface IEncrytyStorage{

event PurchaseVoucher

(

bytes32 oriHash,//The 32-byte hexadecimal string with 0x prefix calculated by the sha256 algorithm of the source file, a total of 66 characters

address consumer,//The renter or buyer of an NFT file

uint8 purchaseType,//Event type. 0: Purchase, 1: Lease

string userFilePubkey,//The file encryption and decryption public key of the renter or purchaser. Required parameters when the storage contract dynamically adjusts the header of the separate file.

uint256 validityDate, // The expiration date of the validity period of the leased NFT file. The type is a UTC timestamp, accurate to the second. If the document expires on January 1, 2030, please fill in 1893427200.

uint256 createDate,//The event stamp of the event emitted by this event, the type is UTC timestamp, accurate to seconds

string extraInfo //Reserved extension fields.

);

    }

 





//Decentralized storage is specially designed and developed for the Dapp trusted by NFT. The function of modifying the owner of the separate file in the storage system is developed. This function must be the Dapp address trusted by the NFT file before it can be called normally.

function transferFileOwner(

bytes32 oriHash,

address ownerAddr

) external;

//If the contract address of a Dapp has been trusted by a certain file, after the contract calls the transferFileOwner function, it can directly set a certain address as the new Owner of the file. At the same time, all trusted Dapps set by the previous Owner will be cleared.

//The Owner in the new storage system needs to reset the trusted Dapp address when relisting the NFT.

```

***

* d. **Use transactionHash for authentication**.

Dapp records the contract transaction hash of NFT lease and transfer. When the downloaded separate file needs to be stored in a decentralized manner to dynamically adjust the Head, the storage system needs to use transactionHash to query the corresponding data of the storage system standard events in the current transaction to authenticate.

***

 

* e. **Separate file authorization retrieval**. When the downloader of the file retrieves the file, the decentralized storage system will decide whether to allow the file retrieval request to dynamically modify the file according to whether it is the Owner in the storage system, or whether the transaction event contains the storage system standard event record. permissions.

```
    curl -H "Content-Type:application/json" -X POST --data

{"jsonrpc":"2.0","method":"w3fs_getAuthorizedHead","params":[{

"oriHash":"0xcdd122382f79686f9a46c37a899f2a6c5ff119097ef938e3998f3a32a7774d8f",

"headFlag":true ,

"txHash":"0x97117265dc58906cf616a88b13a58435086db90e52baf28eeb51a6d31afd3c72"}],"id":1}

http://w3fsMainNet:8545

```


| parameter name | type    | description                                                  |
| -------------- | ------- | ------------------------------------------------------------ |
| oriHash        | String  | A 32-byte hexadecimal string with a 0x prefix calculated by the sha256 algorithm of the source file, a total of 66 characters |
| headFlag       | boolean | Whether the uploaded file part is the file header            |
| txHash         | String  | The transaction Hash of buying or leasing NFT and issuing the standard event PurchaseVoucher |

 

 

**Return value description**

Status: 200- means the submission is successful, 500 means the submission fails, and the specific error information is given in the Message

If it returns 200, the Message is a json string in the format of the example below.

```
{"jsonrpc":"2.0","id":1,"result":{"Status":200,"Message":"{\"FileExt\":\"txt\",\"FileSize\": 1234}","Timestamp":"2022-06-02T07:04:44.244707303Z"}}

 

```

***

 

* f. **Separate file query authorization retrieval status**

```
curl -H "Content-Type:application/json" -X POST --data '{"jsonrpc":"2.0","method":"w3fs_getRetrievalStatus","params":[{ "oriHash":"0xcdd122382f79686f9a46c37a899f2a6c5ff119097ef938e3998f3a32a7774d" "headFlag": true, txhash: "0x97117265dc58906cf616a88b13a58435086db90e52baf28eeb51a6d31afd3c72"}],"id":1}' http://w3fsMainNet:8545

```

| parameter name | type    | description                                                  |
| -------------- | ------- | ------------------------------------------------------------ |
| oriHash        | String  | A 32-byte hexadecimal string with a 0x prefix calculated by the sha256 algorithm of the source file, a total of 66 characters |
| headFlag       | boolean | Whether the uploaded file part is the file header            |
| txhash         | String  | The transaction Hash of buying or leasing NFT and issuing the standard event PurchaseVoucher |

 

**Return value description**

Status: 0 means initial, 100 means being retrieved, 200- means successful submission, 400 means timeout, 500 means submission failure, and Message gives specific error information.

In particular, if it is 200, further downloads can be made. If it is 100, submitting clientRetrieval again will be ignored.

 

***

### 4. Decentralized storage file upload and download

The upload and download data packets of decentralized storage follow the http protocol. When the client requests, it can request and get and return according to the Http protocol specification.

#### 4.1 file upload

The parameter hash submitted when the file is uploaded is the sha256 value of the file to be uploaded (starting with 0x), regardless of whether the file is a entire file or a separate file. i.e. if it is an entire file upload,

The hash parameter value submitted when the file is uploaded is the result of the sha256 calculation of the source file to be uploaded (whether the file is encrypted or not).

If it is a separate file upload, the hash value is the result of the sha256 calculation of the head file or the body file.

 

1. **File upload interface** /uploadFile

client uploads , the small file directly calls the file upload interface

| parameter name | type      | description                                                  |
| -------------- | --------- | ------------------------------------------------------------ |
| name           | string    | file name                                                    |
| hash           | string    | source file sha256 digest, hexadecimal string starting with 0x, a total of 66 characters |
| file           | form file | source file itself                                           |

Outgoing parameters:

| parameter name | type   | description               |
| -------------- | ------ | ------------------------- |
| file           | string | source file sha256 digest |

Status code 400 Parameter error 500 Server error 200 The request is successful and the file parameter is returned

 

**For large files, first call the check file upload status interface to obtain the serial number list of sliced files that have been uploaded successfully, and then call the upload sliced file interface to upload only the slices that have not yet been uploaded. After all sliced files are uploaded, call merge. Dicing file interface**

2. **Check file upload status interface** /checkChunk

Instructions for entering parameters

| parameter name | type   | description                                                  |
| -------------- | ------ | ------------------------------------------------------------ |
| name           | string | file name                                                    |
| hash           | string | source file sha256 digest, hexadecimal string starting with 0x, a total of 66 characters |

Parameters

| parameter name | type   | description                                                  |
| -------------- | ------ | ------------------------------------------------------------ |
| state          | string | file name                                                    |
| chunkList      | Array  | Number of the chunked file, the number of the chunked file that has been uploaded successfully |
| file           | string | source file sha256 digest, hexadecimal string starting with 0x, a total of 66 characters |

Status code 400 Parameter error 500 Server error 200 Request successful

 

3. **Upload chunked file interface** /uploadChunk

Instructions for entering parameters

| parameter name | type      | description                                                  |
| -------------- | --------- | ------------------------------------------------------------ |
| chunkid        | string    | Number of chunk files (starting from 1)                      |
| hash           | string    | source file sha256 digest, hexadecimal string starting with 0x, a total of 66 characters |
| file           | form file | formulation of a certain block of the source file itself     |

 

Parameters

Status code 400 Parameter error 500 Server error 200 Request successful

 

4. **Merge Chunk File Interface** /mergeChunk

Instructions for entering parameters

| parameter name | type   | description                                                  |
| -------------- | ------ | ------------------------------------------------------------ |
| name           | string | file name                                                    |
| hash           | string | source file sha256 digest, hexadecimal string starting with 0x, a total of 66 characters |

 

Parameter description:

| parameter name | type   | description               |
| -------------- | ------ | ------------------------- |
| file           | string | source file sha256 digest |

Status code 400 Parameter error 500 Server error 200 The request is successful and the file parameter is returned

 

5. **Cancel upload interface** /cancelUpload

When the upload is canceled, the cancel upload interface is called , and the server clears the upload progress corresponding to the file

Instructions for entering parameters

| parameter name | type   | description                                                  |
| -------------- | ------ | ------------------------------------------------------------ |
| hash           | string | source file sha256 digest, hexadecimal string starting with 0x, a total of 66 characters |

Parameters

Status code 400 Parameter error 500 Server error 200 Request successful

 

#### 4.2. file download

client ( browser, app , etc. ) clicks to download, calls the download interface to download the file, a temporary file is generated locally, and the received bytes are written to the temporary file. The interface response header contains an Accept-Ranges : bytes proof service The terminal supports resuming download from breakpoints

When the download fails due to a network error, when the retry or continue button is clicked, the download file interface is called, and the request header carries the Range : bytes=100 - it proves that it was disconnected after downloading 100 bytes last time ( this number 100 is to obtain the local Obtain the total number of bytes of the temporary file generated by the previous download ) , as long as the part is not downloaded in this request, after all the download is complete, get the Etag of the response header : 0x6e01a511e93f29a83aab8265954b4cdff9984a1eb58b1a1d3fc73984dbe3a12e (0x+ Original file SHA256) to compare with the calculated local file SHA256 to verify the file Integrity, the last download was successful

The server and client fully follow the http-range development specification.

 

1. **Separate file download interface (separate file and separate authorization file)**  /downloadFile

| parameter name | type             | description                                                  |
| -------------- | ---------------- | ------------------------------------------------------------ |
| fileName       | string           | custom download file name                                    |
| oriHash        | string           | source file sha256 digest, hexadecimal string starting with 0x, a total of 66 characters |
| headFlag       | boolean          | is a header file                                             |
| txhash         | Transaction Hash | The transaction hash when an NFT lease or purchase event occurs, starting with 0x (optional parameter, this parameter needs to be passed when the separate file needs to dynamically authorize the head) |

 

Outgoing parameters:

Status code 400 Parameter error 500 Server error 200 Request successful 404 Resubmit retrieval

 

2. **entire file download interface** /downloadFile4Entire

| parameter name | type   | description                                                  |
| -------------- | ------ | ------------------------------------------------------------ |
| fileName       | string | custom download file name                                    |
| storeKey       | string | source file sha256 digest, hexadecimal string starting with 0x, a total of 66 characters |

 

Outgoing parameters:

Status code 400 Parameter error 500 Server error 200 Request successful 404 Resubmit retrieval

 
