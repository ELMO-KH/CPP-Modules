# تجاوز Memory Isolation

## ❌ المشكل:
- كل process له memory space خاص به
- Linux يمنع الوصول المباشر لـ memory process آخر

## ✅ الحلول:

### 1. **Shared Library** (الأفضل)
```bash
# ننشئو shared library فيها الدالة
c++ -shared -fPIC myFunc.cpp -o libmyfunc.so

# البرامج كلها تستعمل نفس المكتبة
```

### 2. **Shared Memory**
```c++
// البرنامجين يستعملو نفس memory segment
shm_open(), mmap()
```

### 3. **Unix Sockets / Pipes**
```c++
// برنامج يرسل request، الآخر ينفذ الدالة
```

### 4. **ptrace()** (للـ debugging)
```c++
// برنامج يتحكم في process آخر
// معقد وخطير!
```
