//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����:TSKInterface_JNI.h
//˵����TSK�����ӿ�ʵ��JNI����
//���ߣ�Jason
//��ʷ:2021.09.30 Jason ��һ�ζ�����ļ�
//��ע:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TSKANDROIDV2_TSKINTERFACE_JNI_H
#define TSKANDROIDV2_TSKINTERFACE_JNI_H

#include <jni.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����jni�ӿ�ʵ�ֹ�����һЩ����Ҫ���õĺ�
//����java����jbyteArray���ݵ�Native��Ĵ���
#define JNI2NATIVE_JBYTEARRAY(pBufJNI,pBufNative,nLen) \
         jbyte* ba = env->GetByteArrayElements(pBufJNI, JNI_FALSE);  \
         pBufNative = new BYTE[nLen];   \
         memset(pBufNative,0,nLen);   \
         memcpy(pBufNative,ba,nLen);

         //����Native����jstring���ݵ�JNI�㴦��
#define NATIVE2JNI_JSTRING (jsonobj,stringobj)  \
         Json::StreamWriterBuilder writerBuilder;   \
         std::unique_ptr<Json::StreamWriter> json_write(writerBuilder.newStreamWriter());   \
          std::ostringstream ss;   \
           json_write->write(jsonobj,&ss);    \
            stringobj = ss.str();

#endif //TSKANDRIODV2_TSKINTERFACE_JNI_H

//////////////////////////////////////////////////////////////////////////////
//------��ʼ���ӿ�------
//Ҫʹ��TSK��,���ȵ��ó�ʼ���ӿ�.�����ʼ��ʧ��,TSK�⽫������.
//������Ҫʹ��TSK��(ͨ��������˳�),���÷����ʼ���ӿ�.
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandroidv2_TSKJni_Init
//˵��: ��ʼ��TSK��
//���:
//����: ���س�ʼ���Ľ��,ΪINT32,������������:
//          KError_Success,�ɹ�;
//          KError_CantConnectKernel,ʧ��,�޷������ں�;
//          KError_Other,ʧ��,��������;
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandroidv2_TSKJni_Init(
        JNIEnv* env,
        jobject /* this */);

////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandroidv2_TSKJni_UnInit
//˵��: �����ʼ��TSK��
//���:
//����:
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT void JNICALL
Java_io_edfs_tskandroidv2_TSKJni_UnInit(
        JNIEnv* env,
        jobject /* this */);

//////////////////////////////////////////////////////////////////////////////
//------�˺Žӿ�------
//�û����;���֧�ֵ�һ�˺ŵ�¼.
//
//ÿһ����ݶ���һ���ڲ�ID.
//���ID��1��ʼ����,��ζ��0�Ǳ����Ᵽ����.
//ÿһ���˺ſ��ܾ��ж�����,���ǵ����������˺��û����(���������)��ֻ������һ��.
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandroidv2_TSKJni_LoginUser
//˵��: ��¼�˺�
//���: nIID�Ƕ�Ӧ�Ĵ�����û���Ψһ��ݵ��ڲ�ID
//����: ���ص�¼�˺ŵĽ��,ΪINT32,������������:
//          KError_Success,�ɹ�;
//          KError_MultiUser,ʧ��,����������¼�û�;
//          KError_Other,ʧ��,��������;
//��ע:
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandroidv2_TSKJni_LoginUser(
        JNIEnv* env,
        jobject /* this */,jint nIID);

////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandroidv2_TSKJni_LogoutUser
//˵��: �ǳ���ǰ�˺�
//���:
//����: ���صǳ��˺ŵĽ��,ΪINT32,������������:
//          KError_Success,�ɹ�;
//          KError_NoUser,ʧ��,��ǰ���û���¼;
//          KError_Other,ʧ��,��������;
//��ע:
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandroidv2_TSKJni_LogoutUser(
        JNIEnv* env,
        jobject /* this */);

