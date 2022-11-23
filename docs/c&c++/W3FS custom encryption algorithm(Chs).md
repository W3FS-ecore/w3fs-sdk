# 背景
W3FS协议使用电子信封模式对文件进行加密保护，使用对称加密算法+一文一密的随机key加密文件数据。对随机key和身份的权限信息等使用非对称加密算法（ECC256）+用户身份的公钥进行加密，并将加密结果作为一个eseal信封，保存于加密文件的加密头ESeal Zone区中。
ESeal Zone的eseal信封可以有多个，也就是可以使用多个身份分别对随机key进行加密，形成新的eseal信封保存在ESeal Zone中，这意味着多个用户拥有对这个加密文件的使用权限。
非对称加密算法的固定的，这个由W3FS协议规定，目前W3FS协议选择的是ECC256算法。
用于文件数据加密的对称加密算法是可扩展的，只要实现一个符合W3FS协议加密算法开发规范的对称加密算法，就可以被W3FS协议所接受。目前，W3FS协议自建了多种对称加密算法用于文件的加密，例如AES256,DES3,MARS,SEAL算法等。使用W3FS Native APP SDK进行Native APP开发的团队和开发者，可根据自身的应用需求，灵活选择W3FS协议支持的所有对称加密算法，也可以使用其他算法作为自己开发的Native APP的选项，为APP的用户提供更多的选择。
# W3FS对称加密算法开发规范
W3FS协议要求对称加密算法需实现以下规范:
1.	算法属性说明：
算法的属性说明要求对称加密算法需让W3FS协议知道算法的一些必要信息，主要包括如下信息:
 * 算法唯一tag，所有纳入到W3FS协议的对称加密算法必须有一个唯一tag，让W3FS协议能根据tag识别算法，并调用到正确的属性和函数。算法tag是一个16字节长度的二进制数据，可以使用GUID/UUID，或者其他随机数生成算法生成，tag产生后，不可以更改，否则将造成已有加密文件无法识别tag导致文件无法服务的情况。
