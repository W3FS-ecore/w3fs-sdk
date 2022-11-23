package tsk

// #cgo CFLAGS: -DPNG_DEBUG=1 -I./include
// #cgo LDFLAGS: -L./lib -lTSKLinux
// #include "TSKInterface_GO.h"
import "C"
import (
	"encoding/hex"
	"unsafe"
)

var IDENTITY_NULL_KEY = C.IDENTITY_NULL_KEY
var IDENTITY_PUBLIC_KEY = C.IDENTITY_PUBLIC_KEY
var IDENTITY_PRIVATE_KEY = C.IDENTITY_PRIVATE_KEY
var IDENTITY_KEY_ID = C.IDENTITY_KEY_ID

var CRYPT_NULL    = C.CRYPT_NULL
var CRYPT_PUBLIC_KEY = C.CRYPT_PUBLIC_KEY
var CRYPT_PRIVATE_KEY = C.CRYPT_PRIVATE_KEY

var ACTION_ENCRYPT =   C.ACTION_ENCRYPT
var ACTION_DECRYPT =  C.ACTION_DECRYPT

var LIST_VERB_DEFAULT = C.LIST_VERB_DEFAULT //1
var LIST_VERB_CLEAR = C.LIST_VERB_CLEAR     //2
var LIST_VERB_ADD = C.LIST_VERB_ADD         //3
var LIST_VERB_DELETE = C.LIST_VERB_DELETE   //4
var LIST_VERB_MODIFY = C.LIST_VERB_MODIFY   //5

func HexDecode(s string) []byte {
	dst := make([]byte, hex.DecodedLen(len(s)))
	n, err := hex.Decode(dst, []byte(s))
	if err != nil {
		return nil
	}
	return dst[:n]
}

func TSK_Init() int {
	res := C.TSK_GO_Init()
	return int(res)
}

func TSK_LoginUser(userid []byte) int {
	res := C.TSK_GO_LoginUser((*C.uchar)(unsafe.Pointer(&userid)))
	return int(res)
}

func TSK_LogoutUser() int {
	res := C.TSK_GO_LogoutUser()
	return int(res)
}

func TSK_DigestSha256(priAddresslen uint, bytePriAddress []byte, pCookie uint64) ([]byte, int) {
	priSha256 := make([]byte, C.DIGEST_SHA256_LENGTH)
	res := C.TSK_GO_DigestSha256(*(*C.uint)(unsafe.Pointer(&priAddresslen)), (*C.uchar)(unsafe.Pointer(&bytePriAddress[0])), (*C.uint64_t)(unsafe.Pointer(&pCookie)), (*C.uchar)(unsafe.Pointer(&priSha256[0])))
	return priSha256,  int(res)
}

func TSK_DigestCRC32(nFlowLen uint, pFlow []byte, pCookie uint64) (uint, int) {
	var pCRC32 uint
	res := C.TSK_GO_DigestCRC32(*(*C.uint)(unsafe.Pointer(&nFlowLen)), (*C.uchar)(unsafe.Pointer(&pFlow[0])), (*C.uint64_t)(unsafe.Pointer(&pCookie)), (*C.uint)(unsafe.Pointer(&pCRC32)))
	return pCRC32, int(res)
}

func TSK_DigestMD5(nFlowLen uint, pFlow []byte, pCookie uint64) ([]byte, int) {
	pMD5 := make([]byte, C.DIGEST_SHA256_LENGTH)
	res := C.TSK_GO_DigestMD5(*(*C.uint)(unsafe.Pointer(&nFlowLen)), (*C.uchar)(unsafe.Pointer(&pFlow[0])), (*C.uint64_t)(unsafe.Pointer(&pCookie)), (*C.uchar)(unsafe.Pointer(&pMD5[0])))
	return pMD5,  int(res)
}

