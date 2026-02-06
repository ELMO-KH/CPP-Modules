# الفرق المهم!

## ❌ ما وقع في الحل ديالنا (Shared Library):

```
Program A                  Program B
    ↓                          ↓
    └─────→ libshared.so ←─────┘
           (المكتبة المشتركة)
```

- **Program A** ما عندو والو من Program B
- **Program B** ما عندو والو من Program A
- كلاهما يستدعيان دالة من **مكتبة خارجية مشتركة**

## البرامج ما كيتواصلوش مع بعضهم!

```c++
// programA.cpp
dlopen("./libshared.so")  // يحمل من ملف خارجي
// ما كيستدعيش دالة من programB

// programB.cpp  
dlopen("./libshared.so")  // يحمل نفس الملف الخارجي
// ما كيستدعيش دالة من programA
```

---

## 🔥 الهجوم الحقيقي (بدون إذن):

إذا بغيتي تستدعي دالة من برنامج **رغماً عنه**:

### 1. **ptrace() - Process Injection**

```c++
// يتطلب صلاحيات root
ptrace(PTRACE_ATTACH, target_pid, NULL, NULL);
// دابا نقدر نقرا ونكتب في memory ديالو
```

### 2. **/proc/[pid]/mem - Direct Memory Access**

```c++
// نقرا memory ديال process آخر (يتطلب صلاحيات)
int fd = open("/proc/12345/mem", O_RDWR);
pread(fd, buffer, size, address);
```

### 3. **LD_PRELOAD Hijacking**

```bash
# نحقن مكتبة في برنامج قبل ما يشتغل
LD_PRELOAD=./my_hijack.so ./victim_program
```

---

## ⚠️ كلها تتطلب:

1. **صلاحيات root** أو
2. **نفس المستخدم + ptrace enabled** أو  
3. **الضحية يشغل البرنامج بنفسه مع LD_PRELOAD**

---

## 🛡️ Linux يحميك:

```bash
# تحقق من الحماية
cat /proc/sys/kernel/yama/ptrace_scope
# 0 = أي process يقدر يستعمل ptrace على أي process ديالو
# 1 = فقط parent processes (الحماية الافتراضية)
# 2 = فقط root
# 3 = ممنوع نهائياً
```

---

## الخلاصة:

| الطريقة | يحتاج إذن؟ | يشتغل؟ |
|---------|-----------|--------|
| Shared Library | نعم (كلاهما يتفقان يستعملو نفس المكتبة) | ✅ |
| ptrace() | لا (هجوم) | ✅ (بصلاحيات) |
| Direct Memory | لا (هجوم) | ✅ (بصلاحيات) |
| LD_PRELOAD | نوعاً ما (الضحية يشغل مع المكتبة) | ✅ |
| Cross-process pointer | لا | ❌ (ممنوع) |
