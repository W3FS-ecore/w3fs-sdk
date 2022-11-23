
[TOC] 
## w3fs wallet local RPC server open interface documentation
**Introduction**: A local RPC server is enabled in the w3fs wallet application, and a rich functional interface is opened for web or external program calls. External Dapps can develop Dapps with custom business processes based on the relevant interfaces provided.These interfaces mainly include the following functional types:* Allow external Dapps to implement normal on-chain transactions under the w3fs network by calling the rpc interface, such as transfers, calling smart contracts, etc.* Allow external Dapp to call rpc interface to implement related functions provided in W3FS-SDK, such as file encryption, decryption, authorization and other operations.* Allow external Dapps to interact with the decentralized storage file system by calling the rpc interface. 
 
Example of an interface call message
```
The Web uses the normal rpc request method, the Context-Type is application/x-www-form-urlencoded,
The request ip is: 127.0.0.1:9687
The request parameter params is an array, and the parameter name and type are defined according to the interface
Request example:
jsonrpc=2.0&id=1&method=createKeyPair&params[seed]="value"
Example of interface return:
{
"jsonrpc":"2.0",
"id":1,
"result":{
"nRet":0,
"filePublicKey":"aaaaaa",
"filePrivateKey":"bbbbbb",
"keyId":"cccccc"
}
}
```
---
 
 
## 1. js calls the native interface and the use of related tools
 
 
In order to enable the web side to easily interact with the open interface of the native wallet, we provide the "w3fsTool.js" javeScript development toolkit. Developers can implement the introduction of the toolkit according to the following process. The specific use of the toolkit is as follows:
#### 1.1, introduction
 
Imported by import, please download w3fsTool.js
```
import w3fsTool from "./w3fsTool.js";
//Tools are all in w3fsTool, such as rpcAxios method
console.log(w3fsTool.rpcAxios)
```
 
Loaded by script, please download w3fsTool.umd.js
```
<script src="./w3fsTool.umd.js"></script>
<script>
//Tools are all in w3fsTool, such as rpcAxios method
console.log(w3fsTool.rpcAxios)
</script>
```
 
 
#### 1.2, method
 
**rpcAxios( method, params )**<br>
  *Description: js calls native interface method*<br>
  Parameters: <br>
  { String } method method name<br>
  { Object } params Fill in according to the parameters that the method needs to carry, if there are no parameters, you can leave it blank<br>
  Return value: Return according to the data returned by each interface<br>
 
*Example:*
 
```
//There are parameters, such as sending contract transaction interface
rpcAxios("sendContractTransaction",
{
contractAddress:"0xaddress",
methodName:"method",
functionParam:"hexHash",
value:"0"
})
.then((res) => {
console.log(res);
})
.catch((error) => {
console.log(error);
});
 
//No parameters, such as getting identity information interface
rpcAxios("getAccountInfo")
.then((res) => {
console.log(res);
})
.catch((error) => {
console.log(error);
});
```
#### 1.3, some other auxiliary interface calls
```
isBrowser()
Description: Determine whether the Dapp is running in an external browser
Parameters: none
Return value: { Boolean } true: browser access false: in-app access
 
openApplication( isDownload, time, callback )
Description: When the local service cannot be checked externally, this interface can be called to evoke the app or jump to the download page
parameter:
{ Boolean } isDownload true: Execute jump download page false: Do not execute jump download page
{ Number } time The time for judging whether to evoke the app, the default is 1500 milliseconds, if there is a callback function and there is no need to define the time, it can be set to null
{ Function } callback The callback function after the app has been invoked
Return value: none
```
---
## 2. Interface definition
#### 2.1 File module related
* 1. Get a list of all encrypted files
```
Method name: getAllFileList ( pageIndex : Int , uploadState : Int )
Parameters: pageIndex : paging subscript, the default starts from 0 , (the number of returned items for paging is fixed at 20 )
uploadState : 0 : all 1 : stored 2 : not stored
Returns: [{ "name" : "aaa" , "path" : "bbb" , "size" : 10086 , "oriHash" : "ccc" , "headHash" : "ddd" , "bodyHash" : "eee" , "minerId" : "fff" , "isStorage" : false , "mimeType" : "ggg" , "createDate" : 123 , "uploadDate" : 456 }]
Description: The returned list is the encrypted file list in the w3fs wallet file module, and uploadState indicates whether there is any
to the decentralized storage network
name : file name
path : file full path information
size : file size
oriHash : file plaintext Hash
headHash : File encryption envelope header Hash
bodyHash : file encryption body Hash
minerId : the miner id of the file storage (valid when isStorage is true )
isStorage : Whether the file has been stored in the decentralized network
mimeType : file mimeType type
createDate : file creation time
uploadDate : The time when the file was uploaded to the central network storage
```
 
