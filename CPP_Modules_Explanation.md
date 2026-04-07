# شرح وحدات C++ - من CPP00 إلى CPP07

## مقدمة
هذا الملف يشرح بالتفصيل جميع وحدات لغة C++ من CPP00 إلى CPP07. كل وحدة تركز على مفهوم أساسي في البرمجة بـ C++.

---

## CPP00: Namespace و Classes و Member Functions

### ما هي Namespaces؟
Namespaces هي فضاء اسمي يُستخدم لتنظيم الأكواد وتجنب تضارب الأسماء. إذا كان لديك دالتان بنفس الاسم في namespaces مختلفة، لن يكون هناك تضارب.

```cpp
namespace MyNamespace {
    void myFunction() {
        std::cout << "Hello from MyNamespace" << std::endl;
    }
}

MyNamespace::myFunction(); // استدعاء الدالة
```

### Classes وMember Functions
Class هي قالب لإنشاء كائنات (Objects). تحتوي على:
- **Attributes (البيانات)**: متغيرات تخزن البيانات
- **Member Functions (الدوال)**: دوال تعمل على البيانات

```cpp
class Car {
private:
    std::string color;
    int speed;

public:
    Car(std::string c, int s) : color(c), speed(s) {}

    void drive() {
        std::cout << "السيارة " << color << " تسير بسرعة " << speed << std::endl;
    }

    void setSpeed(int s) {
        speed = s;
    }
};
```

### المعدلات (Access Modifiers)
- **public**: يمكن الوصول إليه من أي مكان
- **private**: يمكن الوصول إليه فقط من داخل الفئة
- **protected**: يمكن الوصول إليه من الفئات المشتقة

### Constructor و Destructor
- **Constructor**: دالة خاصة تُستدعى عند إنشاء كائن جديد
- **Destructor**: دالة خاصة تُستدعى عند حذف الكائن

```cpp
class Example {
public:
    Example() { std::cout << "تم إنشاء الكائن" << std::endl; }
    ~Example() { std::cout << "تم حذف الكائن" << std::endl; }
};
```

---

## CPP01: Memory Allocation و Pointers و References

### Pointers (المؤشرات)
مؤشر هو متغير يحتفظ بعنوان متغير آخر في الذاكرة.

```cpp
int x = 10;
int* ptr = &x;  // & تحصل على العنوان
std::cout << *ptr << std::endl;  // * تحصل على القيمة
std::cout << ptr << std::endl;   // تطبع العنوان
```

### Memory Allocation
استخدام `new` و `delete` لتخصيص وتحرير الذاكرة ديناميكياً:

```cpp
int* arr = new int[10];  // تخصيص مصفوفة
delete[] arr;            // تحرير الذاكرة

int* obj = new MyClass();  // تخصيص كائن
delete obj;                // تحرير الذاكرة
```

### References (المراجع)
مرجع هو اسم بديل لمتغير موجود. لا يمكن تغيير ما يشير إليه المرجع.

```cpp
int x = 10;
int& ref = x;  // مرجع لـ x
ref = 20;      // الآن x = 20
```

### الفرق بين Pointers و References:
| الخاصية | Pointer | Reference |
|--------|---------|-----------|
| يمكن أن يكون null | نعم | لا |
| يمكن تغييره | نعم | لا |
| يحتاج إلى dereference | نعم | لا |
| يأخذ مساحة في الذاكرة | نعم | لا |

---

## CPP02: Ad-hoc Polymorphism و Operator Overloading و Canonical Form

### Operator Overloading
تعريف كيفية تعامل العوامل مع أنواع مخصصة:

```cpp
class Vector {
public:
    int x, y;

    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
};

Vector v1(1, 2), v2(3, 4);
Vector v3 = v1 + v2;  // استخدام operator+
```

### Canonical Form (الشكل القياسي)
يجب أن تحتوي كل فئة على:
1. **Default Constructor**: بدون معاملات
2. **Copy Constructor**: نسخ كائن من كائن آخر
3. **Assignment Operator**: إسناد قيمة من كائن إلى آخر
4. **Destructor**: تنظيف الموارد

