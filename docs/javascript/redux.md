---
tags: js
---
# Redux

[[react]]函数组件的状态在外部管理，类似于 client 端的数据库

1.  store 存放当前的数据
2.  state 数据仓库中存储的数据
3.  action 描述当前如何操作 state 状态
4.  dispatch 更改当前 state 的唯一方法
5.  reducer 返回新 state 的唯一方法
    
    ```jsx
    import createStore from 'redux'
    const addOne={
      type: "Add",
      num: 1
    }
    const reducer = (state=10, action)=>{
      switch(action.type){
        case "Add":
          return state + action.num
        default:
          return state
      }
    }
    store = createStore(reducer)
    console.log(store.getState())
    console.log(store.dispatch(addOne))
    console.log(store.getState())
    ```
