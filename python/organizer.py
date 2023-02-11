import numpy as np
import pandas as pd

vgg = [
    "conv1_1", "conv1_2", 
    "conv2_1", "conv2_2", 
    "conv3_1", "conv3_2", "conv3_3", 
    "conv4_1", "conv4_2", "conv4_3", 
    "conv5_1", "conv5_2", "conv5_3"
]

google = [
    "3a_1x1", "3a_3x3_reduce", "3a_3x3", "3a_5x5_reduce", "3a_5x5", "3a_pool_proj",
    "5b_1x1", "5b_3x3_reduce", "5b_3x3", "5b_5x5_reduce", "5b_5x5", "5b_pool_proj"
]

options = [
    "ver8x8_OUTPUT_halo", "ver4x4_OUTPUT_halo", "ver2x2_OUTPUT_halo", "ver1x1_OUTPUT_halo",
    "ver8x8", "ver4x4", "ver2x2", "ver1x1",
    "Xbar_scaleout_4_OUTPUT_halo", "Xbar_scaleout_1_OUTPUT_halo",
    "FI8x8_OUTPUT_halo", "FI2x2_OUTPUT_halo"
]

vgg_layers = []
google_layers = []
df_array = []

for layer in vgg:
    for option in options:
        vgg_layers.append(layer + "_" + option)

for layer in google:
    for option in options:
        google_layers.append(layer + "_" + option)

for layer in vgg_layers:
    fileName = "Results/vgg16/VGG16_" + layer
    # print(fileName)
    f = open(fileName)
    # Collect PE data and Total data separately
    PE_data = ""
    Total_data = ""
    for line in f.readlines():
        if "PE index" in line:
            PE_data += line
        if ("Total " in line) and ("-----" not in line):
            Total_data += line
        elif ("Valid " in line) and ("-----" not in line):
            Total_data += line
    columns = ["Cycles spent", "Cycles active", "Cycles stalled", "Cycles blocked", "Total multops", "Valid multops"]
    index = []
    dataframe = []
    PE_lines = PE_data.splitlines()
    Total_lines = Total_data.splitlines()
    index.append("Total")
    tempdata_line = []
    tempdata_line.append(Total_lines[0][Total_lines[0].index("Total cycles spent: ") + len("Total cycles spent: "):])
    tempdata_line.append(Total_lines[1][Total_lines[1].index("Total active cycles: ") + len("Total active cycles: "):])
    tempdata_line.append(Total_lines[2][Total_lines[2].index("Total stalled cycles: ") + len("Total stalled cycles: "):])
    tempdata_line.append(Total_lines[3][Total_lines[3].index("Total blocked cycles: ") + len("Total blocked cycles: "):])
    tempdata_line.append(Total_lines[4][Total_lines[4].index("Total multiplication operations: ") + len("Total multiplication operations: "):])
    tempdata_line.append(Total_lines[5][Total_lines[5].index("Valid multiplication operations: ") + len("Valid multiplication operations: "):])
    dataframe.append(tempdata_line)
    while (len(PE_lines) > 0):
        temp_data = []
        temp_data.append(PE_lines.pop(0))
        temp_data.append(PE_lines.pop(0))
        index.append("PE index " + temp_data[0][9:15])
        
        data_line = []
        # Cycles spent
        data_line.append(temp_data[0][temp_data[0].index("Total cycles spent: ") + len("Total cycles spent: "):temp_data[0].index(" ----- Number of cycles active")])
        # Cycles active
        data_line.append(temp_data[0][temp_data[0].index("Number of cycles active: ") + len("Number of cycles active: "):temp_data[0].index(" ----- Number of cycles stalled")])
        # Cycles stalled
        data_line.append(temp_data[0][temp_data[0].index("Number of cycles stalled: ") + len("Number of cycles stalled: "):temp_data[0].index(" ----- Number of cycles blocked")])
        # Cycles blocked
        data_line.append(temp_data[0][temp_data[0].index("Number of cycles blocked: ") + len("Number of cycles blocked: "):temp_data[0].index(" ----- Active cycle Ratio")])
        # Total multops
        data_line.append(temp_data[1][temp_data[1].index("Total Multops: ") + len("Total Multops: "):temp_data[1].index(" ----- Number of valid multops")])
        # Valid multops
        data_line.append(temp_data[1][temp_data[1].index("Number of valid multops: ") + len("Number of valid multops: "):temp_data[1].index("----- Valid Multops Ratio")])


        dataframe.append(data_line)
    df = pd.DataFrame(dataframe, index=index, columns=columns)
    if(len(layer) <= 31):
        df_array.append([df, layer])
    else:
        df_array.append([df, layer[0:31]])

