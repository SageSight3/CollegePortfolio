# Singleton

**Forces:** Singletons are objects, that only one instance of should exist. 

**Resolution:** Singletons are useful for objects that don't vary between different different "instances" (in the sense of multiples), of the object. The contents of singletons should be immutable and inaccessible from the outside.

**Java Implementation**

```java
public final class Thingy {
    public static final Thingy aSingleton = new Singleton();
    private E singletonInfoOne = "info1";
    private E singletonInfoTwo = 17402;
    private E singletonInfoEtc = "etc.";

    private static Thingy() {
    }

    public static Thingy getSingleton() {
        return aSingleton;
    }

    //methods
}
```
Reference: https://www.baeldung.com/java-private-constructors

The class is declared as final to ensure and convey it's immutability. The singleton object itself, is also declared as static, so it belongs to the class, making it so only one will exist.

Alternatively, the singleton can be a static private variable with a static getter method.