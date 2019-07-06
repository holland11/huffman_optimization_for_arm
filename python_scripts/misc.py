import re

with open('char_freq.txt', 'r') as f:
	contents = f.readlines()
	chars = []
	freqs = []
	result = ""
	for line in contents:
		m = re.search('(.): (\d+)', line)
		c = m.group(1)
		f = m.group(2)
		chars.append(c)
		freqs.append(int(f))
		result += c * int(int(f)/100)
		
	print(result)