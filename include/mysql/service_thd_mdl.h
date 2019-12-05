/* Copyright (c) 2019, MariaDB Corporation.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1335  USA */

#pragma once

/**
  @file include/mysql/service_thd_mdl.h
  This service provides functions for plugins and storage engines to access
  metadata locks.
*/

#ifdef __cplusplus
extern "C" {
#endif


extern struct thd_mdl_service_st {
  ulong (*thd_lock_wait_timeout_func)(MYSQL_THD);
  void *(*thd_mdl_context)(MYSQL_THD);
} *thd_mdl_service;

#ifdef MYSQL_DYNAMIC_PLUGIN
# define thd_lock_wait_timeout(_THD) \
  thd_mdl_service->thd_lock_wait_timeout_func(_THD)
# define thd_mdl_context(_THD) thd_mdl_service->thd_mdl_context(_THD)
#else
/**
  Read the value of lock_wait_timeout.
  @param thd   the session, or NULL to read the global value
  @return the value of lock_wait_timeout
*/
ulong thd_lock_wait_timeout(MYSQL_THD thd);
/**
  MDL_context accessor
  @param thd   the current session
  @return pointer to thd->mdl_context
*/
void *thd_mdl_context(MYSQL_THD thd);
#endif

#ifdef __cplusplus
}
#endif
