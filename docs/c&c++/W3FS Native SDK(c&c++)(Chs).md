# 简介
 APP开发团队及开发者可以直接学习和理解W3FS底层协议，通过集成W3FS底层Native SDK完成NativeApp的开发。阅读者可通过阅读本开发手册，了解W3FS底层SDK对外开放的所有接口，及接口说明，完成符合W3FS协议规范的Native APP开发。
 
W3FS-SDK使用C++语言开发，提供全平台支持，包括Windows,Linux,Android,iOS,Mac版本。

W3FS-SDK使用各平台标准的函数导出方式导出对外接口，外部使用可支持调用c++模块的语言可直接调用。

针对一些不支持直接调用c++模块的语言开发，W3FS-SDK库也提供了相应的支撑，例如对JAVA语言开发，W3FS-SDK库提供了专门的JNI接口支撑。对不支持c++特定特性的语言，例如GO语言，W3FS-SDK也提供了相应支持，如您使用的开发语言调用W3FS-SDK库有障碍，请联系W3FS开发团队，我们将对其做匹配开发，各语言将有另外的SDK说明文档，您可以查阅。

## **API列表**
### **基础接口**
#### **TSK_Init**
初始化W3FS-SDK Native库.

函数原型:  

``` c
INT32 TSK_Init();
```

参数:  
* 无

返回值:
* INT32: 
KError_Success 成功
KError_CantConnectKernel，失败，无法连接到W3FS文件系统内核（只针对Native方式dapp开发才有效）。
KError_Other,失败,其他错误;

说明:

TSK_Init接口为W3FS-SDK初始化接口，所有加载W3FS-SDK库的NativeApp，在Apppp启动或者初始化的时候，都应调用TSK_Init接口，W3FS-SDK库的其他接口调用依赖于TSK_Init接口的调用成功。
#### **TSK_UnInit**

反向初始化W3FS-SDK Native库

函数原型:  

``` c
void TSK_UnInit();
```

参数:  
* 无

返回值:
* 无

说明:

dapp在程序退出时，需调用TSK_UnInit接口，完成W3FS Native SDK库的反向初始化工作，以让W3FS Native SDK库能清理及释放占用的所有系统资源。
#### **TSK_GetRandomKey**

获取一个指定长度的随机数数组

函数原型:  

``` c
INT32 TSK_GetRandomKey(UINT32 nKeyLen,BYTE * pKey);
```

参数:  
* nKeyLen: 要求获取的随机数长度 [IN]
* pKey: 外部准备的用于接收随机数内存缓存区  [IN/OUT]

返回值:
* KError_Success,成功

说明:

W3FS Native SDK库内建随机数生成器，可根据外部需要，产生要求长度的随机数，以便外部使用，在加载有W3FS内核驱动的APP开发中，通过W3FS-SDK库生成的随机数是由W3FS-SDK驱动内核产生的真随机数。在其他方式的APP开发中，获取到的是由W3FS-SDK库根据当前系统时间以及其他相关因素产生的伪随机数。
### **摘要接口**


W3FS-SDK库提供了多种方式的摘要接口，例如快速的CRC摘要，安全的MD5及SHA256摘要算法。W3FS-SDK库内部使用MD5摘要对有需要的加密数字文件进行签名。外部可通过使用W3FS-SDK库提供的摘要接口，对数据进行摘要。


W3FS-SDK通过统一的数据流摘要方式对外部指定的数据进行摘要，并支持外部多次调用摘要算法，对一段超大长度数据进行联合摘要，同一个摘要过程通过指定的cookie进行识别，一个典型的摘要过程如下:


通过摘要cookie指针不为NULL支持对多个流进行联合摘要.
开始摘要时将获取cookie,该值就一直不变直到结束摘要.
简单来说,判断依据是:当流指针为空,表示开始摘要或者结束摘要;
当流指针不为空,是对流进行摘要.
当流指针为空时,如果pCookie中的值也为NULL是开始摘要,如果pCookie中的值不为NULL是结束摘要.


通过CRC摘要算法举例，典型的使用方式如下:

1. 调用TSK_DigestCRC32(0,NULL,pCookie,NULL)表示开始摘要:流(nFlowLen和pFlow)被指定为空(nFlowLen为0,pFlow为NULL),摘要cookie指针(pCookie)非NULL,其中存储的cookie为0,该接口成功后将返回cookie到该指针内,摘要结果指针(pCRC32)被指定为NULL,这表示让摘要算法初始化,准备开始对多个流进行统一联合摘要.
2. 对每一个流调用TSK_DigestCRC32(nFlowLen,pFlow,pCookie,NULL)表示进行摘要:           流(nFlowLen和pFlow)指定一个具体的流摘要，cookie指针(pCookie)非NULL,其中存储的摘要cookie为步骤1中获取的摘要，cookie摘要结果指针(pCRC32)被指定为NULL,这表示让摘要算法对指定的该流进行摘要.
3. 调用TSK_DigestCRC32(0,NULL,pDigestID,pCRC32)表示结束摘要并接收结果:流(nFlowLen和pFlow)被指定为空(nFlowLen为0,pFlow为NULL),摘要cookie指针(pCookie)非NULL,其中存储的摘要cookie为步骤1中获取的摘要cookie,摘要结果指针(pCRC32)非NULL,这表示让摘要算法终止,并返回现在(最终)的摘要结果.
#### **TSK_DigestCRC32**

迭代支持对多个流进行CRC32摘要

函数原型:  
``` c
INT32 TSK_DigestCRC32(UINT32 nFlowLen,BYTE * pFlow,PVOID * pCookie,UINT32 * pCRC32);
```

参数:  
* nFlowLen：是指定要计算CRC32摘要的流大小 [IN]
* pFlow：是指定要计算CRC32摘要的流 [IN]
* pCookie：指定迭代需要的cookie [IN/OUT]
* pCRC32：中填充为迭代摘要的最终结果,为一个32位的CRC32值 [OUT]

返回值:
* KError_Success,成功
* KError_Other,失败,其他错误

说明:

CRC32摘要是一种高速但非可靠的摘要算法,可以用于对高频率使用的数据进行验证.
#### **TSK_DigestMD5**

