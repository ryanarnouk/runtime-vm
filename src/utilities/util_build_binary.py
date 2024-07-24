# This utility is used to take the hex that matches a human readable UTF-8 encoded
# series of hexits to a binary file that can be read by the system and opened by the runtime.
# In essence, this creates the "assembled" version that is not human readable.

# The examples will continue to be written in UTF-8 encoded hexits, but the actual runtime runs
# through this first

# Use hexdump to verify the contents of the binary file
# hexdump -C <filename>

def hex_to_binary(input_file, output_file):
    """Converts a hex string to a binary file.

    Args:
        input_file: A file containing the disassembled bytecode in a UTF-8 encoded hex string.
        output_file: File where the binary data will be read to (for the interpreter to run the bytecode on).

    Raises:
        ValueError: If the input string is not valid hex.
    """

    # Read the hex data from the input file
    try:
        with open(input_file, "r", encoding="utf-8") as f:
            hex_string = f.read().strip().replace(" ", "")
    except FileNotFoundError:
        print(f"Error: Input file '{input_file}' not found")
        return

    print(hex_string)

    # Validate input
    if not all(c in "0123456789abcdefABCDEF " for c in hex_string):
        print(hex_string)
        raise ValueError("Invalid hex string format")

    # Convert hex string to byte array
    binary_data = bytearray(int(hex_string[i:i+2], 16) for i in range(0, len(hex_string), 2))

    try:
        with open(output_file, "wb") as f:
            f.write(binary_data)
    except OSError as e:
            print(f"Error writing to output file '{output_file}': {e}")
            return

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 3:
        print("Usage: python util_build_binary.py <input_file> <output_file>")
        exit(1)
    input_file, output_file = sys.argv[1], sys.argv[2]
    hex_to_binary(input_file, output_file)
