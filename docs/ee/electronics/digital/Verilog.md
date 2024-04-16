---
tags: Hardware
---

# Verilog

## 语法

由模块组成，模块内部由端口、数据类型、信号声明、行为描述组成。

```verilog
module block1(a,b,c,d) //端口定义
input a,b,c;           //IO说明
output d;
wire x;                //信号类型声明
assign x = a & b;      //功能描述，取与
assign d = x | c;      //取或
endmodule
```

描述行为的方式有三种：

- `assign`：连续赋值，用于组合逻辑
- `myand(a,b,c)`：用元件例化
- `alwaus`：时序逻辑

```verilog
always @(posedge clk) //时序逻辑，时钟上升沿触发
begin
    if (reset) begin
        q <= 1'b0;
    end else begin
        q <= d;
    end
end
```

## 数据类型

- `reg`：寄存器
- `wire`：线，可以是任意的信号
- `parameter`：常量

数字用“位宽'进制数字”表示，比如 `8'b1010`。默认 32 位 10 进制。