迭代支持对多个流进行MD5算法摘要

函数原型:  

``` c
INT32 TSK_DigestMD5(UINT32 nFlowLen,BYTE * pFlow,PVOID * pCookie,BYTE * pMD5);
```

参数:  
* nFlowLen：是指定要计算CRC32摘要的流大小 [IN]
* pFlow：是指定要计算CRC32摘要的流 [IN]
* pCookie：指定迭代需要的cookie [IN/OUT]
* pMD5：中填充为迭代摘要的最终结果,为一个16字节的数组 [OUT]

返回值:
* KError_Success,成功
* KError_Other,失败,其他错误

说明:

MD5摘要是一种低速但可靠的摘要算法
#### **TSK_DigestSha256**

迭代支持对多个流进行SHA256算法摘要

函数原型:  

``` c
INT32 TSK_DigestSha256(UINT32 nFlowLen,BYTE * pFlow,PVOID * pCookie,BYTE * pSHA256);
```

参数:  
* nFlowLen：是指定要计算CRC32摘要的流大小 [IN]
* pFlow：是指定要计算CRC32摘要的流 [IN]
* pCookie：指定迭代需要的cookie [IN/OUT]
* pSHA256：中填充为迭代摘要的最终结果,为一个32字节的数组 [OUT]

返回值:
* KError_Success,成功
* KError_Other,失败,其他错误

说明:

SHA256摘要是一种可靠的摘要算法,可以用于对任意数据的签名验证.
### **身份算法(非对称加密算法)接口**

W3FS-SDK库默认采用ECC256椭圆曲线加密算法作为电子信封模式中的非对称加密算法。选用的曲线为标准的SECP256K1参数。详细参数如下:
* prime：FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F
* A：0000000000000000000000000000000000000000000000000000000000000000
* B：0000000000000000000000000000000000000000000000000000000000000007
* order：FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141
* Gx：79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798
* Gy：483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8

#### **TSK_IdentityIssue**

产生(颁发)一个身份对象

函数原型:  

``` c
INT32 TSK_IdentityIssue(IdentityObject * pIdentity,BYTE* pSeed,UINT32 nSeedLen);
```

参数:  
* pIdentity：获得的身份对象(不透明语义) [OUT]
* pSeed：指定的身份密钥信息的种子信息 [IN]
* nSeedLen：指定的身份密钥信息的种子信息长度，字节单位 [IN]

返回值:
* KError_Success,成功
* KError_Other,失败,其他错误

说明:

身份对象是一个不透明的对象实体,外部不需要了解其内部构成.
只支持ecc 256k1身份
如外部指定了种子信息,生成的身份信息将是一致的,种子信息强制要求为32字节长度,可不指定,将随机颁发身份证书
外部可通过特定的算法设计，对同一个用户的身份使用固定的种子信息，则多次调用办法身份接口产出的用户身份将是固定的，以支持分布式程序设计和开发过程中，将用户的身份密钥信息永远只保存于用户信赖的设备中。只需将身份密钥对应的公钥对外公开即可实现安全的基于W3FS协议的加密数字文件分享功能。
#### **TSK_IdentityIssueEx**

产生(颁发)一个身份对象，并直接返回密钥流形式给外部

函数原型:  

``` c
INT32 TSK_IdentityIssueEx(BYTE* pSeed, UINT32 nSeedLen,BYTE* pPublicKeyBuf, UINT32& nPublicKeyLen,BYTE* pPrivateKenBuf, UINT32& nPrivateKeyLen,BYTE* pKeyID);
```

参数:  
* pSeed：指定的身份密钥信息的种子信息 [IN]
* nSeedLen：指定的身份密钥信息的种子信息长度，字节单位 [IN]
* nPublicKeyLen: 外部传入的公钥缓冲区长度[IN/OUT]
* nPrivateKeyLen: 外部传入的私钥缓冲区长度[IN/OUT]
* pPublicKeyBuf: 身份的公钥信息数据流[IN/OUT]
* pPrivateKeyBuf: 身份的私钥信息数据流[IN/OUT]
* pKeyID: 身份的密钥ID，固定20字节[IN/OUT]

返回值:
* KError_Success,成功
* KError_Other,失败,其他错误

说明:

TSK_IdentityIssueEx函数功能于TSK_IdentityIssue一致，区别在于返回给外部的是外部可直接解析和保存的公私钥二进制流形式，外部可使用TSK_IdentityIssueEx接口，获取到身份密钥的公私钥数据直接保存或做其他处理。
在W3FS-SDK库的设计中，缓存区内存都是由外部程序预先准备好，并和缓冲区长度信息一起传入W3FS-SDK库，W3FS-SDK库直接在外部准备好的缓冲区上直接操作，缓冲区的释放也由外部程序自己负责。
#### **TSK_IdentityFree**

释放一个身份对象

函数原型:  

``` c
INT32 TSK_IdentityFree(IdentityObject identity);
```

参数:  
* identity是要释放的身份对象(不透明语义) [IN]

返回值:
* KError_Success,成功

说明:

与TSK_IdentityIssue函数对应，外部通过TSK_IdentityIssue函数生成一个不透明语义的用户身份，在使用完后，需调用Free接口，释放不透明语义用户身份对象占用的内存空间，遵循谁申请，谁释放原则。
#### **TSK_IdentityExport**

将一个身份对象根据指定的形式（公钥或者私钥）输出二进制形式

函数原型:  

``` c
INT32 TSK_IdentityExport(IdentityObject identity,BYTE Action,UINT32 BufLen,BYTE * Buf,UINT32 * pWrittenLen);
```

参数:  
* identity是目标身份对象(不透明语义) [IN]
* nAction是操作选择： [IN] 1表示公钥,2表示私钥,3表示密钥身份ID
* BufLen是要输出的数据的接收缓冲区大小 [IN]
* Buf是要输出的数据的接收缓冲区 [OUT]
* pWrittenLen中返回实际输出的数据的大小 [IN/OUT]

返回值:
* KError_Success,成功
* KError_Other,其他错误,通常是分配内存错误(或缓冲区不足);


