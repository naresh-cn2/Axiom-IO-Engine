import ctypes
import time

# 1. Load your high-performance C library
c_lib = ctypes.CDLL("./libfastlog.so")

# 2. Tell Python what type of data the function returns (long) 
# and what it takes (two strings/bytes)
c_lib.count_errors.restype = ctypes.c_long
c_lib.count_errors.argtypes = [ctypes.c_char_p, ctypes.c_char_p]

print("Starting Hybrid Engine (Python + C)...")
start_time = time.time()

# 3. Call your C-Engine from inside Python
# We use 'b' prefix because C expects raw bytes, not Python strings
result = c_lib.count_errors(b"server_logs.txt", b" 500 ")

end_time = time.time()
print(f"Found {result} Errors.")
print(f"Hybrid Time: {end_time - start_time:.4f} seconds")