* 算法的基本参数说明，包括算法的key长度，以及算法的分组长度，对称加密算法分为分组算法和非分组算法两种，对于非分组算法，算法的分组长度可固定填1.
* 算法的说明，包括算法名称和算法的描述，类型是字符串。主要用于界面显示，让用户能选择算法
2.	算法计算单元管理：
W3FS协议将对称加密算法的加密过程抽象为CipherCell管理，一个CiperCell单元是指对使用一次对称极爱算法的密钥创建的上下文，通过这个CipherCell可以实现对数据流执行加密解密处理，W3FS协议要求对称加密算法必须支持并发对多个CipnerCell提供加解密处理。CipherCell ID是对CipherCell单元的一个索引，通过这个索引可以快速定位这个CipherCell。W3FS协议建议将CipherCell对象的指针采用动态数组管理，动态数组的索引作为这个CipherCell的ID。
3.	算法计算抽象：
W3FS协议将所有对称加密算法对数据的加解密过程抽象陈过了CipherCell加密，开发人员需要对W3FS协议开发如下三个接口，即可让W3FS协议使用统一的调用方式使用添加的对称加密算法。
```c
////////////////////////////////////////////////////////////////////////////
//名称: CipherFunc_CreateCell
//说明: 定义"创建算法单元"函数的函数指针类型
//入参: nKeyLen是秘钥长度,必定等于算法在Cipher_GetDesc中返回的秘钥长度
//      pKey是秘钥,其长度由nKeyLen指定
//出参: pCellID中返回创建的算法单元的ID
//      返回创建算法单元的结果
//          KError_Success,成功;
//          KError_Other,失败,其他错误;
//备注: 一个算法单元是指对一个秘钥创建的上下文,通过该上下文可以实现对送入的数据流执行加密解密处理.
//      算法必须支持并发对多个算法单元提供加解密处理.
//      算法单元ID是对该算法单元上下文的一个索引,通过该索引可以快速定位该算法单元.
//      建议将算法单元的指针采用动态数组管理,动态数组的索引作为算法单元ID.
////////////////////////////////////////////////////////////////////////////
typedef INT32(*CipherFunc_CreateCell)(UINT32 nKeyLen, BYTE * pKey, UINT16 * pCellID);



////////////////////////////////////////////////////////////////////////////
//名称: CipherFunc_DeleteCell
//说明: 定义"删除指定算法单元"函数的函数指针类型
//入参: nCellID是之前调用CipherFunc_CreateCell创建的一个合法的算法单元ID
//出参: 返回删除指定算法单元的结果
//          KError_Success,成功;
//          KError_Other,失败,其他错误;
//备注: 一个算法单元是指对一个秘钥创建的上下文,通过该上下文可以实现对送入的数据流执行加密解密处理.
//      算法必须支持并发对多个算法单元提供加解密处理.
//      算法单元ID是对该算法单元上下文的一个索引,通过该索引可以快速定位该算法单元.
//      建议将算法单元的指针采用动态数组管理,动态数组的索引作为算法单元ID.
////////////////////////////////////////////////////////////////////////////
typedef INT32(*CipherFunc_DeleteCell)(UINT16 nCellID);



////////////////////////////////////////////////////////////////////////////
//名称: CipherFunc_ProcessCell
//说明: 定义"按指定的算法单元处理指定流"函数的函数指针类型
//入参: nCellID是之前调用CipherFunc_CreateCell创建的一个合法的算法单元ID
//      nAction指定为什么目的(加密或解密)而进行查询,可以是ACTION_ENCRYPT或ACTION_DECRYPT
//      nOffset是指定的流在整体流中的偏移,要求按算法分组大小对齐
//      nLength是指定的流的长度,要求按算法分组大小对齐
//      pFlow是指定的流,要求按算法分组大小对齐
//出参: pFlow里是本次操作对流进行修改后的流
//      返回按指定算法单元处理流的结果,为INT32,具有下列语义:
//          KError_Success,成功;
//          KError_Other,失败,其他错误;
//备注: 一个算法单元是指对一个秘钥创建的上下文,通过该上下文可以实现对送入的数据流执行加密解密处理.
//      算法必须支持并发对多个算法单元提供加解密处理.
//      算法单元ID是对该算法单元上下文的一个索引,通过该索引可以快速定位该算法单元.
//      建议将算法单元的指针采用动态数组管理,动态数组的索引作为算法单元ID.
////////////////////////////////////////////////////////////////////////////
typedef INT32(*CipherFunc_ProcessCell)(UINT16 nCellID, BYTE nAction, INT64 nOffset, UINT32 nLength, BYTE * pFlow);
```
# W3FS对称加密算法开发示例
使用W3FS协议内部支持的AES256算法开发示例如下:
1.	声明算法属性
```c
//算法tag
BYTE g_CipherAesTag[CIPHER_TAG_LENGTH]=
{0x72,0x53,0x6b,0xd7,0xf8,0xa3,0xf2,0xd7,0x33,0xb8,0x00,0x80,0x7b,0xa9,0xec,0x2b};
//算法秘钥长度(字节计算)
#define CIPHER_AES_KEY_LENGTH  32
//算法分组大小(字节计算)
#define CIPHER_AES_BLOCK_SIZE  16

//算法名字,各种语言
#define AES_ENGLISH_NAME "AES"
//算法描述,各种语言
#define AES_ENGLISH_DESC "AES block cipher,256bits Key"
```c

2.	算法计算单元管理
```c
////////////////////////////////////////////////////////////////////////////
//名称: AesInit
//说明: 初始化
//入参: 
//出参: 返回是否成功
//备注: 
////////////////////////////////////////////////////////////////////////////
BOOLEAN AesInit()
{
   if (!pAesArray)
   {
      pAesArray=new CAesArray;
      if (!pAesArray) return FALSE;
      return pAesArray->InitSize(AES_ARRAY_GROWSIZE,AES_ARRAY_GROWSIZE);
   }
   else return TRUE;
}


////////////////////////////////////////////////////////////////////////////
//名称: AesUnInit
//说明: 反向初始化
//入参: 
//出参: 
//备注: 
////////////////////////////////////////////////////////////////////////////
void AesUnInit()
{
   if (pAesArray) 
   {
      INT32 count=pAesArray->GetSize();
      PAesItem pCell;
      for(INT32 i=0;i<count;i++)
      {
         pCell=pAesArray->ElementAt(i);
         if (pCell)
         {
            delete pCell;
            pAesArray->SetAt(i,NULL);
         }
      }
   
      delete pAesArray;
      pAesArray=NULL;
   }
}
```