说明:

外部可通过TSK_IdentityExport接口，从指定的不透明语义的用户身份对象中，导出身份对应的公钥或者私钥。但前提条件是不透明语义对象中本身包含了两种信息，根据ECC加密算法的规则，身份对象如包含私钥信息，则可任意导出公钥或者私钥的二进制流数据。身份对象如只包含公钥信息，则只能导出公钥的二进制流数据。
#### **TSK_IdentityImport**

从一个数据中读取信息恢复身份对象

函数原型:  

``` c
INT32 TSK_IdentityImport(BYTE Action,UINT32 BufLen,BYTE * Buf,IdentityObject * pIdentity);
```

参数:  
* nAction是操作选择： [IN] 1表示公钥,2表示私钥
* BufLen是外部准备的缓冲区大小 [IN]
* Buf是外部准备的身份密钥二进制流数据 [IN]
* pIdentity中返回恢复的身份对象(不透明语义)[OUT]

返回值:
* KError_Success,成功
* KError_Other,其他错误,通常是分配内存错误(或缓冲区不足);


说明:

与TSK_IdentityExport接口对应，将外部传入的一个密钥的二进制流数据导入，恢复成一个不透明语义的身份对象。
#### **TSK_IdentityEncrypt**

使用身份对象执行加密/或签名操作

函数原型:  

``` c
INT32 TSK_IdentityEncrypt(IdentityObject identity,BYTE cryptAction,UINT32 nSrcFlowLen,BYTE * pSrcFlow,UINT32 nTarFlowLen,BYTE * pTarFlow,UINT32 * pTarFlowReturnLen);
```

参数:  
* identity是身份对象(不透明)[IN]
* nAction是操作选择： [IN] 1表示公钥,2表示私钥
* nSrcFlowLen指定原始流的缓冲区长度 [IN]
* pSrcFlow指定原始流缓冲区[IN]
* nTarFlowLen指定接收处理后的目标流的缓冲区长度[IN/OUT]
* pTarFlow指定接收处理后的目标流的缓存区[IN/OUT]

返回值:
* KError_Success,成功
* KError_Other,其他错误,通常是分配内存错误(或缓冲区不足);


说明:

基于ecc256算法的特性,每次ecc256加密以64字节为单位,该特性对外部透明

外部可传入任意长度数据,接口内部将以64字节为单位循环加密，并将加密后的总体数据返回外部,接收加密结果的缓冲区外部应确保长度足够,按原始数据/加密后数据 64/154比例准备好。

ECC加密算法支持使用公钥或者私钥对数据执行加密操作。指定公钥进行加密是对待加密数据执行加密操作，指定私钥进行加密，实际上是对待加密数据执行数字签名操作。

如传入的身份对象只包含公钥信息，则无法支持私钥加密操作。如传入的身份对象包含私钥信息，则公私钥加密/签名操作皆可支持。
#### **TSK_IdentityDecrypt**

使用身份对象执行解密/验签操作

函数原型:  

``` c
INT32 TSK_IdentityDecrypt(IdentityObject identity,BYTE cryptAction,UINT32 nSrcFlowLen,BYTE * pSrcFlow,UINT32 nTarFlowLen,BYTE * pTarFlow,UINT32 * pTarFlowReturnLen);
```

参数:  
* identity是身份对象(不透明)[IN]
* nAction是操作选择： [IN] 1表示公钥进行解密（验签）,2表示私钥进行解密
* nSrcFlowLen指定原始流的缓冲区长度 [IN]
* pSrcFlow指定原始流缓冲区[IN]
* nTarFlowLen指定接收处理后的目标流的缓冲区长度[IN/OUT]
* pTarFlow指定接收处理后的目标流的缓存区[IN/OUT]

返回值:
* KError_Success,成功
* KError_Other,其他错误,通常是分配内存错误(或缓冲区不足);

说明:

接收解密结果的缓冲区外部应确保长度足够,按原始数据/解密后数据 154/64比例申请好
### **对称加密算法接口**


W3FS-SDK采用标准的电子信封模式对数字文件进行全生命周期保护，对于文件数据使用对称加密算法，并使用一文一密形式的随机密钥进行加密，对对称加密算法的随机密钥，使用表示用户身份的非对称算法的公钥进行加密，加密后的数据我们称之为一个eseal结构，保存于文件加密头的eseal身份区中。用户使用加密文件时，需先尝试使用自己的所拥有身份的私钥解密eseal身份区中的每一个eseal结构，加密成功后，才能获取到真实文件加密的对称算法的随机密钥，最终获取到文件的真实数据。

W3FS-SDK的电子信封机制，有机结合了对称加密算法的高效率，以及非对称加密算法的高安全性，为用户提供高效率高安全性的数据全生命周期保护方案。

W3FS-SDK库的对称加密算法管理模块使用可扩展的组件设计，库内部默认集成了AES256,DES3,GOST,MARS,SEAL等常见对称加密算法用于对文件数据进行加密，APP开发人员或者用户可以根据自身的需要与喜好，对对称加密算法进行选择，除此之外，W3FS-SDK库还支持将更多的对称加密算法加入到库中，为用户提供更多的选择。
#### **TSK_GetCipherDesc**

获取当前所有加载了的算法描述

函数原型:  

``` c
INT32 TSK_GetCipherDesc(BYTE * pDescBuf,INT32 nDescBufLen);
```

参数:  
* pDescBuf,外部准备的用以接收报告书缓冲区，建议第一次申请8K（8192）字节长度缓冲区 [IN/OUT]
* nDescBufLen，外部准备的用以接收报告书缓冲区长度，建议第一次长度为8192字节 [IN]

返回值:
* 返回报告书实际长度，如返回值大于外部传入的缓冲区长度，则不会对缓冲区做任何操作，需要外部根据实际长度重新申请足够大的缓冲区，再次获取

说明:

应用层界面上通过该接口获取加载了的算法进行显示.

返回的数据是TSK平台支持的所有对称加密算法描述信息的集合，主要格式如下

