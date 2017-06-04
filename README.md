# SimpleCompiler
Compilers Principles' coursework

<p align="center">
  <a href="https://github.com/Glossy">
    <img src="https://avatars1.githubusercontent.com/u/20094589?v=3&s=400" width=72 height=72>
  </a>

  <h3 align="center">SimpleCompiler</h3>

  <p align="center">
    A C++ simple compiler for a language drawing basic graphics using Qt Creator5.70
    <br>
    This a program of school on the machine experimental.It is a date backup. 
    <br>
    <a href="https://github.com/Glossy/SimpleComplier"><strong>Visit SimpleCompiler &raquo;</strong></a>
  </p>
</p>

<br>

# Table of contents

## Presentation
- [Presentation](#Presentation)

## Syntax & Semantics
- [Synatax](#PriorityQueue)
- [Semantics](#Semantics)

## Scanner
- [Scanner](#Scanner)

## Parser
- [Parser](#Parser)

## Semantic Analysis
- [Semantic Analysis](https://github.com/Glossy/SimpleComplier/tree/master/src/Parser.h)

### Presentation
---
- [Presentation](https://github.com/Glossy/SimpleComplier/tree/master/docs)
    - MainWindow
       ![image](https://github.com/Glossy/SimpleComplier/blob/master/docs/%E7%BC%96%E8%AF%91%E5%99%A8%E7%95%8C%E9%9D%A2.png)
    - Scanner
       ![image](https://github.com/Glossy/SimpleComplier/blob/master/docs/%E8%AF%8D%E6%B3%95%E5%88%86%E6%9E%90.png)
    - Parser
       ![image](https://github.com/Glossy/SimpleComplier/blob/master/docs/%E8%AF%AD%E6%B3%95%E5%88%86%E6%9E%90.png)
    - Drawing Pic
       <br>
       ![image](https://github.com/Glossy/SimpleComplier/blob/master/docs/%E7%94%BB%E5%9B%BE.png)

### Synatax
---
- [Synatax](https://github.com/Glossy/SimpleComplier/tree/master/docs)
    - Using specific drawing languange
	![image](https://github.com/Glossy/SimpleComplier/blob/master/docs/%E8%AF%AD%E6%B3%95%E5%92%8C%E8%AF%AD%E4%B9%89%E8%A6%81%E6%B1%82.png)

### Semantics
---
- [Semantics](https://github.com/Glossy/SimpleComplier/tree/master/docs)
    - For-Draw Statement
	![image](https://github.com/Glossy/SimpleComplier/blob/master/docs/for-draw%E8%AF%AD%E5%8F%A5%E8%A6%81%E6%B1%82.png)
    - Scale & Origin Statement
	![image](https://github.com/Glossy/SimpleComplier/blob/master/docs/scale%EF%BC%8Corigin%E8%A6%81%E6%B1%82.png)
    - Rot & Commented-Out Code Statement
	![image](https://github.com/Glossy/SimpleComplier/blob/master/docs/rot%26%E6%B3%A8%E9%87%8A%E8%A6%81%E6%B1%82.png)

### Scanner
---
- [Synatax](https://github.com/Glossy/SimpleComplier/tree/master/src/Scanner.h)
    - 识别不同的符号symbol（常数、参数、函数、保留字、运算符、分隔符）并存放进scanner.txt中

### Parser
---
- [Parser](https://github.com/Glossy/SimpleComplier/tree/master/src/Parser.h)
    - 读取scanner.txt中内容，采用递归向下的子程序构造DFA（确定性的状态机），生成表达式语法树并存储在parser.txt中


### Semantic Analysis
---
- [Semantic Analysis](https://github.com/Glossy/SimpleComplier/tree/master/src/Parser.h)
    - 语义分析写在了语法分析中，在生成语法树的同时翻译绘制函数图形





## Back to [Glossy](https://github.com/Glossy)





