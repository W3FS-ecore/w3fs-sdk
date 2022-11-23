//
//  TSKSDK.h
//  TSKCrypto
//
//  Created by Jero on 2021/10/29.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Identity issuance
/// @param PubKey Public key
/// @param PubKeyLen Public key length
/// @param PrivateKey private key
/// @param PrivateKeyLen private key length
/// @param KeyID User ID
typedef void(^ _Nullable identityIssueBlock)(NSData *PubKey, NSInteger PubKeyLen,NSData *PrivateKey, NSInteger PrivateKeyLen, NSString *KeyID);

/// Summary callback
/// @param result The data returned
/// @param cookie The cookie needed for the iteration
/// @param code The final result of the iteration summary
typedef void(^ _Nullable digestBlock)(NSData * _Nullable result, NSInteger cookie,NSInteger code);

typedef NS_ENUM(int, TSKResult) {
    TSKResultSuccess = 0,             // success
    TSKResultNoDataHandled = 1,       // version not supported
    TSKResultCreateObject = 10,       // Success, create new object
    TSKResultOpenObject = 11,         // Success, open the object
    TSKResultOverrideObject = 12,     // Success, open the object and override the object
    TSKResultLengthError = -1,        // failure, length error
    TSKResultTimeOut = -2,            // Failure, timeout
    TSKResultOutOfLength = -3,        // failed, insufficient buffer length
    TSKResultCantConnectKernel = -10, // Failed, cannot connect to kernel
    TSKResultFileServing = -11,       // Failed, there is currently a file being served
    TSKResultMultiUser = -20,         // Failed, multiple login users
    TSKResultNoUser = -21,            // Failed, no logged in users
    TSKResultSyntaxError = -30,       // Failed, syntax error
    TSKResultCantFindObject = -31,    // Failed, the specified object could not be found
    TSKResultMultiObject = -32,       // Failed, multiple objects specified
    TSKResultMaybeFindObject = -33,   // Failed, cannot find the specified object at the moment (cannot be sure to find the specified object at the moment)
    TSKResultCommonLogic = -34,       // Failed, common logic error
    TSKResultCipherError = -40,       // failure, encryption algorithm error (usually no encryption algorithm)
    TSKResultCipherInnerError = -41,  // Failure, internal error in encryption algorithm
    TSKResultPermissionDenied = -42,  // Failed, insufficient permission
    TSKResultHeaderCrcError = -50,    // Failed, failed to process encryption header structure, CRC error
    TSKResultIdentitySealError = -51, // Failed, failed to process identity envelope
    TSKResultOther = -100             // failure, other error (usually a memory allocation error)
};

typedef NS_ENUM(unsigned short, PermissionType) {
    PermissionNone = 0,    // can't decrypt and can't distribute
    PermissionOnlyDecpypt, // decryptable but not distributable
    PermissionOnlyAdjust,  // can't be decrypted but can be distributed
    PermissionBoth         // decryptable and distributable
};

typedef NS_ENUM(NSInteger, ListVerbType) {
    ListVerbDefault = 1, // set the default default behavior
    ListVerbClear,       // clear the list of matches
    ListVerbAdd,         // add a match
    ListVerbDelete       // Delete the matches
};

typedef NS_ENUM(NSInteger, FileOperateType) {
    FileOperateEncrypt = 1, // encrypt operation
    FileOperateDecrypt,     // decrypt operation
    FileOperateShare        // Distribute operation
};

typedef NS_ENUM(BOOL, identityOperateType) {
    identityOperateAdd = YES,  // add identity
    identityOperateDelete = NO // Delete identity
};

typedef NS_ENUM(NSInteger, FileSignType) {
    FileSignKeep = 0, // keep signature information
    FileSignSet,      // set the signature information
    FileSignClear     // Clear the signature information
};

typedef NS_ENUM(NSInteger, FileReportType) {
    FileReportLite = 1, // minimalist mode
    FileReportFull      // full mode
};

typedef NS_ENUM(NSInteger, FileTaskState) {
    FileTaskReady = 0,      // to be started
    FileTaskEstimateLength, // data processing in progress (estimating data length phase)
    FileTaskProcessingData, // data processing in progress (processing data phase)
    FileTaskSuccessed,      // data processing completed (all data processed successfully)
    FileTaskCancelled       // data processing completed (externally initiated cancellation)
};

