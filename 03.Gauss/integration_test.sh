#!/bin/bash

set -euo pipefail

status=true

mkdir -p .itest

cat > .itest/input.csv <<EOF
A,A,B
2,1,4
1,-1,-1
EOF

cat > .itest/expected.csv <<EOF
x
1.000000
2.000000
EOF

./gauss .itest/input.csv > .itest/output.csv

if cmp -s .itest/expected.csv .itest/output.csv
then
    echo "Integration test passed"
else
    echo "Integration test failed"
    status=false
fi

$status
