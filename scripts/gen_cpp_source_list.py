#!/usr/bin/env python3
import sys
import json

def filter(path: str) -> bool:
    in_build_dir = "build" in path
    return not in_build_dir

def main():
    if len(sys.argv) < 2:
        print("Usage: gen_cpp_source_list.py <compile_commands.json>")
        sys.exit(1)
    
    json_path = sys.argv[1]
    
    try:
        with open(json_path, 'r') as f:
            compile_commands = json.load(f)
    except FileNotFoundError:
        print(f"Error: File not found - {json_path}")
        sys.exit(1)
    except json.JSONDecodeError:
        print(f"Error: Invalid JSON in {json_path}")
        sys.exit(1)
    
    for entry in compile_commands:
        path = entry.get('file', '')
        if filter(path):
            print(path)

if __name__ == "__main__":
    main()