typedef NS_ENUM(NSInteger, FileTaskReportState) {
    FileTaskReportDataFailed = -6,  // key area checksum error
    FileTaskReportVersionFailed,    // version not supported
    FileTaskReportPermissionFailed, // Permission verification failed
    FileTaskReportTSKFailed,        // TSK library return failed
    FileTaskReportFileCantServices, // Unable to serve the file
    FileTaskReportIgnore,           // Ignored
    FileTaskReportSuccess           // Success
};


@interface CipherDescModel : NSObject

@property (nonatomic , strong) NSData *tag;  // encryption algorithm identifier
@property (nonatomic , copy) NSString *name; // the name of the encryption algorithm
@property (nonatomic , copy) NSString *desc; // algorithm description information

@end

@interface CipherInfoModel : NSObject

@property (nonatomic , assign) NSInteger keyLength; // the length of the secret key required by the algorithm (byte calculation)
@property (nonatomic , assign) NSInteger blockSize; // the group size required by the algorithm (byte calculation)

@end

@interface FileTaskStateModel : NSObject

@property (nonatomic , assign) FileTaskState taskState; // state
@property (nonatomic , assign) NSInteger totalLength;   // total length of data to be processed (in bytes)
@property (nonatomic , assign) NSInteger currentLength; // length of currently processed data (in bytes)

@end

@interface FileTaskReportStateModel : NSObject

@property (nonatomic , assign) FileOperateType operateType;     // file operation type
@property (nonatomic , assign) FileTaskReportState reportState; // the result of the file operation
@property (nonatomic , copy) NSString *srcPath; // source file full path information
@property (nonatomic , copy) NSString *dstPath; // full path information for the target file

@end

@interface FileTaskReportModel : NSObject

@property (nonatomic , assign) NSInteger totalCount;   // total number of files
@property (nonatomic , assign) NSInteger totalSuccess; // number of files that succeeded
@property (nonatomic , assign) NSInteger totalFailed;  // number of failed files
@property (nonatomic , assign) NSInteger totalIgnore;  // number of files ignored
@property (nonatomic , copy, nullable) NSArray<FileTaskReportStateModel *>* reportStates; // detailed report for each file

@end

@interface TSKSDK : NSObject

// MARK: - SDK single instance initialization
+ (instancetype) share;
+ (instancetype) new  UNAVAILABLE_ATTRIBUTE;
- (instancetype) init UNAVAILABLE_ATTRIBUTE;

// MARK: - TSK Library Operations

/// Initialization
///
/// @return Processing results
/// TSKResultSuccess success
/// TSKResultCantConnectKernel, failed, unable to connect to the TSK file system kernel (only valid for Native ///dapp development).
/// TSKResultOther, failed, other errors;
- (TSKResult)TSKInit;

/// Reverse initialization
///
/// Reverse initialization of TSK-SDK Native library
/// Dapp needs to call the TSK_UnInit interface to complete the reverse initialization of the TSK Native SDK library when the program exits, so that the TSK Native SDK library can clean up and release all occupied system resources.
- (void)TSKUnInit;

/// Generate seed information
/// The returned seed information will be used for user registration
///
/// @param seedString The string used to generate the seed information
/// @return seed information.It will be nil when error occurs
- (nullable NSData *)makeSeed:(NSString *)seedString;

/// User Registration
/// Generate (issue) an identity object. based on seed information
///
/// @param seedData The seed information of the specified identity key information
/// @param block Result callback
/// @return Processing result
/// TSKResultSuccess, success
/// TSKResultOther, failed, other errors
- (TSKResult)identityIssue:(NSData *)seedData block:(identityIssueBlock)block;

/// User Login
/// You must be logged in before using the SDK encryption and decryption methods
///
/// @param KeyID the corresponding internal ID representing the unique identity of the user
/// @return Processing result
/// TSKResultSuccess, success;
/// TSKResultMultiUser, failed, there are other login users;
/// TSKResultOther, other errors, usually memory allocation errors (or insufficient buffers);
- (TSKResult)loginUser:(NSString *)KeyID;

/// User logout
/// If you need to switch users or not use the SDK, you need to log out the current user
///
/// @return processing result
/// TSKResultSuccess, success;
- (TSKResult)logoutUser;

