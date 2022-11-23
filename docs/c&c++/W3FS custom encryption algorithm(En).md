# Introduction
W3FS protocol uses eseal mode to encrypt and protect files, using symmetric encryption algorithm + one-text-one-secret random key to encrypt file data.The random key and permission information are encrypted using asymmetric encryption algorithm (ECC256) + public key of user identity, and the encryption result is saved as an eseal envelope in the encryption header ESeal Zone area of the encrypted file.
There can be multiple eseal envelopes in ESeal Zone, which means that multiple identities can be used to encrypt the random key to form a new eseal envelope saved in ESeal Zone, meaning that multiple users have access to this encrypted file.
The asymmetric encryption algorithm is fixed, and this is specified by the W3FS protocol, which currently chooses the ECC256 algorithm.
Symmetric encryption algorithms for file data encryption are scalable and can be accepted by the W3FS protocol as long as it is implemented that conforms to the W3FS protocol encryption algorithm development specification.
W3FS protocol has built in a variety of symmetric encryption algorithms for file encryption, such as AES256, DES3, MARS, SEAL and so on. Teams and developers who use W3FS Native APP SDK for Native APP development can flexibly choose all symmetric encryption algorithms supported by W3FS protocol according to their own application requirements, or use other algorithms as options for their own Native APP development, providing more choices for APP users.
# W3FS symmetric encryption algorithm development specification
The W3FS protocol requires that the symmetric encryption algorithm implement the following specification:
1. Description of algorithm properties. 
   The property description of the algorithm requires the symmetric encryption algorithm to let the W3FS protocol know some necessary information about the algorithm, mainly including the following information:
   * Algorithm unique tag, all the symmetric encryption algorithms incorporated into the W3FS protocol must have a unique tag, so that W3FS protocol can identify the algorithm based on the tag and call to the correct attributes and functions. The algorithm tag is a 16-byte-long binary data, which can be generated using GUID/UUID, or other random number generation algorithms. After the tag is generated, it cannot be changed, otherwise it will cause the old encrypted file to be unable to recognize the tag and lead to an unserviceable file.
   * The basic parameters of the algorithm are described, including the key length of the algorithm and the grouping length of the algorithm, the symmetric encryption algorithm is divided into grouping algorithm and non-grouping algorithm, for the non-grouping algorithm, the grouping length of the algorithm can be fixed by filling 1.
   * Description of the algorithm, including the name of the algorithm and a description of the algorithm, of type string. Mainly Used for interface display to enable the user to select the algorithm
  2. CipherCell Management. 
    The W3FS protocol abstracts the encryption process of symmetric encryption algorithm as CipherCell management. A CiperCell is a context created by using the key of the symmetric encryption algorithm once, through which the CipherCell can perform encryption and decryption processing on the data stream, the W3FS protocol requires that the symmetric encryption algorithm must support the concurrent encryption and decryption of multiple CipherCells. The CipherCell ID is an index of the CipherCell, through which the CipherCell can be quickly located. The W3FS protocol recommends that pointers to CipherCell objects be managed using a dynamic array, with the index of the dynamic array being used as the ID of the CipherCell.
  3. CipherCell abstraction. 
   The W3FS protocol abstracts the process of encryption and decryption of data by all symmetric encryption algorithms into CipherCell encryption, and developers need to develop the following three interfaces to the W3FS protocol to allow the W3FS protocol to use the added symmetric encryption algorithms using a unified call.
   ```c
   ////////////////////////////////////////////////////////////////////////////
   //Name: CipherFunc_CreateCell
   //Description: Define the function pointer type of the "Create CipherCell" function
   //Parameters: nKeyLen[IN],the length of key
   //      pKey[IN],the buffer of key
   //      pCellID[OUT],the CipherCell ID
   //Return: KError_Success,success;
   //          KError_Other,fail;
   ////////////////////////////////////////////////////////////////////////////
  typedef INT32(*CipherFunc_CreateCell)(UINT32 nKeyLen, BYTE * pKey, UINT16 * pCellID);

   ////////////////////////////////////////////////////////////////////////////
   //Name: CipherFunc_DeleteCell
   //Description: Define the function pointer type of the "Delete CipherCell" function
   //Parameters: nCellID[IN],the CipherCell ID
   //Return: KError_Success,success;
   //          KError_Other,fail;
   ////////////////////////////////////////////////////////////////////////////
   typedef INT32(*CipherFunc_DeleteCell)(UINT16 nCellID);

   ////////////////////////////////////////////////////////////////////////////
   //Name: CipherFunc_ProcessCell
   //Description: Define the function pointer type of the "Processes data streams by CipherCell" function
   //Parameters: nCellID[IN],the CipherCell ID
   //      nAction[IN],the action(ACTION_ENCRYPT or ACTION_DECRYPT)
   //      nOffset[IN],the offset of the flow in the overall flow, requiring alignment by algorithm group size
   //      nLength[IN],the length of the flow,requiring alignment by algorithm group size
   //      pFlow[IN/OUT],the flow
   //Return: INT32,KError_Success,success;
   //          KError_Other,fail;
   ////////////////////////////////////////////////////////////////////////////
   typedef INT32(*CipherFunc_ProcessCell)(UINT16 nCellID, BYTE nAction, INT64 nOffset, UINT32 nLength, BYTE * pFlow);
   ```
