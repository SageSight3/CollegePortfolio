# Builder

**Forces:**
How do we build an assembly of objects from a specification?

**Resolution:**
Have a class (consider using visiter pattern) that knows how to outsource the construction of it's specifications' components to part suppliers (factories), then arranges those components relative to the layout outlined by the specification.

A builder can be thought of as a contractor

**Preceding Patterns**
Specification
Application

**Following Patterns**
Factory Method
Abstract Method