/// CRC32 digest algorithm
/// Iterative support for CRC32 digests of multiple streams
///
/// @param data Specifies the stream to compute the CRC32 digest
/// @param cookie Specifies the cookie needed for the iteration
/// @param block Result callback
/// @return processing result
/// TSKResultSuccess, success
/// TSKResultOther, failed, other errors
///
/// Usage: 1. Start summary, get cookie
/// __block NSInteger crc32Cookie;
/// TSKResult result = [[TSKSDK share] digestCRC32:nil cookie:0 block:^(NSData * _Nullable result, NSInteger cookie, NSInteger code) {
/// crc32Cookie = cookie;
/// }];
/// 2. Perform the digest. The incoming cookie is fetched from the first step. If there are multiple streams, repeat the call
/// NSData *data = [@"test" dataUsingEncoding:NSUTF8StringEncoding];
/// result = [[TSKSDK share] digestCRC32:data cookie:crc32Cookie block:nil];
/// 3. End summary. The incoming cookie is obtained from the first step. crc32Code is the digest result
/// __block NSInteger crc32Code;
/// TSKResult result = [[TSKSDK share] digestCRC32:nil cookie:crc32Cookie block:^(NSData * _Nullable result, NSInteger cookie, NSInteger code) {
///    crc32Code = code;
/// }];
- (TSKResult)digestCRC32:(nullable NSData *)data cookie:(NSInteger)cookie block:(digestBlock)block;

/// Single CRC32 digest algorithm
///
/// @param data Specify the stream to calculate the CRC32 digest
/// @param block Result callback
/// @return processing result
/// TSKResultSuccess, success
/// TSKResultOther, failed, other errors
///
/// Usage: Call the method, crc32Code is the summary result
/// NSData *data = [@"test" dataUsingEncoding:NSUTF8StringEncoding];
/// __block NSInteger crc32Code;
/// TSKResult result = [[TSKSDK share] singleDigestCRC32:data block:^(NSData * _Nullable result, NSInteger cookie, NSInteger code) {
///     crc32Code = code;
/// }];
- (TSKResult)singleDigestCRC32:(nonnull NSData *)data block:(digestBlock)block;

/// MD5 digest algorithm
/// Iterative support for MD5 algorithm digests over multiple streams
///
/// @param data Specifies the stream to compute the MD5 digest
/// @param cookie Specifies the cookie needed for the iteration
/// @param block Result callback
/// @return Processing result
/// TSKResultSuccess, success
/// TSKResultOther, failed, other errors
///
/// Usage: 1. Start digest, get cookie
/// __block NSInteger md5Cookie;
/// TSKResult result = [[TSKSDK share] digestMD5:nil cookie:0 block:^(NSData * _Nullable result, NSInteger cookie, NSInteger code) {
/// md5Cookie = cookie;
/// }];
/// 2. Perform the digest. The incoming cookie is fetched from the first step. If there are multiple streams, repeat the call
/// NSData *data = [@"test" dataUsingEncoding:NSUTF8StringEncoding];
/// result = [[TSKSDK share] digestMD5:data cookie:md5Cookie block:nil];
/// 3. End summary. The incoming cookie is obtained from the first step. md5Data is the digest result
/// __block NSData md5Data;
/// TSKResult result = [[TSKSDK share] digestMD5:nil cookie:md5Cookie block:^(NSData * _Nullable result, NSInteger cookie, NSInteger code) {
///    md5Data = result;
/// }];
- (TSKResult)digestMD5:(nullable NSData *)data cookie:(NSInteger)cookie block:(digestBlock)block;

/// Single MD5 digest algorithm
///
/// @param data Specify the stream to calculate the MD5 digest
/// @param block Result callback
/// @return processing result
/// TSKResultSuccess, success
/// TSKResultOther, failed, other errors
///
/// Usage: Call the method, md5Data is the summary result
/// NSData *data = [@"test" dataUsingEncoding:NSUTF8StringEncoding];
/// __block NSData md5Data;
/// TSKResult result = [[TSKSDK share] singleDigestMD5:data block:^(NSData * _Nullable result, NSInteger cookie, NSInteger code) {
///     md5Data = result;
/// }];
- (TSKResult)singleDigestMD5:(nonnull NSData *)data block:(digestBlock)block;

