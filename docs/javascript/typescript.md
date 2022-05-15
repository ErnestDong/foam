---
tags: js
---
# typescript

## 带类型注解的 [[javascript]]

### type

like typing in python. support union

`any` is a type that indicates all type.

### interface

不是 [[python]]的鸭子类型， interface 制定了需要满足什么条件

```typescript
interface Person{
    name: string;
    age?: number; // optional
}

class person implements Person{
    constructor(name: string, age: number){}
    greet(){console.log(this.name)}
}
```

### generic

like template in [[Cpp]]

```typescript
function greeting<T>(name: T):T{
    return name
}

interface Book<T>{
    id: string;
    name: string;
    data: T
}
```

## [[react]] tsx

```sh
# npm create-react-app tsx-example --template typescript
npm init vite tsx-example --template react-ts
```