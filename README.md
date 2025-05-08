# 🚀 C Project Overview

## 📝 Project Summary

This project, written in C, is designed for performance and correctness. While the problem statement is provided in detail in the `enunciado.md` file, the project involves reading structured inputs, performing algorithmic computations, and producing validated outputs — likely in the context of systems or algorithmic programming.

The build is optimized and adheres to strict compilation flags to ensure code quality and error checking.

---

## ⚙️ How to Compile

Open a terminal in the root directory of the project and run:

```bash
gcc -O3 -Wall -Wextra -Werror -Wno-unused-result -o proj1 *.c
```

### What each flag means:

- `-O3` – Enables high-level optimizations for performance.
- `-Wall` – Activates most warning messages.
- `-Wextra` – Enables extra warning messages not included in `-Wall`.
- `-Werror` – Treats all warnings as errors (forces cleaner code).
- `-Wno-unused-result` – Suppresses warnings for ignored return values (often useful for scanf/fgets).
- `-o proj1` – Names the output binary `proj1`.
- `*.c` – Compiles all `.c` files in the directory.

---

## 🧪 Running Public Tests

After compiling the project, navigate to the `public-tests` directory and run:

```bash
cd public-tests
make
```

This command will execute the `Makefile` provided in the test folder, typically running all available public test cases against your compiled program.

Make sure the binary `proj1` exists in the parent directory or as specified in the `Makefile`.

---
