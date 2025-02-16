package test;

import java.util.ArrayList;
import java.util.List;

class X {}
class Y extends X {}
class Z extends Y {

X x = new X();
Y y = new Y();
Z z = new Z();

X[] ax = new X[10];
Y[] ay = new Y[20];

List<X> lx = new ArrayList<X>();
List<Y> ly = new ArrayList<Y>();
List<?> lw;
List<Object> lo = List.of();

List<? super X> lsX = List.of();
List<? super Y> lsY = List.of();

lsY = lsX;          // Correct
//lx = ly;          // Falsch: Incompatible Type
//lo = lw;          // Falsch: Incompatible Type
//y = x;            // Falsch, Supertypen können subtypen zugewiesen werden, aber nicht umgekehrt
x = z;              // Correct, da einem Supertypen ein Subtyp zugewiesen wird
lw = lx;            // Correct, da List<?> eine Zuweisung einer Liste beliebiger Spezialiserung erlaubt
//ly = lx;           // Falsch
x = new Y();         // 1/2
y = (Y) x;           // 2/2 Correct
x = new X();         // 1/2
//y = (Y) x;         // 2/2 Falsch, selber Fall wie y = x
ax = ay;             // Correct, da Arrays covariant sind, solange einem Supertypen ein Subtyp zugewiesen wird
//ay = ax;           // Falsch, da man Subtypen keine Supertypen zuweisen kann
lsX = lo;            // Correct, da Object ein supertype von X ist
//lsX = ly;          // Falsch, da Y kein Super von X ist
lsY = new ArrayList<X>(); // Correct, da X ein Super von Y ist
