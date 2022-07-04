import atexit
import sys
import os

# from numpy import double
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
bubblesort_output = open(f"{os.getcwd()}/dataset/bubblesort.txt", "r")
insertionsort_ouput = open(f"{os.getcwd()}/dataset/insertionsort.txt", "r")
mergesort_ouput = open(f"{os.getcwd()}/dataset/mergesort.txt", "r")
selectionsort_ouput = open(f"{os.getcwd()}/dataset/selectionsort.txt", "r")
simpleloop_ouput = open(f"{os.getcwd()}/dataset/simpleloop.txt", "r")
simpleloopreverse_ouput = open(f"{os.getcwd()}/dataset/simpleloopreverse.txt", "r")

# add_to_plot("bubble sort", bubblesort_data)
figure, axis = plt.subplots(2, 2)
algo_names = ["selection sort","bubble sort","simple loop","merge sort"]

# file = (selectionsort_ouput.read().split("\n"))
files = [selectionsort_ouput.read().split("\n"),bubblesort_output.read().split("\n"),simpleloop_ouput.read().split("\n"),mergesort_ouput.read().split("\n")]
count = 0
for file in files:
    w_boundschecks_x = []
    w_boundcheckselim_x = []
    wo_boundschecks_x = []
    w_boundschecks_y = []
    wo_boundschecks_y = []
    w_boundcheckselim_y = []
    i = 0
    while i < 30:
        benchmark_type = file[i].split(" ")[0]
        x = file[i].split(" ")[1]
        y = file[i].split(" ")[2]
        if benchmark_type == '0':
            wo_boundschecks_x.append(int(x))
            wo_boundschecks_y.append(np.double(y))
        elif benchmark_type == '1':
            w_boundschecks_x.append(int(x))
            w_boundschecks_y.append(np.double(y))
        else:
            w_boundcheckselim_x.append(int(x))
            w_boundcheckselim_y.append(np.double(y))

        i += 1

    df0 = pd.DataFrame(wo_boundschecks_y,wo_boundschecks_x).sort_index()
    df1 = pd.DataFrame(w_boundschecks_y,w_boundschecks_x).sort_index()
    df2 = pd.DataFrame(w_boundcheckselim_y,w_boundcheckselim_x).sort_index()

    if count  == 0:
        use_axis = axis[0,0]
    elif count == 1:
        use_axis = axis[0,1]
    elif count == 2:
        use_axis = axis[1,0]
    else:
        use_axis = axis[1,1]

    use_axis.plot(df0,label="w/o bounds_checks")
    use_axis.plot(df1,label="with bounds-checks")
    use_axis.plot(df2,label="bounds-check elimination")
    use_axis.set_xlabel("number of elements in array")
    use_axis.set_ylabel("execution time in microseconds")
    use_axis.set_label("test")
    use_axis.set_title(f"Performance of {algo_names[count]}")
    use_axis.legend()
    count += 1


# plt.title(f"Performance measurements")
plt.show()




# def add_to_plot(algo_name, file):







# import atexit
# import sys
# import os

# # from numpy import double
# import numpy as np
# import matplotlib.pyplot as plt
# import pandas as pd



# def add_to_plot(algo_name, file):
#     print(file)
#     w_boundschecks_x = []
#     w_boundschecks_x = []
#     w_boundcheckselim_x = []
#     w_boundschecks_y = []
#     w_boundschecks_y = []
#     w_boundcheckselim_y = []
#     i = 0
#     while i < 30:
#         benchmark_type = file[i].split(" ")[0]
#         x = file[i].split(" ")[1]
#         y = file[i].split(" ")[2]
#         if benchmark_type == '0':
#             w_boundschecks_x.append(int(x))
#             w_boundschecks_y.append(np.double(y))
#         elif benchmark_type == '1':
#             w_boundschecks_x.append(int(x))
#             w_boundschecks_y.append(np.double(y))
#         else:
#             w_boundcheckselim_x.append(int(x))
#             w_boundcheckselim_y.append(np.double(y))

#         i += 1

#     df0 = pd.DataFrame(w_boundschecks_y,w_boundschecks_x).sort_index()
#     df1 = pd.DataFrame(w_boundschecks_y,w_boundschecks_x).sort_index()
#     df2 = pd.DataFrame(w_boundcheckselim_y,w_boundcheckselim_x).sort_index()
#     plt.plot(df0,label="w/o bounds_checks")
#     plt.plot(df1,label="with bounds-checks")
#     plt.plot(df2,label="bounds-check elimination")
#     plt.xlabel("number of elements in array")
#     plt.ylabel("execution time in microseconds")

#     plt.title(f"Performance measurements of {algo_name}")
#     plt.legend()



#     plt.show()






# bubblesort_output = open(f"{os.getcwd()}/dataset/bubblesort.txt", "r")
# insertionsort_ouput = open(f"{os.getcwd()}/dataset/insertionsort.txt", "r")
# mergesort_ouput = open(f"{os.getcwd()}/dataset/mergesort.txt", "r")
# selectionsort_ouput = open(f"{os.getcwd()}/dataset/selectionsort.txt", "r")
# simpleloop_ouput = open(f"{os.getcwd()}/dataset/simpleloop.txt", "r")
# simpleloopreverse_ouput = open(f"{os.getcwd()}/dataset/simpleloopreverse.txt", "r")


# bubblesort_data = (bubblesort_output.read().split("\n"))
# print(bubblesort_data)
# add_to_plot("bubble sort", bubblesort_data)




