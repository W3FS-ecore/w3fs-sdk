package tsk

import (
	"encoding/base64"
	"fmt"
	"testing"
	"time"
)

func TestTsk(test *testing.T) {
	fmt.Println("TestTSK")
	TSK_Init()
	var struserid = "8ae765EB8Aebe6f0C07a6f33382bb02B73dD5d4b"
	fmt.Println("ID:", []byte(struserid))

	cip := make([]byte, 8192)
	ciplen := TSK_GetCipherDesc(cip, 8192)

	if ciplen < 8192 {
		cip = append(cip[:ciplen], cip[8192:]...)
		fmt.Println("TSK_GetCipherDesc", cip)
	}

	b64key := base64.StdEncoding.EncodeToString([]byte(struserid))
	byteKey := []byte(b64key)
	keylen := len(byteKey)

	var  pcookie uint64 = 0
	keysha256, res := TSK_DigestSha256(uint(keylen), byteKey, pcookie)
	fmt.Println("TSK_DigestSha256", keysha256, res)

	newpubkey, newprikey, pkeyid, res := TSK_IdentityIssueEx(keysha256)
	fmt.Println("TSK_IdentityIssueEx", newpubkey,newprikey, pkeyid, res)

	res = TSK_LoginUser(pkeyid)
	fmt.Println("TSK_LoginUser", res)


	prilen := len(newprikey)
	pubkey,res := TSK_IdentityGetPublicKeyByPrivateKey(newprikey, uint(prilen))
	fmt.Println("TSK_IdentityGetPublicKeyByPrivateKey", pubkey, res)

	publen := len(newpubkey)
	keyid, res := TSK_IdentityGetKeyIDByPublicKey(newpubkey, uint(publen),  20)
	fmt.Println("TSK_IdentityGetKeyIDByPublicKey", keyid, res)

	var nPermission int16 = -1
	prikeylen := len(newprikey)

	res = TSK_SetHoldIdentity(LIST_VERB_ADD, pkeyid, nPermission, newprikey, prikeylen)
	fmt.Println("TSK_SetHoldIdentity", res)

	res = TSK_SetHoldIdentity(LIST_VERB_DEFAULT, pkeyid, nPermission, newprikey, prikeylen)
	fmt.Println("TSK_SetHoldIdentity", res)

	tskid := TSK_FileOpTask_Init(1,2)
	fmt.Println("TSK_FileOpTask_Init", tskid)

	srcpath := "/home/xuzy/auth/a.txt"
	dstpath := "/home/xuzy/auth/b.txt"
	res = TSK_FileOpTask_PushAFileToTask(int(tskid), []byte(srcpath), []byte(dstpath))
	fmt.Println("TSK_FileOpTask_PushAFileToTask", res)

	res = TSK_FileOpTask_PushAAction(int(tskid), true, keyid, 0, 0, pubkey, publen)
	fmt.Println("TSK_FileOpTask_PushAAction", res)

	res = TSK_FileOpTask_SetShareSign(int(tskid), 0)
	fmt.Println("TSK_FileOpTask_SetShareSign", res)

	res = TSK_FileOpTask_StartATask(int(tskid))
	fmt.Println("TSK_FileOpTask_StartATask", res)

	time.Sleep(5 * time.Second)

	pReportBuf, reportlen , res := TSK_FileOpTask_GetATaskReport(int(tskid), 1, 1024)
	fmt.Println("TSK_FileOpTask_GetATaskReport", pReportBuf, reportlen, res)


	nState, nTotalLength, nCurrentLength, res := TSK_FileOpTask_GetATaskState(int(tskid))
	fmt.Println("TSK_FileOpTask_GetATaskState", nState, nTotalLength, nCurrentLength, res)


	res = TSK_FileOpTask_CancelATask(int(tskid))
	fmt.Println("TSK_FileOpTask_CancelATask", res)

	tskid = TSK_FileOpTask_Init(2,2)
	fmt.Println("TSK_FileOpTask_Init", tskid)

	res = TSK_FileOpTask_UnInitATask(int(tskid))
	fmt.Println("TSK_FileOpTask_UnInitATask", res)

	res = TSK_FileOpTask_CanExit()
	fmt.Println("TSK_FileOpTask_CanExit", res)

	rArr, arrlen, res := TSK_FileOp_GetESealInfo([]byte(dstpath), 8192)
	fmt.Println("TSK_FileOp_GetESealInfo", rArr,arrlen, res)

	res = TSK_LocalServer_Start(9999)
	fmt.Println("TSK_LocalServer_Start", res)
	time.Sleep(5 * time.Second)

	TSK_LocalServer_SetSystemTime(1655189092)
	fmt.Println("TSK_LocalServer_SetSystemTime")

	bRes := TSK_LocalServer_GetSessionKey(byteKey)
	fmt.Println("TSK_LocalServer_GetSessionKey", bRes)

	TSK_LocalServer_Stop()
	fmt.Println("TSK_LocalServer_Stop")

	TSK_LogoutUser()
	TSK_UnInit()
}