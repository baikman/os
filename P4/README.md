# P4 - Steganography
    This program encodes any PNG with any message provided by the user.

    To compile:
        `g++ steg.cpp lodepng.cpp -o steg.exe`
    To run:
        Encode mode:
            ./steg.exe -e <original image name> <modified image name> [input ASCII text file name]
            Providing an input file name is not necessary.
            If the user does not select an input file, they will be prompted to type it in using the CLI.
            Example: ./steg.exe -e brandon.png newbrandon.png input.txt
        Decode mode:
            ./steg.exe -d <modified image name> [output ASCII text file name]
            Providing an output file name is not necessary.
            If the user does not select an output file, the decoded text will print to the console.
            Example: ./steg.exe -d newbrandon.png output.txt