//////////////////////////////////////////////////////////////////////////////
//------ժҪ�ӿ�------
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandroidv2_TSKJni_DigestCRC32
//˵��: ����֧�ֶԶ��������CRC32ժҪ
//���: nFlowLen��ָ��Ҫ����CRC32ժҪ������С
//      pFlow��ָ��Ҫ����CRC32ժҪ����
//      nCookie��ָ��������Ҫ��cookie
//����: json�ַ�����ʽ����ժҪ���
//     ժҪ��ʼ����ֵ{nRet=0,cookie=1000}
//     ժҪ�����з���ֵ{nRet=0}
//     ժҪ��������ֵ{nRet=0,nCRC32=1000}
//��ע: CRC32ժҪ��һ�ָ��ٵ��ǿɿ���ժҪ�㷨,�������ڶԼ�����Ϣ��ṹ���ݱ������֤.
//      �ýӿڶԶ������������ժҪ.
//      ��ʼժҪʱ����ȡcookie,��ֵ��һֱ����ֱ������ժҪ.
//      ����˵,�ж�������:
//      ��������nFlowLenΪ0����cookie,��ʾ��ʼժҪ
//      ��������nFlowLen��Ϊ0����cookie��Ϊ0����ʾժҪ������
//      ��������nFlowLenΪ0����cookie��Ϊ0����ʾժҪ�������������յ�ժҪ�����������ڲ�ժҪ����
//
//      ���͵�ʹ�÷�ʽ����:
//      1.����DigestCRC32(0,NULL,0)��ʾ��ʼժҪ
//        ��(nFlowLen��pFlow)��ָ��Ϊ��(nFlowLenΪ0,pFlowΪNULL)
//        ���ʾ��ժҪ�㷨��ʼ��,׼����ʼ�Զ��������ͳһ����ժҪ.������ժҪ���̵�cookieֵ����cookieֵΨһ��Ӧ�˴�����ժҪ
//      2.��ÿһ��������DigestCRC32(nFlowLen,pFlow,pCookie)��ʾ����ժҪ
//        ��(nFlowLen��pFlow)ָ��һ���������
//        ժҪcookieָ��(pCookie)��0,���д洢��ժҪcookieΪ����1�л�ȡ��ժҪcookie0
//        ���ʾ��ժҪ�㷨��ָ���ĸ�������ժҪ.
//      3.����DigestCRC32(0,NULL,pCookie)��ʾ����ժҪ�����ս��
//        ��(nFlowLen��pFlow)��ָ��Ϊ��(nFlowLenΪ0,pFlowΪNULL)
//        ժҪcookieָ��(pCookie)��NULL,���д洢��ժҪcookieΪ����1�л�ȡ��ժҪcookie
//        ���ʾ��ժҪ�㷨��ֹ,����������(����)��ժҪ���.
//      ʵ��,�Զ����������Ͻ���CRC32ժҪΪ��,��������:
//      INT64 cookie=0;
//      TSK_DigestCRC32(0,NULL,0);
//      TSK_DigestCRC32(nFlowLen,pFlow,cookie);
//      TSK_DigestCRC32(nFlowLen2,pFlow2,cookie);
//      TSK_DigestCRC32(0,NULL,&cookie);
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_edfs_tskandroidv2_TSKJni_DigestCRC32(
        JNIEnv* env,
        jobject /* this */,jint nFlowLen,jbyteArray pFlow,jlong nCookie) ;

////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandroidv2_TSKJni_DigestCRC32Single
//˵��: ��������������CRC32����ժҪ
//���: nflowlen��ָ��Ҫ����CRC32ժҪ������С
//      buffer��ָ��Ҫ����CRC32ժҪ����
//����: ����crc32ժҪ���
//��ע: CRC32ժҪ��һ�ָ��ٵ��ǿɿ���ժҪ�㷨,�������ڶԼ�����Ϣ��ṹ���ݱ������֤.
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandroidv2_TSKJni_DigestCRC32Single(
        JNIEnv* env,
        jobject /* this */,jint nflowlen,jbyteArray buffer);

////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandroidv2_TSKJni_DigestMD5
//˵��: ����֧�ֶԶ��������MD5ժҪ
//���: nFlowLen��ָ��Ҫ����MD5ժҪ������С
//      pFlow��ָ��Ҫ����MD5ժҪ����
//      nCookie��ָ��������Ҫ��cookie
//����: json�ַ�����ʽ����ժҪ���
//     ժҪ��ʼ����ֵ{nRet=0,cookie=1000}
//     ժҪ�����з���ֵ{nRet=0}
//     ժҪ��������ֵ{nRet=0,MD5=��abcded��} MD5Ϊ��base64�������ַ������ⲿҪ�Ƚ��ܣ�MD5��ԭʼ����Ϊ16�ֽ�
//��ע: MD5ժҪ��һ�ֵ��ٵ��ɿ���ժҪ�㷨,�������ڶ��ļ����ݱ����ǩ����֤.
//      ʹ�÷�ʽ��TSK_DigestCRC32һ��,ֻ�ǽ������ս��ʹ��16�ֽڵĻ���.
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_edfs_tskandroidv2_TSKJni_DigestMD5(
        JNIEnv* env,
        jobject /* this */,jint nFlowLen,jbyteArray pFlow,jlong nCookie);

////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandroidv2_TSKJni_DigestMD5Single
//˵��: ��������������MD5����ժҪ
//���: nflowlen��ָ��Ҫ����MD5ժҪ������С
//      buffer��ָ��Ҫ����MD5ժҪ����
//����: ����MD5ժҪ���
//��ע:
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jbyteArray JNICALL
Java_io_edfs_tskandroidv2_TSKJni_DigestMD5Single(
        JNIEnv* env,
        jobject /* this */,jint nflowlen,jbyteArray buffer);

