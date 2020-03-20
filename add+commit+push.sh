#!/bin/bash

echo "debut"

git add --all
echo "etape1->ok"

git commit -m "${1}"
echo "etape2->ok"

git push --force
echo "etape3->ok"

echo "Fin"

exit 0
