# Abstract Factory

**Forces:**
Different platforms will use different things that serve the same purpose

**Resolution:**
Configure a builder with a part supplier (factory), that implements the methods required by an abstract factory (either as interface?, subclass, or factory methods in an abstract factory class*). The builder should only send messages to its parts supplier that are supported by the latter's abstract facotry

Configure builder with a factory
factory supports interface of an abstract factory
builder will only send messages supported by the abstract factory

*in this case, the builder's part supplier class would be the abstract factory, with the factory methods being the part suppliers themselves?

**Preceding Pattern**
Factory
Builder
Application
Specification