////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_DigestSha256
//˵��: ����֧�ֶԶ��������Sha256ժҪ
//���: nFlowLen��ָ��Ҫ����Sha256ժҪ������С
//      pFlow��ָ��Ҫ����Sha256ժҪ����
//      nCookie��ָ��������Ҫ��cookie
//����: json�ַ�����ʽ����ժҪ���
//     ժҪ��ʼ����ֵ{nRet=0,cookie=1000}
//     ժҪ�����з���ֵ{nRet=0}
//     ժҪ��������ֵ{nRet=0,SHA256=��abcded��} SHA256Ϊ��base64�������ַ������ⲿҪ�Ƚ��ܣ�SHA256��ԭʼ����Ϊ32�ֽ�
//��ע: SHA256ժҪ��һ�ֵ��ٵ��ɿ���ժҪ�㷨,�������ڶ��ļ����ݱ����ǩ����֤.
//      ʹ�÷�ʽ��TSK_DigestCRC32һ��,ֻ�ǽ������ս��ʹ��32�ֽڵĻ���.
//      ���tskƽ̨�����鱾����Կ���ɵ����Ӷ�ͨ��tsk���sha256ժҪ�㷨����
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_edfs_tskandriodv2_TSKJni_DigestSha256(
        JNIEnv* env,
        jobject /* this */,jint nFlowLen,jbyteArray pFlow,jlong nCookie);

////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_DigestSha256Single
//˵��: ��������������SHA256����ժҪ
//���: nflowlen��ָ��Ҫ����SHA256ժҪ������С
//      buffer��ָ��Ҫ����SHA256ժҪ����
//����: ����SHA256ժҪ���
//��ע: ���tskƽ̨�����鱾����Կ���ɵ����Ӷ�ͨ��tsk���sha256ժҪ�㷨����
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jbyteArray JNICALL
Java_io_edfs_tskandriodv2_TSKJni_DigestSha256Single(
        JNIEnv* env,
        jobject /* this */,jint nflowlen,jbyteArray buffer);

//////////////////////////////////////////////////////////////////////////////
//------����㷨(�ǶԳƼ����㷨)�ӿ�------
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_IdentityIssueEx
//˵��: ����(�䷢)һ����ݶ���
//���: pSeed,�ⲿָ���İ䷢��ݵ�������Ϣ
//      nSeedLen���ⲿָ���İ䷢��ݵ�������Ϣ����
//����: ����json�����ַ�����ʽ���ⲿ��json�����ʽʾ������
//     {nRet:0,PublicKey:"abcd",PublicKeyLen:78,PrivateKey:"abcd",PrivateKeyLen:112}
//     nRetΪ0�����ӿڵ��óɹ�������£������Ľ��ֵ��������
//     PublicKey,PrivateKeyΪ��Կ��Ϣbase64���������ݣ�ֻΪͨ���ӿڿ��Է����ⲿ���ⲿ������ʹ��
//     PublicKeyLen,PrivateKeyLenΪ��ԿԿԭʼ���������������ȣ�����eccԭ����˽Կ���������ĳ��Ȳ��ǹ̶��ģ����Է��ظ��ⲿ
//��ע: ��ݶ�����һ����͸���Ķ���ʵ��,�ⲿ����Ҫ�˽����ڲ�����.
//      ֻ֧��ecc 256k1���
//      ���ⲿָ����������Ϣ,���ɵ������Ϣ����һ�µ�,������Ϣǿ��Ҫ��Ϊ32�ֽڳ���,�ɲ�ָ��,������䷢���֤��
//      ����eccԭ��ecc˽Կ��������˹�Կ��Ϣ������˽Կ���ݿ��Ե�����Կʹ�ã�ʵ�ֹ�Կ��ʵ�ֵ�һ�й��ܣ����繫Կ���ܣ�����ʹ��˽Կ�����ܽӿ�ָ������Ϊʹ�ù�Կ���ܼ���
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_edfs_tskandriodv2_TSKJni_IdentityIssueEx(
        JNIEnv* env,
        jobject /* this */,jbyteArray pSeed,jint nSeedLen);

