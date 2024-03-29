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

AUTHOR
		Joshua Kirkham (joshk21)
	
