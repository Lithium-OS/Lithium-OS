#!/bin/bash
da=`date -u`
echo "#define BUILD_TIME \"" $da  "\""> build.h