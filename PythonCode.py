import re
import os

# variables for 2 files that are being used
sales_file = "CS210_Project_Three_Input_File.txt"
processed_file = "frequency.dat"


# Function to open file and read into a list line by line
def get_sales_list(filename):
    sales_list = []
    with open(filename, "r") as input_file:
        sales_list = re.split("\n", input_file.read())
        input_file.close()
    return sales_list


# Function to open file and write contents line by line
def write_output_file(output_dict, filename):
    newline = "\n"
    count = 0
    with open(filename, "w") as output_file:
        for key, value in output_dict.items():
            count += 1
            # Added so a newline char is not added to end of file
            if count == len(output_dict):
                newline = ""
            output_file.write(f"{key} {value}{newline}")
        output_file.close()

    return


# Function to read items out of file and print contents to the console
def list_all_items():
    sales_list = []
    sales_list = get_sales_list(processed_file)
    sales_dict = {}
    for line in sales_list:
        key, value = line.split(" ")
        sales_dict[key] = int(value)

    title = "Total sale per item: \n"
    print(title.upper())

    for key, value in sales_dict.items():
        formatted_line = f"{key.title()}"
        formatted_line = f"{formatted_line.ljust(15)}{value}"
        print(formatted_line)
    return 200

# Function takes in user input and matches in a dictionary to find total 
# items sold for that item
def total_specific_item(item):
    # properly format user input to match keys
    item = item.strip().lower()
    item = item.title()

    # Obtaines sales data from file and populates dictionary
    sales_list = []
    sales_list = get_sales_list(processed_file)
    sales_dict = {}
    for line in sales_list:
        key, value = line.split(" ")
        sales_dict[key] = int(value)

    # Gets total sales for item, if item not found 0 is returned 
    value = sales_dict.get(item, 0)
    return value


# Function reads processed data from file and displays formatted histogram
def display_histogram():
    sales_dict = {}
    sales_list = get_sales_list(processed_file)
    for line in sales_list:
        key, value = line.split(" ")
        sales_dict[key] = int(value)
    title = "Histogram of total sales: \n"
    print(title.upper())

    for key, value in sales_dict.items():
        formatted_line = f"{key.title()}"
        # Formatted line to give histogram a more accurate zero line
        formatted_line = f"{formatted_line.ljust(16)}{value * '$'}"
        print(formatted_line)
    return 200

# Function read sales data and process it once and writes to frequency.dat
def prepare_sales_data():
    sales_list = []
    sales_list = get_sales_list(sales_file)
    sales_dict = {}
    sales_dict = process_sales_data(sales_list)
    write_output_file(sales_dict, processed_file)
    return


# Function for counting each item
def process_sales_data(sales_list):
    sales_dict = {}
    for product in sales_list:
        sales_dict[product] = (
            1 if product not in sales_dict.keys() else sales_dict[product] + 1
        )
    return sales_dict
