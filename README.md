🏴‍☠️ Pirate Shooter - Bitwa Morska Pirate Shooter to dynamiczna gra zręcznościowa 2D typu "Vertical Shooter" stworzona w języku C++ z wykorzystaniem biblioteki SFML. Wciel się w rolę kapitana statku pirackiego, niszcz wrogie okręty i przetrwaj jak najdłużej na otwartym morzu!

🚀 Funkcjonalności

  🎮 Gameplay Nieskończona rozgrywka: Walcz z falami wrogów, dopóki nie zostaniesz zestrzelony lub nie zderzysz się ze statkiem przeciwnika.

Dynamiczny poziom trudności: Z każdym zestrzelonym wrogiem gra przyspiesza (skracany czas respawnu przeciwników).

System wyników: Zdobywaj punkty za każdego zniszczonego wroga.

  💻 Rozwiązania Techniczne Silnik Gry (Game Loop): Własna implementacja pętli gry z obsługą DeltaTime i zarządzaniem stanami (Menu / Gra / Game Over).

Szyfrowanie Danych: Wyniki zapisywane są do pliku wyniki.txt z wykorzystaniem algorytmu szyfrującego (przesunięcie ASCII), aby zapobiec edycji wyników.

System Kolizji (Hitboxy): Zoptymalizowane wykrywanie kolizji metodą AABB ze zmniejszonymi hitboxami dla większej precyzji (ignorowanie przezroczystych krawędzi).

Skalowanie Zasobów: Automatyczne dopasowywanie tekstur tła do rozmiaru okna gry.

Zarządzanie Pamięcią: Pełne wykorzystanie wskaźników i dynamicznej alokacji (new/delete) oraz kontenerów std::vector do zarządzania obiektami.

🛠️ Technologie Projekt został zrealizowany przy użyciu:

Język: C++

Biblioteka: SFML 2.6.1 (Graphics, Window, System)

IDE: Visual Studio 2022

Zasoby: Pliki graficzne .png/.jpg, czcionki .ttf, audio .ogg

🕹️ Sterowanie Strzałki/ A,D - sterowanie na boki Spacja - strzelanie Enter - Rozpoczęcie gry Esc - wyjście z gry

📥 Jak uruchomić (Instalacja) Pobranie gotowej gry Pobierz plik .zip z repozytorium Wypakuj archiwum. Uruchom plik SpaceShooterC++.exe
Szyfrowanie Danych: Wyniki zapisywane są do pliku wyniki.txt z wykorzystaniem algorytmu szyfrującego (przesunięcie ASCII), aby zapobiec edycji wyników.

System Kolizji (Hitboxy): Zoptymalizowane wykrywanie kolizji metodą AABB ze zmniejszonymi hitboxami dla większej precyzji (ignorowanie przezroczystych krawędzi).

Skalowanie Zasobów: Automatyczne dopasowywanie tekstur tła do rozmiaru okna gry.

Zarządzanie Pamięcią: Pełne wykorzystanie wskaźników i dynamicznej alokacji (new/delete) oraz kontenerów std::vector do zarządzania obiektami.

🛠️ Technologie
Projekt został zrealizowany przy użyciu:

Język: C++

Biblioteka: SFML 2.6.1 (Graphics, Window, System)

IDE: Visual Studio 2022

Zasoby: Pliki graficzne .png/.jpg, czcionki .ttf

🕹️ Sterowanie
Strzałki/ A,D - sterowanie na boki
Spacja - strzelanie
Enter - Rozpoczęcie gry
Esc - wyjście z gry

📥 Jak uruchomić (Instalacja)
Pobranie gotowej gry
Pobierz plik .zip z repozytorium
Wypakuj archiwum.
Uruchom plik SpaceShooterC++.exe.
