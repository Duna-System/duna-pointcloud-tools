#! /bin/bash

echo "Formatting code..."
find filters grpc registration mapping \( -iname *.h -o -iname *.cpp -o -iname *.md \) -and -not -iname *duna_exports.h | xargs clang-format -i