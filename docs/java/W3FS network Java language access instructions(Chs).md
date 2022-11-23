[TOC]

# w3fs网络Java语言接入说明

w3fs网络为其用户提供了功能强大且具有现实运用价值的能力，其中包含区块链领域的相关技术能力、不限制类型的文件加解密处理能力、文件去中心化存储能力等。这些技术能力的集合可以适用于很多现实场景中，比如运用于NFT领域中，它将使NFT在特定的规则下不受文件类型限制、没有安全风险的进行各种形式的流通，你也可以结合这些能力创造出你能想象得到的任何形式的Dapp。
本文档中将针对JAVA服务提供SDK对接流程做出详细说明。

* W3FS文件加解密SDK的接入说明。


开发者或者开发团队可根据自己定制化的Dapp，选择针对性的技术进行接入。

## JAVA接入使用说明
阅读此说明，你将了解产品信息及使用方式，快速接入并使用本产品
### 1、关于产品
**1.1.功能介绍**
通过简单的集成，就可以使用本SDK的加解密文件、分享加密文件、文件透明使用功能。
加密文件：由加密信封头head(加密头长度、加密头填充区)、实际加密文件body、两部分组成，加密头长度可通过 getEncryptHeadLen()接口获取、加密头填充区可通过getHeadAndFillSumLen()接口获取。
解密文件：也叫文件脱密，即解密完的文件是个全新未加密的文件。
分享文件：分享的是加密文件(未加密文件不可分享)，再原有的加密文件种添加/删除待操作的身份。
文件透明使用：不会解密文件(不生成未加密文件)，通过启用LocalServer后使用WebView可对加密文件进行不解密，直接透明使用。

**1.2 名词释义**
|名词|释义|
|-----|-----|
|Head|由加密头长度跟加密头填充区组成，包含文件操作者、操作权限、操作期限等信息（跟Body组成完整的加密文件）|
|Body|实际加密后的文件内容（跟Head组成完整的加密文件）|
|KeyId|唯一身份ID|
|FilePublicKey|文件加解密公钥|
|FilePrivateKey|文件加解密私钥|
|TaskId|文件加解密等操作的任务id|
|LocalServer|启用LocalServer后使用WebView可对加密文件进行不解密,直接透明使用|
### 2、Java接入指南（提供各个接口说明以及常用的接口组合已完成核心业务功能）
**2.1 把SDK导入项目的lib(或者libs)目录下**
![20220711180008.jpg](images/20220711180008.jpg)
**2.2 提供简便的方法创建文件加解密公私钥对以及登录使用的nIID**

```
//Ethereum account private key
String ethAccountPriKey = "";
IdentityIssueExBase64DTO identityIssueExBase64DTO = TskOperate.createBase64KeyPair(ethAccountPriKey);
//返回信息：公钥，私钥，以及登录使用的nIID（keyId）
{"nRet":0,"publicFileKey":"","publicFileKeyLen":78,"privateFileKey":"","privateFileKeyLen":112,"keyId":"","keyIdLen":20}

```
**2.3 全局初始化方法（此方法必须在项目启动时初始化）：**
```
//例子：使用static 关键词 在项目启动时做初始化动作或者利用CommandLineRunner进行初始化也可以
static {
    String keyId="";
    String privateFileKey="";
    //返回 true 表示初始化成功 false 表示失败
    boolean b = TskOperate.initAccountAndPermission(keyId, privateFileKey);
    System.out.println("init :" + b);
}


@Component
public class InitData implements CommandLineRunner {
    @Override
    public void run(String... args) throws Exception {
        String keyId="";
        String privateFileKey="";
        boolean b = TskOperate.initAccountAndPermission(keyId, privateFileKey);
        System.out.println("init :"+b);
    }
}
```

**2.4 分享方法：**
```
//文件头流Base64字符串
String Head = "";
byte[] headByte = Base64Util.decodeString(saveFileInfoDTO.getHeadFileBase64());
//以太坊地址
String userAdd="0x123456789".substring(2);
//userAdd 公钥
byte[] userPubKeyByte = Base64Util.decodeString(UserFilePublicKey());
//nLastTime  -1 表示没有时间限制 其它时间戳代表文件可使用的时间限制（123456789）
byte[] bytes = TSKJni.FileOpTaskAdjustByFlow(headByte, headByte.length, true, Hex.decode(userAdd), (short) -1, -1, userPubKeyByte, userPubKeyByte.length);
 if (checkBytes(bytes)) {
    byte[] bytes1 = EthUtils.subBytes(bytes, 0,8, bytes.length-8);
    //截取8位之后的数据并转成Base64字符串返回
    String encodeToString = Base64Utils.encodeToString(bytes1);
    retrun encodeToString;
 }

//////////////////////////////【判断分享返回信息】/////////////////////////////////////////
//判断返回是否大于8位并且判断  4字节操作结果(ret) 是否为：0
public static boolean checkBytes(byte[] bytes){
        if(bytes.length<8){
            logger.error("Share error FileOpTaskAdjustByFlow returns:{}", Arrays.toString(bytes));
            return false;
        }
        byte[] bytes1 = EthUtils.subBytes(bytes, 0,0, 4);
        int i = EthUtils.bytesToInt(bytes1);
        return i==0;
    }
```