/// Sha256 digest algorithm
/// Iterative support for SHA256 algorithm digests over multiple streams
///
/// @param data Specifies the stream to compute the Sha256 digest
/// @param cookie Specifies the cookie needed for the iteration
/// @param block Result callback
/// @return Processing results
/// TSKResultSuccess, success
/// TSKResultOther, failed, other errors
///
/// Usage: 1. Start digest, get cookie
/// __block NSInteger sha256Cookie;
/// TSKResult result = [[TSKSDK share] digestSha256:nil cookie:0 block:^(NSData * _Nullable result, NSInteger cookie, NSInteger code) {
/// sha256Cookie = cookie;
/// }];
/// 2. Perform the digest. The incoming cookie is fetched from the first step. If there are multiple streams, repeat the call
/// NSData *data = [@"test" dataUsingEncoding:NSUTF8StringEncoding];
/// result = [[TSKSDK share] digestSha256:data cookie:sha256Cookie block:nil];
/// 3. End summary. The incoming cookie is obtained from the first step. sha256Data is the digest result
/// __block NSData sha256Data;
/// TSKResult result = [[TSKSDK share] digestSha256:nil cookie:sha256Cookie block:^(NSData * _Nullable result, NSInteger cookie, NSInteger code) {
///    sha256Data = result;
/// }];
- (TSKResult)digestSha256:(nullable NSData *)data cookie:(NSInteger)cookie block:(digestBlock)block;

/// Single Sha256 digest algorithm
///
/// @param data Specify the stream to calculate the Sha256 digest
/// @param block Result callback
/// @return Processing result
/// TSKResultSuccess, success
/// TSKResultOther, failed, other errors
///
/// Usage: Call the method, sha256Data is the summary result
/// NSData *data = [@"test" dataUsingEncoding:NSUTF8StringEncoding];
/// __block NSData sha256Data;
/// TSKResult result = [[TSKSDK share] singleDigestMD5:data block:^(NSData * _Nullable result, NSInteger cookie, NSInteger code) {
///     sha256Data = result;
/// }];
- (TSKResult)singleDigestSha256:(nonnull NSData *)data block:(digestBlock)block;

/// Get the description of all currently loaded algorithms
///
/// @return Description of the algorithm
- (nonnull NSArray<CipherDescModel *>*)GetCipherDesc;

/// Get the specified algorithm description
///
/// @param cipherTag The identifier of the algorithm to be queried, for the tag variable of the CipherDescModel
/// @return Information about the specified algorithm.It will be nil when error occurs
- (nullable CipherInfoModel *)GetCipherInfo:(nonnull NSData *)cipherTag;

/// Set the default symmetric encryption algorithm
/// Subsequent encryption and decryption will be performed using the set algorithm
/// Non-essential function, if the method is not called, the default algorithm will be used for encryption and decryption
///
/// @param cipherTag The identifier of the algorithm to be set, which is the tag variable of the CipherDescModel
/// @return the result of processing
/// TSKResultSuccess, success
/// TSKResultCipherError, failed, the algorithm could not be found;
/// TSKResultOther, other errors, usually memory allocation errors (or insufficient buffers);
- (TSKResult)setDefaultCipher:(nonnull NSData *)cipherTag;

/// Set TSK file encryption paragraph encryption information
/// The default encrypted paragraphs are fixed from the file header to the specified size of the file paragraphs.
/// The paragraph size is 0, which is effectively the same as unencrypted; the paragraph size is -1, which is effectively the same as encrypting the entire file.
/// Non-essential function, if this method is not called, the default length is used for encryption and decryption.
///
/// @param zone The size (byte count) of the default encrypted paragraph to set
/// @return the result of processing
/// TSKResultSuccess, success
/// TSKResultOther, other errors, usually memory allocation errors (or insufficient buffers);
- (TSKResult)setDefaultZone:(NSInteger)zone;

/// Set the identity held by the current user of the library store
///
/// @param type Operation type
/// @param KeyID User ID
/// @param permission Permissions
/// @param lastTime File usage period
/// @param privateKey private key
/// @param privateKeyLength private key length
/// @return Processing result
/// TSKResultSuccess, success
/// TSKResultNoUser, failed, there is no currently logged in user;
/// TSKResultSyntaxError, failure, syntax error (such as unsupported verb, etc.);
/// TSKResultMultiObject, failure, semantic error, the Key already exists (the identity ID already exists);
/// TSKResultCantFindObject, failure, semantic error, delete the key that does not exist (the identity ID does not exist);
/// TSKResultOther, other errors, usually memory allocation errors (or insufficient buffers);
///
/// Usage: set current identity (own permission to decrypt and distribute, unlimited file lifetime)
/// TSKResult result = [[TSKSDK share] setHoldIdentity:ListVerbAdd KeyID:address permission:PermissionBoth lastTime:-1 privateKey:priKey privateKeyLength:priKeyLen];
/// Set the current identity as the default identity
/// result = [[TSKSDK share] setHoldIdentity:ListVerbDefault KeyID:address permission:PermissionNone lastTime:0 privateKey:nil privateKeyLength:0];
/// Clear all identities
/// result = [[TSKSDK share] setHoldIdentity:ListVerbClear KeyID:@"" permission:PermissionNone lastTime:0 privateKey:nil privateKeyLength:0];
- (TSKResult)setHoldIdentity:(ListVerbType)type KeyID:(NSString *)KeyID permission:(PermissionType)permission lastTime:(NSInteger)lastTime privateKey:(nullable NSData *)privateKey privateKeyLength:(NSInteger)privateKeyLength;

