#include <sys/cdefs.h>
#include "namespace.h"
#include <lib.h>

#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

#ifdef __weak_alias
__weak_alias(futimes, __futimes50)
#endif

int futimes(int fd, const struct timeval tv[2])
{
  message m;

  memset(&m, 0, sizeof(m));
  m.m_vfs_utimens.fd = fd;
  if (tv == NULL) {
	m.m_vfs_utimens.atime = m.m_vfs_utimens.mtime = 0;
	m.m_vfs_utimens.ansec = m.m_vfs_utimens.mnsec = UTIME_NOW;
  }
  else {
	m.m_vfs_utimens.atime = tv[0].tv_sec;
	m.m_vfs_utimens.mtime = tv[1].tv_sec;
	m.m_vfs_utimens.ansec = tv[0].tv_usec * 1000;
	m.m_vfs_utimens.mnsec = tv[1].tv_usec * 1000;
  }
  m.m_vfs_utimens.name = NULL;
  m.m_vfs_utimens.flags = 0;

  return(_syscall(VFS_PROC_NR, VFS_UTIMENS, &m));
}
