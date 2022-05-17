# vue

与 [[react]] 作用类似的 [[javascript]] 框架，更像是写 html。此外，vue 数据双向绑定，而 react 则是单向数据流。

## vue 语法

1. 模版(类似[[react]]的jsx) {{key}} 返回 js 中 `data()` 函数返回值，可以没有根标签
   1. 如果 `key` 是 html 标签会 raw 输出，需要是 `<span v-html="key"></span>`才能渲染
   2. 标签内渲染运行 javascript 需要用 "" 包裹
2. 指令
   1. `v-if` 条件渲染，可以用 `v-else-if` `v-else`，写在标签内
   2. `v-for` 循环遍历，需要指定 `:key`
   3. `v-bind` 绑定组件

    ```vue
    <template>
        <ul>
            <li v-for="i for i in keys" :key="i">{{i}}</li>
        </ul>
    </template>
    ```

3. 事件处理
   1. `v-on` or "@" 当，方法在 vue `method` 中用键值对导出或直接导出对象

    ```vue
    <script>
        export default{
            name: App,
            data(){
                return {count:1}
            },
            methods:{
                test(){
                    this.count++
                }
            }
        };
    </script>
    ```

`setup`

## vue 组件

### props

props 定义组件的参数，如组建接受 `{x:String}` 类型

导入组件(import)后需要注册组件到 components 里面，以标签形式传递组件

### 组件和页面

页面不重复利用，组件可重复利用，但其实都是 vue 文件

## vue 路由

与 [[react]] 路由类似，将一个 Single Page Application 绑定到不同的路径上。
