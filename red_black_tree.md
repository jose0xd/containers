Red-black tree: is a kind of self-balancing binary search tree.

## Properties:
1. A node is either red or black.
2. The root and leaves (NIL) are black.
3. Is a node is red, then its children are black.
4. All paths from a node to its NIL descendants contain the same number of black nodes.

## Operations: Search, Insert and Remove (the last 2 required rotations sometimes)

LEFT-ROTATE(T, x)
y = x.right         // set y
x.right = y.left    // turn y's left subtree into x's right subtree
if y.left != T.nil
    y.left.p = x
y.p = x.p           // link x's parent to y
if x.p == T.nil
    T.root = y
elseif x == x.p.left
    x.p.left = y
else x.p.right = y
y.left = x          // put x on y's left
x.p = y

## Insert: strategy
1. Insert Z and color it red
2. Recolor and rotate nodes to fix violation

### 4 scenarios
0. Z = root
    color black
1. Z.uncle = red
    recolor parent, grandparent and uncle
2. Z.uncle = black (triangle)
    rotate Z.parent in the opposite direction of Z (Z takes the position of its parent)
3. Z.uncle = black (line)
    rotate Z.grandparent in the opposite direction of Z, and recolor parent and grandparent

RB-INSERT(T, z)
y = T.nil
x = T.root
while x != T.nil
    y = x
    if z.key < x.key
        x = x.left
    else x = x.right
z.p = y
if y == T.nil
    T.root = z
elseif z.key < y.key
    y.left = z
    else y.right = z
z.left = T.nil
z.right = T.nil
z.color = RED
RB-INSERT-FIXUP(T, z)

RB-INSERT-FIXUP(T, z)
while z.p.color == RED
    if z.p == z.p.p.left
        y = z.p.p.right
        if y.color == RED
            z.p.color = BLACK       // case 1
            y.color = BLACK         // case 1
            z.p.p.color = RED       // case 1
            z = z.p.p               // case 1
        else if z == z.p.right
                z = z.p             // case 2
                LEFT-ROTATE(T, z)   // case 2
            z.p.color = BLACK       // case 3
            z.p.p.color = RED       // case 3
            RIGHT-ROTATE(T, z.p.p)  // case 3
    else (same as then clause with
        "right" and "left" exchanged)
T.root.color = BLACK                // case 0

## Remove: strategy
1. transplant: helps us move subtrees within the tree
2. delete: deletes de node
3. delete_fixup: fixes any red-black violations

### 1. transplant
```python
def transplant(self, u, v):
    if u.p == None:
        self.root = v
    elif u == u.p.left:
        u.p.left = v
    else:
        u.p.right = v
    v.p = u.p
```

### 2. delete
1. left child is NIL
2. right child is NIL
3. neither child is NIL

```python
# case 1
if z.left == self.NIL:
    x = z.right
    self.transplant(z, z.right)
# case 2
elif z.right == self.NIL:
    x = z.left
    self.transplant(z, z.left)
# case 3
else:
    y = self.minimum(z.right)
    y_orig_color = y.color
    x = y.right
    if y.p == z:
        x.p = y
    else:
        self.transplant(y, y.right)
        y.right = z.right
        y.right.p = y
    self.transplant(z, y)
    y.left = z.left
    y.left.p = y
    y.color = z.color
if y_orig_color == BLACK
    self.delete_fixup(x)
```

### 3. delete_fixup(x)
w is the sibling of x
1. w is red
2. w is black, and w.left & w.right are black
3. w is black, and w.left is red and w.right is black
4. w is black, and w.right is red

```python
while x != self.root and x.color == BLACK:
    if x == x.p.left:
        w = x.p.right
        # type 1
        if w.color == RED:
            w.color = BLACK
            x.p.color = RED
            self.left_rotate(x.p)
            w = x.p.right
        # type 2
        if w.left.color == BLACK and w.right.color == BLACK:
            w.color = RED 
            x = x.p 
        else:
            # type 3
            if w.right.color == BLACK:
                w.left.color = BLACK
                w.color = RED
                self.right_rotate(w)
                w = x.p.right
            # type 4
            w.color = x.p.color 
            x.p.color = BLACK 
            w.right.color = BLACK 
            self.left_rotate(x.p)
            x = self.root
    else:
        w = x.p.left
        # type 1
        if w.color == RED:
            w.color = BLACK
            x.p.color = RED
            self.right_rotate(x.p)
            w = x.p.left
        # type 2
        if w.right.color == BLACK and w.left.color == BLACK:
            w.color = RED 
            x = x.p 
        else:
            # type 3
            if w.left.color == BLACK:
                w.right.color = BLACK
                w.color = RED
                self.left_rotate(w)
                w = x.p.left
            # type 4
            w.color = x.p.color 
            x.p.color = BLACK 
            w.left.color = BLACK 
            self.right_rotate(x.p)
            x = self.root
x.color = BLACK
```