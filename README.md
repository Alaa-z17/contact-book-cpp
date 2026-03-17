# 📒 Contact Book — C++

A console-based Contact Book app built in **C++** demonstrating
advanced concepts of **Functional & Procedural Programming**.

---

## 🎯 Learning Objectives

- Vectors for dynamic contact management
- Pointers for search and update operations
- Recursion — Merge Sort for alphabetical sorting
- File I/O — save and load contacts from file
- String manipulation with `substr`, `find`, `tolower`
- Input validation using custom header libraries
- Namespaces for code organization
- Separation of concerns with header files

---

## 🕹️ Features

- 📋 List all contacts
- ➕ Add new contact with validation
- ❌ Delete contact with confirmation
- ✏️ Update existing contact
- 🔍 Find contact by name or phone
- 🔤 Sort contacts A-Z using Merge Sort
- 🗑️ Clear all contacts with confirmation
- 💾 Auto-save contacts to file

---

## 🏗️ Project Architecture

```
main()
 └── RunContactBook()
      ├── LoadContactsFromFile()
      └── Menu Loop
           ├── PrintContactList()
           ├── AddContact()
           │    ├── ReadFirstName()
           │    ├── ReadLastName()
           │    ├── ReadPhone()
           │    │    └── ValidationLib::IsValidPhone()
           │    ├── ReadEmail()
           │    │    └── ValidationLib::IsValidEmail()
           │    └── ReadAddress()
           ├── DeleteContact()
           │    └── FindContact()
           │         ├── FindContactByName()
           │         └── FindContactByPhone()
           ├── UpdateContact()
           │    └── FindContact()
           ├── ShowFindContact()
           │    └── PrintContactCard()
           ├── SortContacts()         ← Recursive Merge Sort
           │    └── MergeContacts()
           └── SaveContactsToFile()
           ├── ClearAllContacts()
```

---

## 💡 Key Concepts

| Concept        | Where in Code                                    |
| -------------- | ------------------------------------------------ |
| Enums          | `enSearchBy`, `enMainMenuChoice`                 |
| Structs        | `stContact`                                      |
| Vectors        | `vContacts`                                      |
| Pointers       | `FindContactByName()`, `FindContactByPhone()`    |
| Recursion      | `SortContacts()` — Merge Sort                    |
| File I/O       | `SaveContactsToFile()`, `LoadContactsFromFile()` |
| Namespaces     | `ValidationLib`, `UtilityLib`                    |
| String Methods | `find()`, `substr()`, `tolower()`                |
| Header Files   | `ValidationLib.h`, `UtilityLib.h`                |

## 📁 File Structure

```
contact-book-cpp/
├── .gitignore
├── README.md
├── LICENSE
├── contact-book-cpp.slnx
└── contact-book-cpp/
    ├── contact-book-cpp.cpp
    ├── ValidationLib.h
    ├── UtilityLib.h
    ├── contact-book-cpp.vcxproj
    └── contact-book-cpp.vcxproj.filters
```

> 📝 `Contacts.txt` is auto-generated when you add your first contact.
> It is excluded from version control via `.gitignore`.

---

## 🔧 Build & Run

**Open in Visual Studio**

```
double click: contact-book-cpp.slnx
Ctrl + F5
```

**Windows (MinGW / g++)**

```bash
g++ contact-book-cpp.cpp -o contacts.exe
./contacts.exe
```

---

## 👤 Author

Built as a learning exercise in C++ Procedural Programming.

---

## 📄 License

MIT License
