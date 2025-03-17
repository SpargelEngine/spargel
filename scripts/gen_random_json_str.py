import argparse
import random
from multiprocessing import Pool
import os


def generate_json_string(size, escape_freq, escape_freq_unicode) -> str:
    if size < 0:
        raise ValueError("size must be >= 0")
    if not 0 <= escape_freq <= 1:
        raise ValueError("escape_freq must be >= 0")
    if not 0 <= escape_freq_unicode <= 1:
        raise ValueError("escape_freq_unicode must be >= 0")

    json_str = '"'  # Start with opening quote
    remaining = size - 2  # Account for opening/closing quotes

    # Escape mappings for JSON
    escapes = {
        '\n': r'\n',
        '\t': r'\t',
        '\r': r'\r',
        '\b': r'\b',
        '\f': r'\f',
        '\\': r'\\',
        '"': r'\"',
        '/': r'\/'
    }

    # Characters that don't need escaping
    safe_ascii = [chr(i) for i in range(0x20, 0x7f)
                  if chr(i) not in escapes and chr(i) != '/']

    while remaining > 0:
        if random.random() < escape_freq:
            # Handle escape sequences
            if remaining >= 6 and random.random() < escape_freq_unicode:
                # Add Unicode escape (6 chars: \uXXXX)
                json_str = json_str + r'\u%04x' % random.randint(0x0080, 0xFFFF);
                remaining -= 6
            elif remaining >= 2:
                # Add regular escape sequence
                char = random.choice(list(escapes.keys()))
                json_str = json_str + escapes[char]
                remaining -= 2
            else:
                # Fallback to safe ASCII if not enough space
                json_str = json_str + random.choice(safe_ascii)
                remaining -= 1
        else:
            # Add regular character
            json_str = json_str + random.choice(safe_ascii)
            remaining -= 1

    # Add closing quote and join string
    json_str = json_str + '"'

    return json_str


def generate_chunk(args_) -> str:
    """Generate a single JSON string using the shared parameters"""
    size, escape_freq, escape_freq_unicode = args_
    return generate_json_string(size, escape_freq, escape_freq_unicode)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Generate a large JSON string by concatenating chunks')
    parser.add_argument('size', type=int, help='Total string size')
    parser.add_argument('--chunk-size', type=int,
                        help='Max size per chunk (default=1MB). Use with --chunks for control')
    parser.add_argument('--chunks', type=int, help='Number of chunks to split into')
    parser.add_argument('--escape_freq', type=float, help='Escape character frequency (0.0-1.0, default=0.01)',
                        default=0.01)
    parser.add_argument('--escape_freq_unicode', type=float, help='Unicode escape frequency (0.0-1.0, default=0.01)',
                        default=0.01)
    parser.add_argument('--processes', type=int, help='Number of processes to use (default=CPU count)',
                        default=os.cpu_count())
    args = parser.parse_args()

    try:
        if args.size < 2:
            raise ValueError("size must be >= 2")

        total_inner = args.size - 2

        # Calculate chunk sizes based on parameters
        if args.chunks:
            if args.chunks <= 0:
                raise ValueError("chunks must > 0")
            # Distribute total_inner as evenly as possible across chunks
            base, extra = divmod(total_inner, args.chunks)
            chunk_sizes = [base + 1] * extra + [base] * (args.chunks - extra)
            chunk_sizes = [cs for cs in chunk_sizes if cs > 0]  # Remove zero-sized chunks
            num_chunks = len(chunk_sizes)
        else:
            # Use chunk-size based approach
            chunk_size = args.chunk_size if args.chunk_size else min(1024 * 1024, total_inner)
            if chunk_size <= 0:
                chunk_size = 1024 * 1024  # Default to 1MB chunks
            num_chunks = max(1, (total_inner + chunk_size - 1) // chunk_size)
            base, extra = divmod(total_inner, num_chunks)
            chunk_sizes = [base + 1] * extra + [base] * (num_chunks - extra)

        # Generate chunk args with size including quotes
        chunk_args = [(cs + 2, args.escape_freq, args.escape_freq_unicode) for cs in chunk_sizes]

        with Pool(processes=args.processes) as pool:
            chunks = pool.map(generate_chunk, chunk_args)
            inner_parts = [chunk[1:-1] for chunk in chunks]
            final_str = '"%s"' % ''.join(inner_parts)

            print(final_str, end='')

    except ValueError as e:
        print(str(e))
