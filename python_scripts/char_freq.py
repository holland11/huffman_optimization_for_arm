import glob

def main():
	path = './txt_files/pg-*.txt'
	char_count = {}
	for i in range(128):
		char_count[i] = 0
	for filename in glob.glob(path):
		with open(filename, 'r') as f:
			contents = f.read()
			for c in contents:
				if is_letter(c):
					char_count[ord(c)] += 1
	li = dict_to_list_of_tuples(char_count)
	li = sort_li_by_second_element(li)
	display_list(li)
	
	
	for i in range(128):
		print(str(char_count[i]), end=", ")
	
	return
	
def display_list(li):
	for tup in li:
		print("{}: {}".format(tup[0],tup[1]))
	for tup in li:
		print("{}".format(tup[0]), end=" ")
	print(" ")
	return
	
def dict_to_list_of_tuples(kvs):
	result = [(k,v) for k,v in kvs.items()]
	return result
	
def sort_li_by_second_element(kvs):
	kvs.sort(key=lambda tup: tup[1], reverse=True)
	return kvs
	
def is_letter(c):
	# true if c is a letter or space or new line or period or comma
	return (ord(c)>=0 and ord(c)<=127)
	
if __name__ == "__main__":
	main()