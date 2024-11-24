#!/bin/bash




# Calculate the maximum rejection cost (U_max)
U_max=$(awk '{sum += $2} END {print sum}' jobs.txt)

# Output CSV file
output_file="comparison_results.csv"

# Write headers to CSV
echo "U,Naive Time (s),DP Time (s),Naive Result,DP Result" > $output_file

# Test for U values from 0 to U_max
for ((U=0; U<=U_max; U++))
do
    echo "Testing U=$U..."

    # Run the naive implementation and capture runtime and result
    naive_start=$(date +%s%N)
    naive_output=$(./naive <<EOF
$U
EOF
    )
    naive_end=$(date +%s%N)
    naive_time=$(echo "scale=6; ($naive_end - $naive_start) / 1000000000" | bc)
    naive_result=$(echo "$naive_output" | tail -n 1)

    # Run the DP implementation and capture runtime and result
    dp_start=$(date +%s%N)
    dp_output=$(./dp <<EOF
$U
EOF
    )
    dp_end=$(date +%s%N)
    dp_time=$(echo "scale=6; ($dp_end - $dp_start) / 1000000000" | bc)
    dp_result=$(echo "$dp_output" | tail -n 1)

    # Append results to CSV
    echo "$U,$naive_time,$dp_time,$naive_result,$dp_result" >> $output_file
done

echo "Comparison completed. Results saved to $output_file."