func TSK_IdentityIssueEx(pSeed []byte) ([]byte, []byte, []byte, int) {

	var pubkeylen C.UINT32
	var prikeylen C.UINT32
	pubkeylen = 200
	prikeylen = 200

	pubkey := make([]byte, 200)
	prikey := make([]byte, 200)
	pkeyid := make([]byte, 20)

	res := C.TSK_GO_IdentityIssueEx((*C.uchar)(unsafe.Pointer(&pSeed[0])), C.DIGEST_SHA256_LENGTH,
		(*C.uchar)(unsafe.Pointer(&pubkey[0])), &pubkeylen, (*C.uchar)(unsafe.Pointer(&prikey[0])), &prikeylen,
		(*C.uchar)(unsafe.Pointer(&pkeyid[0])))
	ipublen := C.int(pubkeylen)
	iprilen := C.int(prikeylen)

	newpubkey := append(pubkey[:ipublen], pubkey[200:]...)
	newprikey := append(prikey[:iprilen], prikey[200:]...)

	return newpubkey, newprikey, pkeyid,  int(res)
}

func TSK_SetHoldIdentity(nListVerb int, nIdentityID []byte, nPermission int16, pKeyBuf []byte, nKeyLen int) int {
	cListVerb := (*C.UINT32)(unsafe.Pointer(&nListVerb))
	res := C.TSK_GO_SetHoldIdentity(*cListVerb, (*C.uchar)(unsafe.Pointer(&nIdentityID[0])), *(*C.UINT16)(unsafe.Pointer(&nPermission)), -1, (*C.uchar)(unsafe.Pointer(&pKeyBuf[0])), *(*C.int)(unsafe.Pointer(&nKeyLen)))
	return  int(res)
}

func TSK_IdentityGetPublicKeyByPrivateKey(pPrivateKeyBuf []byte, nFlowLen uint) ([]byte, int) {
	var pubkeylen C.UINT32
	pubkeylen = 200
	pubkey := make([]byte, 200)
	res := C.TSK_GO_IdentityGetPublicKeyByPrivateKey((*C.uchar)(unsafe.Pointer(&pPrivateKeyBuf[0])), *(*C.uint)(unsafe.Pointer(&nFlowLen)), (*C.uchar)(unsafe.Pointer(&pubkey[0])), &pubkeylen )

	if res == 0 {
		ipublen := C.int(pubkeylen)
		pubkey = append(pubkey[:ipublen], pubkey[200:]...)
	}
	return  pubkey,  int(res)
}

func TSK_IdentityGetKeyIDByPublicKey(pPublicKeyBuf []byte, nFlowLen uint, nkeyidlen uint) ([]byte, int){
	var keylen C.UINT32
	pkeyid := make([]byte, nkeyidlen)
	res := C.TSK_GO_IdentityGetKeyIDByPublicKey((*C.uchar)(unsafe.Pointer(&pPublicKeyBuf[0])), *(*C.uint)(unsafe.Pointer(&nFlowLen)), (*C.uchar)(unsafe.Pointer(&pkeyid[0])), &keylen);

	if res == 0 {
		ikeylen := C.int(keylen)
		pkeyid = append(pkeyid[:ikeylen], pkeyid[nkeyidlen:]...)
	}

	return pkeyid,  int(res)
}

func TSK_FileOp_AdjustByFlow(headSrc []byte, srcLen int,bDelAdd bool, userid []byte, nPermission int16, lasttime int, pubkey []byte, pubkeylen int) ([]byte, C.int, int) {
	var dstLen C.int
	dstHead := make([]byte, srcLen+1024)
	clasttime := C.int(lasttime)
	cpubkeylen := C.int(pubkeylen)
	csrclen := C.int(srcLen)
	dstLen = csrclen + 1024
	res := C.TSK_Go_FileOp_AdjustByFlow((*C.uchar)(unsafe.Pointer(&headSrc[0])),
		csrclen, (*C.uchar)(unsafe.Pointer(&dstHead[0])), &dstLen, *(*C.bool)(unsafe.Pointer(&bDelAdd)) ,
		(*C.uchar)(unsafe.Pointer(&userid[0])), *(*C.UINT16)(unsafe.Pointer(&nPermission)), clasttime, (*C.uchar)(unsafe.Pointer(&pubkey[0])), cpubkeylen)
	dstHead = dstHead[:dstLen]
	return dstHead, dstLen,  int(res)
}

