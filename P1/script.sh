#!/bin/sh
if test -e mytar ; then
	echo	"mytar found"
else
	echo 	"mytar not found"
exit 1
fi

if [-x mytar] ; then
	echo	"level permission for execution checked correctly"
else
	echo 	"ERROR: level permission for execution found a problem"
exit 1
fi
