# Dependency Injection

**Forces:**
How can we ensure a class has any dependencies it needs, and how do we release those dependencies once they're no longer needed.

**Resolution:**
If a class has dependencies and its creator knows when they'll no longer be needed, create objects for them, and initialize them. Then, then the class invokes its constructor, pass those dependency objects with the constructor's other args, and release them, once they're no longer needed