* 2. Get the specified encrypted file list
```
Method name: getAssignFileList (
pageIndex : Int ,
suffixType : String,
uploadState : Int )
Parameters: pageIndex : paging subscript, the default starts from 0 , (the number of returned items for paging is fixed at 20 )
suffixType : such as: "jpg" , multiple separated by commas such as : "jpg,png,mp4"
uploadState : 0 : all 1 : stored 2 : not stored
Returns: [{ "name" : "aaa" , "path" : "bbb" , "size" : 10086 , "oriHash" : "ccc" , "headHash" : "ddd" , "bodyHash" : "eee" , "minerId" : "fff" , "isStorage" : false , "mimeType" : "ggg" , "createDate" : 123 , "uploadDate" : 456 }]
Description: The returned list is the encrypted file list in the w3fs wallet file module, and uploadState indicates whether there is any
to the decentralized storage network
name : file name
path : file full path information
size : file size
oriHash : file plaintext Hash
headHash : File encryption envelope header Hash
bodyHash : file encryption body Hash
minerId : the miner id of the file storage (valid when isStorage is true )
isStorage : Whether the file has been stored in the decentralized network
mimeType : file mimeType type
createDate : file creation time
uploadDate : The time when the file was uploaded to the central network storage
```
 
* 3. Get the list of downloaded files
 
```
Method name: getDownloadFileList ( pageIndex : Int )
Parameters: pageIndex : paging subscript, the default starts from 0 , (the number of returned items for paging is fixed at 20 )
Returns: [{ "name" : "aaa" , "path" : "bbb" , "size" 10086 , "oriHash" : "ccc" , "downloadState" 0 , "mimeType" : "ggg" , "createDate" : 123 }]
Description: Returns the list of files downloaded by the w3fs wallet file module, excluding the list of encrypted / uploaded files
name : file name
path : file full path information
size : file size
oriHash : file plaintext Hash
downloadState : 0 : Downloading 1 : Downloading successfully 2 : Downloading failed
mimeType : file mimeType type
createDate : file creation time
```
 
* 4. Download files
```
Method name: downloadFile(
oriHash:String,txHash:String,
isForceDownload:Boolean)
Parameters: oriHash: file oriHash
txHash: NFT transaction Hash, can be empty, for example: when edshare purchases nft and clicks to download, it needs to be passed in
The transaction hash when purchasing nft, the chain will automatically add your identity to the encrypted file
If it is just a normal download file, pass "" (edshare is temporarily unavailable)
isForceDownload: Whether to force a re-download
Return: isForceDownload=true {"nRet":0}
isForceDownload=false if the file has not been downloaded{"nRet":0}otherwise{"nRet":-1004}
Description: The downloaded files are natively processed and downloaded. The downloaded files are displayed in the w3fs wallet file module and returned in the getDownloadFileList interface.
 
```
 
* 5. Open the file
```
Method name: openFile(path:String)
Parameters: path: full path of the file
Return: {"nRet":0}
Description: Native transparent use to open encrypted files, will not generate decrypted files
 
```
 
* 6. Determine whether the file is encrypted
```
Method name: fileIsEncryptByByte(fileHexString: String)
Parameters: fileHexString:fileHexString
Returns: {"isEncrypt":true}
 
Method name: fileIsEncryptByPath(path: String)
Parameters: path:path
Returns: {"isEncrypt":true}
 
```
 
 
---
#### 2.2 Signature/Transaction Related
* 1. Data signature
```
Method name: getDataSign(signMessage: String)
Parameters: signMessage: String to be signed
Return: {"signData":"aaa","signMessage":"132"}
```
 
