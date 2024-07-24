# Template Method

**Forces:**
 When writing code, there are times when multiple methods and objects may share large amounts of identical code, suggesting commonality between them, even if they vary in some or all of their details. This can lead to the bloating of a program wiht repeat code, while also adding redundant complexity to its implementation and upkeep.

 When these scenarios come up when designing and writing a program, the code should instead capture the parts of itself that overlap, while still implementing its unique identity and behavior where it needs to.

**Resolution:**
Extract the commonanlities between the versions of the functions that are similar and put them in one method. This template method can then, when handling part of the code that needs to vary in it's behavior, outsource those instructions to different parts of the program.

Two ways of achieving this, are through Blackbox and Whitebox Specialization, each delegating different parts of the method to different areas of the code in their own way.

**Whitebox Specialization**\
In Whitebox Specialization, template methods exists in superclasses, that through the implementation of abstract and overriden methods, enable their subclasses to override the parts of the template method that they need to handle uniquely.

For example, in java this may look something like:
```java
public abstract class BusinessEarnings {
    protected double balance;
    protected abstract void updateBalance();

    protected void applyFees() {

    }

    protected BusinessEarnings(double bal) {
        setBalance(bal);
    }

    public final double getBalance() {
        return balance;
    }

    public final void setBalance(double bal) {
        this.balance = bal;
    }

    public final int runTransaction() {
        System.out.println("Balance before transaction: $" + Double.toString(balance));
        updateBalance();
        applyFees();
        System.out.println("Balance after transaction: $" + Double.toString(balance));
    }
}

public class Interest extends BusinessEarnings {
    private double interestRate;

    public Interest (double bal, double rate) {
        super(bal);
        setInterestRate(rate);
    }

    public void setInterestRate(double rate) {
        this.interestRate = 1.0 + rate; //add rate to one to make it a multiplier
    }

    public void updateBalance() {
        super.balance = super.balance * 1.03;
    }
}

public class PrintMaker extends BusinessEarnings {
    private double printCost;
    private double matCost;

    public PrintMaker(double bal, double retail, double expenseCost) {
        super(bal);
        setPrintCost(cost);
    }

    public void setPrintCost(double cost) {
        this.printCost = cost;
    }

    public void setMatCost(double cost) {
        this.matCost = cost;
    }

    public void updateBalance () {
        super.balance = super.balance + this.printCost;
    }

    @Override
    public void applyFees() {
        super.balance = super.balance - this.matCost;
    }
}

public class Finances () {
    public static void main(String[] args) {
        Interest interestEarnings = new Interest(1.0, .07);

        PrintMaker printEarnings = new PrintMaker(1.0, 20.00, 5.00);

        System.out.println("Print Maker Transaction")
        printEarnings.runTransaction();
        System.out.println("");
        System.out.println("Interest Transaction")
        interestEarnings.runTransaction();
        System.out.println("");
    }
}
```

Output:
```
Print Maker Transaction
Balance before transaction: $1.0
Balance after transaction: $16.0

Interest
Balance before transaction: $1.0
Balance after transaction: $1.07

```
\
**Blackbox Specialization**
For Blackbox Specialization, the template method, instead of existing in a superclass, exists as an interface, that will delegating the parts of it that need to differ to service provider objects, when needed.

```java
public interface MilitaryBranch {
    public String printName();
}

public class Army implements MilitaryBranch {
    public String printName() {
        System.out.println("Army");
    }

    public void deployTroops() {
        System.out.println("Boots are now on the ground");
    }
}

public class Navy implements MilitaryBranch {
    public String printName() {
        System.out.println("Navy");
    }

    public void formBlockade() {
        System.out.println("No ships across this line");
    }
}

public class AirForce implements MilitaryBranch {
    public String printName() {
        System.out.println("Air Force");
    }

    public void flySortie() {
        System.out.println("Fox 3; bird away");
    }
}

public class Military {
    public static void main(String[] args) {
        Army army = new Army();
        Navy navy = new Navy();
        AirForce airForce = new AirForce();

        army.printName();
        army.deployTroops();
        navy.printName();
        navy.formBlockade();
        airForce.printName();
        airForce.flySortie();
    }
}
```

Output:
```
Army
Boots are now on the ground
Navy
No ships across this line
Air Force
Fox 3; bird away
```