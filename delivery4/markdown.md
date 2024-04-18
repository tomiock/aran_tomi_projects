---
authors: "Tomas Ockier", "Aran Oliveras"
date: 18-04-2024
---

# Part A: Recursion

# Part B: Hashing

## Exercise 1
#### Question A
The table `C` is the one that implements the function  $h(x) = x \mod 10$, for a key $x$. Because we handle the collision using linear probing, an element $x$ will be placed in the first empty cell after $h(x)$.

#### Question B
The method apply in order to resolve collision is chaining, where keys with the same result are appended to a list located in the corresponding position. All of them could  result in the table `D`, because the order between keys that have the same result is not altered between the four different possibilities.

## Exercise 2
The functions have been implemented in file `hash.c`. Similar loops to the ones in the other data structures that we learned have been used.