//////////////////////////////////////////////////////////////////////////////
//------��¼�û��ĳ�����ݽӿ�------
//�û����;��Ȼֻ�ܵ�¼һ���û�,�����ڲ����Զ�����Ϊ��ǰ�û�.
//���ʹ����ݵ�Ĭ������,Ӧ�ò㸺�����ô洢,����Ҫ�������洢.
//
//ÿһ����ݶ���һ���ڲ�ID.
//���ID��1��ʼ����,��ζ��0�Ǳ����Ᵽ����.
//�ڼ�����Ϣ��ṹ��,ǩ����֤���������������ļ���ǩ���߾����ø�ǩ����(�û�����)��ݵ��ڲ�ID������.
//�ڼ�����Ϣ��ṹ��,�����������ļ��ľ���Ȩ��Ҳ���ø��ļ������ŷ��и�����ݵ��ڲ�ID������.
//Ӧ�ò��������ʾʱ,����ͨ�����غ���/Ⱥ�����������ID��Ӧ�����ֺϲ���IDһ����ʾ,��������޷��������ֿɽ���ʾ��ID.
//
//����˽���ƺ͹�����,ֻ���ڷ����������ϸ���һ���������ID�ķ�Χ���ɱ��ⷢ���ظ������ID.
//
//��ݻ�����Ҫ��Ĭ��������Ҫ���õ���(�ں�).
//��ݻ����ṩ��˽Կ�ӽ���,��Կ�ӽ����㷨�ɿ��ṩ.
//��ݻ������ں���Ҳ�����б�ʽ����:
//Ĭ�����Ϊ���û������;ƥ����(��һ���б�)����Ϊ���û����е��������,һ�㼴������б�.
//
//�����洢������ǿ�����Ϊ�Զ�Ĭ�ϲ���(�ں��Զ����ܽ��ܵ�)����Ҫ��,��ʵ����Ҳ���ڲ���Ҫ��洢�����.
//����,��һ�������ļ����зַ������ѻ�Ⱥ�Ĺ���,ʹ���˺��ѻ�Ⱥ�Ĺ�Կ;
//����,��һ��ǩ��������֤�Ĺ���,ʹ���˺��ѻ�Ⱥ�Ĺ�Կ;
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_SetHoldIdentity
//˵��: ���ÿ�洢�ĵ�ǰ�û����е����
//���: nListVerb�Ǳ�׼���б��������,��LIST_VERB_MODIFY����
//       nIdentityID�Ǹ���ݶ�Ӧ���ڲ�ID
//       nPermission�Ǹ���ݵĹ�Կ����Ĭ�ϼ���ʱ�����Ȩ�ޱ�
//       pKeyBuf�Ǹ���ݵ���Կ�����Ƹ�ʽ��Ϣ
//       nKeyLen�Ǹ���ݵ���Կ�����Ƹ�ʽ��Ϣ����
//����: �������õĽ��,ΪINT32,������������:
//          KError_Success,�ɹ�;
//          KError_CantConnectKernel,ʧ��,�޷������ں�;
//          KError_NoUser,ʧ��,��ǰ�޵�¼�û�;
//          KError_SyntaxError,ʧ��,�﷨����(���粻֧�ֵĶ��ʵ�);
//          KError_MultiObject,ʧ��,�������,��Key�Ѿ�����(�����ID�Ѿ�����);
//          KError_CantFindObject,ʧ��,�������,ɾ�������ڵ�Key(�����ID������);
//          KError_Other,ʧ��,��������;
//��ע: ��ǰ�û������е����Ϊһ���б�,��ͨ��ͨ�� LIST_VERB_CLEAR/LIST_VERB_ADD/LIST_VERB_DELETE �����й���.
//       ��LIST_VERB_ADDʱ,���в�����Ȼ����Ҫ�ṩ.
//       ��LIST_VERB_DELETEʱ,������Ȼֻ��Ҫ�ṩnIdentityID����.
//
//       LIST_VERB_DEFAULTΪ�����û����;
//       ��ϣ������(��ı�)һ��Ĭ�����ʱ,�����Ӧ���Ѿ��ڳ�������б���,���Բ���ֻ���ṩnIdentityID����.
//       ��ϣ�����Ĭ�����ʱ,Ӧ��ָ��nIdentityIDΪIDENTITY_NULL,�������������ṩ.
//
//       �������ӵ���ݽ���nPermission������Ϊ���Ȩ��.
//       strPemPrivateKey����pkcs#1�淶�洢,���ǰ���˽Կ�͹�Կ��Ϣ��.
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_SetHoldIdentity(
        JNIEnv* env,
        jobject /* this */,jint nListVerb,jint nIdentityID,jlong nPermission,jbyteArray pKeyBuf,jint nKeyBufLen );

