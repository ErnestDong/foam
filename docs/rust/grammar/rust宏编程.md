---
tags: rust
---

# rust 宏编程

`#[macro_export]`  注释将宏进行了导出，其它的包就可以将该宏引入到当前作用域中。
在 Rust 中宏分为两大类：

- 声明式宏 declarative macros `macro_rules!`，类似 C++的[[macro]]，将被废弃
- 三种**过程宏( *procedural macros* )**过程宏跟函数较为相像，但过程宏是使用源代码作为输入参数，基于代码进行一系列操作后，再输出一段全新的代码
  - `#[derive]`派生宏，可以为目标结构体或枚举派生指定的代码，例如  `Debug`  特征，输出的代码并不会替换之前的代码
  - 类属性宏(Attribute-like macro)，用于为目标添加自定义的属性
  - 类函数宏(Function-like macro)，看上去就像是函数调用

## 声明式宏

```rust
#[macro_export] // 将宏导出让别人用
match_rules! vec{ // `vec!`宏
    ( $( $x:expr ),* ) => { // 匹配参数，`$x:expr` 会匹配任何表达式并给予该模式一个名称：`$x`；`*` 说明之前的模式可以出现零次也可以任意次，这里出现了三次
        {
            let mut temp_vec = Vec::new();
            // `$()` 中的 `temp_vec.push()` 将根据模式匹配的次数生成对应的代码
            $(
                temp_vec.push($x);
            )*
            temp_vec
        }
    };
}
```

## 过程宏

当创建过程宏时，它的定义必须要放入一个独立的包中，且包的类型也是特殊的，它必须是一个名为  `proc-macro`  的库类型，宏所在的包名必须以  `derive`  为后缀，这样才能被 Rust 编译器识别。

### 派生宏

根据[[AST]]构建特征实现代码

```rust
extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn;

#[proc_macro_derive(HelloMacro)]
pub fn hello_macro_derive(input: TokenStream) -> TokenStream {
    // 基于 input 构建 AST 语法树
    let ast = syn::parse(input).unwrap();  // `syn::parse` 调用会返回一个 `DeriveInput` 结构体来代表解析后的 Rust 代码，
    // 构建特征实现代码
    impl_hello_macro(&ast)
}

fn impl_hello_macro(ast: &syn::DeriveInput) -> TokenStream {
    let name = &ast.ident;
    let gen = quote! {
        // 把 name 用`quote!`转换过去
        impl HelloMacro for #name {
            fn hello_macro() {
                println!("Hello, Macro! My name is {}!", stringify!(#name));
            }
        }
    };
    gen.into()
}

#[derive(HelloMacro)]
struct Sunfei; // Hello, Macro! My name is Sunfei!
```

### 属性宏

类属性宏的定义函数有两个参数：

- 第一个参数时用于说明属性包含的内容：`Get, "/"`  部分
- 第二个是属性所标注的类型项，在这里是  `fn index() {...}`，注意，函数体也被包含其中

```rust
#[route(GET, "/")]
fn index() {}
```

### 函数宏

类函数宏可以让我们定义像函数那样调用的宏，使用形式则类似于函数调用

```rust

#[proc_macro]
pub fn sql(input: TokenStream) -> TokenStream {}

sql!(SELECT * FROM posts WHERE id=1);
```

[//begin]: # "Autogenerated link references for markdown compatibility"
[macro]: ../../cpp/macro.md "macro"
[ast]: ../../compilers/model/AST.md "AST"
[//end]: # "Autogenerated link references"
