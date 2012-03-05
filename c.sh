#!/bin/sh

Tools/Scripts/build-webkit --minimal --spd 2>1 >c.log

if [ $? -eq 0 ]
then
   echo "compile success"
   cat c.log |grep "错误"
else
   echo "compile fail"
fi
