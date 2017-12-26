#!/bin/sh
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
#  Abstract: a script to 'cat' contents of most informative files of '/proc'
#  To deploy on <M5, TouchP5> do such console operations:
#	a) touch /tmp/a.sh ; chmod u+rx /tmp/a.sh; vi /tmp/a.sh;
#	b) click 'a' for enter <vi> editor's insert mode;
#	c) paste text of the actual script into edit window (previously
#	copied into there);
#	d) execute </tmp/a.sh> on command line - get output on STDOUT .



`ls -1 /proc> /tmp/$0.tmp`

while read proc_fname; do

	echo "processing <"$proc_fname"> ..."

	if [[ -d "/proc/$proc_fname" ]]; then
		echo " skipping directory <$proc_fname>"; echo ""
	else

		if [[ "/proc/kcore" = "/proc/$proc_fname" || "/proc/kallsyms" = "/proc/$proc_fname" || "/proc/kmsg" = "/proc/$proc_fname" ]]; then

			echo " skipping looooong (and really useless) file <$proc_fname>"; echo ""

		else
			#echo " doing then file $proc_fname"
			cat "/proc/$proc_fname"

			echo ""
		fi
	fi

	echo "done"; echo ""


done < /tmp/$0.tmp

rm -f /tmp/$0.tmp
