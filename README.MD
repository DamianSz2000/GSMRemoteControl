# GSM Zdalne Sterowanie z wykorzystaniem SIM800L 🚀

## Opis 📋
Projekt umożliwia zdalne sterowanie urządzeniem za pomocą sieci GSM. Po odebraniu połączenia moduł SIM800L nasłuchuje tonów DTMF. Wprowadź 4-cyfrowy kod, a jeśli jest poprawny – dioda LED zaświeci się na 5 sekund! 💡

## Wymagane komponenty 🔧
- Arduino (np. UNO)
- Moduł GSM SIM800L
- Dioda LED
- Kondensatory
- Rezystor do LED
- Przewody połączeniowe
- Zasilanie 5V/2A
- Karta SIM z usługami głosowymi

## Schemat elektryczny 🗺️


## Konfiguracja ⚙️
1. Otwórz projekt w Arduino IDE.
2. Upewnij się, że masz zainstalowaną bibliotekę SoftwareSerial.
3. W pliku `main.ino` dostosuj kod PIN karty SIM w komendzie `AT+CPIN`.
4. W razie potrzeby zmień wartość `correctCode`.

## Działanie 🎯
1. Moduł loguje się do sieci GSM.
2. Odbiera połączenie (`RING`) i odpowiada `ATA`.
3. Nasłuchuje tonów DTMF.
4. Po wpisaniu 4-cyfrowego kodu:
   - ✅ Poprawny: `ATH`, LED świeci 5 s 💡
   - ❌ Niepoprawny: `ATH` i reset.
5. System wraca do nasłuchiwania kolejnych połączeń. 🔄
