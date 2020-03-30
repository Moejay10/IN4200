import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
from pandas import DataFrame

# Where to save the figures and data files
DATA_ID = "Results/Data"

def data_path(dat_id):
    return os.path.join(DATA_ID, dat_id)

num_threads = np.linspace(1, 8, 8)

read_graph_from_file1 = 0
read_graph_from_file2 = 0

count_mutual_links1 = np.zeros(len(num_threads))
top_n_webpages1 = np.zeros(len(num_threads))
count_mutual_links2 = np.zeros(len(num_threads))
top_n_webpages2 = np.zeros(len(num_threads))

Time = {}

for i in range(1, len(num_threads) + 1):
    Time["Threads" + str(i)] = pd.read_fwf(data_path("Time" + str(i)))

    print("Results from Threads" + str(i))
    print(Time["Threads" + str(i)]["Time"])

    read_graph_from_file1 += Time["Threads" + str(i)]["Time"][0]
    count_mutual_links1[i-1] =  Time["Threads" + str(i)]["Time"][1]
    top_n_webpages1[i-1] =  Time["Threads" + str(i)]["Time"][2]
    read_graph_from_file2 +=  Time["Threads" + str(i)]["Time"][3]
    count_mutual_links2[i-1] =  Time["Threads" + str(i)]["Time"][4]
    top_n_webpages2[i-1] =  Time["Threads" + str(i)]["Time"][5]

print("\n The average time for:")
print("read_graph_from_file1 =  ", read_graph_from_file1/len(num_threads) )
print("read_graph_from_file2 =  ", read_graph_from_file2/len(num_threads) )


#plot
fig = plt.figure()
w = 5.78851 # Latex document text width
fig.set_size_inches(w = w*1.0, h = 5.5)

sns.set()

if (read_graph_from_file1 < 1e-6):
    plt.title("Web-NotreDame")

    plt.plot(num_threads, count_mutual_links2)
    plt.plot(num_threads, top_n_webpages2)
    plt.legend(["OMP_count_mutual_links2", "OMP_top_n_webpages"])

    plt.xlabel("Number of Threads")
    plt.ylabel("Time (s)")

    DATA_ID = "Results"
    plt.savefig(data_path("Figures/NotreDame.pgf"))

    plt.show()

else:
    plt.title("8node webgraph")

    plt.plot(num_threads, count_mutual_links1)
    plt.plot(num_threads, count_mutual_links2)
    plt.plot(num_threads, top_n_webpages2)
    plt.legend(["OMP_count_mutual_links1", "OMP_count_mutual_links2", "OMP_top_n_webpages"])

    plt.xlabel("Number of Threads")
    plt.ylabel("Time (s)")

    DATA_ID = "Results"
    plt.savefig(data_path("Figures/8nodes.pgf"))

    plt.show()