//////////////////////////////////////////////////////////////////////////////
//------�ԳƼ����㷨�ӿ�------
//�����㷨��Ϊ������չ���ӵ����,���޶�Ϊ�Գ��㷨,����ʵ�ʵ����ݼӽ���.
//�����㷨,���ɼ����㷨dll(���ں�̬dll)������չ�µĶԳƼ����㷨.
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_GetCipherDesc
//˵��: ��ȡ��ǰ���м����˵��㷨����
//���:
//����: ���ص�ǰtsk����֧�ֵ������������ݼ��ܵĶԳƼ����㷨������������
//     �����������������㷨�����������飬�ⲿ�����н�����һ���㷨��������Ϣ�̶�����������ɣ�
//     tagCipher:�̶�16�ֽڵ��㷨id���壬ͨ����idΨһ��ʶtsk��֧�ֵ�һ�������㷨
//     Name:�㷨���ƣ�ansi��ʽ�ַ��������Ȳ��̶����ⲿ��ͨ���ַ�����׷β0�ж�
//     Desc��һ�仰���㷨������anse��ʽ�ַ��������Ȳ��̶����ⲿ��ͨ���ַ�����׷β0�ж�
//��ע: Ӧ�ò������ͨ���ýӿڻ�ȡ�����˵��㷨������ʾ.
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jbyteArray JNICALL
Java_io_edfs_tskandriodv2_TSKJni_GetCipherDesc(
        JNIEnv* env,
        jobject /* this */);

////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_GetCipherInfo
//˵��: ��ȡָ�����㷨��Ϣ
//���: tagCipher��Ҫ��ȡ���㷨tag(�����㷨��GUID��ǩ),�̶�Ϊ16�ֽ�;�ò�������ΪNULL,��ʾָ��Ĭ���㷨;
//����: �����ⲿjson������ַ�����ʽ����ʽʾ������:
//     {nRet:0,pKeyLength:16,pBlockSize:1}
//     nRetΪ0������£���������������壬pKeyLength���ظ��㷨Ҫ�����Կ����(�ֽڼ���)
//      pBlockSize���ظ��㷨Ҫ��ķ����С(�ֽڼ���,��������㷨����1)
//��ע: Ӧ�ò��ڹ������������ʱ����ͨ���ýӿ�ȷ���㷨����Կ��С�ͷ����С.
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_edfs_tskandriodv2_TSKJni_GetCipherInfo(
        JNIEnv* env,
        jobject /* this */,jbyteArray ptagCipher,jint ntagCipherLen);

////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_SetDefaultCipher
//˵��: ���õ�ǰ��Ĭ���㷨
//���: tagCipher��Ҫ����ΪĬ���㷨���㷨tag(�����㷨��GUID��ǩ),�̶�Ϊ16�ֽ�
//����: ��������Ĭ���㷨�Ľ��,ΪINT32,������������:
//          KError_Success,�ɹ�;
//          KError_CantConnectKernel,ʧ��,�޷������ں�;
//          KError_CipherError,ʧ��,δ���ҵ����㷨;
//          KError_Other,ʧ��,��������;
//��ע: Ӧ�ò������ͨ���ýӿ�����Ĭ���㷨.
//      ����ʱ���ָ���㷨tagΪNULLʱ,��ʹ��Ĭ���㷨���м���.
//
//      ָ��Ĭ���㷨��ĳЩ�����²����Ǳ����,������Ҫ���Զ�����ĳЩ�ӽ��ܶ���(�����ļ�ϵͳ�Զ��ӽ���)�Ļ������Ǳ����.
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_SetDefaultCipher(
        JNIEnv* env,
        jobject /* this */,jbyteArray ptagCipher,jint ntagCipherLen);

////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_SetDefaultZone
//˵��: ����Ĭ�ϼ��ܶ���
//���: nLen��Ҫ���õ�Ĭ�ϼ��ܶ���Ĵ�С(�ֽڼ���)
//����: ��������Ĭ�ϼ��ܶ���Ľ��,ΪINT32,������������:
//          KError_Success,�ɹ�;
//          KError_CantConnectKernel,ʧ��,�޷������ں�;
//          KError_Other,ʧ��,��������;
//��ע: Ĭ�ϼ��ܶ���̶��Ǵ��ļ�ͷ,��ָ���Ĵ�С�����ļ�����.
//      �����СΪ0,��ʵ���ϵ���δ����;�����СΪ-1,��ʵ���ϵ��ڼ��������ļ�.
//
//      ָ��Ĭ�ϼ��ܶ�����ĳЩ�����²����Ǳ����,������Ҫ���Զ�����ĳЩ�ӽ��ܶ���(�����ļ�ϵͳ�Զ��ӽ���)�Ļ������Ǳ����.
//      ע��,ָ��Ĭ�ϼ��ܶ��䲢����Ӱ��TSK_ProcessCipherCell�Ĵ���.
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_SetDefaultZone(
        JNIEnv* env,
        jobject /* this */,jlong nLen) ;

