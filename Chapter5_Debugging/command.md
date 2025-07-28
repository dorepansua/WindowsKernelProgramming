# WinDbg Common Commands Cheat Sheet

This guide organizes the most frequently used WinDbg commands into categories for **kernel debugging**.

---

## 1. Process & Thread Management
| Command                         | Description                                             |
|--------------------------------|---------------------------------------------------------|
| `!process 0 0`                 | List all processes in the system                       |
| `.process /p /r <EPROCESS>`    | Switch current process context (reload symbols)        |
| `~`                            | List all threads in current process                    |
| `~#`                           | Show current thread (marked with `.`)                  |
| `~<n>s`                        | Switch to thread number `n`                            |
| `!thread`                      | Display info about the current thread                  |
| `!teb`                         | Display TEB of the current thread                      |

---

## 2. Modules & Symbols
| Command               | Description                                              |
|-----------------------|----------------------------------------------------------|
| `lm`                 | List loaded modules (DLLs, drivers, EXEs)               |
| `.symfix`            | Set symbol path to Microsoft Symbol Server              |
| `.sympath`           | Show or set the symbol path                             |
| `.reload /f`         | Force reload of all symbols                             |
| `.reload /user`      | Reload user-mode symbols only                           |

## 3. Memory & Data Inspection
| Command                | Description                                             |
|------------------------|---------------------------------------------------------|
| `db <addr>`           | Display bytes at memory address                         |
| `du <addr>`           | Display Unicode string                                  |
| `dd <addr>`           | Display DWORD (32-bit) values                           |
| `dq <addr>`           | Display QWORD (64-bit) values                           |
| `dt <module>!<struct>`| Display structure definition at address                 |
| `du @rcx`             | Display Unicode string at address stored in RCX         |

---

## 4. Disassembly & Execution Control
| Command                | Description                                             |
|------------------------|---------------------------------------------------------|
| `u <addr>`            | Unassemble instructions at address                      |
| `p`                   | Step over instruction                                   |
| `t`                   | Step into instruction                                   |
| `g`                   | Continue execution                                      |
| `bp <addr>`           | Set breakpoint at address                               |
| `bl`                  | List all breakpoints                                    |
| `bc *`                | Clear all breakpoints                                   |

---

## 5. System & Driver Info
| Command                | Description                                             |
|------------------------|---------------------------------------------------------|
| `!drivers`            | List all loaded drivers                                 |
| `!handle`             | Show open handles                                       |
| `!verifier`           | Display driver verifier settings                        |

---

## 6. Debugger Utility Commands
| Command                | Description                                             |
|------------------------|---------------------------------------------------------|
| `.cls` *(WinDbg Preview)* | Clear command window output                          |
| `.reload`             | Reload all modules and symbols                          |
| `.help`               | Display WinDbg help                                     |

---

### ✅ Tips:
- Use **`@register`** to reference a CPU register in commands (e.g., `du @rcx`).
- Commands starting with `.` = Meta commands (affect debugger, not target).
- Commands starting with `!` = Extension commands (implemented in DLLs).