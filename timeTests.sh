#!/bin/bash

# Run the naive solution with U=20
echo "Running naive solution with U=20"
time ./naive <<EOF
20
EOF

# Run the DP solution with U=20
echo "Running DP solution with U=20"
time ./dp <<EOF
20
EOF
 