#!/bin/bash
SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

do_hundred_runs() {
    bin_files=$SCRIPTPATH/examples/*.bin

    # echo "HI"
    # echo "$1"
  time_values=()
  total=0
  
  for file in $bin_files
  do
    name="$(basename $file)"
    :> "$SCRIPTPATH/benchmarks/$2/${name::-4}.txt"
    # echo "$SCRIPTPATH/benchmarks/$2/${name::-4}.txt"
  done

  for k in {1..1000};
  do
    for file in $bin_files
    do
        name="$(basename $file)"
        res=""
        res=$($SCRIPTPATH/examples/$name)
        echo $res  >> "$SCRIPTPATH/benchmarks/$2/${name::-4}.txt"
    done
  done

}


programs_files=$SCRIPTPATH/examples/*.c
for file in $programs_files
do
 name="$(basename $file)"
#  echo compiling with no optimizations: $name
 ./comp.bin $file >/dev/null 2>&1
 trimmed_name=${name::-2}
done
 do_hundred_runs $trimmed_name 0

for file in $programs_files
do
 ./comp.bin $file -d >/dev/null 2>&1
done
do_hundred_runs $trimmed_name 1

for file in $programs_files
do
 ./comp.bin $file -d -d >/dev/null 2>&1
done
do_hundred_runs $trimmed_name 2

echo Done