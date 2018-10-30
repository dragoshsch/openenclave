// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <openenclave/internal/mount.h>
#include <stdarg.h>
#include <string.h>
#include "blockdev.h"
#include "fs.h"
#include "oefs.h"

int oe_mount_oefs(
    const char* source,
    const char* target,
    uint32_t flags,
    size_t num_blocks)
{
    int ret = -1;
    oe_block_dev_t* dev = NULL;
    fs_t* fs = NULL;

    if (source)
    {
        /* Open a host device. */
        if (oe_open_host_block_dev(source, &dev) != 0)
            goto done;
    }
    else
    {
        size_t size;

        /* Open a ram device within enclave memory. */

        if (flags & OE_MOUNT_FLAG_CRYPTO)
            goto done;

        if (oefs_size(num_blocks, &size) != 0)
            goto done;

        if (oe_open_ram_block_dev(size, &dev) != 0)
            goto done;
    }

    if (flags & OE_MOUNT_FLAG_MKFS)
    {
        if (oefs_mkfs(dev, num_blocks) != 0)
            goto done;
    }

    if (oefs_initialize(&fs, dev) != 0)
        goto done;

    dev = NULL;

    if (fs_bind(fs, target) != 0)
        goto done;

    fs = NULL;

    ret = 0;

done:

    if (dev)
        dev->release(dev);

    if (fs)
        fs->fs_release(fs);

    return ret;
}