func TSK_GetCipherDesc(pSrcFlow []byte, nDescBufLen int) int {
	res := C.TSK_GO_GetCipherDesc((*C.uchar)(unsafe.Pointer(&pSrcFlow[0])), *(*C.int)(unsafe.Pointer(&nDescBufLen)))
	return int(res)
}

func TSK_GetCipherInfo(tagCipher []byte, pKeyLength int16, pBlockSize int16 ) int {
	res := C.TSK_GO_GetCipherInfo((*C.uchar)(unsafe.Pointer(&tagCipher[0])), (*C.UINT16)(unsafe.Pointer(&pKeyLength)), (*C.UINT16)(unsafe.Pointer(&pBlockSize)));
	return  int(res)
}

func TSK_SetDefaultCipher(tagCipher []byte) int {
	res := C.TSK_GO_SetDefaultCipher((*C.uchar)(unsafe.Pointer(&tagCipher[0])));
	return  int(res)
}

func TSK_SetDefaultZone(nLen int64) int {
	res := C.TSK_GO_SetDefaultZone(*(*C.int64_t)(unsafe.Pointer(&nLen)));
	return int(res)
}

func TSK_CreateCipherCell(tagCipher []byte, nKeyLen int16,  pKey []byte) int {
	res := C.TSK_GO_CreateCipherCell((*C.uchar)(unsafe.Pointer(&tagCipher[0])),*(*C.UINT16)(unsafe.Pointer(&nKeyLen)), (*C.uchar)(unsafe.Pointer(&pKey[0])))
	return   int(res)
}

func TSK_DeleteCipherCell(nCipherCell int) int {
	res := C.TSK_GO_DeleteCipherCell(*(*C.int)(unsafe.Pointer(&nCipherCell)))
	return   int(res)
}

func TSK_ProcessCipherCell(nCipherCell int, nAction int, nOffset int64, nLength uint) ([]byte, int) {
	pFlow := make([]byte, nLength)
	cAction := (*C.uchar)(unsafe.Pointer(&nAction))
	res := C.TSK_GO_ProcessCipherCell(*(*C.int)(unsafe.Pointer(&nCipherCell)), *cAction, *(*C.int64_t)(unsafe.Pointer(&nOffset)), *(*C.uint)(unsafe.Pointer(&nLength)), (*C.uchar)(unsafe.Pointer(&pFlow[0])))
	return  pFlow,  int(res)
}

func TSK_FileOpTask_Init(nAction int, nThreadCount int) int {
	res := C.TSK_GO_FileOpTask_Init(*(*C.int)(unsafe.Pointer(&nAction)), *(*C.int)(unsafe.Pointer(&nThreadCount)))
	return   int(res)
}

func TSK_FileOpTask_PushAFileToTask(nTaskID int, pSrcFilePath []byte, pDstFilePath []byte) int {
	res := C.TSK_GO_FileOpTask_PushAFileToTask(*(*C.int)(unsafe.Pointer(&nTaskID)), (*C.char)(unsafe.Pointer(&pSrcFilePath[0])), (*C.char)(unsafe.Pointer(&pDstFilePath[0])))
	return   int(res)
}

func TSK_FileOpTask_PushAAction(nTaskID int, bDelAdd bool,IID []byte, nPermission int16, nLastTime int, pKeyBuf []byte, nKeyBufLen int) int {
	res := C.TSK_GO_FileOpTask_PushAAction(*(*C.int)(unsafe.Pointer(&nTaskID)) , *(*C.bool)(unsafe.Pointer(&bDelAdd)) , (*C.uchar)(unsafe.Pointer(&IID[0])) , *(*C.UINT16)(unsafe.Pointer(&nPermission)) , *(*C.int)(unsafe.Pointer(&nLastTime))  , (*C.uchar)(unsafe.Pointer(&pKeyBuf[0]))  ,  *(*C.int)(unsafe.Pointer(&nKeyBufLen)));
	return   int(res)
}


