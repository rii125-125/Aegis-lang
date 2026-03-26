# What is Aegis-lang? 🤔
Aegis-lang is,
> A language that makes type safety and robust code more intuitive and easier to understand.

Aegis-lang is completely open source, and we welcome issues from anyone!

# What are its key features?
The main features are:
1. It is a statically typed language that does not use type inference.
2. It does not have a garbage collector.
3. Access rights are defined by the language specification.
4. It allows you to write robust code.

The two points to note are **"no garbage collector"** and **"access rights defined by the language specification"**.

## 1. A statically typed language that does not use type inference
Languages known as statically typed languages, such as Java, Go, and Rust, allow you to write code by adding type annotations. However, for many developers, the mechanism known as type inference renders static typing meaningless.
Furthermore, omitting types can lead to confusion. To avoid these issues, Aegis-lang does not include type inference and requires that at least one type be specified.

## 2. No GC
GC stands for Garbage Collection. GC is a mechanism where the compiler or runtime automatically manages memory. It is currently used in most languages.
However, since programmers cannot directly manipulate memory, they must consider the behavior and scope of variables when referencing them. To prevent such confusion, developers manage memory by utilizing access rights.

## 3. Access Rights as a Language Specification
Access rights refer to the permissions held by all declared variables. This makes it easier to track memory references even without GC.
While Rust’s **ownership** is a similar concept, it is distinct from this.

## 4. Writing Robust Code
Since the language does not include type inference, developers must define types themselves. This means that even if an error occurs, type mismatches and other issues are immediately apparent, making them easier to address.