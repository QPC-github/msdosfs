/* Copyright © 2017 Apple Inc. All rights reserved.
 *
 *  FileOPS_Handler.h
 *  usbstorage_plugin
 *
 *  Created by Or Haimovich on 15/10/17.
 */

#ifndef FileOPS_Handler_h
#define FileOPS_Handler_h

#include <stdio.h>
#include "Common.h"

#if 0
#define VALID_IN_ATTR_MASK (   UVFS_FA_VALID_TYPE           |   \
                               UVFS_FA_VALID_MODE           |   \
                               UVFS_FA_VALID_NLINK          |   \
                               UVFS_FA_VALID_UID            |   \
                               UVFS_FA_VALID_GID            |   \
                               UVFS_FA_VALID_BSD_FLAGS      |   \
                               UVFS_FA_VALID_SIZE           |   \
                               UVFS_FA_VALID_ALLOCSIZE      |   \
                               UVFS_FA_VALID_FILEID         |   \
                               UVFS_FA_VALID_ATIME          |   \
                               UVFS_FA_VALID_MTIME          |   \
                               UVFS_FA_VALID_CTIME          |   \
                               UVFS_FA_VALID_BIRTHTIME)
#endif

#define VALID_OUT_ATTR_MASK (   UVFS_FA_VALID_TYPE           |   \
                                UVFS_FA_VALID_MODE           |   \
                                UVFS_FA_VALID_NLINK          |   \
                                UVFS_FA_VALID_BSD_FLAGS      |   \
                                UVFS_FA_VALID_SIZE           |   \
                                UVFS_FA_VALID_ALLOCSIZE      |   \
                                UVFS_FA_VALID_FILEID         |   \
                                UVFS_FA_VALID_ATIME          |   \
                                UVFS_FA_VALID_MTIME          |   \
                                UVFS_FA_VALID_CTIME          |   \
                                UVFS_FA_VALID_BIRTHTIME)

#define READ_ONLY_FA_FIELDS (   UVFS_FA_VALID_TYPE       |   \
                                UVFS_FA_VALID_NLINK      |   \
                                UVFS_FA_VALID_ALLOCSIZE  |   \
                                UVFS_FA_VALID_FILEID     |   \
                                UVFS_FA_VALID_CTIME      )

#define SYNTH_ROOT_VALID_ATTR_MASK (    UVFS_FA_VALID_TYPE           |   \
                                        UVFS_FA_VALID_MODE           |   \
                                        UVFS_FA_VALID_NLINK          |   \
                                        UVFS_FA_VALID_SIZE           |   \
                                        UVFS_FA_VALID_ALLOCSIZE      |   \
                                        UVFS_FA_VALID_FILEID         |   \
                                        UVFS_FA_VALID_ATIME          |   \
                                        UVFS_FA_VALID_CTIME          |   \
                                        UVFS_FA_VALID_MTIME          |   \
                                        UVFS_FA_VALID_BIRTHTIME)

#define MSDOS_VALID_BSD_FLAGS_MASK (SF_ARCHIVED | SF_IMMUTABLE | UF_IMMUTABLE | UF_HIDDEN)

int     MSDOS_Read(UVFSFileNode Node, uint64_t offset, size_t length, void *outBuf, size_t *actuallyRead);
int     MSDOS_Write(UVFSFileNode Node, uint64_t offset, size_t length, const void *buf, size_t *actuallyWritten);
int     MSDOS_Create(UVFSFileNode dirNode, const char *name, const UVFSFileAttributes *attrs, UVFSFileNode *outNode);
int     MSDOS_GetAttr(UVFSFileNode Node, UVFSFileAttributes *ottars);
int     MSDOS_SetAttr(UVFSFileNode Node, const UVFSFileAttributes *setAttrs, UVFSFileAttributes *outAttrs);
int     MSDOS_Reclaim(UVFSFileNode Node, unsigned int flags);
int     MSDOS_ReadLink(UVFSFileNode Node, void *outBuf, size_t bufsize, size_t *actuallyRead, UVFSFileAttributes *outAttrs);
int     MSDOS_SymLink(UVFSFileNode dirNode, const char *name, const char *contents, const UVFSFileAttributes *attrs, UVFSFileNode *outNode);
int		MSDOS_Link(UVFSFileNode fromNode, UVFSFileNode toDirNode, const char *toName, UVFSFileAttributes *outFileAttrs, UVFSFileAttributes *outDirAttrs);
int     MSDOS_Rename (UVFSFileNode fromDirNode, UVFSFileNode fromNode, const char *fromName, UVFSFileNode toDirNode, UVFSFileNode toNode, const char *toName, uint32_t flags);

void        MSDOS_GetAttrFromDirEntry (NodeRecord_s* psNodeRecord, UVFSFileAttributes *outAttrs);
uint64_t    MSDOS_GetFileID (uint64_t uFirstClusterNumber, bool isFat12Or16Root, FileSystemRecord_s* psFSRecord);

int  FILEOPS_UpdateLastModifiedTime(NodeRecord_s* psNodeRecord, bool *pbShouldFlush);
int  FILEOPS_PreAllocateClusters(NodeRecord_s* psNodeRecord, LIFilePreallocateArgs_t* psPreAllocReq, LIFilePreallocateArgs_t* psPreAllocRes);
int FILEOPS_FreeUnusedPreAllocatedClusters(NodeRecord_s* psNodeRecord);

#endif /* FileOPS_Handler_h */