func TSK_FileOpTask_SetShareSign(nTaskID int, nSignAction int ) int {
	cSignAction := (*C.uchar)(unsafe.Pointer(&nSignAction))
	res := C.TSK_GO_FileOpTask_SetShareSign(*(*C.int)(unsafe.Pointer(&nTaskID)) , *cSignAction);
	return   int(res)
}

func TSK_FileOpTask_StartATask(nTaskID int) int {
	res := C.TSK_GO_FileOpTask_StartATask(*(*C.int)(unsafe.Pointer(&nTaskID)));
	return   int(res)
}

func TSK_FileOpTask_CancelATask(nTaskID int) int {
	res := C.TSK_GO_FileOpTask_CancelATask(*(*C.int)(unsafe.Pointer(&nTaskID)));
	return   int(res)
}

func TSK_FileOpTask_UnInitATask(nTaskID int) int {
	res := C.TSK_GO_FileOpTask_UnInitATask(*(*C.int)(unsafe.Pointer(&nTaskID)));
	return   int(res)
}

func TSK_FileOpTask_GetATaskState(nTaskID int) (int, int64, int64, int) {
	var nState int
	var nTotalLength int64
	var nCurrentLength int64
	res := C.TSK_GO_FileOpTask_GetATaskState(*(*C.int)(unsafe.Pointer(&nTaskID)), (*C.int)(unsafe.Pointer(&nState)),(*C.int64_t)(unsafe.Pointer(&nTotalLength)),(*C.int64_t)(unsafe.Pointer(&nCurrentLength)) )
	return nState, nTotalLength, nCurrentLength,  int(res)
}

func TSK_FileOpTask_GetATaskReport(nTaskID int,nReportMode int,reportLen int) ([]byte, int, int) {
	var nReportBufLength C.int
	pReportBuf := make([]byte, reportLen)
	nReportBufLength = C.int(reportLen)
	res := C.TSK_GO_FileOpTask_GetATaskReport(*(*C.int)(unsafe.Pointer(&nTaskID)), *(*C.int)(unsafe.Pointer(&nReportMode)), (*C.uchar)(unsafe.Pointer(&pReportBuf[0])) , &nReportBufLength)
	return pReportBuf , int(nReportBufLength) ,  int(res)
}

func TSK_FileOpTask_CanExit() int {
	res := C.TSK_GO_FileOpTask_CanExit()
	return  int(res)
}

func TSK_FileOp_GetESealInfo(strFilePath []byte,arrlen int) ([]byte, int, int) {
	var nArrayLength C.int
	pIdentityIDArray := make([]byte, arrlen)
	nArrayLength = C.int(arrlen)
	res := C.TSK_GO_FileOp_GetESealInfo((*C.char)(unsafe.Pointer(&strFilePath[0])), (*C.uchar)(unsafe.Pointer(&pIdentityIDArray[0])), &nArrayLength)
	return pIdentityIDArray, int(nArrayLength),  int(res)
}

func TSK_LocalServer_Start(port int) int {
	res := C.TSK_GO_LocalServer_Start(*(*C.int)(unsafe.Pointer(&port)))
	return  int(res)
}

func TSK_LocalServer_Stop() {
	C.TSK_GO_LocalServer_Stop()
}

func TSK_LocalServer_SetSystemTime(nTime int) {
	C.TSK_GO_LocalServer_SetSystemTime(*(*C.int)(unsafe.Pointer(&nTime)))
}

func TSK_LocalServer_GetSessionKey(pSessionKey []byte) bool {
	res := C.TSK_GO_LocalServer_GetSessionKey((*C.char)(unsafe.Pointer(&pSessionKey[0])))
	return bool(res)
}

func TSK_UnInit() {
	C.TSK_GO_UnInit()
}
