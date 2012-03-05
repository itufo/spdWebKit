#!/bin/sh

Tools/Scripts/build-webkit --minimal --spd 2>1 >c.log

if [ $? -eq 0 ]
then
   echo "compile success"
else
   echo "compile fail"
   cat c.log |grep "错误"
fi
