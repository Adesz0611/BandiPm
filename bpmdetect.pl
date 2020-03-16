#!/usr/bin/perl
# © Copyright 2020 JSS & Hayer. All Rights Reserved.

use strict;   # szigorú Perl. Minden változót deklarálni kell, több dologért, szól, stb.

use Time::HiRes qw/gettimeofday/;  # gettimeofday függvény importálása a Time::HiRes modulból

# @avg tömb, ide kerülnek a mérések, innen átlagolunk
my @avg;

# ennyi mérés után adunk eredményt
my $measures = 10;

# eltároljuk a 
my $last = gettimeofday();


# ez egy függvény
sub getavg {
    my $all = 0; # a sima (nem tömb) változók $ jellel kezdődnek
    my $n = 0;   # Perl-ben nincs típus (int, char, long) 

    # az @avg tömb elemeit matematikailag sorbarendezve elmentjük a @tmp tömbbe
    # @avg változatlan marad
    # @tmp -be ugyan azok az elemek lesznek, mint az @avg-ben, csak sorbarendezve
    my @tmp = sort { $a <=> $b } @avg;

    # Ha a @tmp elemeinek száma megegyezik a $measures értékével, akkor megvágjuk a tömböt
    # A tömb elejéről és a végéről leszedünk pár elemet, mert a kiugró értékeket nem vesszük
    # bele az átlagolásba.
    if (scalar @tmp == $measures) {
        my $cut = int($measures / 4);  # az int() függvény egy szám egész részét veszi
        pop @tmp for (1..$cut);        # lecsípünk $cut darab elemet a @tmp tömb végéről
        shift @tmp for (1..$cut);      # lecsípünk $cut darab elemet a @tmp tömb elejéről
    }

    # Most jön az átlagszámítás. Összeadjuk az összes értéket, majd az
    # eredményt elosztjuk az értékek számával.
    # Végig iteráljuk a @tmp tömböt. A ciklusmagban a $_ speckó változó fogja hordozni
    # az éppen aktuális tömb elemét az iteráció során
    for (@tmp) {
        $all += $_;   # $all változóhoz hozzáadjuk tömb aktuális elemét ($_)
        $n++;         # $n = $n + 1
    }

    return $all / $n;
}

# itt folytatódik a program. Perl-ben nincs külön main függvény, hanem a
# legtetejéről indul.

print "Nyomkodd az ENTER-t az ütem alapján!\n";
printf "Az átlagolás miatt a %d. mérés után kezd pontos lenni!\n", $measures;

# örökké futó while ciklus
while () {
    <STDIN>;                                # várunk egy ENTER lenyomást az STDIN-ről (billentyűzetről ha terminálban vagyunk)
    my $time = gettimeofday();              # aktuális idő elmentése a $time -ba
    my $bpm = 1 / (($time - $last) / 60);   # ritmus kiszámítása az előző és a mostani időből
    $last = $time;                          # az új előző idő a mostani idő :)

    push @avg, $bpm;                        # @avg tömb végéhez hozzáadjuk a $bpm értéket
    shift @avg if (scalar @avg > $measures);# @avg tömb elejéből lecsípünk egyet, ha az @avg tömbünk nagyobb a kelleténél

    # amíg nem egyezik meg az @avg tömb elemeinek száma a $measures
    # értékével... másképp fogalmazva, amíg nincs elegendő mérésünk, addig csak
    # azt írjuk ki, hogy "Számol" és újraindítjuk a while ciklust
    # Az unless az if logikai ellentétje. Lehetett volna úgy is írni, hogy:
    # if (scalar @avg != $measures)  ... de az unless több szempontból jobb Perl-ben
    unless (scalar @avg == $measures) {
        print "Számol...      ";
        next;  # újraindítja a while ciklust
    }

    # minden fasza, van eredmény, ki is írjuk, persze int() függvénnyel, mert
    # nem kell a bpm-be tizedes jegy
    printf "%d bpm    ", int(getavg());
}