```cpp
class MyClass {
private:
    int* data;

public:
    MyClass() : data(nullptr) {}  // Default Constructor

    MyClass(const MyClass& other) {  // Copy Constructor
        data = new int(*other.data);
    }

    MyClass& operator=(const MyClass& other) {  // Assignment Operator
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }

    ~MyClass() {  // Destructor
        delete data;
    }
};
```

---

## CPP03: Inheritance (الوراثة)

### ما هي الوراثة؟
الوراثة تسمح لفئة بوراثة خصائص ودوال من فئة أخرى (فئة الأب).

```cpp
class Animal {
protected:
    std::string name;

public:
    Animal(std::string n) : name(n) {}
    virtual void makeSound() {
        std::cout << "صوت حيوان عام" << std::endl;
    }
};

class Dog : public Animal {
public:
    Dog(std::string n) : Animal(n) {}

    void makeSound() override {
        std::cout << name << " ينبح: واف واف!" << std::endl;
    }
};
```

### أنواع الوراثة:
1. **Public Inheritance**: الخصائص العامة تبقى عامة
2. **Protected Inheritance**: الخصائص العامة تصبح محمية
3. **Private Inheritance**: كل الخصائص تصبح خاصة

### Virtual Functions
تسمح بتعريف سلوك مختلف في الفئات المشتقة:

```cpp
class Base {
public:
    virtual void display() {
        std::cout << "Base" << std::endl;
    }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void display() override {
        std::cout << "Derived" << std::endl;
    }
};
```

---

## CPP04: Subtype Polymorphism و Abstract Classes

### Polymorphism (تعدد الأشكال)
القدرة على استخدام مؤشر أساسي للإشارة إلى كائنات فئات مشتقة:

```cpp
Base* ptr;
Dog dog("Rex");
Cat cat("Whiskers");

ptr = &dog;
ptr->makeSound();  // يطبع: واف واف

ptr = &cat;
ptr->makeSound();  // يطبع: مواء
```

### Abstract Classes (الفئات المجردة)
فئة تحتوي على دوال افتراضية خالصة. لا يمكن إنشاء كائن مباشر منها:

```cpp
class Shape {
public:
    virtual void draw() = 0;  // دالة افتراضية خالصة
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "رسم دائرة" << std::endl;
    }
};

// Shape s;  // خطأ: لا يمكن إنشاء كائن من فئة مجردة
Circle c;
c.draw();  // حسناً
```

### Pure Virtual Functions
دالة بدون تنفيذ في الفئة الأساسية:

```cpp
class Animal {
public:
    virtual void eat() = 0;  // يجب تنفيذها في الفئات المشتقة
    virtual ~Animal() {}
};
```

---

## CPP05: Repetition و Exceptions

### Try-Catch-Throw
معالجة الأخطاء في البرنامج:

```cpp
try {
    if (value < 0) {
        throw std::invalid_argument("القيمة لا يمكن أن تكون سالبة");
    }
    // كود آخر
} catch (const std::invalid_argument& e) {
    std::cerr << "خطأ: " << e.what() << std::endl;
} catch (const std::exception& e) {
    std::cerr << "استثناء عام: " << e.what() << std::endl;
}
```

### أنواع الاستثناءات:
- **std::exception**: الفئة الأساسية لجميع الاستثناءات
- **std::invalid_argument**: معامل غير صحيح
- **std::out_of_range**: قيمة خارج النطاق
- **std::runtime_error**: خطأ وقت التشغيل

### الدوال المخصصة Exception:

```cpp
class CustomException : public std::exception {
private:
    std::string message;

public:
    CustomException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};
```

### NoExcept
تحديد أن الدالة لا تطرح استثناءات:

```cpp
void safeFunction() noexcept {
    // هذه الدالة آمنة ولا تطرح استثناءات
}
```

---

## CPP06: Casts في C++

### Static Cast
تحويل آمن بين الأنواع المرتبطة:

```cpp
int x = 10;
double y = static_cast<double>(x);

Base* base = new Base();
Derived* derived = static_cast<Derived*>(base);  // تحويل مؤشر
```

### Dynamic Cast
تحويل مع التحقق من الصحة في وقت التشغيل. يُستخدم مع الوراثة:

```cpp
Base* base = new Derived();
Derived* derived = dynamic_cast<Derived*>(base);

if (derived != nullptr) {
    // التحويل نجح
    derived->derivedFunction();
} else {
    // التحويل فشل
    std::cout << "لم يكن الكائن من نوع Derived" << std::endl;
}
```