支持的对称加密算法总数:4字节长度的UINT32数据
* 第一个加密算法描述     
16字节长度的加密算法tag标识，用以唯一标识一个算法，并且后续的接口，都使用该tag 表示该算法
算法名字符串，不限长度，以字符串最终的追尾0作为结束标识
算法一句话描述信息字符串，不限长度，以字符串最终的追尾0作为结束标识
* 第二个加密算法描述
16字节长度的加密算法tag标识，用以唯一标识一个算法，并且后续的接口，都使用该tag 表示该算法
算法名字符串，不限长度，以字符串最终的追尾0作为结束标识
算法一句话描述信息字符串，不限长度，以字符串最终的追尾0作为结束标识
* 更多的加密算法描述


通过TSK_GetCipherDesc接口，外部可获取到当前W3FS-SDK库所支持的所有对称加密算法列表，更多时候是用于界面展示，将当前所有支持的算法罗列展示，以便用户选择需要使用的加密算法。
#### **TSK_GetCipherInfo**

获取指定的算法详细信息

函数原型:  

``` c
INT32 TSK_GetCipherInfo(BYTE * tagCipher,UINT16 * pKeyLength,UINT16 * pBlockSize);
```

参数:  
* tagCipher是要获取的算法tag(即该算法的GUID标签),固定为16字节;该参数可以为NULL,表示指定默认算法;[IN]

* pKeyLength返回该算法要求的秘钥长度(字节计算)[IN/OUT]
* pBlockSize算法要求的分组大小(字节计算,因此序列算法返回1)[IN/OUT]

返回值:
* KError_Success,成功;
* KError_CipherError,失败,未能找到该算法;
* KError_Other,其他错误,通常是分配内存错误(或缓冲区不足);

说明:
应用层在构造流处理对象时可以通过该接口确定算法的秘钥大小和分组大小.
也可用于界面展示，用于显示一个加密算法的详细信息。
#### **TSK_SetDefaultCipher**

设置当前的默认算法

函数原型:  

``` c
INT32 TSK_SetDefaultCipher(BYTE * tagCipher);
```

参数:  
* tagCipher是要获取的算法tag(即该算法的GUID标签),固定为16字节;该参数可以为NULL,表示指定默认算法;[IN]

返回值:
* KError_Success,成功;
* KError_CipherError,失败,未能找到该算法;
* KError_Other,其他错误,通常是分配内存错误(或缓冲区不足);

说明:
应用层界面上通过该接口设置默认算法.

加密时如果指定算法tag为NULL时,将使用默认算法进行加密.

上层设置的默认加密算法为单次启动有效，退出W3FS-SDK库，重新启动后，将还原用户的设置，所以外部APP如需使用本功能，可将用户的设置记录，再次启动时，主动调用设置默认的算法。
### **账号接口**

用户相关;库仅支持单一账号登录.

每一个身份都有一个唯一的20字节长度的身份ID。外部可在生成用户时，通过特定的算法，生成符合W3FS-SDK要求的身份ID。

每一个账号可能具有多个身份,但是单独表征该账号用户身份(代表这个人)的只可能是一个.

在W3FS协议中，身份是一个很特殊的概念，身份与账户是分开的，账户表示的一个用户。而身份简单来说，是一个用户所拥有的权限，举例来说，例如一个用户加入了群组A，社区B，使用了某个应用C。则这个用户对所有群组A,社区B，应用C的内部加密文件，以及用户自身的隐私文件，对于该用户来说，都应该是可见的。所以这个用户至少拥有4个身份，对应的，也可以说是用户至少拥有这4个身份对应的非对称加密算法的密钥，可以通过这些身份的密钥去尝试解密属于这些身份的加密文件，进而用户可以使用这些加密文件。

但是在用户登录时，统一都使用用户自身的身份登录W3FS-SDK库，其他身份通过应用自身的管理，配置给用户。
#### **TSK_LoginUser**

登录账号

函数原型:  

``` c
INT32 TSK_LoginUser(BYTE* nIdentityID);
```

参数:  
* nIdentityID是对应的代表该用户的唯一身份的内部ID

返回值:
* KError_Success,成功;
* KError_MultiUser,失败,存在其他登录用户;
* KError_Other,其他错误,通常是分配内存错误(或缓冲区不足);
#### **TSK_LogoutUser**

登出当前账号

函数原型:  

``` c
INT32 TSK_LogoutUser();
```

参数:  
* 无

返回值:
* KError_Success,成功;
#### **TSK_SetHoldIdentity**

设置W3FS-SDK库当前用户持有的身份

函数原型:  

``` c
INT32 TSK_SetHoldIdentity(UINT32 nListVerb,BYTE* nIdentityID, PermissionInfo nPermission, int nLastTime,BYTE * pKeyBuf,INT32 nKeyLen);
```

参数:  
* nListVerb是标准的列表操作动词,无LIST_VERB_MODIFY语义 [IN]
* nIdentityID是该身份的ID [IN]
* nPermission是该身份对应的权限，用户持有的身份默认拥有全部权限，需外部设置 [IN]
* nLastTime是该身份的公钥用于默认加密时给予的文件最后使用期限，请务必传入-1，文件创建者拥有无限期使用权限 [IN]
* pKeyBuf是该身份的密钥二进制格式信息,字节单位 [IN]
* nKeyLen是该身份的密钥二进制格式信息长度，字节单位 [IN]

返回值:
* KError_Success,成功;
* KError_NoUser,失败,当前无登录用户;
* KError_SyntaxError,失败,语法错误(例如不支持的动词等);
* KError_MultiObject,失败,语义错误,该Key已经存在(该身份ID已经存在);
* KError_CantFindObject,失败,语义错误,删除不存在的Key(该身份ID不存在);
* KError_Other,其他错误,通常是分配内存错误(或缓冲区不足);

说明:

W3FS-SDK库对用户的身份管理采用链表结构，外部对用户的身份操作实质上是对管理链表的各种操作动作。

前用户所持有的身份为一个列表,其通常通过LIST_VERB_CLEAR/LIST_VERB_ADD/LIST_VERB_DELETE 来进行管理.

当LIST_VERB_ADD时,所有参数显然都需要提供.