with pd.ExcelWriter("VGGResult.xlsx") as writer:
    for df in df_array:
        df[0].to_excel(writer, sheet_name=df[1])


for layer in google_layers:
    fileName = "Results/google/inception_" + layer
    # print(fileName)
    f = open(fileName)
    # Collect PE data and Total data separately
    PE_data = ""
    Total_data = ""
    for line in f.readlines():
        if "PE index" in line:
            PE_data += line
        if ("Total " in line) and ("-----" not in line):
            Total_data += line
        elif ("Valid " in line) and ("-----" not in line):
            Total_data += line
    columns = ["Cycles spent", "Cycles active", "Cycles stalled", "Cycles blocked", "Total multops", "Valid multops"]
    index = []
    dataframe = []
    PE_lines = PE_data.splitlines()
    Total_lines = Total_data.splitlines()
    index.append("Total")
    tempdata_line = []
    tempdata_line.append(Total_lines[0][Total_lines[0].index("Total cycles spent: ") + len("Total cycles spent: "):])
    tempdata_line.append(Total_lines[1][Total_lines[1].index("Total active cycles: ") + len("Total active cycles: "):])
    tempdata_line.append(Total_lines[2][Total_lines[2].index("Total stalled cycles: ") + len("Total stalled cycles: "):])
    tempdata_line.append(Total_lines[3][Total_lines[3].index("Total blocked cycles: ") + len("Total blocked cycles: "):])
    tempdata_line.append(Total_lines[4][Total_lines[4].index("Total multiplication operations: ") + len("Total multiplication operations: "):])
    tempdata_line.append(Total_lines[5][Total_lines[5].index("Valid multiplication operations: ") + len("Valid multiplication operations: "):])
    dataframe.append(tempdata_line)
    while (len(PE_lines) > 0):
        temp_data = []
        temp_data.append(PE_lines.pop(0))
        temp_data.append(PE_lines.pop(0))
        index.append("PE index " + temp_data[0][9:15])
        
        data_line = []
        # Cycles spent
        data_line.append(temp_data[0][temp_data[0].index("Total cycles spent: ") + len("Total cycles spent: "):temp_data[0].index(" ----- Number of cycles active")])
        # Cycles active
        data_line.append(temp_data[0][temp_data[0].index("Number of cycles active: ") + len("Number of cycles active: "):temp_data[0].index(" ----- Number of cycles stalled")])
        # Cycles stalled
        data_line.append(temp_data[0][temp_data[0].index("Number of cycles stalled: ") + len("Number of cycles stalled: "):temp_data[0].index(" ----- Number of cycles blocked")])
        # Cycles blocked
        data_line.append(temp_data[0][temp_data[0].index("Number of cycles blocked: ") + len("Number of cycles blocked: "):temp_data[0].index(" ----- Active cycle Ratio")])
        # Total multops
        data_line.append(temp_data[1][temp_data[1].index("Total Multops: ") + len("Total Multops: "):temp_data[1].index(" ----- Number of valid multops")])
        # Valid multops
        data_line.append(temp_data[1][temp_data[1].index("Number of valid multops: ") + len("Number of valid multops: "):temp_data[1].index("----- Valid Multops Ratio")])


        dataframe.append(data_line)
    df = pd.DataFrame(dataframe, index=index, columns=columns)
    if(len(layer) <= 31):
        df_array.append([df, layer])
    else:
        df_array.append([df, layer[0:31]])

with pd.ExcelWriter("GoogleResult.xlsx") as writer:
    for df in df_array:
        df[0].to_excel(writer, sheet_name=df[1])


    # print(PE_data.splitlines())
    # print(Total_data.splitlines())