### Reinterpret Cast
تحويل بين أنواع غير مرتبطة (خطير جداً):

```cpp
int x = 10;
void* ptr = reinterpret_cast<void*>(&x);
int* intPtr = reinterpret_cast<int*>(ptr);
```

### Const Cast
إزالة أو إضافة const:

```cpp
const int x = 10;
int* ptr = const_cast<int*>(&x);
*ptr = 20;  // خطير: تعديل ثابت
```

### الفرق بين Casts:
| النوع | الاستخدام | الأمان |
|------|----------|--------|
| static_cast | تحويل أنواع معروفة | عالي |
| dynamic_cast | تحويل مع التحقق | عالي |
| reinterpret_cast | تحويل عام | منخفض |
| const_cast | إزالة const | متوسط |

---

## CPP07: Templates (القوالب)

### Class Templates
إنشاء فئة عامة تعمل مع أنواع مختلفة:

```cpp
template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    void push(const T& value) {
        elements.push_back(value);
    }

    T pop() {
        T value = elements.back();
        elements.pop_back();
        return value;
    }

    bool isEmpty() const {
        return elements.empty();
    }
};

Stack<int> intStack;
intStack.push(5);

Stack<std::string> strStack;
strStack.push("Hello");
```

### Function Templates
إنشاء دالة عامة:

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

int result1 = add<int>(5, 3);      // 8
double result2 = add<double>(5.5, 3.2);  // 8.7
```

### Template Specialization
حالات خاصة للنماذج:

```cpp
// النموذج العام
template <typename T>
void print(T value) {
    std::cout << "عام: " << value << std::endl;
}

// تخصص لـ const char*
template <>
void print<const char*>(const char* value) {
    std::cout << "نص: " << value << std::endl;
}
```

### Multiple Template Parameters:

```cpp
template <typename T, typename U>
class Pair {
private:
    T first;
    U second;

public:
    Pair(T f, U s) : first(f), second(s) {}

    T getFirst() const { return first; }
    U getSecond() const { return second; }
};

Pair<int, std::string> p(10, "عشرة");
```

### Variadic Templates
قوالب مع عدد متغير من المعاملات:

```cpp
template <typename... Args>
void printAll(Args... args) {
    (std::cout << ... << args);  // C++17
}

printAll(1, 2.5, "Hello");  // يطبع: 12.5Hello
```

### Template Constraints (C++20)
تحديد القيود على نوع القالب:

```cpp
template <typename T>
requires std::is_integral_v<T>
T multiply(T a, T b) {
    return a * b;
}

multiply(5, 3);           // حسناً
// multiply(5.5, 3.2);   // خطأ: ليس عدد صحيح
```

---

## ملخص المفاهيم الرئيسية

### CPP00: الأساسيات
- Namespaces لتنظيم الكود
- Classes و Member Functions
- Constructor و Destructor

### CPP01: إدارة الذاكرة
- Pointers و References
- new و delete
- الفرق بينهما

### CPP02: التحميل الزائد
- Operator Overloading
- Canonical Form (Big 3/5)

### CPP03: الوراثة
- الفئات الأساسية والمشتقة
- Virtual Functions
- Access Modifiers

### CPP04: Polymorphism
- الاستخدام المتعدد للفئات الأساسية
- Abstract Classes
- Pure Virtual Functions

### CPP05: معالجة الأخطاء
- Try-Catch-Throw
- Custom Exceptions
- noexcept

### CPP06: Casts
- Static Cast
- Dynamic Cast
- Reinterpret Cast
- Const Cast

### CPP07: القوالب
- Class و Function Templates
- Template Specialization
- Variadic Templates
- Template Constraints

---

## نصائح مهمة

1. **استخدم const**: اجعل الدوال والمعاملات const عندما لا تحتاج إلى تعديل البيانات
2. **تجنب الذاكرة المسربة**: استخدم delete مع new
3. **استخدم References**: أفضل من Pointers في كثير من الحالات
4. **وثق كودك**: أضف تعليقات واضحة
5. **اختبر كودك**: تأكد من أن الكود يعمل بشكل صحيح

---

**آخر تحديث: أبريل 2026**
