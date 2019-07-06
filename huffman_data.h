#ifndef _HUFFMAN_DATA_H_
#define _HUFFMAN_DATA_H_

/*
	tree 0 has height 0 and 1 nodes
	tree 1 has height 1 and 3 nodes
	tree 2 has height 1 and 3 nodes
	tree 3 has height 12 and 39 nodes
	tree 4 has height 3 and 7 nodes
	tree 5 has height 3 and 7 nodes
	tree 6 has height 0 and 1 nodes
	tree 7 has height 25 and 187 nodes
	
	Knowing this, we can make each subtree (except tree 7) into a single array that 
		contains every leaf node in the subtree.
	The array will be 2^height.
	If a leaf node is not at the full depth of the tree, then it will be accessible
		from every index below it.
		For example, if a leaf is located at 01, and the height of the subtree is 3, 
			then 010 and 011 (array[2] and array[3]) will both point to the leaf node 01.
			There will need to be some kind of variable which tells the program to only consume
				the 01 and to save the 3rd bit for the next 'round'.
				
	Start by taking 3 bits to figure out which subtree we are in.
	If in subtree 0 or 6, we know we are already at a leaf node.
	If in subtree 1 or 2, we know to take 1 bit to get to a leaf node.
	If in subtree 4 or 5, we take 3 more bits.
		From those 3 bits, we index into the array and decide how many bits to consume/save.
	If in subtree 3, we take 12 bits and decide how many need to be consumed / saved.
	
	Complications:
		-Need to take 12 bits but only have 7 left in the current u_int_32
			(fill the 'storage' variable with the 7 then continue the loop)
			(loop must start by checking the storage variable always.)
		-Need to take 12 bits but only have 7 left in the current u_int_32 and it's the last u_int_32.
			(After loop finishes, check the storage variable to see what's left.
				We can add 0s or 1s to get the correct number of bits to index into the array)
				
	vars:
	bits_required[8] (array representing the number of bits required in each subtree (index 8 is root))
	while read 32 bits into buffer
		bits_left = 32
		while true
			if bits_left < bits_required[subtree] // bits_required[8] == 3 (root)
				storage = buffer
				storage_len = bits_left
				break
			if storage_len < bits_required[subtree]
				bits_to_push = bits_required[subtree] - storage_len
				storage = storage << bits_to_push
				temp = 0xffffffff >> (32-bits_to_push)
				temp = temp & buffer // extract bits_to_push from buffer
				buffer = buffer >> bits_to_push // remove those bits from the buffer
				storage = storage | temp // put the bits from buffer onto the storage
				current_array[storage] // this is the target node
			else if storage_len >
				
*/

