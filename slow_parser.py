import time

print("Starting Python line-by-line read...")
start_time = time.time()
error_count = 0

with open("server_logs.txt", "r") as f:
    for line in f:
        if " 500 " in line:
            error_count += 1

print(f"Found {error_count} Server Errors (500).")
print(f"Time taken: {time.time() - start_time:.2f} seconds")