3.	算法计算抽象
```c
////////////////////////////////////////////////////////////////////////////
//名称: AesCreateCell
//说明: 创建算法单元
//入参: nKeyLen是秘钥长度,必定等于算法在Cipher_GetDesc中返回的秘钥长度
//      pKey是秘钥,其长度由nKeyLen指定
//出参: pCellID中返回创建的算法单元的ID
//      返回创建算法单元的结果
//          KError_Success,成功;
//          KError_Other,失败,其他错误;
//备注: 一个算法单元是指对一个秘钥创建的上下文,通过该上下文可以实现对送入的数据流执行加密解密处理.
//      算法必须支持并发对多个算法单元提供加解密处理.
//      算法单元ID是对该算法单元上下文的一个索引,通过该索引可以快速定位该算法单元.
//      建议将算法单元的指针采用动态数组管理,动态数组的索引作为算法单元ID.
////////////////////////////////////////////////////////////////////////////
INT32 AesCreateCell(UINT32 nKeyLen,BYTE * pKey,UINT16 * pCellID)
{
   PAesItem pCell;
   INT32 nCellID;

   //验证key长度
   if (nKeyLen!=CIPHER_AES_KEY_LENGTH) return KError_Other;
   //创建算法单元
   pCell=new AesItem;
   if (!pCell) return KError_Other;
   aes_setkey_enc(&(pCell->enContext),pKey,CIPHER_AES_KEY_LENGTH*8);
   aes_setkey_dec(&(pCell->deContext),pKey,CIPHER_AES_KEY_LENGTH*8);
   //寻找合适的索引
   nCellID=pAesArray->FindAPos();
   if (nCellID==-1) {delete pCell;return KError_Other;}
   if (nCellID & 0xFFFF0000) {delete pCell;return KError_Other;}//限制算法单元索引最多16位
   //写入索引
   pAesArray->SetAt(nCellID,pCell);
   *pCellID=(UINT16)nCellID;
   return KError_Success;
}


////////////////////////////////////////////////////////////////////////////
//名称: AesDeleteCell
//说明: 删除指定算法单元
//入参: nCellID是之前调用CipherFunc_CreateCell创建的一个合法的算法单元ID
//出参: 返回删除指定算法单元的结果
//          KError_Success,成功;
//          KError_Other,失败,其他错误;
//备注: 一个算法单元是指对一个秘钥创建的上下文,通过该上下文可以实现对送入的数据流执行加密解密处理.
//      算法必须支持并发对多个算法单元提供加解密处理.
//      算法单元ID是对该算法单元上下文的一个索引,通过该索引可以快速定位该算法单元.
//      建议将算法单元的指针采用动态数组管理,动态数组的索引作为算法单元ID.
////////////////////////////////////////////////////////////////////////////
INT32 AesDeleteCell(UINT16 nCellID)
{
   PAesItem pCell;
   pCell=pAesArray->ElementAt((INT32)nCellID);
   if (pCell)
   {
      delete pCell;
       pAesArray->SetAt((INT32)nCellID,NULL);
      return KError_Success;
   }
   else return KError_Other;
}


////////////////////////////////////////////////////////////////////////////
//名称: AesProcessCell
//说明: 按指定的算法单元处理指定流
//入参: nCellID是之前调用CipherFunc_CreateCell创建的一个合法的算法单元ID
//      nAction指定为什么目的(加密或解密)而进行查询,可以是ACTION_ENCRYPT或ACTION_DECRYPT
//      nOffset是指定的流在整体流中的偏移,要求按算法分组大小对齐
//      nLength是指定的流的长度,要求按算法分组大小对齐
//      pFlow是指定的流,要求按算法分组大小对齐
//出参: pFlow里是本次操作对流进行修改后的流
//      返回按指定算法单元处理流的结果,为INT32,具有下列语义:
//          KError_Success,成功;
//          KError_Other,失败,其他错误;
//备注: 一个算法单元是指对一个秘钥创建的上下文,通过该上下文可以实现对送入的数据流执行加密解密处理.
//      算法必须支持并发对多个算法单元提供加解密处理.
//      算法单元ID是对该算法单元上下文的一个索引,通过该索引可以快速定位该算法单元.
//      建议将算法单元的指针采用动态数组管理,动态数组的索引作为算法单元ID.
////////////////////////////////////////////////////////////////////////////
INT32 AesProcessCell(UINT16 nCellID,BYTE nAction,INT64 nOffset,UINT32 nLength,BYTE * pFlow)
{
   DWORD nTimes=nLength/AES_BLOCK_BYTE_NUM; //多少个block
   DWORD nBase=0;
   DWORD i;
   PAesItem pCell;
   pCell=pAesArray->ElementAt((INT32)nCellID);
   if (pCell)
   {
      if (nAction==ACTION_ENCRYPT) 
      {
         for (i=0;i<nTimes;i++)
         {
            aes_crypt_ecb(&(pCell->enContext),AES_ENCRYPT,pFlow+nBase,pFlow+nBase);
            nBase+=AES_BLOCK_BYTE_NUM;
         }  
         return KError_Success;
      }
      else if (nAction==ACTION_DECRYPT) 
      {
         for (i=0;i<nTimes;i++)
         {
            aes_crypt_ecb(&(pCell->deContext),AES_DECRYPT,pFlow+nBase,pFlow+nBase);
            nBase+=AES_BLOCK_BYTE_NUM;
         }  
         return KError_Success;
      }
      else return KError_Other;
   }
   else return KError_Other;
}
```