#define C0 { .code=237816886, .len=28 }
#define C1 { .code=237816887, .len=28 }
#define C2 { .code=237816888, .len=28 }
#define C3 { .code=237816889, .len=28 }
#define C4 { .code=237816890, .len=28 }
#define C5 { .code=237816891, .len=28 }
#define C6 { .code=237816892, .len=28 }
#define C7 { .code=237816893, .len=28 }
#define C8 { .code=237816894, .len=28 }
#define C9 { .code=237816895, .len=28 }
#define C10 { .code=58, .len=6 }
#define C11 { .code=118908416, .len=27 }
#define C12 { .code=118908417, .len=27 }
#define C13 { .code=118908418, .len=27 }
#define C14 { .code=118908419, .len=27 }
#define C15 { .code=118908420, .len=27 }
#define C16 { .code=118908421, .len=27 }
#define C17 { .code=118908422, .len=27 }
#define C18 { .code=118908423, .len=27 }
#define C19 { .code=118908424, .len=27 }
#define C20 { .code=118908425, .len=27 }
#define C21 { .code=118908426, .len=27 }
#define C22 { .code=118908427, .len=27 }
#define C23 { .code=118908428, .len=27 }
#define C24 { .code=118908429, .len=27 }
#define C25 { .code=118908430, .len=27 }
#define C26 { .code=118908431, .len=27 }
#define C27 { .code=118908432, .len=27 }
#define C28 { .code=118908433, .len=27 }
#define C29 { .code=118908434, .len=27 }
#define C30 { .code=118908435, .len=27 }
#define C31 { .code=118908436, .len=27 }
#define C32 { .code=6, .len=3 }
#define C33 { .code=904, .len=10 }
#define C34 { .code=225, .len=8 }
#define C35 { .code=928967, .len=20 }
#define C36 { .code=464485, .len=19 }
#define C37 { .code=928973, .len=20 }
#define C38 { .code=232240, .len=18 }
#define C39 { .code=504, .len=9 }
#define C40 { .code=1762, .len=12 }
#define C41 { .code=1763, .len=12 }
#define C42 { .code=3522, .len=13 }
#define C43 { .code=3715889, .len=22 }
#define C44 { .code=25, .len=6 }
#define C45 { .code=98, .len=8 }
#define C46 { .code=118, .len=7 }
#define C47 { .code=14094, .len=15 }
#define C48 { .code=16177, .len=14 }
#define C49 { .code=8090, .len=13 }
#define C50 { .code=14513, .len=14 }
#define C51 { .code=32365, .len=15 }
#define C52 { .code=29031, .len=15 }
#define C53 { .code=32364, .len=15 }
#define C54 { .code=29024, .len=15 }
#define C55 { .code=14095, .len=15 }
#define C56 { .code=14514, .len=14 }
#define C57 { .code=29025, .len=15 }
#define C58 { .code=1815, .len=11 }
#define C59 { .code=1012, .len=10 }
#define C60 { .code=118908437, .len=27 }
#define C61 { .code=928964, .len=20 }
#define C62 { .code=1857945, .len=21 }
#define C63 { .code=896, .len=10 }
#define C64 { .code=464484, .len=19 }
#define C65 { .code=199, .len=9 }
#define C66 { .code=905, .len=10 }
#define C67 { .code=441, .len=10 }
#define C68 { .code=2021, .len=11 }
#define C69 { .code=442, .len=10 }
#define C70 { .code=1820, .len=11 }
#define C71 { .code=1821, .len=11 }
#define C72 { .code=198, .len=9 }
#define C73 { .code=111, .len=8 }
#define C74 { .code=1794, .len=11 }
#define C75 { .code=1760, .len=12 }
#define C76 { .code=2020, .len=11 }
#define C77 { .code=1014, .len=10 }
#define C78 { .code=2030, .len=11 }
#define C79 { .code=2026, .len=11 }
#define C80 { .code=899, .len=10 }
#define C81 { .code=7046, .len=14 }
#define C82 { .code=2023, .len=11 }
#define C83 { .code=911, .len=10 }
#define C84 { .code=454, .len=9 }
#define C85 { .code=8089, .len=13 }
#define C86 { .code=3629, .len=12 }
#define C87 { .code=906, .len=10 }
#define C88 { .code=16183, .len=14 }
#define C89 { .code=887, .len=11 }
#define C90 { .code=58061, .len=16 }
#define C91 { .code=32352, .len=15 }
#define C92 { .code=118908438, .len=27 }
#define C93 { .code=32353, .len=15 }
#define C94 { .code=118908439, .len=27 }
#define C95 { .code=1795, .len=11 }
#define C96 { .code=118908440, .len=27 }
#define C97 { .code=8, .len=4 }
#define C98 { .code=119, .len=7 }
#define C99 { .code=47, .len=6 }
#define C100 { .code=22, .len=5 }
#define C101 { .code=0, .len=3 }
#define C102 { .code=39, .len=6 }
#define C103 { .code=38, .len=6 }
#define C104 { .code=4, .len=4 }
#define C105 { .code=3, .len=4 }
#define C106 { .code=2031, .len=11 }
#define C107 { .code=48, .len=7 }
#define C108 { .code=18, .len=5 }
#define C109 { .code=57, .len=6 }
#define C110 { .code=5, .len=4 }
#define C111 { .code=7, .len=4 }
#define C112 { .code=127, .len=7 }
#define C113 { .code=2027, .len=11 }
#define C114 { .code=30, .len=5 }
#define C115 { .code=2, .len=4 }
#define C116 { .code=10, .len=4 }
#define C117 { .code=62, .len=6 }
#define C118 { .code=54, .len=7 }
#define C119 { .code=46, .len=6 }
#define C120 { .code=898, .len=10 }
#define C121 { .code=26, .len=6 }
#define C122 { .code=886, .len=11 }
#define C123 { .code=928965, .len=20 }
#define C124 { .code=464487, .len=19 }
#define C125 { .code=928966, .len=20 }
#define C126 { .code=118908441, .len=27 }
#define C127 { .code=118908442, .len=27 }