当LIST_VERB_DELETE时,参数显然只需要提供nIdentityID即可.

LIST_VERB_DEFAULT为设置用户身份;

当希望设置(或改变)一个默认身份时,该身份应该已经在持有身份列表中,所以参数只需提供nIdentityID即可.

当希望清除默认身份时,应该指定nIdentityID为IDENTITY_NULL,其他参数不用提供.

``` c
//nListVerb的各项动作定义如下:
#define LIST_VERB_DEFAULT 1 //设置默认的默认行为
#define LIST_VERB_CLEAR 2 //清除匹配列表
#define LIST_VERB_ADD 3 //增加匹配项
#define LIST_VERB_DELETE 4 //删除匹配项
#define LIST_VERB_MODIFY 5 //修改匹配项
```


PermissionInfo结构是W3FS-SDK库对身份权限的定义，实质上是用一个2字节整数，按位表示一个身份拥有的权限，目前W3FS-SDK库定义了如下两种权限:

``` c
typedef struct _PermissionInfo{
    UINT16 bOwner : 1;//是否是Owner：0表示非Owner，1表示Owner
    UINT16 bAdjust : 1;//是否具有分发权限：0表示不具有，1表示具有。
    }PermissionInfo, *PPermissionInfo;
```

在W3FS-SDK库中，bOwner表示用户是加密的数字文件的Owner，对加密的数字文件拥有所有权限，包括文件读取，写入，分享，解密等。

其他非Owner身份对加密的数字文件只拥有读取权限。

bAdjust是一个特殊权限，拥有该权限的身份拥有对加密文件进行分享的权限。即有权限将另一个身份加入到加密数字文件的ESeal身份区中，构建新的ESeal结构，也有权限删除或修改已有ESeal身份区中的eseal结构。

在不支持结构体的语言开发中，可以简单用一个2字节的整数传入作为权限。-1表示身份拥有所有权限，1表示Owner权限，2表示分享权限。
#### **TSK_SetDefaultZone**

设置默认加密段落

函数原型:  

``` c
INT32 TSK_SetDefaultZone(INT64 nLen);
```

参数:  
* nLen是要设置的默认加密段落的大小(字节计数)[IN]

返回值:
* KError_Success,成功;
* KError_Other,其他错误,通常是分配内存错误(或缓冲区不足);

说明:

默认加密段落固定是从文件头,到指定的大小处的文件段落.

段落大小为0,这实际上等于未加密;段落大小为-1,这实际上等于加密整个文件.

指定默认加密段落在某些环境下并不是必需的,但在需要库自动进行某些加解密动作(例如文件系统自动加解密)的环境下是必需的.

段落加密是W3FS-SDK对文件加密的特殊支持，默认情况下，W3FS-SDK对数字文件的加密是全文加密，即对文件的全部数据执行按照指定算法的重编码加密。

但外部可以根据需要，通过设置段落加密的配置，以使得W3FS-SDK在对文件数据的加密或者解密过程中，得到更高效率的体现。段落加密的依据是，目前几乎所有格式的数字文件对文件数据都是有格式要求的。通过加密从文件头开始，指定长度的数据，可以达到只重编码一部分数据，即可破坏应用软件对数据文件格式的要求，应用软件无法解析格式被破坏的数据文件，进而达到数据保护的目的。建议，如果使用W3FS-SDK提供的段落加密功能，段落配置不小于1MB，甚至可以更高。进而达到更高的安全性。

### **文件操作任务模块接口**

W3FS-SDK库提供了数字文件加解密及分享功能接口。

在W3FS-SDK库中，文件加密包括外部通过调用文件任务操作接口，主动将一个文件从未加密状态修改成安全的加密状态。以及W3FS-SDK实时文件系统内核根据配置的规则，通过无感加密，将一个文件加密。

相对应的，文件解密包括外部通过调用文件任务操作接口，主动将一个加密文件脱密成未加密明文状态，以及W3FS-SDK实时文件系统内核驱动以及W3FS LocalServer模块无感在内存中解密文件数据，将数据实时提供给应用程序使用。

文件操作任务模块只包含外部模块，或者说用户主动操作，将一个文件加密，解密，或分发操作。不包括由W3FS-SDK实时文件系统内核驱动以及W3FS LocalServer模块提供的无感加解密。

文件操作任务模块通过异步多线程方式操作用户指定的文件，并为保证对文件加解密过程中对文件重编码操作阶段，文件数据的安全，文件操作任务模块统一通过副本操作模式操作用户指定的文件，文件数据重编码阶段，对文件数据的所有修改都是在外部指定的文件中进行，操作完成后，由外部决定是删除源文件还是备份源文件，这是W3FS-SDK为防止重编码过程中，设备有可能发生的突然断电或者程序异常导致问题产生的容灾机制。

W3FS-SDK提供文件手动操作功能，包括文件加密，解密，分享等操作，并提供任务操作接口，支持外部对文件操作任务进行控制，包括任务的取消等操作。

加密操作仅仅使用用户当前指定的默认身份的公钥完成，外部应确认调用文件操作接口前已完成用户登录，及设置用户身份及默认身份操作
解密操作仅仅使用当前用户具有的所有私钥完成，外部应确认调用文件操作接口前已完成用户登录，及设置用户拥有身份的操作
分发操作使用的身份及动作（添加或删除身份）由外部根据一次分发操作的对象添加

文件操作接口使用任务机制，外部应先创建一个文件操作任务，并设置文件操作任务的各种参数（包括基本参数，及扩展参数）
文件操作是一个耗时操作，库内部使用新线程异步完成，在文件操作执行过程中，外部可通过任务机制接口控制文件操作的执行
文件操作的中间状态信息，及最终结果信息，外部应通过任务操作接口轮询获取，并展示相应的界面提示信息
文件操作任务的标准流程如下:

1. 初始化一次文件操作任务：设置一次文件操作任务的基本参数属性，包括任务对应的线		程数，及任务的动作(加密/解密/分发)

