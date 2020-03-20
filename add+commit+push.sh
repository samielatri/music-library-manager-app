#!/bin/bash

echo "debut\n"

git add -A
echo "etape1->ok\n"

git commit -m "${1}"
echo "etape2->ok\n"

git push
echo "etape3->ok\n"

echo "FIN\n"

exit 0