#define N0 { .letter=101, .left=0, .right=0, .nbits=3 }
#define N1 { .letter=128, .left=8, .right=9, .nbits=3 }
#define N2 { .letter=128, .left=10, .right=11, .nbits=3 }
#define N3 { .letter=128, .left=24, .right=61, .nbits=3 }
#define N4 { .letter=128, .left=12, .right=13, .nbits=3 }
#define N5 { .letter=128, .left=18, .right=19, .nbits=3 }
#define N6 { .letter=32, .left=0, .right=0, .nbits=3 }
#define N7 { .letter=128, .left=62, .right=207, .nbits=3 }
#define N8 { .letter=115, .left=0, .right=0, .nbits=4 }
#define N9 { .letter=105, .left=0, .right=0, .nbits=4 }
#define N10 { .letter=104, .left=0, .right=0, .nbits=4 }
#define N11 { .letter=110, .left=0, .right=0, .nbits=4 }
#define N12 { .letter=97, .left=0, .right=0, .nbits=4 }
#define N13 { .letter=128, .left=14, .right=15, .nbits=4 }
#define N14 { .letter=108, .left=0, .right=0, .nbits=5 }
#define N15 { .letter=128, .left=16, .right=17, .nbits=5 }
#define N16 { .letter=103, .left=0, .right=0, .nbits=6 }
#define N17 { .letter=102, .left=0, .right=0, .nbits=6 }
#define N18 { .letter=116, .left=0, .right=0, .nbits=4 }
#define N19 { .letter=128, .left=20, .right=21, .nbits=4 }
#define N20 { .letter=100, .left=0, .right=0, .nbits=5 }
#define N21 { .letter=128, .left=22, .right=23, .nbits=5 }
#define N22 { .letter=119, .left=0, .right=0, .nbits=6 }
#define N23 { .letter=99, .left=0, .right=0, .nbits=6 }
#define N24 { .letter=128, .left=25, .right=34, .nbits=4 }
#define N25 { .letter=128, .left=26, .right=33, .nbits=5 }
#define N26 { .letter=128, .left=27, .right=28, .nbits=6 }
#define N27 { .letter=107, .left=0, .right=0, .nbits=7 }
#define N28 { .letter=128, .left=29, .right=30, .nbits=7 }
#define N29 { .letter=45, .left=0, .right=0, .nbits=8 }
#define N30 { .letter=128, .left=31, .right=32, .nbits=8 }
#define N31 { .letter=72, .left=0, .right=0, .nbits=9 }
#define N32 { .letter=65, .left=0, .right=0, .nbits=9 }
#define N33 { .letter=44, .left=0, .right=0, .nbits=6 }
#define N34 { .letter=128, .left=35, .right=36, .nbits=5 }
#define N35 { .letter=121, .left=0, .right=0, .nbits=6 }
#define N36 { .letter=128, .left=37, .right=38, .nbits=6 }
#define N37 { .letter=118, .left=0, .right=0, .nbits=7 }
#define N38 { .letter=128, .left=39, .right=60, .nbits=7 }
#define N39 { .letter=128, .left=40, .right=55, .nbits=8 }
#define N40 { .letter=128, .left=41, .right=54, .nbits=9 }
#define N41 { .letter=128, .left=42, .right=51, .nbits=10 }
#define N42 { .letter=128, .left=43, .right=44, .nbits=11 }
#define N43 { .letter=75, .left=0, .right=0, .nbits=12 }
#define N44 { .letter=128, .left=45, .right=46, .nbits=12 }
#define N45 { .letter=42, .left=0, .right=0, .nbits=13 }
#define N46 { .letter=128, .left=47, .right=48, .nbits=13 }
#define N47 { .letter=81, .left=0, .right=0, .nbits=14 }
#define N48 { .letter=128, .left=49, .right=50, .nbits=14 }
#define N49 { .letter=47, .left=0, .right=0, .nbits=15 }
#define N50 { .letter=55, .left=0, .right=0, .nbits=15 }
#define N51 { .letter=128, .left=52, .right=53, .nbits=11 }
#define N52 { .letter=40, .left=0, .right=0, .nbits=12 }
#define N53 { .letter=41, .left=0, .right=0, .nbits=12 }
#define N54 { .letter=67, .left=0, .right=0, .nbits=10 }
#define N55 { .letter=128, .left=56, .right=57, .nbits=9 }
#define N56 { .letter=69, .left=0, .right=0, .nbits=10 }
#define N57 { .letter=128, .left=58, .right=59, .nbits=10 }
#define N58 { .letter=122, .left=0, .right=0, .nbits=11 }
#define N59 { .letter=89, .left=0, .right=0, .nbits=11 }
#define N60 { .letter=73, .left=0, .right=0, .nbits=8 }
#define N61 { .letter=111, .left=0, .right=0, .nbits=4 }
#define N62 { .letter=128, .left=63, .right=202, .nbits=4 }
#define N63 { .letter=128, .left=64, .right=201, .nbits=5 }
#define N64 { .letter=128, .left=65, .right=76, .nbits=6 }
#define N65 { .letter=128, .left=66, .right=75, .nbits=7 }
#define N66 { .letter=128, .left=67, .right=72, .nbits=8 }
#define N67 { .letter=128, .left=68, .right=69, .nbits=9 }
#define N68 { .letter=63, .left=0, .right=0, .nbits=10 }
#define N69 { .letter=128, .left=70, .right=71, .nbits=10 }
#define N70 { .letter=74, .left=0, .right=0, .nbits=11 }
#define N71 { .letter=95, .left=0, .right=0, .nbits=11 }
#define N72 { .letter=128, .left=73, .right=74, .nbits=9 }
#define N73 { .letter=120, .left=0, .right=0, .nbits=10 }
#define N74 { .letter=80, .left=0, .right=0, .nbits=10 }
#define N75 { .letter=34, .left=0, .right=0, .nbits=8 }
#define N76 { .letter=128, .left=77, .right=194, .nbits=7 }
#define N77 { .letter=128, .left=78, .right=81, .nbits=8 }
#define N78 { .letter=128, .left=79, .right=80, .nbits=9 }
#define N79 { .letter=33, .left=0, .right=0, .nbits=10 }
#define N80 { .letter=66, .left=0, .right=0, .nbits=10 }
#define N81 { .letter=128, .left=82, .right=83, .nbits=9 }
#define N82 { .letter=87, .left=0, .right=0, .nbits=10 }
#define N83 { .letter=128, .left=84, .right=193, .nbits=10 }
#define N84 { .letter=128, .left=85, .right=192, .nbits=11 }
#define N85 { .letter=128, .left=86, .right=91, .nbits=12 }
#define N86 { .letter=128, .left=87, .right=90, .nbits=13 }
#define N87 { .letter=128, .left=88, .right=89, .nbits=14 }
#define N88 { .letter=54, .left=0, .right=0, .nbits=15 }
#define N89 { .letter=57, .left=0, .right=0, .nbits=15 }
#define N90 { .letter=50, .left=0, .right=0, .nbits=14 }
#define N91 { .letter=128, .left=92, .right=93, .nbits=13 }
#define N92 { .letter=56, .left=0, .right=0, .nbits=14 }
#define N93 { .letter=128, .left=94, .right=191, .nbits=14 }
#define N94 { .letter=128, .left=95, .right=190, .nbits=15 }
#define N95 { .letter=128, .left=96, .right=105, .nbits=16 }
#define N96 { .letter=128, .left=97, .right=98, .nbits=17 }
#define N97 { .letter=38, .left=0, .right=0, .nbits=18 }
#define N98 { .letter=128, .left=99, .right=102, .nbits=18 }
#define N99 { .letter=128, .left=100, .right=101, .nbits=19 }
#define N100 { .letter=61, .left=0, .right=0, .nbits=20 }
#define N101 { .letter=123, .left=0, .right=0, .nbits=20 }
#define N102 { .letter=128, .left=103, .right=104, .nbits=19 }
#define N103 { .letter=125, .left=0, .right=0, .nbits=20 }
#define N104 { .letter=35, .left=0, .right=0, .nbits=20 }
#define N105 { .letter=128, .left=106, .right=109, .nbits=17 }
#define N106 { .letter=128, .left=107, .right=108, .nbits=18 }
#define N107 { .letter=64, .left=0, .right=0, .nbits=19 }
#define N108 { .letter=36, .left=0, .right=0, .nbits=19 }
#define N109 { .letter=128, .left=110, .right=189, .nbits=18 }
#define N110 { .letter=128, .left=111, .right=188, .nbits=19 }
#define N111 { .letter=128, .left=112, .right=187, .nbits=20 }
#define N112 { .letter=128, .left=113, .right=186, .nbits=21 }
#define N113 { .letter=128, .left=114, .right=145, .nbits=22 }
#define N114 { .letter=128, .left=115, .right=130, .nbits=23 }
#define N115 { .letter=128, .left=116, .right=123, .nbits=24 }
#define N116 { .letter=128, .left=117, .right=120, .nbits=25 }
#define N117 { .letter=128, .left=118, .right=119, .nbits=26 }
#define N118 { .letter=11, .left=0, .right=0, .nbits=27 }
#define N119 { .letter=12, .left=0, .right=0, .nbits=27 }
#define N120 { .letter=128, .left=121, .right=122, .nbits=26 }
#define N121 { .letter=13, .left=0, .right=0, .nbits=27 }
#define N122 { .letter=14, .left=0, .right=0, .nbits=27 }
#define N123 { .letter=128, .left=124, .right=127, .nbits=25 }
#define N124 { .letter=128, .left=125, .right=126, .nbits=26 }
#define N125 { .letter=15, .left=0, .right=0, .nbits=27 }
#define N126 { .letter=16, .left=0, .right=0, .nbits=27 }
#define N127 { .letter=128, .left=128, .right=129, .nbits=26 }
#define N128 { .letter=17, .left=0, .right=0, .nbits=27 }
#define N129 { .letter=18, .left=0, .right=0, .nbits=27 }
#define N130 { .letter=128, .left=131, .right=138, .nbits=24 }
#define N131 { .letter=128, .left=132, .right=135, .nbits=25 }
#define N132 { .letter=128, .left=133, .right=134, .nbits=26 }
#define N133 { .letter=19, .left=0, .right=0, .nbits=27 }
#define N134 { .letter=20, .left=0, .right=0, .nbits=27 }
#define N135 { .letter=128, .left=136, .right=137, .nbits=26 }
#define N136 { .letter=21, .left=0, .right=0, .nbits=27 }
#define N137 { .letter=22, .left=0, .right=0, .nbits=27 }
#define N138 { .letter=128, .left=139, .right=142, .nbits=25 }
#define N139 { .letter=128, .left=140, .right=141, .nbits=26 }
#define N140 { .letter=23, .left=0, .right=0, .nbits=27 }
#define N141 { .letter=24, .left=0, .right=0, .nbits=27 }
#define N142 { .letter=128, .left=143, .right=144, .nbits=26 }
#define N143 { .letter=25, .left=0, .right=0, .nbits=27 }
#define N144 { .letter=26, .left=0, .right=0, .nbits=27 }
#define N145 { .letter=128, .left=146, .right=161, .nbits=23 }
#define N146 { .letter=128, .left=147, .right=154, .nbits=24 }
#define N147 { .letter=128, .left=148, .right=151, .nbits=25 }
#define N148 { .letter=128, .left=149, .right=150, .nbits=26 }
#define N149 { .letter=27, .left=0, .right=0, .nbits=27 }
#define N150 { .letter=28, .left=0, .right=0, .nbits=27 }
#define N151 { .letter=128, .left=152, .right=153, .nbits=26 }
#define N152 { .letter=29, .left=0, .right=0, .nbits=27 }
#define N153 { .letter=30, .left=0, .right=0, .nbits=27 }
#define N154 { .letter=128, .left=155, .right=158, .nbits=25 }
#define N155 { .letter=128, .left=156, .right=157, .nbits=26 }
#define N156 { .letter=31, .left=0, .right=0, .nbits=27 }
#define N157 { .letter=60, .left=0, .right=0, .nbits=27 }
#define N158 { .letter=128, .left=159, .right=160, .nbits=26 }
#define N159 { .letter=92, .left=0, .right=0, .nbits=27 }
#define N160 { .letter=94, .left=0, .right=0, .nbits=27 }
#define N161 { .letter=128, .left=162, .right=171, .nbits=24 }
#define N162 { .letter=128, .left=163, .right=166, .nbits=25 }
#define N163 { .letter=128, .left=164, .right=165, .nbits=26 }
#define N164 { .letter=96, .left=0, .right=0, .nbits=27 }
#define N165 { .letter=126, .left=0, .right=0, .nbits=27 }
#define N166 { .letter=128, .left=167, .right=168, .nbits=26 }
#define N167 { .letter=127, .left=0, .right=0, .nbits=27 }
#define N168 { .letter=128, .left=169, .right=170, .nbits=27 }
#define N169 { .letter=0, .left=0, .right=0, .nbits=28 }
#define N170 { .letter=1, .left=0, .right=0, .nbits=28 }
#define N171 { .letter=128, .left=172, .right=179, .nbits=25 }
#define N172 { .letter=128, .left=173, .right=176, .nbits=26 }
#define N173 { .letter=128, .left=174, .right=175, .nbits=27 }
#define N174 { .letter=2, .left=0, .right=0, .nbits=28 }
#define N175 { .letter=3, .left=0, .right=0, .nbits=28 }
#define N176 { .letter=128, .left=177, .right=178, .nbits=27 }
#define N177 { .letter=4, .left=0, .right=0, .nbits=28 }
#define N178 { .letter=5, .left=0, .right=0, .nbits=28 }
#define N179 { .letter=128, .left=180, .right=183, .nbits=26 }
#define N180 { .letter=128, .left=181, .right=182, .nbits=27 }
#define N181 { .letter=6, .left=0, .right=0, .nbits=28 }
#define N182 { .letter=7, .left=0, .right=0, .nbits=28 }
#define N183 { .letter=128, .left=184, .right=185, .nbits=27 }
#define N184 { .letter=8, .left=0, .right=0, .nbits=28 }
#define N185 { .letter=9, .left=0, .right=0, .nbits=28 }
#define N186 { .letter=43, .left=0, .right=0, .nbits=22 }
#define N187 { .letter=62, .left=0, .right=0, .nbits=21 }
#define N188 { .letter=37, .left=0, .right=0, .nbits=20 }
#define N189 { .letter=124, .left=0, .right=0, .nbits=19 }
#define N190 { .letter=90, .left=0, .right=0, .nbits=16 }
#define N191 { .letter=52, .left=0, .right=0, .nbits=15 }
#define N192 { .letter=86, .left=0, .right=0, .nbits=12 }
#define N193 { .letter=58, .left=0, .right=0, .nbits=11 }
#define N194 { .letter=128, .left=195, .right=196, .nbits=8 }
#define N195 { .letter=84, .left=0, .right=0, .nbits=9 }
#define N196 { .letter=128, .left=197, .right=200, .nbits=9 }
#define N197 { .letter=128, .left=198, .right=199, .nbits=10 }
#define N198 { .letter=70, .left=0, .right=0, .nbits=11 }
#define N199 { .letter=71, .left=0, .right=0, .nbits=11 }
#define N200 { .letter=83, .left=0, .right=0, .nbits=10 }
#define N201 { .letter=109, .left=0, .right=0, .nbits=6 }
#define N202 { .letter=128, .left=203, .right=204, .nbits=5 }
#define N203 { .letter=10, .left=0, .right=0, .nbits=6 }
#define N204 { .letter=128, .left=205, .right=206, .nbits=6 }
#define N205 { .letter=46, .left=0, .right=0, .nbits=7 }
#define N206 { .letter=98, .left=0, .right=0, .nbits=7 }
#define N207 { .letter=128, .left=208, .right=209, .nbits=4 }
#define N208 { .letter=114, .left=0, .right=0, .nbits=5 }
#define N209 { .letter=128, .left=210, .right=211, .nbits=5 }
#define N210 { .letter=117, .left=0, .right=0, .nbits=6 }
#define N211 { .letter=128, .left=212, .right=247, .nbits=6 }
#define N212 { .letter=128, .left=213, .right=236, .nbits=7 }
#define N213 { .letter=128, .left=214, .right=215, .nbits=8 }
#define N214 { .letter=39, .left=0, .right=0, .nbits=9 }
#define N215 { .letter=128, .left=216, .right=219, .nbits=9 }
#define N216 { .letter=128, .left=217, .right=218, .nbits=10 }
#define N217 { .letter=76, .left=0, .right=0, .nbits=11 }
#define N218 { .letter=68, .left=0, .right=0, .nbits=11 }
#define N219 { .letter=128, .left=220, .right=235, .nbits=10 }
#define N220 { .letter=128, .left=221, .right=228, .nbits=11 }
#define N221 { .letter=128, .left=222, .right=227, .nbits=12 }
#define N222 { .letter=128, .left=223, .right=226, .nbits=13 }
#define N223 { .letter=128, .left=224, .right=225, .nbits=14 }
#define N224 { .letter=91, .left=0, .right=0, .nbits=15 }
#define N225 { .letter=93, .left=0, .right=0, .nbits=15 }
#define N226 { .letter=48, .left=0, .right=0, .nbits=14 }
#define N227 { .letter=85, .left=0, .right=0, .nbits=13 }
#define N228 { .letter=128, .left=229, .right=230, .nbits=12 }
#define N229 { .letter=49, .left=0, .right=0, .nbits=13 }
#define N230 { .letter=128, .left=231, .right=234, .nbits=13 }
#define N231 { .letter=128, .left=232, .right=233, .nbits=14 }
#define N232 { .letter=53, .left=0, .right=0, .nbits=15 }
#define N233 { .letter=51, .left=0, .right=0, .nbits=15 }
#define N234 { .letter=88, .left=0, .right=0, .nbits=14 }
#define N235 { .letter=82, .left=0, .right=0, .nbits=11 }
#define N236 { .letter=128, .left=237, .right=242, .nbits=8 }
#define N237 { .letter=128, .left=238, .right=239, .nbits=9 }
#define N238 { .letter=59, .left=0, .right=0, .nbits=10 }
#define N239 { .letter=128, .left=240, .right=241, .nbits=10 }
#define N240 { .letter=79, .left=0, .right=0, .nbits=11 }
#define N241 { .letter=113, .left=0, .right=0, .nbits=11 }
#define N242 { .letter=128, .left=243, .right=244, .nbits=9 }
#define N243 { .letter=77, .left=0, .right=0, .nbits=10 }
#define N244 { .letter=128, .left=245, .right=246, .nbits=10 }
#define N245 { .letter=78, .left=0, .right=0, .nbits=11 }
#define N246 { .letter=106, .left=0, .right=0, .nbits=11 }
#define N247 { .letter=112, .left=0, .right=0, .nbits=7 }

#endif