/// Initialize a file manipulation task
/// All subsequent operations and control of file manipulation tasks are performed by the returned task ID
///
/// @param type The type of operation
/// @param threadCount The maximum number of threads recommended to balance performance and user experience is (cpu cores/2+1)
/// @return Less than 0 indicates that the initialization of the file operation task failed, and no subsequent operations are required. Greater than or equal to 0 indicates that the initialization was successful, and the task ID corresponding to the file operation task is returned. All subsequent operations and control of the file operation task are performed through the task ID.
- (NSInteger)fileOperateInit:(FileOperateType)type threadCount:(NSInteger)threadCount;

/// Add a full path of the file/folder to be manipulated to the specified file manipulation task
/// Can be called multiple times to work on multiple files/folders at the same time during a single file operation task
/// Only valid before the operation task is started, after the operation task is started, it cannot be added again
/// The source file and the target file must be different paths, and the source file must be real.
///
/// @param taskID file operation task ID
/// @param fromPath Source file path
/// @param toPath Target file path
/// @return result
/// TSKResultSuccess, success
/// Others are failures
- (TSKResult)addFileToTask:(NSInteger)taskID fromPath:(NSString *)fromPath toPath:(nullable NSString *)toPath;

/// Add a pending identity item action to the specified file operation task
/// This method is only valid for file distribution
/// Can be called multiple times to complete the distribution operation in the order it is called
///
/// @param taskID File operation task ID
/// @param type identity operation type
/// @param KeyID User ID
/// @param permission Permission
/// @param lastTime File usage period
/// @param pubKey public key
/// @param pubKeyLength public key length
/// @return Processing result
/// TSKResultSuccess, success
/// Others are failures
- (TSKResult)addActionToTask:(NSInteger)taskID type:(identityOperateType)type KeyID:(NSString *)KeyID permission:(PermissionType)permission lastTime:(NSInteger)lastTime pubKey:(nullable NSData *)pubKey pubKeyLength:(NSInteger)pubKeyLength;

/// Set file operation task signature action
/// This method is only valid for document distribution
///
/// @param taskID File operation task ID
/// @param type Signature action information
/// @return Processing result
/// TSKResultSuccess, success
/// Others are failures
- (TSKResult)setShareSign:(NSInteger)taskID type:(FileSignType)type;

/// Open file manipulation task
/// After the file operation task is started, the Set Parameters interface cannot be called again to modify the properties of the file operation task
///
/// @param taskID File operation task ID
/// @return Processing result
/// TSKResultSuccess, success
/// Others are failures
- (TSKResult)startFileTask:(NSInteger)taskID;

/// Aborting file manipulation tasks
/// The file operation task is an asynchronous multi-threaded operation, the return value only returns whether the interface call is successful, the final result of the task cancellation to obtain the file operation task status interface call results shall prevail
/// After the file operation task is canceled, it cannot be opened again, and the delete file operation task interface should be called subsequently
/// The file operation task is cancelled, the file status of the completed operation will not be rolled back
///
/// @param taskID File operation task ID
/// @return processing result
/// TSKResultSuccess, success
/// Others are failures
- (TSKResult)cancelFileTask:(NSInteger)taskID;

/// Delete file operation task
/// After a file operation task is completed, regardless of the result, this method should be called to release the various system resources occupied by the file operation task
/// A task whose status is predicted and in progress is not allowed to be deleted, and must wait for completion, or be actively canceled before being allowed to be deleted
///
/// @param taskID File operation task ID
/// @return Processing result
/// TSKResultSuccess, success
/// Others are failures
- (TSKResult)fileOperateUnInit:(NSInteger)taskID;