//////////////////////////////////////////////////////////////////////////////
//------������ӿ�------
//////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowCreateByDefault
//˵��: ����Ĭ����Ϣ���������Ϣ��ο��ṹ
//���:
//����: ���ش�������id���ⲿ�豣���id�����������������������ڣ�����id���ļ��ϸ�һһ��Ӧ
//     ����ֵС��0���Ǵ���ʧ�ܣ���ʧ��ԭ�������¼���:
//          KError_IdentitySealError,ʧ��,δ���ҵ����;
//          KError_CipherError,ʧ��,δ���ҵ����㷨;
//          KError_CipherInnerError,ʧ��,�㷨�ڲ�����;
//          KError_Other,ʧ��,��������;
//��ע: �̶���ʹ���û���ݹ����ŷ�.
//      ��Ȼ�û�������Ǹ������Ȩ��,��ôʵ������ǽ�ʹ���û���ݲ����Ȩ�޹����ŷ�.
///////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowCreateByDefault(
        JNIEnv* env,
        jobject /* this */);

///////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowCreateByFlow
//˵��: ���������������Ϣ��ο��ṹ
//���: jpinput,Ҫ���䳤�ȱ�����ڵ��ڼ�����Ϣ���ʵ�����ݳ���
//      ninputlen,�ⲿ����������ݳ���
//����: ���ش�������id���ⲿ�豣���id�����������������������ڣ�����id���ļ��ϸ�һһ��Ӧ
////     ����ֵС��0���Ǵ���ʧ�ܣ���ʧ��ԭ�������¼���:
////          KError_IdentitySealError,ʧ��,δ���ҵ����;
////          KError_CipherError,ʧ��,δ���ҵ����㷨;
////          KError_CipherInnerError,ʧ��,�㷨�ڲ�����;
////          KError_Other,ʧ��,��������;
//��ע:
///////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowCreateByFlow(
        JNIEnv* env,
        jobject /* this */,jbyteArray jpinput,jint ninputlen);

///////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowGetSealInfo
//˵��: ��ȡָ����������������Ϣ
//���: nflowid,ָ���������id��Ϣ
//����: ����Ŀ��������������������Ϣ��json�����ʽ����һ���������id��ɣ�����:[0x1000,0x1001,0x1002]
///////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowGetSealInfo(
        JNIEnv* env,
        jobject /* this */,jint nflowid);

///////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowModifyForNew
//˵��: �޸�ָ��������Ϣ��ο��ṹ,Ҫ����Ϊ��ʵ�������趨
//���: nflowid��ָ����������id
//����: ���ع�����,ΪINT32,������������:
//          KError_Success,�ɹ�;
//          KError_IdentitySealError,ʧ��,δ���ҵ����;
//          KError_CipherError,ʧ��,δ���ҵ����㷨;
//          KError_CipherInnerError,ʧ��,�㷨�ڲ�����;
//          KError_Other,ʧ��,��������;
//��ע: ֮ǰ����CreateByFlow�����ɹ��ļ�����Ϣ��ο��ṹ��Ӧ��һ��������Ϣͷ.
//      ���ڽ��������һ��ȫ�µ�����ʵ��(�ļ�)ȥ,��Ȼ�漰���������ļ�Ψһ,һ��һ�ܵ�����.
//
//      ���ǵ�ǩ���Ǹ������Ķ���,��һ�������ļ����ϱ�д��Ĺ��̻ᵼ�·���Ҫ��ǩ����������.
//      ����,��Ȼ��������Ϊ����Ŀ¼�����ļ������µ�Ϊ��ʵ�������趨,��ô�̶�Ĩȥǩ��Ҫ��.
///////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowModifyForNew(
        JNIEnv* env,
        jobject /* this */,jint nflowid);

