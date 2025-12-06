## Project Overview

This project simulates a simple **bank client management system** that allows managing client records through a **menu-driven console interface**.
The system stores client data in a text file and supports full **CRUD operations** (Create, Read, Update, Delete).

---

## Key Features

- ✅ Add new clients with **unique account numbers**
- ✅ Display all clients in a **formatted table**
- ✅ Search for a client by **account number**
- ✅ Update existing client information
- ✅ Delete clients with **user confirmation**
- ✅ Persistent data storage using **text files**

---

## Technologies & Concepts Used

### Language
- **C++**

### Core Concepts
- Structs & data modeling
- Functions & modular programming
- Enums for menu control
- Vectors & dynamic data handling
- File handling (read / write / overwrite)
- String manipulation & parsing
- Input validation & user confirmation
- Clean console output using `<iomanip>`

---

## Data Handling

- Client data is stored in a text file using a **custom separator**
- Records are converted between **text lines** and **structured objects**
- Deleted records are handled using a **soft delete flag** followed by file rewrite
