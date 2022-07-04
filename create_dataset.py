import sys
import os

bubblesort_output = open(f"{os.getcwd()}/dataset/bubblesort.txt", "w")
insertionsort_ouput = open(f"{os.getcwd()}/dataset/insertionsort.txt", "w")
mergesort_ouput = open(f"{os.getcwd()}/dataset/mergesort.txt", "w")
selectionsort_ouput = open(f"{os.getcwd()}/dataset/selectionsort.txt", "w")
simpleloop_ouput = open(f"{os.getcwd()}/dataset/simpleloop.txt", "w")
simpleloopreverse_ouput = open(f"{os.getcwd()}/dataset/simpleloopreverse.txt", "w")

for num_elems_filename in os.listdir(f"benchmarks/"):
    for filename in os.listdir(f"benchmarks/{num_elems_filename}"):
        for filename_2 in os.listdir(f"{os.getcwd()}/benchmarks/{num_elems_filename}/{filename}"):
            # print(os.path.join(f"{os.getcwd()}/benchmarks/{filename}", filename_2))
            if os.path.join(f"{os.getcwd()}/benchmarks/{num_elems_filename}/{filename}", filename_2).__contains__("_avg"):
                avg_file = open(f"{os.getcwd()}/benchmarks/{num_elems_filename}/{filename}/{filename_2}", "r")
                print(filename_2)
                # print(avg_file.read())

                # print(f"{num_elems_filename} {avg_file.read()}")
                if filename_2.__contains__("mergesort"):
                    mergesort_ouput.write(f"{filename} {num_elems_filename} {avg_file.read()}\n")
                    continue
                if filename_2.__contains__("insertionsort"):
                    insertionsort_ouput.write(f"{filename} {num_elems_filename} {avg_file.read()}\n")
                    continue
                if filename_2.__contains__("bubblesort"):
                    bubblesort_output.write(f"{filename} {num_elems_filename} {avg_file.read()}\n")
                    continue
                if filename_2.__contains__("selectionsort"):
                    selectionsort_ouput.write(f"{filename} {num_elems_filename} {avg_file.read()}\n")
                    continue
                if filename_2.__contains__("simpleLoop.txt"):
                    simpleloop_ouput.write(f"{filename} {num_elems_filename} {avg_file.read()}\n")
                    continue
                if filename_2.__contains__("simpleLoopBackward"):
                    simpleloopreverse_ouput.write(f"{filename} {num_elems_filename} {avg_file.read()}\n")
                    continue
                continue