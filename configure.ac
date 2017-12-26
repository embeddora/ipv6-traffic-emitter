#
# Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#        * Redistributions of source code must retain the above copyright
#          notice, this list of conditions and the following disclaimer.
#        * Redistributions in binary form must reproduce the above copyright
#          notice, this list of conditions and the following disclaimer in the
#          documentation and/or other materials provided with the distribution.
#        * Neither the name of The Linux Foundation nor
#          the names of its contributors may be used to endorse or promote
#          products derived from this software without specific prior written
#          permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#  Abstract: input file to generate "configure" for "Traffic Emitter and
#  Traffic Receiver" applications.
#

AC_INIT("traffic_er" project's, ver. 0.2)

AC_MSG_NOTICE([Preparing single 'configure' file for both applications: "traffic_emitter" (IPv6 Traffic Emitter) and "traffic_receiver" (IPv6  Traffic Receiver)])

echo "Testing a compiler"
AC_PROG_CC
AC_LANG(C)

cu_in_h=1
AC_CHECK_HEADERS(curl/curl.h, [], [cu_in_h=0])
if test $cu_in_h == 0
then
	AC_MSG_NOTICE([curl/curl.h is missing.])
	echo 1>&2 "** check libcurl headers"
	exit -1
else
	AC_MSG_NOTICE([curl/curl.h is present])
fi


cu_in_l=1
AC_CHECK_LIB(curl, curl_easy_init, [], [cu_in_l=0])
if test $cu_in_l == 0
then
	AC_MSG_NOTICE([libcurl.a items fail.])
	echo 1>&2 "** install libcurl"
	exit -1

else
	AC_MSG_NOTICE([libcurl.a items found working.])
fi


go_in_h=1
AC_CHECK_HEADERS(getopt.h, [], [go_in_h=0])
if test $go_in_h == 0
then
	AC_MSG_NOTICE([getopt.h is missing.])
	echo 1 >&2 "** check libc headers"
	exit -1
else
	AC_MSG_NOTICE([getopt.h is present])
fi

go_in_l=1
AC_CHECK_LIB(c, getopt_long, [], [go_in_l=0])
if test $go_in_l == 0
then
	AC_MSG_NOTICE([getopt items fail.])
	echo 1 >&2 "** check libc library"
	exit -1
else
	AC_MSG_NOTICE([getopt items found working])
fi



AC_SUBST(BUILD_CURL, $BUILD_CURL)

AC_SUBST(PLATFORM, $(uname -s))

AC_SUBST(INSTALL_OPTIONS, $INSTALL_OPTIONS)
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