2. 设置一次文件操作的任务目标：将一次文件操作对应的任务目标（文件/文件夹）一一通过接口设置进W3FS-SDK库
3. 设置一次文件分发操作的身份操作动作：只针对文件分发操作，该接口调用才生效，对文件的身份区执行身份的添加删除操作
4. 设置一次文件分发操作的签名属性:只针对文件分发操作，该接口调用才生效
5. 启动文件操作任务；
6. 获取文件操作任务状态:
7. 控制文件操作任务（包括文件操作任务的中止等），因文件操作任务是一个异步多线程执行的任务，所以对一次文件操作任务的控制并不会马上体现，最终结果应通过获取文件操作任务状态接口获取
8. 获取文件操作任务结果报告书
9. 反向初始化一次文件操作任务，销毁一次文件操作任务中创建的各种对象。
#### **TSK_FileOpTask_Init**

初始化一个文件操作任务

函数原型:  

``` c
INT32 TSK_FileOpTask_Init(INT32 nAction,INT32 nThreadCount);
```

参数:  
* nAction,此次文件操作任务对应的具体操作，1,加密；2，解密；3，分发[IN]
* nThreadCount，此次文件操作任务要启动的线程数，默认值为1[IN]

返回值:
* 小于0表示文件操作任务初始化失败，无需后续操作，大于等于0表示初始化成功，并且返回此次文件操作任务对应的任务ID，后续对文件操作任务的所有操作及控制都通过该任务ID进行


说明:

nThreadCount，文件手动操作是一个耗时且涉及到密集计算的操作，建议通过设置合理的多线程数在性能和用户体验间获得平衡，例如最高设置为(cpu核心数/2+1)的线程数目

库内部将以文件为单位，库内部将启动不超过外部设置的任务线程数阈值对一次任务的多个文件进行多线程处理，当然，如果一次文件操作任务目标文件数小于设置的线程数，将以实际文件数开启多线程处理
#### **TSK_FileOpTask_PushAFileToTask**

添加一个待操作文件/文件夹全路径到指定的文件操作任务中

函数原型:  

``` c
INT32 TSK_FileOpTask_PushAFileToTask(INT32 nTaskID, WCHAR* pSrcFullPath,WCHAR* pDstFullPath);
```

参数:  
* nTaskID,指定的文件操作任务ID[IN]
* pSrcFullPath，待操作源文件/文件夹全路径信息[IN]
* pDstFullPath,待操作目标文件/文件夹全路径信息[IN]

返回值:
* KError_Success,成功;

说明:

pSrcFullPath,pDstFullPath使用OS原生方式处理字符串类型数据，在windows操作系统中，使用Unicode字符集，在Linux,Mac,IOS,Android等其他操作系统中，使用UTF-8字符集。

一次文件操作任务可操作同时对多个文件/文件夹处理，外部可在一次文件操作任务过程中，多次调用本函数设置一次文件操作任务的目标全路径

此函数只在任务真正开始启动前有效，当任务状态已经启动后，包括任务处于暂停状态下，都无法再次调用该接口完成操作目标的添加

加解密操作才需要传入两个路径，分发操作绝大多数情况下因预留的头部空间足够，都是在源文件上操作，所以分发操作只需要传入源文件路径即可，目标文件可传NULL源文件与目标文件必须为不是同一个路径，且源文件需真实存在.
#### **TSK_FileOpTask_PushAAction**

添加一个待操作身份项动作到指定的文件操作任务中

函数原型:  

``` c
INT32 TSK_FileOpTask_PushAAction(INT32 nTaskID, BOOLEAN bDelAdd,BYTE* IID, PermissionInfo nPermission, int nLastTime, BYTE* pKeyBuf, DWORD nKeyBufLen);
```

参数:  
* nTaskID,指定的文件操作任务ID[IN]
* bDelAdd,在身份区里面添加还是删除一个身份，true,添加，false,删除[IN]IID，待操作身份的20字节身份ID信息[IN]
* nPermission,待操作身份的权限信息,删除身份动作时，该参数无意义，可传空权限 [IN]
* nLastTime,待操作身份的最后使用时间限定信息,删除身份动作时，该参数无意义,可传0 [IN]
* pKeyBuf，待操作身份的公钥信息，删除身份动作时，该参数无意义，可传NULL [IN]
* nKeyBufLen，待操作身份的公钥长度信息，删除身份动作时，该参数无意义，可传0 [IN]

返回值:
* KError_Success,成功;
* 其他为失败，可参考W3FS Native SDK库标准返回值定义


说明:

此接口只针对文件分发有效，TSK库的身份区调整使用的是按动作还原方式执行对身份的添加或删除操作.

外部应将用户对指定文件或文件夹的分发动作记录起来，作为一个动作列表一一传送给TSK库，库再按用户分发动作的先后顺序，将动作还原，最终完成分发操作

此函数只在任务真正开始启动前有效，当任务状态已经启动后，包括任务处于暂停状态下，都无法再次调用该接口完成操作目标的添加
#### **TSK_FileOpTask_SetShareSign**

设置一个文件操作任务签名动作

函数原型:  

``` c
INT32 TSK_FileOpTask_SetShareSign(INT32 nTaskID, BYTE nSignAction);
```

参数:  
* nTaskID,指定的文件操作任务ID[IN]
* nSignAction是签名动作信息，0为保持签名信息，1为设置签名信息，2为清除签名信息  [IN]

返回值:
* KError_Success,成功;
* 其他为失败，可参考W3FS Native SDK库标准返回值定义


说明:

设置签名动作只针对文件分发操作，库内部默认值为0，保持当前的签名信息

此函数只在任务真正开始启动前有效，当任务状态已经启动后，包括任务处于暂停状态下，都无法再次调用该接口完成操作目标的添加
#### **TSK_FileOpTask_StartATask**

开启一个文件操作任务

函数原型:  

``` c
INT32 TSK_FileOpTask_StartATask(INT32 nTaskID);
```

参数:  
* nTaskID,指定的文件操作任务ID[IN]

返回值:
* KError_Success,成功;
* 其他为失败，可参考W3FS Native SDK库标准返回值定义


说明:

文件操作任务开始后，无法再次调用设置参数接口，修改文件操作任务的属性,异步操作，内部将启动异步多线程完成真正的事务
#### **TSK_FileOpTask_CancelATask**

