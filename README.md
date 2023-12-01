# sophia2

The minimal bytecode interpreted successor to the
[sophia](https://github.com/xNaCly/Sophia) programming language.

Planned features:

- concise syntax
- somewhat complete standard library
- no oop but structures and structure attached functions
- datatypes:
  - number: all integers, floats and doubles are represented as number
  - string: structure containing the length and the content of the string
  - bool: true or false
  - array: dynamically growing list of elements
  - structures: collection of fields, key value

## Running locally

> Requires `make` and `gcc`.

```shell
git clone https://github.com/xnacly/sophia2
cd sophia2
make
```

## Supported language features

- [ ] arithmetic
- [ ] variables
- [ ] built-ins
  - [ ] print
  - [ ] println
- [ ] type inferring
- [ ] datatypes
  - [ ] number
  - [ ] string
  - [ ] bool
  - [ ] array
  - [ ] structure
- [ ] types for functions and structures
- [ ] functions
  - [ ] definition
  - [ ] call
  - [ ] return keyword
- [ ] functions attached to structures
- [ ] control flow
  - [ ] if
  - [ ] for
- [ ] standard library in c (performance!)