# W3FS symmetric encryption algorithm development example
An example of development using the AES256 algorithm, which is supported internally by the W3FS protocol:
1.	Description of AES256
```c
//the tag
BYTE g_CipherAesTag[CIPHER_TAG_LENGTH]=
{0x72,0x53,0x6b,0xd7,0xf8,0xa3,0xf2,0xd7,0x33,0xb8,0x00,0x80,0x7b,0xa9,0xec,0x2b};
//the length of key(In bytes)
#define CIPHER_AES_KEY_LENGTH  32
//the block size(In bytes)
#define CIPHER_AES_BLOCK_SIZE  16

//name
#define AES_ENGLISH_NAME "AES"
//Description
#define AES_ENGLISH_DESC "AES block cipher,256bits Key"
```c

2.	CipherCell Management for AES256
```c
////////////////////////////////////////////////////////////////////////////
//Name: AesInit
//Description: Init 
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
//Name: AesUnInit
//Description: UnInit
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

3.	CipherCell abstraction for AES256
```c
////////////////////////////////////////////////////////////////////////////
//Name: AesCreateCell
//Description: Create a CipherCell
////////////////////////////////////////////////////////////////////////////
INT32 AesCreateCell(UINT32 nKeyLen,BYTE * pKey,UINT16 * pCellID)
{
   PAesItem pCell;
   INT32 nCellID;

   //Check the Parameter
   if (nKeyLen!=CIPHER_AES_KEY_LENGTH) return KError_Other;
   //Create CipherCell
   pCell=new AesItem;
   if (!pCell) return KError_Other;
   aes_setkey_enc(&(pCell->enContext),pKey,CIPHER_AES_KEY_LENGTH*8);
   aes_setkey_dec(&(pCell->deContext),pKey,CIPHER_AES_KEY_LENGTH*8);
   //Find the CipherCellID
   nCellID=pAesArray->FindAPos();
   if (nCellID==-1) {delete pCell;return KError_Other;}
   if (nCellID & 0xFFFF0000) {delete pCell;return KError_Other;}
   //Save the CipherCell
   pAesArray->SetAt(nCellID,pCell);
   *pCellID=(UINT16)nCellID;
   return KError_Success;
}

////////////////////////////////////////////////////////////////////////////
//Name: AesDeleteCell
//Description: Delete a CipherCell
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
//Name: AesProcessCell
//Description: Processes data streams by CipherCell
////////////////////////////////////////////////////////////////////////////
INT32 AesProcessCell(UINT16 nCellID,BYTE nAction,INT64 nOffset,UINT32 nLength,BYTE * pFlow)
{
   DWORD nTimes=nLength/AES_BLOCK_BYTE_NUM; 
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