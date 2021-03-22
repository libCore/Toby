# Toby v0.1
## Config language and Parser Designed by and for Humans.</p>
<img src="https://img.shields.io/badge/toby-v0.1-blue"/>

# Objectives

Toby focuses on to be the minimal and yet human alternative to any config parsers.

Toby is Hash table (map) friendly, making it very easy to integrate into your language and/or project.

**There are no types**. As commented below, everything will be interpreted as a string.

# Example

```ini
#version 1
; Important! First line should be always the version.

[Host]
name = Zankuro

[Database]
server = 192.168.1.2
ports = 3000 3001 3002
max_connections = 100
; You can use `true` or `false`. But is more easy if using 1.
enabled = 1

; /!\ WIP Zone /!\ This is se additions upcoming for the version 2.
[servers]

; We can use dots.
[servers.alpha]
ip = 192.168.1.3

; Or slashes.
[servers/beta]
ip = 192.168.1.4
```

# Comparison with other languages / formats

Toby aims to be simple. It doesn't have any types, because you don't need it. 

Talking about types. We allow the programmer (you) to interpret the data of every field why your own. Look at Database#ports. It's three integers separated with white spaces.
You can interpret this as a string. Or if you strip and parse: an array of three integers.

As you can see, the syntax of Toby is minimalists. This is because you don't need anything more.