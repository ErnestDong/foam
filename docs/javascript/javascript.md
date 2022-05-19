---
tags: js
---
# javascript

## == 和 ===

```js
console.log(1=='1'); // true
console.log(1==='1'); //false
```

## es6

### use `let` instead of `var`

`let` 可以定义局部变量而 `var` 不可以

### arrow functions

函数复杂写法是

```js
let arr = [1, 2, 4, 8];
let func = function (x) {
  return x * 2;
};
console.log(arr.map(func));
```

```js
let arr = [1, 2, 3, 5];
console.log(arr.map((x) => (x*2)))
```

### f-string

```js
let name="ernest"
console.log(`hello ${name}`)
```

### 对象传播操作符

解包时把剩余的对象传给该变量

### babel

讲 ES6 语法转换为 ES5 以支持浏览器

### 模块化

```js
/// common JS ，常在 node 中用
// import
http = require("http");
// export
module.export{
    a, b, c
};
```

```js
/// es6
// export
export function myfunc(){};
// import
import {myfunc} from "./myfunc";
```

### iterator

```js
let arr = [1, 2, 4]
for(let i=0; i<3; i++){console.log(i)}
for(let i of arr){console.log(i)}
```

### OOP

```js
class Person{
    constructor(name){
        this.name = name
    };
    hello(){
        console.log(this.name)
    }
};
let me = new Person("I");
console.log(me.hello())

class Student extends Person{
    constructor(name, studentNum){
        super(name);
        this.studentNum = studentNum;
    }
}
```

### [[协程|异步]]

#### promise

利用解决异步回调的问题。

```javascript
new Promise((resolve, reject)=>{
    console.log("try to resolve")
    if (resolvable){
        resolve()
    }else{
        reject()
    }
}).then(res=>{
    console.log("resolved")
    return 1
}, err=>{
    console.log("rejected")
})
```

除了 then 方法之外，promise 还有 catch  和 finally 两个方法用于捕获运行的错误

#### async 和 await

async 标记为异步函数，返回值是一个 promise 对象

await 相当于 then 等待完成

## [[浏览器模型]]