///////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowModifyForSeal
//˵��: �޸�ָ��������Ϣ��ο��ṹ,Ҫ����Ϊ�ַ��������ŷ⴦�������趨
//���: nflowid��ָ��Ҫ������������id
//      bDelAdd��˵��ɾ����������(�޸�)�ŷ�;FALSEΪɾ���ŷ�,TRUEΪ����(�޸�)�ŷ�;
//      pKeyBuf��ָ��Ҫɾ��������(�޸�)�ŷ��Ӧ�������Ϣ��Կ��Ϣ(Ҳ������˽Կ)���ڲ���ʹ�ù�Կ���д���
//      nKeyBufLen�������Կ��Ϣ����
//����: ���ع�����,ΪINT32,������������:
//          KError_Success,�ɹ�;
//          KError_IdentitySealError,ʧ��,δ���ҵ����;
//          KError_Other,ʧ��,��������;
//��ע: pIdentity�����ܼ���Ĺؼ�,�������Ӧ�ú������.
//      ��Ȼ,��ʹ������Ҫ��,Ҳ�������,���Ǳ����ܴ����.
//      Ӧ�ò�ֻ��Ҫ���������߼��趨pIdentity���򼴿�:
//          nIID������Ӧ���趨Ϊ��Ӧ���ŷ�����ID;
//          nPermissionӦ���趨ΪҪ�������޸ĵ��ŷ��е�Ȩ��.
//          ����ɾ���ŷ�Ĳ���,pIdentity����û����ݶ���,�������BuildFromNone����.
//          ��������/�޸��ŷ�Ĳ���,pIdentityҪ�������ݶ������й�Կ,�������BuildFromPublic����.
//          ��ȻpIdentity��Ҫ����ݶ������˽Կ��Ϣ,����Ȼ����BuildFromPrivate�������ݶ���Ҳ���й�Կ,��Ҳ����Ҫ��.
//
//      ����Լ����ļ�ִ����һ�������ش���,Ӧ����������������,����ʵ����д�ü����ļ��ļ�����Ϣ��.
//      ����Ըü����ļ�ִ�����ж������ɹ�,Ӧ���ʵ����д�ü����ļ��ļ�����Ϣ��.
//
//      ֮ǰ����CreateByFlow�����ɹ��ļ�����Ϣ��ο��ṹ��Ӧ��һ��������Ϣͷ.
//      ���������趨�����ŷ�,��Ȼ�����������Ϣ��ο��ṹ�е�����Ȩ�޼��ϱ仯.
//      ���ǿ��ǵ��ַ�����ֻ������Ӧ�ò���ֹ�����,���ҷַ�������ض���رռ�����Ϣ��ο��ṹ,
//      ��������������ڲ��������趨������Ϣ��ο��ṹ�е�����Ȩ�޼���,����Խ�ʡ�ޱ�Ҫ�ĺ�ʱ����.
///////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowModifyForSeal(
        JNIEnv* env,
        jobject /* this */,jint nflowid,jboolean bDelAdd,jint nIID,jlong nPermissionInfo,jbyteArray pKeyBuf,jint nKeyBufLen);

///////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowModifyForSign
//˵��: �޸�ָ��������Ϣ��ο��ṹ,Ҫ����Ϊ�ַ�������ǩ�����������趨
//���: nflowidָ����������id
//      bDelAdd��˵��Ĩȥ��������(�޸�)ǩ��;FALSEΪĨȥǩ��,TRUEΪ����(�޸�)ǩ��;
//      pDigest���ļ��������ݵ�ժҪ���˵��,ָ��16�ֽ����ݵ�ָ��
//����: ����ǩ�����,ΪINT32,������������:
//          KError_Success,�ɹ�;
//          KError_IdentitySealError,ʧ��,δ���ҵ����;
//          KError_Other,ʧ��,��������;
//��ע: ��bDelAddΪFALSE��ʾĨȥǩ��ʱ,pDigest����ΪNULL;
//      ��bDelAddΪTRUE��ʾ����(�޸�)ǩ��ʱ,pDigest���������ݲ���ΪNULL;
///////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowModifyForSign(
        JNIEnv* env,
        jobject /* this */,jint nflowid,jboolean bDelAdd,jbyteArray pDigestBuf,jint nDigestBufLen);

///////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowRecountSeal
//˵��: ���¸��ݵ�ǰ�û������е�������ݽ���������Ϣ��ο��ṹ�Եõ������õ�ǰ�û����յ�Ȩ��
//���: nflowidָ����������id
//����: �������¼�����,ΪINT32,������������:
//          KError_Success,�ɹ�;
//          KError_Other,ʧ��,��������;
//��ע: CreateByDefault �� CreateByFlow �����ļ�����Ϣ��ο��ṹ,��Ȩ���Ѿ���ȷ������.
//       ModifyForNew,ModifyForSign ���������ŷ�仯(Ҳ��Ȼ��������Ȩ�ޱ仯).
//
//       ModifyForSeal,TSKHelp_ModifyForWholeSeal �������ŷ�仯,���������������в�����������ȷ��������Ȩ�޽��.
//       ����,������漰���������ú�,��Ҫ�˽����յ�Ȩ�����,��Ҫ����RecountSeal��ͨ��������Ϣ��ṹ�е�nPermission���˽�.
//       ͨ��,Ӧ�ò�Ӧ�������漰�����������ú�(�ַ���������ӦShell�¼�)ʹ�ñ��ӿ�ȥ�ж��Ƿ��ŷ��������.
//       ����ͨ����Ҫ��֤һ���ļ�/�ļ��б��ַ���,��ǰ�û������پ����ض�Ȩ�޵�.
//       ���øýӿڷ��ش��������Ȼ���سɹ����Ǽ�����Ϣ��ṹ�е�nPermission�򲻾����ض�Ȩ��,Ӧ�ò㶼Ӧ��Ϊ�ַ�������.
///////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowRecountSeal(
        JNIEnv* env,
        jobject /* this */,jint nflowid);

