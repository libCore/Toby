<p algin="center">
	<p style="font-size:40px;">Toby v0.1</p>
	<p style="font-size:32px;">Config language and Parser Designed by and for Humans.</p>
	<img src="https://img.shields.io/badge/toby-v0.1-blue"/>
</p>

# Overview

Toby focus on be the minimal and yet human alternative to any config parsers.

Toby is Hash table (map) friendly, making it very easy to integrate into your language and / or project.

**There is no types**. As commented below, everything will be interpreted as a string.

# Syntax

One of the keys of Toby is his syntax. Is extremely simple and easy to use and comprehend.

```toby
[Main]
lang=c++
```

We can strip the code above into three simple elements:

1. Scope (Tag)
2. Identifier (key)
3. Value (Data)

# Usage

Include the `Toby.hh` header file into your project.

# Why?

This config language was design to be extremely easy to modify and configure.
On top of that, we get rid of all **unecesary** stuff. That includes: types.

# License

BSD 2-Clause License

- Permisions: Commercial use, Distribution, Modification, Private use
- Conditions: License and copyright notice
- Limitations: Liability, Warranty