中止一个文件操作任务

函数原型:  

``` c
INT32 TSK_FileOpTask_CancelATask(INT32 nTaskID);
```

参数:  
* nTaskID,指定的文件操作任务ID[IN]

返回值:
* KError_Success,成功;
* 其他为失败，可参考W3FS Native SDK库标准返回值定义


说明:

文件操作任务是一个异步多线程操作，中止一个任务的接口调用返回值只是简单的返回接口调用是否成功，任务的取消状态最终以获取文件操作任务状态接口调用结果为准

文件操作任务取消后，无法再次开启，外部还应调用删除文件操作任务接口，释放文件操作任务占用的各种系统资源

文件操作任务取消，已完成操作的文件状态不会被回退，外部可调用获取文件操作任务结果报告书接口获取文件操作任务的操作结果
#### **TSK_FileOpTask_UnInitATask**

删除一个文件操作任务

函数原型:  

``` c
INT32 TSK_FileOpTask_UnInitATask(INT32 nTaskID);
```

参数:  
* nTaskID,指定的文件操作任务ID[IN]

返回值:
* KError_Success,成功;
* 其他为失败，可参考W3FS Native SDK库标准返回值定义


说明:

一个文件操作任务完成后（包括主动取消），外部应调用该接口，释放文件操作任务占用的各种系统资源

任务状态为预估及进行的任务，不允许删除，需等待完成，或者主动取消完成后才允许删除
#### **TSK_FileOpTask_GetATaskState**

获取一个文件操作任务的状态

函数原型:  

``` c
INT32 TSK_FileOpTask_GetATaskState(INT32 nTaskID,INT32* nState,INT64* nTotalLength,INT64* nCurrentLength);
```

参数:  
* nTaskID,指定的文件操作任务ID[IN]
* nTotalLength，指定文件操作任务总的待处理数据长度（单位字节）[OUT]
* nCurrentLength，指定文件操作任务当前已处理的数据长度（单位字节）[out]
* nState,指定文件操作任务当前状态[OUT]


返回值:
* KError_Success,成功;
* 其他为失败，可参考W3FS Native SDK库标准返回值定义


说明:

在W3FS-SDK库中，对文件操作任务状态有以下定义:
* 0--待开始，nTotalLength,nCurrentLength数据无效
* 1--数据处理进行中（预估数据长度阶段），nTotalLength,nCurrentLength数据无效，外部界面 提示可简单提示为时间预估中
* 2--数据处理进行中（处理数据阶段），外部可使用nTotalLength,nCurrentLength换算百分比， 或者直接显示数据长度
* 3--数据处理完成（全部数据处理成功），nTotalLength,nCurrentLength数据无效
* 4--数据处理完成（外部主动取消），nTotalLength,nCurrentLength数据无效

任务状态成功，并不代表文件处理成功，文件处理结果要调用获取文件操作任务结果报告书获取

文件操作任务是一个异步多线程任务，外部可通过一个工作线程轮询方式通过操作任务ID定时获取任务状态，为避免界面频繁刷新，定时时长建议不可设置过短，建议500ms一次获取

换算百分比外部要处理一种异常情况，要获取的总数据长度是0，已处理数据长度也长期是0.例如加密一大批空文件的情况
#### **TSK_FileOpTask_GetATaskReport**

获取一个文件操作任务最终结果报告书

函数原型:  

``` c
INT32 TSK_FileOpTask_GetATaskReport(INT32 nTaskID, INT32 nReportMode,BYTE* pReportBuf,INT32* nReportBufLength);
```

参数:  
* nTaskID,指定的文件操作任务ID[IN]
* nReportMode,结果报告书模式[IN]
* pReportBuf,外部准备好的接收结果报告书的缓存区[IN/OUT]
* nReportBufLength,外部准备好的接收结果报告书的缓冲区长度[IN/OUT]

返回值:
* KError_Success,成功;
* 其他为失败，可参考W3FS Native SDK库标准返回值定义


说明:

结果报告书以内存流返回（各个元素直接内存拷贝形式放置于外部提供的内存缓存区中）

简约模式报告书示例如下：
4字节整数count+4字节整数success+4字节整数fail+4字节整数ignore

完整模式报告书示例如下:
4字节整数count+4字节整数success+4字节整数fail+4字节整数ignore+一个个的文件操作结果


单个文件操作结果打包成流后结构如下
4字节nAction+4字节nResult+4字节源文件全路径长度（包括追尾0的长度）+源文件全路径（包括追尾0）+4字节目标文件全路径长度(包括追尾0)+目标文件全路径（包括追尾0），目标文件全路径可能为空，则长度解析出来为0，直接根据偏移读取下一个字段即可

外部可通过先解析出count总的文件元素个数，通过内存偏移循环解析文件操作结果。
``` c
//单个文件操作结果定义如下:
#define FILEOP_RESULT_NOERROR 0 //文件操作成功
#define FILEOP_RESULT_IGNORE -1 //文件操作忽略，例如加密文件时本身就是加密文件，解密文件时本身就是非加密文件,分发文件目标文件还未加密
#define FILEOP_RESULT_FILECANTSERVER -2 //文件操作失败，因为无法服务该文件，例如文件打开失败或者读写失败，及最后的文件后期处理失败
#define FILEOP_RESULT_TSKFAILED -3 //文件操作失败，因为TSK库返回失败，例如创建TEFS结构体失败
#define FILEOP_RESULT_PERMISSIONFAILED -4 //文件操作失败，因为权限问题，例如源文件不允许解密或不允许分发
#define FILEOP_RESULT_VERSIONFAILED -5 ////加密文件,但是版本不支持,拒绝
#define FILEOP_RESULT_DATAFAILED -6 //加密文件,但是关键区校验错误,拒绝
```
#### **TSK_FileOpTask_CanExit**

文件操作任务模块是否可退出

函数原型:  

``` c
INT32 TSK_FileOpTask_CanExit();
```
参数:  
* 无

返回值:
* 0表示当前正在有任务执行中，不可退出，1表示当前所有任务执行完成，程序可退出

说明:

建议外部在应用退出或者用户注销时，调用此接口，查询当前是否还有文件操作任务处理进行状态，不允许退出，需等待所有任务完成或者主动取消后才允许退出
#### **TSK_FileOp_AdjustByFlow**

通过给定的身份及相关属性，调整指定的加密头流数据，并将新的加密头流数据返回给外部

函数原型:  

``` c
INT32 TSK_FileOp_AdjustByFlow(BYTE* pHeadSrc, INT32 nHeadFlowSrcLen, BYTE* pHeadFlowDst, INT32* nHeadFlowDstLen,BOOLEAN bDelAdd, BYTE* nIID, PermissionInfo nPermission, int nLastTime, BYTE* pKeyBuf, DWORD nKeyBufLen);
```
参数:  
* pHeadFlowSrc,外部传入的原始加密头流数据[IN]
* nHeadFlowSrcLen,外部传入的原始加密头流数据长度信息[IN]
* nIID,要修改的身份ID[IN]
* nPermission，要修改的身份对应的权限[IN]
* nLastTime,要修改的身份的最后文件使用时间[IN]
* pKeyBuf,要修改的身份的密钥缓存区[IN]
* nKeyBufLen,要修改的身份的密钥缓存区长度[IN]
* bAdd,对加密头身份区是增加还是删除信封，true增加，false删除[IN]
* pHeadFlowDst,外部准备好的用于接收调整后的加密头流数据缓存区[IN/OUT]
* nHeadFlowDstLen，调整后的加密头流数据长度[IN/OUT]

返回值:
* 返回操作结果，参考TSK库返回结果定义


说明:

外部准备的用于接收新的加密头流数据的缓存区必须足够大，一个新的身份在加密头信封区在目前版本占用154字节，建议外部准备的缓冲区比原始信封大1024字节，真实的调整后的头数据长度将通过nHeadFlowDstLen返回

特殊接口，一般是有代理文件分享需求的APP开发时调用，客户端本地可通过常规的文件分享任务接口完成文件分享操作
### **LocalService部分接口**

W3FS-SDK库内部集成一个本地HttpLocalSerer模块，支持外部使用标准http请求获取一个加密文件的真实数据，支持在无W3FS-SDK实时文件系统内核驱动环境下，通过浏览器途径无感解密一个加密文件
#### **TSK_LocalServer_Start**

启动W3FS-SDK内部的HttpLocalServer模块

函数原型:  

``` c
INT32 TSK_LocalServer_Start(INT32 nPort);
```
参数:  
* nPort,LocalServer指定的端口[IN]

返回值:
* 返回操作结果，参考TSK库返回结果定义

说明: 
在未集成W3FS内核驱动模块的NativeAPP开发中，本地LocalServer是提供加密的数据文件透明无感使用的唯一途径。
#### **TSK_LocalServer_Stop**

停止W3FS-SDK内部的HttpLocalServer模块

函数原型:  

``` c
void TSK_LocalServer_Stop();
```
参数:  
* 无

返回值:
* 无
#### **TSK_LocalServer_SetSystemTime**

设置当前系统时间

函数原型:  

``` c
void TSK_LocalServer_SetSystemTime(INT32 nTime);
```
参数:  
* nTime,外部设置的系统时间

返回值:
* 无

说明:

设置的时间为从1970 年 1 月 1 日午夜开始经过的秒数（4字节整数）
#### **TSK_LocalServer_GetSessionKey**

获取当前随机key

函数原型:  

``` c
bool TSK_LocalServer_GetSessionKey(char pSessionKey[20]);
```
参数:  
* pSessionKey,外部准备好的用于接收SessionKey的缓存区[IN/OUT]

返回值:
* 无

说明:

SessionKey为固定20字节长度信息，用于LocalSever验证，库启动后，外部必须获取当前SessionKey，往LocalServer的请求须带上获取的SessionKey用于LocalServer判断请求是否有效

pSessionKey为方便外部使用，已全部固定为可见字符串，并加入了追尾0，所以实际的sessionkey只有19字节
#### **TSK_LocalServer_SetCurrentWebSiteParam**

设置当前服务dapp网站的基本参数

函数原型:  

``` c
void TSK_LocalServer_SetCurrentWebSiteParam(WCHAR* strRootDir,WCHAR* 
strDynamicFlag,WCHAR* strRemoteServer,WCHAR* strIndexFileName,WCHAR* 
strPemFilePath);
```
参数:  
* strRootDir,当前dapp网站的根目录全路径信息[IN]
* strDynamicFlag，动态请求标识，LocalServer将通过该标识判断是否要将请求转发给对应的服务器，如需支持本地LocalServer动态请求转发，dapp开发过程中应严格遵守自己定义的请求规范,动态请求标识可以有多个，使用|号分隔，例如/d|/api|/opt,localserver要求动态请求标识必须处于请求的Uri开始位置
* strRemoteServer,动态请求转发远程服务器
* strIndexFileName,本地dapp的首页，可传NULL，默认使用index.html作为首页
* strPemFilePath,远程服务器地址如配置成https，则需将该服务器的SSL公钥以标准pem证书文件形式提供给LocalServer

返回值:
* 无

说明:
W3FS Native SDK库内建的LocalServer可作为本地HttpServer服务器使用，支持把dapp的网站数据通过下载到本地并打开的方式，为dapp提供更加快速的启动及使用体验，dapp可以把所有web网站的所有静态资源以压缩包的形式上传到分布式存储或其他类型的网络存储，NativeApp在打开dapp时，可以将压缩包下载到本地，并解压，对dapp所有静态资源的访问可以通过LocalServer在本地执行，动态请求可转发给dapp真正的服务器进行处理，依托于分布式存储或其他第三方存储，为dapp的运营提供更优的解决方案。
目前，W3FS Native SDK库内建的LocalServer在同一时间内只支持对一个dapp网站服务，外部应管理好dapp的打开窗口，再每次打开dapp时，及时更新该网站的本地参数
LocalServer目前只支持dapp静态数据的获取，以及动态请求的转发，如需支持动态请求转发，外部应配置好
外部可通过三个参数均传NULL，代表清除之前配置数据












