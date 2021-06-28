AES

NAME
		aes - perform the Rijndael cipher

SYNOPSIS
		aes -k -t [OPTION]... 

DESCRIPTION
		Perform the Rijndael cipher on a string of hexadecimal characters. 

		-c, --cbc IV
				use CBC mode with an IV as an initialization vector. IV must
				be 16 bytes in length. (An IV of all 0s is equiv. to no IV)

		-d		decrypt

		-k KEY	
				use KEY as a key. KEY must be 16, 24, or 32 bytes in length.

		-t TEXT 
				use TEXT as the plain/ciphertext in string form.

		The KEY and TEXT arguments must be in hexadecimal form with no breaks
		or spaces. 

	
	Exit status:
		0		if OK
		1		invalid invocation
		syssegv if I messed something up

SAMPLE INVOCATION 
		aes -k ABCDEF1234567890ABCDEFG1234567890 -t ABCDEF1234567890ABCDEFG1234567890

COMPILATION
		Compile all .c files into a single executable. Example:

			gcc -o aes *.c

FOR PROF. HART
		Regarding ECB mode: When I was looking up how to do ECB mode, I read
		that it needed an initialization vector (IV), but this wasn't on the
		class slides, and wasn't implemented in the online test tool. For the
		test runs we were required to submit, I used an IV of all 0s, which
		is equivalent to having none (like in the test website).

		Most of the documentation for functions behavior is in the relevant .h
		file. Comments in code explain implentation, not functionality. 

		The various non-code deliverables can be found in the "deliverables" 
		directory. The analysis of secrecy can be found in the file 
		"secrecy_analysis.txt"

		Thank you very much for giving me an extension on this project.

AUTHOR
		Joshua Kirkham (joshk21)
	
