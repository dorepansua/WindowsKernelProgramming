# 📄 Summary of Chapter 6: Kernel Mechanisms

| **Topic**                | **Key Concepts**                                                                                                                                              |
|--------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Thread Synchronization** | Multiple threads accessing shared data must be synchronized to prevent data races, crashes, and corruption.                                                  |
| **Dispatcher Objects**   | Kernel-provided synchronization primitives with **signaled / non-signaled** states. Threads can wait on them without using CPU.                              |
| **Wait Functions**       | `KeWaitForSingleObject`, `KeWaitForMultipleObjects` — allow waiting on one or more objects.                                                                  |
| **Wait Parameters**      | Includes `WaitReason`, `WaitMode`, `Alertable`, `Timeout`, `WaitType`, and object pointers.                                                                  |
| **Mutex (Mutant)**       | Allows only **one thread** to access a resource at a time. Supports recursive acquisition. Only the owning thread can release it.                            |
| **Mutex API**            | `KeInitializeMutex`, `KeWaitForSingleObject`, `KeReleaseMutex`. Mutex is signaled when free, non-signaled when owned.                                        |
| **Reader-Writer Lock**   | Executive Resource lock allows **multiple readers** or **one writer**. Ideal for data that is frequently read but infrequently written.                      |
| **Design Consideration** | Select the synchronization primitive based on access patterns: mutex for exclusive access, resource lock for read-heavy scenarios.                           |
