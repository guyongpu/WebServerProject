#!/bin/bash
commit_str=$1
git add .
git commit -m "${commit_str}"
git push origin master
echo "github push finish!"