### 3、SDK提供接口说明：
```
    ////////////////////////////////////////////////////////////////////////////////
                    【调用方式：初始化==》 int i = TSKJni.Init();】
    ////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    //------初始化接口------
    //要使用TSK库,首先调用初始化接口.如果初始化失败,TSK库将不可用.
    //不再需要使用TSK库(通常是软件退出),调用反向初始化接口.
    //////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.Init
    //说明: 初始化TSK库
    //入参:
    //出参: 返回初始化的结果,为INT32,具有下列语义:
    //          KError.Success,成功;
    //          KError.CantConnectKernel,失败,无法连接内核;
    //          KError.Other,失败,其他错误;
    ////////////////////////////////////////////////////////////////////////////
    public static native int Init();

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.UnInit
    //说明: 反向初始化TSK库
    //入参:
    //出参:
    ////////////////////////////////////////////////////////////////////////////
    public static native void UnInit();

    //////////////////////////////////////////////////////////////////////////////
    //------账号接口------
    //用户相关;库仅支持单一账号登录.
    //
    //每一个身份都有一个内部ID.
    //身份ID从1开始分配,意味着0是被特殊保留的.
    //每一个账号可能具有多个身份,但是单独表征该账号用户身份(代表这个人)的只可能是一个.
    //////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.LoginUser
    //说明: 登录账号
    //入参: nIID是对应的代表该用户的唯一身份的内部ID
    //出参: 返回登录账号的结果,为INT32,具有下列语义:
    //          KError.Success,成功;
    //          KError.MultiUser,失败,存在其他登录用户;
    //          KError.Other,失败,其他错误;
    //备注:
    ////////////////////////////////////////////////////////////////////////////
    public static native int LoginUser(byte[] nIID);

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.LogoutUser
    //说明: 登出当前账号
    //入参:
    //出参: 返回登出账号的结果,为INT32,具有下列语义:
    //          KError.Success,成功;
    //          KError.NoUser,失败,当前无用户登录;
    //          KError.Other,失败,其他错误;
    //备注:
    ////////////////////////////////////////////////////////////////////////////
    public static native int LogoutUser();

    //////////////////////////////////////////////////////////////////////////////
    //------摘要接口------
    //////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.DigestCRC32
    //说明: 迭代支持对多个流进行CRC32摘要
    //入参: nFlowLen是指定要计算CRC32摘要的流大小
    //      pFlow是指定要计算CRC32摘要的流
    //      nCookie中指定迭代需要的cookie
    //出参: json字符串形式返回摘要结果
    //     摘要开始返回值{nRet=0,cookie=1000}
    //     摘要进行中返回值{nRet=0}
    //     摘要结束返回值{nRet=0,nCRC32=1000}
    //备注: CRC32摘要是一种高速但非可靠的摘要算法,可以用于对加密信息块结构数据本身的验证.
    //      该接口对多个流进行联合摘要.
    //      开始摘要时将获取cookie,该值就一直不变直到结束摘要.
    //      简单来说,判断依据是:
    //      当流长度nFlowLen为0，且cookie,表示开始摘要
    //      当流长度nFlowLen不为0，且cookie不为0，表示摘要进行中
    //      当流长度nFlowLen为0，且cookie不为0，表示摘要结束，返回最终的摘要结果，并清空内部摘要对象
    //
    //      典型的使用方式如下:
    //      1.调用DigestCRC32(0,NULL,0)表示开始摘要
    //        流(nFlowLen和pFlow)被指定为空(nFlowLen为0,pFlow为NULL)
    //        这表示让摘要算法初始化,准备开始对多个流进行统一联合摘要.并返回摘要过程的cookie值，该cookie值唯一对应此次联合摘要
    //      2.对每一个流调用DigestCRC32(nFlowLen,pFlow,pCookie)表示进行摘要
    //        流(nFlowLen和pFlow)指定一个具体的流
    //        摘要cookie指针(pCookie)非0,其中存储的摘要cookie为步骤1中获取的摘要cookie0
    //        这表示让摘要算法对指定的该流进行摘要.
    //      3.调用DigestCRC32(0,NULL,pCookie)表示结束摘要并接收结果
    //        流(nFlowLen和pFlow)被指定为空(nFlowLen为0,pFlow为NULL)
    //        摘要cookie指针(pCookie)非NULL,其中存储的摘要cookie为步骤1中获取的摘要cookie
    //        这表示让摘要算法终止,并返回现在(最终)的摘要结果.
    //      实例,以对两个流联合进行CRC32摘要为例,代码如下:
    //      INT64 cookie=0;
    //      TSK.DigestCRC32(0,NULL,0);
    //      TSK.DigestCRC32(nFlowLen,pFlow,cookie);
    //      TSK.DigestCRC32(nFlowLen2,pFlow2,cookie);
    //      TSK.DigestCRC32(0,NULL,&cookie);
    ////////////////////////////////////////////////////////////////////////////
    public static native String DigestCRC32(int nFlowLen, byte[] pFlow, long nCookie);

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.DigestCRC32Single
    //说明: 对数据流流进行CRC32单次摘要
    //入参: nflowlen是指定要计算CRC32摘要的流大小
    //      buffer是指定要计算CRC32摘要的流
    //出参: 返回crc32摘要结果
    //备注: CRC32摘要是一种高速但非可靠的摘要算法,可以用于对加密信息块结构数据本身的验证.
    ////////////////////////////////////////////////////////////////////////////
    public static native int DigestCRC32Single(int nflowlen, byte[] buffer);

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.DigestMD5
    //说明: 迭代支持对多个流进行MD5摘要
    //入参: nFlowLen是指定要计算MD5摘要的流大小
    //      pFlow是指定要计算MD5摘要的流
    //      nCookie中指定迭代需要的cookie
    //出参: json字符串形式返回摘要结果
    //     摘要开始返回值{nRet=0,cookie=1000}
    //     摘要进行中返回值{nRet=0}
    //     摘要结束返回值{nRet=0,MD5=“abcded”} MD5为经base64编码后的字符串，外部要先解密，MD5码原始长度为16字节
    //备注: MD5摘要是一种低速但可靠的摘要算法,可以用于对文件数据本身的签名验证.
    //      使用方式和TSK.DigestCRC32一致,只是接收最终结果使用16字节的缓冲.
    ////////////////////////////////////////////////////////////////////////////
    public static native String DigestMD5(int nFlowLen, byte[] pFlow, long nCookie);

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.DigestMD5Single
    //说明: 对数据流流进行MD5单次摘要
    //入参: nflowlen是指定要计算MD5摘要的流大小
    //      buffer是指定要计算MD5摘要的流
    //出参: 返回MD5摘要结果
    //备注:
    ////////////////////////////////////////////////////////////////////////////
    public static native byte[] DigestMD5Single(int nflowlen, byte[] buffer);

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.DigestSha256
    //说明: 迭代支持对多个流进行Sha256摘要
    //入参: nFlowLen是指定要计算Sha256摘要的流大小
    //      pFlow是指定要计算Sha256摘要的流
    //      nCookie中指定迭代需要的cookie
    //出参: json字符串形式返回摘要结果
    //     摘要开始返回值{nRet=0,cookie=1000}
    //     摘要进行中返回值{nRet=0}
    //     摘要结束返回值{nRet=0,SHA256=“abcded”} SHA256为经base64编码后的字符串，外部要先解密，SHA256码原始长度为32字节
    //备注: SHA256摘要是一种低速但可靠的摘要算法,可以用于对文件数据本身的签名验证.
    //      使用方式和TSK.DigestCRC32一致,只是接收最终结果使用32字节的缓冲.
    //      针对tsk平台，建议本地密钥生成的种子都通过tsk库的sha256摘要算法生成
    ////////////////////////////////////////////////////////////////////////////
    public static native byte[] DigestSha256(int nFlowLen, byte[] pFlow, long nCookie);

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.DigestSha256Single
    //说明: 对数据流流进行SHA256单次摘要
    //入参: nflowlen是指定要计算SHA256摘要的流大小
    //      buffer是指定要计算SHA256摘要的流
    //出参: 返回SHA256摘要结果
    //备注: 针对tsk平台，建议本地密钥生成的种子都通过tsk库的sha256摘要算法生成
    ////////////////////////////////////////////////////////////////////////////
    public static native byte[] DigestSha256Single(int nflowlen, byte[] buffer);

    //////////////////////////////////////////////////////////////////////////////
    //------身份算法(非对称加密算法)接口------
    //////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.IdentityIssueExBase64
    //说明: 产生(颁发)一个身份对象
    //入参: pSeed,外部指定的颁发身份的种子信息
    //      nSeedLen，外部指定的颁发身份的种子信息长度
    //出参: 返回json对象字符串形式给外部，json对象格式示例如下
    //     {nRet:0,PublicKey:"abcd",PublicKeyLen:78,PrivateKey:"abcd",PrivateKeyLen:112,KeyID:"abcd",KeyIDLen:20}
    //     nRet为0，即接口调用成功的情况下，其他的结果值才有意义
    //     PublicKey,PrivateKey为密钥信息base64编码后的数据，只为通过接口可以返回外部，外部需解码后使用
    //     PublicKeyLen,PrivateKeyLen为公钥钥原始二进制数据流长度，基于ecc原理，公私钥二进制流的长度不是固定的，所以返回给外部
    //     KeyID,生成的用于加密的密钥的身份ID，该ID与身份密钥唯一绑定，是一个重要数据，后续使用该身份密钥用于文件加解密时，都需提供该ID，固定20字节
    //备注: 身份对象是一个不透明的对象实体,外部不需要了解其内部构成.
    //      只支持ecc 256k1身份
    //      如外部指定了种子信息,生成的身份信息将是一致的,种子信息强制要求为32字节长度,可不指定,将随机颁发身份证书
    //      基于ecc原理，ecc私钥本身包含了公钥信息，所以私钥数据可以当作公钥使用，实现公钥能实现的一切功能，例如公钥加密，可以使用私钥，加密接口指定动作为使用公钥加密即可
    ////////////////////////////////////////////////////////////////////////////
    public static native String IdentityIssueExBase64(byte[] pSeed, int nSeedLen);

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.IdentityIssueGetPrivateKey
    //说明: 产生(颁发)一个身份对象
    //入参: pSeed,外部指定的颁发身份的种子信息
    //      nSeedLen，外部指定的颁发身份的种子信息长度
    //出参: 返回私钥二进制数据
    //备注: 身份对象是一个不透明的对象实体,外部不需要了解其内部构成.
    //      只支持ecc 256k1身份
    //      如外部指定了种子信息,生成的身份信息将是一致的,种子信息强制要求为32字节长度,可不指定,将随机颁发身份证书
    //      基于ecc原理，ecc私钥本身包含了公钥信息，所以私钥数据可以当作公钥使用，实现公钥能实现的一切功能，例如公钥加密，可以使用私钥，加密接口指定动作为使用公钥加密即可
    //      要分离对应的公钥数据，需将返回的私钥调用GetPublicKeyByPrivateKey接口
    ////////////////////////////////////////////////////////////////////////////
    public static native byte[] IdentityIssueGetPrivateKey(byte[] jbyteArray, int nSeedLen);

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.IdentityGetPublicKeyByPrivateKey
    //说明: 根据传入的私钥分离出对应的公钥二进制数据
    //入参: pPrivateKey,私钥二进制数据
    //      nPrivateKeyLen，私钥长度
    //出参: 返回公钥二进制数据
    //备注:
    ////////////////////////////////////////////////////////////////////////////
    public static native byte[] IdentityGetPublicKeyByPrivateKey(byte[] jbyteArray, int nSeedLen);

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.IdentityGetKeyIDByPublicKey
    //说明: 根据传入的公钥计算出身份的ID
    //入参: pPublicKey,公钥二进制数据
    //      nPublicKeyLen，公钥长度
    //出参: 返回身份ID二进制数据，身份ID固定20字节，身份的密钥ID是重要数据，与身份的密钥唯一绑定，后续使用身份密钥时，都需传入该ID
    //备注:
    ////////////////////////////////////////////////////////////////////////////
    public static native byte[] IdentityGetKeyIDByPublicKey(byte[] pPublicKey, int nPublicKeyLen);

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.SetHoldIdentity
    //说明: 设置库存储的当前用户持有的身份
    //入参: nListVerb是标准的列表操作动词,无LIST.VERB.MODIFY语义
    //       nIdentityID是该身份对应的内部ID
    //       nLastTime是该身份的公钥用于默认加密时给予的最大文件使用权限时间，默认传-1
    //       pKeyBuf是该身份的密钥二进制格式信息
    //       nKeyLen是该身份的密钥二进制格式信息长度
    //出参: 返回设置的结果,为INT32,具有下列语义:
    //          KError.Success,成功;
    //          KError.CantConnectKernel,失败,无法连接内核;
    //          KError.NoUser,失败,当前无登录用户;
    //          KError.SyntaxError,失败,语法错误(例如不支持的动词等);
    //          KError.MultiObject,失败,语义错误,该Key已经存在(该身份ID已经存在);
    //          KError.CantFindObject,失败,语义错误,删除不存在的Key(该身份ID不存在);
    //          KError.Other,失败,其他错误;
    //备注: 当前用户所持有的身份为一个列表,其通常通过 LIST.VERB.CLEAR/LIST.VERB.ADD/LIST.VERB.DELETE 来进行管理.
    //       当LIST.VERB.ADD时,所有参数显然都需要提供.
    //       当LIST.VERB.DELETE时,参数显然只需要提供nIdentityID即可.
    //
    //       LIST.VERB.DEFAULT为设置用户身份;
    //       当希望设置(或改变)一个默认身份时,该身份应该已经在持有身份列表中,所以参数只需提供nIdentityID即可.
    //       当希望清除默认身份时,应该指定nIdentityID为IDENTITY.NULL,其他参数不用提供.
    //
    //       所有增加的身份建议nPermission均设置为最大权限.
    //       strPemPrivateKey按照pkcs#1规范存储,其是包括私钥和公钥信息的.
    ////////////////////////////////////////////////////////////////////////////
    public static native int SetHoldIdentity(int nListVerb, byte[] nIdentityID, short nPermissionInfo, int nLastTime, byte[] jbyteArray, int nKeyBufLen);

    //////////////////////////////////////////////////////////////////////////////
    //------对称加密算法接口------
    //加密算法作为可以扩展增加的组件,被限定为对称算法,用于实际的数据加解密.
    //加密算法,可由加密算法dll(或内核态dll)额外扩展新的对称加密算法.
    //////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.GetCipherDesc
    //说明: 获取当前所有加载了的算法描述
    //入参:
    //出参: 返回当前tsk库锁支持的所有用于数据加密的对称加密算法的描述报告书
    //     json格式返回，格式如下:
    //     [{tag:xxx,name:xxx,desc:xxxx},...]
    ////////////////////////////////////////////////////////////////////////////
    public static native String GetCipherDesc();

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.GetCipherInfo
    //说明: 获取指定的算法信息
    //入参: strciphertag是要获取的算法tag(即该算法的GUID标签),固定为16字节;该参数可以为空字符串,表示指定默认算法;
    //出参: 返回外部json对象的字符串形式，格式示例如下:
    //     {nRet:0,pKeyLength:16,pBlockSize:1}
    //     nRet为0的情况下，后续语义才有意义，pKeyLength返回该算法要求的秘钥长度(字节计算)
    //      pBlockSize返回该算法要求的分组大小(字节计算,因此序列算法返回1)
    //备注: 应用层在构造流处理对象时可以通过该接口确定算法的秘钥大小和分组大小.
    ////////////////////////////////////////////////////////////////////////////
    public static native String GetCipherInfo(String strciphertag);

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.SetDefaultCipher
    //说明: 设置当前的默认算法
    //入参: strciphertag是要设置为默认算法的算法tag(即该算法的GUID标签)
    //出参: 返回设置默认算法的结果,为INT32,具有下列语义:
    //          KError.Success,成功;
    //          KError.CantConnectKernel,失败,无法连接内核;
    //          KError.CipherError,失败,未能找到该算法;
    //          KError.Other,失败,其他错误;
    //备注: 应用层界面上通过该接口设置默认算法.
    //      加密时如果指定算法tag为NULL时,将使用默认算法进行加密.
    //
    //      指定默认算法在某些环境下并不是必需的,但在需要库自动进行某些加解密动作(例如文件系统自动加解密)的环境下是必需的.
    ////////////////////////////////////////////////////////////////////////////
    public static native int SetDefaultCipher(String strciphertag);

    ////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.SetDefaultZone
    //说明: 设置默认加密段落
    //入参: nLen是要设置的默认加密段落的大小(字节计数)
    //出参: 返回设置默认加密段落的结果,为INT32,具有下列语义:
    //          KError.Success,成功;
    //          KError.CantConnectKernel,失败,无法连接内核;
    //          KError.Other,失败,其他错误;
    //备注: 默认加密段落固定是从文件头,到指定的大小处的文件段落.
    //      段落大小为0,这实际上等于未加密;段落大小为-1,这实际上等于加密整个文件.
    //
    //      指定默认加密段落在某些环境下并不是必需的,但在需要库自动进行某些加解密动作(例如文件系统自动加解密)的环境下是必需的.
    //      注意,指定默认加密段落并不会影响TSK.ProcessCipherCell的处理.
    ////////////////////////////////////////////////////////////////////////////
    public static native int SetDefaultZone(long nLen);

    ///////////////////////////////////////// ///////////////////////
    //名称：TSKJni.FileOpTaskInit
    //说明：初始化一个文件操作任务
    //参数：nAction[IN],动作动词，1,encrypt；2，decrypt；3，share
    // nThreadCount[IN]，任务线程数，默认为1
    //返回：小于0表示文件操作任务初始化失败
    // 大于等于0表示成功，返回值为任务ID，后续操作以ID为索引
    //备注：逐个文件的多线程执行
    // 多线程数可以根据当前cpu个数来设置
    ///////////////////////////////////////// ///////////////////////////
    public static native int FileOpTaskInit(int nAction, int nThreadCount);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.FileOpTaskPushAFileToTask
    //说明: 将等待操作的文件/文件夹的完整路径添加到指定的文件操作任务中
    //入参: nTaskID[IN],任务 ID，由 TSK.FileOpTask.Init 返回
    //      pSrcFullPath[IN]，源文件/文件夹路径
    //      pDstFullPath[IN],目标文件/文件夹路径
    //出参:INT32, KError.Success,success;
    //备注: 可以在单个文件操作任务中处理多个文件/文件夹
     // 这个接口可以被多次调用
     // 该函数只在任务真正启动之前有效，当任务状态已经启动时，包括任务挂起时，不能再次调用该接口完成添加操作目标
     // pSrcFullPath 和 pDstFullPath 不能是同一个路径，pSrcFullPath 必须是真实的
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native int FileOpTaskPushAFileToTask(int nTaskID, String strSrcFilePath, String strDstFilePath);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.FileOpTaskPushAAction
    //说明: 将身份添加到指定的文件共享任务
    //入参: nTaskID[IN],任务 ID，由 TSK.FileOpTask.Init 返回
    //      bDelAdd[IN],动作，true为添加，false为删除
    //      IID[IN]，身份标识
    //      nPermission,身份的许可
    //      nLastTime, 上次使用时间的文件标识
    //      pKeyBuf[IN]，身份密钥的缓冲区
    //      nKeyBufLen，身份密钥的缓冲区长度
    //出参:INT32, KError.Success,success;
    //备注: 此界面仅适用于文件共享
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native int FileOpTaskPushAAction(int nTaskID, boolean bDelAdd, byte[] IID, short nPermission, int nLastTime, byte[] pKeyBuf, int nKeyBufLen);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.FileOpTaskSetShareSign
    //说明: 设置文件操作任务签名动作
    //入参: nTaskID[IN],任务 ID，由 TSK.FileOpTask.Init 返回
     // nSignAction[IN],签名动作，0表示保持，1表示设置，2表示清除
    //出参： INT32,KError.Success,success;
    //备注: 此界面仅适用于文件共享
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native int FileOpTaskSetShareSign(int nTaskID, byte nSignAction);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.FileOpTaskStartATask
    //说明: 启动文件操作任务
    //入参: nTaskID[IN],任务 ID，由 TSK.FileOpTask.Init 返回
    //出参:INT32,KError.Success,
    //备注: 任务启动后无法调用设置参数接口。 异步操作，通过启动一个异步多线程来完成事务
/////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native int FileOpTaskStartATask(int nTaskID);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.FileOpTaskCancelATask
    //说明: 停止文件操作任务
    //入参: nTaskID[IN],任务 ID，由 TSK.FileOpTask.Init 返回
    //出参: INT32,KError.Success,success
    //备注: 文件操作任务是异步多线程操作，中止任务的接口调用返回值简单返回接口调用是否成功，
     // 并且任务的状态是基于TSK.FileOpTask.GetATaskState接口调用的结果
     // 文件操作任务取消后无法再次打开，需要调用TSK.FileOpTask.UnInitATask接口销毁任务
     // 文件操作任务被取消，操作完成状态不会回滚，通过TSK.FileOpTask.GetATaskReport接口获取任务报告
/////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native int FileOpTaskCancelATask(int nTaskID);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.FileOpTaskUnInitATask
    //说明: 销毁文件操作任务
    //入参: nTaskID[IN],任务 ID，由 TSK.FileOpTask.Init 返回
    //出参: INT32,KError.Success,success
    //备注：状态为预估和进行中的任务不允许删除，必须等待完成或主动取消后才允许删除
/////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native int FileOpTaskUnInitATask(int nTaskID);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.FileOpTaskGetATaskState
    //说明: 获取任务状态
    //入参: nTaskID[IN],任务 ID，由 TSK.FileOpTask.Init 返回
    //出参: 返回值作为json字符串传递，例如{nRet:0,nState:0,nTotalLength:1000,nCurrentLength:900},
    // nTotalLength 和 nCurrentLength 是 64 位整数，以字节为单位
    // nRet，返回值，只针对KError.Success，其他字段有效，否则函数调用失败
    // nTotalLength，文件操作任务的总数据长度（以字节为单位）
    // nCurrentLength，处理数据的长度（以字节为单位）
    // nState，任务的当前状态，0为待启动，nTotalLength,nCurrentLength数据无效
    // 1 数据处理中（估计数据长度阶段），nTotalLength,nCurrentLength数据无效
    // 2 数据处理中（处理数据阶段）
    // 3个数据处理完成（所有数据处理成功），nTotalLength,nCurrentLength数据无效
    // 4数据处理完成（主动取消），nTotalLength,nCurrentLength数据无效
    //备注：任务状态成功不代表文件处理成功。通过TSK.FileOpTask.GetATaskReport获取文件处理结果
    // 一旦任务开始，建议一个周期获取500ms
    // 转换百分比要处理nTotalLength为0，nCurrentLength也为0的异常情况，例如加密大批量空文件的情况
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native int FileOpTaskGetATaskState(int nTaskID);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.FileOpTaskCanExit
    //说明: 文件操作模块可以退出
    //入参:
    //出参: 0表示当前有任务正在执行，不能退出，1表示当前所有任务都已执行，程序可以退出
 ////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native int FileOpTaskCanExit();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.FileOpTaskGetATaskReport
    //说明: 获取任务结果报告
    //入参: nTaskID[IN],任务 ID，由 TSK.FileOpTask.Init 返回
    //      nReportMode[IN],nReportMode[IN],thr报告模式，1极简模式，结果报告只返回文件总数，处理文件数，成功文件数，失败文件数，忽略文件数 2全模式， 结果报告除了返回简单模式的//内容外，还包括具体的文档处理状态
    //出参: 返回值作为json字符串传递，
    //      e.g.:
    //     Minimalist mode:{ret:0,count：10，success：4，fail:1,ignore:5}
    //     Full mode:{ret:0,count：10，success：4，fail:1,ignore:5,
    //                   filelist:[{srcpath：c:\\1.txt,dstpath：d:\\1.txt,action:1,result：0}.。。]}
/////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native String FileOpTaskGetATaskReport(int nTaskID, int nReportMode);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.FileOpTaskAdjustByFlow
    //说明: Adjusts the specified encrypted header stream data by the given identity and related attributes to return the new encrypted header stream data
    //入参: pHeadFlowSrc[IN],源头流量
    //      nHeadFlowSrcLen[IN],源头流量长度
    //      nIID[IN],身份标识
    //      nPermission[IN]，身份的许可
    //      nLastTime[IN],上次使用时间的文件标识
    //      pKeyBuf[IN],身份密钥的缓冲区
    //      nKeyBufLen[IN],身份密钥的缓冲区长度
    //      bAdd[IN],操作的动作，true添加身份，false删除身份
    //出参: 操作的动作，true添加身份，false删除身份
    //      内存结构如下：4字节操作结果(ret)+4字节新头数据长度(nHeadFlowDstLen)+头数据(pHeadFlowDst)
    //      返回的内存数组应该根据格式进行解析，只有当ret为KError.Success时，后面的数据才有意义
    //////////////////////////////////////////////////////////////////////////////////////////////
    public static native byte[] FileOpTaskAdjustByFlow(byte[] pHeadSrc, int nHeadFlowSrcLen, boolean bDelAdd, byte[] nIID, short nPermission, int nLastTime, byte[] pKeyBuf, int nKeyBufLen);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.FileOpGetESealInfoByPath
    //入参: 获取指定文件的eseal区的所有身份信息
    //入参: strFilePath[IN],文件路径
    //出参: 返回文件 ESeal 部分中所有身份 ID 的数组，每个身份 ID 20 个字节
  ///////////////////////////////////////////////////////////////////////////////////////////////////
    public static native byte[] FileOpGetESealInfoByPath(String strFilePath);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.LocalServerStop
    //说明: 停止TSK SDK内部的HttpLocalServer模块
    //备注:肯定成功
/////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native int LocalServerStart(int nPort);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.LocalServerStop
    //说明: 停止 HttpLocalServer 模块
/////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native int LocalServerStop();

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.LocalServerSetSystemTime
    //说明: 设置当前系统时间
    //入参: nTime,外部设置的系统时间
    //出参:
    //备注:肯定成功
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native int LocalServerSetSystemTime(int nTime);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.LocalServerGetSessionKey
    //说明: 获取当前随机key
    //入参:
    //出参:字符串形式的返回值，外部直接使用
    //备注: 本地LocalServer服务启动后，外部必须获取当前SessionKey，往LocalServer的请求须带上获取的SessionKey
    //     用于LocalServer判断请求是否有效
    //     pSessionKey为方便外部使用，已全部固定为可见字符串，并加入了追尾0，所以实际的sessionkey只有19字节
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native String LocalServerGetSessionKey();

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //名称: TSKJni.LocalServerSetCurrentDappParam
    //说明: 设置当前欲打开的本地dapp应用的web参数
    //入参: strDappRootDir,本地dapp的root文件夹（dapp本地资源的根目录全路径信息）
    //     strDynamicFlag,本地dapp所有动态请求参数标识，可以为空，表示本地dapp是一个纯静态应用
    //                     动态请求标识可以有多个，使用|号分隔，例如/d|/api|/opt,localserver要求动态请求标识必须处于请求的Uri开始位置
    //     strRemoteServer，本地dapp对应的远程服务器，所有带动态请求参数标识的请求，都会被LocalServer转发到远程服务器
    //     strIndexFileName，本地dapp的首页文件名，默认为index.html，所以该参数可以传空
    //     strPemFilePath,如远程服务器要求Https，需提供域名的ssl公钥pem证书格式全路径给LocalServer使用，pem由dapp开发商提供，文件格式保存到本地
    //出参:固定返回0，肯定成功
    //备注:TSK内建的LocalServer可作为本地HttpServer服务器使用，支持把dapp的网站数据通过下载到本地并打开的方式，为dapp提供更加快速的启动及使用体验
    //    目前，TSK内建的LocalServer在同一时间内只支持对一个dapp网站服务，外部应管理好dapp的打开窗口，再每次打开dapp时，及时更新该网站的本地参数
    //    LocalServer目前只支持dapp静态数据的获取，以及动态请求的转发，如需支持动态请求转发，外部应配置好
    //    外部可通过三个参数均传空值，代表清除之前配置数据
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    public static native int LocalServerSetCurrentDappParam(String strDappRootDir, String strDynamicFlag, String strRemoteServer, String strIndexFileName, String strPemFilePath);

```
### 4、SDK接口返回说明：
/////////////////////////////////////////////
//定义接口错误码
//错误码>=0,为成功;
//错误码<0,为失败;
/////////////////////////////////////////////
//成功
KError.Success                         0
//成功,但是未处理任何流数据
KError.NoDataHandled                   1
//成功,新建该对象
KError.CreateObject                    10
//成功,打开该对象
KError.OpenObject                      11
//成功,打开该对象并且覆盖该对象
KError.OverrideObject                  12
//失败,长度错误
KError.LengthError                     -1
//失败,超时
KError.TimeOut                         -2
//失败，缓存区长度不足
KError.OutOfLength                     -3
//失败,无法连接内核
KError.CantConnectKernel               -10
//失败,当前存在被服务的文件
KError.FileServing                     -11
//失败,多个登录用户
KError.MultiUser                       -20
//失败,无登录用户
KError.NoUser                          -21
//失败,语法错误
KError.SyntaxError                     -30
//失败,找不到指定对象
KError.CantFindObject                  -31
//失败,多个指定对象
KError.MultiObject                     -32
//失败,暂时找不到指定对象(当前无法确定能找到指定对象)
KError.MaybeFindObject                 -33
//失败,通用逻辑错误
KError.CommonLogic                     -34
//失败,加密算法错误(通常是没有加密算法)
KError.CipherError                     -40
//失败,加密算法内部错误
KError.CipherInnerError                -41
//失败，权限不足
KError.PermissionDenied                -42
//失败,处理加密头结构失败,CRC错
KError.HeaderCrcError                  -50
//失败,身份信封处理失败
KError.IdentitySealError               -51
//失败,其他错误(通常是内存分配错误)
KError.Other                           -100