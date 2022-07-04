import sys
import os
# f_0 = open(f"{os.getcwd()}/benchmarks/{sys.argv[1]}/0", "r")
# f_1 = open(f"{os.getcwd()}/benchmarks/{sys.argv[1]}/1", "r")
# f_2 = open(f"{os.getcwd()}/benchmarks/{sys.argv[1]}/2", "r")


for filename in os.listdir(f"benchmarks/{sys.argv[1]}"):
    for filename_2 in os.listdir(f"{os.getcwd()}/benchmarks/{sys.argv[1]}/{filename}"):
        # print(os.path.join(f"{os.getcwd()}/benchmarks/{filename}", filename_2))
        if os.path.join(f"{os.getcwd()}/benchmarks/{sys.argv[1]}/{filename}", filename_2).__contains__("_avg"):
            continue
        f = open(os.path.join(f"{os.getcwd()}/benchmarks/{sys.argv[1]}/{filename}", filename_2), 'r')
        print(f"working on {filename_2}")
        total = 0
        outliers_count = 0
        for line in f:
            num = int(line)
            if num < 0:
                outliers_count += 1
            else:
                total += num

        avg = total / (1000 - outliers_count)
        new_file_name = "_avg" +filename_2.split(".")[0] + ".txt"
        print(f"deleted {outliers_count} outliers")
        print(f"avg is {avg}\n\n")
        # print(f"{os.getcwd()}/benchmarks/{sys.argv[1]}/{filename}/{new_file_name}")
        output_f = open(f"{os.getcwd()}/benchmarks/{sys.argv[1]}/{filename}/{new_file_name}", "w")
        # print(text)
        output_f.write(str(avg))
        # print(f.name)


# {sys.argv[1]}
# print(f_0.read()) 