import os
import subprocess
import sys

def run_tests():
    """
    Runs the cub3D executable against all maps in the maps/invalid directory
    and checks if the executable correctly returns an error status.
    """
    executable = "./cub3D"
    invalid_maps_dir = "maps/invalid"
    passed_tests = 0
    failed_tests = 0

    if not os.path.exists(executable):
        print(f"Error: Executable '{'./cub3D'}' not found. Please compile the project first.")
        sys.exit(1)

    if not os.path.isdir(invalid_maps_dir):
        print(f"Error: Directory '{'maps/invalid'}' not found.")
        sys.exit(1)

    map_files = sorted([f for f in os.listdir(invalid_maps_dir)])

    print(f"--- Running Invalid Map Tests ---")
    for map_file in map_files:
        map_path = os.path.join(invalid_maps_dir, map_file)
        command = [executable, map_path]
        
        try:
            result = subprocess.run(command, capture_output=True, text=True, timeout=5)
            
            # Expecting a non-zero exit code for invalid maps
            if result.returncode != 0:
                print(f"\033[92m✅ PASS:\033[0m {map_file}")
                passed_tests += 1
            else:
                print(f"\033[91m❌ FAIL:\033[0m {map_file} (Exited with code 0, expected error)")
                failed_tests += 1
                
        except subprocess.TimeoutExpired:
            print(f"\033[91m❌ FAIL:\033[0m {map_file} (Test timed out)")
            failed_tests += 1
        except Exception as e:
            print(f"\033[91m❌ FAIL:\033[0m {map_file} (An error occurred: {e})")
            failed_tests += 1
            
    print("\n--- Test Summary ---")
    print(f"Passed: {passed_tests}, Failed: {failed_tests}")
    print("--------------------")

    if failed_tests > 0:
        sys.exit(1)

if __name__ == "__main__":
    run_tests()
