# DataStructureByC 🚀

A lightweight, efficient, and generic Data Structure library implemented in pure C from scratch.

![Language](https://img.shields.io/badge/language-C99-blue.svg)
![Build](https://img.shields.io/badge/build-CMake-green.svg)
![License](https://img.shields.io/badge/license-MIT-orange.svg)

## 📖 Introduction

**DataStructureByC** is a project dedicated to implementing core data structures manually to understand the underlying principles of memory management, pointer manipulation, and algorithm optimization.

It uses a **generic design** (`void *`) to store any type of data and features modern C practices like **macro optimizations**, **safe memory management**, and **adapter patterns**.

## ✨ Features implemented

### 1. Vector (Dynamic Array) 📦
- Automatic memory expansion (Growth factor: 1.5x - 2x).
- Random access with $O(1)$ complexity.
- Support for any data type via `void*`.

### 2. Doubly Linked List 🔗
- Efficient insertion and deletion at both ends ($O(1)$).
- Safe node memory management.
- Implements `prev` and `next` pointer navigation.

### 3. Stack 🥞
- **Adapter Pattern**: Built on top of `Vector` for code reuse.
- LIFO (Last In, First Out) logic.
- Safe boundary checks (no underflow/overflow).

### 4. Queue 🚶‍♂️
- **Adapter Pattern**: Built on top of `List` for efficiency.
- FIFO (First In, First Out) logic.
- Standard "Push Back, Pop Front" operations.

### 5. HashMap (Hash Table) 🗺️
- **Architecture**: Bucket Array + Linked List (Chaining) to handle collisions.
- **Algorithm**: Uses the classic **djb2** hash algorithm for string keys (implemented via macros for performance).
- **Auto-Resizing**: Automatically expands capacity when `Load Factor > 0.75`.
- Leak-free design with deep copy for keys.

## 🛠️ Build & Run

This project uses **CMake** as the build system.

### Prerequisites
- GCC or MinGW compiler
- CMake (3.10+)

### Compilation

```bash
# 1. Create a build directory
mkdir build
cd build

# 2. Generate Makefiles
cmake ..

# 3. Compile everything (Static Library + Tests)
cmake --build .