/// Get the status of a file operation task
/// The task state success does not mean the file processing is successful, the file processing result should be called to get the file operation task result report to get
/// The returned task state taskState is FileTaskReady to be started, totalLength,currentLength data is invalid
/// FileTaskEstimateLength data processing in progress (estimated data length stage), totalLength,currentLength data is invalid
/// FileTaskProcessingData Data processing in progress (processing data phase), can use totalLength,currentLength to convert the percentage, or directly display the data length
/// FileTaskSuccessed Data processing completed (all data processed successfully), totalLength,currentLength data invalid
/// FileTaskCancelled data processing completed (external initiative to cancel), totalLength,currentLength data invalid
///
/// @param taskID File operation task ID
/// @return Task status information.It will be nil when error occurs
- (nullable FileTaskStateModel *)getFileTaskState:(NSInteger)taskID;

/// Get a report on the final results of the document manipulation task
///
/// @param taskID File operation task ID
/// @param type result report mode return reportStates only if set to FileReportFull
/// @return result report.It will be nil when error occurs
- (nullable FileTaskReportModel *)getFileTaskReport:(NSInteger)taskID type:(FileReportType)type;

/// Get all identity information in the eseal area of the specified file
///
/// @param path Full path to the file
/// @return All user IDs contained in the file.It will be nil when error occurs
- (nullable NSArray<NSString *>*)GetESealInfoByPath:(NSString *)path;

/// Get the user ID from the public key
///
/// @param pubKeyData public key
/// @return userID.It will be nil when error occurs
- (nullable NSString *)identityGetKeyIDByPublicKey:(NSData *)pubKeyData;

/// Get the public key from the private key
///
/// @param privateKeyData private key
/// @return public key.It will be nil when error occurs
- (nullable NSString *)identityGetPublicKeyByPrivateKey:(NSData *)privateKeyData;

/// Whether the file manipulation task module is exitable
/// If a file operation task is being processed, it is not allowed to exit and must wait until all tasks are completed or actively cancelled before it is allowed to exit
///
/// @return whether exit is allowed
- (BOOL)checkFileTaskCanExit;

/// Enable local Http service
///
/// @param port Port number
/// @return The result of the operation
- (TSKResult)startLocalHttpServer:(NSInteger)port;

/// Stop local Http service
- (void)stopLocalHttpServer;

/// Set local Http service time
///
/// @param time Timestamp
- (void)setTimeForLocalHttpServer:(NSInteger)time;

/// Obtain authentication key
/// If using local services, the current authentication key must be obtained, and requests to local services must carry the obtained key to determine whether the request is valid
///
/// @return Authentication key
- (NSString *)getKeyFromLocalHttpServer;

/// Set the basic parameters of the current website
/// Download and open the DApp website data locally to provide a faster start-up and usage experience for DApp
/// Currently only support dApp static data acquisition, and dynamic request forwarding
///
/// @param fullPath The full path to the site's root directory
/// @param dynamicFlag Dynamic request flag
/// @param remoteServer Address of the remote server to which dynamic requests are forwarded
/// @param homepageName Home page name, default is index.html
/// @param pemPath The server's SSL public key is provided in the form of a standard pem certificate file
- (void)setCurrentWebSiteParamForLocalHttpServer:(nullable NSString *)fullPath dynamicFlag:(nullable NSString *)dynamicFlag remoteServer:(nullable NSString *)remoteServer homepageName:(nullable NSString *)homepageName pemPath:(nullable NSString *)pemPath;

/// Get the raw data of the encrypted message header
///
/// @param path The full path to the file
/// @return raw data of encrypted message header
- (NSData *)getOriginHeader:(NSString *)path;

/// Get the encrypted message header after padding
/// The output file size is a multiple of 8K
///
/// @param headerData pre-populated data
/// @param toPath The full path to the output file
/// @return processing result
- (TSKResult)getFilledHeader:(NSData *)headerData toPath:(NSString *)toPath;

/// Get the original length of the encrypted message header
///
/// @param path The full path to the file
/// @return original length of encrypted message header (i.e. not including padding)
- (NSInteger)getHeaderCount:(NSString *)path;

/// Determine if a file has been encrypted using the SDK based on the path
///
/// @param path Full path to the file
/// @return if the file is encrypted
- (BOOL)isFileEncrypted:(NSString *)path;

/// Get the length of the padding area of the encrypted message header
///
/// @param path file path
/// @return length of padding area of encrypted message header
- (NSInteger)getEncryptHeadFillLen:(NSString *)path;

/// Get the actual content length of the encrypted message header
/// 
/// @param path file path
/// @return The actual length of the encrypted message header
- (NSInteger)getEncryptHeadLen:(NSString *)path;

@end

NS_ASSUME_NONNULL_END