///////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_DigestFlow
//˵��: ��������ժҪ
//���: nflowidΪָ����������id,������Чʱ�ò���������Ч
//      nOffset��ָ���������������е�ƫ��,��ʵ�ʽ���ժҪʱ,������Ч
//      nLength��ָ�������ĳ���,��ʵ�ʽ���ժҪʱ,������Ч
//      pFlow��ָ������,��ʵ�ʽ���ժҪʱ,������Ч
//      pCookie��ָ��������Ҫ��cookie
//����: ����json������ַ�����ʽ����ʽʾ������:
//     {nRet:0,cookie:1000,pMD5:"abcd"}
//     �����ĸ����̣�nRetΪ0������£���������������塣pMD5�Ǿ�base64���������ݣ��ⲿ�����
//��ע: ��TSK_DigestMD5�ķ�װ,�����˰��ռ�����Ϣ��ο��ṹ����ֻ�Լ��ܶ����ڵ�����ִ��ժҪ.
//      ���͵��÷�ʽ:
//      nflowid��0��nLength��pCookie��0��ʾ��ʼһ��ժҪ����,�����ⲿ�����õ�ժҪ����cookie
//      nflowid��ָ��id,pFlow��ΪNull,cookie���������践�ص�ֵ����ʾժҪ���̽�����
//      cookie���������践�ص�ֵ,pFlowΪNull����ʾժҪ���̽������������յ�ժҪ���
///////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jstring JNICALL
Java_io_edfs_tskandriodv2_TSKJni_DigestFlow(
        JNIEnv* env,
        jobject /* this */,jint nflowid,jlong nOffset,jint nLength,jbyteArray pFlow,jlong pCookie) ;

///////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowProcessFlow
//˵��: �������м��ܽ���
//���: nflowidΪָ��������id,����Ϊ֮ǰͨ��CreateByDefault(����),CreateByFlow�����ܣ���������id
//      nActionָ����������,֧��ACTION_ENCRYPT,ACTION_DECRYPT
//      nOffset��ָ���������������е�ƫ��
//      nLength��ָ�������ĳ���
//      pFlow��ָ������,����ΪNULL
//����: �����ر�����������
//��ע: ������Ϣ��ο��ṹ������Ч���Ѿ��⿪�����;
///////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jbyteArray JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowProcessFlow(
        JNIEnv* env,
        jobject /* this */,jint nflowid,jbyte nAction,
        jlong nOffset, jint nLength, jbyteArray pFlow);

///////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowFreeAFlow
//˵��: �ͷ�TSK�����(����)�ļ�����Ϣ��ο��ṹ
//���: nflowidΪָ��Ҫ�ͷŵ�������id
//����:
//��ע: �ⲿʹ����һ��������֮�󣬱�����øýӿ��ͷţ������ļ��ӽ��ܣ��������.
///////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowFreeAFlow(
        JNIEnv* env,
        jobject /* this */,jint nflowid);

///////////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowGetEFSLength
//˵��: ��ȡEFSʵ���С,��ID������ʽ
//���: nFlowID,Ŀ����ID
//��ע: һ����������Ҫд�ļ������У���ȡ��Ӧ������������֮������ݴ�С
//////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowGetEFSLength(
        JNIEnv* env,
        jobject /* this */,jint nflowid) ;

///////////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowGetFillLength
//˵��: ��ȡ������Ĵ�С
//���: nFlowID,Ŀ����ID
//��ע: һ����������Ҫд�ļ������У���ȡ��Ӧ��������EDFS�����ļ�����Ӧ������������ݴ�С
//////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowGetFillLength(
        JNIEnv* env,
        jobject /* this */,jint nflowid);

///////////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowSetFillLength
//˵��: ����������Ĵ�С
//���: nFlowID,Ŀ����ID
//��ע: �ⲿ������EFS�����Ӧ�������յĽ����̬�����������С������¼����Ӧ��EFS������
//////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jint JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowSetFillLength(
        JNIEnv* env,
        jobject /* this */,jint nflowid,jint nfilllength) ;

///////////////////////////////////////////////////////////////////////////////////////////////
//����: Java_io_edfs_tskandriodv2_TSKJni_FlowGetEFSFlow
//˵��: �õ�EFSʵ����
//���: nFlowID,Ŀ����ID
//��ע: ����EFS���������ɺ�����д�뵽�ļ�ʱ�������������л�ȡ����Ӧ��EFS���������������
//////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT jbyteArray JNICALL
Java_io_edfs_tskandriodv2_TSKJni_FlowGetEFSFlow(
        JNIEnv* env,
        jobject /* this */,jint nflowid);