* 2. Only transaction signature, sending transaction is processed by DApp (not available at the moment)
```
Method name: getTransactionSign(
nonce:BigInteger,
gasPrice:BigInteger,
gasLimit:BigInteger,
contractAddress:String,
tokenValue:BigInteger,
encodedFunction:String)
Parameters: nonce: the number of transactions in the current account
gasPrice: gasPrice
gasLimit: gasLimit
contractAddress: contract address
BigInteger: amount
encodedFunction: encoded hexadecimal string
Return: String signed data
```
 
* 3. Send native Token transfer transactions
```
Method name: sendNativeTokenTransaction(to: String, value: String)
Parameters: to: recipient address
value: transfer amount
Return: {"nRet":0}
```
 
* 4. Send ERC20Token transfer transaction
```
Method name: sendErc20TokenTransaction(
to: String,
contractAddress: String,
functionParam: String,
tokenName: String,
tokenSymbol: String,
value: String)
Parameters: to: recipient address
contractAddress: contract address
functionParam: signed hexadecimal string
tokenName: token name
tokenSymbol: token symbol
value: transfer amount
Return: {"nRet":0}
```
 
* 5. Send contract transaction
```
Method name: sendContractTransaction(
contractAddress: String,
methodName: String,
functionParam: String,
value: String)
Parameters: contractAddress: contract address
methodName: method name
functionParam: signed hexadecimal string
value: amount
Return: {"nRet":0}
```
#### 2.3 Other interfaces
* 1. Check whether the service is enabled
```
Method name: isAlive()
Description: Call this interface to query whether the local rpc service of the native wallet application is in the open state. If there is no callback, please call the wake-up wallet command.
Parameters: none
return: true
```
* 2. Obtain identity information
```
Method name: getAccountInfo()
Note: Dapp can obtain the relevant identity information in the native wallet application by calling this interface. The returned information includes the EOA address of the wallet application, the public key of the EOA account, the KeyId of file encryption and decryption, and the public key in the file encryption and decryption key pair. key
Parameters: none
Return: {"address":"aaaa","publicKey":"bbb","keyId":"ccc","filePublicKey":"ddd"}
```
* 3. Clear the WebView cache
```
Method name: clearDiskCache()
Parameters: none
Return: {"nRet":0}
```
 
---
## 3. Status code
```
 
//success
const val SUCCESS = 0
 
//Success, but no stream data was processed
const val NO_DATA_HANDLED = 1
 
//Success, create the object
const val CREATE_OBJECT = 10
 
//Success, open the object
const val OPEN_OBJECT = 11
 
//Success, open the object and overwrite the object
const val OVERRIDE_OBJECT = 12
 
//fail, wrong length
const val LENGTH_ERROR = -1
 
//failure, timeout
const val TIME_OUT = -2
 
//fail, insufficient buffer length
const val OUT_Of_LENGTH = -3
 
//fail, unable to connect to the kernel
const val CANT_CONNECT_KERNEL = -10
 
//Failure, there is currently a file being served
const val FILE_SERVING = -11
 
//fail, multiple login users
const val MULTI_USER = -20
 
//fail, no logged in user
const val NO_USER = -21
 
//fail, syntax error
const val SYNTAX_ERROR = -30
 
// Failed, the specified object could not be found
const val CANT_FIND_OBJECT = -31
 
//failure, multiple specified objects
const val MULTI_OBJECT = -32
 
//Failure, the specified object cannot be found temporarily (currently it is impossible to determine that the specified object can be found)
const val MAYBE_FIND_OBJECT = -33
 
//fail, generic logic error
const val COMMON_LOGIC = -34
 
//Failed, the encryption algorithm is wrong (usually there is no encryption algorithm)
const val CIPHER_ERROR = -40
 
//Failed, internal encryption algorithm error
const val CIPHER_INNER_ERROR = -41
 
//fail, insufficient permissions
const val PERMISSIND_DENIED = -42
 
//Failure, processing encrypted header structure failed, CRC error
const val HEADER_CRC_ERROR = -50
 
//fail, identity envelope processing failed
const val IDENTITY_SEAL_ERROR = -51
 
//fail, other errors (usually memory allocation errors)
const val OTHER = -100
 
//file does not exist
const val FILE_DOES_NOT_EXIST = -200
```
 
