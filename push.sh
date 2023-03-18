#!/bin/bash

dev=$(git status | awk 'NR=='1'{print $3}')
echo "$dev"
git add .
git commit -m "$(date +"%Y.%m.%d_%H:%M")"
git push origin $dev
# cat "$(date +"%Y.%m.%d_%H:%M")"
