#!/bin/bash


# Output CSV file
output_file="comparison_results.csv"

# Write headers to CSV
echo "U,Naive Time (s),DP Time (s)" > $output_file

# Test for U values from 1 to 20
for U in {1..20}
do
    echo "Testing U=$U..."

    # Run the naive implementation
    naive_start=$(date +%s%N)
    ./naive <<EOF > /dev/null
$U
EOF
    naive_end=$(date +%s%N)
    naive_time=$(echo "scale=6; ($naive_end - $naive_start) / 1000000000" | bc)

    # Run the DP implementation
    dp_start=$(date +%s%N)
    ./dp <<EOF > /dev/null
$U
EOF
    dp_end=$(date +%s%N)
    dp_time=$(echo "scale=6; ($dp_end - $dp_start) / 1000000000" | bc)

    # Append results to CSV
    echo "$U,$naive_time,$dp_time" >> $output_file
done

echo "Comparison completed. Results saved to $output_file."
