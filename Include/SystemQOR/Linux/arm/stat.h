//stat.h

#ifndef SYSTEMQOR_LINUX_ARM_STAT_H_3
#define SYSTEMQOR_LINUX_ARM_STAT_H_3

namespace nsLinux
{
    struct stat
    {
        dev_t st_dev;
        int __st_dev_padding;
        long __st_ino_truncated;
        mode_t st_mode;
        nlink_t st_nlink;
        uid_t st_uid;
        gid_t st_gid;
        dev_t st_rdev;
        int __st_rdev_padding;
        off_t st_size;
        blksize_t st_blksize;
        blkcnt_t st_blocks;
        struct timespec st_atim;
        struct timespec st_mtim;
        struct timespec st_ctim;
        ino_t st_ino;
    };

    typedef stat sstat;

}//nsLinux

#endif//SYSTEMQOR_LINUX_ARM_STAT_H_3
