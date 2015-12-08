Alkalmazásfejlesztés házi
=========================

Minimális feladatok (e nélkül a házi feladat értékelhetetlen és nem ér pontot):

-   **DONE** A kliens programnak C++­ban, Qt és QML­ben, qmake és gcc toolchainnel kell készülnie, GIT verziókövetéssel.
-   **DONE** Grafikus felülettel kell rendelkeznie, ami parancsokat tud küldeni és állapotot tud fogadni a robottól vagy egy szimulátortól.
-   **DONE** A szimulátorral TCP socketen, soros porton vagy bluetoothon keresztül kell kommunikálnia.
-   **DONE** Egy parancs kiadására (pl. start) a visszakapott adatokból egyértelműen látszania kell, hogy a robot (igazi vagy szimulált) tényleg elindult.
-   A leadott program a ZIP­et kitömörítve további függőségek nélkül induljon el egy Windows 8 vagy Ubuntu virtuális gépen. (Legyen a ZIP­ben a futtatható program is.)
    Természetesen ha egy igazi robot jelenléte kell neki, akkor nem gond, ha nem működik minden funkció, de induljon el és ezt a tényt esztétikus formában jelezze.

Alap feladatok
--------------

-   **DONE** A robot állapot leírásában kell lennie skalár, vektor és szöveges (pl. log üzenetek) adatoknak is.
-   **DONE** Az aktuális állapot szövegesen és a vektor érték(ek) esetében grafikusan is jelenjen meg.
-   **DONE** A korábbi állapotok szövegesen és grafikusan jelenjenek meg (redundancia nem kell, minden úgy jelenjen meg, ahogy logikusabb, csak legyen szöveges és grafikus is).
-   **DONE** Az alkalmazás használjon legalább 5 Qt­s signalt.
-   A dokumentáció készüljön a forráskód alapján (kiegészítve egyéb fájlokkal) Doxygen segítségével.
-   **DONE** A dokumentációban legyen legalább 1 UML class diagram és legalább 1 UML szekvencia diagram.
-   **DONE** A kliens program felhasználói felületet legyen esztétikus. Például az ablakot átméretezve ne essen szét az egész, hanem kövesse az átméretezést.
-   **DONE** A GIT repositoryban látszódjanak a fejlesztés során készült commitok, vagyis ne egyetlen commit rakja be a kész programot a repositoryba a munka legvégén. A commitok ne szélsőségesen csak egy csapattagtól származzanak. A commit megjegyzések legyenek kifejezőek.
-   **DONE** A GIT repositoryban látszódjon, hogy a munka során a csapat használt brancheket is. Ne egy lineáris commit lánc legyen. (Arra hivatkozni nem ér, hogy voltak branchek, csak mindig rebaselték őket.)

Bónusz pontok
-------------

(a leadott dokumentációban külön kiemelve)

-   **DONE** 3p: A repository a githubon vagy bitbucketen van és meg van osztva az előadóval, aki így folyamatában is látja a fejlesztést.
-   5p: Öntesztelő funkció a robot számára. A tesztet futtathatja a kliens program is, de a robot firmwareje is. A lényeg, hogy van öntesztelési funkció.
-   2p: A dokumentáció számos UML diagramot használ, a leírások kihasználják a Markdown lehetőségeit, valamint a dokumentációban vannak hivatkozások, @see, @warning stb. parancsok.
-   **DONE** 2p (+1p): A forráskód használ smart pointereket. weak\_ptr esetén +1 pont jár.
-   3p: Tervezési minták azonosítása a programban: minimum 3 hely azonosítása a forráskódban (dokumentációba beleírva), ahol egy tervezési minta szerepel.
-   4p: QTest unit teszt, legalább 3 eltérő test case.
-   5p: A fejlesztés során tapasztalt tanulságok részletes összefoglalása egy publikálható jegyzet (“snippet”) formájában, githubon pull request formájában leadva.

