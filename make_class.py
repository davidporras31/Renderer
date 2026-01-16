import os
import sys


def main():
    if len(sys.argv) > 3 or len(sys.argv) < 2:
        print("Usage: python make_class.py ClassName")
        print("or: python make_class.py ClassFile ClassName")
        return

    class_file: str = ""
    class_name: str = ""
    
    if len(sys.argv) == 2:
        class_name = sys.argv[1]
    else:
        class_file = sys.argv[1]
        class_name = sys.argv[2]

    class_h: str = f"""
#ifndef {class_name.upper()}_H
#define {class_name.upper()}_H

class {class_name} {{
private:
    // data
public:
    {class_name}();
    ~{class_name}();
}};

#endif // {class_name.upper()}_H
    """
    class_cpp = f"""
#include "../include/{class_name}.h"

{class_name}::{class_name}() {{
    // Constructor implementation
}}

{class_name}::~{class_name}() {{
    // Destructor implementation
}}
    """
    class_h_file: str = f"./include/{class_file}/{class_name}.h"
    class_cpp_file: str = f"./src/{class_file}/{class_name}.cpp"

    if os.path.exists(os.path.dirname(class_h_file)) is False:
        os.makedirs(os.path.dirname(class_h_file))
        print(f"Created directory {os.path.dirname(class_h_file)}")
    if os.path.exists(os.path.dirname(class_cpp_file)) is False:
        os.makedirs(os.path.dirname(class_cpp_file))
        print(f"Created directory {os.path.dirname(class_cpp_file)}")

    if os.path.exists(class_h_file) or os.path.exists(class_cpp_file):
        print(f"Error: {class_name}.h or {class_name}.cpp already exists.")
        return

    with open(class_h_file, "w") as f:
        f.write(class_h)

    with open(class_cpp_file, "w") as f:
        f.write(class_cpp)

if __name__ == "__main__":
    main()