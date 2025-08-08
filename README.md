# Name Mangling

This project demonstrates **C++ name mangling** across different compilers and platforms (GCC, Clang, MSVC) by:

- Creating a class with **overloaded** and **templated** methods
- Compiling it with **CMake**
- Automatically inspecting the **mangled symbol names**
- Providing cross-platform support via `nm`, `dumpbin`, or `llvm-nm`


## Build & Run
```bash
# 1. Clone the Repository
git clone https://github.com/AniDashyan/name_mangling
cd name_mangling

# 2. Build with CMake
cmake -S . -B build
cmake --build build

# 3. Run the Executable
./build/main
```

We should see:

```
int: 42
double: 3.14
template: hello
```

---

##  Inspect Mangled Symbols

Manually inspect symbols:

### Linux/macOS

```bash
nm -C build/main | grep Foo
```

### Windows (MSVC)

```cmd
dumpbin /symbols build\CMakeFiles\main.dir\main.obj | findstr Foo
```

Or (if using LLVM):

```cmd
llvm-nm -C build\CMakeFiles\main.dir\main.obj | findstr Foo
```

##  Name Mangling: What & Why?

C++ allows features like:

* Function overloading
* Namespaces
* Templates

To support these features at the binary level, compilers **mangle** symbol names — turning them into unique, encoded strings.

### 🔧 Examples of Mangled Names

| Compiler  | Function           | Mangled Symbol                                                                                               |
| --------- | ------------------ | ------------------------------------------------------------------------------------------------------------ |
| GCC/Clang | `bar(int)`         | `_ZN7Example3Foo3barEi`                                                                                      |
| GCC/Clang | `bar(double)`      | `_ZN7Example3Foo3barEd`                                                                                      |
| MSVC      | `bar(int)`         | `?bar@Foo@Example@@QEAAXH@Z`                                                                                 |
| MSVC      | `baz<std::string>` | `??$baz@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Foo@Example@@QEAAXV?$basic_string...` |

---

## How Does It Work?

```cpp
class Foo {
    public:
        void bar(int x);
        void bar(double x);

        template<typename T>
        void baz(T val);
};
```

### Output

Each compiler outputs **different mangled names** for the same functions based on its **ABI (Application Binary Interface)**:

* GCC/Clang use the **Itanium ABI**
* MSVC uses the **Microsoft ABI**

Demangling tools (`nm -C`, `llvm-nm -C`, `dumpbin`) decode these back to human-readable form.
Would you like me to generate a ZIP package or set this up in a ready-to-fork GitHub template?
```
